#ifndef LATEXCOMPLETER_P_H
#define LATEXCOMPLETER_P_H

#include "mostQtHeaders.h"

#include "codesnippet.h"
#include "latexcompleter_config.h"

typedef CodeSnippet CompletionWord;

//class CompleterInputBinding;
class CompletionListModel : public QAbstractListModel {
	Q_OBJECT

public:
    CompletionListModel(QObject *parent = 0): QAbstractListModel(parent),mostUsedUpdated(false),mCanFetchMore(false),mLastMU(0),mEnvMode(false), mWordCount(0), mCitCount(-1) {}

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role)const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

	const QList<CompletionWord> & getWords(){return words;}
	const QSet<QChar>& getAcceptedChars(){return acceptedChars;}
	bool isNextCharPossible(const QChar &c); //does this character lead to a new possible word
	void filterList(const QString &word,int mostUsed=-1,bool fetchMore=false);
    void setEnvironMode(bool mode);
	void setBaseWords(const QSet<QString> &newwords,CompletionType completionType);
	void setBaseWords(const QList<CompletionWord> &newwords, CompletionType completionType);
    void setBaseWords(const QSet<QString> &baseCommands,const QSet<QString> &newwords, CompletionType completionType);
	void setAbbrevWords(const QList<CompletionWord> &newwords);
    void setCitationWords(const QList<CompletionWord> &newwords);
	void incUsage(const QModelIndex &index);
	void setConfig(LatexCompleterConfig* newConfig);
	virtual bool canFetchMore(const QModelIndex &parent) const;
	void fetchMore(const QModelIndex &parent);
	CompletionWord getLastWord();
private:
	friend class LatexCompleter; //TODO: make this unnecessary
	QList<CompletionWord> words;
	QString curWord;

	QList<CompletionWord> baselist;
    QList<CompletionWord> wordsText, wordsCommands,wordsAbbrev,wordsCitations,wordsCitationCommands;
	QSet<QChar> acceptedChars;
	int mostUsedUpdated;

	bool mCanFetchMore;
	QString mLastWord;
	int mLastMU;
	CompletionWord mLastWordInList;

    bool mEnvMode;

    int mWordCount,mCitCount;

    QList<CompletionWord>::iterator it;

	static LatexCompleterConfig* config;
};

#endif // LATEXCOMPLETER_P_H
