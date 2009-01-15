
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
#include <QTextCodec>
#include <QFileInfo>
#include <QMessageBox>

SpellerUtility::SpellerUtility(): active(false){
    checkCache.reserve(1020);
}
bool SpellerUtility::loadDictionary(QString dic,QString ignoreFilePrefix){
    if (dic==currentDic) return true;
    else unload();
    currentDic=dic;
    QString base = dic.left(dic.length()-4);
    pChecker = new Hunspell(base.toLatin1()+".aff",base.toLatin1()+".dic");
    spell_encoding=QString(pChecker->get_dic_encoding());
    spellCodec = QTextCodec::codecForName(spell_encoding.toLatin1());

    checkCache.clear();
    ignoredWords.clear();
    ignoreListFileName=base+".ign";
    if (!QFileInfo(ignoreListFileName).isWritable())  
        ignoreListFileName=ignoreFilePrefix+QFileInfo(dic).baseName()+".ign";
    if (!QFileInfo(ignoreListFileName).isWritable()) {
        ignoreListFileName="";
        emit reloadDictionary();
        return true;
    }
    QFile f(ignoreListFileName);
    if ( !f.open(QFile::ReadOnly) ) {
        emit reloadDictionary();
        return true;
    }
    ignoredWords=QTextCodec::codecForName("UTF-8")->toUnicode(f.readAll()).split("\n",QString::SkipEmptyParts).toSet();
    emit reloadDictionary();
    return true;

}
void SpellerUtility::unload(){
    if (ignoreListFileName!="" && ignoredWords.count()>0) { 
        QFile f(ignoreListFileName);
		if ( f.open(QFile::WriteOnly) )
        {
            QTextCodec* utf8=QTextCodec::codecForName("UTF-8");
            f.write(utf8->fromUnicode("%Ignored-Words;encoding:utf-8;version:TexMakerX:1.8\n"));
            foreach (QString str, ignoredWords) 
                if (!str.startsWith("%")) 
                    f.write(utf8->fromUnicode(str+"\n"));
        }
    }
    currentDic="";
    ignoreListFileName="";
}
void SpellerUtility::addToIgnoreList(QString toIgnore){
    ignoredWords.insert(toIgnore);
}
    
SpellerUtility::~SpellerUtility(){
    unload();
    delete pChecker;
}
bool SpellerUtility::check(QString word){
    if (word.length()<=1) return true;
    if (ignoredWords.contains(word)) return true;
    if (checkCache.contains(word)) return checkCache.value(word);
    QByteArray encodedString = spellCodec->fromUnicode(word);
    bool result=pChecker->spell(encodedString.data());
    while (checkCacheInsertion.size()>1000) checkCacheInsertion.removeFirst();
    checkCache.insert(word,result);
    checkCacheInsertion.append(word);
    return result;
}
QStringList SpellerUtility::suggest(QString word){
    QByteArray encodedString = spellCodec->fromUnicode(word);
    char ** wlst;
    int ns = pChecker->suggest(&wlst,encodedString.data());
    QStringList suggestion;
    if (ns > 0) {
        for (int i=0; i < ns; i++) {
            suggestion << spellCodec->toUnicode(wlst[i]);
            free(wlst[i]);
        }
        free(wlst);
    }
    return suggestion;
}

bool SpellerUtility::isActive(){
    return active;
}
void SpellerUtility::setActive(bool a){
    active=a;
}
