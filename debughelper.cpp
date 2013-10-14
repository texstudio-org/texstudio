#include "debughelper.h"
#include "mostQtHeaders.h"
#include "smallUsefulFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#ifndef NO_CRASH_HANDLER
#if (defined(x86_64) || defined(__x86_64__))
#define CPU_IS_X86_64
#elif (defined(ppc) || defined(__ppc__) || defined(__powerpc__) || defined(__POWERPC__) || defined(PPC) || defined(__PPC) || defined(_ARCH_PPC))
#define CPU_IS_PPC
#elif (defined(ppc64) || defined(__ppc64__) || defined(__powerpc64__) || defined(__POWERPC64__) || defined(PPC64))
#define CPU_IS_PPC
#elif (defined(arm) || defined(__arm__))
#define CPU_IS_ARM
#elif (defined(ia64) || defined(__ia64__))
#define CPU_IS_IA64
#elif (defined(mips) || defined(__mips__) || defined(mipsel) || defined(__mipsel__))
#define CPU_IS_MIPS
#elif (defined(sparc) || defined(__sparc__))
#define CPU_IS_SPARC32
#elif (defined(s390x) || defined(__s390x__))
#define CPU_IS_S390_64
#elif (defined(s390) || defined(__s390__) )
#define CPU_IS_S390_31
#else
#define CPU_IS_X86_32
#endif


#if (defined(__unix__) || defined(unix) || defined(__linux__) || defined(linux) || defined(__gnu_hurd__) || defined(__FreeBSD__) || defined(__FreeBSD_kernel__))
#define OS_IS_LINUX_LIKE
#endif

#if (defined(OS_IS_LINUX_LIKE) || defined(Q_WS_MACX))
#define OS_IS_UNIX_LIKE
#endif

//===========================Abstract CPU model==========================

//platfom independent implementation of assembler instructions 
//(use case: before changing eip, the old eip must be pushed in the correct way on the stack, otherwise the 
//           backtrace doesn't show the function that actually crashed)
struct SimulatedCPU {
	char * pc; //e.g. eip, r15
	char * frame; //e.g. ebp, r11
	char * stack; //e.g. esp, r13
#if defined(CPU_IS_ARM) || defined(CPU_IS_MIPS) || defined(CPU_IS_PPC) || defined(CPU_IS_SPARC32)
	char * returnTo; //lr/r14
#endif
	
	inline void push(char * value){
		stack -= sizeof(void*); 
		*(char**)(stack) = value; 
	}
	inline char* pop(){
		char* temp = *(char**)(stack);
		stack += sizeof(void*); 
		return temp;
	}

	inline void jmp(char * value){
		pc = value;
	}

	inline void call(char * value);
	inline void ret();
	inline void enter(int size);
	inline void leave();
	

	void set_all(void* context);
	void get_all(void* context);
	void set_from_real();

	bool stackWalk();
	void unwindStack(){
		SimulatedCPU temp = *this;
		int frames = 0; 
		while (temp.stackWalk()) frames++;
		if (frames == 0) return;
		if (frames < 100) frames = frames - 10;
		else frames = frames - 100;
		while (frames > 0) { this->leave(); frames--; }
	}	

	int backtrace(void ** array, int size) {
		if (!pc || !frame) return 0;
		for (int i=0;i<size;i++)
			array[i] = 0;
		int i = 0;
		do {
			array[i] = pc;
			i++;
		} while (stackWalk() && i < size);
		return i;
	}
};

#ifdef CPU_CONTEXT_TYPE
#undef CPU_CONTEXT_TYPE
#endif
#ifdef RETURNTO_FROM_UCONTEXT
#undef RETURNTO_FROM_UCONTEXT
#endif

//===========================STACK TRACE PRINTING=========================

#ifdef Q_WS_WIN
#include <QSysInfo>
#include "windows.h"

//from wine
//dbghelp.h
typedef BOOL WINAPI (*SymInitializeFunc)(HANDLE, PCSTR, BOOL);

typedef struct _IMAGEHLP_SYMBOL64
{
	DWORD                       SizeOfStruct;
	DWORD64                     Address;
	DWORD                       Size;
	DWORD                       Flags;
	DWORD                       MaxNameLength;
	CHAR                        Name[1];
} IMAGEHLP_SYMBOL64, *PIMAGEHLP_SYMBOL64;

typedef struct _IMAGEHLP_LINE64
{
	DWORD                       SizeOfStruct;
	PVOID                       Key;
	DWORD                       LineNumber;
	PCHAR                       FileName;
	DWORD64                     Address;
} IMAGEHLP_LINE64, *PIMAGEHLP_LINE64;

typedef BOOL WINAPI (*SymGetSymFromAddr64Func)(HANDLE, DWORD64, PDWORD64, PIMAGEHLP_SYMBOL64);
typedef BOOL WINAPI (*SymGetLineFromAddr64Func)(HANDLE, DWORD64, PDWORD, PIMAGEHLP_LINE64);

#define CPU_CONTEXT_TYPE CONTEXT
#define LOAD_FUNCTION(name, ansiname) static name##Func name = (name##Func)GetProcAddress(dbghelp, ansiname);
#define LOAD_FUNCTIONREQRET(name, ansiname, result) LOAD_FUNCTION(name,ansiname) if (!name) return result;

HMODULE dbghelp = 0;

bool loadDbgHelp(){
	if (dbghelp != 0) return true;
	dbghelp = LoadLibraryA("dbghelp.dll");
	return dbghelp;
}

