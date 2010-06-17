#ifndef THESAURUSDIALOG_H
#define THESAURUSDIALOG_H

#include "mostQtHeaders.h"
class ThesaurusDatabaseType;
class ThesaurusDialog: public QDialog
{
	Q_OBJECT

public:
	ThesaurusDialog(QWidget *parent = 0);
	~ThesaurusDialog(){}
	QString getReplaceWord();
	void setSearchWord(const QString word);
/*	void readDatabase(const QString filename);
	static ThesaurusDatabaseType loadDatabase(const QString& fileName);
	void setDatabase(ThesaurusDatabaseType database);*/

	static void prepareDatabase(const QString& fileName);
	static ThesaurusDatabaseType * retrieveDatabase();
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

	ThesaurusDatabaseType *thesaurus;
	QString thesaurusFileName;
	static void loadDatabase(const QString& fileName);
};

#endif // THESAURUSDIALOG_H
