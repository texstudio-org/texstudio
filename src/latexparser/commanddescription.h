#ifndef Header_CommandDescription
#define Header_CommandDescription

#include "mostQtHeaders.h"
#include "latextokens.h"

/*!
 * \brief define available arguments for a command
 */
class CommandDescription
{
public:
	CommandDescription();
	int optionalArgs; ///< number of optional arguments
	int bracketArgs; ///< number of () arguments
    int overlayArgs; ///< number of <> arguments (beamer overlay, usually 0 or 1)
	int args; ///< number of mandatory arguments (in braces)
	int level;
    bool bracketCommand;
    bool verbatimAfterOptionalArg;
	QList<Token::TokenType> argTypes; ///< define argument type as token
	QList<Token::TokenType> optTypes; ///< define argument type as token
	QList<Token::TokenType> bracketTypes; ///< define argument type as token
    QList<Token::TokenType> overlayTypes; ///< define argument type as token
    QString optionalCommandName; ///< stores optionally command name. It is used for processing command description during lexing
	QString toDebugString() const; ///< debug function to get easier information on command description
    bool operator==(const CommandDescription &v) const; ///< compare two command descriptions
};

typedef QStack<CommandDescription> CommandStack;

Q_DECLARE_METATYPE(CommandStack);

//typedef QHash<QString, CommandDescription> CommandDescriptionHash;
/*!
 * \brief special definiton of QHash<QString, CommandDescription>
 * It defines a special version of unite which avoids overwritiung good defined CDs with poorly defined one (...#S)
 */
class CommandDescriptionHash : public QHash<QString, CommandDescription>
{
public:
    void unite(const CommandDescriptionHash &other); // special unite which avoids overwritiung good defined CDs with poorly defined one (...#S)
};

#endif // COMMANDDESCRIPTION_H
