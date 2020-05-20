#ifndef EXECPROGRAM_T_H
#define EXECPROGRAM_T_H

#ifndef QT_NO_DEBUG

#include "mostQtHeaders.h"

class ExecProgramTest: public QObject
{
	Q_OBJECT

private slots:
	void commandLineParser_data(void);
	void commandLineParser(void);
};

#endif // QT_NO_DEBUG

#endif // EXECPROGRAM_T_H
