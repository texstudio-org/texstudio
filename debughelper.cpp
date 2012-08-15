#include "debughelper.h"
#include "mostQtHeaders.h"
#include "smallUsefulFunctions.h"
#include "QMutex"

#if (defined(x86_64) || defined(__x86_64__))
#define CPU_IS_64
#elif (defined(ppc) || defined(__ppc__))
#define CPU_IS_PPC
#else
#define CPU_IS_32
#endif

//===========================Abstract CPU model==========================

//platfom independent implementation of assembler instructions 
//(use case: before changing eip, the old eip must be pushed in the correct way on the stack, otherwise the 
//           backtrace doesn't show the function that actually crashed)
#define CALL_INSTRUCTION_SIZE 0
struct SimulatedCPU {
	char * pc; //e.g. eip
	char * frame; //e.g. ebp
	char * stack; //e.g. esp
	
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
	inline void call(char * value){
		push(pc + CALL_INSTRUCTION_SIZE);
		jmp(value);
	}
	inline void ret(){
		pc = pop();
	}
	inline void enter(int size){
		push(frame);
		frame = stack;
		stack -= size;
	}
	inline void leave(){
		stack = frame;
		frame = pop();
		ret();
	}
	
	void set_all(void* context);
	void get_all(void* context);

	bool stackWalk(){
		leave();
		pc-=CALL_INSTRUCTION_SIZE;
	//	fprintf(stderr, "%p (at %p), %p (at %p), %p\n", *(char**)(frame),frame, *(char**)(stack), stack, pc);
		return frame >= stack && frame && stack;
	}
	void unwindStack(){
		SimulatedCPU temp = *this;
		int frames = 0; 
		while (temp.stackWalk()) frames++;
		if (frames == 0) return;
		if (frames < 100) frames = frames - 10;
		else frames = frames - 100;
		while (frames > 0) { this->leave(); frames--; }
	}	
};
#ifdef CPU_CONTEXT_TYPE
#undef CPU_CONTEXT_TYPE
#endif

//===========================STACK TRACE PRINTING=========================
void print_message(const char* title, const char *where, const char *assertion, const char *file, int line, const char* end){
#ifdef Q_WS_WIN
	qDebug("%s %s at %s in %s: %i\r\n%s", title, assertion, where, file, line, end);
#else
	fprintf(stderr, "%s %s at %s in %s: %i\r\n%s", title, assertion, where, file, line, end);
	qDebug("%s %s at  %s in %s: %i\r\n%s", title, assertion, where, file, line, end);
#endif
}

#if defined(unix) || defined(Q_WS_MACX)
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "execinfo.h"
/*
void print_backtrace_with_gdb(){ //from http://stackoverflow.com/questions/3151779/how-its-better-to-invoke-gdb-from-program-to-print-its-stacktrace
	//carefully, might crash the X server
	char pid_buf[30];
	sprintf(pid_buf, "%d", getpid());
	char name_buf[512];
	name_buf[readlink("/proc/self/exe", name_buf, 511)]=0;
	int child_pid = fork();
	if (!child_pid) {
		dup2(2,1); // redirect output to stderr
		fprintf(stdout,"stack trace for %s pid=%s\n",name_buf,pid_buf);
		execlp("gdb", "gdb", "--batch", "-n", "-ex", "thread", "-ex", "bt", name_buf, pid_buf, NULL);
		abort(); // If gdb failed to start 
	} else {
		waitpid(child_pid,NULL,0);
	}
}*/


