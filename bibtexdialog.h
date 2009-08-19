#ifndef BIBTEXDIALOG_H
#define BIBTEXDIALOG_H

#include "mostQtHeaders.h"

namespace Ui {
    class BibTeXDialog;
}

struct BibTeXType {
	QString name;
	QString description;
	QStringList mandatoryFields, optionalFields;
	BibTeXType (const BibTeXType& other): 
			name(other.name), description(other.description), 
			mandatoryFields(other.mandatoryFields), optionalFields(other.optionalFields){}
	BibTeXType (const QString& d, const QString& n, const QStringList& mf, const QStringList& of):
			name(n), description(d), mandatoryFields(mf), optionalFields(of){}		
};


class BibTeXDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(BibTeXDialog)
public:
    explicit BibTeXDialog(QWidget *parent = 0, const QStringList& sl=QStringList(), const QString& curFile=QString());
    virtual ~BibTeXDialog();

	QString resultString;
	static QString textToInsert(const BibTeXType& entry, bool keepOptionalFields, const QMap<QString,QString>& fields);
	static QString textToInsert(const QString& entryName);
	static QList<BibTeXType> getPossibleBibTeXTypes();
protected:
    virtual void changeEvent(QEvent *e);
	virtual void accept();
private slots:
	void typeSelectionChanged();
private:
    Ui::BibTeXDialog *m_ui;
	static void needTypes();
	static QList<BibTeXType> types;
};

#endif // BIBTEXDIALOG_H
