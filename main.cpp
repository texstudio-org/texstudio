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

class TexmakerApp : public QApplication
{
private:
    //Texmaker *mw;  // Moved to public
protected:
    bool event(QEvent *event);
public:
    Texmaker *mw;  // Moved from private:
    TexmakerApp( int & argc, char ** argv );
    ~TexmakerApp();
    void init( int & argc, char ** argv );  // This function does all the initialization instead of the constructor.
};

TexmakerApp::TexmakerApp( int & argc, char ** argv ) : QApplication ( argc, argv )
{
    mw = 0;
}

void TexmakerApp::init( int & argc, char ** argv )
{
QPixmap pixmap(":/images/splash.png");
QSplashScreen *splash = new QSplashScreen(pixmap);
splash->show();
QTranslator* appTranslator=new QTranslator(this);
QTranslator* basicTranslator=new QTranslator(this);
#if defined( Q_WS_X11 )
QString transdir=PREFIX"/share/texmaker";
#endif
#if defined( Q_WS_MACX )
QString transdir=QCoreApplication::applicationDirPath() + "/../Resources";
#endif
#if defined(Q_WS_WIN)
QString transdir=QCoreApplication::applicationDirPath();
#endif
QString locale = QString(QLocale::system().name()).left(2);
if ( locale.length() < 2 ) locale = "en";
if (appTranslator->load(QString("texmaker_")+locale,transdir)) 	installTranslator(appTranslator);
if (basicTranslator->load(QString("qt_")+locale,transdir)) installTranslator(basicTranslator);
mw = new Texmaker();
connect( this, SIGNAL( lastWindowClosed() ), this, SLOT( quit() ) );
splash->finish(mw);
delete splash;
for ( int i = 1; i < argc; ++i )
	{
	QString arg = argv[ i ];
	if ( arg[0] != '-' )    mw->load( arg );
	if ( arg == "-master" ) mw->ToggleMode();
	if (( arg == "-line" ) && (i<argc-1))  mw->setLine( argv[ ++i ] );
	}
}

TexmakerApp::~TexmakerApp()
{
    if (mw) delete mw;
}

bool TexmakerApp::event ( QEvent * event )
{
    if (event->type() == QEvent::FileOpen) {
        QFileOpenEvent *oe = static_cast<QFileOpenEvent *>(event);
        mw->load(oe->file());
    }
    return QApplication::event(event);
}

int main( int argc, char ** argv )
{
TexmakerApp a( argc, argv ); // This is a dummy constructor so that the programs loads fast.

DSingleApplication instance("TexMaker");
if ( instance.isRunning() ) {
    QString msg;
    for(int i=0; i<argc; ++i){
        msg += argv[i];
        msg += "#!#";
    }
    instance.sendMessage( msg );
    return 0;
}

a.init(argc,argv); // Initialization takes place only if there is no other instance running.

QObject::connect( &instance, SIGNAL( messageReceived(const QString &) ),                   a.mw,   SLOT( onOtherInstanceMessage(const QString &) ) );

return a.exec();
}
