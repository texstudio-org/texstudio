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

class LatexReference : public QObject
{
	Q_OBJECT
public:
	explicit LatexReference(QObject *parent=0);

	void setFile(QString filename);
	bool contains(const QString & command);
	QString getTextForTooltip(const QString & command);
	QString getSectionText(const QString & command);
	QString getPartialText(const QString & command);

protected:
	void makeIndex();

private:
	struct Anchor {
		Anchor() {name = QString(); start_pos = -1; end_pos = -1;}
		Anchor(const QString & n) {name = n; start_pos = -1; end_pos = -1;}
		QString name;
		int start_pos;
		int end_pos;
	};

	QString m_filename;
	QString m_htmltext;
	QHash<QString, Anchor> m_anchors; // maps commands to their anchor
	QHash<QString, Anchor> m_sectionAnchors; // maps commands to the anchor of their section
};

#endif // HELP_H
