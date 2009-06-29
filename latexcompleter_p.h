#ifndef LATEXCOMPLETER_P_H
#define LATEXCOMPLETER_P_H

#include "codesnippet.h"

#include <QAbstractListModel>
#include <QChar>
#include <QList>
#include <QSet>

typedef CodeSnippet CompletionWord;

//class CompleterInputBinding;
class CompletionListModel : public QAbstractListModel {
	Q_OBJECT

public:
	CompletionListModel(QObject *parent = 0): QAbstractListModel(parent) {}

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

	const QList<CompletionWord> & getWords(){return words;}
	const QSet<QChar>& getAcceptedChars(){return acceptedChars;}
	bool isNextCharPossible(const QChar &c); //does this character lead to a new possible word
	void filterList(const QString &word);
	void setBaseWords(const QStringList &newwords, bool normalTextList);
private:
	friend class LatexCompleter; //TODO: make this unnecessary
	QList<CompletionWord> words;
	QString curWord;

	QList<CompletionWord> baselist;
	QList<CompletionWord> wordsText, wordsCommands;
	QSet<QChar> acceptedChars;
};

#endif // LATEXCOMPLETER_P_H
