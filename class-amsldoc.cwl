# amsldoc class
# Matthew Bertucci 2022/06/24 for v2.07

#include:class-book
#include:url

# passes all options to book class
#keyvals:\documentclass/amsldoc#c
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
openright
openany
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

\begin{ctab}{cols}#\tabular
\begin{ctab}[pos]{cols}#\tabular
\end{ctab}
\begin{error}{message%text}
\end{error}
\begin{histnote}
\end{histnote}

\*{index entry}
\<#S
\<%<text%>>
\activevert#*
\actualchar#*
\addbslash{arg}#*
\allowtthyphens#*
\AmS
\amslatex/
\amstex/
\arg{arg}
\arrayargpatch#*
\autoindex{entry}#*
\bibtex/
\bslchar#*
\bst{BibTeX style}
\cls{class}
\cn{csname}
\cnat
\cnbang
\cnbreak#*
\cnm{csname}{arg}
\cnmm{csname}{arg1}{arg2}
\cnmsm{csname}{arg1}*{arg2}
\cnom{csname}{optarg}{arg}
\cnt{counter}
\cs{csname}#*
\embrace{text}#*
\encapchar#*
\env{envname}
\errexa
\errexpl
\errora{message%text}#*
\errorbullet#*
\fn{file name}
\fnt{font name}
\gloss{arg}#*
\indexcs{cs}
\latex/
\lbracechar#*
\levelchar#*
\mail{email%URL}#U
\makeindx/
\mdash
\ncn{csname}
\ndash
\nobslash{arg}#*
\ntt#*
\ommitude[optarg]{arg}#*
\ommitude{arg}#*
\openbox#*
\opt{option}
\pkg{package}
\qc{\%<<char>%>}
\qc{def}#S
\qcamp
\qcat
\qcbang
\qedsymbol
\qq{text}
\quotechar#*
\rbracechar#*
\secref{label}#r
\tex/
\Textures
\verbatimchar#*
\xypic/