#ifndef THESAURUSDIALOG_H
#define THESAURUSDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QGridLayout>

class ThesaurusDialog: public QDialog
{
	Q_OBJECT

public:
	ThesaurusDialog(QWidget *parent = 0);
	~ThesaurusDialog(){};
	QString getReplaceWord();
	void setSearchWord(const QString word);
	void readDatabase(const QString filename);

private slots:
	void classClicked(QListWidgetItem *item);
	void wordClicked(QListWidgetItem *item);
	void lookupClicked();

protected:
	QPushButton* replaceBt;
	QPushButton* lookupBt;
	QPushButton* cancelBt;
	QLineEdit* searchWrdLe;
	QLineEdit* replaceWrdLe;
	QListWidget *classlistWidget;
	QListWidget *replacelistWidget;

	QMultiMap<QString,QStringList> Thesaurus;
	QString thesaurusFileName;
};

#endif // THESAURUSDIALOG_H