void print_backtrace(const char* title, const char *where, const char * assertion, const char * file, int line){ //http://stackoverflow.com/questions/3151779/how-its-better-to-invoke-gdb-from-program-to-print-its-stacktrace/4611112#4611112
	print_message(title, where, assertion, file, line,"");

	void *trace[48];
	int trace_size = backtrace(trace, 48);
	char** messages = backtrace_symbols(trace, trace_size);
	for (int i=1; i<trace_size; ++i)
		printf("[bt] %s\n", messages[i]);
	
	
	char filename[] = "/tmp/texstudioXXXX_backtrace.txt";
	static int count = 1;
	snprintf(filename, sizeof(filename), "/tmp/texstudio_backtrace%i.txt", count);
	
	FILE* f = fopen(filename, "w");
	if (!f) return;
	fprintf(f, "%s %s at %s in %s: %i\r\n", title, assertion, where, file, line);
	for (int i=1; i<trace_size; ++i)
		fprintf(f,"[bt] %s\n", messages[i]);
	fclose(f);
}


#elif defined(Q_WS_WIN)
#include <QSysInfo>
#include "windows.h"

//from wine
//dbghelp.h
typedef BOOL WINAPI (*SymInitializeFunc)(HANDLE, PCSTR, BOOL);
typedef PVOID WINAPI (*SymFunctionTableAccess64Func)(HANDLE, DWORD64);
typedef DWORD64 WINAPI (*SymGetModuleBase64Func)(HANDLE, DWORD64);
typedef enum
{
	AddrMode1616,
	AddrMode1632,
	AddrModeReal,
	AddrModeFlat
} ADDRESS_MODE;
//
// New KDHELP structure for 64 bit system support.
// This structure is preferred in new code.
//
typedef struct _KDHELP64 {
	
	//
	// address of kernel thread object, as provided in the
	// WAIT_STATE_CHANGE packet.
	//
	DWORD64   Thread;
	
	//
	// offset in thread object to pointer to the current callback frame
	// in kernel stack.
	//
	DWORD   ThCallbackStack;
	
	//
	// offset in thread object to pointer to the current callback backing
	// store frame in kernel stack.
	//
	DWORD   ThCallbackBStore;
	
	//
	// offsets to values in frame:
	//
	// address of next callback frame
	DWORD   NextCallback;
	
	// address of saved frame pointer (if applicable)
	DWORD   FramePointer;
	
	
	//
	// Address of the kernel function that calls out to user mode
	//
	DWORD64   KiCallUserMode;
	
	//
	// Address of the user mode dispatcher function
	//
	DWORD64   KeUserCallbackDispatcher;
	
	//
	// Lowest kernel mode address
	//
	DWORD64   SystemRangeStart;
	
	DWORD64  Reserved[8];
	
} KDHELP64, *PKDHELP64;

typedef struct _tagADDRESS64 {
	DWORD64       Offset;
	WORD          Segment;
	ADDRESS_MODE  Mode;
} ADDRESS64, *LPADDRESS64;

typedef struct _STACKFRAME64
{
	ADDRESS64   AddrPC;
	ADDRESS64   AddrReturn;
	ADDRESS64   AddrFrame;
	ADDRESS64   AddrStack;
	ADDRESS64   AddrBStore;
	PVOID       FuncTableEntry;
	DWORD64     Params[4];
	BOOL        Far;
	BOOL        Virtual;
	DWORD64     Reserved[3];
	KDHELP64    KdHelp;
} STACKFRAME64, *LPSTACKFRAME64;

typedef BOOL (CALLBACK *PREAD_PROCESS_MEMORY_ROUTINE64)(HANDLE, DWORD64, PVOID, DWORD, PDWORD);
typedef PVOID (CALLBACK *PFUNCTION_TABLE_ACCESS_ROUTINE64)(HANDLE, DWORD64);
typedef DWORD64 (CALLBACK *PGET_MODULE_BASE_ROUTINE64)(HANDLE, DWORD64);
typedef DWORD64 (CALLBACK *PTRANSLATE_ADDRESS_ROUTINE64)(HANDLE, HANDLE, LPADDRESS64);
typedef BOOL WINAPI (*StackWalk64Func)(DWORD, HANDLE, HANDLE, LPSTACKFRAME64, PVOID,
                                       PREAD_PROCESS_MEMORY_ROUTINE64,
                                       PFUNCTION_TABLE_ACCESS_ROUTINE64,
                                       PGET_MODULE_BASE_ROUTINE64,
                                       PTRANSLATE_ADDRESS_ROUTINE64);

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

