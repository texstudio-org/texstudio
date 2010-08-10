#include "bibtexdialog.h"
#include "ui_bibtexdialog.h"

QList<BibTeXType> BibTeXDialog::types;

void BibTeXDialog::needTypes(){
	if (!types.empty()) return;
	types << BibTeXType(tr("Article in &Journal"), "@Article",
						QStringList() << "author" << "title" << "journal" << "year",
						QStringList() << "key" << "volume" << "number" << "pages" << "month" << "note" << "annote");
	types << BibTeXType(tr("Article in Conference &Proceedings"), "@InProceedings",
						QStringList() <<"author" << "title" << "booktitle",
						QStringList() <<"crossref" << "key" << "pages" << "year" << "editor" <<"volume" << "number" << "series" << "address" << "month" << "organization" << "publisher" << "note" << "annote");
	types << BibTeXType(tr("Article in a &Collection"), "@InCollection",
						QStringList() << "author" << "title" << "booktitle",
						QStringList() <<"crossref" << "key" << "pages" << "publisher" << "year" <<  "editor" << "volume" << "number" << "series" << "type" << "chapter" << "address" << "edition" << "month" << "note" << "annote");
	types << BibTeXType(tr("Chapter or &Pages in a Book"), "@InBook",
						QStringList() << "author/editor" << "title" << "chapter" << "publisher" << "year",
						QStringList() << "key" << "volume" << "number" << "series" << "type" << "address" << "edition" << "month" << "pages" << "note" <<  "annote");
	types << BibTeXType(tr("Conference Pr&oceedings"), "@Proceedings",
						QStringList() << "title" << "year",
						QStringList() << "key" << "editor" << "volume" << "number" <<
 "series" << "address" << "month" << "organization" << "publisher" << "note" <<
 "annote");
	types << BibTeXType(tr("&Book"), "@Book",
						QStringList() << "author/editor" << "title" << "publisher" << "year",
						QStringList() <<  "key" << "volume" << "number" << "series" << "address" <<
 "edition" << "month" << "note" << "annote");
	types << BibTeXType(tr("Book&let"), "@Booklet",
						QStringList() << "title",
						QStringList() << "key" << "author" << "howpublished" << "address" << "month" << "year" << "note" << "annote");
	types << BibTeXType(tr("PhD. &Thesis"), "@PhdThesis",
						QStringList() << "author" << "title" << "school" << "year",
						QStringList() << "key" << "type" << "address" << "month" << "note" <<
 "annote");
	types << BibTeXType(tr("&Master's Thesis"), "@MastersThesis",
						QStringList() << "author" << "title" << "school" << "year",
						QStringList() <<  "key" << "type" << "address" << "month" <<  "note" <<
 "annote");
	types << BibTeXType(tr("Technical &Report"), "@TechReport",
						   QStringList() << "author" << "title" << "institution" << "year",
						   QStringList() <<  "key" << "type" << "number" << "address" << "month" <<
 "note" << "annote");
	types << BibTeXType(tr("Technical Ma&nual"), "@Manual",
						QStringList() << "title",
						QStringList() << "key" << "author" << "organization" << "address" << "edition" << "month" << "year" << "note" << "annote");
 
	types << BibTeXType(tr("&Unpublished"), "@Unpublished",
						QStringList() << "author" << "title" << "note",
						QStringList() << "key" << "month" << "year" << "annote");
	types << BibTeXType(tr("Miscellan&eous"), "@Misc",
						   QStringList(),
						   QStringList() << "key" << "author" << "title" << "howpublished" << "month" << "year" << "note" << "annote");
}


BibTeXDialog::BibTeXDialog(QWidget *parent, const QStringList& fileList, int curFile, const QString& id) :
    QDialog(parent),
    m_ui(new Ui::BibTeXDialog)
{
    m_ui->setupUi(this);
	m_ui->fileList->addItem(tr("<new file>"));
	foreach (const QString& s, fileList)
		m_ui->fileList->addItem(s);
	m_ui->fileList->setCurrentRow(curFile+1);
	needTypes();
	if (!id.isEmpty()){
		m_ui->fieldTable->setRowCount(1);
		QTableWidgetItem* item=new QTableWidgetItem("ID");
		QFont f=QApplication::font();
		f.setBold(true);
		item->setFont(f);
		m_ui->fieldTable->setItem(0,0,item);
		m_ui->fieldTable->setItem(0,1,new QTableWidgetItem(id));
	}
	foreach (const BibTeXType& bt, types){
	    QString zw=bt.description;
	    zw.remove("&");
	    m_ui->typeList->addItem(zw);
	}
	connect(m_ui->typeList,SIGNAL(itemSelectionChanged()),this,SLOT(typeSelectionChanged()));
}

BibTeXDialog::~BibTeXDialog()
{
    delete m_ui;
}

