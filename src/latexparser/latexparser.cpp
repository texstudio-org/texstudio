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
	environmentCommands = QSet<QString>::fromList(QStringList() << "\\begin" << "\\end" << "\\newenvironment" << "\\renewenvironment");
	mathStartCommands  << "$" << "$$" << "\\(" << "\\[" ;
	mathStopCommands  << "$" << "$$" << "\\)" << "\\]" ;

	possibleCommands.clear();
	possibleCommands["tabular"] = QSet<QString>::fromList(QStringList() << "&" );
	possibleCommands["array"] = QSet<QString>::fromList(QStringList() << "&" );
	possibleCommands["tabbing"] = QSet<QString>::fromList(QStringList() << "\\<" << "\\>" << "\\=" << "\\+");
	possibleCommands["normal"] = QSet<QString>::fromList(QStringList() << "\\\\" << "\\_" << "\\-" << "$" << "$$" << "\\$" << "\\#" << "\\{" << "\\}" << "\\S" << "\\'" << "\\`" << "\\^" << "\\=" << "\\." << "\\u" << "\\v" << "\\H" << "\\t" << "\\c" << "\\d" << "\\b" << "\\o" << "\\O" << "\\P" << "\\l" << "\\L" << "\\&" << "\\~" << "\\" << "\\," << "\\%" << "\\\"");
	possibleCommands["math"] = QSet<QString>::fromList(QStringList() << "_" << "^" << "\\$" << "\\#" << "\\{" << "\\}" << "\\S" << "\\," << "\\!" << "\\;" << "\\:" << "\\\\" << "\\ " << "\\|");
	possibleCommands["%definition"] << "\\newcommand" << "\\renewcommand" << "\\newcommand*" << "\renewcommand*" << "\\providecommand" << "\\newlength" << "\\let";
	possibleCommands["%usepackage"] << "\\usepackage" << "\\documentclass";
	possibleCommands["%graphics"] << "\\includegraphics";
	possibleCommands["%bibitem"] << "\\bibitem";
	possibleCommands["%cite"]  << "\\cite" <<  "\\nptextcite"  ;
	possibleCommands["%label"] << "\\label";
	possibleCommands["%bibliography"] << "\\bibliography";
	possibleCommands["%file"] << "\\include" << "\\input" << "\\import" << "\\includeonly" << "\\includegraphics" << "\\bibliographystyle" << "\\bibliography";
	possibleCommands["%ref"] = QSet<QString>();  // will all be populated via cwl
	possibleCommands["%include"] << "\\include" << "\\input";
	possibleCommands["%import"] << "\\import" << "\\inputfrom" << "\\subimport" << "\\subinputfrom"
								<< "\\import*" << "\\inputfrom*" << "\\subimport*" << "\\subinputfrom*";
	commandDefs.clear();
}

