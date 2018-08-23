#include "buildmanager.h"

#include "smallUsefulFunctions.h"
#include "configmanagerinterface.h"
#include "utilsSystem.h"

#include "userquickdialog.h"

#ifdef Q_OS_WIN32
#include "windows.h"
#endif

#ifdef Q_OS_WIN32
#define ON_WIN(x) x
#define ON_NIX(x)
#else
#define ON_WIN(x)
#define ON_NIX(x) x
#endif

static const QString DEPRECACTED_TMX_INTERNAL_PDF_VIEWER = "tmx://internal-pdf-viewer";

const QString BuildManager::TXS_CMD_PREFIX = "txs:///";

int BuildManager::autoRerunLatex = 5;
bool BuildManager::showLogInCaseOfCompileError = true;
bool BuildManager::m_replaceEnvironmentVariables = true;
bool BuildManager::m_interpetCommandDefinitionInMagicComment = true;
bool BuildManager::m_supportShellStyleLiteralQuotes = true;
bool BuildManager::singleViewerInstance = false;
QString BuildManager::autoRerunCommands;
QString BuildManager::additionalSearchPaths, BuildManager::additionalPdfPaths, BuildManager::additionalLogPaths;

// *INDENT-OFF* (astyle-config)
#define CMD_DEFINE(up, id) const QString BuildManager::CMD_##up = BuildManager::TXS_CMD_PREFIX + #id;
CMD_DEFINE(LATEX, latex) CMD_DEFINE(PDFLATEX, pdflatex) CMD_DEFINE(XELATEX, xelatex) CMD_DEFINE(LUALATEX, lualatex) CMD_DEFINE(LATEXMK, latexmk)
CMD_DEFINE(VIEW_DVI, view-dvi) CMD_DEFINE(VIEW_PS, view-ps) CMD_DEFINE(VIEW_PDF, view-pdf) CMD_DEFINE(VIEW_LOG, view-log)
CMD_DEFINE(DVIPNG, dvipng) CMD_DEFINE(DVIPS, dvips) CMD_DEFINE(DVIPDF, dvipdf) CMD_DEFINE(PS2PDF, ps2pdf) CMD_DEFINE(GS, gs) CMD_DEFINE(MAKEINDEX, makeindex) CMD_DEFINE(TEXINDY, texindy) CMD_DEFINE(MAKEGLOSSARIES, makeglossaries) CMD_DEFINE(METAPOST, metapost) CMD_DEFINE(ASY, asy) CMD_DEFINE(BIBTEX, bibtex) CMD_DEFINE(BIBTEX8, bibtex8) CMD_DEFINE(BIBER, biber) CMD_DEFINE(SVN, svn) CMD_DEFINE(SVNADMIN, svnadmin)
CMD_DEFINE(COMPILE, compile) CMD_DEFINE(VIEW, view) CMD_DEFINE(BIBLIOGRAPHY, bibliography) CMD_DEFINE(INDEX, index) CMD_DEFINE(GLOSSARY, glossary) CMD_DEFINE(QUICK, quick) CMD_DEFINE(RECOMPILE_BIBLIOGRAPHY, recompile-bibliography)
CMD_DEFINE(VIEW_PDF_INTERNAL, view-pdf-internal) CMD_DEFINE(CONDITIONALLY_RECOMPILE_BIBLIOGRAPHY, conditionally-recompile-bibliography)
CMD_DEFINE(INTERNAL_PRE_COMPILE, internal-pre-compile)
#undef CMD_DEFINE
// *INDENT-ON* (astyle-config)

//! These commands should not consist of a command list, but rather a single command.
//! Otherwise surpising side effects can happen, see https://sourceforge.net/p/texstudio/bugs/2119/
const QStringList atomicCommands = QStringList() << "txs:///latex" << "txs:///pdflatex" << "txs:///xelatex"<< "txs:///lualatex" << "txs:///latexmk";

QString searchBaseCommand(const QString &cmd, QString options);
QString getCommandLineViewDvi();
QString getCommandLineViewPs();
QString getCommandLineViewPdfExternal();
QString getCommandLineGhostscript();

CommandInfo::CommandInfo(): user(false), meta(false), rerunCompiler(false), guessFunc(nullptr) {}

QString CommandInfo::guessCommandLine() const
{
	if (guessFunc) {
		QString temp = (*guessFunc)();
		if (!temp.isEmpty()) return temp;
	}

	if (!baseName.isEmpty()) {
		//search it
		QString bestCommand = searchBaseCommand(baseName, defaultArgs);
		if (!bestCommand.isEmpty()) return bestCommand;
	}

	if (metaSuggestionList.size() > 0)
		return metaSuggestionList.first();

	return "";
}

void CommandInfo::setCommandLine(const QString &cmdString)
{
	if (cmdString == "<default>") commandLine = guessCommandLine();
	if (cmdString == BuildManager::tr("<unknown>")) commandLine = "";
	else {
		//force commands to include options (e.g. file name)
		QString trimmed = cmdString.trimmed();
		QString unquote = trimmed;
		if (trimmed.startsWith('"') && trimmed.endsWith('"')) unquote = trimmed.mid(1, trimmed.length() - 2);
		if (baseName != "" &&
		        ((unquote == baseName) ||
		         (   (unquote.endsWith(QDir::separator() + baseName) || unquote.endsWith("/" + baseName))
		             && (!unquote.contains(" ") || (!unquote.contains('"') && unquote != trimmed)) //spaces mean options, if not everything is quoted
		             && (QFileInfo(unquote).exists())
		         )
		        )) {
			commandLine = cmdString + " " + defaultArgs;
		} else {
			commandLine = cmdString;
		}
	}
}

QString CommandInfo::getPrettyCommand() const
{
	if (commandLine.isEmpty() && metaSuggestionList.isEmpty()) return BuildManager::tr("<unknown>");
	else return commandLine;
}

QString CommandInfo::getProgramName(const QString &commandLine)
{
	QString cmdStr = commandLine.trimmed();
	int p = -1;
	if (cmdStr.startsWith('"')) p = cmdStr.indexOf('"', 1) + 1;
	else if (cmdStr.contains(' ')) p = cmdStr.indexOf(' ');
	if (p == -1) p = cmdStr.length(); //indexOf failed if it returns -1
	return cmdStr.mid(0, p);
}

QString CommandInfo::getProgramNameUnquoted(const QString &commandLine)
{
	QString cmdStr = getProgramName(commandLine);
	if (cmdStr.startsWith('"') && cmdStr.endsWith('"'))
		cmdStr = cmdStr.mid(1, cmdStr.length() - 2);
	return cmdStr;
}

QString CommandInfo::getProgramName() const
{
	return getProgramName(commandLine);
}

ExpandingOptions::ExpandingOptions(const QFileInfo &mainFile, const QFileInfo &currentFile, const int currentLine): mainFile(mainFile), currentFile(currentFile), currentLine(currentLine), nestingDeep(0), canceled(false)
{
	override.removeAll = false;
}

/*
QString BuildManager::getLatexCommandExecutable(LatexCommand cmd){
 QString cmdStr = getLatexCommand(cmd).trimmed();
 int p=-1;
 if (cmdStr.startsWith('"')) p = cmdStr.indexOf('"',1)+1;
 else if (cmdStr.contains(' ')) p = cmdStr.indexOf(' ')+1;
 if (p==-1) p = cmdStr.length(); //indexOf failed if it returns -1
 return cmdStr.mid(0, p);
}*/

CommandToRun::CommandToRun() {}
CommandToRun::CommandToRun(const QString &cmd): command(cmd) {}

QString BuildManager::chainCommands(const QString &a)
{
	return a;
}

QString BuildManager::chainCommands(const QString &a, const QString &b)
{
	return a + "|" + b;
}

QString BuildManager::chainCommands(const QString &a, const QString &b, const QString &c)
{
	return a + "|" + b + "|" + c;
}

QString BuildManager::chainCommands(const QString &a, const QString &b, const QString &c, const QString &d)
{
	return a + "|" + b + "|" + c + "|" + d;
}

/** splits a string into options. Splitting occurs at spaces, except in quotes. **/
QStringList BuildManager::splitOptions(const QString &s)
{
	QStringList options;
	QChar c;
	bool inQuote = false;
	int start = 0;
	int i;
	for (i = 0; i < s.length(); i++) {
		c = s[i];
		if (inQuote) {
			if (c == '"' && s[i - 1] != '\\') {
				inQuote = false;
			}
		} else {
			if (c == '"') {
				inQuote = true;
			} else if (c == ' ') {
				if (start == i) start = i + 1; // multiple spaces;
				else {
					options << dequoteStr(s.mid(start, i - start));
					start = i + 1;
				}
			}
		}
	}
	if (start < i) options << dequoteStr(s.mid(start, i - start));
	return options;
}

QHash<QString, QString> getEnvVariables(bool uppercaseNames)
{
	QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
	QHash<QString, QString> result;
	foreach (const QString &name, envKeys(env)) {
		if (uppercaseNames) {
			result.insert(name.toUpper(), env.value(name));
		} else {
			result.insert(name, env.value(name));
		}
	}
	return result;
}

QString BuildManager::replaceEnvironmentVariables(const QString &s)
{
#ifdef Q_OS_WIN
	Qt::CaseSensitivity caseSensitivity = Qt::CaseInsensitive;
#else
	Qt::CaseSensitivity caseSensitivity = Qt::CaseSensitive;
#endif
	static QHash<QString, QString> envVariables = getEnvVariables(caseSensitivity == Qt::CaseInsensitive);  // environment variables can be static because they do not change during program execution.
	return replaceEnvironmentVariables(s, envVariables, caseSensitivity == Qt::CaseInsensitive);
}

/*!
 * Replace environment variables in the string.
 */
QString BuildManager::replaceEnvironmentVariables(const QString &s, const QHash<QString, QString> &variables, bool compareNamesToUpper)
{
	QString result(s);
#ifdef Q_OS_WIN
	QRegExp rxEnvVar("%([\\w()]+)%");  // word and brackets between %...%
#else
	QRegExp rxEnvVar("\\$(\\w+)");
#endif
	int i = 0;
	while (i >= 0 && i < result.length()) {
		i = result.indexOf(rxEnvVar, i);
		if (i >= 0) {
			QString varName = rxEnvVar.cap(1);
			if (compareNamesToUpper) {
				varName = varName.toUpper();
			}
			QString varContent = variables.value(varName, "");
			result.replace(rxEnvVar.cap(0), varContent);
			i += varContent.length();
		}
	}
	return result;
}

/*!
 * returns paths with replaced [txs-app-dir], [txs-config-dir] and optionally with replaced environment variables
 * paths may be an arbitrary string, in particular a single path or a list of paths
 */
QString BuildManager::resolvePaths(QString paths)
{
	paths = ConfigManagerInterface::getInstance()->parseDir(paths);
	if (m_replaceEnvironmentVariables)
		return replaceEnvironmentVariables(paths);
	else
		return paths;
}

BuildManager::BuildManager(): processWaitedFor(nullptr)
#ifdef Q_OS_WIN32
	, pidInst(0)
#endif
{
	initDefaultCommandNames();
	connect(this, SIGNAL(commandLineRequested(QString, QString *, bool *)), SLOT(commandLineRequestedDefault(QString, QString *, bool *)));

	m_stopBuildAction = new QAction(getRealIcon("stop"), tr("Stop Compile"), this);
	connect(m_stopBuildAction, SIGNAL(triggered()), this, SLOT(killCurrentProcess()));
	m_stopBuildAction->setEnabled(false);
}

BuildManager::~BuildManager()
{
	//remove preview file names
	foreach (const QString &elem, previewFileNames)
		removePreviewFiles(elem);
#ifdef Q_OS_WIN32
	if (pidInst) DdeUninitialize(pidInst);
#endif
}

