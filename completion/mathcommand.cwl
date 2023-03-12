# mathcommand package
# Matthew Bertucci 2021/07/22 for v1.04

#include:l3keys2e
#include:etoolbox

\newmathcommand{cmd}{def}#d
\newmathcommand{cmd}[args]{def}#d
\newmathcommand{cmd}[args][default]{def}#d
\newtextcommand{cmd}{def}#d
\newtextcommand{cmd}[args]{def}#d
\newtextcommand{cmd}[args][default]{def}#d
\renewmathcommand{cmd}{def}
\renewmathcommand{cmd}[args]{def}
\renewmathcommand{cmd}[args][default]{def}
\renewtextcommand{cmd}{def}
\renewtextcommand{cmd}[args]{def}
\renewtextcommand{cmd}[args][default]{def}
\declaremathcommand{cmd}{def}#d
\declaremathcommand{cmd}[args]{def}#d
\declaremathcommand{cmd}[args][default]{def}#d
\declaretextcommand{cmd}{def}#d
\declaretextcommand{cmd}[args]{def}#d
\declaretextcommand{cmd}[args][default]{def}#d
\NewDocumentMathCommand{cmd}{xargs}{def}#d
\NewDocumentTextCommand{cmd}{xargs}{def}#d
\RenewDocumentMathCommand{cmd}{xargs}{def}
\RenewDocumentTextCommand{cmd}{xargs}{def}
\DeclareDocumentMathCommand{cmd}{xargs}{def}#d
\DeclareDocumentTextCommand{cmd}{xargs}{def}#d
\ProvideDocumentMathCommand{cmd}{xargs}{def}#d
\ProvideDocumentTextCommand{cmd}{xargs}{def}#d
\declarecommand{cmd}{def}#d
\declarecommand{cmd}[args]{def}#d
\declarecommand{cmd}[args][default]{def}#d
\storecommand{cmd}
\storecommand[prefix]{cmd}

\IfEmptyTF{string}{NoValueCode}{ValueCode}
\EmptyContent{arg}#*
\GetIndex{string}
\GetExponent{string}

\newcommandPIE{cmd}{def}#d
\newcommandPIE{cmd}[args]{def}#d
\newcommandPIE{cmd}[args][default]{def}#d
\renewcommandPIE{cmd}{def}
\renewcommandPIE{cmd}[args]{def}
\renewcommandPIE{cmd}[args][default]{def}
\declarecommandPIE{cmd}{def}#d
\declarecommandPIE{cmd}[args]{def}#d
\declarecommandPIE{cmd}[args][default]{def}#d
\NewDocumentCommandPIE{cmd}{xargs}{def}#d
\RenewDocumentCommandPIE{cmd}{xargs}{def}
\DeclareDocumentCommandPIE{cmd}{xargs}{def}#d
\ProvideDocumentCommandPIE{cmd}{xargs}{def}#d
\newmathcommandPIE{cmd}{def}#d
\newmathcommandPIE{cmd}[args]{def}#d
\newmathcommandPIE{cmd}[args][default]{def}#d
\renewmathcommandPIE{cmd}{def}
\renewmathcommandPIE{cmd}[args]{def}
\renewmathcommandPIE{cmd}[args][default]{def}
\declaremathcommandPIE{cmd}{def}#d
\declaremathcommandPIE{cmd}[args]{def}#d
\declaremathcommandPIE{cmd}[args][default]{def}#d
\NewDocumentMathCommandPIE{cmd}{xargs}{def}#d
\RenewDocumentMathCommandPIE{cmd}{xargs}{def}
\DeclareDocumentMathCommandPIE{cmd}{xargs}{def}#d
\ProvideDocumentMathCommandPIE{cmd}{xargs}{def}#d

\LoopCommands{list}{code}
\LoopCommands{%<list%>}[%<name1%>]%<[name2]...[name7]%>{%<code%>}
\lettersUppercase
\lettersLowercase
\lettersAll
\lettersGreekLowercase
\lettersGreekUppercase
\lettersGreekAll

\disablecommand{cmds}
\suggestcommand{cmd}{suggestion}

\mathcommandconfigure{keyvals}

#keyvals:\mathcommandconfigure
disabled=#error,warning,silent
#endkeyvals
