#ifndef COMMANDDESCRIPTION_H
#define COMMANDDESCRIPTION_H

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
	int args; ///< number of mandatory arguments (in braces)
	int level;
	QList<Token::TokenType> argTypes; ///< define argument type as token
	QList<Token::TokenType> optTypes; ///< define argument type as token
	QList<Token::TokenType> bracketTypes; ///< define argument type as token
    QString optionalCommandName; ///< stores optionally command name. It is used for processing command description during lexing
	QString toDebugString() const; ///< debug function to get easier information on command description
    bool operator==(const CommandDescription &v) const; ///< compare two command descriptions
};

typedef QStack<CommandDescription> CommandStack;

Q_DECLARE_METATYPE(CommandStack);

typedef QHash<QString, CommandDescription> CommandDescriptionHash;

#endif // COMMANDDESCRIPTION_H
