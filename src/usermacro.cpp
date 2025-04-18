#include "mostQtHeaders.h"
#include "usermacro.h"
#include "smallUsefulFunctions.h"
#include "qformatscheme.h"
#include "qlanguagefactory.h"
#include "qdocument.h"
#include "latexdocument.h"
#include <QJsonDocument>
#include <QJsonArray>

Macro::Macro() : type(Snippet), triggerLookBehind(false), document(nullptr)
{
}

Macro::Macro(const QString &nname, const QString &typedTag, const QString &nabbrev, const QString &ntrigger): triggerLookBehind(false), document(nullptr)
{
	Macro::Type typ;
	QString tag = parseTypedTag(typedTag, typ);
	init(nname, typ, tag, nabbrev, ntrigger);
}

Macro::Macro(const QString &nname, Macro::Type ntype, const QString &ntag, const QString &nabbrev, const QString &ntrigger): triggerLookBehind(false), document(nullptr)
{
	init(nname, ntype, ntag, nabbrev, ntrigger);
}

Macro::Macro(const QStringList &fieldList): type(Snippet), triggerLookBehind(false), document(nullptr)
{
	if (fieldList.count() >= 4) {
		Macro::Type t;
		QString tag = parseTypedTag(fieldList[1], t);
		init(fieldList[0], t, tag, fieldList[2], fieldList[3]);
	}
}

Macro Macro::fromTypedTag(const QString &typedTag)
{
	return Macro("unnamed", typedTag);
}

void Macro::init(const QString &nname, Macro::Type ntype, const QString &ntag, const QString &nabbrev, const QString &ntrigger)
{
	name = nname;
	type = ntype;
	tag = ntag;
	abbrev = nabbrev;
	trigger = ntrigger;
	triggerLookBehind = false;
	QString realtrigger = trigger;
    triggers = SpecialTriggers();
	if (realtrigger.trimmed().startsWith("?")) {
		QStringList sl = realtrigger.split("|");
		realtrigger.clear();
		foreach (const QString &x, sl) {
			QString t = x.trimmed();
			if (t == "?txs-start") triggers |= ST_TXS_START;
			else if (t == "?new-file") triggers |= ST_NEW_FILE;
			else if (t == "?new-from-template") triggers |= ST_NEW_FROM_TEMPLATE;
			else if (t == "?load-file") triggers |= ST_LOAD_FILE;
			else if (t == "?load-this-file") triggers |= ST_LOAD_THIS_FILE;
			else if (t == "?save-file") triggers |= ST_FILE_SAVED;
			else if (t == "?close-file") triggers |= ST_FILE_CLOSED;
			else if (t == "?master-changed") triggers |= ST_MASTER_CHANGED;
			else if (t == "?after-typeset") triggers |= ST_AFTER_TYPESET;
			else if (t == "?after-command-run") triggers |= ST_AFTER_COMMAND_RUN;
			else if (realtrigger.isEmpty()) realtrigger = t;
			else realtrigger = realtrigger + "|" + t;
		}
	}
	if (realtrigger.isEmpty()) return;

	triggers |= ST_REGEX;

	int lastLen;
	do {
		lastLen = realtrigger.length();
		if (realtrigger.startsWith("(?language:")) {
			const int langlen = strlen("(?language:");
			int paren = 1, bracket = 0, i = langlen;
			for (; i < realtrigger.length() && paren; i++) {
				switch (realtrigger[i].unicode()) {
				case '(':
					if (!bracket) paren++;
					break;
				case ')':
					if (!bracket) paren--;
					break;
				case '[':
					bracket = 1;
					break;
				case ']':
					bracket = 0;
					break;
				case '\\':
					i++;
					break;
				}
			}
			triggerLanguage = realtrigger.mid(langlen, i - langlen - 1);
			triggerLanguage.replace("latex", "\\(La\\)TeX");
			realtrigger.remove(0, i);
		}

		if (realtrigger.startsWith("(?highlighted-as:")) {
			int start = realtrigger.indexOf(':') + 1;
			int closing = realtrigger.indexOf(")");
			triggerFormatsUnprocessed = realtrigger.mid(start, closing - start).replace(',', '|').replace(" ", ""); //handle later, when the formats are loaded
			realtrigger.remove(0, closing + 1);
		}
		if (realtrigger.startsWith("(?not-highlighted-as:")) {
			int start = realtrigger.indexOf(':') + 1;
			int closing = realtrigger.indexOf(")");
			triggerFormatExcludesUnprocessed = realtrigger.mid(start, closing - start).replace(',', '|').replace(" ", ""); //handle later, when the formats are loaded
			realtrigger.remove(0, closing + 1);
		}
        if (realtrigger.startsWith("(?inEnv:")) {
            int start = realtrigger.indexOf(':') + 1;
            int closing = realtrigger.indexOf(")");
            QString envs= realtrigger.mid(start, closing - start).replace(',', '|').replace(" ", ""); //handle later, when the formats are loaded
            triggerInEnvs = envs.split("|");
            realtrigger.remove(0, closing + 1);
        }

	} while (lastLen != realtrigger.length());

    triggerRegex = QRegularExpression("(?:" + realtrigger + ")$"); // (?: non capturing)
}

