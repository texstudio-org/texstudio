#ifndef HELP_H
#define HELP_H

#include "mostQtHeaders.h"

class Help : public QObject
{
	Q_OBJECT
public:
	static Help *instance();

	static bool isMiktexTexdoc();
	static int texDocSystem;
	static QString packageDocFile(const QString &package);

	
signals:
	void texdocAvailableReply(const QString &package, bool available);


public slots:
	void execTexdocDialog(const QStringList &packages, const QString &defaultPackage);
	void viewTexdoc(QString package);
	void texdocAvailableRequest(const QString &package);

private slots:
	void viewTexdocError();
	void texdocAvailableRequestFinished(int exitCode);

private:
	Help();
	Help(const Help &);
	Help& operator=(const Help &);

	static Help *m_Instance;

};

#endif // HELP_H
