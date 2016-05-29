#ifndef MODIFIDIEDQOBJECT_H
#define MODIFIDIEDQOBJECT_H


#include <qglobal.h>


#ifndef NO_CRASH_HANDLER

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#define ASSERT_THROW Q_DECL_NOTHROW
#else
#define ASSERT_THROW
#endif


#ifndef QT_NO_DEBUG

#undef Q_ASSERT
#undef Q_ASSERT_X

#define Q_ASSERT(cond) ((!(cond)) ? txs_assert(#cond,__FILE__,__LINE__) : qt_noop())
#define Q_ASSERT_X(cond, where, what) ((!(cond)) ? txs_assert_x(where, what, __FILE__,__LINE__) : qt_noop())


#define qt_assert txs_assert
#define qt_assert_x txs_assert_x




void txs_assert(const char *assertion, const char *file, int line) ASSERT_THROW;
void txs_assert_x(const char *where, const char *assertion, const char *file, int line) ASSERT_THROW;


#endif
#endif

#include <QObject>

#endif