void Macro::initTriggerFormats()
{
	QFormatScheme *fs = QDocument::defaultFormatScheme();
	REQUIRE(fs);
	foreach (const QString &formatName,	triggerFormatsUnprocessed.split('|')) {
		if (fs->exists(formatName)) {
			triggerFormats << fs->id(formatName);
		}
	}
	triggerFormatsUnprocessed.clear();
	foreach (const QString &formatName,	triggerFormatExcludesUnprocessed.split('|')) {
		if (fs->exists(formatName)) {
			triggerFormatExcludes << fs->id(formatName);
		}
	}
	triggerFormatExcludesUnprocessed.clear();

}

QStringList Macro::toStringList() const
{
	return QStringList() << name << typedTag() << abbrev << trigger;
}

QString Macro::snippet() const
{
	if (type == Snippet)
		return tag;
	else if (type == Environment)
		return "\\begin{" + tag + "}";
    else if (type == AIQuery)
        return tag;
	return QString();
}

QString Macro::script() const
{
	if (type == Script)
		return tag;
    return QString();
}

QString Macro::shortcut() const
{
    return m_shortcut;
}

bool Macro::isEmpty() const
{
    return name.isEmpty() && tag.isEmpty() && trigger.isEmpty();
}

void Macro::setShortcut(const QString &sc)
{
    m_shortcut=sc;
}

void Macro::setTrigger(const QString &newTrigger)
{
    init(name,type,tag,abbrev,newTrigger);
}

QString Macro::typedTag() const
{
	switch(type) {
    case Snippet: return tag;
    case Environment: return "%" + tag;
    case Script: return "%SCRIPT\n" + tag;
    case AIQuery: return "%AIQUERY\n" + tag;
	default:
		qDebug() << "unknown macro type" << type;
	}
    return QString();
}

void Macro::setTypedTag(const QString &m_tag)
{
    tag=parseTypedTag(m_tag,type);
}

QString Macro::getTag()
{
    return tag;
}

void Macro::setTag(const QString &ntag)
{
    tag=ntag;
}

void Macro::setType(const Macro::Type &ntype)
{
    type=ntype;
}

QString Macro::parseTypedTag(QString typedTag, Macro::Type &retType)
{
	if (typedTag.startsWith("%SCRIPT\n")) {
		retType = Script;
		return typedTag.mid(8);
    } else if (typedTag.startsWith("%AIQUERY\n")){
        retType = AIQuery;
        return typedTag.mid(9);
	} else if (typedTag.startsWith('%') && (typedTag.length() == 1 || typedTag.at(1).isLetter())) {
		// Note: while % is an empty environemnt, reserved sequences like %%, %<, %| are snippets.
		retType = Environment;
		return typedTag.mid(1);
	}
	retType = Snippet;
	return typedTag;
}

void Macro::parseTriggerLanguage(QLanguageFactory *langFactory)
{
    if(!langFactory) return;
    if (triggerLanguage.isEmpty()) return;
	triggerLanguages.clear();
    QRegularExpression tempRE(triggerLanguage+"$", QRegularExpression::CaseInsensitiveOption);
	foreach (const QString &lang, langFactory->languages()) {
        if (lang.indexOf(tempRE)==0)
			triggerLanguages << langFactory->languageData(lang).d;
	}
}

bool Macro::isActiveForTrigger(Macro::SpecialTrigger trigger) const
{
	return (triggers & trigger);
}

bool Macro::isActiveForLanguage(QLanguageDefinition *lang) const
{
	// if no trigger language is specified, the macro is active for all languages.
	return triggerLanguage.isEmpty() || triggerLanguages.contains(lang);
}