bool initDebugHelp(){
	if (dbghelp != 0) return true; //don't call syminitialize twice
	if (!loadDbgHelp()) return false;

	LOAD_FUNCTIONREQRET(SymInitialize, "SymInitialize", false);

	if (!(*SymInitialize)(((QSysInfo::windowsVersion() & QSysInfo::WV_DOS_based) == 0)?GetCurrentProcess():(HANDLE)GetCurrentProcessId(), 0, true))
		return false;
	return true;
}

QStringList backtrace_symbols_win(void** addr, int size){
	if (!initDebugHelp()){
		if (dbghelp) return QStringList(QString("Failed to initialize SymInitialize ") + QString::number(GetLastError()));
		else return QStringList("Failed to load dbghelp");
	}

	LOAD_FUNCTIONREQRET(SymGetSymFromAddr64, "SymGetSymFromAddr64", QStringList("Failed to load SymGetSymFromAddr64"));
	LOAD_FUNCTION(SymGetLineFromAddr64, "SymGetLineFromAddr64");

	HANDLE process = GetCurrentProcess();

	_IMAGEHLP_SYMBOL64* symbol = (_IMAGEHLP_SYMBOL64*)malloc(sizeof(_IMAGEHLP_SYMBOL64) + 256);
	QStringList res;
	for (int i=0;i<size;i++) {
		DWORD64 displacement = 0;
		DWORD displacement32 = 0;
		ZeroMemory(symbol, sizeof(_IMAGEHLP_SYMBOL64));
		symbol->SizeOfStruct = sizeof(_IMAGEHLP_SYMBOL64);
		symbol->MaxNameLength = 256;

		_IMAGEHLP_LINE64 line;

		QString cur;

		if ((*SymGetSymFromAddr64)(process, (DWORD64)addr[i], &displacement, symbol))
			cur = QString::fromLocal8Bit(symbol->Name)+"+"+QString::number(displacement);
		else
			cur = "??? error: " + QString::number(GetLastError());


		if (SymGetLineFromAddr64) {
			if ((*SymGetLineFromAddr64)(process, (DWORD64)addr[i], &displacement32, &line))
				cur += " in " + QString::fromLocal8Bit(line.FileName)+":"+QString::number(line.LineNumber);
		}

		res << cur;
	}
	return res;
}

QString temporaryFileNameFormat(){
	return QDir::tempPath() + QString("/texstudio_backtrace%1.txt");
}

#else
#include "execinfo.h"
QString temporaryFileNameFormat(){
	return "/tmp/texstudio_backtrace%1.txt";
}
QStringList backtrace_symbols_win(void**, int){
	return QStringList();
}

#endif



void print_backtrace(const SimulatedCPU& state, const QString& message){
#ifdef Q_WS_WIN
	qDebug("%s", qPrintable(message));
#define PRINT(...) do { qDebug(__VA_ARGS__); if (logFile) fprintf(logFile, __VA_ARGS__);  } while (0)
#else
	fprintf(stderr, "%s\n", qPrintable(message));
	qDebug("%s", qPrintable(message));
#define PRINT(...) do { fprintf(stderr, __VA_ARGS__); qDebug(__VA_ARGS__); if (logFile) fprintf(logFile, __VA_ARGS__); } while (0)
#endif
	static int count = 0;
	count++;
	FILE* logFile = fopen(qPrintable(temporaryFileNameFormat().arg(count)), "w");
	PRINT("%s\n", qPrintable(message));

	void *trace[48];
	SimulatedCPU copystate = state;
	int size;
#if defined(CPU_IS_MIPS) || defined(CPU_IS_IA64) || defined(CPU_IS_SPARC32) || defined(CPU_IS_S390_31) || defined(CPU_IS_390_64)
	size = backtrace(trace, 48); //always use standard backtrace on exotic architectures
#else
	size = copystate.backtrace(trace, 48);
#endif

#ifdef Q_WS_WIN
	QStringList additionalMessages = backtrace_symbols_win(trace, size);
	char** messages = 0;
#else
	QStringList additionalMessages;
	char** messages = backtrace_symbols(trace, size);
#endif
	for (int i=0; i<size; ++i) {
		const char * message = messages ? messages[i] : "";
		if (i >= additionalMessages.size()) PRINT("[bt] %s\n", message);
		else PRINT("[bt] %p %s %s\n", trace[i], message, qPrintable(additionalMessages[i]));
	}

	if (logFile) fclose(logFile);
}

void print_backtrace(const QString& message){
	SimulatedCPU cpu;
	cpu.set_from_real();
	print_backtrace(cpu, message);
}


//===========================CRASH HANDLER==============================



#ifdef OS_IS_UNIX_LIKE
#include "unistd.h"
#include "sys/wait.h"
#define SAFE_INT volatile sig_atomic_t
#else
#define SAFE_INT int
#endif

SAFE_INT crashHandlerType = 1;
SAFE_INT lastErrorWasAssert = 0;
SAFE_INT lastErrorWasLoop = 0;
volatile void* sigSegvRecoverReturnAddress = 0; //address where it should jump to, if recovering causes another sigsegv

#define CRASH_HANDLER_RECOVER 1
#define CRASH_HANDLER_PRINT_BACKTRACE 2
#define CRASH_HANDLER_LOOP_GUARDIAN_DISABLED 4


//=========================POSIX SIGNAL HANDLER===========================



#ifdef OS_IS_LINUX_LIKE
#include "signal.h"
#include "ucontext.h"
#include "sys/ucontext.h"
#include "pthread.h"

