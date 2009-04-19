#include "encodingdialog.h"
#include <QFileInfo>
#include <QFont>
#include <QMessageBox>
#include <QTextCodec>
EncodingDialog::EncodingDialog(QWidget *parent, QEditor *editor) :
    QDialog(parent), edit(editor){
    setupUi(this);
	foreach (int mib, QTextCodec::availableMibs()) {
		QString name = QTextCodec::codecForMib(mib)->name();
		foreach(QByteArray ba, QTextCodec::codecForMib(mib)->aliases())
			name+=" / " + ba;
		QListWidgetItem* it = new QListWidgetItem(name, encodings);
		it->setData(Qt::UserRole, mib);
		if (mib==edit->getFileEncoding()->mibEnum()) encodings->setCurrentItem(it);
		if (mib==0 || mib==4 /*latin1*/ || mib==106 /*utf-8*/ || mib==1013 || mib==1014 /*utf16be+le*/){
			QFont font=QApplication::font();
			font.setBold(true);
			it->setFont(font);
		}
	}
	label->setText("Select Encoding for \""+edit->fileName()+"\"");
	if (!QFileInfo(edit->fileName()).exists()) reload->setEnabled(false);
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

void EncodingDialog::on_view_clicked(){
	if (QMessageBox::warning(this,"TexMakerX",tr("If the new and old encodings are incompatible, some characters may be destroyed.\nAre you sure you want accept data loss?"),QMessageBox::Yes|QMessageBox::No) != QMessageBox::Yes){
        reject();
		return;
	}
	edit->viewAsEncoding(QTextCodec::codecForMib(encodings->currentItem()->data(Qt::UserRole).toInt()));
	accept();
}
void EncodingDialog::on_change_clicked(){
	edit->setFileEncoding(QTextCodec::codecForMib(encodings->currentItem()->data(Qt::UserRole).toInt()));
	accept();
}
void EncodingDialog::on_reload_clicked(){
	if (edit->isContentModified()) 
		if (QMessageBox::warning(this,"TexMakerX",tr("The document has been changed.\nThese changes will be lost, if you reload it with the new encoding.\nAre you sure you want to undo all changes?"),QMessageBox::Yes|QMessageBox::No) != QMessageBox::Yes){
            reject();
			return;
		}
	edit->load(edit->fileName(),QTextCodec::codecForMib(encodings->currentItem()->data(Qt::UserRole).toInt()));
	accept();
}
void EncodingDialog::on_cancel_clicked(){
	reject();
}