/*!
 * \brief check if any format trigger are set
 * Included or excluded formats are considered
 * \return
 */
bool Macro::hasFormatTriggers() const
{
    if (!triggerFormatsUnprocessed.isEmpty() || !triggerFormatExcludesUnprocessed.isEmpty()) (const_cast<Macro *>(this))->initTriggerFormats();
    return !triggerFormats.isEmpty() || !triggerFormatExcludes.isEmpty();
}
/*!
 * \brief return the list of format triggers
 * \return
 */
QList<int> Macro::getFormatTriggers() const
{
    return triggerFormats;
}
/*!
 * \brief return the list of format triggers which should be excluded
 * \return
 */
QList<int> Macro::getFormatExcludeTriggers() const
{
    return triggerFormatExcludes;
}
/*!
 * \brief return the list of environment trigger
 * \return
 */
QStringList Macro::getTriggerInEnvs() const
{
    return triggerInEnvs;
}

bool Macro::save(const QString &fileName) const {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QJsonObject dd;
    dd.insert("formatVersion",2);
    dd.insert("name",name);
    QString typeName=( type==Script ? "Script" : ( type==Environment ? "Environment" : "Snippet" ) );
    if(type==AIQuery){
        typeName="AIQuery";
    }
    dd.insert("type", typeName );
    dd.insert("tag",QJsonArray::fromStringList(tag.split("\n")));
    dd.insert("description",QJsonArray::fromStringList(description.split("\n")));
    dd.insert("abbrev",abbrev);
    dd.insert("trigger",trigger);
    dd.insert("menu",menu);
    dd.insert("shortcut",m_shortcut);
    QJsonDocument jsonDoc(dd);
    file.write(jsonDoc.toJson());
    return true;
}

bool Macro::load(const QString &fileName){
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream in(&file);
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
    in.setCodec("UTF-8");
#endif
    QString text=in.readAll();
    return loadFromText(text);
}

bool Macro::loadFromText(const QString &text)
{
    QHash<QString,QString>rawData;
    QJsonParseError parseError;
    QJsonDocument jsonDoc=QJsonDocument::fromJson(text.toUtf8(),&parseError);
    if(parseError.error!=QJsonParseError::NoError){
        // parser could not read input
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("Macro read-in failed\nError: ")+parseError.errorString());
        msgBox.exec();
        return false;
    }
    QJsonObject dd=jsonDoc.object();
    if(dd.contains("formatVersion")){
        for(const QString& key : dd.keys()){
            if(dd[key].isString()){
                rawData.insert(key,dd[key].toString());
            }
            if(dd[key].isArray()){
                QJsonArray array=dd[key].toArray();
                QString text;
                for(QJsonArray::const_iterator it=array.constBegin();it!=array.constEnd();it++){
                    if(it->isString()){
                        if(!text.isEmpty()){
                            text.append('\n');
                        }
                        text.append(it->toString());
                    }
                }
                rawData.insert(key,text);
            }
        }
    }else{
        //old format
        qDebug()<<"support for old macro format was removed!";
        return false;
    }

    // distrbute data on internal structure
    Macro::Type typ;
    QString tag;
    switch(dd.value("formatVersion").toInt()) {
      case 1:
        tag = parseTypedTag(rawData.value("tag"),typ);
        rawData.insert("formatVersion","2");
        qDebug() << QString("Macro %1 with version 1 migrated as type %2.").arg(rawData.value("name"), ( typ==Script ? "Script" : ( typ==Environment ? "Environment" : "Snippet" ) ));
        break;
      case 2: {
        QString qtype = rawData.value("type");
        typ = ( qtype=="Script" ? Script : ( qtype=="Environment" ? Environment : Snippet ) );
        if(qtype=="AIQuery"){
            typ=AIQuery;
        }
        tag = rawData.value("tag");
        break;
      }
      default:
        qDebug() << QString("Trying to import macro %1 with unknown version %2 as type Snippet. Type maybe wrong.").arg(rawData.value("name")).arg(dd.value("formatVersion").toInt());
        typ = Snippet;
        tag = rawData.value("tag");
    }
    init(rawData.value("name"),typ,tag,rawData.value("abbrev"),rawData.value("trigger"));
    m_shortcut=rawData.value("shortcut");
    menu=rawData.value("menu");
    description=rawData.value("description");
    return true;
}


