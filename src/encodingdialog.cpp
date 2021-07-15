#include "encodingdialog.h"
#include "encoding.h"

EncodingDialog::EncodingDialog(QWidget *parent, QEditor *editor) :
	QDialog(parent), edit(editor)
{
	setupUi(this);
	UtilsUi::resizeInFontHeight(this, 55, 26);

	encodings->setSelectionBehavior(QAbstractItemView::SelectRows);
	encodings->setRowCount(QTextCodec::availableMibs().size());
	int row = 0;
	foreach (const int mib, QTextCodec::availableMibs()) {
		QTextCodec *codec = QTextCodec::codecForMib(mib);
		QString name = codec->name();
		foreach (const QByteArray ba, QTextCodec::codecForMib(mib)->aliases())
			name += " / " + ba;
		QTableWidgetItem *it = new QTableWidgetItem(name);
		it->setData(Qt::UserRole, mib);
		if (mib == 0 || mib == 4 /*latin1*/ || mib == 106 /*utf-8*/ || mib == 1013 || mib == 1014 /*utf16be+le*/) {
			QFont font = QApplication::font();
			font.setBold(true);
			it->setFont(font);
		}
		encodings->setItem(row, 0, it);
		if (mib == edit->getFileCodec()->mibEnum()) encodings->setCurrentItem(it);
		it = new QTableWidgetItem(Encoding::latexNamesForTextCodec(codec).join(" or "));
		it->setData(Qt::UserRole, mib);
		encodings->setItem(row, 1, it);
		row++;
	}
	encodings->resizeColumnsToContents();
	encodings->resizeRowsToContents();
	encodings->setFocus();
	label->setText(tr("Select Encoding for") + " \"" + QDir::toNativeSeparators(edit->fileName()) + "\"");
    if (!QFileInfo::exists(edit->fileName())) reload->setEnabled(false);
}

void EncodingDialog::changeEvent(QEvent *e)
{
	switch (e->type()) {
	case QEvent::LanguageChange:
		retranslateUi(this);
		break;
	default:
		break;
	}
}

void EncodingDialog::on_view_clicked()
{
	if (!UtilsUi::txsConfirmWarning(tr("If the new and old encodings are incompatible, some characters may be destroyed.\nAre you sure you want accept data loss?"))) {
		reject();
		return;
	}
	edit->viewWithCodec(QTextCodec::codecForMib(encodings->currentItem()->data(Qt::UserRole).toInt()));
	accept();
}

void EncodingDialog::on_change_clicked()
{
	edit->setFileCodec(QTextCodec::codecForMib(encodings->currentItem()->data(Qt::UserRole).toInt()));
	accept();
}

void EncodingDialog::on_reload_clicked()
{
	if (edit->isContentModified())
		if (!UtilsUi::txsConfirmWarning(tr("The document has been changed.\nThese changes will be lost, if you reload it with the new encoding.\nAre you sure you want to undo all changes?"))) {
			reject();
			return;
		}
	LatexDocument *doc = qobject_cast<LatexDocument *>(edit->document());
	doc->initClearStructure();
	edit->load(edit->fileName(), QTextCodec::codecForMib(encodings->currentItem()->data(Qt::UserRole).toInt()));
	accept();
}

void EncodingDialog::on_cancel_clicked()
{
	reject();
}
