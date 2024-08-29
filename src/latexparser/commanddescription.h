#ifndef Header_CommandDescription
#define Header_CommandDescription

#include "mostQtHeaders.h"
#include "latextokens.h"

/*!
 * \brief define arguments
 * Specify the type of the argument and the token type
 */
class ArgumentDescription {
public:
    enum ArgType {
        MANDATORY,
        OPTIONAL,
        BRACKET,
        OVERLAY
    };
    ArgType type;
    Token::TokenType tokenType;
    bool operator==(const ArgumentDescription &v) const;
};

/*!
 * \brief define available arguments for a command
 * Arguments are stored as a list of argument descriptions
 * The argument position is encoded into the list position
 */
class CommandDescription
{
public:
	CommandDescription();
	int level;
    bool bracketCommand;
    bool verbatimAfterOptionalArg;
    QList<ArgumentDescription> arguments; ///< define arguments as argument description
    QString optionalCommandName; ///< stores optionally command name. It is used for processing command description during lexing
	QString toDebugString() const; ///< debug function to get easier information on command description
    int args(ArgumentDescription::ArgType argType=ArgumentDescription::MANDATORY) const; ///< return number of arguments
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
