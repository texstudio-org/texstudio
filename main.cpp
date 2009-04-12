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

#include "dsingleapplication.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QSplashScreen>
#include <QDir>
#include <QFileOpenEvent>
#include "texmaker.h"
#include "smallUsefulFunctions.h"
#ifdef Q_WS_WIN
#include "windows.h"
typedef BOOL (*AllowSetForegroundWindowFunc) (DWORD);
#endif
class TexmakerApp : public QApplication
{
protected:
    bool event(QEvent *event);
public:
    bool initialized;
    QString delayedFileLoad;
    Texmaker *mw;  // Moved from private:
    TexmakerApp( int & argc, char ** argv );
    ~TexmakerApp();
    void init( int & argc, char ** argv );  // This function does all the initialization instead of the constructor.
};

TexmakerApp::TexmakerApp( int & argc, char ** argv ) : QApplication ( argc, argv )
{
    mw = 0;
    initialized=false;
}

void TexmakerApp::init( int & argc, char ** argv )
    {
QPixmap pixmap(":/images/splash.png");
QSplashScreen *splash = new QSplashScreen(pixmap);
splash->show();
processEvents();

QTranslator* appTranslator=new QTranslator(this);
QTranslator* basicTranslator=new QTranslator(this);
QString locale = QString(QLocale::system().name()).left(2);
if ( locale.length() < 2 ) locale = "en";
if (appTranslator->load(findResourceFile("texmakerx_"+locale+".qm"))) installTranslator(appTranslator);
if (basicTranslator->load(findResourceFile("qt_"+locale+".qm"))) installTranslator(basicTranslator);
mw = new Texmaker();
connect( this, SIGNAL( lastWindowClosed() ), this, SLOT( quit() ) );
splash->finish(mw);
delete splash;

initialized = true;

QStringList cmdLine;
for ( int i = 1; i < argc; ++i ) cmdLine << argv [i];
if (!delayedFileLoad.isEmpty()) cmdLine << delayedFileLoad;
mw->executeCommandLine(cmdLine,true);
}

TexmakerApp::~TexmakerApp()
{
    if (mw) delete mw;
}

bool TexmakerApp::event ( QEvent * event )
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

int main( int argc, char ** argv )
{
TexmakerApp a( argc, argv ); // This is a dummy constructor so that the programs loads fast.

DSingleApplication instance("TexMakerX");

bool startAlways=false;

for(int i=0; i<argc; ++i)
    if (!strcmp("--start-always",argv[i])) startAlways=true;

if (!startAlways)
    if ( instance.isRunning() ) {
        #ifdef Q_WS_WIN
        AllowSetForegroundWindowFunc asfw = (AllowSetForegroundWindowFunc)GetProcAddress(GetModuleHandleA("user32.dll"),"AllowSetForegroundWindow");
        if (asfw) asfw(/*ASFW_ANY*/(DWORD)(-1));
        
        #endif
        QString msg;
        for(int i=1; i<argc; ++i){
            msg += argv[i];
            msg += "#!#";
        }
        instance.sendMessage( msg );
        return 0;
    }

a.init(argc,argv); // Initialization takes place only if there is no other instance running.

QObject::connect( &instance, SIGNAL( messageReceived(const QString &) ), 
                  a.mw,   SLOT( onOtherInstanceMessage(const QString &) ) );

return a.exec();
}
