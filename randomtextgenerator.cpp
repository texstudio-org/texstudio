#include "randomtextgenerator.h"
#include "smallUsefulFunctions.h"
#include "ui_randomtextgenerator.h"
#include <QDateTime>

RandomTextGenerator::RandomTextGenerator(QWidget *parent,const QStringList& textLines):
    QDialog(parent),
    ui(new Ui::RandomTextGenerator),lines(textLines)
{
    ui->setupUi(this);
	connect(ui->generateButton,SIGNAL(clicked()), this, SLOT(generateText()));
}

RandomTextGenerator::~RandomTextGenerator()
{
    delete ui;
}

void RandomTextGenerator::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

int myrand(int max){
	return qrand() % max;
}


void RandomTextGenerator::generateText(){
	//---------------------------reading all words and characters in words-------------------
	if (words.empty()) {
		if (lines.empty()) {
			ui->outputEdit->setText(tr("No data given"));
			return;
		}
		ui->outputEdit->setText(tr("Reading all words\n(This will take a while but only on the first generation)"));
		QApplication::processEvents();
		words.clear();
		chars.clear();
		foreach (const QString& line, lines) {
			int index=0;
			int wordStartIndex=0;
			QString outWord;
			while (nextTextWord(line,index,outWord,wordStartIndex)) {
				outWord=outWord.toUpper();
				words << outWord;
				chars += outWord+" ";
			}
		}
		lines.clear();
		if (words.empty()) {
			ui->outputEdit->setText(tr("The current document contains no words, but we need some phrases as a base to create the random text from"));
			return;
		}
	}
	
	
	//----------------------------------generating ---------------------------------------
	//like Shannon in "A Mathematical Theory of Communication" (1949)
	
	int order = -1;
	bool usewords=true;
	int length=ui->lengthSpinBox->value();
	if (ui->wordOrder1RadioButton->isChecked()) order=1;
	else if (ui->wordOrder2RadioButton->isChecked()) order=2;
	else if (ui->wordOrder3RadioButton->isChecked()) order=3;
	else if (ui->wordOrderXRadioButton->isChecked()) order=ui->wordOrderSpinBox->value();
	else {
		usewords=false;
		if (ui->characterOrder1RadioButton->isChecked()) order=1;
		else if (ui->characterOrder2RadioButton->isChecked()) order=2;
		else if (ui->characterOrder3RadioButton->isChecked()) order=3;
		else if (ui->characterOrderXRadioButton->isChecked()) order=ui->characterOrderSpinBox->value();		
	}
	if (order<=0) {
		ui->outputEdit->setText(tr("You didn't select an order!"));
		return;
	}
	ui->outputEdit->setText(tr("Generating random text..."));
	QApplication::processEvents();
	
	QString text;
	qsrand(QDateTime::currentDateTime().toTime_t()); //TODO: milliseconds
	if (usewords) {
		//----------generate with words ------------------
		QString text;
		QStringList last = QStringList() << words[myrand(words.size())];
		QList<int> possibleMatches;
		for (int n=1;n<length;n++){
			if (last.size()==order) last.removeFirst();
			possibleMatches.clear();
			//search possible extensions and choose one of them at random
			for (int i=0;i<words.size()-last.size();i++){
				bool found=true;
				for (int j=0;j<last.size();j++)
					if (words[i+j]!=last[j]) {
						found=false;
						break;
					}
				if (found) possibleMatches<<(i+last.size());
			}
			if (possibleMatches.empty()) {
				text+="\n\n"+tr("Couldn't find possible extension word");
				ui->outputEdit->setText(text);
				return;
			}
			last << words[possibleMatches[myrand(possibleMatches.size())]];
			text+=last.last()+" ";
			ui->outputEdit->setText(tr("Generating random text...")+"\n\n"+text);
			QApplication::processEvents();
		}
		ui->outputEdit->setText(text);
	} else {
		//----------generate with characters--------------
		QString text;
		QString last = chars.at(myrand(chars.size()));
		for (int n=1;n<length;n++){
			if (last.size()==order) last.remove(0,1);
			int position=myrand(chars.size());
			//choose a random position and search next possible extension
			//(faster than the method used by words, but statistically not so sound, 
			//should work best with infinite large texts)
			int foundPos=-1;
			for (int i=position;i<chars.size()-last.size();i++) 
				if (chars.mid(i,last.size())==last) {
					foundPos=i+last.size();
					break;
				}
			if (foundPos==-1) {
				for (int i=0;i<position-last.size();i++) 
					if (chars.mid(i,last.size())==last) {
						foundPos=i+last.size();
						break;
					}
				if (foundPos==-1) {
					text+="\n\n"+tr("Couldn't find possible extension word");
					ui->outputEdit->setText(text);
					return;
				}
			}
			const QChar& c=chars.at(foundPos);
			last+=c;
			text+=c;
			ui->outputEdit->setText(tr("Generating random text...")+"\n\n"+text);
			QApplication::processEvents();
		}
		ui->outputEdit->setText(text);	
	}
}

	