#define USE_SIGNAL_HANDLER
#ifdef CPU_IS_X86_64
#define PC_FROM_UCONTEXT(context) (context)->uc_mcontext.gregs[REG_RIP]
#define STACK_FROM_UCONTEXT(context) (context)->uc_mcontext.gregs[REG_RSP]
#define FRAME_FROM_UCONTEXT(context) (context)->uc_mcontext.gregs[REG_RBP]
#elif defined(CPU_IS_X86_32)
#define PC_FROM_UCONTEXT(context) (context)->uc_mcontext.gregs[REG_EIP]
#define STACK_FROM_UCONTEXT(context) (context)->uc_mcontext.gregs[REG_ESP]
#define FRAME_FROM_UCONTEXT(context) (context)->uc_mcontext.gregs[REG_EBP]
#elif defined(CPU_IS_PPC)
#define PC_FROM_UCONTEXT(context) (context)->uc_mcontext.gp_regs[32]
#define STACK_FROM_UCONTEXT(context) (context)->uc_mcontext.gp_regs[1]
#define FRAME_FROM_UCONTEXT(context) (context)->uc_mcontext.gp_regs[31] //not always used
#define RETURNTO_FROM_UCONTEXT(context) (context)->uc_mcontext.gp_regs[34]
#elif defined(CPU_IS_ARM)
#define PC_FROM_UCONTEXT(context) (context)->uc_mcontext.arm_pc
#define STACK_FROM_UCONTEXT(context) (context)->uc_mcontext.arm_sp
#define FRAME_FROM_UCONTEXT(context) (context)->uc_mcontext.arm_fp
#define RETURNTO_FROM_UCONTEXT(context) (context)->uc_mcontext.arm_lr
#elif defined(CPU_IS_IA64)
#define PC_FROM_UCONTEXT(context) (context)->_u._mc.sc_ip
#define STACK_FROM_UCONTEXT(context) (context)->_u._mc.sc_gr[12] //is that register 12?
#define FRAME_FROM_UCONTEXT(context) (context)->_u._mc.sc_cfm //does not really make sense
#elif defined(CPU_IS_MIPS)
#define PC_FROM_UCONTEXT(context) (context)->uc_mcontext.pc
#define STACK_FROM_UCONTEXT(context) (context)->uc_mcontext.sc_regs[29]
#define FRAME_FROM_UCONTEXT(context) (context)->uc_mcontext.sc_regs[30]
#define RETURNTO_FROM_UCONTEXT(context) (context)->uc_mcontext.sc_regs[31]
#elif defined(CPU_IS_SPARC32)
#define PC_FROM_UCONTEXT(context) (context)->uc_mcontext.gregs[REG_nPC]
#define STACK_FROM_UCONTEXT(context) (context)->uc_mcontext.gregs[REG_O6]
//todo: gwins-> might be 0. (first or last (context)->uc_mcontext.gwins[0].wbcnt-1 window?)
#define FRAME_FROM_UCONTEXT(context) (context)->uc_mcontext.gwins->wbuf[0].rw_in[6]
#define RETURNTO_FROM_UCONTEXT(context) (context)->uc_mcontext.gwins->wbuf[0].rw_in[7]
#elif defined(CPU_IS_S390_31) || defined(CPU_IS_S390_64)
#define PC_FROM_UCONTEXT(context) (context)->uc_mcontext.psw.addr
#define STACK_FROM_UCONTEXT(context) (context)->uc_mcontext.gregs[15]
#define FRAME_FROM_UCONTEXT(context) (context)->uc_mcontext.gregs[11]
//#define RETURNTO_FROM_UCONTEXT(context) (context)->uc_mcontext.gregs[14]
#else
#error Unknown cpu architecture
#endif

#define SIGMYHANG SIGRTMIN + 4             //signal send to the main thread, if the guardian detects an endless loop
#define SIGMYHANG_CONTINUE SIGRTMIN + 5    //signal send to the main thread, if the endless loop should be continued
#endif

#ifdef Q_WS_MACX
#include "signal.h"
//#include "ucontext.h"
#include "sys/signal.h"
#include "sys/ucontext.h"
#define USE_SIGNAL_HANDLER
//names from http://google-glog.googlecode.com/svn-history/r75/trunk/m4/pc_from_ucontext.m4
//for mac <= 10.4/tiger: if __ss.__ doesn't compile, replace it by ss.

#if defined(__DARWIN_UNIX03) && defined(_STRUCT_X86_EXCEPTION_STATE32)
#define MAC_CONTEXT_PREFIXED(x) __##x
#else
#define MAC_CONTEXT_PREFIXED(x) x
#endif

// >= mac 10.5
#ifdef CPU_IS_X86_64
#define PC_FROM_UCONTEXT(context) context->uc_mcontext->MAC_CONTEXT_PREFIXED(ss).MAC_CONTEXT_PREFIXED(rip)
#define STACK_FROM_UCONTEXT(context) context->uc_mcontext->MAC_CONTEXT_PREFIXED(ss).MAC_CONTEXT_PREFIXED(rsp)
#define FRAME_FROM_UCONTEXT(context) context->uc_mcontext->MAC_CONTEXT_PREFIXED(ss).MAC_CONTEXT_PREFIXED(rbp)
#elif defined(CPU_IS_PPC)
#define PC_FROM_UCONTEXT(context) context->uc_mcontext->MAC_CONTEXT_PREFIXED(ss).__srr0
#error need ppc stack register name
#elif defined(CPU_IS_X86_32)
#define PC_FROM_UCONTEXT(context) context->uc_mcontext->MAC_CONTEXT_PREFIXED(ss).MAC_CONTEXT_PREFIXED(eip)
#define STACK_FROM_UCONTEXT(context) context->uc_mcontext->MAC_CONTEXT_PREFIXED(ss).MAC_CONTEXT_PREFIXED(esp)
#define FRAME_FROM_UCONTEXT(context) context->uc_mcontext->MAC_CONTEXT_PREFIXED(ss).MAC_CONTEXT_PREFIXED(ebp)
#else
#error Unsupported processor architecture
#endif
#define SIGMYHANG SIGUSR1             //signal send to the main thread, if the guardian detects an endless loop
#define SIGMYHANG_CONTINUE SIGUSR2    //signal send to the main thread, if the endless loop should be continued
#endif

