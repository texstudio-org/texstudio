#ifndef RANDOMTEXTGENERATOR_H
#define RANDOMTEXTGENERATOR_H

#include "mostQtHeaders.h"
#include "qdocument.h"

namespace Ui {
    class RandomTextGenerator;
}


class RandomTextGenerator : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(RandomTextGenerator)
public:
    explicit RandomTextGenerator(QWidget *parent = 0, const QStringList& textLines=QStringList());
    virtual ~RandomTextGenerator();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::RandomTextGenerator *ui;
	QString chars;
	QList<QString> words;
	QStringList lines;
	
private slots:
	void generateText();
};

#endif // RANDOMTEXTGENERATOR_H
