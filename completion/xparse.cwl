#include:expl3
\NewDocumentCommand{cmd}{xargs}{def}#d
\RenewDocumentCommand{cmd}{xargs}{def}
\ProvideDocumentCommand{cmd}{xargs}{def}#d
\DeclareDocumentCommand{cmd}{xargs}{def}#d
\NewDocumentEnvironment{envname}{xargs}{begindef}{enddef}#N
\RenewDocumentEnvironment{envname}{xargs}{begindef}{enddef}
\ProvideDocumentEnvironment{envname}{xargs}{begindef}{enddef}#N
\DeclareDocumentEnvironment{envname}{xargs}{begindef}{enddef}#N
\NewExpandableDocumentCommand{cmd}{xargs}{def}#d
\RenewExpandableDocumentCommand{cmd}{xargs}{def}
\ProvideExpandableDocumentCommand{cmd}{xargs}{def}#d
\DeclareExpandableDocumentCommand{cmd}{xargs}{def}#d
\IfNoValueTF{arg}{-NoValue-Code}{ValueCode}
\IfNoValueT{arg}{-NoValue-Code}
\IfNoValueF{arg}{ValueCode}
\IfValueTF{arg}{trueCode}{-NoValue-Code}
\IfValueT{arg}{ValueCode}
\IfValueF{arg}{-NoValue-Code}
\IfBooleanTF{arg}{trueCode}{falseCode}
\IfBooleanT{arg}{trueCode}
\IfBooleanF{arg}{falseCode}


# Functions deemed experimental in the documentation
\BooleanFalse#S
\BooleanTrue#S
\ProcessedArgument#S
\ReverseBoolean#S
\SplitArgument#S
\SplitList#S
\ProcessList#S
\TrimSpaces#S
\GetDocumentCommandArgSpec#S
\GetDocumentEnvironmentArgSpec#S
\ShowDocumentCommandArgSpec#S
\ShowDocumentEnvironmentArgSpec#S
