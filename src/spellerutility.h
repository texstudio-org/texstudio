/***************************************************************************
 *   copyright       : (C) 2008 by Benito van der Zander                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef Header_Speller_Utility
#define Header_Speller_Utility

#include "mostQtHeaders.h"
#include <QMutex>

#ifdef HUNSPELL_STATIC
#include "hunspell/hunspell.hxx"
#else
#include <hunspell.hxx>
#endif

class SpellerUtility: public QObject {
	Q_OBJECT

public:
	friend class SpellerManager;
    void addToIgnoreList(QString toIgnore, bool intoIgnFile=true);
	void removeFromIgnoreList(QString toIgnore);
	QStringListModel* ignoreListModel();

	bool check(QString word);
	QStringList suggest(QString word);

	QString name() {return mName;}
	QString getCurrentDic() {return currentDic;}

	static int spellcheckErrorFormat;
    static bool inlineSpellChecking,hideNonTextSpellingErrors;

signals:
	void aboutToDelete();
	void dictionaryLoaded();
	void ignoredWordAdded(const QString& newlyIgnoredWord);

private:
	SpellerUtility(QString name);
	~SpellerUtility();
	bool loadDictionary(QString dic, QString ignoreFilePrefix);
	void saveIgnoreList();
	void unload();

	QString mName;
	QString mLastError;
	QString currentDic, ignoreListFileName, spell_encoding;
	Hunspell * pChecker;
	QTextCodec *spellCodec;
	QStringList ignoredWordList;
	QSet<QString> ignoredWords;
	QStringListModel ignoredWordsModel;
    QMutex mSpellerMutex;
};


class SpellerManager: public QObject {
	Q_OBJECT

public:
	SpellerManager();
	~SpellerManager();

	static bool isOxtDictionary(const QString &fileName);
	static bool importDictionary(const QString &fileName, const QString &targetDir);

	void setIgnoreFilePrefix(const QString &ignoreFilePrefix);
	QStringList dictPaths() {return m_dictPaths;}
	void setDictPaths(const QStringList &dictPaths);
	void scanForDictionaries(const QString &path, bool scansubdirs=true);

	QStringList availableDicts();

	bool hasSpeller(const QString &name);
	bool hasSimilarSpeller(const QString &name, QString &bestName);
	SpellerUtility *getSpeller(QString name);

	QString defaultSpellerName();
	bool setDefaultSpeller(const QString &name);
	void unloadAll();

	static QString prettyName(const QString &name);

signals:
	void dictPathChanged();
	void defaultSpellerChanged();

private:
	QStringList m_dictPaths;
	QString ignoreFilePrefix;
	QHash<QString, SpellerUtility *> dicts;
	QHash<QString, QString> dictFiles;
	SpellerUtility *emptySpeller;
	QString mDefaultSpellerName;
};


#endif
