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

  Notes:
  In order to use this class you might consider changing the range of ports to scan
  delimited by: [d_unique_port_start,d_unique_port_finish]
  and timeouts used: d_timeout_try_connect, d_timeout_try_read, d_timeout_try_write.

  Todo: 
  Implement another, faster and more robust cross-platform method to identify wheter
  another instance is running, once done then the port scan can be performed.

  Author: Dima Fedorov Levit <dimin@dimin.net> <http://www.dimin.net/>
  Copyright (C) BioImage Informatics <www.bioimage.ucsb.edu>

  Licence: GPL

  History:
    02/08/2007 17:14 - First creation
      
  ver: 1       
*******************************************************************************/

#ifndef D_SINGLE_APPLICATION_H
#define D_SINGLE_APPLICATION_H

const int d_unique_port_start  = 23232;
const int d_unique_port_finish = 23242;

// timeouts are in ms
const int d_timeout_try_connect = 10; 
const int d_timeout_try_read    = 1000; 
const int d_timeout_try_write   = 30000; 

#include <QString>
#include <QThread>
#include <QTcpSocket>
#include <QTcpServer>

class DTalker;

//******************************************************************************
// DSingleApplication
//******************************************************************************

class DSingleApplication : public QObject {
  Q_OBJECT

public:
  DSingleApplication( const QString & id, bool initialize = true );
  ~DSingleApplication();
  QString id() const;
  void initialize ( );
  bool isRunning () const;
 
public slots:
  bool sendMessage ( const QString & message );

signals:
  void messageReceived ( const QString & message ); 



protected slots:
  void onClientMessage( const QString & message );

private:
  // server is used if no other instance was found to start the port and wait for others
  DTalker *tcpServer;
  // socket is used if other instance was found to communicate with it
  QTcpSocket *tcpSocket;

  int port;
  QString app_id;
  bool other_instance_running;

  void init();
};


//******************************************************************************
// DPortChecker
// This class is used to check specific port if it has an instance of this app
//******************************************************************************

class DPortChecker : public QThread {
  Q_OBJECT

public:
  enum PortStatus { free=0, us=1, others=2 };

  DPortChecker( const QString &id, int port, QObject *parent = 0 );
  ~DPortChecker();

  PortStatus status() const;
  void check( int port );
  QTcpSocket* transferSocketOwnership();

protected:
  void run();

private:
  PortStatus result; 
  QTcpSocket *tcpSocket;
  int port;
  QString app_id;
};


//******************************************************************************
// DTalker
// This is a server responsible to talking to incoming connections
//******************************************************************************

class DTalker : public QTcpServer {
  Q_OBJECT

public:
  DTalker( const QString &id, QObject *parent = 0 );

signals:
  void messageReceived ( const QString & message ); 

protected slots:
  void onClientMessage( const QString & message );

protected:
  void incomingConnection(int socketDescriptor);

private:
  QString app_id;

};


//******************************************************************************
// DListner
// This thread is used to communicate with connected client
//******************************************************************************

class DListner : public QThread {
  Q_OBJECT

public:
  DListner( const QString &id, int socketDescriptor, QObject *parent );
  ~DListner();

signals:
  void messageReceived ( const QString & message ); 

protected:
  void run();

private:
  int socketDescriptor;
  QString app_id;
  quint32 blockSize;

  void read( QTcpSocket *tcpSocket );
};

//******************************************************************************
// DPortList
//******************************************************************************

class DPortInfo {
public:
  DPortInfo( int p, bool f ): port(p), free(f) { }
  int port;
  bool free;
};

class DPortList : public QList<DPortInfo> {
public:
  int firstFreePort();
  bool freePortAvailable();
};

#endif //D_SINGLE_APPLICATION_H
