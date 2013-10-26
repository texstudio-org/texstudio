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


#if QT_VERSION >= 0x040400
#include <qtsingleapplication.h>
#else
#include "dsingleapplication.h"
#endif

#include <QSplashScreen>
#ifdef Q_WS_WIN
#include "windows.h"
typedef BOOL (*AllowSetForegroundWindowFunc)(DWORD);
#endif


#if QT_VERSION >= 0x040400
class TexmakerApp : public QtSingleApplication {
#else
class TexmakerApp : public QApplication {
#endif
protected:
	bool event(QEvent *event);
public:
	bool initialized;
	QString delayedFileLoad;
	Texmaker *mw;  // Moved from private:
	TexmakerApp(int & argc, char ** argv);
    #if QT_VERSION >= 0x040400
	TexmakerApp(QString &id,int & argc, char ** argv);
    #endif
	~TexmakerApp();
	void init(QStringList &cmdLine);   // This function does all the initialization instead of the constructor.
/*really slow global event logging:
	bool notify(QObject* obj, QEvent* event){
		qWarning(qPrintable(QString("%1 obj %2 named %3 typed %4 child of %5 received %6").arg(QTime::currentTime().toString("HH:mm:ss:zzz")).arg((long)obj,8,16).arg(obj->objectName()).arg(obj->metaObject()->className()).arg(obj->parent()?obj->parent()->metaObject()->className():"").arg(event->type())));
		return QApplication::notify(obj,event);
	}//*/
};


#if QT_VERSION >= 0x040400
TexmakerApp::TexmakerApp(int & argc, char ** argv) : QtSingleApplication(argc, argv) {
	mw = 0;
	initialized=false;
}

TexmakerApp::TexmakerApp(QString &id,int & argc, char ** argv) : QtSingleApplication(id,argc, argv) {
	mw = 0;
	initialized=false;
}
#else
TexmakerApp::TexmakerApp(int & argc, char ** argv) : QApplication(argc, argv) {
	mw = 0;
	initialized=false;
}
#endif





void TexmakerApp::init(QStringList &cmdLine) {
	QPixmap pixmap(":/images/splash.png");
	QSplashScreen *splash = new QSplashScreen(pixmap);
	splash->show();
	processEvents();

	mw = new Texmaker(0,0,splash);
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
	QStringList environment = QProcess::systemEnvironment();
	QString user=environment.filter(QRegExp("^USERNAME=|^USER=",Qt::CaseInsensitive)).first();

	if(!user.isEmpty()){
		int l=user.indexOf("=",0);
		user="_"+user.right(user.length()-l-1);
	}
	user=TEXSTUDIO+user;
#if QT_VERSION >= 0x040400
	TexmakerApp a(user,argc, argv);
#else
    TexmakerApp a(argc, argv);
	DSingleApplication instance(user);
#endif
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
			else if ((cmdArgument == "-page" || cmdArgument == "--page") && (++i < args.count()))
				cmdLine << "--page" << args[i];
			else if ((cmdArgument == "-insert-cite" || cmdArgument == "--insert-cite") && (++i < args.count()))
				cmdLine << "--insert-cite" << args[i];
			else if (cmdArgument == "--ini-file" && (++i < args.count()))
				ConfigManager::iniFileOverride = args[i];
			else if (cmdArgument.startsWith("-"))
				cmdLine << cmdArgument;			
		} else
			cmdLine << QFileInfo(cmdArgument).absoluteFilePath();
	}

	if (!startAlways)
#if QT_VERSION >= 0x040400
		if (a.isRunning()) {
#else
		if (instance.isRunning()) {
#endif
#ifdef Q_WS_WIN
			AllowSetForegroundWindowFunc asfw = (AllowSetForegroundWindowFunc)GetProcAddress(GetModuleHandleA("user32.dll"),"AllowSetForegroundWindow");
			if (asfw) asfw(/*ASFW_ANY*/(DWORD)(-1));
#endif

#if QT_VERSION >= 0x040400
			a.sendMessage(cmdLine.join("#!#"));
#else
			instance.sendMessage(cmdLine.join("#!#"));
#endif
			return 0;
		}

	a.setApplicationName( TEXSTUDIO );
	a.init(cmdLine); // Initialization takes place only if there is no other instance running.

#if QT_VERSION >= 0x040400
	QObject::connect(&a, SIGNAL(messageReceived(const QString &)),
					 a.mw,   SLOT(onOtherInstanceMessage(const QString &)));
#else
	QObject::connect(&instance, SIGNAL(messageReceived(const QString &)),
					 a.mw,   SLOT(onOtherInstanceMessage(const QString &)));
#endif

	return a.exec();
}
