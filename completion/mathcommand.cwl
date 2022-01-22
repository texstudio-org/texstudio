# mathcommand package
# Matthew Bertucci 7/22/2021 for v1.04

\newmathcommand{command}[args]{def}#d
\newtextcommand{command}[args]{def}#d
\renewmathcommand{command}[args]{def}#d
\renewtextcommand{command}[args]{def}#d
\declaremathcommand{command}[args]{def}#d
\declaretextcommand{command}[args]{def}#d
\NewDocumentMathCommand{command}{xargs}{def}#d
\NewDocumentTextCommand{command}{xargs}{def}#d
\RenewDocumentMathCommand{command}{xargs}{def}#d
\RenewDocumentTextCommand{command}{xargs}{def}#d
\DeclareDocumentMathCommand{command}{xargs}{def}#d
\DeclareDocumentTextCommand{command}{xargs}{def}#d
\ProvideDocumentMathCommand{command}{xargs}{def}#d
\ProvideDocumentTextCommand{command}{xargs}{def}#d
\declarecommand{command}[args]{def}#d
\storecommand{command}
\storecommand[prefix]{command}

\IfEmptyTF{string}{NoValueCode}{ValueCode}
\GetIndex{string}
\GetExponent{string}

\newcommandPIE{command}[args]{def}#d
\renewcommandPIE{command}[args]{def}#d
\declarecommandPIE{command}[args]{def}#d
\NewDocumentCommandPIE{command}{xargs}{def}#d
\RenewDocumentCommandPIE{command}{xargs}{def}#d
\DeclareDocumentCommandPIE{command}{xargs}{def}#d
\ProvideDocumentCommandPIE{command}{xargs}{def}#d
\newmathcommandPIE{command}[args]{def}#d
\renewmathcommandPIE{command}[args]{def}#d
\declaremathcommandPIE{command}[args]{def}#d
\NewDocumentMathCommandPIE{command}{xargs}{def}#d
\RenewDocumentMathCommandPIE{command}{xargs}{def}#d
\DeclareDocumentMathCommandPIE{command}{xargs}{def}#d
\ProvideDocumentMathCommandPIE{command}{xargs}{def}#d

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
