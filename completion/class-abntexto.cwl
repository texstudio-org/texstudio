# abntexto class
# Matthew Bertucci 2023/02/01 for v2.0.0-alpha

#include:keyval

## Fonte tipográfica ##
\setfontsize{id}
\definefontsize{id}{definições}
\sizedef{cmd}{tamanho}{entrelinha natural}{definições}
\spacing{factor}
\singlesp
\onehalfsp
\doublesp

## Layout ##
\setlayout{keyvals}

#keyvals:\setlayout
paper=%<size%>
width=##L
height=##L
left=##L
right=##L
top=##L
bottom=##L
twoside#true,false
#endkeyvals

\pretextual
\textual

## Sumário ##
\tocifont#*
\tociifont#*
\tociiifont#*
\tocivfont#*
\tocvfont#*
\sectionfont#*
\subsectionfont#*
\subsubsectionfont#*
\paragraphfont#*
\subparagraphfont#*
\abovesection#*
\abovesubsection#*
\abovesubsubsection#*
\aboveparagraph#*
\abovesubparagraph#*
\belowsection#*
\belowsubsection#*
\belowsubsubsection#*
\belowparagraph#*
\belowsubparagraph#*
\maketoc

## Alíneas ##
\begin{topics}
\end{topics}

## Áreas de legenda ##
\place{content%text}
\legend{type}{content%text}
\src{texto%text}
\aboveplace#*
\belowplace#*
\definelegendplace{type}{name}{list name}{ref def}{ext}

## Citações ##
\enquote{texto%text}
\Enquote{texto%text}

## Apêndice e anexo ##
\annex
\appendixlabelwidth#*
\annexlabelwidth#*

## Glossário ##
\corrprinton
\corrprintoff

# not documented
\addtotoc#S
\advcount{arg1}#S
\annexlabelbox{arg}#S
\appendixlabelbox{arg}#S
\cfparagraph#S
\cfsection#S
\cfsubparagraph#S
\cfsubsection#S
\cfsubsubsection#S
\countannex#S
\countappendix#S
\countparagraph#S
\countseclevel#S
\countsection#S
\countsubparagraph#S
\countsubsection#S
\countsubsubsection#S
\counttopics#S
\counttopicsdepth#S
\currspacing#S
\Enter#S
\extlabelwidth#S
\extleaders#S
\extline{arg1}{arg2}{arg3}{arg4}#S
\extpagenumwidth#S
\extrightmargin#S
\hangfrom#S
\heading{arg1}#S
\hreftocline{arg1}#S
\identifyparagraph#S
\identifysection#S
\identifysubparagraph#S
\identifysubsection#S
\identifysubsubsection#S
\indexcard{arg1}#S
\indexcardA{arg1}#S
\indexcardbar#S
\judgeline{arg1}#S
\legendlabel#S
\legendmaxwidth#S
\legendname#S
\makeext{arg}#S
\marksection{arg}#S
\marksubsection{arg}#S
\nbpar#S
\noindentfirst#S
\recountseci#S
\recountsecii#S
\recountseciii#S
\recountseciv#S
\setcurrlabel{arg}#S
\setnormalsize#S
\setsmall#S
\srclabel#S
\startparagraph{arg}#S
\startsection{arg}#S
\startsubparagraph{arg}#S
\startsubsection{arg}#S
\startsubsubsection{arg}#S
\theannex#S
\theappendix#S
\thelegend#S
\toclabelbox{arg1}#S
\toclabelwidth#S
\tocname#S
\topicsitem#S
\topicslabeli#S
\topicslabelii#S
\topicslabelwidth#S
\topicsmakelabel#S
\tryindentfirst#S
\twonewpage#S
\xindexcardbar#S