///position of the % starting a comment (takes care of multiple backslashes before comment character ..)
int LatexParser::commentStart(const QString &text)
{
	if (text.startsWith("%")) return 0;
	QString test = text;
	test.replace("\\\\", "  ");
	int cs = test.indexOf(QRegExp("[^\\\\]%")); // find start of comment (if any)
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
	int abort = line.indexOf(QRegExp("(\\s|\\\\)"), start + 1);
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
			stop = line.indexOf(QRegExp("\\S+"), start);
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

/*! return a number for a context
 * 0 unknown
 * 1 command
 * 2 option \command[option]{arg}
 * 3 argument \command{arg}
 * 4 argument 2   \command{arg}{arg2}
 * etc
 * \warning obsolete for lexer-based token system, though still in use in some code
 */
int LatexParser::findContext(QString &line, int &column) const
{

	if (line.isEmpty())
		return 0;
	QString eow = "\\[]{}$";
	int i = column;
	if (i >= line.length())
		i = line.length();
	if (i > 0)
		i--; // character left of pos is to be checked
	else
		return 0; // no context can be detected at line start (old behavior)
	while (i >= 0 && !eow.contains(line.at(i)))
		i--;
	if (i < 0)
		return 0; // no eow found
	QChar ch = line.at(i);
	if (ch == '\\') {
		// command found
		int start = i;
		i++;
		while (i < line.length() && !eow.contains(line.at(i)))
			i++;
		line = line.mid(start, i - start);
		column = start;
		return 1;
	}
	int start_ref = findOpeningBracket(line, i);
	int start_opt = findOpeningBracket(line, i, '[', ']');
	int ret = 0;
	if (start_ref > start_opt) {
		// assuming we are in command argument
		ret = 3;
		i = start_ref - 1;
	} else {
		if (start_opt > -1) {
			//assuming we are in command option
			ret = 2;
			i = start_opt - 1;
		}
	}
	if (ret == 0)
		return 0;

	int n = 0;
	QString openBrackets = "[{";
	QString closeBrackets = "]}";
	eow = getCommonEOW();
	eow.remove(' ');
	int stop = i;
	while (i > -1) {
		ch = line.at(i);
		if (openBrackets.contains(ch)) {
			//TODO check if correct bracket was opened ...
			n--;
			if (n < 0)
				break;
			i--;
			stop = i;
			continue;
		}
		if (closeBrackets.contains(ch)) {
			n++;
			if (ch == '}')
				++ret;  //going through another braces pair, [] is not checked
			i--;
			continue;
		}
		if (n == 0 && eow.contains(ch)) {
			if (ch == '\\') {
				//TODO: check if not \\ (newline) was found
				line = line.mid(i, stop - i + 1).simplified();
				column = i;
				return ret;
			} else { // this is a overly strict interpretation of command syntax
				return 0;
			}
		}
		i--;
	}

	return 0;
}

LatexParser::ContextType LatexParser::findContext(const QString &line, int column, QString &command, QString &value) const
{
	command = line;
	int col = column; //remember column
	int temp = findContext(command, column);
	QStringList vals;
	resolveCommandOptions(line, column, vals);
	value = "";
	if (!vals.isEmpty()) {
		value = vals.takeFirst();
		if (value.startsWith('[') && temp != 2) {
			if (!vals.isEmpty()) {
				value = vals.takeFirst();
			}
		}
		if (value.startsWith('{') || value.startsWith('['))
			value.remove(0, 1);
		if (value.endsWith('}') || value.endsWith(']'))
			value.chop(1);
	}
	switch (temp) {
	case 0:
		return Unknown;
	case 1:
		return Command;
	case 3:
		if (specialTreatmentCommands.contains(command)) {
			QSet<QPair<QString, int> > helper = specialTreatmentCommands.value(command);
			QPair<QString, int> elem;
			foreach (elem, helper) {
				if (elem.second == 1)
					return ArgEx;
			}
		}
		// check key/val
		{
			QStringList keys = possibleCommands.keys();
			bool handled = false;
			QString elem;
			QStringList checkOptions;
			checkOptions <<  "key%1" + command << "key%1" + command + "#c";

			foreach (elem, checkOptions) {
				if (keys.contains(elem)) {
					handled = true;
					command = elem.mid(4);
					break;
				}
			}

			if (handled) {
				// check that cursor is within keyval
				bool isKey = false;
				for (int i = col; col > 0; col--) {
					if (line.at(i - 1).isLetter())
						continue;
					if (line.at(i - 1) == '{' || line.at(i - 1) == ',')
						isKey = true;
					break;
				}
				if (isKey)
					return Keyval;
				else
					return KeyvalValue;
			}
		}
		// normal context
		if (environmentCommands.contains(command))
			return Environment;
		else if (possibleCommands["%label"].contains(command))
			return Label;
		else if (possibleCommands["%ref"].contains(command))
			return Reference;
		else if (possibleCommands["%usepackage"].contains(command))
			return Package;
		else if (possibleCommands["%cite"].contains(command))
			return Citation;
		else if (possibleCommands["%citeExtendedCommand"].contains(command))
			return Citation_Ext;
		else if (possibleCommands["%graphics"].contains(command))
			return Graphics;
		else return Option;
	case 2:
		// find possible commands for keyval completion
	{
		if (specialTreatmentCommands.contains(command)) {
			QSet<QPair<QString, int> > helper = specialTreatmentCommands.value(command);
			QPair<QString, int> elem;
			foreach (elem, helper) {
				if (elem.second == 0)
					return OptionEx;
			}
		}
		QStringList keys = possibleCommands.keys();
		QString arg;
		if (!vals.isEmpty()) {
			arg = vals.first();
			if (arg.startsWith('{') )
				arg.remove(0, 1);
			if (arg.endsWith('}'))
				arg.chop(1);
		}
		bool handled = false;
		QString elem;
		QStringList checkOptions;
		checkOptions << "key%" + command + "/" + arg << "key%" + command + "/" + arg + "#c" << "key%" + command << "key%" + command + "#c";

		foreach (elem, checkOptions) {
			if (keys.contains(elem)) {
				handled = true;
				command = elem.mid(4);
				break;
			}
		}

		if (handled) {
			// check that cursor is within keyval
			bool isKey = false;
			for (int i = col; col > 0; col--) {
				if (line.at(i - 1).isLetter())
					continue;
				if (line.at(i - 1) == '[' || line.at(i - 1) == ',')
					isKey = true;
				break;
			}
			if (isKey)
				return Keyval;
			else
				return KeyvalValue;
		}
        [[clang::fallthrough]];
	}
	default:
		return Unknown;
	}
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
	specialTreatmentCommands.unite(elem.specialTreatmentCommands);
	specialDefCommands.unite(elem.specialDefCommands);
	commandDefs.unite(elem.commandDefs);
	mapSpecialArgs.unite(elem.mapSpecialArgs);
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
				packageAliases.insertMulti(alias, line);
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

