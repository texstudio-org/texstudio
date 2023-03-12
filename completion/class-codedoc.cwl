# codedoc class
# Matthew Bertucci 11/6/2021 for v0.3

#keyvals:\documentclass/codedoc#c
autoclose
index
noheader
obeystop
tracing0
tracing1
tracing2
%<class name%>
#endkeyvals

### 1 Code & Documentation ###
## 1.1 Writing code ##
\ProduceFile{file}
\ProduceFile{file}[file name]
\ProduceFile{file}[file name][file version]
\ProduceFile{file}[file name][file version][file date]
\FileSource
\FileName
\FileVersion
\FileDate
\CloseFile{file}
\begin{code}#V
\end{code}
\begin{code*}#V
\end{code*}
\CodeFont{font specs}
\LineNumber{envname}{font specs}{width}
\LineNumber{envname}{font specs}{width}[number]
\begin{invisible}
\end{invisible}
\Header{text}
\AddBlankLine
\TabSize{number}
\Gobble{number}
\BoxTolerance{dimen%l}

## 1.2 Macros to describe macros ##
\DescribeMacro{macro}
\DefineMacro{macro}
\DescribeEnvironment{envname}
\DefineEnvironment{envname}
\DescribeIndexFont{font specs}
\DefineIndexFont{font specs}
\PrintMacro{macro}
\DocStripMarginpar
\IgnorePrefix{macro prefix}
\PrintPrefix{macro prefix}
\meta{arg}
\marg{arg}
\oarg{arg}
\parg{arg}
\bslash
\StopHere{code}

## 1.3 Choosing the class ##
#ifOption:memoir
#include:class-memoir
#endif
#ifOption:book
#include:class-book
#endif
#ifOption:ltxdockit
#include:class-ltxdockit
#endif
#ifOption:scrartcl
#include:class-scrartcl
#endif
#ifOption:scrbook
#include:class-scrbook
#endif
#ifOption:scrreprt
#include:class-scrreprt
#endif
#ifOption:scrlttr2
#include:class-scrlttr2
#endif
#ifOption:ltxdoc
#include:class-ltxdoc
#endif
#ifOption:report
#include:class-report
#endif
#ifOption:ltxguide
#include:class-ltxguide
#endif
#ifOption:ltxguidex
#include:class-ltxguidex
#endif
#ifOption:l3doc
#include:class-l3doc
#endif

## 1.4 Dangerous strings ##
\DangerousEnvironment{envname list}
\StartIgnore
\StopIgnore

### 2 Verbatim Madness ###
## 2.1 Example environments ##
\begin{example}
\end{example}
\begin{example*}
\end{example*}
\CodeInput
\CodeOutput
\NewExample{envname}{code input}{code output}{immediate execution}#N
\NewExample[options%keyvals]{envname}{code input}{code output}{immediate execution}#N
\RenewExample{envname}{code input}{code output}{immediate execution}
\RenewExample[options%keyvals]{envname}{code input}{code output}{immediate execution}
#keyvals:\NewExample,\RenewExample
numbered
continuous
visibleEOL
#endkeyvals
\eTeXOff
\eTeXOn

## 2.2 \ShortVerb and friends ##
\ShortVerb{character}
\UndoShortVerb
\ShortCode{character}
\ShortCode[example name]{character}
\UndoShortCode
\VerbBreak{character}
\UndoVerbBreak
\VerbCommand{escape}{left brace}{right brace}
\UndoVerbCommand
\CodeEscape{character}
\UndoCodeEscape

## Miscellaneous ##
\AtChar#*
#ifOption:index
#include:makeidx
#endif
