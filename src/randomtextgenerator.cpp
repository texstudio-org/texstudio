#include "randomtextgenerator.h"
#include "latexparser/latex2text.h"
#include "utilsUI.h"
#include "ui_randomtextgenerator.h"
#include "utilsUI.h"
#include "latexdocument.h"
#include "qdocument.h"


RandomTextGenerator::RandomTextGenerator(QWidget *parent, LatexDocuments* documents):
	QDialog(parent),
    ui(new Ui::RandomTextGenerator), documents(documents)
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
		if (documents->documents.empty()) {
			ui->outputEdit->setText(tr("No data given"));
			return;
		}
		ui->outputEdit->setText(tr("Reading all words\n(This will take a while but only on the first generation)"));
		QApplication::processEvents();
		words.clear();
		chars.clear();
		bool upcase = ui->upperCaseCheckBox->isChecked();
		bool punctation = ui->punctationCheckBox->isChecked();
		static const QString Punctation = ".,:;!?";
		foreach (QDocument* doc, documents->documents) {
			QList<LineInfo> inlines;
			for (int i=0;i<doc->lineCount();i++){

				if (ui->latexInput->isChecked()) {
					inlines << LineInfo(doc->line(i).handle());
				} else {
					QString line = doc->line(i).text();
#if (QT_VERSION>=QT_VERSION_CHECK(5,14,0))
					QStringList newl = line.split(punctation ? QRegularExpression("\\s+") : QRegularExpression("[-~!@#$%^&*()_+{}|:\"\\<>?,./;\[= \t'+]"), Qt::SkipEmptyParts);
#else
					QStringList newl = line.split(punctation ? QRegExp("\\s+") : QRegExp("[~!@#$%^&*()_+{}|:\"\\<>?,./;[-= \t'+]"), QString::SkipEmptyParts);
#endif
					words << newl;
				}
			}
			if (ui->latexInput->isChecked()) {
				QList<TokenizedBlock> blocks = tokenizeWords(LatexParser::getInstancePtr(), inlines);
				foreach (const TokenizedBlock& tb, blocks)
					words << tb.words;
			}
		}
		if (ui->latexInput->isChecked() && !punctation) {
			for (int i = 0; i < words.size(); i++)
				foreach (QChar c, Punctation)
					words[i] = words[i].replace(c, QString(""));
		}
		if (upcase) for (int i = 0; i < words.size(); i++) words[i] = words[i].toUpper();
		chars = words.join(" ");
		if (words.empty()) {
			ui->outputEdit->setText(tr("The current document contains no words, but we need some phrases as a base to create the random text from"));
			return;
		}
	}

        //----------------------------------generating
        //---------------------------------------
        // lorem ipsum
        if (ui->loremIpsumRadioButton->isChecked()) {
                generateLoremIpsum();
                return;
        }

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

    std::srand(QDateTime::currentDateTime().toSecsSinceEpoch()); //TODO: milliseconds

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

void RandomTextGenerator::generateLoremIpsum() {
        const static QString loremIpsum(
            "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam "
            "nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam "
            "erat, sed diam voluptua. At vero eos et accusam et justo duo "
            "dolores et ea rebum. Stet clita kasd gubergren, no sea takimata "
            "sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit "
            "amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor "
            "invidunt ut labore et dolore magna aliquyam erat, sed diam "
            "voluptua. At vero eos et accusam et justo duo dolores et ea "
            "rebum. Stet clita kasd gubergren, no sea takimata sanctus est "
            "Lorem ipsum dolor sit amet. ");

        QString text;

        int length = ui->lengthSpinBox->value();

        while (length > 100) {
                text += loremIpsum;
                length -= 100;
        }

        int nthSpaceIndex = 0;

        for (int spaceCounter = 0; spaceCounter < length; spaceCounter++) {
                nthSpaceIndex = loremIpsum.indexOf(' ', nthSpaceIndex + 1);
        }

        text += loremIpsum.left(nthSpaceIndex);

        ui->outputEdit->setText(text.trimmed());
}
