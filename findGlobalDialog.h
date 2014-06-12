#ifndef FINDGLOBALDIALOG_H
#define FINDGLOBALDIALOG_H

#include <QDialog>

namespace Ui {
    class findGlobalDialog;
}

class findGlobalDialog : public QDialog {
    Q_OBJECT
public:
	enum SearchScope
	{
			Local		= 0,
            OpenedFiles		= 1
	};

    findGlobalDialog(QWidget *parent = 0);
    ~findGlobalDialog();

	void setSearchWord(QString word);
	QString getSearchWord();
    QString getReplaceWord();
	bool isWords();
	bool isCase();
	bool isRegExp();
	int getSearchScope();

private slots:
	void on_cbWords_toggled(bool state);
	void on_cbRegExp_toggled(bool state);


protected:
    void changeEvent(QEvent *e);

private:
    Ui::findGlobalDialog *m_ui;
};

#endif // FINDGLOBALDIALOG_H
