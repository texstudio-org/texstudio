/*******************************************************************************

  DSingleApplication is basically imitating QtSingleApplication commercial class

  The implementation is though quite different from what is described in
  trolltech documetation for QtSingleApplication. DSingleApplication uses
  tcp sockets to test/open a port in a range and then sed a message to that port
  and expects a correct answer, if it's correct then the app is running and
  we can talk to it.

  Messages sent are in text and start with APP_ID+":", unles message has this three 
  bytes it is descarded. Each text message is prepended with int32 value of
  it's size.

  Author: Dima Fedorov Levit <dimin@dimin.net> <http://www.dimin.net/>
  Copyright (C) BioImage Informatics <www.bioimage.ucsb.edu>

  Licence: GPL

  History:
    02/08/2007 17:14 - First creation
      
  ver: 1       
*******************************************************************************/

#include "dsingleapplication.h"

#include <QtCore>
#include <QtGui>
#include <QtNetwork>


DSingleApplication::DSingleApplication( const QString &id, bool initialize ) {
  other_instance_running = false;
  app_id = id;
  port = d_unique_port_start;

  tcpServer = new DTalker( app_id, this );
  tcpSocket = NULL;

  if (initialize) init();
}

DSingleApplication::~DSingleApplication() {
  if (tcpServer != NULL) delete tcpServer;
  if (tcpSocket != NULL) delete tcpSocket;
}

QString DSingleApplication::id () const {
  return app_id;
}

void DSingleApplication::initialize () {
  init();
}

bool DSingleApplication::isRunning () const {
  // may require some checks here
  return other_instance_running;
}
 
void DSingleApplication::init() {

  // start at d_unique_port_start and go until find a free port or a port
  // that answers correctly
  other_instance_running = false;

  DPortChecker checker( app_id, d_unique_port_start, this );

  // first go over the range of ports and check for other instance
  // if not, then listen on the forst port available
  DPortList ports;

  while (port <= d_unique_port_finish) {

    // here check if the stuff running on port is our instance if not procede
    checker.check( port );
    checker.wait();
    DPortChecker::PortStatus port_status = checker.status();

    if (port_status == DPortChecker::us) {
      other_instance_running = true;
      // here we have to connect to other instance to send messages
      tcpSocket = checker.transferSocketOwnership();
      return;
    }

    DPortInfo pi( port, checker.status() == DPortChecker::free );
    ports << pi;
    ++port;
  } // while

  port = ports.firstFreePort();

  // other instance is not running in the range and there's available port
  if (port == -1) return;
  
  // this port is free and current instance is in listening mode
  bool listening = tcpServer->listen( QHostAddress::LocalHost, port );
  if (listening)
    connect( tcpServer, SIGNAL(messageReceived(const QString &)), this, SLOT(onClientMessage(const QString &)) );

}

bool DSingleApplication::sendMessage ( const QString &message ) {
  if (!other_instance_running) return false;
  if (!tcpSocket) return false;
  if ( tcpSocket->state() != QAbstractSocket::ConnectedState ) return false;

  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setVersion( out.version() ); // set to the current Qt version
  
  QString msg = app_id + ":" + message;
  out << (quint32) msg.size();
  out << msg;

  tcpSocket->write(block);
  tcpSocket->flush();
  tcpSocket->waitForBytesWritten( d_timeout_try_write );

  return true;
}

void DSingleApplication::onClientMessage( const QString & message ) {
  emit messageReceived( message );
}


//******************************************************************************
// DPortChecker
// This class is used to check specific port if it has an instance of this app
//******************************************************************************

DPortChecker::DPortChecker( const QString &id, int port, QObject *parent ) 
: QThread(parent)
{
  tcpSocket = NULL;
  this->port = port;
  app_id = id;
  result = DPortChecker::free;
}

DPortChecker::~DPortChecker() {
  if (tcpSocket != NULL) delete tcpSocket;
}

DPortChecker::PortStatus DPortChecker::status() const {
  return result;
}

