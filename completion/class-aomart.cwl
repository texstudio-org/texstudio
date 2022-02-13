# aomart class
# Matthew Bertucci 2/12/2022 for v1.25

#include:class-amsart
#include:fancyhdr
#include:lastpage
#include:ifpdf
#include:environ
#include:yhmath
#include:cmtiup
#include:hyperref
# hyperref loaded with colorlinks option
#include:color

#keyvals:\documentclass/aomart#c
8pt
9pt
10pt
11pt
12pt
manuscript
screen
olddoi
doi2016
oldkeywords
printscheme
# options passed to amsart class
a4paper
centertags
draft
e-only
final
fleqn
landscape
leqno
letterpaper
noamsfonts
nomath
notitlepage
onecolumn
oneside
portrait
reqno
tbtags
titlepage
twocolumn
twoside
#endkeyvals

\orcid{orcid%URL}#U
\givenname{name}
\surname{name}
\fulladdress{full address%text}
\copyrightnote{note text%text}
\keyword{keyword%text}
\subject{primary or secondary}{classification scheme}{subject}
\formatdate{YYYY-MM-DD}
\received{\formatdate{YYYY-MM-DD}}
\revised{\formatdate{YYYY-MM-DD}}
\accepted{\formatdate{YYYY-MM-DD}}
\published{\formatdate{YYYY-MM-DD}}
\publishedonline{\formatdate{YYYY-MM-DD}}
\proposed{name}
\seconded{name}
\corresponding{name}
\editor{name}
\version{version}
\volumenumber{number}
\issuenumber{number}
\publicationyear{number}
\papernumber{number}
\startpage{number}
\endpage{number}
\publicationyear{year}
\doinumber{number}
\mrnumber{number}
\zblnumber{number}
\arxivnumber{number}
\oldsubsections#*
\widebar{arg}#m
\EditorialComment{comment%todo}#D
\fullref{word%text}{label}#r
\pfullref{word%text}{label}#r
\bfullref{word%text}{label}#r
\eqfullref{word%text}{label}#r
\fullpageref{label}#r
\fullpageref[prefix text%text]{label}#r
\newtheorem[code]{envname}{caption}#*N
\newtheorem*[code]{envname}{caption}#*N
\doi{DOI%URL}#U
\mr{mathscinet path%URL}#U
\zbl{zentralblatt path%URL}#U
\jfm{jahrbuch path%URL}#U
\arxiv{arxiv path%URL}#U
\annalsurl{URL}#*U

# deprecated
\specialdigits#S
\sishape#S
\textsi{text}#S