QMutex backtraceMutex;


#define CPU_CONTEXT_TYPE CONTEXT
#define LOAD_FUNCTION(name, ansiname) static name##Func name = (name##Func)GetProcAddress(dbghelp, ansiname);
#define LOAD_FUNCTIONREQ(name, ansiname) LOAD_FUNCTION(name,ansiname) if (!name) return "failed to load function: " #name;

QString initDebugHelp(){
	static HMODULE dbghelp = 0;
	if (dbghelp != 0) return ""; //don't call syminitialize twice
	dbghelp = LoadLibraryA("dbghelp.dll");
	if (!dbghelp) return "failed to load dbghelp.dll";

	LOAD_FUNCTIONREQ(SymInitialize, "SymInitialize");

	if (!(*SymInitialize)(((QSysInfo::windowsVersion() & QSysInfo::WV_DOS_based) == 0)?GetCurrentProcess():(HANDLE)GetCurrentProcessId(), 0, true))
		return "Failed to initialize SymInitialize " + QString::number(GetLastError());
	return "";
}

QString lookUpAddresses(const QList<DWORD64>& stackFrames){
	QStringList result(initDebugHelp());

	static HMODULE dbghelp = LoadLibraryA("dbghelp.dll");
	if (!dbghelp) return "failed to load dbghelp.dll";

	LOAD_FUNCTIONREQ(SymGetSymFromAddr64, "SymGetSymFromAddr64");
	LOAD_FUNCTION(SymGetLineFromAddr64, "SymGetLineFromAddr64");

	HANDLE process = GetCurrentProcess();

	_IMAGEHLP_SYMBOL64* symbol = (_IMAGEHLP_SYMBOL64*)malloc(sizeof(_IMAGEHLP_SYMBOL64) + 256);
	for (int i=0;i<stackFrames.size();i++) {
		DWORD64 displacement = 0;
		DWORD displacement32 = 0;
		ZeroMemory(symbol, sizeof(_IMAGEHLP_SYMBOL64));
		symbol->SizeOfStruct = sizeof(_IMAGEHLP_SYMBOL64);
		symbol->MaxNameLength = 256;

		_IMAGEHLP_LINE64 line;

		QString cur = QString::number(stackFrames[i], 16)+": ";

		if ((*SymGetSymFromAddr64)(process, stackFrames[i], &displacement, symbol))
			cur += QString::fromLocal8Bit(symbol->Name)+"+"+QString::number(displacement);
		else
			cur += "??? error: " + QString::number(GetLastError());


		if (SymGetLineFromAddr64) {
			if ((*SymGetLineFromAddr64)(process, stackFrames[i], &displacement32, &line))
				cur += " in " + QString::fromLocal8Bit(line.FileName)+":"+QString::number(line.LineNumber);
		}

		result << cur;
	}
	return result.join("\r\n");
}


