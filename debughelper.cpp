#include "debughelper.h"
#include "mostQtHeaders.h"
#include "QMutex"

#if (defined(x86_64) || defined(__x86_64__))
#define CPU_IS_64
#elif (defined(ppc) || defined(__ppc__))
#define CPU_IS_PPC
#else
#define CPU_IS_32
#endif

//===========================STACK TRACE PRINTING=========================

#define print_backtrace qt_noop

#ifndef QT_NO_DEBUG
#ifdef linux
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void print_backtrace(){ //from http://stackoverflow.com/questions/3151779/how-its-better-to-invoke-gdb-from-program-to-print-its-stacktrace
	char pid_buf[30];
	sprintf(pid_buf, "%d", getpid());
	char name_buf[512];
	name_buf[readlink("/proc/self/exe", name_buf, 511)]=0;
	int child_pid = fork();
	if (!child_pid) {
		dup2(2,1); // redirect output to stderr
		fprintf(stdout,"stack trace for %s pid=%s\n",name_buf,pid_buf);
		execlp("gdb", "gdb", "--batch", "-n", "-ex", "thread", "-ex", "bt", name_buf, pid_buf, NULL);
		abort(); /* If gdb failed to start */
	} else {
		waitpid(child_pid,NULL,0);
	}
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

#define LOAD_FUNCTION(name, ansiname) static name##Func name = (name##Func)GetProcAddress(dbghelp, ansiname);
#define LOAD_FUNCTIONREQ(name, ansiname) LOAD_FUNCTION(name,ansiname) if (!name) return "failed to load function: " #name;
//from http://jpassing.com/2008/03/12/walking-the-stack-of-the-current-thread/
//     http://www.codeproject.com/Articles/11132/Walking-the-callstack
//alternative: __builtin_return_address, but it is said to not work so well
QString getBacktrace(){
  if (!backtraceMutex.tryLock()) return "locked";

  //init crap
  QStringList result;
  HANDLE process =  GetCurrentProcess();
  HANDLE thread = GetCurrentThread();

  static HMODULE dbghelp = LoadLibraryA("dbghelp.dll");
  if (!dbghelp) return "failed to load dbghelp.dll";

  LOAD_FUNCTIONREQ(SymInitialize, "SymInitialize");
  LOAD_FUNCTIONREQ(SymGetModuleBase64, "SymGetModuleBase64");
  LOAD_FUNCTIONREQ(SymFunctionTableAccess64, "SymFunctionTableAccess64");
  LOAD_FUNCTIONREQ(StackWalk64, "StackWalk64");
  LOAD_FUNCTIONREQ(SymGetSymFromAddr64, "SymGetSymFromAddr64");
  LOAD_FUNCTION(SymGetLineFromAddr64, "SymGetLineFromAddr64");

  if (!(*SymInitialize)(((QSysInfo::windowsVersion() & QSysInfo::WV_DOS_based) == 0)?process:(HANDLE)GetCurrentProcessId(), 0, true))
    result << "Failed to initialize SymInitialize " << QString::number(GetLastError());

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


  //get stackframes
  QList<DWORD64> stackFrames;
  while ((*StackWalk64)(machineType, process, thread, &stackFrame, &context, 0, SymFunctionTableAccess64, SymGetModuleBase64, 0))
    stackFrames << stackFrame.AddrPC.Offset;


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

  backtraceMutex.unlock();

  return result.join("\r\n");
}

void print_backtrace(const QString& message){
  QString bt = getBacktrace();
  QFile tf(QDir::tempPath() + "\\texstudio_backtrace.txt");
  if (tf.open(QFile::WriteOnly)){
    tf.write(message.toLocal8Bit());
    tf.write(bt.toLocal8Bit());
    tf.close();
  };
  qDebug() << bt;
  fprintf(stderr, "%s\r\n", qPrintable(bt));
}
#else //unknown os/mac
void print_backtrace(const QString&){}
#endif
#else //release
void print_backtrace(const QString&){}
#endif




#undef qt_assert
Q_CORE_EXPORT void qt_assert(const char *assertion, const char *file, int line);




void txs_assert(const char *assertion, const char *file, int line){
	QString message = QString(
		"Assert failure: %s in %s:%i\r\n"
		"Prepare to print backtrace:\r\n"
		).arg(assertion).arg(file).arg(line);
#ifdef linux
	fprintf(stderr,qPrintable(message));
#endif
	qDebug() << message;
	print_backtrace(message);
	qt_assert(assertion, file, line);
}


























//=========================POSIX SIGNAL HANDLER===========================




#ifdef linux
#include "signal.h"
#include "ucontext.h"
#include "sys/ucontext.h"
#define USE_SIGNAL_HANDLER
#if CPU_IS_64
#define PC_FROM_UCONTEXT(context) context->uc_mcontext.gregs[REG_RIP]
#else
#define PC_FROM_UCONTEXT(context) context->uc_mcontext.gregs[REG_EIP]
#endif
#endif

#ifdef Q_WS_MACX
#include "sys/signal.h"
#include "sys/ucontext.h"
#define USE_SIGNAL_HANDLER
//names from http://google-glog.googlecode.com/svn-history/r75/trunk/m4/pc_from_ucontext.m4
//for mac <= 10.4/tiger: if __ss.__ doesn't compile, replace it by ss.
#if CPU_IS_64
#define PC_FROM_UCONTEXT(context) context->__ss.__rip
#elif CPU_IS_PPC
#define PC_FROM_UCONTEXT(context) context->__ss.__srr0
#else
#define PC_FROM_UCONTEXT(context) context->__ss.__eip
#endif
#endif

#ifdef USE_SIGNAL_HANDLER

volatile sig_atomic_t crashHandlerType = 1;
volatile sig_atomic_t lastCrashSignal = 0;

void signalHandler(int type, siginfo_t *, void* ccontext){
	if (crashHandlerType == 1 && ccontext != 0) {
		lastCrashSignal = type;
		ucontext_t* context = static_cast<ucontext_t*>(ccontext);
		// context->uc_mcontext.gregs[REG_RIP]
		*(void**)(&PC_FROM_UCONTEXT(context)) = (void*)(&recover);
	} else {
		switch (type) {
		case SIGSEGV: txs_assert("SIGSEGV","",0); break;
		case SIGFPE: txs_assert("SIGFPE","",0); break;
		default: txs_assert("SIG???","",0); break;
		}
	}
}

void registerCrashHandler(){
	if (crashHandlerType >= 0) {
		struct sigaction sa;
		memset(&sa, 0, sizeof(sa)); sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = &signalHandler;  sigaction(SIGSEGV, &sa, 0);
		sa.sa_sigaction = &signalHandler; sigaction(SIGFPE, &sa, 0);
	}
}

QString getLastSignal(int type = -1){
	if (type < 0) type = lastCrashSignal;
	switch (type) {
	case SIGSEGV: return "SIGSEGV"; break;
	case SIGFPE: return "SIGFPE"; break;
	default: return "SIG???";
	}
}

QString getLastCrashInformation(){
	return getLastSignal();
}

#endif







//=========================WINDOWS EXCEPTION HANDLER===========================
void registerCrashHandler(){}

QString getLastCrashInformation(){return "";}

