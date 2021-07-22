# mathcommand package
# Matthew Bertucci 7/22/2021

\newmathcommand{command}[args]{def}#d
\newtextcommand{command}[args]{def}#d
\renewmathcommand{command}[args]{def}#d
\renewtextcommand{command}[args]{def}#d
\declaremathcommand{command}[args]{def}#d
\declaretextcommand{command}[args]{def}#d
\NewDocumentMathCommand{command}{args}{def}#d
\NewDocumentTextCommand{command}{args}{def}#d
\RenewDocumentMathCommand{command}{args}{def}#d
\RenewDocumentTextCommand{command}{args}{def}#d
\DeclareDocumentMathCommand{command}{args}{def}#d
\DeclareDocumentTextCommand{command}{args}{def}#d
\ProvideDocumentMathCommand{command}{args}{def}#d
\ProvideDocumentTextCommand{command}{args}{def}#d
\declarecommand
\storecommand[optional prefix]{macro}

\IfEmptyTF{string}{NoValueCode}{ValueCode}
\GetIndex{string}
\GetExponent{string}

\newcommandPIE{command}[args]{def}#d
\renewcommandPIE{command}[args]{def}#d
\declarecommandPIE{command}[args]{def}#d
\NewDocumentCommandPIE{command}{args}{def}#d
\RenewDocumentCommandPIE{command}{args}{def}#d
\DeclareDocumentCommandPIE{command}{args}{def}#d
\ProvideDocumentCommandPIE{command}{args}{def}#d
\newmathcommandPIE{command}[args]{def}#d
\renewmathcommandPIE{command}[args]{def}#d
\declaremathcommandPIE{command}[args]{def}#d
\NewDocumentMathCommandPIE{command}{args}{def}#d
\RenewDocumentMathCommandPIE{command}{args}{def}#d
\DeclareDocumentMathCommandPIE{command}{args}{def}#d
\ProvideDocumentMathCommandPIE{command}{args}{def}#d

\LoopCommands{list}[name]{code}
\lettersUppercase
\lettersLowercase
\lettersAll
\lettersGreekLowercase
\lettersGreekUppercase
\lettersGreekAll

\disablecommand{commands}
\suggestcommand{command}{suggestion}

\mathcommandconfigure{keyvals}

#keyvals:\mathcommandconfigure
disabled=#error,warning,silent
#endkeyvals