#ifdef USE_SIGNAL_HANDLER
#define CPU_CONTEXT_TYPE ucontext_t
volatile sig_atomic_t lastCrashSignal = 0;
#define SIGMYSTACKSEGV 123

#define LAST_POSSIBLE_TXS_ADDRESS ( ( (char*)&isAddressInTeXstudio) + 0x900000 )
//do not use etext, since it behaves funny (e.g. becomes 0 when including sys/ptrace)
//#define LAST_POSSIBLE_TXS_ADDRESS (&_etext)

CPU_CONTEXT_TYPE lastLoopContext;

bool isAddressInTeXstudio(void * address){
	return address < LAST_POSSIBLE_TXS_ADDRESS;
}


inline quintptr ptrdistance(void* a, void* b){
	if (a < b) return (quintptr)(b) - (quintptr)(a);
	else return (quintptr)(a) - (quintptr)(b);
}

const char * signalIdToName(int id){
	switch (id){
	case SIGSEGV: return ("SIGSEGV"); 
	case SIGFPE: return ("SIGFPE"); 
	case SIGMYSTACKSEGV: return ("SIGSEGV on stack"); 
	//case SIGMYHANG: return "Endless loop";
	default: 
		if (id == SIGMYHANG) return "Endless loop";
		else return ("SIG???"); 
	}
}

void signalHandler(int type, siginfo_t * si, void* ccontext){
	lastErrorWasAssert = 0;
	lastErrorWasLoop = 0;
	SimulatedCPU cpu;
	if (ccontext) {
		cpu.set_all(ccontext);
		if (cpu.frame == 0) cpu.frame = cpu.stack;

		if (type == SIGSEGV && sigSegvRecoverReturnAddress) {
			cpu.jmp((char*)sigSegvRecoverReturnAddress);
			sigSegvRecoverReturnAddress = 0;
			cpu.get_all(ccontext);
			return;
		}

		char *addr = (char*)(si->si_addr);
		char * minstack = cpu.stack < cpu.frame ? cpu.stack : cpu.frame;
		if (type == SIGSEGV && ptrdistance(addr, minstack) < 1024) type = SIGMYSTACKSEGV;
	}
	if (crashHandlerType & CRASH_HANDLER_PRINT_BACKTRACE || !ccontext) {
		print_backtrace(signalIdToName(type));
		if (!ccontext) return;
	}
	if (crashHandlerType & CRASH_HANDLER_RECOVER) {
		if (type == SIGMYHANG) {
			if (!isAddressInTeXstudio(cpu.pc)) return; //don't mess with library functions
			lastLoopContext = *(static_cast<CPU_CONTEXT_TYPE*>(ccontext));
			lastErrorWasLoop = 1;
		} else if (type == SIGMYSTACKSEGV) cpu.unwindStack();	
		
		lastCrashSignal = type;

		cpu.call((char*)(&recover));
		
		cpu.get_all(ccontext);
	}
}

void signalHandlerContinueHanging(int, siginfo_t *, void* ccontext){
	*(static_cast<CPU_CONTEXT_TYPE*>(ccontext)) = lastLoopContext; 
}

const int SIGNAL_STACK_SIZE = 256*1024;
char staticSignalStack[SIGNAL_STACK_SIZE];
pthread_t mainThreadID;

void registerCrashHandler(int mode){
	crashHandlerType = mode;
	if (mode >= 0) {
		stack_t ss;
		ss.ss_sp = staticSignalStack;
		ss.ss_size = SIGNAL_STACK_SIZE;
		ss.ss_flags = 0;
		sigaltstack(&ss, 0);
		
		struct sigaction sa;
		memset(&sa, 0, sizeof(sa)); sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
		sa.sa_sigaction = &signalHandler; sigaction(SIGSEGV, &sa, 0);
		sa.sa_sigaction = &signalHandler; sigaction(SIGFPE, &sa, 0);
		
		if (!(mode & CRASH_HANDLER_LOOP_GUARDIAN_DISABLED)) {
			sa.sa_sigaction = &signalHandler; sigaction(SIGMYHANG, &sa, 0);
			sa.sa_sigaction = &signalHandlerContinueHanging; sigaction(SIGMYHANG_CONTINUE, &sa, 0);
			mainThreadID = pthread_self();
		}		
	}
}

QString getLastCrashInformationInternal(){
	return signalIdToName(lastCrashSignal);
}


bool recoverMainThreadFromOutside(){
	//fprintf(stderr, "%i -> %lx",SIGMYHANG, mainThreadID);
	lastErrorWasLoop = 0;
	lastCrashSignal = 0;
	if (pthread_kill(mainThreadID, SIGMYHANG) != 0) return false;
	
	int loopend = 1000000;
	while ( !lastCrashSignal && (--loopend >= 0) ) ;
	__sync_synchronize(); //memory barrier (does it work?)  (better have a barrier here, than a lock in the signal handler)
	return lastErrorWasLoop;
}

void undoMainThreadRecoveringFromOutside(){
	pthread_kill(mainThreadID, SIGMYHANG_CONTINUE);
}

#endif







//=========================WINDOWS EXCEPTION HANDLER===========================
#ifdef Q_WS_WIN


void * maxStack = 0;

