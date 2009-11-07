#include "findGlobalDialog.h"
#include "ui_findGlobalDialog.h"

findGlobalDialog::findGlobalDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::findGlobalDialog)
{
    m_ui->setupUi(this);
}

findGlobalDialog::~findGlobalDialog()
{
    delete m_ui;
}

void findGlobalDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void findGlobalDialog::setSearchWord(QString word){
	m_ui->lineEditSearchWord->setText(word);
}

QString findGlobalDialog::getSearchWord(){
	return m_ui->lineEditSearchWord->text();
}

bool findGlobalDialog::isWords(){
	return m_ui->cbWords->isChecked();
}
bool findGlobalDialog::isCase(){
	return m_ui->cbCase->isChecked();
}
bool findGlobalDialog::isRegExp(){
	return m_ui->cbRegExp->isChecked();
}
int findGlobalDialog::getSearchScope(){
	return m_ui->comboBoxScope->currentIndex();
}

void findGlobalDialog::on_cbWords_toggled(bool state){
	if(state) m_ui->cbRegExp->setChecked(false);
}

void findGlobalDialog::on_cbRegExp_toggled(bool state){
	if(state) m_ui->cbWords->setChecked(false);
}