void BuildManager::initDefaultCommandNames()
{
	REQUIRE (commands.isEmpty());

	//id, platform-independent command, display name, arguments
	registerCommand("latex",       "latex",        "LaTeX",       "-src -interaction=nonstopmode %.tex", "Tools/Latex");
	registerCommand("pdflatex",    "pdflatex",     "PdfLaTeX",    "-synctex=1 -interaction=nonstopmode %.tex", "Tools/Pdflatex");
	registerCommand("xelatex",     "xelatex",      "XeLaTeX",     "-synctex=1 -interaction=nonstopmode %.tex", "");
	registerCommand("lualatex",    "lualatex",     "LuaLaTeX",    "-synctex=1 -interaction=nonstopmode %.tex", "");
	registerCommand("view-dvi",    "",             tr("DVI Viewer"), "%.dvi", "Tools/Dvi", &getCommandLineViewDvi);
	registerCommand("view-ps",     "",             tr("PS Viewer"), "%.ps", "Tools/Ps", &getCommandLineViewPs);
	registerCommand("view-pdf-external", "",        tr("External PDF Viewer"), "%.pdf", "Tools/Pdf", &getCommandLineViewPdfExternal);
	registerCommand("dvips",       "dvips",        "DviPs",       "-o %.ps %.dvi", "Tools/Dvips");
	registerCommand("dvipng",      "dvipng",       "DviPng",      "-T tight -D 120 %.dvi", "Tools/Dvipng");
	registerCommand("ps2pdf",      "ps2pdf",       "Ps2Pdf",      "%.ps", "Tools/Ps2pdf");
	registerCommand("dvipdf",      "dvipdfmx",       "DviPdf",      "%.dvi", "Tools/Dvipdf");
	registerCommand("bibtex",      "bibtex",       "BibTeX",       ON_WIN("%") ON_NIX("%.aux"),  "Tools/Bibtex"); //miktex bibtex will stop (appears like crash in txs) if .aux is attached
	registerCommand("bibtex8",     "bibtex8",      "BibTeX 8-Bit", ON_WIN("%") ON_NIX("%.aux"));
	registerCommand("biber",       "biber",        "Biber" ,       "%"); //todo: correct parameter?
	registerCommand("makeindex",   "makeindex",    "Makeindex",   "%.idx", "Tools/Makeindex");
	registerCommand("texindy",     "texindy",      "Texindy", "%.idx");
	registerCommand("makeglossaries", "makeglossaries", "Makeglossaries", "%");
	registerCommand("metapost",    "mpost",        "Metapost",    "-interaction=nonstopmode ?me)", "Tools/Metapost");
	registerCommand("asy",         "asy",          "Asymptote",   "?m*.asy", "Tools/Asy");
	registerCommand("gs",          "gs;mgs",       "Ghostscript", "\"?am.ps\"", "Tools/Ghostscript", &getCommandLineGhostscript);
	registerCommand("latexmk",     "latexmk",      "Latexmk",     "-pdf -silent -synctex=1 %");


	QStringList descriptionList;
	descriptionList << tr("Compile & View") << tr("PS Chain") << tr("DVI Chain") << tr("PDF Chain") << tr("DVI->PDF Chain") << tr("DVI->PS->PDF Chain") << tr("Asymptote DVI Chain") << tr("Asymptote PDF Chain");
	registerCommand("quick", tr("Build & View"), QStringList() << "txs:///compile | txs:///view" << "txs:///ps-chain" << "txs:///dvi-chain" << "txs:///pdf-chain" << "txs:///dvi-pdf-chain" << "txs:///dvi-ps-pdf-chain" << "txs:///asy-dvi-chain" << "txs:///asy-pdf-chain" /* too long breaks design<< "latex -interaction=nonstopmode %.tex|bibtex %.aux|latex -interaction=nonstopmode %.tex|latex -interaction=nonstopmode %.tex| txs:///view-dvi"*/, "Tools/Userquick", true, descriptionList);

	descriptionList.clear();
	descriptionList << tr("PdfLaTeX") << tr("LaTeX") << tr("XeLaTeX") << tr("LuaLaTeX") << tr("Latexmk");
	registerCommand("compile", tr("Default Compiler"), QStringList() << "txs:///pdflatex" << "txs:///latex" << "txs:///xelatex" << "txs:///lualatex" << "txs:///latexmk", "", true, descriptionList);
	descriptionList.clear();
	descriptionList << tr("PDF Viewer") << tr("DVI Viewer") << tr("PS Viewer");
	registerCommand("view", tr("Default Viewer"), QStringList() << "txs:///view-pdf" << "txs:///view-dvi" << "txs:///view-ps", "", true, descriptionList);
	descriptionList.clear();
	descriptionList << tr("Internal PDF Viewer (Embedded)") << tr("Internal PDF Viewer (Windowed)")  << tr("External PDF Viewer");
	registerCommand("view-pdf", tr("PDF Viewer"), QStringList() << "txs:///view-pdf-internal --embedded" << "txs:///view-pdf-internal" << "txs:///view-pdf-external", "", true, descriptionList);
	descriptionList.clear();
	descriptionList << tr("BibTeX") << tr("BibTeX 8-Bit") << tr("Biber");
	registerCommand("bibliography", tr("Default Bibliography Tool"), QStringList() << "txs:///bibtex" << "txs:///bibtex8" << "txs:///biber", "", true, descriptionList);
	descriptionList.clear();
	descriptionList << tr("BibTeX") << tr("BibTeX 8-Bit") << tr("Biber");
	registerCommand("index", tr("Default Index Tool"), QStringList() << "txs:///makeindex" << "txs:///texindy", "", true, descriptionList);
	descriptionList.clear();
	descriptionList << tr("Makeglossaries");
	registerCommand("glossary", tr("Default Glossary Tool"), QStringList() << "txs:///makeglossaries", "", true, descriptionList);

	registerCommand("ps-chain", tr("PS Chain"), QStringList() << "txs:///latex | txs:///dvips | txs:///view-ps");
	registerCommand("dvi-chain", tr("DVI Chain"), QStringList() << "txs:///latex | txs:///view-dvi");
	registerCommand("pdf-chain", tr("PDF Chain"), QStringList() << "txs:///pdflatex | txs:///view-pdf");
	registerCommand("dvi-pdf-chain", tr("DVI->PDF Chain"), QStringList() << "txs:///latex | txs:///dvipdf | txs:///view-pdf");
	registerCommand("dvi-ps-pdf-chain", tr("DVI->PS->PDF Chain"), QStringList() << "txs:///latex | txs:///dvips | txs:///ps2pdf | txs:///view-pdf");
	registerCommand("asy-dvi-chain", tr("Asymptote DVI Chain"), QStringList() << "txs:///latex | txs:///asy | txs:///latex | txs:///view-dvi");
	registerCommand("asy-pdf-chain", tr("Asymptote PDF Chain"), QStringList() << "txs:///pdflatex | txs:///asy | txs:///pdflatex | txs:///view-pdf");

	registerCommand("pre-compile", tr("Precompile"), QStringList() << "", "Tools/Precompile");
	registerCommand("internal-pre-compile", tr("Internal Precompile"), QStringList() << "txs:///pre-compile | txs:///conditionally-recompile-bibliography");
	registerCommand("recompile-bibliography", tr("Recompile Bibliography"), QStringList() << "txs:///compile | txs:///bibliography | txs:///compile");


	registerCommand("svn",         "svn",          "SVN",         "", "Tools/SVN");
	registerCommand("svnadmin",    "svnadmin",     "SVNADMIN",    "", "Tools/SVNADMIN");

	internalCommands << CMD_VIEW_PDF_INTERNAL << CMD_CONDITIONALLY_RECOMPILE_BIBLIOGRAPHY << CMD_VIEW_LOG;
}

void BuildManager::checkOSXElCapitanDeprecatedPaths(QSettings &settings, const QStringList &commands)
{
#ifdef Q_OS_MAC
#if QT_VERSION >= 0x050500
	if (QSysInfo::MacintoshVersion == QSysInfo::MV_10_11) {
#else  // older Qt versions don't know MV_10_11
	if (QSysInfo::MacintoshVersion > QSysInfo::MV_10_10) {
#endif
		ConfigManagerInterface *config = ConfigManagerInterface::getInstance();
		if (!config->getOption("Tools/CheckOSXElCapitanDeprecatedPaths", true).toBool()) {
			return;
		}
		bool oldPathsFound = false;
		foreach (const QString &id, commands) {
			QString cmd = settings.value(id).toString();
			if (cmd.contains("/usr/texbin/")) {
				oldPathsFound = true;
				break;
			}
		}
		if (!oldPathsFound) {
			return;
		}
		QString newPath = "/Library/TeX/texbin/";
		QString info(tr("OSX 10.11 does not allow applications to write there anymore. Therefore,\n"
		                "recent versions of MacTeX changed the bin path to /Library/TeX/texbin/\n"
		                "\n"
		                "Do you want TeXstudio to change all command paths from /usr/texbin/ to\n"
		                "%1?"));
		if (QDir("/Library/TeX/texbin/").exists()) {
			info = info.arg("/Library/TeX/texbin/");
		} else if (QDir("/usr/local/texbin/").exists()) {
			info = info.arg("/usr/local/texbin/");
			newPath = "/usr/local/texbin/";
		} else {
			info = tr("OSX 10.11 does not allow applications to write there anymore. You may\n"
			          "need to update MacTeX to version 2015.\n"
			          "\n"
			          "Afterwards, MacTeX programs will be located at /Library/TeX/texbin/\n"
			          "\n"
			          "Do you want TeXstudio to change all command paths from /usr/texbin/ to\n"
			          "/Library/TeX/texbin/?");
		}
		QMessageBox msgBox(QApplication::activeWindow());
		msgBox.setWindowTitle(TEXSTUDIO);
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setText(tr("Some of your commands are refering to locations in /usr/texbin/"));
		msgBox.setInformativeText(info);
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Yes);
		emit hideSplash();  // make sure the message box not hidden by the splash screen
		int ret = msgBox.exec();
		if (ret == QMessageBox::Yes) {
			config->setOption("Tools/CheckOSXElCapitanDeprecatedPaths", false);
			foreach (const QString &id, commands) {
				QString cmd = settings.value(id).toString();
				if (cmd.contains("/usr/texbin/")) {
					cmd.replace("/usr/texbin/", newPath);
				}
				settings.setValue(id, cmd);
			}
		} else if (ret == QMessageBox::No) {
			config->setOption("Tools/CheckOSXElCapitanDeprecatedPaths", false);
		}
	}
#else
    Q_UNUSED(settings)
    Q_UNUSED(commands)
#endif
}

CommandInfo &BuildManager::registerCommand(const QString &id, const QString &basename, const QString &displayName, const QString &args, const QString &oldConfig, const GuessCommandLineFunc guessFunc, bool user )
{
	CommandInfo ci;
	ci.id = id;
	ci.baseName = basename;
	ci.displayName = displayName;
	ci.defaultArgs = args;
	ci.deprecatedConfigName = oldConfig;
	ci.guessFunc = guessFunc;
	ci.user = user;
	if (!user) commandSortingsOrder << id;
	return commands.insert(id, ci).value();
}

CommandInfo &BuildManager::registerCommand(const QString &id, const QString &displayname, const QStringList &alternatives, const QString &oldConfig, const bool metaCommand, const QStringList simpleDescriptions)
{
	CommandInfo ci;
	ci.id = id;
	ci.displayName = displayname;
	ci.metaSuggestionList = alternatives;
	ci.simpleDescriptionList = simpleDescriptions;
	ci.meta = metaCommand;
	ci.deprecatedConfigName = oldConfig;
	commandSortingsOrder << id;
	return commands.insert(id, ci).value();
}

QString BuildManager::getCommandLine(const QString &id, bool *user)
{
	QString result;
	emit commandLineRequested(id.trimmed(), &result, user);
	return result;
}

QStringList BuildManager::parseExtendedCommandLine(QString str, const QFileInfo &mainFile, const QFileInfo &currentFile, int currentline)
{
	ConfigManagerInterface *config = ConfigManagerInterface::getInstance();
	str = config->parseDir(str);
	if (m_replaceEnvironmentVariables) {
		str = replaceEnvironmentVariables(str);
	}
	// need to reformat literal quotes before the file insertion logic, because ?a"
	// might be extended to "C:\somepath\" which would then be misinterpreted as an
	// literal quote at the end.
	if (config->getOption("Tools/SupportShellStyleLiteralQuotes", true).toBool()) {
		str = ProcessX::reformatShellLiteralQuotes(str);
	}

	str = str + " "; //end character  so str[i++] is always defined
	QStringList result;
	result.append("");
	for (int i = 0; i < str.size(); i++) {
		QString add;
		if (str.at(i) == QChar('%')) {
			if (str.at(i + 1) == QChar('%')) add = str.at(++i);
			else add = "\"" + mainFile.completeBaseName() + "\"";
		} else if (str.at(i) == QChar('@')) {
			if (str.at(i + 1) == QChar('@')) add = str.at(++i);
			else add = QString::number(currentline);
		} else if (str.at(i) == QChar('?')) {
			if (str.at(++i) == QChar('?')) add = "?";
			else {
				QString command, commandRem;
				QString *createCommand = &command;
				int endMode = 0;
				bool fullSearch = false;
				while (i < str.size()) {
					if (str.at(i) == QChar(')')) {
						endMode = 1;
						break;
					} else if (str.at(i) == QChar(' ') || str.at(i) == QChar('\t')) {
						endMode = 2;
						break;
					} else if (str.at(i) == QChar('\"')) {
						endMode = 3;
						break;
					} else if (str.at(i) == QChar('.') && !fullSearch) {
						endMode = 4;
						break;
					} else if (str.at(i) == QChar('*')) {
						fullSearch = true;
						createCommand = &commandRem;
					}
					(*createCommand) += str.at(i);
					i++;
				}
				bool useCurrentFile = command.startsWith("c:");
				const QFileInfo &selectedFile = (useCurrentFile && !currentFile.fileName().isEmpty()) ? currentFile : mainFile;
				if (useCurrentFile) command = command.mid(2);
				bool absPath = command.startsWith('a');
				//check only sane commands
				if (command == "ame")
					command = QDir::toNativeSeparators(selectedFile.absoluteFilePath());
				else if (command == "am") {
					command = QDir::toNativeSeparators(selectedFile.absoluteFilePath());
					if (selectedFile.suffix() != "") command.chop(1 + selectedFile.suffix().length());
				} else if (command == "a") {
					command = QDir::toNativeSeparators(selectedFile.absolutePath());
					if (!command.endsWith(QDir::separator())) command += QDir::separator();
				} else if (command == "rme")
					command = QDir::toNativeSeparators(mainFile.dir().relativeFilePath(selectedFile.absoluteFilePath()));
				else if (command == "rm") {
					command = QDir::toNativeSeparators(mainFile.dir().relativeFilePath(selectedFile.absoluteFilePath()));
					if (selectedFile.suffix() != "") command.chop(1 + selectedFile.suffix().length());
				} else if (command == "r") {
					command = QDir::toNativeSeparators(mainFile.dir().relativeFilePath(selectedFile.absolutePath()));
					if (command == "") command = ".";
					if (!command.endsWith(QDir::separator())) command += QDir::separator();
				} else if (command == "me") command = selectedFile.fileName();
				else if (command == "m") command = selectedFile.completeBaseName();
				else if (command == "e") command = selectedFile.suffix();
				else if (command.isEmpty() && !commandRem.isEmpty()); //empty search
				else continue; //invalid command

				command.append(commandRem);
				switch (endMode) {
				case 2:
					command += " ";
					break;
				case 3:
					command = "\"" + command + "\"";
					break;
				case 4:
					command += ".";
					break;
				default:
					;
				}
				if (!fullSearch) add = command;
				else {
					QDir dir(QFileInfo(mainFile).absoluteDir());
					if (command.contains("/")) command = command.mid(command.lastIndexOf("/") + 1);
					if (command.contains(QDir::separator())) command = command.mid(command.lastIndexOf(QDir::separator()) + 1);
					QStringList commands = QDir(dir).entryList(QStringList() << command.trimmed(), QDir::Files);
					QString mid;
					if (absPath) {
						mid = QDir::toNativeSeparators(dir.canonicalPath());
						if (!mid.endsWith('/') && !mid.endsWith(QDir::separator())) mid += QDir::separator();
					}
					QStringList oldCommands = result;
					result.clear();
					for (int i = 0; i < oldCommands.size(); i++)
						for (int j = 0; j < commands.size(); j++)
							result.append(oldCommands[i] + mid + commands[j]);
				}
			}
		} else add = str.at(i);
		if (!add.isEmpty())
			for (int i = 0; i < result.size(); i++)
				result[i] += add;
	}
	//  QMessageBox::information(0,"",str+"->"+result,0);
	for (int i = 0; i < result.size(); i++) result[i] = result[i].trimmed(); //remove useless characters
	return result;
}

