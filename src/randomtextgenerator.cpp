#include "randomtextgenerator.h"
#include "latexparser/latexreader.h"
#include "utilsUI.h"
#include "ui_randomtextgenerator.h"
#include "utilsUI.h"

RandomTextGenerator::RandomTextGenerator(QWidget *parent, const QStringList &textLines):
	QDialog(parent),
	ui(new Ui::RandomTextGenerator), lines(textLines)
{
	ui->setupUi(this);
	UtilsUi::resizeInFontHeight(this, 41, 39);

	connect(ui->generateButton, SIGNAL(clicked()), this, SLOT(generateText()));
	connect(ui->latexInput, SIGNAL(toggled(bool)), SLOT(resetWords()));
	connect(ui->punctationCheckBox, SIGNAL(toggled(bool)), SLOT(resetWords()));
	connect(ui->upperCaseCheckBox, SIGNAL(toggled(bool)), SLOT(resetWords()));
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

int myrand(int max)
{
    return std::rand() % max;
}


void RandomTextGenerator::generateText()
{
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
		bool upcase = ui->upperCaseCheckBox->isChecked();
		bool punctation = ui->punctationCheckBox->isChecked();
		foreach (const QString &line, lines) {
			QString outWord;
			static const QString Punctation = ".,:;!?";

			if (ui->latexInput->isChecked()) {
				int index = 0;
				int wordStartIndex = 0;
				int lastIndex = 0;
				LatexReader lr(line);
				while (lr.nextTextWord()) {
					if (upcase) outWord = outWord.toUpper();
					if (punctation) {
						for (int i = lastIndex; i < wordStartIndex; i++)
							if (Punctation.indexOf(line[i]) >= 0) {
								outWord += line[i];
							}
					}
					words << outWord;
					chars += outWord + " ";
					lastIndex = index;
				}
			} else {
				QStringList newl = line.split(punctation ? QRegExp("\\s+") : QRegExp("[~!@#$%^&*()_+{}|:\"\\<>?,./;[-= \t'+]"), QString::SkipEmptyParts);
				if (upcase) for (int i = 0; i < newl.size(); i++) newl[i] = newl[i].toUpper();
				words << newl;
			}
		}
		//lines.clear();
		if (words.empty()) {
			ui->outputEdit->setText(tr("The current document contains no words, but we need some phrases as a base to create the random text from"));
			return;
		}
	}


	//----------------------------------generating ---------------------------------------
	//like Shannon in "A Mathematical Theory of Communication" (1949)

	int order = -1;
	bool usewords = true;
	int length = ui->lengthSpinBox->value();
	if (ui->wordOrder1RadioButton->isChecked()) order = 1;
	else if (ui->wordOrder2RadioButton->isChecked()) order = 2;
	else if (ui->wordOrder3RadioButton->isChecked()) order = 3;
	else if (ui->wordOrderXRadioButton->isChecked()) order = ui->wordOrderSpinBox->value();
	else {
		usewords = false;
		if (ui->characterOrder1RadioButton->isChecked()) order = 1;
		else if (ui->characterOrder2RadioButton->isChecked()) order = 2;
		else if (ui->characterOrder3RadioButton->isChecked()) order = 3;
		else if (ui->characterOrderXRadioButton->isChecked()) order = ui->characterOrderSpinBox->value();
	}
	if (order <= 0) {
		ui->outputEdit->setText(tr("You didn't select an order!"));
		return;
	}
	ui->outputEdit->setText(tr("Generating random text..."));
	QApplication::processEvents();

    std::srand(QDateTime::currentDateTime().toTime_t()); //TODO: milliseconds

	text = "";
	QFile f;
	void (RandomTextGenerator::*newWordFound)(const QString &) = &RandomTextGenerator::newWordForText;
	if (ui->exportCheckBox->isChecked()) {
		newWordFound = &RandomTextGenerator::newWordForStream;
		f.setFileName(ui->exportFileNameLineEdit->text());
		if (!f.open(QFile::WriteOnly)) {
			UtilsUi::txsWarning(tr("Couldn't create file %1").arg(ui->exportFileNameLineEdit->text()));
			return;
		}
		textStream.setDevice(&f);
		ui->outputEdit->setText(tr("Generating random text..."));
	}

	if (usewords) {
		//----------generate with words ------------------
		QList<int> wordsIds;
		QHash<QString, int> wordToId;
		QHash<int, QString> idToWord;
		QMultiHash<int, int> startingIndices;
		int totalIds = 0;
		for (int i = 0; i < words.size(); i++) {
			int id = wordToId.value(words[i], -1);
			if (id == -1) {
				totalIds++;
				id = totalIds;
				wordToId.insert(words[i], totalIds);
				idToWord.insert(totalIds, words[i]);
			}
            startingIndices.insert(id, i);
			wordsIds << id;
		}
		QString text;
		QList<int> last = QList<int>() << wordToId.value(words[myrand(words.size())]);
		QList<int> possibleMatches;
		for (int n = 1; n < length; n++) {
			if (last.size() == order) last.removeFirst();
			possibleMatches.clear();
			if (last.size() == 0)
				last << wordsIds[myrand(wordsIds.size())];
			else {
				//search possible extensions and choose one of them at random
				QMultiHash<int, int>::iterator it = startingIndices.find(last.first());
				while (it != startingIndices.end() && it.key() == last.first()) {
					if (it.value() + last.size() >= wordsIds.size()) {
						++it;
						continue;
					}
					bool found = true;
					for (int j = 1; j < last.size(); j++)
						if (wordsIds[it.value() + j] != last[j]) {
							found = false;
							break;
						}
					if (found) possibleMatches << (it.value() + last.size());
					++it;
				}
				if (possibleMatches.empty())
					last = QList<int>() << wordsIds[myrand(wordsIds.size())];
				else
					last << wordsIds[possibleMatches[myrand(possibleMatches.size())]];
			}
			(this->*newWordFound)(idToWord.value(last.last()) + (myrand(15) == 0 ? "\n" : " "));
		}
	} else {
		//----------generate with characters--------------
		QString text;
		QString last = chars.at(myrand(chars.size()));
		for (int n = 1; n < length; n++) {
			if (last.size() == order) last.remove(0, 1);
			int position = myrand(chars.size());
			//choose a random position and search next possible extension
			//(faster than the method used by words, but statistically not so sound,
			//should work best with infinite large texts)
			int foundPos = -1;
			for (int i = position; i < chars.size() - last.size(); i++)
				if (chars.mid(i, last.size()) == last) {
					foundPos = i + last.size();
					break;
				}
			if (foundPos == -1) {
				for (int i = 0; i < position - last.size(); i++)
					if (chars.mid(i, last.size()) == last) {
						foundPos = i + last.size();
						break;
					}
				if (foundPos == -1) {
					last = "";
					foundPos = myrand(chars.size());
				}
			}
			const QChar &c = chars.at(foundPos);
			last += c;
			(this->*newWordFound)(c);
		}
	}

	if (ui->exportCheckBox->isChecked()) {
		ui->outputEdit->setText(tr("Finished generation"));
		textStream.setDevice(nullptr);
	} else {
		ui->outputEdit->setText(text);
	}
}

void RandomTextGenerator::resetWords()
{
	words.clear();
}

void RandomTextGenerator::newWordForText(const QString &w)
{
	text += w;
	ui->outputEdit->setText(tr("Generating random text...") + "\n\n" + text);
	QApplication::processEvents();
}

void RandomTextGenerator::newWordForStream(const QString &w)
{
	textStream << w;
}

