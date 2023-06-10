#include "latexparser.h"

const QString CommonEOW = QString("~!#$%^&*()_+{}|:\"\\<>?,./;[]-= \t\n\r`'") +
						  QChar(171) + QChar(187) + QChar(8223) + QChar(8222) + QChar(8221) + QChar(8220) +  /* fancy quotation marks */
						  QChar(160);  /* non-breaking Space */


const QString & getCommonEOW()
{
	return CommonEOW;
}



const int LatexParser::MAX_STRUCTURE_LEVEL = 10;

LatexParser *LatexParserInstance = nullptr;

LatexParser::LatexParser()
{
	if (!LatexParserInstance) {
		LatexParserInstance = this;
		init();
	}
}

LatexParser::~LatexParser()
{
	if (LatexParserInstance == this) {
        LatexParserInstance = nullptr;
	}
}

LatexParser &LatexParser::getInstance()
{
	Q_ASSERT(LatexParserInstance);
	return *LatexParserInstance;
}

LatexParser * LatexParser::getInstancePtr()
{
	return LatexParserInstance;
}

void LatexParser::init()
{
    environmentCommands = QSet<QString>{"\\begin" , "\\end" , "\\newenvironment" , "\\renewenvironment"};
    mathStartCommands = QStringList{ "$" , "$$" , "\\(" , "\\[" };
    mathStopCommands = QStringList{ "$" , "$$" , "\\)" , "\\]" } ;

	possibleCommands.clear();
    possibleCommands["tabular"] = QSet<QString>{"&" };
    possibleCommands["array"] = QSet<QString>{ "&" };
    possibleCommands["tabbing"] = QSet<QString>{"\\<" , "\\>" , "\\=" , "\\+"};
    possibleCommands["normal"] = QSet<QString>{ "\\\\" , "\\_" , "\\-" , "$" , "$$" , "\\$" , "\\#" , "\\{" , "\\}" , "\\S" , "\\'" , "\\`" , "\\^" , "\\=" , "\\." , "\\u" , "\\v" , "\\H" , "\\t" , "\\c" , "\\d" , "\\b" , "\\o" , "\\O" , "\\P" , "\\l" , "\\L" , "\\&" , "\\~" , "\\" , "\\," , "\\%" , "\\\"", "\\," , "\\!" , "\\;" , "\\:" , "\\/"};
    possibleCommands["math"] = QSet<QString>{ "_" , "^" , "\\$" , "\\#" , "\\{" , "\\}" , "\\S" , "\\," , "\\!" , "\\;" , "\\:" , "\\/" , "\\\\" , "\\ " , "\\|"};
    possibleCommands["%definition"] = QSet<QString>{ "\\newcommand" , "\\renewcommand" , "\\newcommand*" , "\\renewcommand*" , "\\providecommand" , "\\newlength" , "\\let"};
    possibleCommands["%usepackage"] = QSet<QString>{ "\\usepackage" , "\\documentclass" };
    possibleCommands["%graphics"] = QSet<QString>{ "\\includegraphics" };
    possibleCommands["%bibitem"] = QSet<QString>{ "\\bibitem" };
    possibleCommands["%cite"]  = QSet<QString>{ "\\cite" ,  "\\nptextcite"  };
    possibleCommands["%label"] = QSet<QString>{ "\\label" };
    possibleCommands["%bibliography"] = QSet<QString>{ "\\bibliography" };
    possibleCommands["%file"] = QSet<QString>{ "\\include" , "\\input" , "\\import" , "\\includeonly" , "\\includegraphics" , "\\bibliographystyle" , "\\bibliography"};
	possibleCommands["%ref"] = QSet<QString>();  // will all be populated via cwl
    possibleCommands["%include"] = QSet<QString>{ "\\include" , "\\input"};
    possibleCommands["%import"] = QSet<QString>{ "\\import" , "\\inputfrom" , "\\subimport" , "\\subinputfrom"
                                , "\\import*" , "\\inputfrom*" , "\\subimport*" , "\\subinputfrom*"
                                , "\\includefrom" , "\\includefrom*" , "\\subincludefrom" , "\\subincludefrom*"};
	commandDefs.clear();
}

///position of the % starting a comment (takes care of multiple backslashes before comment character ..)
int LatexParser::commentStart(const QString &text)
{
	if (text.startsWith("%")) return 0;
	QString test = text;
	test.replace("\\\\", "  ");
    int cs = test.indexOf(QRegularExpression("[^\\\\]%")); // find start of comment (if any)
    if (cs > -1) {
        return cs + 1;
    } else return -1;
}

/// remove comment from text, take care of multiple backslashes before comment character ...
QString LatexParser::cutComment(const QString &text)
{
	return text.left(LatexParser::commentStart(text));
}

