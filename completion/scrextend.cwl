# scrextend package
# Matthew Bertucci 11/19/2021 for v3.34

#include:scrkbase

#keyvals:\KOMAoptions#c
draft=#true,on,yes,false,off,no
overfullrule=#true,on,yes,false,off,no
fontsize=##L
titlepage=#true,on,yes,false,off,no,firstiscover
cleardoublepage=#empty,headings,letter,myheadings,plain,plain.letter,scrheadings,plain.scrheadings,current
footnotes=#multiple,nomultiple
egregdoesnotlikesansseriftitles
#endkeyvals

\cleardoubleoddstandardpage
\cleardoubleoddpageusingstyle{page style}
\cleardoubleoddemptypage
\cleardoubleoddplainpage
\cleardoubleevenstandardpage
\cleardoubleevenpageusingstyle{page style}
\cleardoubleevenemptypage
\cleardoubleevenplainpage
\cleardoublestandardpage
\cleardoubleoddpage
\cleardoubleevenpage
\cleardoublepageusingstyle{page style}
\cleardoubleemptypage
\cleardoubleplainpage
\changefontsizes{font size}#*

\extratitle{short title}
\frontispiece{frontispiece%text}
\titlehead{title head%text}
\subject{subject%text}
\subtitle{subtitle%text}
\publishers{publisher}
\uppertitleback{titlebackhead%text}
\lowertitleback{titlebackfoot%text}
\dedication{dedication%text}
\maketitle[page number]
\coverpagetopmargin#*
\coverpagebottommargin#*
\coverpageleftmargin#*
\coverpagerightmargin#*

\titlefont#*
\dictum{text}
\dictum[author]{text}
\dictumrule#*
\dictumwidth#*
\raggeddictum#*
\dictumauthorformat{author}#*
\raggeddictumtext#*
\raggeddictumauthor#*
\ifthispagewasodd#*
\thispagewasoddtrue#*
\thispagewasoddfalse#*
\Ifthispageodd{true code}{false code}#*
\marginline{margin note%text}
\raggedfootnote#*
\deffootnote{indent%l}{parindent%l}{definition}#*
\deffootnote[mark width%l]{indent%l}{parindent%l}{definition}#*
\deffootnotemark{definition}#*
\thefootnotemark#*
\multiplefootnoteseparator#*
\multfootsep#*
\multiplefootnotemarker#*
\sectfont#*
\FamilyElseValue#*
\begin{labeling}{widest pattern}
\begin{labeling}[delimiter]{widest pattern}
\end{labeling}
\labelinglabel{arg}#*
\begin{addmargin}{indent%l}
\begin{addmargin}[left indent%l]{indent%l}
\end{addmargin}
\begin{addmargin*}{indent%l}
\begin{addmargin*}[inner indent%l]{indent%l}
\end{addmargin*}

# deprecated
\ifthispageodd#S