/*!
 * \brief extracts the
 * \param s
 * \param stdOut output parameter
 * \param stdErr output parameter
 * \return a copy of s truncated to the first occurence of an output redirection
 */
QString BuildManager::extractOutputRedirection(const QString &commandLine, QString &stdOut, QString &stdErr)
{
	QStringList args = ::extractOutputRedirection(tokenizeCommandLine(commandLine), stdOut, stdErr);
	if (stdOut.isEmpty() && stdErr.isEmpty()) {
		return commandLine;
	} else {
		return args.join(" ");
	}
}

QString addPathDelimeter(const QString &a)
{
    return ((a.endsWith("/") || a.endsWith("\\")) ? a : (a + QDir::separator()));
}

QString BuildManager::findFileInPath(QString fileName)
{
	foreach (QString path, getEnvironmentPathList()) {
		path = addPathDelimeter(path);
		if (QFileInfo(path + fileName).exists()) return (path + fileName);
	}
	return "";
}

#ifdef Q_OS_WIN32
typedef BOOL (__stdcall *AssocQueryStringAFunc)(DWORD, DWORD, const char *, const char *, char *, DWORD *);
QString W32_FileAssociation(QString ext)
{
	if (ext == "") return "";
	if (ext[0] != QChar('.')) ext = '.' + ext;
	QString result = "";
	QByteArray ba = ext.toLocal8Bit();
	HMODULE mod = LoadLibraryA("shlwapi.dll");
	AssocQueryStringAFunc assoc = (AssocQueryStringAFunc)(GetProcAddress(mod, "AssocQueryStringA"));
	if (assoc) {
		const DWORD ASSOCSTR_COMMAND = 1;
		char buf[1024];
		DWORD buflen = 1023;
		if (assoc(0, ASSOCSTR_COMMAND, ba.data(), "open", &buf[0], &buflen) == S_OK) {
			buf[buflen] = 0;
			result = QString::fromLatin1(buf);
			result.replace("%1", "?am" + ext);
			//QMessageBox::information(0,result,result,0);
		};
	}
	FreeLibrary(mod);
	return result;
}

QStringList getProgramFilesPaths()
{
	QStringList res;
	QString a = getenv("PROGRAMFILES");
	if (!a.isEmpty()) res << addPathDelimeter(a);
	a = getenv("PROGRAMFILES(X86)");
	if (!a.isEmpty()) res << addPathDelimeter(a);
	if (a != "C:/Program Files" && QDir("C:/Program Files").exists()) res << "C:/Program Files/";
	if (a != "C:/Program Files (x86)" && QDir("C:/Program Files (x86)").exists()) res << "C:/Program Files (x86)/";
	if (a + " (x86)" != "C:/Program Files (x86)" && QDir(a + " (x86)").exists()) res << (a + " (x86)");
	return res;
}

/*!
 * \return the Uninstall string of the program from the registry
 *
 * Note: This won't get the path of 64bit installations when TXS running as a 32bit app due to wow6432 regristry redirection
 * http://www.qtcentre.org/threads/36966-QSettings-on-64bit-Machine
 * http://stackoverflow.com/questions/25392251/qsettings-registry-and-redirect-on-regedit-64bit-wow6432
 * No workaround known, except falling back to the native Windows API. For the moment we'll rely on alternative detection methods.
 */
