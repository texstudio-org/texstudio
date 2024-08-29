#include "commanddescription.h"

CommandDescription::CommandDescription(): level(0),bracketCommand(false),verbatimAfterOptionalArg(false),arguments()
{

}

QString CommandDescription::toDebugString() const
{
    QString result;
    for(const ArgumentDescription& arg: arguments){
        result += QString("type: %1, tokenType: %2\n").arg(arg.type).arg(arg.tokenType);
    }
    return result;
}

int CommandDescription::args(ArgumentDescription::ArgType argType) const
{
    int result = 0;
    for(const ArgumentDescription& arg: arguments){
        if(arg.type == argType){
            ++result;
        }
    }
    return result;
}

bool ArgumentDescription::operator==(const ArgumentDescription &v) const
{
    return this->tokenType==v.tokenType && this->type==v.type;
}

bool CommandDescription::operator==(const CommandDescription &v) const
{
    return (this->optionalCommandName==v.optionalCommandName && this->arguments == v.arguments );
}

void CommandDescriptionHash::unite(const CommandDescriptionHash &other){
    //QHash<QString,CommandDescription>::unite(other);
    // checks whether cd is already present
    // it is only overwritten, if the new definition contain *more* arguments
    // thus automatically generated definitions like \section#S are not used to disturb present functionality
    foreach (const QString &elem, other.keys()) {
        if (this->contains(elem)) {
            CommandDescription cd = this->value(elem);
            CommandDescription cd_new = other.value(elem);
            if (cd_new.arguments.size() > cd.arguments.size()) {
                //simple selection criteria
                this->insert(elem, other.value(elem));
            } else {
                if (cd_new.arguments.size() == cd.arguments.size()) {
                    // when same number of args (>0), general arg is considered inferior
                    int overlayArgs = 0;
                    int optionalArgs = 0;
                    for (const ArgumentDescription &ad : cd.arguments) {
                        if (ad.type == ArgumentDescription::OPTIONAL){
                            ++optionalArgs;
                        }
                        if (ad.type == ArgumentDescription::OVERLAY){
                            ++overlayArgs;
                        }
                    }
                    int new_overlayArgs = 0;
                    int new_optionalArgs = 0;
                    int new_generalArgs=0;
                    for (const ArgumentDescription &ad : cd_new.arguments) {
                        if (ad.tokenType == Token::generalArg){
                            ++new_generalArgs;
                        }
                        if (ad.type == ArgumentDescription::OPTIONAL){
                            ++optionalArgs;
                        }
                        if (ad.type == ArgumentDescription::OVERLAY){
                            ++overlayArgs;
                        }
                    }
                    if (new_optionalArgs > optionalArgs) {
                        // same number of arguments but more optional arguments
                        this->insert(elem, other.value(elem));
                    } else {
                        if (new_optionalArgs == optionalArgs && cd.arguments.size()>0) {
                            if(new_overlayArgs> overlayArgs){
                                // same number of arguments but more overlay arguments
                                this->insert(elem, other.value(elem));
                            }else{
                                bool override = true;

                                if(new_overlayArgs < overlayArgs){
                                    override=false; // don't overwrite if overlayArgs less
                                }
                                if(new_generalArgs>0){
                                    override=false; // don't overwrite if generalArgs
                                }
                                if (override)
                                    this->insert(elem, other.value(elem));
                            }
                        }
                    }
                }
            }
        } else {
            this->insert(elem, other.value(elem));
        }
    }
}



