#include "commanddescription.h"

CommandDescription::CommandDescription(): optionalArgs(0), bracketArgs(0), args(0), level(0)
{

}

QString tokenTypesToString(const QList<Token::TokenType>& types)
{
	QStringList res;
	for (int i=0;i<types.length();i++) res << QString("%1").arg((int)types[i]);
	return res.join(" ");
}

QString CommandDescription::toDebugString() const
{
    return QString("%1:%2:%3").arg(tokenTypesToString(optTypes)).arg(tokenTypesToString(argTypes)).arg(tokenTypesToString(bracketTypes));
}

bool CommandDescription::operator==(const CommandDescription &v) const
{
    return (this->optionalCommandName==v.optionalCommandName && this->args==v.args && this->argTypes==v.argTypes && this->level==v.level && this->optionalArgs==v.optionalArgs && this->optTypes==v.optTypes && this->bracketArgs==v.bracketArgs && this->bracketTypes==v.bracketTypes);
}


