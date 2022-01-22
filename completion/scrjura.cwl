# scrjura package
# Matthew Bertucci 11/19/2021 for v3.34

#include:scrkbase
#include:tocbasic

#keyvals:\usepackage/scrjura#c
contract
#endkeyvals

#keyvals:\KOMAoptions#c,\usepackage/scrjura#c
juratotoc=#true,on,yes,false,off,no
juratocindent=##L
juratocnumberwidth=##L
juratitlepagebreak=#true,on,yes,false,off,no
clausemark=#both,false,off,no,forceboth,forceright,right
parnumber=#true,false,auto,manual
ref=#long,numeric,clauseonly,onlyclause,ClauseOnly,OnlyClause,parlong,longpar,ParL,parnumeric,numericpar,ParN,paroff,nopar,parshort,shortpar,ParS,sentencelong,longsentence,SentenceL,sentencenumeric,numericsentence,SentenceN,sentenceoff,nosentence,sentenceshort,shortsentence,SentenceS,short
#endkeyvals

#keyvals:\setkomafont#c,\addtokomafont#c,\usekomafont#c,\usesizeofkomafont#c,\usefamilyofkomafont#c,\useseriesofkomafont#c,\useshapeofkomafont#c,\useencodingofkomafont#c,\usefontofkomafont#c
Clause
contract.Clause
parnumber
sentencenumber
#endkeyvals

\Clausemark{text}#*
\ellipsispar#*
\ellipsispar[number]#*
\parellipsis#*
\thecontractClause#*
\Clauseformat{number}#*
\thecontractSubClause#*

\DeclareNewJuraEnvironment{envname}{start code}{end code}#*N
\DeclareNewJuraEnvironment{envname}[options%keyvals]{start code}{end code}#*N

#keyvals:\DeclareNewJuraEnvironment#c
Clause=%<command%>
ClauseFont=%<commands%>
SubClause=%<command%>
Sentence=%<command%>
ClauseNumberFormat=%<command%>
#endkeyvals

\begin{contract}
\end{contract}

\Clause
\Clause[options%keyvals]
\SubClause
\SubClause[options%keyvals]
\Sentence

#keyvals:\Clause#c,\SubClause#c
dummy
head=%<running head%>
nohead
notocentry
number=%<number%>
preskip=##L
postskip=##L
title=%<title%>
tocentry=%<entry%>
#endkeyvals

\refClause{label}#r
\refClauseN{label}#r
\refL{label}#r
\refS{label}#r
\refN{label}#r
\refPar{label}#r
\refParL{label}#r
\refParS{label}#r
\refParN[number format]{label}#r
\refSentence{label}#r
\refSentenceL{label}#r
\refSentenceS{label}#r
\refSentenceN{label}#r

\theClause#*
\theSubClause#*
\theHClause#*
\theHSubClause#*
\thepar#*
\theHpar#*
\AutoPar#*
\ManualPar#*
\parformat#*
\parformatseparation#*
\withoutparnumber#*
\thisparnumber#*
\thesentence#*
\theHsentence#*
\sentencenumberformat#*
\parciteformat#*
\sentenceciteformat#*
\parlongformat#*
\parshortformat#*
\parnumericformat#*
\sentencelongformat#*
\sentenceshortformat#*
\sentencenumericformat#*
\parname#*
\parshortname#*
\sentencename#*
\sentenceshortname#*
\newmaxpar{envname}{arg1}{arg2}#*
\getmaxpar{envname}{arg1}{arg2}#*

# deprecated
\DeprecatedParagraph#S
\ParagraphCompatibilityHacks#S
\Paragraph#S
\SubParagraph#S
\refParagraph#S
\refParagraphN#S
