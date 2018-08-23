#ifndef LATEXPARSER_H
#define LATEXPARSER_H

#include "commanddescription.h"


/*!
 * \brief class for storing latex syntax informtion and latex parsing
 *
 * The latex parsing is less important since the token based system, but the storage of syntax information is still used.
 */
class LatexParser
{
	friend class SmallUsefulFunctionsTest;
public:
	LatexParser(); ///< constructor
	~LatexParser();
	void init(); ///< set default values

	static const int MAX_STRUCTURE_LEVEL;

	enum ContextType {Unknown, Command, Environment, Label, Reference, Citation, Citation_Ext, Option, Graphics, Package, Keyval, KeyvalValue, OptionEx, ArgEx};
	// could do with some generalization as well, optionEx/argEx -> special treatment with specialOptionCommands

	static LatexParser &getInstance();
	static LatexParser *getInstancePtr();

	static int commentStart(const QString &text);
	static QString cutComment(const QString &text);
    static bool resolveCommandOptions(const QString &line, int column, QStringList &values, QList<int> *starts = nullptr);
	static QString removeOptionBrackets(const QString &option);
	int structureDepth()
	{
		return MAX_STRUCTURE_LEVEL;
	}
	int structureCommandLevel(const QString &cmd) const;

	/// realizes whether col is in a \command or in a parameter {}
	int findContext(QString &line, int &column) const;
	ContextType findContext(const QString &line, int column, QString &command, QString &value) const;

	QSet<QString> environmentCommands; ///< used by LatexReader only, obsolete
	QSet<QString> optionCommands; ///< used by LatexReader only, obsolete
	QStringList mathStartCommands; ///< commands to start math-mode like '$'
	QStringList mathStopCommands; ///< commands to stop math-mode like '$'
	QSet<QString> customCommands; ///< commands defined in config dialog as custom commands
	QMultiHash<QString, QString> packageAliases; ///< aliases for classes to packages e.g. article = latex-document, latex-mathsymbols, etc
	QMultiHash<QString, QString> environmentAliases; ///< aliases for environments, e.g. equation is math, supertabular is also tab etc.
	/// commands used for syntax check (per doc basis)
	QHash<QString, QSet<QString> > possibleCommands;
	QHash<QString, QSet<QPair<QString, int> > > specialTreatmentCommands; ///< special commands, obsolete
	QHash<QString, QString> specialDefCommands; ///< define special elements, e.g. define color etc
	QMap<int, QString> mapSpecialArgs;

	CommandDescriptionHash commandDefs; ///< command definitions

	void append(const LatexParser &elem); ///< append values
	void substract(const LatexParser &elem); ///< remove values
	void clear(); ///< set to default values
    void importCwlAliases(const QString filename); ///< import package aliases from disc
};
Q_DECLARE_METATYPE(LatexParser)


const QString & getCommonEOW();
/// closing bracket (opening and closing bracket considered correctly)
int findClosingBracket(const QString &word, int &start, QChar oc = QChar('{'), QChar cc = QChar('}'));
/// opening bracket (opening and closing bracket considered correctly), start at "start"
int findOpeningBracket(const QString &word, int start, QChar oc = QChar('{'), QChar cc = QChar('}'));


#endif // LATEXPARSER_H
