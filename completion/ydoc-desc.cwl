# ydoc-code package
# Matthew Bertucci 11/13/2021 for v0.6alpha

#include:needspace
#include:shortvrb
#include:etoolbox
#include:xcolor
#include:hyperref
#include:xspace

macrodesc#B
keydesc#B
macroimpl#B
meta#B
scriptcolor#B
optioncolor#B
optional#B
metaoptional#B
urlcolor#B
linkcolor#B
filecolor#B
citecolor#B
anchorcolor#B
menucolor#B
runcolor#B

\meta{arg}
\marg{arg}
\oarg{arg}
\parg{arg}
\aarg{arg}
\sarg{arg}

\pkg{package}
\cls{class}
\lib{library}
\env{envname}
\opt{option}
\optpar{option}
\file{file}

\pkgstyle{text}#*
\clsstyle{text}#*
\libstyle{text}#*
\envstyle{text}#*
\optstyle{text}#*
\filestyle{text}#*

cls#B
lib#B
env#B
file#B
pkg#B
opt#B

\cs{csname}
\cmd{cmd}
\Key{keyname}

\macrodescstyle#*
\keydescstyle#*
\macroargsstyle#*
\envcodestyle#*
\verbstyle#*
\metastyle#*
\margstyle#*
\Optional#*
\optional#*
\optionalstyle#*
\optionalon#*
\optionaloff#*
\oargstyle#*
\pargstyle#*
\aargstyle#*
\sargstyle#*
\descindent#*
\beforedescskip#*
\afterdescskip#*
\descsep#*

\AlsoMacro{macro}
\DescribeMacro{macro}
\DescribeScript{script}
\DescribeKey{keyname}
\MakeShortMacroArgs{\%<char%>}
\DeleteShortMacroArgs{\%<char%>}

\Macro{macro}
\MacroArgs{args}
\begin{DescribeMacros}
\end{DescribeMacros}
\begin{DescribeKeys}
\end{DescribeKeys}
\DescribeMacrosTabcolsep#*
\begin{DescribeMacrosTab}{cols}#\tabular
\end{DescribeMacrosTab}
\DescribeLength{length macro}{default value}
\DescribeEnv{envname}
\begin{DescribeEnv}{envname}
\end{DescribeEnv}

\descbox#*
\PrintMacroName{macro}#*
\PrintKeyName{keyname}#*
\PrintLengthName{length macro}#*
\PrintEnvName{\begin}{%<envname%>}#*
\PrintEnvName{\end}{%<envname%>}#*
\PrintMacros#*
\PrintLength#*
\PrintEnv#*
\PrintSubEnv#*

\bslash
\percent
\braceleft
\braceright

\codeline{arg}
\codelinebefore#*
\codelineafter#*
\begin{codequote}
\end{codequote}
\begin{macroquote}
\end{macroquote}