#ifndef Header_Help
#define Header_Help

#include "mostQtHeaders.h"

class Help : public QObject
{
	Q_OBJECT

public:
    explicit Help(QObject *parent=nullptr);

    bool isMiktexTexdoc();
    bool isTexdocExpectedToFinish();
    QString packageDocFile(const QString &package, bool silent = false);

signals:
	void texdocAvailableReply(const QString &package, bool available, QString errorMessage);
    void runCommand(const QString &commandline, QString *output);
    void runCommandAsync(const QString &commandline, const char * returnCmd);
    void statusMessage(const QString &message);

public slots:
	void execTexdocDialog(const QStringList &packages, const QString &defaultPackage);
	void viewTexdoc(QString package);
	void texdocAvailableRequest(const QString &package);
    void texdocAvailableRequestFinished(int,QProcess::ExitStatus status);

private:
    QString runTexdoc(QString args);
    bool runTexdocAsync(QString args,const char * finishedCMD);
    int texDocSystem;
};


class LatexReference : public QObject
{
	Q_OBJECT

public:
	explicit LatexReference(QObject *parent = 0);

	void setFile(QString filename);
	bool contains(const QString &command);
	QString getTextForTooltip(const QString &command);
	QString getSectionText(const QString &command);
	QString getPartialText(const QString &command);

protected:
	void makeIndex();

private:
	struct Anchor {
		Anchor()
		{
			name = QString();
			start_pos = -1;
			end_pos = -1;
		}
		Anchor(const QString &n)
		{
			name = n;
			start_pos = -1;
			end_pos = -1;
		}
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
