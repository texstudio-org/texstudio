#ifndef MODIFIDIEDQOBJECT_H
#define MODIFIDIEDQOBJECT_H


#ifndef QT_NO_DEBUG
#define qt_assert txs_assert
//void txs_assert(const char *assertion, const char *file, int line);
//#define Q_ASSERT(cond) ((!(cond)) ? qt_assert(#cond,__FILE__,__LINE__) : qt_noop())
#endif

#include <QObject>

Q_CORE_EXPORT void txs_assert(const char *assertion, const char *file, int line);

#endif
