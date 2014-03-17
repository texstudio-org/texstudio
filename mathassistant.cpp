#include "mathassistant.h"
#include "smallUsefulFunctions.h"
#include <QMutex>

MathAssistant *MathAssistant::m_Instance = 0;

MathAssistant::MathAssistant() :
	QObject()
{
	connect(&process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processError(QProcess::ProcessError)));
	connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processFinished(int,QProcess::ExitStatus)));
}

void MathAssistant::exec() {
	if (process.state() == QProcess::Running) return;

	// return value of TexTablet is always zero, so we have to decide on the clipboard contents, if TexTablet was aborted
	lastClipboardText = QApplication::clipboard()->text();
	QApplication::clipboard()->clear();

	//TODO This is the default installation path of TexTablet. Make it configurabe.
	QString texTablet = QCoreApplication::applicationDirPath() + "/TexTablet/TeXTablet.exe";
	if (!QFileInfo(texTablet).exists()) {
		QString msg = QString(tr("TexTablet not found."));
		QMessageBox msgBox;
		msgBox.setWindowTitle(tr("Math Assistant"));
		msgBox.setTextFormat(Qt::RichText);
		msgBox.setText(msg);
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.exec();
		return;
	}
	process.setWorkingDirectory(QFileInfo(texTablet).absolutePath());
	process.start("\""+texTablet+"\"");
}

void MathAssistant::processError(QProcess::ProcessError err)
{
	switch(err)
	{
	case QProcess::FailedToStart:
		QMessageBox::information(0,"FailedToStart","FailedToStart");
		break;
	case QProcess::Crashed:
		QMessageBox::information(0,"Crashed","Crashed");
		break;
	case QProcess::Timedout:
		QMessageBox::information(0,"Timedout","Timedout");
		break;
	case QProcess::WriteError:
		QMessageBox::information(0,"WriteError","WriteError");
		break;
	case QProcess::ReadError:
		QMessageBox::information(0,"ReadError","ReadError");
		break;
	case QProcess::UnknownError:
		QMessageBox::information(0,"UnknownError","UnknownError");
		break;
	default:
		QMessageBox::information(0,"default","default");
		break;
	}
}

void MathAssistant::processFinished(int exitCode, QProcess::ExitStatus exitStatus) {
	Q_UNUSED(exitCode);
	if (exitStatus != QProcess::NormalExit) {
		txsCritical(tr("TexTablet crashed."));
	}
	// exit code is always zero for TexTablet

	QString text = QApplication::clipboard()->text();
	if (text.startsWith("$"))
		emit formulaReceived(text);
	QApplication::clipboard()->setText(lastClipboardText);
}

MathAssistant *MathAssistant::instance() {
	static QMutex mutex;
	mutex.lock();
	if (!m_Instance)
		m_Instance = new MathAssistant();
	mutex.unlock();
	return m_Instance;
}