/// returns true if the options are complete, false if the scanning ended while still in the options
bool LatexParser::resolveCommandOptions(const QString &line, int column, QStringList &values, QList<int> *starts)
{
	const QString BracketsOpen("[{(");
	const QString BracketsClose("]})");
	int start = column;
	int stop = -1;
	int type;
	// check if between command and options is located text or other command
    int abort = line.indexOf(QRegularExpression("(\\s|\\\\)"), start + 1);
	while (start < line.length()) {
		// find first available bracket after position start
		int found = -1;
		type = -1;
		for (int i = 0; i < BracketsOpen.size(); i++) {
			int zw = line.indexOf(BracketsOpen[i], start);
			if (zw > -1 && (zw < found || found == -1)) {
				found = zw;
				type = i;
			}
		}
		if (type < 0) break;
		// check if only space between cmd and opening bracket
		if (abort > 0) {
			if ((found - abort) > 0) {
				QString test = line.mid(abort, found - abort);
				test = test.simplified();
				test.remove(' ');
				if (!test.isEmpty())
					break;
			}
			abort = -1;
		}
		// check wether a word letter appears before (next command text ...)
		if (stop > -1) {
            stop = line.indexOf(QRegularExpression("\\S+"), start);
		}
		if (stop < found && stop > -1) break;
		// find apropriate closing bracket.
		int lvl = 0;
		stop = -1;
		for (int i = found + 1; i < line.length(); i++) {
			QChar c = line[i];
			if (lvl == 0 && c == BracketsClose[type]) {
				stop = i;
				break;
			}
			if (BracketsOpen.contains(c)) {
				lvl++;
			}
			if (lvl > 0 && BracketsClose.contains(c)) {
				lvl--;
			}
		}
		if (found > -1 && stop > -1) {
			values << line.mid(found, stop - found + 1);
			if (starts)
				starts->append(found);
			start = stop + 1;
		} else return false;
	}
	return true;
}
/*!
 * \brief remove option brackets from text on 'option'
 * \param option text
 * \return option without []
 */
QString LatexParser::removeOptionBrackets(const QString &option)
{
	if (option.isNull() || option.length() < 2) return option;
	if ((option.at(0) == '{' && option.at(option.length() - 1) == '}') ||
	        (option.at(0) == '[' && option.at(option.length() - 1) == ']'))
		return option.mid(1, option.length() - 2);
	return option;
}
/*!
 * \brief determines level of structure in a section-command
 * \param cmd latex command
 * \return level of stucture
 */
int LatexParser::structureCommandLevel(const QString &cmd) const
{
	for (int i=0; i<=MAX_STRUCTURE_LEVEL; i++) {
		if (possibleCommands[QString("%structure%1").arg(i)].contains(cmd)) {
			return i;
		}
	}
	return -1;
}

void LatexParser::append(const LatexParser &elem)
{
	QHash<QString, QSet<QString> >::const_iterator i = elem.possibleCommands.constBegin();
	while (i != elem.possibleCommands.constEnd()) {
		QString key = i.key();
		QSet<QString> set = i.value();
		possibleCommands[key].unite(set);
		++i;
	}
	foreach (const QString key, elem.environmentAliases.keys()) {
		QStringList values = elem.environmentAliases.values(key);
		foreach (const QString value, values) {
			if (!environmentAliases.contains(key, value))
				environmentAliases.insert(key, value);
		}
	}
#if (QT_VERSION>=QT_VERSION_CHECK(5,15,0))
    specialDefCommands.insert(elem.specialDefCommands);
    commandDefs.unite(elem.commandDefs);
    mapSpecialArgs.insert(elem.mapSpecialArgs);
#else
	specialDefCommands.unite(elem.specialDefCommands);
	commandDefs.unite(elem.commandDefs);
	mapSpecialArgs.unite(elem.mapSpecialArgs);
#endif
}

void LatexParser::substract(const LatexParser &elem)
{
	QHash<QString, QSet<QString> >::const_iterator i = elem.possibleCommands.constBegin();
	while (i != elem.possibleCommands.constEnd()) {
		QString key = i.key();
		QSet<QString> set = i.value();
		possibleCommands[key].subtract(set);
		++i;
	}
	foreach (QString key, elem.commandDefs.keys()) {
		commandDefs.remove(key);
	}
}

void LatexParser::clear()
{
	init();
}

void LatexParser::importCwlAliases(const QString filename)
{
	QFile tagsfile(filename);
	if (tagsfile.open(QFile::ReadOnly)) {
		QString line;
		QString alias;
		while (!tagsfile.atEnd()) {
			line = tagsfile.readLine().trimmed();
			if (line.startsWith("#"))
				continue;
			if (line.endsWith(":")) {
				alias = line.left(line.length() - 1);
				continue;
			}
			if (!alias.isEmpty())
                packageAliases.insert(alias, line);
		}
	}
}


int findOpeningBracket(const QString &word, int start, QChar oc, QChar cc)
{
	int i = start;
	int n = 0;
	while (i > -1) {
		QChar ch = word.at(i);
		if (ch == oc) {
			n--;
			if (n < 0)
				break;
		}
		if (ch == cc) {
			n++;
		}
		i--;
	}
	return i;
}


int findClosingBracket(const QString &word, int &start, QChar oc, QChar cc)
{
	int i = 0;
	if (start < 0) start = word.indexOf(oc, i);
	i = start > -1 ? start : 0;
	int stop = word.indexOf(cc, i);
	i = word.indexOf(oc, i + 1);
	while (i > 0 && stop > 0 && i < stop) {
		stop = word.indexOf(cc, stop + 1);
		i = word.indexOf(oc, i + 1);
	}
	return stop;
}


QString interpretXArgs(const QString &xarg)
{
    QString result;
    bool braceMode=false;
    for(int i=0;i<xarg.length();++i){
        QChar c=xarg[i];
        if(c=='{'){
            braceMode=false;
        }
        if(braceMode) continue;
        if(c==' ') continue;
        if(c=='m'){
            result.append("{%<arg%>}");
        }
        if(c.toUpper()=='O'){
            result.append("[%<arg%>]");
        }
        if(c.toUpper()=='R'||c.toUpper()=='D'){
            if(i+2<xarg.length()){
                result.append(xarg[i+1]+QString("%<arg%>")+xarg[i+2]);
                i+=2; // skip after definition
            }
        }
        if(c=='{'){
            braceMode=true;
        }
    }
    return result;
}