#if 0
void printStackInfo(){
	SYSTEM_INFO  si;
	MEMORY_BASIC_INFORMATION mi, info;
	GetSystemInfo(&si);
	for (int i=-2; i<=32; i++) {
	bool allocated = VirtualQuery((char*)maxStack + i*si.dwPageSize, &info, sizeof(info));
	fprintf(stderr, "> %i: base: %p, allocbase: %p, size: %x, allocprotect: %x, protect: %x, state: %x\n",
									 allocated, info.BaseAddress, info.AllocationBase, info.RegionSize, info.AllocationProtect,  info.Protect, info.State);
	}
}
#endif

void myresetstkoflw(){
	if (!maxStack) return;
	SYSTEM_INFO  si;
	GetSystemInfo(&si);


  MEMORY_BASIC_INFORMATION info;
  if (VirtualQuery(maxStack, &info, sizeof(info)) != sizeof(info)) return;

  //int pagesToFree = 16;
 // allocated = VirtualFree(info.AllocationBase, pagesToFree * si.dwPageSize, MEM_DECOMMIT);
  //VirtualProtect((char*)info.AllocationBase + si.dwPageSize, si.dwPageSize, PAGE_NOACCESS, &tempi);
  //VirtualFree((char*)info.AllocationBase + si.dwPageSize, si.dwPageSize, MEM_DECOMMIT);
  //VirtualProtect((char*)info.AllocationBase + 2*si.dwPageSize, si.dwPageSize, PAGE_GUARD | PAGE_READWRITE, &tempi);
  DWORD tempi;
  //Just put that guard page back, where it was.
  VirtualProtect((char*)info.BaseAddress, si.dwPageSize, PAGE_GUARD | PAGE_READWRITE, &tempi);

  //printStackInfo();
}

void recoverWithStackGuardianPage(){
	myresetstkoflw();
	//typedef int (*ResetstkoflwFunc) ();
	//ResetstkoflwFunc resetstkoflw = (ResetstkoflwFunc)(GetProcAddress(LoadLibraryA("msvcr70.dll"), "_resetstkoflw"));
	//if (resetstkoflw) (*resetstkoflw)();
	recover();
}

#define CATCHED_EXCEPTIONS(X)  \
	X(EXCEPTION_ACCESS_VIOLATION) 	X(EXCEPTION_ARRAY_BOUNDS_EXCEEDED) X(EXCEPTION_DATATYPE_MISALIGNMENT) \
	X(EXCEPTION_FLT_DENORMAL_OPERAND) 	X(EXCEPTION_FLT_DIVIDE_BY_ZERO) X(EXCEPTION_FLT_INEXACT_RESULT) \
	X(EXCEPTION_FLT_INVALID_OPERATION) X(EXCEPTION_FLT_OVERFLOW) X(EXCEPTION_FLT_UNDERFLOW) \
	X(EXCEPTION_IN_PAGE_ERROR) \
	X(EXCEPTION_INT_DIVIDE_BY_ZERO) X(EXCEPTION_INT_OVERFLOW) \
	X(EXCEPTION_INVALID_DISPOSITION) \
	X(EXCEPTION_FLT_STACK_CHECK)  X(EXCEPTION_STACK_OVERFLOW)
//EXCEPTION_ILLEGAL_INSTRUCTION
//EXCEPTION_NONCONTINUABLE_EXCEPTION
//EXCEPTION_PRIV_INSTRUCTION
#ifdef CPU_IS_X86_64
#define PC_FROM_UCONTEXT(context) (context)->Rip
#define FRAME_FROM_UCONTEXT(context) (context)->Rbp
#define STACK_FROM_UCONTEXT(context) (context)->Rsp
#elif defined(CPU_IS_X86_32)
#define PC_FROM_UCONTEXT(context) (context)->Eip
#define FRAME_FROM_UCONTEXT(context) (context)->Ebp
#define STACK_FROM_UCONTEXT(context) (context)->Esp
#else
#error Unsupported processor architecture
#endif


const char* exceptionCodeToName(int code){
	switch (code){
#define X(t) case t: return #t;
	CATCHED_EXCEPTIONS(X)
#undef X
	}
	return "unknown";
}


int lastExceptionCode = 0;
quintptr lastExceptionAddress = 0;

LONG WINAPI crashHandler(_EXCEPTION_POINTERS *ExceptionInfo) {
	if (!ExceptionInfo) return EXCEPTION_CONTINUE_SEARCH;
	bool isCatched = false;
#define X(t) if (ExceptionInfo->ExceptionRecord->ExceptionCode == t) isCatched = true;
	CATCHED_EXCEPTIONS(X)
              #undef X

	if (!isCatched) return EXCEPTION_CONTINUE_SEARCH;
	
	if ((ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION || ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW)
	    && sigSegvRecoverReturnAddress) {
		SimulatedCPU cpu;
		cpu.set_all(ExceptionInfo->ContextRecord);
		cpu.jmp((char*)sigSegvRecoverReturnAddress);
		sigSegvRecoverReturnAddress = 0;
		cpu.get_all(ExceptionInfo->ContextRecord);
		return EXCEPTION_CONTINUE_EXECUTION;
	}

	//if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION) print_backtrace("");

	lastErrorWasAssert = 0;
	lastErrorWasLoop = 0;

	if (crashHandlerType & CRASH_HANDLER_PRINT_BACKTRACE){
		print_backtrace(exceptionCodeToName(ExceptionInfo->ExceptionRecord->ExceptionCode));
	}


	if (crashHandlerType & CRASH_HANDLER_RECOVER) {
		lastExceptionCode = ExceptionInfo->ExceptionRecord->ExceptionCode;
		
		SimulatedCPU cpu;
		cpu.set_all(ExceptionInfo->ContextRecord);

		lastExceptionAddress = (quintptr)(cpu.pc);

		if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW || ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_FLT_STACK_CHECK) {
			maxStack = cpu.stack;
			cpu.unwindStack();
			cpu.call((char*)&recoverWithStackGuardianPage);
		} else {
			cpu.call((char*)&recover);
		}

		cpu.get_all(ExceptionInfo->ContextRecord);

		return EXCEPTION_CONTINUE_EXECUTION;
	}

	return EXCEPTION_CONTINUE_SEARCH;
}

