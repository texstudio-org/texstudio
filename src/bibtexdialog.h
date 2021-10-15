#ifndef Header_Bibtex_Dialog
#define Header_Bibtex_Dialog

#include "mostQtHeaders.h"

namespace Ui {
class BibTeXDialog;
}

struct BibTeXType {
	QString name;
	QString description;
	QStringList mandatoryFields, optionalFields;
	BibTeXType (const BibTeXType &other):
		name(other.name), description(other.description),
		mandatoryFields(other.mandatoryFields), optionalFields(other.optionalFields) {}
	BibTeXType (const QString &d, const QString &n, const QStringList &mf, const QStringList &of):
		name(n), description(d), mandatoryFields(mf), optionalFields(of) {}
	BibTeXType & operator= (const BibTeXType &other) = default; // Silence -Wdeprecated-copy
};


class BibTeXDialog : public QDialog
{
	Q_OBJECT
	Q_DISABLE_COPY(BibTeXDialog)

public:
	enum BibType {BIBTEX, BIBLATEX};

	explicit BibTeXDialog(QWidget *parent = 0, const QStringList &fileList = QStringList(), int curFile = -1, const QString &defId = "");
	virtual ~BibTeXDialog();

	QString resultString;
	int resultFileId; //-1 for new, 0..n for files from fileList, -2 for none
	static void setBibType(BibType type);
	static QString textToInsert(const BibTeXType &entry, bool keepOptionalFields, const QMap<QString, QString> &fields);
	static QString textToInsert(const QString &entryName);
	static QList<BibTeXType> getPossibleEntryTypes(BibType type);
protected:
	virtual void changeEvent(QEvent *e);
	virtual void accept();
private slots:
	void typeSelectionChanged();
private:
	Ui::BibTeXDialog *m_ui;
	static void needEntryTypes();
	static void generateBibtexEntryTypes(bool forceRecreate = false);
	static void generateBiblatexEntryTypes(bool forceRecreate = false);
	static QList<BibTeXType> *entryTypes;
	static QList<BibTeXType> bibtexEntryTypes;
	static QList<BibTeXType> biblatexEntryTypes;
	static BibType bibType;
};

#endif // BIBTEXDIALOG_H
