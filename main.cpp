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
 
#include "texmaker.h"
#include "smallUsefulFunctions.h"
#include "dsingleapplication.h"

#include <QSplashScreen>
#ifdef Q_WS_WIN
#include "windows.h"
typedef BOOL (*AllowSetForegroundWindowFunc)(DWORD);
#endif
class TexmakerApp : public QApplication {
protected:
	bool event(QEvent *event);
public:
	bool initialized;
	QString delayedFileLoad;
	Texmaker *mw;  // Moved from private:
	TexmakerApp(int & argc, char ** argv);
	~TexmakerApp();
	void init(QStringList &cmdLine);   // This function does all the initialization instead of the constructor.
};

TexmakerApp::TexmakerApp(int & argc, char ** argv) : QApplication(argc, argv) {
	mw = 0;
	initialized=false;
}

void TexmakerApp::init(QStringList &cmdLine) {
	QPixmap pixmap(":/images/splash.png");
	QSplashScreen *splash = new QSplashScreen(pixmap);
	splash->show();
	processEvents();

	mw = new Texmaker();
	connect(this, SIGNAL(lastWindowClosed()), this, SLOT(quit()));
	splash->finish(mw);
	delete splash;

	initialized = true;

	if (!delayedFileLoad.isEmpty()) cmdLine << delayedFileLoad;
	mw->executeCommandLine(cmdLine,true);
}

TexmakerApp::~TexmakerApp() {
	if (mw) delete mw;
}

bool TexmakerApp::event(QEvent * event) {
	if (event->type() == QEvent::FileOpen) {
		QFileOpenEvent *oe = static_cast<QFileOpenEvent *>(event);
		if (initialized) mw->load(oe->file());
		else delayedFileLoad = oe->file();
		event->accept();
		return true;
	}
	return QApplication::event(event);
}

int main(int argc, char ** argv) {
// This is a dummy constructor so that the programs loads fast.
	TexmakerApp a(argc, argv);
	QStringList environment = QProcess::systemEnvironment();
	QString user=environment.filter(QRegExp("^USERNAME=|^USER=",Qt::CaseInsensitive)).first();
	if(!user.isEmpty()){
		int l=user.indexOf("=",0);
		user="_"+user.right(user.length()-l-1);
	}
	user="TexMakerX"+user;
	DSingleApplication instance(user);

	bool startAlways=false;
	QStringList args = QCoreApplication::arguments();
	QStringList cmdLine;
	for (int i = 1; i < args.count(); ++i) {
		QString cmdArgument =  args[i];

		if (cmdArgument.startsWith('-')) {
			// various commands
			if (cmdArgument == "--start-always")
				startAlways = true;
			else if ((cmdArgument == "-line" || cmdArgument == "--line") && (++i < args.count()))
				cmdLine << "--line" << args[i];
			else if (cmdArgument.startsWith("-"))
				cmdLine << cmdArgument;			
		} else
			cmdLine << QFileInfo(cmdArgument).absoluteFilePath();
	}

	if (!startAlways)
		if (instance.isRunning()) {
#ifdef Q_WS_WIN
			AllowSetForegroundWindowFunc asfw = (AllowSetForegroundWindowFunc)GetProcAddress(GetModuleHandleA("user32.dll"),"AllowSetForegroundWindow");
			if (asfw) asfw(/*ASFW_ANY*/(DWORD)(-1));
#endif

			instance.sendMessage(cmdLine.join("#!#"));
			return 0;
		}

	a.init(cmdLine); // Initialization takes place only if there is no other instance running.

	QObject::connect(&instance, SIGNAL(messageReceived(const QString &)),
	                 a.mw,   SLOT(onOtherInstanceMessage(const QString &)));

	return a.exec();
}
