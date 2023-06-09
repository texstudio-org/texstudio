#ifndef Header_Latex_Package
#define Header_Latex_Package

#include "mostQtHeaders.h"
#include "codesnippet.h"
#include "latexparser/commanddescription.h"

typedef QPair<QString, int> QPairQStringInt;
class LatexCompleterConfig;

/*!
 * \brief store necessary information for latex package
 *
 * Stores commands for completion and syntax check.
 */
class LatexPackage
{
public:
	LatexPackage();

	// Temporary solution: keys of LatexDocuments::cachedPackages have become complex. Use these functions to manage them.
	// This is a first step for refactoring the existing code. No functionality is changed.
	// In the long run, the information should be stored and accessed via the LatexPackage objects, which are referenced by the keys.
	static QString makeKey(const QString &cwlFilename, const QString &options);  // TODO not yet used: where are the keys actually created?
	static QString keyToCwlFilename(const QString &key);
	static QString keyToPackageName(const QString &key);
	static QStringList keyToOptions(const QString &key);

	bool notFound;  // Workaround: explicit flag better than using a magic value in package name. TODO: Do we need not found packages?
    bool containsOptionalSections; ///< optimization to not reread for different package options
	QString packageName; ///< name of package
	QStringList requiredPackages; ///< necessary sub-packages
	CodeSnippetList completionWords; ///< list of completion words
	QHash<QString, QSet<QString> > possibleCommands; ///< possible commands, info for syntax checking
	QHash<QString, QString> specialDefCommands; ///< define special elements, e.g. define color etc
	QSet<QString> optionCommands; ///< commands which contain arguments, obsolete
	QMultiHash<QString, QString> environmentAliases; ///< environment aliases, especially environments which signify math environments concerning syntax check
	CommandDescriptionHash commandDescriptions; ///< command definitions
	void unite(LatexPackage &add, bool forCompletion = false); ///< merge with LatexPackage \a add
};

LatexPackage loadCwlFile(const QString fileName, LatexCompleterConfig *config = nullptr, QStringList conditions = QStringList());


#endif // LATEXPACKAGE_H