#include "psapi.h"
typedef BOOL WINAPI (*GetModuleInformationFunc)(HANDLE hProcess, HMODULE hModule, LPMODULEINFO lpmodinfo, DWORD cb );
typedef WINBASEAPI HANDLE WINAPI (*OpenThreadFunc)(DWORD,BOOL,DWORD);


void * ownBaseAddress = 0;
unsigned int ownSize = 0x01000000;
DWORD mainThreadID = 0;
OpenThreadFunc OpenThreadDyn;

void registerCrashHandler(int mode){
	crashHandlerType = mode;
	if (mode >= 0) {
		SetUnhandledExceptionFilter(&crashHandler);

		if (!(mode & CRASH_HANDLER_LOOP_GUARDIAN_DISABLED)) {
			OpenThreadDyn = (OpenThreadFunc)(GetProcAddress(GetModuleHandleA("kernel32.dll"), "OpenThread"));

			if (OpenThreadDyn) {
				mainThreadID = GetCurrentThreadId();
				MODULEINFO moduleInfo;
				HMODULE psapi = LoadLibraryA("psapi.dll");
				GetModuleInformationFunc GetModuleInformation = (GetModuleInformationFunc)(GetProcAddress(psapi, "K32GetModuleInformation"));
				if (!GetModuleInformation) GetModuleInformation = (GetModuleInformationFunc)(GetProcAddress(psapi, "GetModuleInformation"));
				if ((*GetModuleInformation)(GetCurrentProcess(), GetModuleHandle(0), &moduleInfo, sizeof(moduleInfo))) {
					ownBaseAddress = moduleInfo.lpBaseOfDll;
					ownSize = moduleInfo.SizeOfImage;
				}
			}
		}
	}
}

QString getLastCrashInformationInternal(){
	return QString::fromLocal8Bit(exceptionCodeToName(lastExceptionCode)) + " at " + QString::number(lastExceptionAddress,16);
}


bool isAddressInTeXstudio(char * address){
	return address >= ownBaseAddress && address <= ((char*)ownBaseAddress) + ownSize;
}


typedef bool (*ChangeThreadContextFunc)(HANDLE thread, CONTEXT* c);


bool doSomethingWithMainThreadContext(ChangeThreadContextFunc something){
	if (!mainThreadID || !OpenThreadDyn) return false;
	HANDLE mainThread = (*OpenThreadDyn)(THREAD_GET_CONTEXT | THREAD_QUERY_INFORMATION | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME, false, mainThreadID);
	if (!mainThread) return false;
	bool result = false;
	SuspendThread(mainThread);
	CONTEXT c;
	c.ContextFlags = (CONTEXT_FULL);
	if (GetThreadContext(mainThread, &c)) 
		result = (*something)(mainThread, &c);
	ResumeThread(mainThread);
	CloseHandle(mainThread);
	return result;
}

CONTEXT lastRecoveredContext;
bool changeContextToRecover(HANDLE thread, CONTEXT* c){
	bool result = false;
	if (isAddressInTeXstudio((char*)(PC_FROM_UCONTEXT(c)))) {
		lastRecoveredContext = *c;
		SimulatedCPU cpu;
		cpu.set_all(c);
		cpu.call((char*)&recover);
		cpu.get_all(c);
		result = SetThreadContext(thread, c);
		if (result) lastErrorWasLoop = true;
	}
	return result;
}
bool recoverMainThreadFromOutside(){
	return doSomethingWithMainThreadContext(changeContextToRecover);
}

bool changeContextToUndoRecoving(HANDLE thread, CONTEXT* c){
	Q_UNUSED(c);
	return SetThreadContext(thread, &lastRecoveredContext);
}
void undoMainThreadRecoveringFromOutside(){
	doSomethingWithMainThreadContext(changeContextToUndoRecoving);
}
#endif


#if !defined(USE_SIGNAL_HANDLER) && !defined(Q_WS_WIN)
#warning Unrecognized OS. Crash handler will be disabled.

bool recoverMainThreadFromOutside(){
	fprintf(stderr, "Main thread locks frozen\n");
	return true;
}

void undoMainThreadRecoveringFromOutside(){}
QString getLastCrashInformationInternal(){return "unknown (os unsupported by crash handler)";}
void registerCrashHandler(int mode){}
#endif




//========================NEW ASSERT==============================


#undef qt_assert
Q_CORE_EXPORT void qt_assert(const char *assertion, const char *file, int line);
Q_CORE_EXPORT void qt_assert_x(const char *where, const char *what, const char *file, int line);

QString lastAssert;

void txs_assert(const char *assertion, const char *file, int line){
	txs_assert_x("something",assertion,file,line);
}

void txs_assert_x(const char *where, const char *assertion, const char *file, int line){
	lastAssert = QString("Assert failure: %1 at %2 in %3:%4").arg(assertion).arg(where).arg(file).arg(line);
	print_backtrace(lastAssert);

	lastErrorWasAssert = 1;
	recover();

	//won't be called:
	qt_assert(assertion, file, line);
	exit(1);
}

QString getLastCrashInformation(bool& wasLoop){
	wasLoop = lastErrorWasLoop;
	if (lastErrorWasAssert) return lastAssert;
	else return getLastCrashInformationInternal();
}
















