
/***************************************************************************
 *   copyright       : (C) 2008 by Benito van der Zander                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "spellerutility.h"
#include "smallUsefulFunctions.h"
#include "JlCompress.h"

int SpellerUtility::spellcheckErrorFormat = -1;

SpellerUtility::SpellerUtility(QString name): mName(name), currentDic(""), pChecker(nullptr), spellCodec(nullptr)
{
	checkCache.reserve(1020);
}

bool SpellerUtility::loadDictionary(QString dic, QString ignoreFilePrefix)
{
	if (dic == currentDic) return true;
	else unload();
	QString base = dic.left(dic.length() - 4);
	QString dicFile = base + ".dic";
	QString affFile = base + ".aff";
	if (!QFileInfo(dicFile).exists() || !QFileInfo(affFile).exists()) {
		if (!QFileInfo(affFile).exists())
			mLastError = tr("Missing .aff file:\n%1").arg(affFile);
		else
			mLastError = tr("Dictionary does not exist.");
		emit dictionaryLoaded(); //remove spelling error marks from errors with previous dictionary (because these marks could lead to crashes if not removed)
		return false;
	}
	currentDic = dic;
	pChecker = new Hunspell(affFile.toLocal8Bit(), dicFile.toLocal8Bit());
	if (!pChecker) {
		currentDic = "";
		ignoreListFileName = "";
		mLastError = "Creation of Hunspell object failed.";
		REQUIRE_RET(false, false);
	}
	spell_encoding = QString(pChecker->get_dic_encoding());
	spellCodec = QTextCodec::codecForName(spell_encoding.toLatin1());
    if (spellCodec == nullptr) {
		mLastError = "Could not determine encoding.";
		unload();
		emit dictionaryLoaded();
		return false;
	}

	checkCache.clear();
	ignoredWords.clear();
	ignoredWordList.clear();
	ignoredWordsModel.setStringList(QStringList());
	ignoreListFileName = base + ".ign";
	if (!isFileRealWritable(ignoreListFileName))
		ignoreListFileName = ignoreFilePrefix + QFileInfo(dic).baseName() + ".ign";
	if (!isFileRealWritable(ignoreListFileName)) {
		ignoreListFileName = "";
		mLastError.clear();
		emit dictionaryLoaded();
		return true;
	}
	QFile f(ignoreListFileName);
	if (!f.open(QFile::ReadOnly)) {
		mLastError.clear();
		emit dictionaryLoaded();
		return true;
	}
	ignoredWordList = QTextCodec::codecForName("UTF-8")->toUnicode(f.readAll()).split("\n", QString::SkipEmptyParts);
	// add words in user dic
	QByteArray encodedString;
	QString spell_encoding = QString(pChecker->get_dic_encoding());
	QTextCodec *codec = QTextCodec::codecForName(spell_encoding.toLatin1());
	foreach (const QString &elem, ignoredWordList) {
		encodedString = codec->fromUnicode(elem);
		pChecker->add(encodedString.data());
	}
	qSort(ignoredWordList.begin(), ignoredWordList.end(), localeAwareLessThan);
	while (!ignoredWordList.empty() && ignoredWordList.first().startsWith("%")) ignoredWordList.removeFirst();
	ignoredWordsModel.setStringList(ignoredWordList);
	ignoredWords = ignoredWordList.toSet();
	mLastError.clear();
	emit dictionaryLoaded();
	return true;

}

void SpellerUtility::saveIgnoreList()
{
	if (ignoreListFileName != "" && ignoredWords.count() > 0) {
		QFile f(ignoreListFileName);
		if (f.open(QFile::WriteOnly)) {
			QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
			f.write(utf8->fromUnicode("%Ignored-Words;encoding:utf-8;version:" TEXSTUDIO ":1.8\n"));
			foreach (const QString str, ignoredWordList)
				if (!str.startsWith("%"))
					f.write(utf8->fromUnicode(str + "\n"));
		}
	}
}

void SpellerUtility::unload()
{
	saveIgnoreList();
	currentDic = "";
	ignoreListFileName = "";
    if (pChecker != nullptr) {
		delete pChecker;
        pChecker = nullptr;
	}
}

void SpellerUtility::addToIgnoreList(QString toIgnore)
{
	QString word = latexToPlainWord(toIgnore);
	QByteArray encodedString;
	QString spell_encoding = QString(pChecker->get_dic_encoding());
	QTextCodec *codec = QTextCodec::codecForName(spell_encoding.toLatin1());
	encodedString = codec->fromUnicode(word);
	pChecker->add(encodedString.data());
	ignoredWords.insert(word);
	if (!ignoredWordList.contains(word))
		ignoredWordList.insert(qLowerBound(ignoredWordList.begin(), ignoredWordList.end(), word, localeAwareLessThan), word);
	ignoredWordsModel.setStringList(ignoredWordList);
	saveIgnoreList();
	emit ignoredWordAdded(word);
}

void SpellerUtility::removeFromIgnoreList(QString toIgnore)
{
	QByteArray encodedString;
	QString spell_encoding = QString(pChecker->get_dic_encoding());
	QTextCodec *codec = QTextCodec::codecForName(spell_encoding.toLatin1());
	encodedString = codec->fromUnicode(toIgnore);
	pChecker->remove(encodedString.data());
	ignoredWords.remove(toIgnore);
	ignoredWordList.removeAll(toIgnore);
	ignoredWordsModel.setStringList(ignoredWordList);
	saveIgnoreList();
}

QStringListModel *SpellerUtility::ignoreListModel()
{
	return &ignoredWordsModel;
}

SpellerUtility::~SpellerUtility()
{
	emit aboutToDelete();
	unload();
}

bool SpellerUtility::check(QString word)
{
    if (currentDic == "" || pChecker == nullptr) return true; //no speller => everything is correct
	if (word.length() <= 1) return true;
	if (ignoredWords.contains(word)) return true;
	if (word.endsWith('.') && ignoredWords.contains(word.left(word.length() - 1))) return true;
    if (checkCache.contains(word)) return checkCache.value(word);
    QByteArray encodedString = spellCodec->fromUnicode(word);
#if QT_VERSION >= 0x050400
    bool result = pChecker->spell(encodedString.toStdString());
#else
    bool result = pChecker->spell(QString(encodedString).toStdString());
#endif
	while (checkCacheInsertion.size() > 1000) checkCacheInsertion.removeFirst();
	checkCache.insert(word, result);
	checkCacheInsertion.append(word);
	return result;
}

QStringList SpellerUtility::suggest(QString word)
{
	Q_ASSERT(pChecker);
    if (currentDic == "" || pChecker == nullptr) return QStringList(); //no speller => everything is correct
    std::vector<std::string> wlst;
    QByteArray encodedString = spellCodec->fromUnicode(word);
#if QT_VERSION >= 0x050400
    wlst = pChecker->suggest(encodedString.toStdString());
#else
    wlst = pChecker->suggest(QString(encodedString).toStdString());
#endif
	QStringList suggestion;
    int ns=wlst.size();
	if (ns > 0) {
		for (int i = 0; i < ns; i++) {
#if QT_VERSION >= 0x050400
            suggestion << spellCodec->toUnicode(QByteArray::fromStdString(wlst[i]));
#else
            QString wrd=QString::fromStdString(wlst[i]);
            suggestion << wrd;//spellCodec->toUnicode(wrd.toUtf8());
#endif

		}
	}
	return suggestion;
}


SpellerManager::SpellerManager()
{
	emptySpeller = new SpellerUtility("<none>");
	mDefaultSpellerName = emptySpeller->name();
}

SpellerManager::~SpellerManager()
{
	unloadAll();
	if (emptySpeller) {
		delete emptySpeller;
        emptySpeller = nullptr;
	}
}

bool SpellerManager::isOxtDictionary(const QString &fileName)
{
	QFileInfo fi(fileName);
	if (!(QStringList() << "oxt" << "zip").contains(fi.suffix())) return false;
	QStringList files = JlCompress::getFileList(fileName);
	QString affFile;
	QString dicFile;
	foreach (const QString &f, files) {
		if (f.endsWith(".aff")) {
			affFile = f;
		}
		if (f.endsWith(".dic")) {
			dicFile = f;
		}
	}
	if (affFile.length() <= 4 || dicFile.length() <= 4) return false;
	if (affFile.left(affFile.length() - 4) != affFile.left(affFile.length() - 4)) return false; // different names
	return true;
}

bool SpellerManager::importDictionary(const QString &fileName, const QString &targetDir)
{
	if (!isOxtDictionary(fileName)) {
		bool continueAnyway = UtilsUi::txsConfirmWarning(tr("The selected file does not seem to contain a Hunspell dictionary. Do you want to import it nevertheless?"));
		if (!continueAnyway) {
			return false;
		}
	}
	QFileInfo fi(fileName);
	QStringList extractedFiles = JlCompress::extractDir(fileName, QDir(targetDir).filePath(fi.fileName()));
	if (extractedFiles.isEmpty()) {
		UtilsUi::txsWarning(tr("Dictionary import failed: No files could be extracted."));
	}
	return !extractedFiles.isEmpty();
}

void SpellerManager::setIgnoreFilePrefix(const QString &prefix)
{
	ignoreFilePrefix = prefix;
}

void SpellerManager::setDictPaths(const QStringList &dictPaths)
{
	if (dictPaths == m_dictPaths) return;
	m_dictPaths = dictPaths;

	QList<SpellerUtility *> oldDicts = dicts.values();

	dicts.clear();
	dictFiles.clear();
	QMap<QString, QString> usedFiles;
	foreach (const QString &path, dictPaths) {
		scanForDictionaries(path);
	}

	// delete after new dict files are identified so a user can reload the new dict in response to a aboutToDelete signal
	foreach (SpellerUtility *su, oldDicts) {
		delete su;
	}

	emit dictPathChanged();
}

void SpellerManager::scanForDictionaries(const QString &path, bool scansubdirs)
{
	if (path.isEmpty()) return;
    QDirIterator iterator(path);
	while (iterator.hasNext()) {
		iterator.next();
		if (!iterator.fileInfo().isDir()) {
			if (iterator.fileName().endsWith(".dic") && !iterator.fileName().startsWith("hyph_")) {
				QFileInfo fi(iterator.fileInfo());
				QString realDictFile = (fi.isSymLink()) ? QFileInfo(fi.symLinkTarget()).canonicalFilePath() : fi.canonicalFilePath();
				if (dictFiles.contains(fi.baseName()))
					continue;
				dictFiles.insert(fi.baseName(), realDictFile);
			}
		} else if (scansubdirs) {
			scanForDictionaries(iterator.filePath(), false);
		}
	}
}

QStringList SpellerManager::availableDicts()
{
	if (dictFiles.keys().isEmpty())
		return QStringList() << emptySpeller->name();
	return QStringList(dictFiles.keys());
}

bool SpellerManager::hasSpeller(const QString &name)
{
	if (name == emptySpeller->name()) return true;
	return dictFiles.contains(name);
}

bool match(QString &guess, const QList<QString> &keys)
{
	for (int i = 0; i < keys.length(); i++) {
		if (0 == QString::compare(keys[i], guess, Qt::CaseInsensitive)) {
			guess = keys[i];
			return true;
		}
	}
	return false;
}

bool SpellerManager::hasSimilarSpeller(const QString &name, QString &bestName)
{
	if (name.length() < 2) return false;

	QList<QString> keys = dictFiles.keys();

	// case insensitive match
	bestName = name;
	if (match(bestName, keys)) return true;

	// match also with "_" -> "-" replacement
	bestName = name;
	if (bestName.contains('_')) {
		bestName.replace("_", "-");
		if (match(bestName, keys)) return true;
	}

	// match also with "-" -> "_" replacement
	bestName = name;
	if (bestName.contains('-')) {
		bestName.replace("-", "_");
		if (match(bestName, keys)) return true;
	}

	// match only beginning to beginning of keys
	bestName = name;
	QString alternative = name;
	alternative.replace("_", "-");
	for (int i = 0; i < keys.length(); i++)
		if (keys[i].startsWith(bestName, Qt::CaseInsensitive) || keys[i].startsWith(alternative)) {
			bestName = keys[i];
			return true;
		}
	return false;
}

/*!
    If the language has not been used yet, a SpellerUtility for the language is loaded. Otherwise
    the existing SpellerUtility is returned. Possible names are the dictionary file names without ".dic"
    ending and "<default>" for the default speller
*/
SpellerUtility *SpellerManager::getSpeller(QString name)
{
	if (name == "<default>") name = mDefaultSpellerName;
	if (!dictFiles.contains(name)) return emptySpeller;

    SpellerUtility *su = dicts.value(name, nullptr);
	if (!su) {
		su = new SpellerUtility(name);
		if (!su->loadDictionary(dictFiles.value(name), ignoreFilePrefix)) {
			UtilsUi::txsWarning(QString("Loading of dictionary failed:\n%1\n\n%2").arg(dictFiles.value(name)).arg(su->mLastError));
			delete su;
            return nullptr;
		}
		dicts.insert(name, su);
	}
	return su;
}

QString SpellerManager::defaultSpellerName()
{
	return mDefaultSpellerName;
}

bool SpellerManager::setDefaultSpeller(const QString &name)
{
	if (dictFiles.contains(name)) {
		mDefaultSpellerName = name;
		emit defaultSpellerChanged();
		return true;
	}
	return false;
}

void SpellerManager::unloadAll()
{
	foreach (SpellerUtility *su, dicts.values()) {
		delete su;
	}
	dicts.clear();
}

QString SpellerManager::prettyName(const QString &name)
{
	QLocale loc(name);
	if (loc == QLocale::c()) {
		return name;
	} else {
		return QString("%1 - %2 (%3)").arg(name).arg(QLocale::languageToString(loc.language())).arg(QLocale::countryToString(loc.country()));
	}
}

