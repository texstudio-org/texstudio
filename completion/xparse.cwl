# created by sungmin817
#include:expl3
\DeclareDocumentCommand{func}{argspec}{code}#d
\NewDocumentCommand{func}{argspec}{code}#d
\RenewDocumentCommand{func}{argspec}{code}#d
\ProvideDocumentCommand{func}{argspec}{code}#d
#\DeclareDocumentEnvironment{env}{arg}{startCode}{endCode}#d
#\NewDocumentEnvironment
#\RenewDocumentEnvironment
#\ProvideDocumentEnvironment
#\DeclareExpandableDocumentCommand
\IfNoValueTF{arg}{trueCode}{falseCode}
\IfBooleanTF{arg}{trueCode}{falseCode}
