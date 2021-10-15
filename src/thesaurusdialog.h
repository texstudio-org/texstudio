#ifndef Header_Thesaurus_Dialog
#define Header_Thesaurus_Dialog

#include "mostQtHeaders.h"
class ThesaurusDatabaseType;
class ThesaurusDialog: public QDialog
{
	Q_OBJECT

public:
	ThesaurusDialog(QWidget *parent = 0);
	~ThesaurusDialog();
	QString getReplaceWord();
	void setSearchWord(const QString &word);
	/*	void readDatabase(const QString filename);
		static ThesaurusDatabaseType loadDatabase(const QString& fileName);
		void setDatabase(ThesaurusDatabaseType database);*/

	static void prepareDatabase(const QString &fileName);
	static void setUserPath(const QString &userDir);
	static ThesaurusDatabaseType *retrieveDatabase();

private slots:
	void classChanged(int row);
	void wordChanged(int row);
	void lookupClicked();
	void containsClicked();
	void startsWithClicked();
	void addUserWordClicked();
	void removeUserWordClicked();

protected:
	QPushButton *replaceBt;
	QPushButton *lookupBt;
	QPushButton *startsWithBt;
	QPushButton *containsBt;
	QPushButton *cancelBt;
	QPushButton *addBt;
	QPushButton *removeBt;
	QLineEdit *searchWrdLe;
	QLineEdit *replaceWrdLe;
	QListWidget *classlistWidget;
	QListWidget *replacelistWidget;

	ThesaurusDatabaseType *thesaurus;
	QString thesaurusFileName;
	static void loadDatabase(const QString &fileName);
	static QString userPath;

	QSet<QString> duplicatesCheck;
	void addItems(const QString &className);
};

#endif // THESAURUSDIALOG_H
