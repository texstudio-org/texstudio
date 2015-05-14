#ifndef MODIFIDIEDQOBJECT_H
#define MODIFIDIEDQOBJECT_H


#ifndef NO_CRASH_HANDLER


#ifndef QT_NO_DEBUG

//defines copied and modified from qglobal.h (can't use Q_OS_WIN32 to check for windows without including qglobal.h first, but can't really include qglobal.h, because we want to change the assert definition there)
#ifdef MY_WINDOWS
#undef MY_WINDOWS
#endif
#if defined(__APPLE__) && (defined(__GNUC__) || defined(__xlC__) || defined(__xlc__))
#elif defined(__SYMBIAN32__) || defined(SYMBIAN)
#elif defined(__CYGWIN__)
#elif defined(MSDOS) || defined(_MSDOS)
#elif defined(__OS2__)
#elif !defined(SAG_COM) && (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
#define MY_WINDOWS
#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#define MY_WINDOWS
#elif defined(__MWERKS__) && defined(__INTEL__)
#define MY_WINDOWS
#endif

#ifdef MY_WINDOWS
#define Q_ASSERT(cond) ((!(cond)) ? txs_assert(#cond,__FILE__,__LINE__) : qt_noop())
#define Q_ASSERT_X(cond, where, what) ((!(cond)) ? txs_assert_x(where, what, __FILE__,__LINE__) : qt_noop())
#undef MY_WINDOWS
#else
#define qt_assert txs_assert
#define qt_assert_x txs_assert_x
#endif
#endif
#endif

void txs_assert(const char *assertion, const char *file, int line);
void txs_assert_x(const char *where, const char *assertion, const char *file, int line);


#endif

#include <QObject>

