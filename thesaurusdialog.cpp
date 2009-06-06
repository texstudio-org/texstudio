#include "thesaurusdialog.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>

thesaurusdialog::thesaurusdialog(QWidget *parent)
	:QDialog(parent)
{
	replaceBt=new QPushButton(tr("replace"),this);
	lookupBt=new QPushButton(tr("lookup"),this);
	cancelBt=new QPushButton(tr("cancel"),this);
	searchWrdLe=new QLineEdit("",this);
	searchWrdLe->setEnabled(false);
	replaceWrdLe=new QLineEdit("",this);
	replaceWrdLe->setEnabled(false);
	classlistWidget = new QListWidget(this);
	replacelistWidget = new QListWidget(this);
	QGridLayout *gridLayout=new QGridLayout(this);
	gridLayout->addWidget(searchWrdLe,0,0,1,1,Qt::AlignLeft);
	gridLayout->addWidget(replaceWrdLe,0,1,1,1,Qt::AlignLeft);
	gridLayout->addWidget(replaceBt,0,2,1,1,Qt::AlignLeft);
	gridLayout->addWidget(lookupBt,1,2,1,1,Qt::AlignLeft);
	gridLayout->addWidget(cancelBt,2,2,1,1,Qt::AlignLeft);
	gridLayout->addWidget(classlistWidget,1,0,5,1,Qt::AlignLeft);
	gridLayout->addWidget(replacelistWidget,1,1,5,1,Qt::AlignLeft);

	setLayout(gridLayout);

	setWindowTitle(tr("Thesaurus"));

	connect(replaceBt, SIGNAL(clicked()), this, SLOT(accept()));
	connect(lookupBt, SIGNAL(clicked()), this, SLOT(lookupClicked()));
	connect(cancelBt, SIGNAL(clicked()), this, SLOT(reject()));
	connect(classlistWidget, SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(classClicked(QListWidgetItem*)));
	connect(replacelistWidget, SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(wordClicked(QListWidgetItem*)));

	//initialize Thesaurus empty
	Thesaurus.clear();
}

void thesaurusdialog::setSearchWord(const QString word)
{
	searchWrdLe->setText(word);
	replaceWrdLe->setText("");
	//clear Lists
	classlistWidget->clear();
	replacelistWidget->clear();
	// do all the other calculations
	QList<QStringList> result=Thesaurus.values(word.toLower());
	// set word classes
	QString first;

	foreach(QStringList elem,result){
		first=elem[0];
		classlistWidget->addItem(first);
	}
	classlistWidget->setCurrentRow(0);
	classClicked(classlistWidget->item(0));
}

QString thesaurusdialog::getReplaceWord()
{
	return replaceWrdLe->text();
}

void thesaurusdialog::readDatabase(const QString filename)
{
	if (!QFile::exists(filename)) return;

	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::warning(this,tr("Error"), tr("You do not have read permission to this file."));
		return;
	}

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

void thesaurusdialog::classClicked(QListWidgetItem *item)
{
	if(!item) return;
	int row=classlistWidget->row(item);
	QString word=searchWrdLe->text();
	QList<QStringList> result=Thesaurus.values(word.toLower());
	replacelistWidget->clear();
	replacelistWidget->addItems(result[row]);
}

void thesaurusdialog::wordClicked(QListWidgetItem *item)
{
	replaceWrdLe->setText(item->text());
}

void thesaurusdialog::lookupClicked()
{
	QString word=replaceWrdLe->text();
	word.replace(QRegExp(" \\(.*"), "");
	setSearchWord(word);
}