QString getUninstallString(const QString &program) {
	foreach (const QString &baseKey, QStringList() << "HKEY_LOCAL_MACHINE" << "HKEY_CURRENT_USER") {
		QSettings base(baseKey, QSettings::NativeFormat);
		QString s = base.value("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + program + "\\UninstallString").toString();
		if (!s.isEmpty())
			return s;
	}
	return QString();
}

/*!
 * \return an existing subdir of the from path\subDirFilter\subSubDir.
 *
 * Example:
 * QStringList searchPaths = QStringList() << "C:\\" << "D:\\"
 * findSubdir(searchPaths, "*miktex*", "miktex\\bin\\")
 * will work for "C:\\MikTeX\\miktex\\bin\\" or "D:\\MikTeX 2.9\\miktex\\bin"
 */
QString findSubDir(const QStringList &searchPaths, const QString &subDirFilter, const QString &subSubDir) {
	qDebug() << searchPaths;
	foreach (const QString &path, searchPaths) {
		foreach (const QString &dir, QDir(path).entryList(QStringList(subDirFilter), QDir::AllDirs, QDir::Time)) {
			QDir fullPath(addPathDelimeter(path) + addPathDelimeter(dir) + subSubDir);
			if (fullPath.exists())
				return fullPath.absolutePath();
		}
	}
	return QString();
}

/*!
 * Returns the MikTeX bin path.
 * This should not be called directly but only through getMiKTeXBinPath() to prevent multiple searches.
 */
QString getMiKTeXBinPathInternal()
{
	// search the registry
	QString mikPath = getUninstallString("MiKTeX 2.9");
	// Note: this does currently not work for MikTeX 64bit because of registry redirection (also we would have to parse the
	// uninstall string there for the directory). For the moment we'll fall back to other detection methods.
	if (!mikPath.isEmpty() && QDir(addPathDelimeter(mikPath) + "miktex\\bin\\").exists()) {
		mikPath = addPathDelimeter(mikPath) + "miktex\\bin\\";
	}

	// search the PATH
	if (mikPath.isEmpty()) {
		foreach (QString path, getEnvironmentPathList()) {
			path = addPathDelimeter(path);
			if ((path.endsWith("\\miktex\\bin\\x64\\") || path.endsWith("\\miktex\\bin\\")) && QDir(path).exists())
				return path;
		 }
	}

	// search all program file paths
    if (mikPath.isEmpty()) {
		mikPath = QDir::toNativeSeparators(findSubDir(getProgramFilesPaths(), "*miktex*", "miktex\\bin\\"));
	}

	// search a fixed list of additional locations
	if (mikPath.isEmpty()) {
		static const QStringList candidates = QStringList() << "C:\\miktex\\miktex\\bin"
															<< "C:\\tex\\texmf\\miktex\\bin"
															<< "C:\\miktex\\bin"
															<< QString(qgetenv("LOCALAPPDATA")) + "\\Programs\\MiKTeX 2.9\\miktex\\bin";
		foreach (const QString &path, candidates)
			if (QDir(path).exists()) {
				mikPath = path;
				break;
			}
	}

    if(!mikPath.endsWith("\\")){
        mikPath.append("\\");
    }
	// post-process to detect 64bit installation
	if (!mikPath.isEmpty()) {
        if (QDir(mikPath + "x64\\").exists())
            return mikPath + "x64\\";
		else
			return mikPath;
	}
	return "";
}

static QString miktexBinPath = "<search>";
/*!
 * \return the MikTeX bin path. This uses caching so that the search is only performed once per session.
 */
QString getMiKTeXBinPath()
{
    if (miktexBinPath == "<search>") miktexBinPath = getMiKTeXBinPathInternal();
	return miktexBinPath;
}

/*!
 * Returns the TeXlive bin path.
 * This should not be called directly but only through getTeXLiveWinBinPath() to prevent multiple searches.
 */
QString getTeXLiveWinBinPathInternal()
{
	//check for uninstall entry
	foreach (const QString &baseKey, QStringList() << "HKEY_CURRENT_USER" << "HKEY_LOCAL_MACHINE") {
		QSettings reg(baseKey + "\\Software", QSettings::NativeFormat);
		QString uninstall;
		for (int v = 2017; v > 2008; v--) {
			uninstall = reg.value(QString("microsoft/windows/currentversion/uninstall/TeXLive%1/UninstallString").arg(v), "").toString();
			if (!uninstall.isEmpty()) {
				int p = uninstall.indexOf("\\tlpkg\\", 0, Qt::CaseInsensitive);
				QString path = p > 0 ? uninstall.left(p) : "";
				if (QDir(path + "\\bin\\win32").exists())
					return path + "\\bin\\win32\\";
			}
		}
	}
	//check for path
	QString pdftex = BuildManager::findFileInPath("pdftex.exe");
	int p = pdftex.indexOf("\\bin\\", 0, Qt::CaseInsensitive);
	if (p <= 0) return "";
	QString path = pdftex.left(p);
	if (!QFileInfo(path + "\\release-texlive.txt").exists()) return "";
	return path + "\\bin\\win32\\";
}

static QString texliveWinBinPath = "<search>";
/*!
 * \return the TeXlive bin path on windows. This uses caching so that the search is only performed once per session.
 */
QString getTeXLiveWinBinPath()
{
	if (texliveWinBinPath == "<search>") texliveWinBinPath = getTeXLiveWinBinPathInternal();
	return texliveWinBinPath;
}


QString findGhostscriptDLL()   //called dll, may also find an exe
{
	//registry
	foreach (QString program, QStringList() << "GPL Ghostscript" << "AFPL Ghostscript")
		foreach(QString hkeyBase, QStringList() << "HKEY_CURRENT_USER" << "HKEY_LOCAL_MACHINE") {
			QSettings reg(hkeyBase + "\\Software\\" + program, QSettings::NativeFormat);
			QStringList version = reg.childGroups();
			if (version.empty()) continue;
			version.sort();
			for (int i = version.size() - 1; i >= 0; i--) {
				QString dll = reg.value(version[i] + "/GS_DLL", "").toString();
				if (!dll.isEmpty()) return dll;
			}
		}
	//environment
	QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
	if (env.contains("GS_DLL")) {
		return env.value("GS_DLL");
	}
	//file search
	foreach (const QString &p, getProgramFilesPaths())
		if (QDir(p + "gs").exists())
			foreach (const QString &gsv, QDir(p + "gs").entryList(QStringList() << "gs*.*", QDir::Dirs, QDir::Time)) {
				QString x = p + "gs/" + gsv + "/bin/gswin32c.exe";
				if (QFile::exists(x)) return x;
			}
	return "";
}
#endif

QString searchBaseCommand(const QString &cmd, QString options)
{
	foreach(QString command, cmd.split(";")) {
		QString fileName = command   ON_WIN(+ ".exe");
		if (!options.startsWith(" ")) options = " " + options;
		if (!BuildManager::findFileInPath(fileName).isEmpty())
			return fileName + options; //found in path
		else {
			//platform dependent mess
#ifdef Q_OS_WIN32
			//Windows MikTex
			QString mikPath = getMiKTeXBinPath();
			if (!mikPath.isEmpty() && QFileInfo(mikPath + fileName).exists())
				return "\"" + mikPath + fileName + "\" " + options; //found
			//Windows TeX Live
			QString livePath = getTeXLiveWinBinPath();
			if (!livePath.isEmpty() && QFileInfo(livePath + fileName).exists())
				return "\"" + livePath + fileName + "\" " + options; //found
#endif
#ifdef Q_OS_MAC
			QStringList paths;
			paths << "/usr/bin/texbin/" << "/usr/local/bin/" << "/usr/texbin/" << "/Library/TeX/texbin/" << "/Library/TeX/local/bin/" ;
			paths << "/usr/local/teTeX/bin/i386-apple-darwin-current/" << "/usr/local/teTeX/bin/powerpc-apple-darwin-current/" << "/usr/local/teTeX/bin/x86_64-apple-darwin-current/";

			for (int i = 2013; i >= 2007; i--) {
				//paths << QString("/usr/texbin MACTEX/TEXLIVE%1").arg(i); from texmaker comment
				paths << QString("/usr/local/texlive/%1/bin/x86_64-darwin/").arg(i);
				paths << QString("/usr/local/texlive/%1/bin/i386-darwin/").arg(i);
				paths << QString("/usr/local/texlive/%1/bin/powerpc-darwin/").arg(i);
			}
			foreach (const QString &p, paths)
				if (QFileInfo(p + fileName).exists()) {
					if (cmd == "makeglossaries") {
						// workaround: makeglossaries calls makeindex or xindy and therefore has to be run in an environment that has these commands on the path
						return QString("sh -c \"PATH=$PATH:%1; %2%3\"").arg(p).arg(fileName).arg(options);
					} else {
						return p + fileName + options;
					}
				}
#endif
		}
	}
	return "";
}

ExpandedCommands BuildManager::expandCommandLine(const QString &str, ExpandingOptions &options)
{
	QRegExp re(QRegExp::escape(TXS_CMD_PREFIX) + "([^/ [{]+)(/?)((\\[[^\\]*]+\\]|\\{[^}]*\\})*) ?(.*)");

	options.nestingDeep++;
	if (options.canceled) return ExpandedCommands();
	if (options.nestingDeep > maxExpandingNestingDeep) {
		if (!UtilsUi::txsConfirmWarning(tr("The command has been expanded to %1 levels. Do you want to continue expanding \"%2\"?").arg(options.nestingDeep).arg(str))) {
			options.canceled = true;
			return ExpandedCommands();
		}
	}

	ExpandedCommands res;
	QStringList splitted = str.split("|");
	foreach (const QString &split, splitted) { //todo: ignore | in strings
		QString subcmd = split.trimmed();

		if (!subcmd.startsWith(TXS_CMD_PREFIX))  {
			RunCommandFlags  flags = getSingleCommandFlags(subcmd);

			if (options.override.removeAll)
				subcmd = CommandInfo::getProgramName(subcmd);
			if (!options.override.append.isEmpty())
				subcmd += " " + options.override.append.join(" "); //todo: simplify spaces???
			//Regexp matching parameters
			//Unescaped: .*(-abc(=([^ ]*|"([^"]|\"([^"])*\")*"))?).*
			//Doesn't support nesting deeper than \"
			static QString parameterMatching = "(=([^ ]*|\"([^\"]|\\\"([^\"])*\\\")*\"))?";
			for (int i = 0; i < options.override.remove.size(); i++) {
				const QString &rem = options.override.remove[i];
				QRegExp removalRegex(" (-?" + QRegExp::escape(rem) + (rem.contains("=") ? "" : parameterMatching) + ")");
				subcmd.replace(removalRegex, " ");
			}
			for (int i = 0; i < options.override.replace.size(); i++) {
				const QString &rem = options.override.replace[i].first;
				QRegExp replaceRegex(" (-?" + QRegExp::escape(rem) + parameterMatching + ")");
				int pos = replaceRegex.indexIn(subcmd);
				QString rep = " " + rem + options.override.replace[i].second;
				if (pos < 0) subcmd.insert(CommandInfo::getProgramName(subcmd).length(), rep);
				else {
					subcmd.replace(pos, replaceRegex.matchedLength(), rep);
					pos += rep.length();
					int newpos;
					while ( (newpos = replaceRegex.indexIn(subcmd, pos)) >= 0)
						subcmd.replace(newpos, replaceRegex.matchedLength(), " ");
				}
			}

			foreach (const QString &c, parseExtendedCommandLine(subcmd, options.mainFile, options.currentFile, options.currentLine)) {
				CommandToRun temp(c);
				temp.flags = flags;
				res.commands << temp;
			}
		} else if (re.exactMatch(subcmd)) {
			const QString &cmdName = re.cap(1);
			const QString &slash = re.cap(2);
			QString modifiers = re.cap(3);
			QString parameters = re.cap(5);
			if (slash != "/" && !modifiers.isEmpty()) {
				UtilsUi::txsInformation(tr("You have used txs:///command[... or txs:///command{... modifiers, but we only support modifiers of the form txs:///command/[... or txs:///command/{... with an slash suffix to keep the syntax purer."));
				modifiers.clear();
			}
            if (options.override.removeAll) {
                parameters.clear();
                modifiers.clear();
            }

			bool user;
			QString cmd = getCommandLine(cmdName, &user);
			if (cmd.isEmpty()) {
				if (options.nestingDeep == 1) UtilsUi::txsWarning(tr("Command %1 not defined").arg(subcmd));
				else if (cmdName != "pre-compile") qDebug() << tr("Command %1 not defined").arg(subcmd); //pre-compile is expecte
				if (cmdName != "pre-compile") {
					res.commands << CommandToRun(""); // add empty command to provoke an error on higher level. Otherwise the missing of the command is simply ignoed e.g. txs:/quick without empty pdflatex
					res.primaryCommand = "";
				}
				continue;
			}

			int space = cmd.indexOf(' ');
			if (space == -1) space = cmd.size();
			if (cmd.startsWith(TXS_CMD_PREFIX) && internalCommands.contains(cmd.left(space))) {
				res.commands << CommandToRun(cmd + " " + parameters);
				res.commands.last().parentCommand = res.commands.last().command;
				if (user) res.commands.last().flags |= RCF_CHANGE_PDF;
				continue;
			}

			//parse command modifiers
			bool removeAllActivated = false;
			int replacePrepended = 0, removePrepended = 0;
			if (!modifiers.isEmpty()) {
				//matching combinations like [-abc][-foo=bar]{-xasa...}
				QRegExp modifierRegexp("^((\\[([^=\\]]+)(=[^\\]]+)?\\])|(\\{([^}]*)\\}))");
				while (modifierRegexp.indexIn(modifiers) >= 0) {
					if (!modifierRegexp.cap(3).isEmpty()) {
						replacePrepended++;
						options.override.replace.prepend(QPair<QString, QString>(modifierRegexp.cap(3), modifierRegexp.cap(4)));
						//qDebug() << "replace >" << options.override.replace.first().first << "< with >"<<options.override.replace.first().second<<"<";
					} else if (!modifierRegexp.cap(5).isEmpty()) {
						if (modifierRegexp.cap(6).isEmpty()) {
							removeAllActivated = true; // qDebug() << "remove all";
						} else {
							removePrepended++;
							options.override.remove.prepend(modifierRegexp.cap(6));
							//qDebug() << "remove >" << options.override.remove.first() << "<";
						}
					}
					modifiers.remove(0, modifierRegexp.matchedLength());
				}
			}
			if (removeAllActivated) options.override.removeAll = true;
			if (!parameters.isEmpty()) options.override.append.prepend(parameters);
			//todo /(masterfile,currentfile) modifier ?

			//recurse
			ExpandedCommands ecNew = expandCommandLine(cmd, options);
			if (ecNew.commands.length() > 1 && atomicCommands.contains(cmd)) {
				UtilsUi::txsWarning(QString(tr("The command %1 is expected to be atomic. However, it is currently "
				                      "defined as a command-chain containing %2 commands. This is beyond "
				                      "the specification and may lead to surprising side-effects.\n\n"
				                      "Please change your configuration and define command lists only at "
				                      "'Options -> Configure TeXstudio -> Build' not at "
				                      "'Options -> Configure TeXstudio -> Commands'.")).arg(cmd).arg(ecNew.commands.length()));
			}
			QList<CommandToRun> &newPart = ecNew.commands;

			//clean up modifiers
			if (removeAllActivated) options.override.removeAll = false;
			if (!parameters.isEmpty()) options.override.append.removeFirst();
			for (; replacePrepended > 0; replacePrepended--) options.override.replace.removeFirst();
			for (; removePrepended > 0; removePrepended--) options.override.remove.removeFirst();

			if (newPart.isEmpty()) continue;

			if (commands.value(cmdName).rerunCompiler)
				for (int i = 0; i < newPart.size(); i++)
					newPart[i].flags |= RCF_RERUN;

			for (int i = 0; i < newPart.size(); i++)
				if (newPart[i].parentCommand.isEmpty()) {
					newPart[i].parentCommand = cmdName;
					if (user) {
						newPart[i].flags |= RCF_SHOW_STDOUT;
						newPart[i].flags |= RCF_CHANGE_PDF;
					}
				}

			if (splitted.size() == 1)
				res.primaryCommand = cmdName;

			res.commands << newPart;
		} else UtilsUi::txsWarning(tr("Failed to understand command %1").arg(subcmd));
	}
	options.nestingDeep--;
	return res;
}

bool similarCommandInList(const QString &cmd, const QStringList &list)
{
	if (list.contains(cmd)) return true;
	//compare the executable base name with all base names in the list
	//(could be made faster by caching the list base names, but it is not really an issue)
	QString fullCmd = CommandInfo::getProgramNameUnquoted(cmd).replace(QDir::separator(), '/');
#ifdef Q_OS_WIN
	fullCmd = fullCmd.toLower();
	if (fullCmd.endsWith(".exe")) fullCmd = fullCmd.left(fullCmd.length() - 4);
#endif
	int lastPathSep = fullCmd.lastIndexOf('/');
	QString relCmd = lastPathSep < 0 ? fullCmd : fullCmd.mid(lastPathSep + 1);
	foreach (const QString &listCmd, list) {
		QString fullListCmd = CommandInfo::getProgramNameUnquoted(listCmd).replace(QDir::separator(), '/');
#ifdef Q_OS_WIN
		fullListCmd = fullListCmd.toLower();
		if (fullListCmd.endsWith(".exe")) fullListCmd = fullListCmd.left(fullListCmd.length() - 4);
#endif
		if (fullCmd == fullListCmd) return true;
		int lastPathSepListCmd = fullListCmd.lastIndexOf('/');
		QString relListCmd = lastPathSepListCmd < 0 ? fullListCmd : fullListCmd.mid(lastPathSepListCmd + 1);
		if (lastPathSep < 0 || lastPathSepListCmd < 0) //do not compare relative, if both are absolute paths
			if (relCmd == relListCmd) return true;
	}
	return false;
}

RunCommandFlags BuildManager::getSingleCommandFlags(const QString &subcmd) const
{
	int result = 0;
	if (similarCommandInList(subcmd, latexCommands)) result |= RCF_COMPILES_TEX;
	if (similarCommandInList(subcmd, pdfCommands)) result |= RCF_CHANGE_PDF;
	if (rerunnableCommands.contains(subcmd)) result |= RCF_RERUNNABLE;
	if (stdoutCommands.contains(subcmd)) result |= RCF_SHOW_STDOUT;
	bool isAcrobat = false;
#ifdef Q_OS_WIN
	isAcrobat = subcmd.contains("Acrobat.exe") || subcmd.contains("AcroRd32.exe");
#endif

	if (viewerCommands.contains(subcmd) && !isAcrobat && singleViewerInstance) result |= RCF_SINGLE_INSTANCE;
    return static_cast<RunCommandFlags>(result);
}

bool BuildManager::hasCommandLine(const QString &program)
{
	for (CommandMapping::const_iterator it = commands.constBegin(), end = commands.constEnd(); it != end; ++it)
		if (it.value().commandLine == program) return true;
	return false;
}

#if defined(Q_OS_MAC)

QString getCommandLineViewDvi()
{
	return "open %.dvi > /dev/null";
}

QString getCommandLineViewPs()
{
	return "open %.ps > /dev/null";
}

QString getCommandLineViewPdfExternal()
{
	return "open %.pdf > /dev/null";
}

QString getCommandLineGhostscript()
{
	return "";
}

#elif defined(Q_OS_WIN32)

QString getCommandLineViewDvi()
{
	const QString yapOptions = " -1 -s @?\"c:ame \"?am.dvi\"";
	QString def = W32_FileAssociation(".dvi");
	if (!def.isEmpty()) {
		if (def.contains("yap.exe")) {
			def = def.trimmed();
			if (def.endsWith("\"?am.dvi\"")) {
				def.replace("\"?am.dvi\"", yapOptions);
			} else if (def.endsWith("?am.dvi")) {
				def.replace("?am.dvi", yapOptions);
			} else if (def.endsWith(" /dde")) {
				def.replace(" /dde", yapOptions);
			}
		}
		return def;
	}
	def = searchBaseCommand("yap", yapOptions); //miktex
	if (!def.isEmpty()) return def;
	def = searchBaseCommand("dviout", "%.dvi"); //texlive
	if (!def.isEmpty()) return def;

	if (QFileInfo("C:/texmf/miktex/bin/yap.exe").exists())
		return "C:/texmf/miktex/bin/yap.exe " + yapOptions;

	return "";
}

QString getCommandLineViewPs()
{
	QString def = W32_FileAssociation(".ps");
	if (!def.isEmpty())
		return def;

	QString livePath = getTeXLiveWinBinPath();
	if (!livePath.isEmpty())
		if (QFileInfo(livePath + "psv.exe").exists())
			return "\"" + livePath + "psv.exe\"  \"?am.ps\"";


	QString gsDll = findGhostscriptDLL().replace("/", "\\"); //gsview contains gs so x
	int pos;
	while ((pos = gsDll.lastIndexOf("\\")) > -1) {
		gsDll = gsDll.mid(0, pos + 1);
		if (QFileInfo(gsDll + "gsview32.exe").exists())
			return "\"" + gsDll + "gsview32.exe\" -e \"?am.ps\"";
		if (QFileInfo(gsDll + "gsview.exe").exists())
			return "\"" + gsDll + "gsview.exe\" -e \"?am.ps\"";
		gsDll = gsDll.mid(0, pos);
	}

	foreach (const QString &p, getProgramFilesPaths())
		if (QFile::exists(p + "Ghostgum/gsview/gsview32.exe"))
			return "\"" + p + "Ghostgum/gsview/gsview32.exe\" -e \"?am.ps\"";
	return "";
}

QString getCommandLineViewPdfExternal()
{
	QString def = W32_FileAssociation(".pdf");
	if (!def.isEmpty())
		return def;

	foreach (const QString &p, getProgramFilesPaths())
		if (QDir(p + "Adobe").exists())
			foreach (const QString &rv, QDir(p + "Adobe").entryList(QStringList() << "Reader*", QDir::Dirs, QDir::Time)) {
				QString x = p + "Adobe/" + rv + "/Reader/AcroRd32.exe";
				if (QFile::exists(x)) return "\"" + x + "\" \"?am.pdf\"";
			}
	return "";
}

QString getCommandLineGhostscript()
{
	const QString gsArgs = " \"?am.ps\"";
	QString livePath = getTeXLiveWinBinPath();
	if (!livePath.isEmpty()) {
		if (QFileInfo(livePath + "rungs.exe").exists())
			return "\"" + livePath + "rungs.exe\"" + gsArgs;
		if (QFileInfo(livePath + "rungs.bat").exists()) //tl 2008 (?)
			return "\"" + livePath + "rungs.bat\"" + gsArgs;
	}
	QString dll = findGhostscriptDLL().replace("gsdll32.dll", "gswin32c.exe", Qt::CaseInsensitive);
	if (dll.endsWith("gswin32c.exe")) return "\"" + dll + "\"" + gsArgs;
	else if (QFileInfo("C:/Program Files/gs/gs8.64/bin/gswin32c.exe").exists())  //old behaviour
		return "\"C:/Program Files/gs/gs8.64/bin/gswin32c.exe\"" + gsArgs;
	else if (QFileInfo("C:/Program Files/gs/gs8.63/bin/gswin32c.exe").exists())  //old behaviour
		return "\"C:/Program Files/gs/gs8.63/bin/gswin32c.exe\"" + gsArgs;
	else if (QFileInfo("C:/Program Files/gs/gs8.61/bin/gswin32c.exe").exists())
		return "\"C:/Program Files/gs/gs8.61/bin/gswin32c.exe\"" + gsArgs;
	return "";
}

#elif defined(Q_WS_X11) || defined(Q_OS_LINUX)

// xdvi %.dvi  -sourceposition @:%.tex
// kdvi "file:%.dvi#src:@ %.tex"
QString getCommandLineViewDvi()
{
	return "xdg-open %.dvi > /dev/null";
}

QString getCommandLineViewPs()
{
	return "xdg-open %.ps > /dev/null";
}

QString getCommandLineViewPdfExternal()
{
	return "xdg-open %.pdf > /dev/null";
}

QString getCommandLineGhostscript()
{
	return "";
}

#else

#warning Unrecognized OS. Default viewers will probably be wrong

QString getCommandLineViewDvi()
{
	return "xdvi %.dvi > /dev/null";
}

QString getCommandLineViewPs()
{
	return "gv %.ps > /dev/null";
}

QString getCommandLineViewPdfExternal()
{
	return "xpdf %.pdf > /dev/null";
}

QString getCommandLineGhostscript()
{
	return "";
}

#endif


bool BuildManager_hadSuccessfulProcessStart;

void BuildManager::registerOptions(ConfigManagerInterface &cmi)
{
	cmi.registerOption("Tools/Quick Mode", &deprecatedQuickmode, -1);
	cmi.registerOption("Tools/Max Expanding Nesting Deep", &maxExpandingNestingDeep, 10);
	Q_ASSERT(sizeof(dvi2pngMode) == sizeof(int));
    cmi.registerOption("Tools/Dvi2Png Mode", reinterpret_cast<int *>(&dvi2pngMode), 3);
    cmi.registerOption("Files/Save Files Before Compiling", reinterpret_cast<int *>(&saveFilesBeforeCompiling), static_cast<int>(SFBC_ONLY_NAMED));
	cmi.registerOption("Preview/Remove Beamer Class", &previewRemoveBeamer, true);
	cmi.registerOption("Preview/Precompile Preamble", &previewPrecompilePreamble, true);

	cmi.registerOption("Tools/Automatic Rerun Commands", &autoRerunCommands, "compile|latex|pdflatex|lualatex|xelatex");

	cmi.registerOption("User/ToolNames", &deprecatedUserToolNames, QStringList());
	cmi.registerOption("User/Tools", &deprecatedUserToolCommands, QStringList());

	cmi.registerOption("Tools/Display Names", &userToolDisplayNames, QStringList());
	cmi.registerOption("Tools/User Order", &userToolOrder, QStringList());
	cmi.registerOption("Tools/Preview Compile Time Out", &previewCompileTimeOut, 15000); //hidden option, 15s predefined

	cmi.registerOption("Tools/Had Successful Process Start", &BuildManager_hadSuccessfulProcessStart, false);
}

void removeDuplicateUserTools(QStringList &userToolOrder, QStringList &userToolDisplayNames)
{
	// workaround to cleanup duplicates in usertools https://sourceforge.net/p/texstudio/discussion/907839/
	// needed for some time even after that fix will be in place to catch the duplicates already created by previous versions
	int i = 0;
	QSet<QString> visitedTools;
	while (i < qMin(userToolOrder.size(), userToolDisplayNames.size())) {
		QString tool = userToolOrder[i];
		if (visitedTools.contains(tool)) {
			userToolOrder.removeAt(i);
			userToolDisplayNames.removeAt(i);
		} else {
			visitedTools.insert(tool);
			i++;
		}
	}
}

void BuildManager::readSettings(QSettings &settings)
{
	QStringList rerunCommandsUnexpanded = autoRerunCommands.split("|");
	for (int i = 0; i < rerunCommandsUnexpanded.size(); i++)
		if (rerunCommandsUnexpanded[i].startsWith(TXS_CMD_PREFIX))
			rerunCommandsUnexpanded[i] = rerunCommandsUnexpanded[i].mid(TXS_CMD_PREFIX.size());

	removeDuplicateUserTools(userToolOrder, userToolDisplayNames);
	settings.beginGroup("Tools");
	settings.beginGroup("Commands");
	QStringList cmds = settings.childKeys();

	checkOSXElCapitanDeprecatedPaths(settings, cmds);

	foreach (const QString &id, cmds) {
		QString cmd = settings.value(id).toString();
		CommandMapping::iterator it = commands.find(id);
		if (it == commands.end()) {
			// command not known by default -> user command
			QString displayName(id);
			int idx = userToolOrder.indexOf(id);
			if (idx >= 0 && idx < userToolDisplayNames.length()) {
				displayName = userToolDisplayNames[idx];
			}
            registerCommand(id, "", displayName, "", "", nullptr, true).commandLine = cmd;
		} else {
			// default command
			it.value().commandLine = cmd;
		}
	}
	settings.endGroup();
	settings.endGroup();

	//import old or choose default
	for (CommandMapping::iterator it = commands.begin(), end = commands.end(); it != end; ++it) {
		CommandInfo &cmd = it.value();
		cmd.rerunCompiler = rerunCommandsUnexpanded.contains(cmd.id);
		if (!cmd.commandLine.isEmpty()) continue;
		if (!cmd.deprecatedConfigName.isEmpty()) {
			QString import = settings.value(it.value().deprecatedConfigName).toString();
			if (cmd.id == "quick") {
				if (deprecatedQuickmode == 8)
					cmd.commandLine = import;
			} else if (cmd.id == "view-pdf-external") {
				if (import.startsWith(DEPRECACTED_TMX_INTERNAL_PDF_VIEWER)) {
					import.remove(0, DEPRECACTED_TMX_INTERNAL_PDF_VIEWER.length() + 1);
					cmd.commandLine = import;
					commands.find("view-pdf").value().commandLine = CMD_VIEW_PDF_INTERNAL + " --embedded";
				} else {
					cmd.commandLine = import;
					commands.find("view-pdf").value().commandLine = CMD_VIEW_PDF_INTERNAL + " --embedded";
				}
			} else cmd.commandLine = import;
		}
		if (!cmd.commandLine.isEmpty()) continue;
		if (cmd.id == "quick") {
			if (deprecatedQuickmode >= 1 && deprecatedQuickmode < cmd.metaSuggestionList.size() )
				cmd.commandLine = cmd.metaSuggestionList[deprecatedQuickmode];
			continue;
		}
		cmd.commandLine = cmd.guessCommandLine();
	}
	if (commands.value("quick").commandLine.isEmpty()) {
		//Choose suggestion that actually exists
		CommandInfo &quick = commands.find("quick").value();
		for (int i = 0; i < quick.metaSuggestionList.size() - 1; i++) {
			QString referenced = quick.metaSuggestionList[i];
			if (referenced.isEmpty()) continue;
			QStringList subCommands = referenced.split("|");
			bool hasAll = true;
			foreach (const QString &s, subCommands) {
				QString trimmed = s.trimmed();
				trimmed.remove(0, TXS_CMD_PREFIX.length());
				if (commands.value(trimmed).commandLine.isEmpty()) {
					hasAll = false;
					break;
				}
			}
			if (hasAll) {
				quick.commandLine = quick.metaSuggestionList[i];
				break;
			}
		}
		deprecatedQuickmode = -2;
	}
	//import old
	for (int i = 0; i < qMin(deprecatedUserToolNames.size(), deprecatedUserToolCommands.size()); i++)
		if (!deprecatedUserToolNames[i].endsWith("!!!CONVERTED!!!")) {
			QString cmd = deprecatedUserToolCommands[i];
			cmd.replace(DEPRECACTED_TMX_INTERNAL_PDF_VIEWER, CMD_VIEW_PDF_INTERNAL);
            CommandInfo &ci = registerCommand(QString("user%1").arg(i), "", deprecatedUserToolNames[i], "", "", nullptr, true);
			ci.commandLine = cmd;
			userToolOrder << ci.id;
			userToolDisplayNames << ci.displayName;
			deprecatedUserToolNames[i] = deprecatedUserToolNames[i] + "!!!CONVERTED!!!";
		}
	//import very old
	for (int i = 1; i <= 5; i++) {
		QString temp = settings.value(QString("User/Tool%1").arg(i), "").toString();
		if (!temp.isEmpty()) {
			temp.replace(DEPRECACTED_TMX_INTERNAL_PDF_VIEWER, CMD_VIEW_PDF_INTERNAL);
            CommandInfo &ci = registerCommand(QString("userold%1").arg(i), "", settings.value(QString("User/ToolName%1").arg(i)).toString(), "", "", nullptr, true);
			ci.commandLine  = temp;
			userToolOrder << ci.id;
			userToolDisplayNames << ci.displayName;
			settings.remove(QString("User/Tool%1").arg(i));
			settings.remove(QString("User/ToolName%1").arg(i));
		}
	}
    int md = dvi2pngMode;
#ifdef NO_POPPLER_PREVIEW
	if (md == DPM_EMBEDDED_PDF)
		md = -1;
#endif
	if (md < 0) {
		if (isCommandDirectlyDefined(CMD_DVIPNG)) dvi2pngMode = DPM_DVIPNG; //best/fastest mode
		else if (isCommandDirectlyDefined(CMD_DVIPS) && isCommandDirectlyDefined(CMD_GS)) dvi2pngMode = DPM_DVIPS_GHOSTSCRIPT; //compatible mode
		else dvi2pngMode = DPM_DVIPNG; //won't work
	}

	setAllCommands(commands, userToolOrder);
}

void BuildManager::saveSettings(QSettings &settings)
{
	QStringList order = getCommandsOrder();
	userToolOrder.clear();
	userToolDisplayNames.clear();
	settings.beginGroup("Tools");
	settings.beginGroup("Commands");
	settings.remove("");
	QStringList rerunCmds;
	for (int i = 0; i < order.size(); i++) {
		CommandMapping::iterator it = commands.find(order[i]);
		if (it == commands.end()) continue;
		settings.setValue(it->id, it->commandLine);
		if (it->user) {
			userToolDisplayNames << it->displayName;
			userToolOrder << it->id;
		}
		if (it->rerunCompiler) {
			rerunCmds << it->id;
		}
	}
	autoRerunCommands = rerunCmds.join("|");
	settings.endGroup();
	settings.endGroup();
}

void BuildManager::checkLatexConfiguration(bool &noWarnAgain)
{
	if (commands.contains("pdflatex") && commands["pdflatex"].commandLine.isEmpty()) {
		QString message = tr("No LaTeX distribution was found on your system. As a result, the corresponding commands are not configured. This means, that you cannot compile your documents to the desired output format (e.g. pdf).");

#ifdef Q_OS_WIN
		message += "<br><br>"
		           + tr("Popular LaTeX distributions on windows are %1 and %2.").arg("<a href='http://miktex.org/'>MikTeX</a>").arg("<a href='https://www.tug.org/texlive/'>TeXLive</a>")
		           + "<br><br>"
		           + tr("If you intend to work with LaTeX, you'll most certainly want to install one of those.");
#elif defined(Q_OS_MAC)
		message += "<br><br>"
		           + tr("A popular LaTeX distribution on OSX is %1.").arg("<a href='https://tug.org/mactex/'>MacTeX</a>")
		           + "<br><br>"
		           + tr("If you intend to work with LaTeX, you'll most certainly want to install it.");
#else
		message += "<br><br>"
		           + tr("If you intend to work with LaTeX, you'll most certainly want to install a LaTeX distribution.");
#endif
		UtilsUi::txsWarning(message, noWarnAgain);
	}
}

bool BuildManager::runCommand(const QString &unparsedCommandLine, const QFileInfo &mainFile, const QFileInfo &currentFile, int currentLine, QString *buffer, QTextCodec *codecForBuffer )
{
	if (waitingForProcess()) return false;

    emit clearLogs();

	if (unparsedCommandLine.isEmpty()) {
		emit processNotification(tr("Error: No command given"));
		return false;
	}
	ExpandingOptions options(mainFile, currentFile, currentLine);
	ExpandedCommands expansion = expandCommandLine(unparsedCommandLine, options);
	if (options.canceled) return false;
	if (!checkExpandedCommands(expansion)) return false;

	bool latexCompiled = false, pdfChanged = false;
	for (int i = 0; i < expansion.commands.size(); i++) {
		latexCompiled |= expansion.commands[i].flags & RCF_COMPILES_TEX;
		pdfChanged |= expansion.commands[i].flags & RCF_CHANGE_PDF;
		if (buffer || i != expansion.commands.size() - 1)
			expansion.commands[i].flags |= RCF_WAITFORFINISHED; // don't let buffer be destroyed before command is finished
	}
	if (latexCompiled) {
		ExpandedCommands temp = expandCommandLine(CMD_INTERNAL_PRE_COMPILE, options);
		for (int i = temp.commands.size() - 1; i >= 0; i--) expansion.commands.prepend(temp.commands[i]);
	}

	bool asyncPdf = !(expansion.commands.last().flags & RCF_WAITFORFINISHED) && (expansion.commands.last().flags & RCF_CHANGE_PDF);

	emit beginRunningCommands(expansion.primaryCommand, latexCompiled, pdfChanged, asyncPdf);
	bool result = runCommandInternal(expansion, mainFile, buffer, codecForBuffer);
	emit endRunningCommands(expansion.primaryCommand, latexCompiled, pdfChanged, asyncPdf);
	return result;
}

bool BuildManager::checkExpandedCommands(const ExpandedCommands &expansion)
{
	if (expansion.commands.isEmpty()) {
		emit processNotification(tr("Error: No command expanded"));
		if (!BuildManager_hadSuccessfulProcessStart) {
			emit processNotification("<br>" + tr("<b>Make sure that you have installed a (La)TeX distribution</b> e.g. MiKTeX or TeX Live, and have set the correct paths to this distribution on the command configuration page.<br>"
			                                     "A (La)TeX editor like TeXstudio cannot work without the (La)TeX commands provided by such a distribution."));
		}
		return false;
	}

	// check if one command in the list is empty (expansion produced an error, e.g. txs:quick and compile is undefined
	foreach (const CommandToRun elem, expansion.commands) {
		if (elem.command.isEmpty()) {
			emit processNotification(tr("Error: One command expansion invalid.") +
			                         QString("\n    %1: %2").arg(tr("Parent Command"), elem.parentCommand) +
			                         QString("\n    %1: %2").arg(tr("Primary Command"), expansion.primaryCommand));
			if (!BuildManager_hadSuccessfulProcessStart) {
				emit processNotification("<br>" + tr("<b>Make sure that you have installed a (La)TeX distribution</b> e.g. MiKTeX or TeX Live, and have set the correct paths to this distribution on the command configuration page.<br>"
				                                     "A (La)TeX editor like TeXstudio cannot work without the (La)TeX commands provided by such a distribution."));
			}
			return false;
		}
	}
	return true;
}

bool BuildManager::runCommandInternal(const ExpandedCommands &expandedCommands, const QFileInfo &mainFile, QString *buffer, QTextCodec *codecForBuffer)
{
	const QList<CommandToRun> &commands = expandedCommands.commands;

	int remainingReRunCount = autoRerunLatex;
	for (int i = 0; i < commands.size(); i++) {
		CommandToRun cur = commands[i];
		if (testAndRunInternalCommand(cur.command, mainFile))
			continue;

		bool singleInstance = cur.flags & RCF_SINGLE_INSTANCE;
		if (singleInstance && runningCommands.contains(cur.command)) continue;
		bool latexCompiler = cur.flags & RCF_COMPILES_TEX;
		bool lastCommandToRun = i == commands.size() - 1;
		bool waitForCommand = latexCompiler || (!lastCommandToRun && !singleInstance) || cur.flags & RCF_WAITFORFINISHED;

		ProcessX *p = newProcessInternal(cur.command, mainFile, singleInstance);
		REQUIRE_RET(p, false);
		p->subCommandName = cur.parentCommand;
		p->subCommandPrimary = expandedCommands.primaryCommand;
		p->subCommandFlags = cur.flags;
		connect(p, SIGNAL(finished(int)), SLOT(emitEndRunningSubCommandFromProcessX(int)));


		p->setStdoutBuffer(buffer);
		p->setStdoutCodec(codecForBuffer);

		emit beginRunningSubCommand(p, expandedCommands.primaryCommand, cur.parentCommand, cur.flags);

		if (!waitForCommand) connect(p, SIGNAL(finished(int)), p, SLOT(deleteLater()));

		p->startCommand();
		if (!p->waitForStarted(1000)) return false;

		if (latexCompiler || (!lastCommandToRun && !singleInstance) )
			if (!waitForProcess(p)) {
				p->deleteLater();
				return false;
			}

		if (waitForCommand) { //what is this? does not really make any sense (waiting is done in the block above) and breaks multiple single-instance pdf viewer calls (30 sec delay)
			p->waitForFinished();
			p->deleteLater();
		}

		bool rerunnable = (cur.flags & RCF_RERUN) && (cur.flags & RCF_RERUNNABLE);
		if (rerunnable || latexCompiler) {
			LatexCompileResult result = LCR_NORMAL;
			emit latexCompiled(&result);
			if (result == LCR_ERROR) return false;
			if (result == LCR_NORMAL || !rerunnable) continue;
			if (remainingReRunCount <= 0) continue; //do not abort since the rerun condition might have been trigged accidentally
			if (result == LCR_RERUN_WITH_BIBLIOGRAPHY) {
				QString tempWaitForFinished; //if it does not wait on bibtex it will fail
				runCommand(CMD_BIBLIOGRAPHY, mainFile, mainFile, 0, &tempWaitForFinished);
				remainingReRunCount--;
			}
			REQUIRE_RET(result == LCR_RERUN || result == LCR_RERUN_WITH_BIBLIOGRAPHY, false);
			remainingReRunCount--;
			i--; //rerun
			//qDebug() << "rerun";
		}

	}
	return true;
}

void BuildManager::emitEndRunningSubCommandFromProcessX(int)
{
	ProcessX *p = qobject_cast<ProcessX *>(sender());
	REQUIRE(p); //p can be NULL (although sender() is not null) ! If multiple single instance viewers are in a command. Why? should not happen
	emit endRunningSubCommand(p, p->subCommandPrimary, p->subCommandName, p->subCommandFlags);
}


ProcessX *BuildManager::firstProcessOfDirectExpansion(const QString &command, const QFileInfo &mainFile, const QFileInfo &currentFile, int currentLine,bool nonstop)
{
	ExpandingOptions options(mainFile, currentFile, currentLine);
    if(nonstop){
        options.nestingDeep=1; // tweak to avoid pop-up error messages
    }
	ExpandedCommands expansion = expandCommandLine(command, options);
    if (options.canceled) return nullptr;

    if (expansion.commands.isEmpty()) { return nullptr; }

    foreach(CommandToRun elem,expansion.commands){
        if(elem.command.isEmpty()){
            return nullptr; // error in command expansion
        }

    }

	return newProcessInternal(expansion.commands.first().command, mainFile);
}

//don't use this
ProcessX *BuildManager::newProcessInternal(const QString &cmd, const QFileInfo &mainFile, bool singleInstance)
{
	if (singleInstance && runningCommands.contains(cmd))
        return nullptr;

	ProcessX *proc = new ProcessX(this, cmd, mainFile.absoluteFilePath());
	connect(proc, SIGNAL(processNotification(QString)), SIGNAL(processNotification(QString)));
	if (singleInstance) {
		connect(proc, SIGNAL(finished(int)), SLOT(singleInstanceCompleted(int))); //will free proc after the process has ended
		runningCommands.insert(cmd, proc);
	}
	if (!mainFile.fileName().isEmpty())
		proc->setWorkingDirectory(mainFile.absolutePath());
	if (cmd.startsWith(TXS_CMD_PREFIX))
		connect(proc, SIGNAL(startedX()), SLOT(runInternalCommandThroughProcessX()));

	updatePathSettings(proc, resolvePaths(additionalSearchPaths));
	return proc;
}

bool BuildManager::waitForProcess(ProcessX *p)
{
	REQUIRE_RET(!processWaitedFor, false);
	processWaitedFor = p;
	m_stopBuildAction->setEnabled(true);
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	QTime time;
	time.start();
	while (p && p->isRunning()) {
		if (time.elapsed() > 2000)
			qApp->instance()->processEvents(QEventLoop::AllEvents);
		else
			qApp->instance()->processEvents(QEventLoop::ExcludeUserInputEvents);
		// workaround for high CPU consumption when waiting
		// TODO: replace this loop by notification mechansim
		ThreadBreaker::msleep(1);
	}
	QApplication::restoreOverrideCursor();
	bool result = processWaitedFor;
    processWaitedFor = nullptr;
	m_stopBuildAction->setEnabled(false);
	return result;
}

bool BuildManager::waitingForProcess() const
{
	return processWaitedFor;
}

void BuildManager::killCurrentProcess()
{
	if (!processWaitedFor) return;
	processWaitedFor->kill();
    processWaitedFor = nullptr;
}

QString BuildManager::createTemporaryFileName()
{
	QTemporaryFile *temp = new QTemporaryFile(QDir::tempPath () + "/texstudio_XXXXXX.tex");
	temp->open();
	temp->setAutoRemove(false);
	QString tempName = temp->fileName();
	delete temp;
	return tempName;
}

void addLaTeXInputPaths(ProcessX *p, const QStringList &paths)
{
	if (paths.isEmpty()) return;
	static const QString SEP = ON_WIN(";") ON_NIX(":");
	static const QStringList envNames = QStringList() << "TEXINPUTS" << "BIBINPUTS" << "BSTINPUTS" << "MFINPUTS" << "MPINPUTS" << "TFMFONTS";
	QString addPath = paths.join(SEP) + SEP + "." + SEP;
	QStringList env = p->environment();
	env << QProcess::systemEnvironment();
	foreach (const QString &envname, envNames) {
		bool found = false;
		for (int i = 0; i < env.size(); i++)
			if (env[i].startsWith(envname + "=")) {
				found = true;
				env[i] = env[i] + SEP + addPath;
				break;
			}
		if (!found)
			env.append(envname + "=" + addPath);
	}
	p->setOverrideEnvironment(env);
}

//there are 3 ways to generate a preview png:
//1. latex is called => dvipng is called after latex finished and converts the dvi
//2. latex is called and dvipng --follow is called at the same time, and will manage the wait time on its own
//3. latex is called => dvips converts .dvi to .ps => ghostscript is called and created final png
//Then ghostscript to convert it to
void BuildManager::preview(const QString &preamble, const PreviewSource &source, const QString &masterFile, QTextCodec *outputCodec)
{
	QString tempPath = QDir::tempPath() + QDir::separator() + "." + QDir::separator();

	//process preamble
	QString preamble_mod = preamble;
	static const QRegExp beamerClass("^(\\s*%[^\\n]*\\n)*\\s*\\\\documentclass(\\[[^\\]]*\\])?\\{beamer\\}"); //detect the usage of the beamer class
	if (previewRemoveBeamer && preamble_mod.contains(beamerClass)) {
		//dvipng is very slow (>14s) and ghostscript is slow (1.4s) when handling beamer documents,
		//after setting the class to article dvipng runs in 77ms
		preamble_mod.remove(beamerClass);
		preamble_mod.insert(0, "\\documentclass{article}\n\\usepackage{beamerarticle}");
	}

	QString masterDir = QFileInfo(masterFile).dir().absolutePath();
	QStringList addPaths;
	addPaths << masterDir;
	if (preamble_mod.contains("\\usepackage{import}")) {
		QStringList imports = regExpFindAllMatches(preamble_mod, QRegExp("\\\\subimport\\{([^}\n]*)\\}\\{[^}\n]*\\}"), 1);
		imports.sort();
		for (int i = imports.size() - 1; i > 0; i--)
			if (imports[i] == imports[i - 1]) imports.removeAt(i);
		foreach (const QString &dir, imports)
			addPaths << masterDir + QDir::separator() + dir;
	}

	QString preambleFormatFile;
	if (previewPrecompilePreamble) {
		preambleFormatFile = preambleHash.value(preamble_mod, "");
		if (preambleFormatFile != "<failed>") {
			if (!preambleFormatFile.isEmpty())
				if (!QFile::exists(tempPath + preambleFormatFile + ".fmt"))
					preambleFormatFile = "";
			if (preambleFormatFile.isEmpty()) {
				//write preamble
				QTemporaryFile *tf = new QTemporaryFile(tempPath + "hXXXXXX.tex");
				REQUIRE(tf);
				tf->open();
				QTextStream out(tf);
				if (outputCodec) out.setCodec(outputCodec);
				out << preamble_mod;
				tf->setAutoRemove(false);
				tf->close();

				//compile
				QFileInfo fi(*tf);
				preambleFormatFile = fi.completeBaseName();
				previewFileNames.append(fi.absoluteFilePath());
                ProcessX *p = nullptr;
				if (dvi2pngMode == DPM_EMBEDDED_PDF) {
					p = newProcessInternal(QString("%1 -interaction=nonstopmode -ini \"&pdflatex %3 \\dump\"").arg(getCommandInfo(CMD_PDFLATEX).getProgramName()).arg(preambleFormatFile), tf->fileName()); //no delete! goes automatically
				} else {
					p = newProcessInternal(QString("%1 -interaction=nonstopmode -ini \"&latex %3 \\dump\"").arg(getCommandInfo(CMD_LATEX).getProgramName()).arg(preambleFormatFile), tf->fileName()); //no delete! goes automatically
				}

				REQUIRE(p);
				addLaTeXInputPaths(p, addPaths);
				p->setProperty("preamble", preamble_mod);
				p->setProperty("preambleFile", preambleFormatFile);
				connect(p, SIGNAL(finished(int)), this, SLOT(preamblePrecompileCompleted(int)));
				connect(p, SIGNAL(finished(int)), p, SLOT(deleteLater()));
				tf->setParent(p); //free file when process is deleted

				p->startCommand();

				if (p->waitForStarted()) {
					if (p->waitForFinished(800)) {
						if (p->exitStatus() == QProcess::NormalExit && p->exitCode() == 0) {
							preambleHash.insert(preamble_mod, preambleFormatFile);
						} else {
							preambleHash.insert(preamble_mod, "<failed>");
							preambleFormatFile = "";
						}
					} else
						preambleFormatFile = ""; //wait + normal compile while waiting

				} else preambleFormatFile = ""; //compiling failed
				//delete tf; // tex file needs to be freed
			}
		} else preambleFormatFile = "";
	}

	// write to temp file
	// (place /./ after the temporary directory because it fails otherwise with qt4.3 on win and the tempdir "t:")
	QTemporaryFile *tf = new QTemporaryFile(tempPath + "XXXXXX.tex");
	if (!tf) return;
	tf->open();

	QTextStream out(tf);
	if (outputCodec) out.setCodec(outputCodec);
	if (preambleFormatFile.isEmpty()) out << preamble_mod;
	else out << "%&" << preambleFormatFile << "\n";
	out << "\n\\begin{document}\n" << source.text << "\n\\end{document}\n";
	// prepare commands/filenames
	QFileInfo fi(*tf);
	QString ffn = fi.absoluteFilePath();
	previewFileNames.append(ffn);
	previewFileNameToSource.insert(ffn, source);
	tf->setAutoRemove(false);
	tf->close();
	delete tf; // tex file needs to be freed
    ProcessX *p1 = nullptr;
	if (dvi2pngMode == DPM_EMBEDDED_PDF) {
		// start conversion
		// tex -> dvi
		p1 = firstProcessOfDirectExpansion(CMD_PDFLATEX, QFileInfo(ffn)); //no delete! goes automatically
	} else {
		// start conversion
		// tex -> dvi
		p1 = firstProcessOfDirectExpansion(CMD_LATEX, QFileInfo(ffn)); //no delete! goes automatically
	}
	if (!p1) return; // command failed, not set ?
	addLaTeXInputPaths(p1, addPaths);
	connect(p1, SIGNAL(finished(int)), this, SLOT(latexPreviewCompleted(int)));
	p1->startCommand();
	QTimer::singleShot(previewCompileTimeOut, p1, SLOT(kill()));

	if (dvi2pngMode == DPM_DVIPNG_FOLLOW) {
		p1->waitForStarted();
		// dvi -> png
		//follow mode is a tricky features which allows dvipng to run while tex isn't finished
		ProcessX *p2 = firstProcessOfDirectExpansion("txs:///dvipng/[--follow]", ffn);
		if (!p2) return; // command failed, not set ?
        p1->setProperty("proc",QVariant::fromValue(p2));
        connect(p1,SIGNAL(finished(int)),this,SLOT(PreviewLatexCompleted(int)));
		if (!p1->overrideEnvironment().isEmpty()) p2->setOverrideEnvironment(p1->overrideEnvironment());
		connect(p2, SIGNAL(finished(int)), this, SLOT(conversionPreviewCompleted(int)));
		p2->startCommand();
	}
}

void BuildManager::clearPreviewPreambleCache()
{
	QHash<QString, QString>::const_iterator it = preambleHash.constBegin();
	while (it != preambleHash.constEnd()) {
		removePreviewFiles(it.value());
		previewFileNames.removeAll(it.value());
		++it;
	}
	preambleHash.clear();
}

bool BuildManager::isCommandDirectlyDefined(const QString &id) const
{
	if (id.startsWith(TXS_CMD_PREFIX)) return isCommandDirectlyDefined(id.mid(TXS_CMD_PREFIX.length()));
	if (internalCommands.contains(TXS_CMD_PREFIX + id)) return true;
	return !commands.value(id).commandLine.isEmpty();
}

CommandInfo BuildManager::getCommandInfo(const QString &id) const
{
	if (id.startsWith(TXS_CMD_PREFIX)) return getCommandInfo(id.mid(TXS_CMD_PREFIX.length()));
	CommandMapping::const_iterator it = commands.constFind(id);
	if (it == commands.end()) return CommandInfo();
	return *it;
}

QString BuildManager::editCommandList(const QString &list, const QString &excludeId)
{
	QStringList ids = commandSortingsOrder, names, commands;
	ids << userToolOrder;
	ids.insert(ids.indexOf("view-pdf-external"), CMD_VIEW_PDF_INTERNAL);
	ids << CMD_CONDITIONALLY_RECOMPILE_BIBLIOGRAPHY;
	ids.removeAll(excludeId);
	ids.removeAll(TXS_CMD_PREFIX + excludeId);
	for (int i = 0; i < ids.size(); i++) {
		CommandInfo ci = getCommandInfo(ids[i]);
		names << (ci.displayName.isEmpty() ? ids[i] : ci.displayName);
		if (names.last() == CMD_VIEW_PDF_INTERNAL) names.last() = tr("Internal Pdf Viewer");
		commands << (ci.commandLine.isEmpty() ? ids[i] : ci.commandLine);
		if (!ids[i].startsWith(TXS_CMD_PREFIX)) ids[i] = TXS_CMD_PREFIX + ids[i];
	}

    UserQuickDialog uqd(nullptr, ids, names, commands);
	uqd.setCommandList(list);
	if (uqd.exec() == QDialog::Accepted) return uqd.getCommandList();
	else return list;
}

CommandMapping BuildManager::getAllCommands()
{
	return commands;
}

QStringList BuildManager::getCommandsOrder()
{
	QStringList order = commandSortingsOrder;
	order << userToolOrder;
	foreach (const QString &more, commands.keys())
		if (!order.contains(more)) order << more;
	return order;
}

void BuildManager::setAllCommands(const CommandMapping &cmds, const QStringList &userOrder)
{
	this->commands = cmds;
	this->userToolOrder = userOrder;

	for (CommandMapping::iterator it = commands.begin(), end = commands.end(); it != end; ++it)
		if (it.value().commandLine == tr("<unknown>"))
			it.value().commandLine = "";

	static QStringList latexCommandsUnexpanded, rerunnableCommandsUnexpanded, pdfCommandsUnexpanded, stdoutCommandsUnexpanded, viewerCommandsUnexpanded;
	ConfigManagerInterface::getInstance()->registerOption("Tools/Kind/LaTeX", &latexCommandsUnexpanded, QStringList() << "latex" << "pdflatex" << "xelatex" << "lualatex" << "latexmk" << "compile");
	ConfigManagerInterface::getInstance()->registerOption("Tools/Kind/Rerunnable", &rerunnableCommandsUnexpanded, QStringList() << "latex" << "pdflatex" << "xelatex" << "lualatex");
	ConfigManagerInterface::getInstance()->registerOption("Tools/Kind/Pdf", &pdfCommandsUnexpanded, QStringList() << "pdflatex" << "xelatex" << "lualatex" << "latexmk" << "dvipdf" << "ps2pdf");
	ConfigManagerInterface::getInstance()->registerOption("Tools/Kind/Stdout", &stdoutCommandsUnexpanded, QStringList() << "bibtex" << "biber" << "bibtex8" << "bibliography");
	ConfigManagerInterface::getInstance()->registerOption("Tools/Kind/Viewer", &viewerCommandsUnexpanded, QStringList() << "view-pdf" << "view-ps" << "view-dvi" << "view-pdf-internal" << "view-pdf-external" << "view");

	QList<QStringList *> lists = QList<QStringList *>() << &latexCommands << &rerunnableCommands << &pdfCommands << &stdoutCommands << &viewerCommands;
	QList<QStringList *> listsUnexpanded = QList<QStringList *>() << &latexCommandsUnexpanded << &rerunnableCommandsUnexpanded << &pdfCommandsUnexpanded << &stdoutCommandsUnexpanded << &viewerCommandsUnexpanded;
	Q_ASSERT(lists.size() == listsUnexpanded.size());
	for (int i = 0; i < lists.size(); i++) {
		QStringList *sl = lists[i];
		*sl = *listsUnexpanded.at(i);
		for (int i = 0; i < sl->size(); i++) {
			Q_ASSERT(commands.contains((*sl)[i]) || (*sl)[i] == "view-pdf-internal");
			(*sl)[i] = getCommandInfo((*sl)[i]).commandLine.trimmed();
		}
	}
}

/*!
 * Returns a best guess compiler for a string given in "% !TeX TS-program = [program]" \ "% !TeX program = [program]"
 */
QString BuildManager::guessCompilerFromProgramMagicComment(const QString &program)
{
	if (program == "latex") return BuildManager::CMD_LATEX;
	else if (program == "pdflatex") return BuildManager::CMD_PDFLATEX;
	else if (program == "xelatex") return BuildManager::CMD_XELATEX;
	else if (program == "luatex" || program == "lualatex") return BuildManager::CMD_LUALATEX;
	return QString();

}

/*!
 * Returns a best guess viewer for a string given in "% !TeX TS-program = [program]" \ "% !TeX program = [program]"
 */
QString BuildManager::guessViewerFromProgramMagicComment(const QString &program)
{
	if (program == "latex") return BuildManager::CMD_VIEW_DVI;
	else if (program == "pdflatex" || program == "xelatex" || program == "luatex" || program == "lualatex") {
		return CMD_VIEW_PDF;
	}
	return QString();
}

void BuildManager::singleInstanceCompleted(int status)
{
	Q_UNUSED(status);
	QObject *s = sender();
	REQUIRE(s);
	for (QMap<QString, ProcessX *>::iterator it = runningCommands.begin(), end = runningCommands.end(); it != end;)
		if (it.value() == s) it = runningCommands.erase(it);
		else ++it;
}

void BuildManager::preamblePrecompileCompleted(int status)
{
	Q_UNUSED(status);
	QProcess *p = qobject_cast<QProcess *>(sender());
	REQUIRE(p);
	if (p->exitCode() != 0 || p->exitStatus() != QProcess::NormalExit) {
		preambleHash.insert(p->property("preamble").toString(), "<failed>");
	} else
		preambleHash.insert(p->property("preamble").toString(), p->property("preambleFile").toString());
}

//latex has finished the dvi creation
//now either dvips or dvipng is necessary if not already running
void BuildManager::latexPreviewCompleted(int status)
{
	Q_UNUSED(status);
	if (dvi2pngMode == DPM_DVIPNG) {
		ProcessX *p1 = qobject_cast<ProcessX *> (sender());
		if (!p1) return;
		// dvi -> png
        ProcessX *p2 = firstProcessOfDirectExpansion(CMD_DVIPNG, p1->getFile(),QFileInfo(),0,true);
		if (!p2) return; //dvipng does not work
		//REQUIRE(p2);
		if (!p1->overrideEnvironment().isEmpty()) p2->setOverrideEnvironment(p1->overrideEnvironment());
		connect(p2, SIGNAL(finished(int)), this, SLOT(conversionPreviewCompleted(int)));
		p2->startCommand();
	}
	if (dvi2pngMode == DPM_DVIPS_GHOSTSCRIPT) {
		ProcessX *p1 = qobject_cast<ProcessX *> (sender());
		if (!p1) return;
		// dvi -> ps
        ProcessX *p2 = firstProcessOfDirectExpansion("txs:///dvips/[-E]", p1->getFile(),QFileInfo(),0,true);
		if (!p2) return; //dvips does not work
		//REQUIRE(p2);
		if (!p1->overrideEnvironment().isEmpty()) p2->setOverrideEnvironment(p1->overrideEnvironment());
		connect(p2, SIGNAL(finished(int)), this, SLOT(dvi2psPreviewCompleted(int)));
		p2->startCommand();
	}
	if (dvi2pngMode == DPM_EMBEDDED_PDF) {
		ProcessX *p1 = qobject_cast<ProcessX *> (sender());
		if (!p1) return;
		QString processedFile = p1->getFile();
		if (processedFile.endsWith(".tex"))
			processedFile = QDir::fromNativeSeparators(parseExtendedCommandLine("?am.tex", processedFile).first());
			// TODO: fromNativeSeparators is a workaround to fix bug
			// yields different dir separators depending on the context. This should be fixed (which direction?).
			// Test (on win): switch preview between dvipng and pdflatex
		QString fn = parseExtendedCommandLine("?am).pdf", processedFile).first();
		if (QFileInfo(fn).exists()) {
			emit previewAvailable(fn, previewFileNameToSource[processedFile]);
		}
	}
}

//dvi to ps conversion is finished, call ghostscript to make a useable png from it
void BuildManager::dvi2psPreviewCompleted(int status)
{
	Q_UNUSED(status);
	ProcessX *p2 = qobject_cast<ProcessX *> (sender());
	if (!p2) return;
	// ps -> png, ghostscript is quite, safe, will create 24-bit png
	QString filePs = parseExtendedCommandLine("?am.ps", p2->getFile()).first();
    ProcessX *p3 = firstProcessOfDirectExpansion("txs:///gs/[-q][-dSAFER][-dBATCH][-dNOPAUSE][-sDEVICE=png16m][-dEPSCrop][-sOutputFile=\"?am)1.png\"]", filePs,QFileInfo(),0,true);
    if (!p3) return; //gs does not work
	if (!p2->overrideEnvironment().isEmpty()) p3->setOverrideEnvironment(p2->overrideEnvironment());
	connect(p3, SIGNAL(finished(int)), this, SLOT(conversionPreviewCompleted(int)));
	p3->startCommand();
}
void BuildManager::PreviewLatexCompleted(int status){
    if(status!=0){
        // latex compile failed, kill dvipng
        ProcessX *p1 = qobject_cast<ProcessX *> (sender());
        ProcessX *p2=p1->property("proc").value<ProcessX *>();
        p2->terminate();
    }
}

void BuildManager::conversionPreviewCompleted(int status)
{
	Q_UNUSED(status);
	ProcessX *p2 = qobject_cast<ProcessX *> (sender());
	if (!p2) return;
	// put image in preview
	QString processedFile = p2->getFile();
	if (processedFile.endsWith(".ps")) processedFile = parseExtendedCommandLine("?am.tex", processedFile).first();
	QString fn = parseExtendedCommandLine("?am)1.png", processedFile).first();
	if (QFileInfo(fn).exists())
		emit previewAvailable(fn, previewFileNameToSource[processedFile]);
}

void BuildManager::commandLineRequestedDefault(const QString &cmdId, QString *result, bool *user)
{
	if (user) *user = false;
	if (!result) return;
	int space = cmdId.indexOf(' ');
	if (space == -1) space = cmdId.size();
	if (internalCommands.contains(cmdId.left(space)) || internalCommands.contains(TXS_CMD_PREFIX + cmdId.left(space))) {
		*result = cmdId;
		if (!result->startsWith(TXS_CMD_PREFIX)) *result = TXS_CMD_PREFIX + *result;
		return;
	}
	CommandMapping::iterator it = commands.find(cmdId);
	if (it != commands.end()) {
		*result = it->commandLine;
		if (user) *user = it->user;
	}
}

void BuildManager::runInternalCommandThroughProcessX()
{
	ProcessX *p = qobject_cast<ProcessX *>(sender());
	REQUIRE(p);
	REQUIRE(p->getCommandLine().startsWith(TXS_CMD_PREFIX));
	testAndRunInternalCommand(p->getCommandLine(), p->getFile());
}

bool BuildManager::testAndRunInternalCommand(const QString &cmd, const QFileInfo &mainFile)
{
	int space = cmd.indexOf(' ');
	QString cmdId, options;
	if (space == -1 ) cmdId = cmd;
    else {
        cmdId = cmd.left(space);
        options = cmd.mid(space + 1);
    }
	if (internalCommands.contains(cmdId)) {
		emit runInternalCommand(cmdId, mainFile, options);
		return true;
	}
	return false;
}

QString BuildManager::findFile(const QString &defaultName, const QStringList &searchPaths)
{
	//TODO: merge with findResourceFile
	QFileInfo base(defaultName);
	if (base.exists()) return defaultName;
	if (searchPaths.isEmpty()) return "";

	foreach (QString p, searchPaths) {
		if (p.startsWith('/') || p.startsWith("\\\\") || (p.length() > 2 && p[1] == ':' && (p[2] == '\\' || p[2] == '/'))) {
			QFileInfo fi(QDir(p), base.fileName());
			if (fi.exists()) return fi.absoluteFilePath();
		} else {
			// ?? seems a bit weird: if p is not an absolute path, then interpret p as directory
			// e.g. default = /my/filename.tex
			//      p = foo
			// -->  /my/foo/filename.tex
			// TODO: do we want/use this anywere or can it be removed?
			QString absPath = base.absolutePath() + "/";
			QString baseName = "/" + base.fileName();
			QFileInfo fi(absPath + p + baseName);
			if (fi.exists()) return fi.absoluteFilePath();
		}
	}
	return "";
}

void BuildManager::removePreviewFiles(QString elem)
{
	QDir currentDir(QFileInfo(elem).absoluteDir());
	elem = QFileInfo(elem).completeBaseName();
	QStringList files;
	files = currentDir.entryList(QStringList(elem + "*"),
	                             QDir::Files | QDir::NoSymLinks);
	foreach (const QString &file, files)
		QFile::remove(currentDir.absolutePath() + "/" + file);
}

//DDE things
#ifdef Q_OS_WIN32
#include "windows.h"
bool BuildManager::executeDDE(QString ddePseudoURL)
{
	//parse URL
	if (ddePseudoURL.startsWith("dde:///")) ddePseudoURL.remove(0, 7);
	else if (ddePseudoURL.startsWith("dde://")) {
		UtilsUi::txsInformation(tr("You have used a dde:// command with two slashes, which is deprecated. Please change it to a triple slash command dde:/// by adding another slash."));
		ddePseudoURL.remove(0, 6);
	} else return false;

	if (ddePseudoURL.length() < 3) return false;
	QString serviceEXEPath;
	if (ddePseudoURL[1] == ':' || (ddePseudoURL[0] == '"' && ddePseudoURL[2] == ':')) { //extended dde of format dde:///<path>:control/commands
		int pathLength = ddePseudoURL.indexOf(':', 3);
		serviceEXEPath = ddePseudoURL.left(pathLength);
		ddePseudoURL.remove(0, pathLength + 1);
	}

	int slash = ddePseudoURL.indexOf("/");
	if (slash == -1) return false;
	QString service = ddePseudoURL.left(slash);
	ddePseudoURL.remove(0, slash + 1);
	slash = ddePseudoURL.indexOf("/");
	if (slash == -1) return false;
	QString topic = ddePseudoURL.left(slash);
	ddePseudoURL.remove(0, slash + 1);
	QStringList commands = ddePseudoURL.split("[", QString::SkipEmptyParts);
	if (commands.isEmpty()) return false;


	//connect to server/topic

	if (pidInst == 0)
		if (DdeInitializeA(&pidInst, NULL, APPCLASS_STANDARD | APPCMD_CLIENTONLY | CBF_SKIP_ALLNOTIFICATIONS, 0L) != DMLERR_NO_ERROR)
			return false;

	QCoreApplication::processEvents();

	HSZ hszService = DdeCreateStringHandleA(pidInst, service.toLocal8Bit().data() , CP_WINANSI);
	if (!hszService) return false;
	HSZ hszTopic = DdeCreateStringHandleA(pidInst, topic.toLocal8Bit().data(), CP_WINANSI);
	if (!hszTopic) {
		DdeFreeStringHandle(pidInst, hszService);
		return false;
	}
	HCONV hConv = DdeConnect(pidInst, hszService, hszTopic, NULL);
	if (!hConv && !serviceEXEPath.isEmpty()) {
		if (!serviceEXEPath.contains('"') && serviceEXEPath.contains(' ') && QFileInfo(serviceEXEPath).exists())
			serviceEXEPath = "\"" + serviceEXEPath + "\"";
		//connecting failed; start the service if necessary
		QProcess *p = new QProcess(QCoreApplication::instance()); //application is parent, to close the service if txs is closed
		p->start(serviceEXEPath);
		if (p->waitForStarted(5000)) {
			connect(p, SIGNAL(finished(int)), p, SLOT(deleteLater())); //will free proc after the process has ended
			//try again to connect (repeatedly 2s long)
			DWORD startTime = GetTickCount();
			while (!hConv && GetTickCount() - startTime < 1000) {
				hConv = DdeConnect(pidInst, hszService, hszTopic, NULL);
				Sleep(100);
			}
		} else delete p;
	}

	QCoreApplication::processEvents();

	DdeFreeStringHandle(pidInst, hszService);
	DdeFreeStringHandle(pidInst, hszTopic);
	if (!hConv) return false;

	//execute requests
	foreach (const QString s, commands) {
		QString temp = ("[" + s.trimmed());
		QByteArray ba = temp.toLocal8Bit();
		HDDEDATA req = DdeCreateDataHandle(pidInst, (LPBYTE) ba.data(), ba.size() + 1, 0, 0, CF_TEXT, 0);
		if (req) {
			HDDEDATA recData = DdeClientTransaction((BYTE *)req, (DWORD) - 1, hConv, 0, 0, XTYP_EXECUTE, 1000, 0);
			DdeFreeDataHandle(req);
			if (recData) DdeFreeDataHandle(recData);
		}
		//else QMessageBox::information(0,"TeXstudio",QObject::tr("DDE command %1 failed").arg("["+s),0); //break; send all commands
	}

	QCoreApplication::processEvents();

	//disconnect
	DdeDisconnect(hConv);

	QCoreApplication::processEvents();

	return true;
}
#endif

ProcessX::ProcessX(BuildManager *parent, const QString &assignedCommand, const QString &fileToCompile):
    QProcess(parent), cmd(assignedCommand.trimmed()), file(fileToCompile), isStarted(false), ended(false), stderrEnabled(true), stdoutEnabled(true), stdoutEnabledOverrideOn(false), stdoutBuffer(nullptr), stdoutCodec(nullptr)
{

	QString stdoutRedirection, stderrRedirection;
	cmd = BuildManager::extractOutputRedirection(cmd, stdoutRedirection, stderrRedirection);
	if (stdoutRedirection == "/dev/null" || stdoutRedirection == "nul") {
		stdoutEnabled = false;
	} else if (stdoutRedirection == "txs:///messages") {
		stdoutEnabledOverrideOn = true;
	} else if (!stdoutRedirection.isEmpty()) {
		parent->processNotification(tr("The specified stdout redirection is not supported: \"%1\". Please see the manual for details.").arg("> " + stdoutRedirection));
	}
	if (stderrRedirection == "/dev/null" || stderrRedirection == "nul") {
		stderrEnabled = false;
	} else if (stderrRedirection == "txs:///messages") {
		// nothing to do because stderr goes to messages by default
	} else if (stderrRedirection == "&1") {
		stderrEnabled = stdoutEnabled || stdoutEnabledOverrideOn;
	} else if (!stderrRedirection.isEmpty()) {
		parent->processNotification(tr("The specified stderr redirection is not supported: \"%1\". Please see the manual for details.").arg("2> " + stderrRedirection));
	}
	connect(this, SIGNAL(started()), SLOT(onStarted()));
	connect(this, SIGNAL(finished(int)), SLOT(onFinished(int)));
	connect(this, SIGNAL(error(QProcess::ProcessError)), SLOT(onError(QProcess::ProcessError)));
}

/*!
 * Reformats shell-style literal quotes (\") to QProcess-style literal quotes (""")
 * e.g. "Epic 12\" singles" -> "Epic 12""" singles"
 */
QString ProcessX::reformatShellLiteralQuotes(QString cmd)
{
	return cmd.replace("\\\"", "\"\"\"");
}

void ProcessX::startCommand()
{
	ended = false;

#ifdef Q_OS_WIN32
	if (cmd.startsWith("dde://") || cmd.startsWith("dde:///")) {
		onStarted();
		BuildManager *manager = qobject_cast<BuildManager *>(parent());
		if (!manager) {
			emit finished(1);
			emit finished(1, NormalExit);
			return;
		}
		bool ok = manager->executeDDE(cmd);
		emit finished(ok ? 0 : 1);
		emit finished(ok ? 0 : 1, NormalExit);
		return;
	}
#endif

	if (cmd.startsWith("txs:///")) {
		onStarted();
		emit startedX();
		emit finished(0);
		emit finished(0, NormalExit);
		return;
	}
	if (stdoutEnabled || stdoutBuffer)
		connect(this, SIGNAL(readyReadStandardOutput()), this, SLOT(readFromStandardOutput()));
	if (stderrEnabled)
		connect(this, SIGNAL(readyReadStandardError()), this, SLOT(readFromStandardError()));

	//qDebug() << workingDirectory();
	//qDebug() << cmd;
	QByteArray path = qgetenv("PATH");
#ifdef Q_OS_OSX
	QString basePath = getEnvironmentPath();
    qputenv("PATH", path + getPathListSeparator().toLatin1() + BuildManager::resolvePaths(BuildManager::additionalSearchPaths).toUtf8() + getPathListSeparator().toLatin1() + basePath.toUtf8());
	// needed for searching the executable in the additional paths see https://bugreports.qt-project.org/browse/QTBUG-18387
#else
	qputenv("PATH", path + getPathListSeparator().toLatin1() + BuildManager::resolvePaths(BuildManager::additionalSearchPaths).toUtf8()); // needed for searching the executable in the additional paths see https://bugreports.qt-project.org/browse/QTBUG-18387
#endif
	QProcess::start(cmd);
	qputenv("PATH", path); // restore

	if (error() == FailedToStart || error() == Crashed)
		isStarted = ended = true; //prevent call of waitForStarted, if it failed to start (see QTBUG-33021)

#ifdef PROFILE_PROCESSES
	connect(this, SIGNAL(finished(int)), SLOT(finished()));
	time.start();
#endif
}

bool ProcessX::waitForStarted(int timeOut)
{
	if (isStarted) return true;
	return QProcess::waitForStarted(timeOut);
}

const QString &ProcessX::getFile()
{
	return file;
}
const QString &ProcessX::getCommandLine()
{
	return cmd;
}

bool ProcessX::showStdout() const
{
	return stdoutEnabled;
}

void ProcessX::setShowStdout(bool show)
{
	if (stdoutEnabledOverrideOn) show = true;
	stdoutEnabled = show;
}

QString *ProcessX::getStdoutBuffer()
{
	return stdoutBuffer;
}

void ProcessX::setStdoutBuffer(QString *buffer)
{
	stdoutBuffer = buffer;
}

void ProcessX::setStdoutCodec(QTextCodec *codec)
{
	stdoutCodec = codec;
}

bool ProcessX::showStderr() const
{
	return stderrEnabled;
}

void ProcessX::setShowStderr(bool show)
{
	stderrEnabled = show;
}

void ProcessX::setOverrideEnvironment(const QStringList &env)
{
	overriddenEnvironment = env;
	setEnvironment(env);
}

const QStringList &ProcessX::overrideEnvironment()
{
	return overriddenEnvironment;
}


int ProcessX::exitStatus() const
{
	return QProcess::exitStatus();
}

int ProcessX::exitCode() const
{
	return QProcess::exitCode();
}

QString ProcessX::readAllStandardOutputStr()
{
	return stdoutCodec ? stdoutCodec->toUnicode(QProcess::readAllStandardOutput()) : QString::fromLocal8Bit(QProcess::readAllStandardOutput());
}

QString ProcessX::readAllStandardErrorStr()
{
	return stdoutCodec ? stdoutCodec->toUnicode(QProcess::readAllStandardError()) : QString::fromLocal8Bit(QProcess::readAllStandardError());
}

bool ProcessX::waitForFinished( int msecs )
{
	return QProcess::waitForFinished(msecs);
}

bool ProcessX::isRunning() const
{
	return isStarted && !ended;
}

void ProcessX::onStarted()
{
	if (isStarted) return; //why am I called twice?
	isStarted = true;
	BuildManager_hadSuccessfulProcessStart = true;
	emit startedX();
	emit processNotification(tr("Process started: %1").arg(cmd));
}

void ProcessX::onError(ProcessError error)
{
	if (error == FailedToStart) {
		emit processNotification(tr("Error: Could not start the command: %1").arg(cmd));

		if (!BuildManager_hadSuccessfulProcessStart)
			emit processNotification("<br>" + tr("<b>Make sure that you have installed a (La)TeX distribution</b> e.g. MiKTeX or TeX Live, and have set the correct paths to this distribution on the command configuration page.<br>"
			                                     "A (La)TeX editor like TeXstudio cannot work without the (La)TeX commands provided by such a distribution."));

	} else if (error == Crashed)
		emit processNotification(tr("Error: Command crashed: %1").arg(cmd));
}

void ProcessX::onFinished(int error)
{
	if (cmd.contains("AcroRd32.exe") && error == 1) error = 0; // fix for Adobe Reader: It returns 1 on success
	if (error) {
		emit processNotification(tr("Process exited with error(s)"));
		readFromStandardError(true);
	} else {
		emit processNotification(tr("Process exited normally"));
		readFromStandardOutput();
		readFromStandardError();
	}
	ended = true;
}

#ifdef PROFILE_PROCESSES
void ProcessX::finished()
{
	qDebug() << "Process: " << qPrintable(cmd) << "  Running time: " << time.elapsed();
}
#endif

void ProcessX::readFromStandardOutput()
{
	if (!stdoutEnabled && !stdoutBuffer) return;
	QString t = readAllStandardOutputStr().trimmed();
	if (stdoutBuffer) stdoutBuffer->append(t);
	emit standardOutputRead(t);
}

void ProcessX::readFromStandardError(bool force)
{
	if (!stderrEnabled && !force) return;
	QString t = readAllStandardErrorStr().simplified();
	emit standardErrorRead(t);
}