//from http://jpassing.com/2008/03/12/walking-the-stack-of-the-current-thread/
//     http://www.codeproject.com/Articles/11132/Walking-the-callstack
//alternative: __builtin_return_address, but it is said to not work so well
QString getBacktrace(){
	if (!backtraceMutex.tryLock()) return "locked";
	
	//init crap
	HANDLE process =  GetCurrentProcess();
	HANDLE thread = GetCurrentThread();
	
	QStringList result(initDebugHelp());

	CONTEXT context;
	ZeroMemory( &context, sizeof( CONTEXT ) );
	STACKFRAME64 stackFrame;
#if (defined(x86_64) || defined(__x86_64__))
	RtlCaptureContext( &context );
#else
	// Those three registers are enough.
geteip:
	context.Eip = (DWORD)&&geteip;
	__asm__(
	"mov %%ebp, %0\n"
	"mov %%esp, %1"
	: "=r"(context.Ebp), "=r"(context.Esp));
#endif
	ZeroMemory( &stackFrame, sizeof( stackFrame ) );
#ifdef CPU_IS_64
	DWORD machineType           = IMAGE_FILE_MACHINE_AMD64;
	stackFrame.AddrPC.Offset    = context.Rip;
	stackFrame.AddrPC.Mode      = AddrModeFlat;
	stackFrame.AddrFrame.Offset = context.Rbp;//changed from rsp. correctly?
	stackFrame.AddrFrame.Mode   = AddrModeFlat;
	stackFrame.AddrStack.Offset = context.Rsp;
	stackFrame.AddrStack.Mode   = AddrModeFlat;
#else
	DWORD machineType           = IMAGE_FILE_MACHINE_I386;
	stackFrame.AddrPC.Offset    = context.Eip;
	stackFrame.AddrPC.Mode      = AddrModeFlat;
	stackFrame.AddrFrame.Offset = context.Ebp;
	stackFrame.AddrFrame.Mode   = AddrModeFlat;
	stackFrame.AddrStack.Offset = context.Esp;
	stackFrame.AddrStack.Mode   = AddrModeFlat;
	/* #elif _M_IA64
    MachineType                 = IMAGE_FILE_MACHINE_IA64;
    StackFrame.AddrPC.Offset    = Context.StIIP;
    StackFrame.AddrPC.Mode      = AddrModeFlat;
    StackFrame.AddrFrame.Offset = Context.IntSp;
    StackFrame.AddrFrame.Mode   = AddrModeFlat;
    StackFrame.AddrBStore.Offset= Context.RsBSP;
    StackFrame.AddrBStore.Mode  = AddrModeFlat;
    StackFrame.AddrStack.Offset = Context.IntSp;
    StackFrame.AddrStack.Mode   = AddrModeFlat;
  #else
    #error "Unsupported platform"*/
#endif
	
	static HMODULE dbghelp = LoadLibraryA("dbghelp.dll");
	if (!dbghelp) return "failed to load dbghelp.dll";

	LOAD_FUNCTIONREQ(StackWalk64, "StackWalk64");
	LOAD_FUNCTIONREQ(SymGetModuleBase64, "SymGetModuleBase64");
	LOAD_FUNCTIONREQ(SymFunctionTableAccess64, "SymFunctionTableAccess64");

	//get stackframes
	QList<DWORD64> stackFrames;
	while ((*StackWalk64)(machineType, process, thread, &stackFrame, &context, 0, SymFunctionTableAccess64, SymGetModuleBase64, 0))
		stackFrames << stackFrame.AddrPC.Offset;
	
	result << lookUpAddresses(stackFrames);

	backtraceMutex.unlock();
	
	return result.join("\r\n");
}

void print_backtrace(const char* title, const char *where, const char *assertion, const char *file, int line){
	print_message(title, where, assertion, file, line,"Prepare to print backtrace:\n");
	QString bt = getBacktrace();
	static int count = 1;
	QFile tf(QDir::tempPath() + QString("/texstudio_backtrace%1.txt").arg(count++));
	if (tf.open(QFile::WriteOnly)){
		tf.write(QString("%1 %2 in %3: %4\r\n").arg(title).arg(assertion).arg(file).arg(line).toLocal8Bit());
		tf.write(bt.toLocal8Bit());
		tf.close();
	};
	qDebug() << bt;
	fprintf(stderr, "%s\r\n", qPrintable(bt));
}



#else //unknown os/mac
void print_backtrace(const char* title, const char *where, const char * assertion, const char * file, int line){
	fprintf(stderr, "Unknown OS");
}
#endif

void print_backtrace(const QString& message){
	print_backtrace(message.toLocal8Bit().data(),"","","",0);
}

void print_backtrace(const char* message){
	print_backtrace(message,"","","",0);
}






