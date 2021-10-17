#ifndef Header_MathAssistant
#define Header_MathAssistant

#include "mostQtHeaders.h"

class MathAssistant : public QObject
{
	Q_OBJECT

public:
	static MathAssistant *instance();

	void exec();

signals:
	void formulaReceived(QString formula);

public slots:

private slots:
	void processError(QProcess::ProcessError err);
	void processFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
	MathAssistant();

	static MathAssistant *m_Instance;

	QProcess process;
	QString lastClipboardText;
};

#endif // MATHASSISTANT_H
