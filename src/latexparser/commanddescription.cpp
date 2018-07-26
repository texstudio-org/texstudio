#include "commanddescription.h"

CommandDescription::CommandDescription(): optionalArgs(0), bracketArgs(0), args(0), level(0),bracketCommand(false)
{

}

QString tokenTypesToString(const QList<Token::TokenType>& types)
{
	QStringList res;
    foreach (const Token::TokenType &type,types) res << QString("%1").arg(type);
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

void CommandDescriptionHash::unite(const CommandDescriptionHash &other){
    //QHash<QString,CommandDescription>::unite(other);
    // checks whether cd is already present
    // it is only overwritten, if the new definition contain *more* arguments
    // thus automatically generated definitions like \section#S are not used to disturb present functionality
    foreach (const QString &elem, other.keys()) {
        if (this->contains(elem)) {
            CommandDescription cd = this->value(elem);
            CommandDescription cd_neu = other.value(elem);
            if (cd_neu.args > cd.args) {
                //simple selection criteria
                this->insert(elem, other.value(elem));
            } else {
                // when same number of args (>0), general arg is considered inferior
                if ( (cd_neu.args == cd.args) && (cd.args > 0)) {
                    if (cd_neu.optionalArgs > cd.optionalArgs) {
                        // same number of arguments but more optional arguments
                        this->insert(elem, other.value(elem));
                    } else {
                        if (cd_neu.optionalArgs == cd.optionalArgs) {
                            bool override = true;
                            for (int i = 0; i < cd.args; i++) {
                                if (cd_neu.argTypes.at(i) == Token::generalArg)
                                    override = false;
                            }
                            for (int i = 0; i < cd.optionalArgs; i++) {
                                if (cd_neu.optTypes.at(i) == Token::generalArg)
                                    override = false;
                            }
                            if (override)
                                this->insert(elem, other.value(elem));
                        }
                    }
                }
            }
        } else {
            this->insert(elem, other.value(elem));
        }
    }
}

