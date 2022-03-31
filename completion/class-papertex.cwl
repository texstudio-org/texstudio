# papertex class
# Matthew Bertucci 3/29/2022 for v1.2b

#include:ifthen
#include:ifpdf
#include:multido
#include:datetime
#include:multicol
#include:fancyhdr
#include:fancybox
#include:geometry
#include:graphicx
#include:color
#include:hyperref
#include:textpos
#include:hyphenat
#include:wrapfig
#include:lastpage
#include:setspace
#include:ragged2e

#keyvals:\documentclass/papertex#c
9pt
10pt
11pt
12pt
a3paper
columnlines
hyphenatedtitles
showgrid
#endkeyvals

\authorandplace{author}{place}
\begin{authorblock}
\end{authorblock}
\begin{editorial}{n}{heading%text}{author}{label}
\end{editorial}
\begin{frontpage}
\end{frontpage}
\begin{indexblock}{title%text}
\end{indexblock}
\begin{news}{n}{heading%text}{subheading%text}{pages of}{label}
\end{news}
\begin{shortnews}{n}{title%text}{subtitle%text}{label}
\end{shortnews}
\begin{weatherblock}{title%text}
\end{weatherblock}
\columntitle{type%keyvals}{text}
\edition{text}
\expandedtitle{type%keyvals}{text}
\firstimage{imagefile}{caption%text}#g
\firstnews{heading%text}{text}{time}
\foot{left%text}{center%text}{right%text}
\heading{left%text}{center%text}{right%text}
\image{imagefile}{caption%text}
\indexitem{text}{reference}
\minraggedcols=%<integer%>
\newsection{name}
\newssep
\secondnews{heading%text}{subheading%text}{text}{pages of}{time}
\shortnewsitem{heading%text}{text}
\thirdnews{heading%text}{subheading%text}{text}{pages of}{time}
\timestamp{time}
\weatheritem{imagefile}{day}{max}{min}{short desc%text}#g

#keyvals:\columntitle,\expandedtitle
shadowbox
doublebox
ovalbox
Ovalbox
lines
#endkeyvals

\columnlines#*
\editionFormat#*
\editorialAuthorFormat#*
\editorialTitleFormat#*
\firstTextFormat#*
\firstTitleFormat#*
\grid[show]{%<rows%>}{%<columns%>}#*
\grid{rows}{columns}#*
\headDateTimeFormat#*
\indexEntryFormat#*
\indexEntryPageFormat#*
\indexEntryPageTxt#*
\indexEntrySeparator#*
\indexFormat#*
\innerAuthorFormat#*
\innerPlaceFormat#*
\innerSubtitleFormat#*
\innerTextFinalMark#*
\innerTitleFormat#*
\logo#*
\minilogo#*
\mylogo{imagefile}#*g
\pagesFormat#*
\papertexInit#*
\pictureCaptionFormat#*
\raggedFormat#*
\secondSubtitleFormat#*
\secondTextFormat#*
\secondTitleFormat#*
\shortnewsItemTitleFormat#*
\shortnewsSubtitleFormat#*
\shortnewsTitleFormat#*
\thirdSubtitleFormat#*
\thirdTextFormat#*
\thirdTitleFormat#*
\timestampFormat#*
\timestampSeparator#*
\timestampTxt#*
\weatherFormat#*
\weatherTempFormat#*
\weatherUnits#*