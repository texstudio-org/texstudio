#ifndef THESAURUSDIALOG_H
#define THESAURUSDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QGridLayout>

class thesaurusdialog : public QDialog
{
	Q_OBJECT

public:
	thesaurusdialog(QWidget *parent = 0);
	~thesaurusdialog(){};
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
};

#endif // THESAURUSDIALOG_H
