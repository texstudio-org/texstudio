# fetchbibpes package
# Matthew Bertucci 2022/05/13 for v2.4.10

#include:xkeyval

#keyvals:\usepackage/fetchbibpes#c
deffolder=%<file path%>
useverses={%<file1,file2,...%>}
useselverses
usesr
fetchsubtr
ignorecfg
cfg=%<name%>
#endkeyvals

\fetchverse{book ch:vrs}
\fetchverse[options%keyvals]{book ch:vrs}
\fetchverses{book ch:vrs}
\fetchverses[options%keyvals]{book ch:vrs}
\fetchverses*{book ch:vrs}
\fetchverses*[options%keyvals]{book ch:vrs}

#keyvals:\fetchverse,\fetchverses,\fetchverses*,\useBookStyle,\fetchversestxt
abbr=#esword,none,long,short
roman#true,false
from=#KVJ,KVJ+,ISV
alt=%<word%>
alt*={%<word1,word2,...%>}
transl=%<text%>
from*=#KJV,KJV+,ISV
pcolor=#%color
pformat=%<format cmds%>
delims=%<<tok1><tok2>%>
enclosewith=%<<tok1><tok2>\quote%>
format=%<format cmds%>
caps#true,false
showfirst#true,false
shownone
useperiod#true,false
citeatend#true,false
nocite
priorref=
ltxquotes
replace={%<find1%>}{%<replace1%>}%<{find2}{replace2}...%>
localdefs={%<localdefs%>}
typeset=
typeset*=
#endkeyvals

\useOldAlt
\useNewAlt
\showTranslAlways
\showTranslDecld
\verseFmt{text}#*
\quote#*
\LaTeXQuotesOff
\LaTeXQuotesOn
\gobbleto{word}{cmd}#d
\addtoBibles{list}
\defaultBible{transl}
\fbdefaultBible#*
\useBookStyle{options%keyvals}
\usePassage{verse ref}
\fetchversestxt{book ch:vrs}
\fetchversestxt[options%keyvals]{book ch:vrs}
\versetxt
\passagetxt
\cobblevrs{cmd}{text}#d
\cobblevrs*{cmd}{text}#d
\translFmt{definition}
\translFmtDef#*
\translTxtFmt{definition}
\translTxtFmtDef#*
\priorRefSpc{space cmd}
\fbFitItIn
\fbFillRght
\afterBookSpc{space cmd}
\resetAfterBookSpc
\afterRef{code}
\afterNumSpc{space cmd}
\verseFmtReset
\verseFmtDef{text}#*
\afterVerseFmt{cmd}
\registerBibles{list}
\verseCmts{{%<comment1%>}{%<comment2%>}%<...%>}
\fbMarParFmt{text}#*
\fbResetMarParFmt
\fbMarNotesOn
\fbMarNotesOff
\selectedVersesFrom{{from=%<version%>,onlyverses={%<verses%>}}%<...%>}

#ifOption:usesr
\sr{text}{passages}
#endif

\begin{declareBVs}
\end{declareBVs}
\begin{declareBVs*}
\end{declareBVs*}
\BV(verse ref)
\null

#ifOption:fetchsubtr
\markverse{book ch:vrs}
\markverse[options%keyvals]{book ch:vrs}
#keyvals:\markverse
name=%<name%>
from=%<transl%>
marks={%<bfind1%>}{%<efind1%>}%<{bfind2}{efind2}...%>
#endkeyvals
\bMrkFP
\eMrkFP
#endif
#ifOption:fetchsubstr
\markverse{book ch:vrs}
\markverse[options%keyvals]{book ch:vrs}
#keyvals:\markverse
name=%<name%>
from=%<transl%>
marks={%<bfind1%>}{%<efind1%>}%<{bfind2}{efind2}...%>
#endkeyvals
\bMrkFP
\eMrkFP
#endif

\begin{fpquote}
\begin{fpquote}[options%keyvals]
\end{fpquote}
\begin{fpverse}
\begin{fpverse}[options%keyvals]
\end{fpverse}
\begin{fpquotation}
\begin{fpquotation}[options%keyvals]
\end{fpquotation}

#keyvals:\begin{fpquote},\begin{fpverse},\begin{fpquotation}
leftmargin=##L
rightmargin=##L
#endkeyvals

#keyvals:\begin{fpverse},\begin{fpquotation}
itemindent=##L
#endkeyvals

\bDQ
\eDQ
\bSQ
\eSQ

# not documented
\letEach%<\cmd1\cmd2...%>\to%<\cmd%>#*
\letEach{cmd}#Sd
\to#S
\AlwaysShowDefBible#*
\bookexistsfalse#*
\bookexiststrue#*
\bookFmt{arg1}{arg2}{arg3}{arg4}#*
\csarg{arg1}{arg2}#*
\cvrtdqs#*
\expBkAbbrChoices#*
\fbSetFromChoiceKey{arg1}#*
\fetchInputMsg#*
\fetchsubstrfalse#*
\fetchsubstrtrue#*
\fetchtoks{arg}#*
\fetchversetxt#*
\fetchWarningMsg#*
\fsbstrInputMsg#*
\fsbstrWarningMsg#*
\G{nnnn}#*
\H{nnnn}#*
\handleUnRegBibles{arg1}#*
\ifbookexists#*
\iffetchsubstr#*
\ifparsefetcharg#*
\ifshowDefBible#*
\ifuseoldalt#*
\ifversestochend#*
\iiioiv{arg1}{arg2}{arg3}{arg4}#*
\inputVerseList{arg1}#*
\ioiv{arg1}{arg2}{arg3}{arg4}#*
\isitstar#*
\isstopreplace{arg1}#*
\istopreplacei{arg1}#*
\NeverShowDefBible#*
\parsefetchargfalse#*
\parsefetchargtrue#*
\selBkAbbr#*
\setNumStyle#*
\showDefBiblefalse#*
\showDefBibletrue#*
\srInputMsg#*
\srWarningMsg#*
\useoldaltfalse#*
\useoldalttrue#*
\useverseslist#*
\verseCmtsi{arg1}#*
\versestochendfalse#*
\versestochendtrue#*