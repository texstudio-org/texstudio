#ifndef Header_RandomText_Generator
#define Header_RandomText_Generator

#include "mostQtHeaders.h"
#include "qdocument.h"

namespace Ui {
class RandomTextGenerator;
}


class RandomTextGenerator : public QDialog
{
	Q_OBJECT
	Q_DISABLE_COPY(RandomTextGenerator)

public:
	explicit RandomTextGenerator(QWidget *parent = 0, const QStringList &textLines = QStringList());
	virtual ~RandomTextGenerator();

protected:
	virtual void changeEvent(QEvent *e);

private:
	Ui::RandomTextGenerator *ui;
	QString chars;
	QList<QString> words;
	QStringList lines;

	QString text;
	QTextStream textStream;

	void newWordForText(const QString &w);
	void newWordForStream(const QString &w);

private slots:
	void generateText();
	void resetWords();
};

#endif // RANDOMTEXTGENERATOR_H
