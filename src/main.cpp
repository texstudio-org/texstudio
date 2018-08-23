/***************************************************************************
 *   copyright       : (C) 2003-2007 by Pascal Brachet                     *
 *   addons by Frederic Devernay <frederic.devernay@m4x.org>               *
 *   addons by Luis Silvestre                                              *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "mostQtHeaders.h"
/*! \mainpage TexStudio
 *
 * \see Texstudio
 * \see PDFDocument
 */

#include "texstudio.h"
#include "smallUsefulFunctions.h"
#include "debughelper.h"
#include "utilsVersion.h"
#include <qtsingleapplication.h>
#include <QSplashScreen>

#ifdef Q_OS_WIN32
#include "windows.h"
typedef BOOL (WINAPI *AllowSetForegroundWindowFunc)(DWORD);
#endif

class TexstudioApp : public QtSingleApplication
{
public:
	bool initialized;
	QString delayedFileLoad;
	Texstudio *mw;  // Moved from private:
	TexstudioApp(int &argc, char **argv);
	TexstudioApp(QString &id, int &argc, char **argv);
	~TexstudioApp();
	void init(QStringList &cmdLine);   // This function does all the initialization instead of the constructor.
	/*bool notify(QObject* obj, QEvent* event){
		//really slow global event logging:
		//qWarning(qPrintable(QString("%1 obj %2 named %3 typed %4 child of %5 received %6").arg(QTime::currentTime().toString("HH:mm:ss:zzz")).arg((long)obj,8,16).arg(obj->objectName()).arg(obj->metaObject()->className()).arg(obj->parent()?obj->parent()->metaObject()->className():"").arg(event->type())));
		try {
			return QApplication::notify(obj,event);
		} catch (const std::exception& e){
			qDebug() << "Catched exception: " << e.what();
			return false;
		}
	}*/


protected:
	bool event(QEvent *event);
};

TexstudioApp::TexstudioApp(int &argc, char **argv) : QtSingleApplication(argc, argv)
{
    mw = nullptr;
	initialized = false;
}

TexstudioApp::TexstudioApp(QString &id, int &argc, char **argv) : QtSingleApplication(id, argc, argv)
{
    mw = nullptr;
	initialized = false;
}

void TexstudioApp::init(QStringList &cmdLine)
{
	QPixmap pixmap(":/images/splash.png");
	QSplashScreen *splash = new QSplashScreen(pixmap);
	splash->show();
	processEvents();

    mw = new Texstudio(nullptr, nullptr, splash);
	connect(this, SIGNAL(lastWindowClosed()), this, SLOT(quit()));
	splash->finish(mw);
	delete splash;

	initialized = true;

	if (!delayedFileLoad.isEmpty()) cmdLine << delayedFileLoad;
	mw->executeCommandLine(cmdLine, true);
    if(!cmdLine.contains("--auto-tests")){
        mw->startupCompleted();
    }
}

TexstudioApp::~TexstudioApp()
{
	if (mw) delete mw;
}

bool TexstudioApp::event(QEvent *event)
{
	if (event->type() == QEvent::FileOpen) {
		QFileOpenEvent *oe = static_cast<QFileOpenEvent *>(event);
		if (initialized) mw->load(oe->file());
		else delayedFileLoad = oe->file();
		event->accept();
		return true;
	}
	return QApplication::event(event);
}

QString generateAppId()
{
	QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
	QString user = env.value("USER");
	if (user.isEmpty()) {
		user = env.value("USERNAME");
	}
	return QString("%1_%2").arg(TEXSTUDIO).arg(user);
}

QStringList parseArguments(const QStringList &args, bool &outStartAlways)
{
	QStringList cmdLine;
	for (int i = 1; i < args.count(); ++i) {
		QString cmdArgument =  args[i];

		if (cmdArgument.startsWith('-')) {
			// various commands
			if (cmdArgument == "--start-always")
				outStartAlways = true;
			else if (cmdArgument == "--no-session")
				ConfigManager::dontRestoreSession = true;
			else if ((cmdArgument == "-line" || cmdArgument == "--line") && (++i < args.count()))
				cmdLine << "--line" << args[i];
			else if ((cmdArgument == "-page" || cmdArgument == "--page") && (++i < args.count()))
				cmdLine << "--page" << args[i];
			else if ((cmdArgument == "-insert-cite" || cmdArgument == "--insert-cite") && (++i < args.count()))
				cmdLine << "--insert-cite" << args[i];
			else if (cmdArgument == "--ini-file" && (++i < args.count())) {
				// deprecated: use --config instead
				ConfigManager::configDirOverride = QFileInfo(args[i]).absolutePath();
			}
			else if (cmdArgument == "--config" && (++i < args.count()))
				ConfigManager::configDirOverride = args[i];
			else if (cmdArgument.startsWith("-"))
				cmdLine << cmdArgument;
		} else
			cmdLine << QFileInfo(cmdArgument).absoluteFilePath();
	}
	return cmdLine;
}

bool handleCommandLineOnly(const QStringList &cmdLine) {
	// note: stdout is not supported for Win GUI applications. Will simply not output anything there.
	if (cmdLine.contains("--help")) {
		QTextStream(stdout) << "Usage: texstudio [options] [file]\n"
							<< "\n"
							<< "Options:\n"
							<< "  --config DIR            use the specified settings directory\n"
							<< "  --master                define the document as explicit root document\n"
							<< "  --line LINE[:COL]       position the cursor at line LINE and column COL\n"
							<< "  --insert-cite CITATION  inserts the given citation\n"
							<< "  --start-always          start a new instance, even if TXS is already running\n"
							<< "  --pdf-viewer-only       run as a standalone pdf viewer without an editor\n"
							<< "  --page PAGENUM          display a certain page in the pdf viewer\n"
                            << "  --no-session            do not load/save the session at startup/close\n"
                            << "  --version               show version number\n";
		return true;
	}

	if (cmdLine.contains("--version")) {
        QTextStream(stdout) << "TeXstudio " << TXSVERSION << " (" << TEXSTUDIO_GIT_REVISION << ")\n";
		return true;
	}

	return false;
}

int main(int argc, char **argv)
{
	QString appId = generateAppId();
	// This is a dummy constructor so that the programs loads fast.
	TexstudioApp a(appId, argc, argv);
	bool startAlways = false;
	QStringList cmdLine = parseArguments(QCoreApplication::arguments(), startAlways);

	if (handleCommandLineOnly(cmdLine)) {
		return 0;
	}

	if (!startAlways) {
		if (a.isRunning()) {
#ifdef Q_OS_WIN32
			AllowSetForegroundWindowFunc asfw = (AllowSetForegroundWindowFunc) GetProcAddress(GetModuleHandleA("user32.dll"), "AllowSetForegroundWindow");
			if (asfw) asfw(/*ASFW_ANY*/(DWORD)(-1));
#endif
			a.sendMessage(cmdLine.join("#!#"));
			return 0;
		}
	}

	a.setApplicationName( TEXSTUDIO );
	a.init(cmdLine); // Initialization takes place only if there is no other instance running.

	QObject::connect(&a, SIGNAL(messageReceived(const QString &)),
	                 a.mw, SLOT(onOtherInstanceMessage(const QString &)));

	try {
		return a.exec();
	} catch (...) {
#ifndef NO_CRASH_HANDLER
		catchUnhandledException();
#endif
		throw;
	}
}