//===========================CRASH HANDLER==============================



#ifdef Q_WS_WIN
#define SAFE_INT int
#else
#define SAFE_INT volatile sig_atomic_t
#endif

SAFE_INT crashHandlerType = 1;
SAFE_INT lastErrorWasAssert = 0;
SAFE_INT lastErrorWasLoop = 0;

#define CRASH_HANDLER_RECOVER 1
#define CRASH_HANDLER_PRINT_BACKTRACE 2
#define CRASH_HANDLER_LOOP_GUARDIAN_DISABLED 4


//=========================POSIX SIGNAL HANDLER===========================



#ifdef linux
#include "signal.h"
#include "ucontext.h"
#include "sys/ucontext.h"
#define USE_SIGNAL_HANDLER
#ifdef CPU_IS_64
#define PC_FROM_UCONTEXT(context) (context)->uc_mcontext.gregs[REG_RIP]
#define STACK_FROM_UCONTEXT(context) (context)->uc_mcontext.gregs[REG_RSP]
#define FRAME_FROM_UCONTEXT(context) (context)->uc_mcontext.gregs[REG_RBP]
#else
#define PC_FROM_UCONTEXT(context) (context)->uc_mcontext.gregs[REG_EIP]
#define STACK_FROM_UCONTEXT(context) (context)->uc_mcontext.gregs[REG_ESP]
#define FRAME_FROM_UCONTEXT(context) (context)->uc_mcontext.gregs[REG_EBP]
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
#ifdef CPU_IS_64
#define PC_FROM_UCONTEXT(context) context->uc_mcontext->MAC_CONTEXT_PREFIXED(ss).MAC_CONTEXT_PREFIXED(rip)
#define STACK_FROM_UCONTEXT(context) context->uc_mcontext->MAC_CONTEXT_PREFIXED(ss).MAC_CONTEXT_PREFIXED(rsp)
#define FRAME_FROM_UCONTEXT(context) context->uc_mcontext->MAC_CONTEXT_PREFIXED(ss).MAC_CONTEXT_PREFIXED(rbp)
#elif defined(CPU_IS_PPC)
#define PC_FROM_UCONTEXT(context) context->uc_mcontext->MAC_CONTEXT_PREFIXED(ss).__srr0
#error need ppc stack register name
#else
#define PC_FROM_UCONTEXT(context) context->uc_mcontext->MAC_CONTEXT_PREFIXED(ss).MAC_CONTEXT_PREFIXED(eip)
#define STACK_FROM_UCONTEXT(context) context->uc_mcontext->MAC_CONTEXT_PREFIXED(ss).MAC_CONTEXT_PREFIXED(esp)
#define FRAME_FROM_UCONTEXT(context) context->uc_mcontext->MAC_CONTEXT_PREFIXED(ss).MAC_CONTEXT_PREFIXED(ebp)
#endif
#define SIGMYHANG SIGUSR1             //signal send to the main thread, if the guardian detects an endless loop
#define SIGMYHANG_CONTINUE SIGUSR2    //signal send to the main thread, if the endless loop should be continued
#endif

#ifdef USE_SIGNAL_HANDLER
#define CPU_CONTEXT_TYPE ucontext_t
volatile sig_atomic_t lastCrashSignal = 0;
#define SIGMYSTACKSEGV 123

