#include "thesaurusdialog.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>

ThesaurusDialog::ThesaurusDialog(QWidget *parent)
	:QDialog(parent)
{
	replaceBt=new QPushButton(tr("replace"),this);
	lookupBt=new QPushButton(tr("lookup"),this);
	startsWithBt=new QPushButton(tr("starts with ..."),this);
	containsBt=new QPushButton(tr("contains ..."),this);
	cancelBt=new QPushButton(tr("cancel"),this);
	searchWrdLe=new QLineEdit("",this);
	searchWrdLe->setEnabled(false);
	replaceWrdLe=new QLineEdit("",this);
	replaceWrdLe->setEnabled(true);
	classlistWidget = new QListWidget(this);
	replacelistWidget = new QListWidget(this);
	replacelistWidget->setSortingEnabled(true);

	QGridLayout *gridLayout=new QGridLayout(this);
	gridLayout->addWidget(searchWrdLe,0,0,1,1,Qt::AlignLeft);
	gridLayout->addWidget(replaceWrdLe,0,1,1,1,Qt::AlignLeft);
	gridLayout->addWidget(replaceBt,0,2,1,1,Qt::AlignLeft);
	gridLayout->addWidget(lookupBt,1,2,1,1,Qt::AlignLeft);
	gridLayout->addWidget(startsWithBt,2,2,1,1,Qt::AlignLeft);
	gridLayout->addWidget(containsBt,3,2,1,1,Qt::AlignLeft);
	gridLayout->addWidget(cancelBt,4,2,1,1,Qt::AlignLeft);
	gridLayout->addWidget(classlistWidget,1,0,5,1,Qt::AlignLeft);
	gridLayout->addWidget(replacelistWidget,1,1,5,1,Qt::AlignLeft);

	setLayout(gridLayout);

	setWindowTitle(tr("Thesaurus"));

	connect(replaceBt, SIGNAL(clicked()), this, SLOT(accept()));
	connect(lookupBt, SIGNAL(clicked()), this, SLOT(lookupClicked()));
	connect(startsWithBt, SIGNAL(clicked()), this, SLOT(startsWithClicked()));
	connect(containsBt, SIGNAL(clicked()), this, SLOT(containsClicked()));
	connect(cancelBt, SIGNAL(clicked()), this, SLOT(reject()));
	connect(classlistWidget, SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(classClicked(QListWidgetItem*)));
	connect(replacelistWidget, SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(wordClicked(QListWidgetItem*)));

	//initialize Thesaurus empty
	Thesaurus.clear();
}

void ThesaurusDialog::setSearchWord(const QString word)
{
	searchWrdLe->setText(word);
	replaceWrdLe->setText(word);
	//clear Lists
	classlistWidget->clear();
	replacelistWidget->clear();
	// do all the other calculations
	QList<QStringList> result=Thesaurus.values(word.toLower());
	// set word classes
	QString first;
	if(result.count()>0) classlistWidget->addItem(tr("<all>"));
	foreach(QStringList elem,result){
		first=elem[0];
		classlistWidget->addItem(first);
	}
	classlistWidget->setCurrentRow(0);
	classClicked(classlistWidget->item(0));
}

QString ThesaurusDialog::getReplaceWord()
{
	QString word=replaceWrdLe->text();
	word.replace(QRegExp(" \\(.*"), "");
	return word;
}

void ThesaurusDialog::readDatabase(const QString filename)
{
	if (!QFile::exists(filename)) return;

	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::warning(this,tr("Error"), tr("You do not have read permission to this file."));
		thesaurusFileName="";
		return;
	}

	if (thesaurusFileName==filename) return;
	thesaurusFileName=filename;
	
	Thesaurus.clear();
	// read in file
	QTextStream stream(&file);
	QString line;
	QString key;
	QStringList parts;
	line = stream.readLine();
	stream.setCodec(qPrintable(line));
	do {
		line = stream.readLine();
		parts=line.split("|");
		if(parts[0]=="-"){
			parts.removeFirst();
			Thesaurus.insert(key,parts);
		}
		else {
			key=parts[0];
		}
	} while (!line.isNull());
}

void ThesaurusDialog::classClicked(QListWidgetItem *item)
{
	if(!item) return;
	int row=classlistWidget->row(item);
	QString word=searchWrdLe->text();
	QList<QStringList> result=Thesaurus.values(word.toLower());
	replacelistWidget->clear();

	if(row==0){
		foreach(QStringList elem,result){
			replacelistWidget->addItems(elem);
		}
	}else replacelistWidget->addItems(result[row-1]);
}

void ThesaurusDialog::wordClicked(QListWidgetItem *item)
{
	replaceWrdLe->setText(item->text());
}

void ThesaurusDialog::lookupClicked()
{
	QString word=replaceWrdLe->text();
	word.replace(QRegExp(" \\(.*"), "");
	setSearchWord(word);
}

void ThesaurusDialog::containsClicked()
{
	QString word=replaceWrdLe->text();
	word.replace(QRegExp(" \\(.*"), "");
	classlistWidget->clear();
	replacelistWidget->clear();
	QMultiMap<QString, QStringList>::const_iterator i = Thesaurus.constBegin();
	while (i != Thesaurus.constEnd()) {
		if(!replacelistWidget->findItems(i.key(),Qt::MatchExactly).count()&&i.key().contains(word)) replacelistWidget->addItem(i.key());
		++i;
	}
}

void ThesaurusDialog::startsWithClicked()
{
	QString word=replaceWrdLe->text();
	word.replace(QRegExp(" \\(.*"), "");
	classlistWidget->clear();
	replacelistWidget->clear();
	QMultiMap<QString, QStringList>::const_iterator i = Thesaurus.lowerBound(word);
	while (i != Thesaurus.constEnd() && i.key().startsWith(word)) {
		if(!replacelistWidget->findItems(i.key(),Qt::MatchExactly).count()) replacelistWidget->addItem(i.key());
		++i;
	}
}