///CPU Information


#ifdef CPU_CONTEXT_TYPE

void SimulatedCPU::set_all(void *ccontext) {
	CPU_CONTEXT_TYPE* context = static_cast<CPU_CONTEXT_TYPE*>(ccontext);
	this->pc = (char*)PC_FROM_UCONTEXT(context);
	this->frame = (char*)FRAME_FROM_UCONTEXT(context);
	this->stack = (char*)STACK_FROM_UCONTEXT(context);
#ifdef RETURNTO_FROM_UCONTEXT
	this->returnTo = (char*)RETURNTO_FROM_UCONTEXT(context);
#endif
//	for (int i=0;i<sizeof(context->uc_mcontext.gregs) / sizeof(context->uc_mcontext.gregs[0]);i++)
//		fprintf(stderr, "Regs: %i: %p\n", i, context->uc_mcontext.gregs[i]);
}
void SimulatedCPU::get_all(void *ccontext) {
	CPU_CONTEXT_TYPE* context = static_cast<CPU_CONTEXT_TYPE*>(ccontext);
	*(char**)(&PC_FROM_UCONTEXT(context)) = this->pc;
	*(char**)(&FRAME_FROM_UCONTEXT(context)) = this->frame;
	*(char**)(&STACK_FROM_UCONTEXT(context)) = this->stack;
#ifdef RETURNTO_FROM_UCONTEXT
	*(char**)(&RETURNTO_FROM_UCONTEXT(context)) = this->returnTo;
#endif
}
void SimulatedCPU::set_from_real(){
	this->pc = 0;
	this->frame = 0;
	this->stack = 0;
#ifdef CPU_IS_X86_32
	__asm__(
	"mov %%ebp, %0\n"
	"mov %%esp, %1"
	: "=r"(frame), "=r"(stack));
#elif defined(CPU_IS_X86_64)
	__asm__(
	"mov %%rbp, %0\n"
	"mov %%rsp, %1"
	: "=r"(frame), "=r"(stack));
#elif defined(CPU_IS_ARM)
	__asm__( //otherway around in the mov than x86?
	"mov %[fp], fp\n"
	"mov %[sp], sp\n"
	"mov %[lr], lr\n"
	: [fp] "=r"(frame), [sp] "=r"(stack), [lr] "=r" (returnTo));
#elif defined(CPU_IS_IA64)
	__asm__(
	//"mov %0 = cfm\n"
	"mov %0 = r12"
	: /*"=r"(frame),*/ "=r"(stack));
#elif defined(CPU_IS_MIPS)
	__asm__( //otherway around in the mov than x86?
	"move %0, $30\n"
	"move %1, $sp\n"
	"move %2, $ra\n"
	: "=r"(frame), "=r"(stack), "=r" (returnTo));
#elif defined(CPU_IS_PPC)
	__asm__( //otherway around in the mov than x86?
	"mr %0, 31\n"
	"mr %1, 1\n"
	"mflr %2\n"
	: "=r"(frame), "=r"(stack), "=r" (returnTo));
#elif defined(CPU_IS_SPARC32)
	__asm__(
	"mov %i6, %0\n"
	"mov %o6, %1\n"
	"mov %i7, %2\n"
	: "=r"(frame), "=r"(stack), "=r" (returnTo));
#elif defined(CPU_IS_S390_31)
	__asm__(
	"LR %0, %r11\n"
	"LR %1, %r15\n"
	: "=r"(frame), "=r"(stack));
#elif defined(CPU_IS_S390_64)
	__asm__(
	"LGR %0, %r11\n"
	"LGR %1, %r15\n"
	: "=r"(frame), "=r"(stack));
#else
#error Unknown processor architecture
#endif
	geteip:
	this->pc = (char*)&&geteip;
}

#endif


//todo: fix CALL_INSTRUCTION_SIZE 
//(should be the size of the call instruction. 
//however, since the call instruction is in the signal handler and not actually part of the program, 0 might be the more correct value)
#define CALL_INSTRUCTION_SIZE 0
#if defined(CPU_IS_X86_64) || defined (CPU_IS_X86_32)
//TODO: check ppc
void SimulatedCPU::call(char * value){
	push(pc + CALL_INSTRUCTION_SIZE);
	jmp(value);
}
void SimulatedCPU::ret(){
	pc = pop();
}
void SimulatedCPU::enter(int size){
	push(frame);
	frame = stack;
	stack -= size;
}
void SimulatedCPU::leave(){
	sigSegvRecoverReturnAddress = &&recover;
	stack = frame;
	frame = pop();
	ret();
recover:
	if (sigSegvRecoverReturnAddress == 0) {
		frame = 0;
		stack = 0;
		pc = 0;
	}
	sigSegvRecoverReturnAddress = 0;
}
#elif defined(CPU_IS_ARM) || defined(CPU_IS_MIPS)
//todo: does this work on mips?
void SimulatedCPU::call(char * value){   //bl
	returnTo = pc + CALL_INSTRUCTION_SIZE;
	jmp(value);
}
void SimulatedCPU::ret(){
	pc = returnTo;
}
void SimulatedCPU::enter(int size){
	push(returnTo);
	push(frame);
	frame = stack + 4;
	stack -= size;
}
void SimulatedCPU::leave(){
	stack = frame - 4;
	frame = pop();
	returnTo = pop();
	ret();
}
#elif defined(CPU_IS_PPC)
//see https://developer.apple.com/library/mac/#documentation/DeveloperTools/Conceptual/LowLevelABI/110-64-bit_PowerPC_Function_Calling_Conventions/64bitPowerPC.html#//apple_ref/doc/uid/TP40002471-SW14
void SimulatedCPU::call(char * value){   //bl
	returnTo = pc + CALL_INSTRUCTION_SIZE;
	jmp(value);
}
void SimulatedCPU::ret(){
	pc = returnTo;
}
void SimulatedCPU::enter(int size){
	//todo
}
void SimulatedCPU::leave(){
	returnTo = *(char**)(stack+2*8);
	stack = pop();
	frame = stack; //??
	ret();
}
#elif defined(CPU_IS_IA64) || defined(CPU_IS_SPARC32) || defined(CPU_IS_S390_31) || defined(CPU_IS_390_64)
//not really implemented
//not possible on SPARC? (as register windows are protected)
void SimulatedCPU::call(char * value){   //bl
	jmp(value);
	//todo this should do an awful lot of register swapping/saving for IA64
}
void SimulatedCPU::ret(){
	//pc = br0;
	pc = 0;
}
void SimulatedCPU::enter(int size){

}
void SimulatedCPU::leave(){
	ret();
}
#else
#error Unknown cpu architecture
#endif	


