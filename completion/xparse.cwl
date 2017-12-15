#include:expl3
\NewDocumentCommand{cmd}{args}{def}#d
\RenewDocumentCommand{cmd}{args}{def}#d
\ProvideDocumentCommand{cmd}{args}{def}#d
\DeclareDocumentCommand{cmd}{args}{def}#d
\NewDocumentEnvironment{envname}{args}{begindef}{enddef}#N
\RenewDocumentEnvironment{envname}{args}{begindef}{enddef}#N
\ProvideDocumentEnvironment{envname}{args}{begindef}{enddef}#N
\DeclareDocumentEnvironment{envname}{args}{begindef}{enddef}#N
\NewExpandableDocumentCommand{cmd}{args}{def}#d
\RenewExpandableDocumentCommand{cmd}{args}{def}#d
\ProvideExpandableDocumentCommand{cmd}{args}{def}#d
\DeclareExpandableDocumentCommand{cmd}{args}{def}#d
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