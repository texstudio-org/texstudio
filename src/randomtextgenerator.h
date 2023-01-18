#ifndef Header_RandomText_Generator
#define Header_RandomText_Generator

#include "mostQtHeaders.h"
class LatexDocuments;

namespace Ui {
class RandomTextGenerator;
}



class RandomTextGenerator : public QDialog
{
	Q_OBJECT
	Q_DISABLE_COPY(RandomTextGenerator)

public:
	explicit RandomTextGenerator(QWidget *parent = 0, LatexDocuments* documents = 0);
	virtual ~RandomTextGenerator();

protected:
	virtual void changeEvent(QEvent *e);

private:
	Ui::RandomTextGenerator *ui;
	QString chars;
	QStringList words;
	LatexDocuments *documents;

	QString text;
	QTextStream textStream;

	void newWordForText(const QString &w);
	void newWordForStream(const QString &w);

private slots:
	void generateText();
	void resetWords();
};

#endif // RANDOMTEXTGENERATOR_H
