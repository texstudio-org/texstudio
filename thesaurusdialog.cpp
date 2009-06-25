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
	replaceWrdLe=new QLineEdit("",this);

	//replaceWrdLe->setEnabled(false);
	classlistWidget = new QListWidget(this);
	replacelistWidget = new QListWidget(this);
	replacelistWidget->setSortingEnabled(true);

	replacelistWidget->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
	classlistWidget->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
	searchWrdLe->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
	replaceWrdLe->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);

	QGridLayout *gridLayout=new QGridLayout(this);
	gridLayout->addWidget(searchWrdLe,0,0);
	gridLayout->addWidget(replaceWrdLe,0,1);
	gridLayout->addWidget(replaceBt,0,2,Qt::AlignTop);
	gridLayout->addWidget(classlistWidget,1,0,Qt::AlignTop);
	gridLayout->addWidget(replacelistWidget,1,1,Qt::AlignTop);
	gridLayout->setColumnStretch(0,10);
	gridLayout->setColumnStretch(1,10);
	gridLayout->setRowStretch(1,10);

	QVBoxLayout *verticalLayout=new QVBoxLayout();
	verticalLayout->addWidget(lookupBt,0,Qt::AlignTop);
	verticalLayout->addWidget(startsWithBt,0,Qt::AlignTop);
	verticalLayout->addWidget(containsBt,0,Qt::AlignTop);
	verticalLayout->addWidget(cancelBt,0,Qt::AlignTop);
	verticalLayout->insertStretch(-1,10);

	gridLayout->addItem(verticalLayout,1,2);

	searchWrdLe->setEnabled(false);

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
