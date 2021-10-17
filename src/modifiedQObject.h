#ifndef Header_Modified_QObject
#define Header_Modified_QObject


#include <qglobal.h>

// Crash handler and its helper functions are available only when using GNU libc
#if !defined(NO_CRASH_HANDLER) && (defined(__GLIBC__) || defined(Q_OS_WIN32))

#define ASSERT_THROW Q_DECL_NOTHROW


#ifndef QT_NO_DEBUG

#undef Q_ASSERT
#undef Q_ASSERT_X

#define Q_ASSERT(cond) ((!(cond)) ? txs_assert(#cond,__FILE__,__LINE__) : static_cast<void>(0))
#define Q_ASSERT_X(cond, where, what) ((!(cond)) ? txs_assert_x(where, what, __FILE__,__LINE__) : static_cast<void>(0))


#define qt_assert txs_assert
#define qt_assert_x txs_assert_x




void txs_assert(const char *assertion, const char *file, int line) ASSERT_THROW;
void txs_assert_x(const char *where, const char *assertion, const char *file, int line) ASSERT_THROW;


#endif
#endif

#include <QObject>

#endif
