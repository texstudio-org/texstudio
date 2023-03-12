# doc package
# Matthew Bertucci 2022/05/18 for v3.0h

#include:l3keys2e
#include:multicol
#include:hypdoc

\SetupDoc{options%keyvals}#c

#keyvals:\usepackage/doc#c,\SetupDoc#c
hyperref#true,false
nohyperref#true,false
multicol#true,false
nomulticol#true,false
debugshow#true,false
noindex#true,false
noprint#true,false
reportchangedates#true,false
toplevel#true,false
notoplevel#true,false
#endkeyvals

\DocInput{file}#i
\IndexInput{file}#i

\begin{macrocode}
\end{macrocode}
\begin{macrocode*}
\end{macrocode*}

\DescribeMacro{macro%cmd}
\DescribeMacro[options%keyvals]{macro%cmd}
\DescribeEnv{envname}
\DescribeEnv[options%keyvals]{envname}

\begin{macro}{macro%cmd}
\begin{macro}[options%keyvals]{macro%cmd}
\end{macro}
\begin{environment}{envname}
\begin{environment}[options%keyvals]{envname}
\end{environment}

#keyvals:\DescribeMacro#c,\DescribeEnv#c,\begin{macro}#c,\begin{environment}#c
noindex
noprint
#endkeyvals

\MacrocodeTopsep#*
\MacroTopsep#*
\MacroIndent#*
\MacroFont#*

\PrintDescribeMacro{macro%cmd}
\PrintDescribeEnv{envname}
\PrintMacroName{macro%cmd}
\PrintEnvName{envname}

\NewDocElement{element}{envname}#N
\NewDocElement[options%keyvals]{element}{envname}#N
\RenewDocElement{element}{envname}
\RenewDocElement[options%keyvals]{element}{envname}

#keyvals:\NewDocElement#c,\RenewDocElement#c
macrolike#true,false
envlike#true,false
toplevel#true,false
notoplevel#true,false
idxtype=%<string%>
printtype=%<string%>
idxgroup=%<string%>
noindex#true,false
noprint#true,false
#endkeyvals

\SpecialEscapechar

\DisableCrossrefs
\EnableCrossrefs
\DoNotIndex{macro list%definition}
\PageIndex
\CodelineIndex
\theCodelineNo
\CodelineNumbered

\actualchar#*
\quotechar#*
\encapchar#*
\levelchar#*
\SpecialMainMacroIndex{cmd}
\SpecialMainEnvIndex{envname}
\SpecialMacroIndex{cmd}
\SpecialEnvIndex{envname}
\SpecialIndex{cmd}
\SpecialShortIndex{cmd}
\SpecialMainIndex{cmd}#*
\SpecialUsageIndex{cmd}#*
\SortIndex{sort key}{index entry}
\verbatimchar#*
\*#S
\PrintIndex
\IndexMin#*
\IndexPrologue{text}
\IndexParms#*
\main{text%plain}#*
\usage{text%plain}#*
\code{text%plain}#*

\DocstyleParms#*

\MakeShortVerb{\%<character%>}
\MakeShortVerb*{\%<character%>}
\DeleteShortVerb{\%<character%>}
# following three lines tell highlighter not to mark args as incorrect
\MakeShortVerb{definition}#S
\MakeShortVerb*{definition}#S
\DeleteShortVerb{definition}#S

\Web
\AmSTeX
\BibTeX
\SliTeX
\PlainTeX
\meta{arg}
\OnlyDescription
\MaybeStop{finale code}
\StopEventually{finale code}#*
\Finale
\AlsoImplementation
\changes{version}{date}{text}
\generalname#*
\cs{csname}
\RecordChanges
\PrintChanges
\GlossaryMin#*
\GlossaryPrologue{text}
\GlossaryParms#*
\begin{theglossary}
\end{theglossary}
\bslash
\MakePrivateLetters
\DontCheckModules
\CheckModules
\Module{directive}
\AltMacroFont#*
\theStandardModuleDepth#*

\OldMakeindex#*
\percentchar#*
\CharacterTable{contents}#*
\CharTableChanges#*
\CheckSum{number}#*

# not in main documentation
\efill#*
\filedate#*
\fileinfo#*
\filename#*
\fileversion#*
\GetFileInfo{file}
\LeftBraceIndex#*
\MakePercentComment#*
\MakePercentIgnore#*
\PercentIndex#*
\pfill#*
\RecordIndexType{cmd}{type}#*
\RecordIndexTypeAux{cmd}{type}#*
\RightBraceIndex#*
\ShowIndexingState#*