//generate an entry in the bibtex format out of the given parameters
QString BibTeXDialog::textToInsert(const BibTeXType& entry, bool keepOptionalFields, const QMap<QString,QString>& fields){
	QString result=entry.name+"{"+fields.value("ID","%<ID%>")+",\n";
	QMap<QString,QString> remainingFields=fields;
	remainingFields.remove("ID");
	foreach (const QString &s, entry.mandatoryFields){
		if (!s.contains("/")) {
			result+=s+ " = {"+remainingFields.value(s,"%<"+s+"%>")+"},\n";
			remainingFields.remove(s);;
		} else {
			//split alternative values and use first set value, if non is set use all prepended with ALT like in texmaker
			QStringList sl=s.split("/");
			bool inserted=false;
			foreach (const QString& t, sl)
				if (remainingFields.contains(t)) {
					result+=t+ " = {"+remainingFields.value(t,"%<"+t+"%>")+"},\n";
					inserted=true;
					remainingFields.remove(t);
					break;
				}
			if (!inserted)
				foreach (const QString& t, sl)
					result+="ALT"+t+ " = {%<"+t+"%>},\n";
		}
		
	}
	
	foreach (const QString &s, entry.optionalFields){
		QMap<QString,QString>::iterator it=remainingFields.find(s);
		if (it!=remainingFields.end()) {
			result+=s+ " = {"+remainingFields.value(s,"%<"+s+"%>")+"},\n";
			remainingFields.erase(it);
		} else if (keepOptionalFields)
			result+="OPT"+s+ " = {%<"+s+"%>},\n";
	}
	for (QMap<QString,QString>::const_iterator it=remainingFields.constBegin();it!=remainingFields.constEnd();++it)
		result+=it.key()+" = {"+it.value()+"},\n";
	result+="}\n";
	return result;
}

QString BibTeXDialog::textToInsert(const QString& entryName){
	needTypes();
	foreach (const BibTeXType& t, types)
		if (t.name==entryName) 
			return textToInsert(t,true,QMap<QString,QString>());
	return "";
}


QList<BibTeXType> BibTeXDialog::getPossibleBibTeXTypes(){
	types.clear(); //remove old types to allow translation change without restart
	needTypes();
	return types;
}

void BibTeXDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void BibTeXDialog::accept(){
	resultString="";
	if (m_ui->typeList->currentRow()<0 || m_ui->typeList->currentRow()>=types.count()) 
		return;
	QMap<QString, QString> curFields;
	for (int i=0;i<m_ui->fieldTable->rowCount();i++){
		if (!m_ui->fieldTable->item(i,0) || !m_ui->fieldTable->item(i,1)) 
			continue;
		QString k=m_ui->fieldTable->item(i,0)->text();
		if (k.contains("/")) k=k.split("/").first();
		QString v=m_ui->fieldTable->item(i,1)->text();
		if (v!="") curFields.insert(k,v);
	}
	resultString=textToInsert(types.at(m_ui->typeList->currentRow()),m_ui->optFieldCheckBox->isChecked(),curFields);
	resultFileId=m_ui->fileList->currentRow()-1;
	QDialog::accept();
}
void BibTeXDialog::typeSelectionChanged(){
	if (m_ui->typeList->currentRow()<0 || m_ui->typeList->currentRow()>=types.count()) 
		return;
	//save current values
	QMap<QString, QString> curFields;
	for (int i=0;i<m_ui->fieldTable->rowCount();i++){
		if (!m_ui->fieldTable->item(i,0) || !m_ui->fieldTable->item(i,1)) 
			continue;
		curFields.insert(m_ui->fieldTable->item(i,0)->text(),m_ui->fieldTable->item(i,1)->text());
	}
	//update
	m_ui->fieldTable->clearContents();
	const BibTeXType &bt = types.at(m_ui->typeList->currentRow());
	m_ui->fieldTable->setRowCount(bt.mandatoryFields.count()+bt.optionalFields.count()+10);
	QFont f=QApplication::font(); f.setBold(true);

	//mandatory fields
	int row=0;
	QStringList fields=bt.mandatoryFields;
	fields.prepend("ID");
	for (int i=0;i<fields.count();i++,row++) {
		QTableWidgetItem* item=new QTableWidgetItem(fields[i]);
		item->setFont(f);
		m_ui->fieldTable->setItem(row, 0, item);
		m_ui->fieldTable->setItem(row, 1, new QTableWidgetItem(curFields.value(fields[i],"")));						
	}
	
	//optional fields
	for (int i=0;i<bt.optionalFields	.count();i++,row++) {
		QTableWidgetItem *item=new QTableWidgetItem(bt.optionalFields[i]);
		item->setForeground(Qt::red);
		m_ui->fieldTable->setItem(row, 0, item);
		m_ui->fieldTable->setItem(row, 1, new QTableWidgetItem(curFields.value(bt.optionalFields[i],"")));						
	}
	m_ui->fieldTable->setCurrentCell(0,1);
	m_ui->fieldTable->resizeRowsToContents();
}