bool SimulatedCPU::stackWalk(){
	leave();
	pc-=CALL_INSTRUCTION_SIZE;
//	fprintf(stderr, "%p (at %p), %p (at %p), %p\n", *(char**)(frame),frame, *(char**)(stack), stack, pc);
	return frame >= stack && frame && stack;
}



#else
 // defined NO_CRASH_HANDLER
 

void print_backtrace(const QString& message){}
void registerCrashHandler(int mode){}
QString getLastCrashInformation(bool & wasLoop){return "";}



#endif


#ifdef HAS_DEBUGGER_PRESENT
#undef HAS_DEBUGGER_PRESENT
#endif


#ifdef Q_WS_WIN
#define HAS_DEBUGGER_PRESENT
#else
#if (!defined(QT_NO_DEBUG) && defined(Q_OS_LINUX))
#define HAS_DEBUGGER_PRESENT
#include <sys/ptrace.h>
//from http://stackoverflow.com/questions/3596781/detect-if-gdb-is-running

#ifndef NO_CRASH_HANDLER
int gdb_check()
{
  int pid = fork();
  int status;
  int res;

  if (pid == -1)
    {
      perror("fork");
      return -1;
    }

  if (pid == 0)
    {
      int ppid = getppid();
      /* Child */
      if (ptrace(PTRACE_ATTACH, ppid, NULL, NULL) == 0)
        {
          /* Wait for the parent to stop and continue it */
          waitpid(ppid, NULL, 0);
          ptrace(PTRACE_CONT, ppid, NULL, NULL);

          /* Detach */
          ptrace(PTRACE_DETACH, ppid, NULL, NULL);

          /* We were the tracers, so gdb is not present */
          res = 0;
        }
      else
        {
          /* Trace failed so gdb is present */
          res = 1;
        }
      _Exit(res);
    }
  else
    {
      waitpid(pid, &status, 0);
      res = WEXITSTATUS(status);
    }
  return res;
}

int _debugger_present = -1;
bool IsDebuggerPresent()
{
  if (-1 == _debugger_present)
    _debugger_present = gdb_check();
  if (_debugger_present == 1)  {
    fprintf(stderr, "debugger detected: no recovering\n\n");
    fflush(stderr);
  }
  return _debugger_present == 1;
}
#endif
#endif
#endif





//==================GUARDIAN==================

Guardian * guardian = 0;
bool running = true;
volatile int mainEventLoopTicks = 0;
volatile bool undoRecovering = false;
void Guardian::run(){
#ifndef NO_CRASH_HANDLER
	int lastTick = mainEventLoopTicks;
	int errors = 0;
	while (running) {
		int slowOperationWait = slowOperations * 15;
		do {
			sleep(10);
			slowOperationWait -= 1;
		} while (slowOperationWait >= 0);
		
		if (undoRecovering) {
			undoRecovering = false;
			errors = 1;
			undoMainThreadRecoveringFromOutside();
			continue;
		}
		if (crashHandlerType & CRASH_HANDLER_LOOP_GUARDIAN_DISABLED) continue;
		if (lastTick == mainEventLoopTicks) errors++;
		else errors = 0;
		lastTick = mainEventLoopTicks;
		if (errors >= 60) {
			fprintf(stderr, "Main thread in trouble\n");
#ifdef HAS_DEBUGGER_PRESENT
			if (IsDebuggerPresent()) return;
#endif
			int repetitions = 0;
			while (lastTick == mainEventLoopTicks && !recoverMainThreadFromOutside()) {
				msleep(50);
				repetitions ++;
				if (repetitions > 50) break;  //give up for now
			}
			if (repetitions < 50) //recovered
				errors -= 6 ; //wait 1 min now
			//if (repetitions < 50) return; the crash handler can't be debugged, if this thread continues calling it
		}
	}
	guardian = 0;
#endif
}

void Guardian::summon(){
#ifndef NO_CRASH_HANDLER
	if (guardian) return;
	if (crashHandlerType & CRASH_HANDLER_LOOP_GUARDIAN_DISABLED) return;
	guardian = new Guardian();
	guardian->start();
#endif
}

void Guardian::calm(){
	mainEventLoopTicks++;
}

void Guardian::shutdown(){
	running = false;
}

void Guardian::continueEndlessLoop(){
	undoRecovering = true;
}


Guardian* Guardian::instance(){
	return guardian;
}

void Guardian::slowOperationStarted(){
	slowOperations++;
}

void Guardian::slowOperationEnded(){
	slowOperations--;
	if (slowOperations < 0) slowOperations = 0;
}


