#ifndef THESAURUSDIALOG_H
#define THESAURUSDIALOG_H

#include "mostQtHeaders.h"

typedef QMultiMap<QString,QStringList> ThesaurusDatabaseType;

class ThesaurusDialog: public QDialog
{
	Q_OBJECT

public:
	ThesaurusDialog(QWidget *parent = 0);
	~ThesaurusDialog(){}
	QString getReplaceWord();
	void setSearchWord(const QString word);
        void readDatabase(const QString filename);
        static ThesaurusDatabaseType loadDatabase(QFile *file);
        void setDatabase(ThesaurusDatabaseType database);

private slots:
	void classClicked(QListWidgetItem *item);
	void wordClicked(QListWidgetItem *item);
	void lookupClicked();
	void containsClicked();
	void startsWithClicked();

protected:
	QPushButton* replaceBt;
	QPushButton* lookupBt;
	QPushButton* startsWithBt;
	QPushButton* containsBt;
	QPushButton* cancelBt;
	QLineEdit* searchWrdLe;
	QLineEdit* replaceWrdLe;
	QListWidget *classlistWidget;
	QListWidget *replacelistWidget;

	QMultiMap<QString,QStringList> Thesaurus;
	QString thesaurusFileName;
};

#endif // THESAURUSDIALOG_H