void DPortChecker::check( int port ) {
  this->port = port;
  start();
}

void DPortChecker::run() {
  result = DPortChecker::free;

  if (tcpSocket == NULL) 
    tcpSocket = new QTcpSocket();

  tcpSocket->connectToHost( QHostAddress(QHostAddress::LocalHost), port );
  if (!tcpSocket->waitForConnected(d_timeout_try_connect)) { tcpSocket->abort(); return; }

  result = DPortChecker::others;
  if (!tcpSocket->waitForReadyRead(d_timeout_try_read)) { tcpSocket->abort(); return; }

  // now compare received bytes with app_id
  QDataStream in(tcpSocket);
  in.setVersion( in.version() ); // set to the current Qt version

  if (tcpSocket->bytesAvailable() > 0) {
    QString msgString;
    in >> msgString;
    if (msgString.size() <= 1) { tcpSocket->abort(); return; }
    int s = qMin( msgString.size(), app_id.size() );
    if ( QString::compare( msgString.left(s), app_id.left(s) ) == 0)
      result = DPortChecker::us; 
  }
}

QTcpSocket* DPortChecker::transferSocketOwnership() {
  QTcpSocket *tmp = tcpSocket;
  tcpSocket = NULL;
  return tmp;
}

//******************************************************************************
// DTalker
// This is a server responsible to talking to incoming connections
//******************************************************************************

DTalker::DTalker(const QString &id, QObject *parent)
: app_id(id), QTcpServer(parent)
{

}

void DTalker::incomingConnection( int socketDescriptor ) {

  DListner *listner = new DListner(app_id, socketDescriptor, this);
  connect(listner, SIGNAL(messageReceived(const QString &)), this, SLOT(onClientMessage( const QString &)) );
  connect(listner, SIGNAL(finished()), listner, SLOT(deleteLater()));
  listner->start();
}

void DTalker::onClientMessage( const QString & message ) {
  emit messageReceived( message );
}


//******************************************************************************
// DListner
// This thread is used to communicate with connected client
//******************************************************************************

DListner::DListner( const QString &id, int socketDescriptor, QObject *parent ) 
  : socketDescriptor(socketDescriptor), app_id(id), QThread(parent)
{
  blockSize = 0;
}

DListner::~DListner() {

}

void DListner::run() {
  QTcpSocket tcpSocket;
  if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
    return;
  }

  // send app_id to client
  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setVersion( out.version() ); // set to the current Qt version instead
  out << app_id;
  tcpSocket.write(block);
  //waitForBytesWritten ( int msecs ) 

  while (1) {
    if (tcpSocket.state() != QAbstractSocket::ConnectedState) return;
    tcpSocket.waitForReadyRead(-1);
    read( &tcpSocket );
  }
}

void DListner::read( QTcpSocket *tcpSocket ) {
  if (tcpSocket == NULL) return;
  if ( tcpSocket->state() != QAbstractSocket::ConnectedState ) return;

  QDataStream in(tcpSocket);
  in.setVersion( in.version() ); // set to the current Qt version instead

  if (blockSize == 0) {
    if (tcpSocket->bytesAvailable() < (int)sizeof(quint32)) return;
    in >> blockSize;
  }
  if (tcpSocket->bytesAvailable() < blockSize) return;
  QString msgString;
  in >> msgString;
  
  // if header matches, trim and emit
  QString magic = app_id + ":";
  if ( QString::compare( msgString.left(magic.size()), magic ) == 0)
    emit messageReceived( msgString.remove(0, magic.size()) );

  blockSize = 0;
  if (tcpSocket->bytesAvailable() > 0) read(tcpSocket);
}

//******************************************************************************
// DPortList
//******************************************************************************

int DPortList::firstFreePort() {
  DPortList::iterator it = this->begin();
  while ( it < this->end() ) {
    if ( it->free == true ) return it->port;
    ++it;
  }
  return -1;
}

bool DPortList::freePortAvailable() {
  int p = firstFreePort();
  return p != -1;
}
