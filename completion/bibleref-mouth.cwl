# bibleref-mouth package
# Matthew Bertucci 10/23/2021 for v1.0

#include:fmtcount
#include:hyperref

\bibleref{reference}

\setbiblestyle{style name%keyvals}

#keyvals:\setbiblestyle#c
fullname
jerusalem
anglosaxon
JEH
NTG
MLA
chicago
text
verse
biblegateway.com
#endkeyvals

\thebook{passage}#*
\thechapter{passage}#*
\theverse{passage}#*
\bookchapterseparator{separators}#*
\chapterverseseparator{separators}#*
\ifsamebook{left}{right}{truehandler}{falsehandler}#*
\ifsamechapter{left}{right}{truehandler}{falsehandler}#*
\ifsameverse{left}{right}{truehandler}{falsehandler}#*
\ifhasbook{passage}{truehandler}{falsehandler}#*
\ifhaschapter{passage}{truehandler}{falsehandler}#*
\ifhasverse{passage}{truehandler}{falsehandler}#*
\thebookname{style name}{passage}#*

\providebiblestyle{style name}{formatting}
\providebiblebookalias{book}{alias}
\providebiblebook{style name}{book}{bookname}

\standardbiblestyle{bkstyle}{bkchsep}{chvsep}{bksep}{chsep}{vsep}{rangesep}{chstyle}{vstyle}{beginpassage}{endpassage}{list}#*
\providebiblegatewayurl{url style name}{version}#*
\providebiblegatewaystyle{style name}{url style name}{text style name}#*