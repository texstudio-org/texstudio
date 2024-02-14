# contract package
# Matthew Bertucci 2024/02/09 for v0.91

#include:scrkbase
#include:tocbasic

\contractSetup{options%keyvals}

#keyvals:\contractSetup,\usepackage/contract#c
juratotoc=%<true|false|<integer>%>
juratocindent=##L
juratocnumberwidth=##L
contract
juratitlepagebreak#true,false
clausemark=#both,false,off,no,forceboth,forceright,right
parnumber=#auto,true,false,manual
ref=#long,numeric,clauseonly,onlyclause,ClauseOnly,OnlyClause,parlong,longpar,ParL,parnumeric,numericpar,ParN,paroff,nopar,parshort,shortpar,ParS,sentencelong,longsentence,SentenceL,sentencenumeric,numericsentence,SentenceN,sentenceoff,nosentence,sentenceshort,shortsentence,SentenceS,short
#endkeyvals

\begin{contract}
\end{contract}

\Clause[properties%keyvals]
\SubClause[properties%keyvals]

#keyvals:\Clause,\SubClause
dummy
head=%<running head%>
nohead
notocentry
number=%<number%>
preskip=##L
postskip=##L
title=%<text%>
tocentry=%<entry%>
#endkeyvals

\Clauseformat#*
\thepar#*
\theHpar#*
\parformat#*
\parformatseparation#*
\withoutparnumber#*
\ellipsispar
\ellipsispar[number]
\parellipsis#*
\thesentence#*
\theHsentence#*
\sentencenumberformat#*
\Sentence
\refL{label}#r
\refS{label}#r
\refN{label}#r
\refClause{label}#r
\refClauseN{label}#r
\refPar{label}#r
\refParL{label}#r
\refParS{label}#r
\refParN{label}#r
\refParN[number format]{label}#r
\refSentence{label}#r
\refSentenceL{label}#r
\refSentenceS{label}#r
\refSentenceN{label}#r

\DeclareNewJuraEnvironment{envname}{begdef}{enddef}#N
\DeclareNewJuraEnvironment{envname}[properties%keyvals]{begdef}{enddef}#N

#keyvals:\DeclareNewJuraEnvironment
Clause=%<command%>
ClauseFont=%<commands%>
SubClause=%<command%>
Sentence=%<command%>
ClauseNumberFormat=%<command%>
#endkeyvals

\parname#*
\parshortname#*
\sentencename#*
\sentenceshortname#*

# not in main documentation
\AutoPar#S
\Clausemark#S
\DeprecatedParagraph#S
\getmaxpar{arg1}{arg2}{arg3}#S
\ifparnumber#S
\ManualPar#S
\newmaxpar{arg1}{arg2}{arg3}#S
\ParagraphCompatibilityHacks#S
\parciteformat#S
\parlongformat#S
\parnumberfalse#S
\parnumbertrue#S
\parnumericformat#S
\parshortformat#S
\sentenceciteformat#S
\sentencelongformat#S
\sentencenumericformat#S
\sentenceshortformat#S
\thecontractAbsoluteClause#S
\thecontractClause#S
\thecontractSubClause#S
\theHClause#S
\theHSubClause#S
\thisparnumber#S

# deprecated
\Paragraph#S
\refParagraph#S
\refParagraphN#S
\SubParagraph#S