#ifdef Q_WS_MACX
#define LAST_POSSIBLE_TXS_ADDRESS ( ( (char*)&isAddressInTeXstudio) + 0x800000 )
#else
#define LAST_POSSIBLE_TXS_ADDRESS (&_etext)
extern int LAST_POSSIBLE_TXS_ADDRESS;
//perhaps always use __etext? (did work on linux)
#endif


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

		char *addr = (char*)(si->si_addr);
		char * minstack = cpu.stack < cpu.frame ? cpu.stack : cpu.frame;
		if (ptrdistance(addr, minstack) < 1024) type = SIGMYSTACKSEGV;
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
#ifdef CPU_IS_64
#define PC_FROM_UCONTEXT(context) (context)->Rip
#define FRAME_FROM_UCONTEXT(context) (context)->Rbp
#define STACK_FROM_UCONTEXT(context) (context)->Rsp
#else
#define PC_FROM_UCONTEXT(context) (context)->Eip
#define FRAME_FROM_UCONTEXT(context) (context)->Ebp
#define STACK_FROM_UCONTEXT(context) (context)->Esp
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
bool recoverMainThreadFromOutside(){
	fprintf(stderr, "Main thread locks frozen\n");
	return true;
}

void undoMainThreadRecoveringFromOutside(){}
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
	print_message("Assertion failure: ", where, assertion,  file, line, "Prepare to print backtrace:\r\n");
	print_backtrace("Assertion failure (repeated): ", where, assertion, file, line);

	lastErrorWasAssert = 1;
	lastAssert = QString("Assert failure: %1 at %2 in %3:%4").arg(assertion).arg(where).arg(file).arg(line);
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








//==================GUARDIAN==================

Guardian * guardian = 0;
bool running = true;
volatile int mainEventLoopTicks = 0;
volatile bool undoRecovering = false;
void Guardian::run(){
	int lastTick = mainEventLoopTicks;
	int errors = 0;
	while (running) {
		int slowOperationWait = slowOperations * 15;
		do {
			sleep(4);
			slowOperationWait -= 1;
		} while (slowOperationWait >= 0);
		
		if (undoRecovering) {
			undoRecovering = false;
			errors = 1;
			undoMainThreadRecoveringFromOutside();
			continue;
		}
		if (crashHandlerType & CRASH_HANDLER_LOOP_GUARDIAN_DISABLED) continue;
#ifdef Q_WS_WIN
		if (IsDebuggerPresent()) continue;
#endif
		if (lastTick == mainEventLoopTicks) errors++;
		else errors = 0;
		lastTick = mainEventLoopTicks;
		if (errors >= 10) {
			fprintf(stderr, "Main thread in trouble\n");
			int repetitions = 0;
			while (lastTick == mainEventLoopTicks && !recoverMainThreadFromOutside()) {
				msleep(50);
				repetitions ++;
				if (repetitions > 50) break;  //give up for now
			}
			if (repetitions < 50) //recovered
				errors = 0;
			//if (repetitions < 50) return; the crash handler can't be debugged, if this thread continues calling it
		}
	}
	guardian = 0;
}

void Guardian::summon(){
	if (guardian) return;
	if (crashHandlerType & CRASH_HANDLER_LOOP_GUARDIAN_DISABLED) return;
	guardian = new Guardian();
	guardian->start();
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



#ifdef CPU_CONTEXT_TYPE

void SimulatedCPU::set_all(void *ccontext) {
	CPU_CONTEXT_TYPE* context = static_cast<CPU_CONTEXT_TYPE*>(ccontext);
	this->pc = (char*)PC_FROM_UCONTEXT(context);
	this->frame = (char*)FRAME_FROM_UCONTEXT(context);
	this->stack = (char*)STACK_FROM_UCONTEXT(context);
//	for (int i=0;i<sizeof(context->uc_mcontext.gregs) / sizeof(context->uc_mcontext.gregs[0]);i++)
//		fprintf(stderr, "Regs: %i: %p\n", i, context->uc_mcontext.gregs[i]);
}
void SimulatedCPU::get_all(void *ccontext) {
	CPU_CONTEXT_TYPE* context = static_cast<CPU_CONTEXT_TYPE*>(ccontext);
	*(char**)(&PC_FROM_UCONTEXT(context)) = this->pc;
	*(char**)(&FRAME_FROM_UCONTEXT(context)) = this->frame;
	*(char**)(&STACK_FROM_UCONTEXT(context)) = this->stack;
}

#endif
