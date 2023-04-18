# scrextend package
# Matthew Bertucci 2023/04/17 for v3.39

#include:scrkbase
#include:scrlogo

#keyvals:\KOMAoptions#c
draft=#true,on,yes,false,off,no
overfullrule=#true,on,yes,false,off,no
fontsize=##L
titlepage=#true,on,yes,false,off,no,firstiscover
cleardoublepage=#empty,headings,letter,myheadings,plain,plain.letter,scrheadings,plain.scrheadings,current
footnotes=#multiple,nomultiple
#endkeyvals

#keyvals:\setkomafont#c,\addtokomafont#c,\usekomafont#c,\usesizeofkomafont#c,\usefamilyofkomafont#c,\useseriesofkomafont#c,\useshapeofkomafont#c,\useencodingofkomafont#c,\usefontofkomafont#c
subtitle
titlehead
author
date
publishers
dedication
sectioning
disposition
dictum
dictumauthor
dictumtext
labelinglabel
labelingseparator
#endkeyvals

\begin{addmargin*}[inner indent%l]{indent%l}
\begin{addmargin*}{indent%l}
\begin{addmargin}[left indent%l]{indent%l}
\begin{addmargin}{indent%l}
\begin{labeling}[delimiter]{widest pattern}
\begin{labeling}{widest pattern}
\changefontsizes{font size}#*
\cleardoubleemptypage
\cleardoubleevenemptypage
\cleardoubleevenpage
\cleardoubleevenpageusingstyle{pagestyle%keyvals}
\cleardoubleevenplainpage
\cleardoubleevenstandardpage
\cleardoubleoddemptypage
\cleardoubleoddpage
\cleardoubleoddpageusingstyle{pagestyle%keyvals}
\cleardoubleoddplainpage
\cleardoubleoddstandardpage
\cleardoublepageusingstyle{pagestyle%keyvals}
\cleardoubleplainpage
\cleardoublestandardpage
\coverpagebottommargin#*
\coverpageleftmargin#*
\coverpagerightmargin#*
\coverpagetopmargin#*
\dedication{dedication%text}
\deffootnote[mark width%l]{indent%l}{parindent%l}{definition}#*
\deffootnote{indent%l}{parindent%l}{definition}#*
\deffootnotemark{definition}#*
\dictum[author]{text}
\dictum{text}
\dictumauthorformat{author}#*
\dictumrule#*
\dictumwidth#*
\end{addmargin*}
\end{addmargin}
\end{labeling}
\extratitle{short title}
\FamilyElseValue#*
\frontispiece{frontispiece%text}
\Ifthispageodd{true code}{false code}#*
\ifthispagewasodd#*
\labelinglabel{arg}#*
\lowertitleback{titlebackfoot%text}
\maketitle[page number]
\marginline{margin note%text}
\maybesffamily
\multfootsep#*
\multiplefootnotemarker#*
\multiplefootnoteseparator#*
\publishers{publisher}
\raggeddictum#*
\raggeddictumauthor#*
\raggeddictumtext#*
\raggedfootnote#*
\sectfont#*
\subject{subject%text}
\subtitle{subtitle%text}
\textmaybesf{text}
\thefootnotemark#*
\thispagewasoddfalse#*
\thispagewasoddtrue#*
\titlefont#*
\titlehead{title head%text}
\uppertitleback{titlebackhead%text}

#keyvals:\cleardoubleevenpageusingstyle#c,\cleardoubleoddpageusingstyle#c,\cleardoublepageusingstyle#c
headings
myheadings
empty
plain
#endkeyvals

# deprecated
\ifthispageodd#S
