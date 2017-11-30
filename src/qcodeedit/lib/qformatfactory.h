/*
	Transition header file.
*/

#ifndef _QFORMAT_FACTORY_H_

#include "qformatscheme.h"

class QFormatFactory : public QFormatScheme
{
	public:
		inline QFormatFactory(QObject *p = 0) : QFormatScheme(p) {}
		inline QFormatFactory(const QString& f, QObject *p = 0) : QFormatScheme(f, p) {}
};

#endif
