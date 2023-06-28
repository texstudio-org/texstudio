# swfigure package
# Matthew Bertucci 2022/05/16 for v0.9.20

#include:etoolbox
#include:graphicx
#include:afterpage
#include:wrapfig2

\DFimage[mode]{imagefile}{caption%text}
\DFimage[mode]{imagefile}[lof entry%text]{caption%text}
\DFimage[mode]{imagefile}{caption%text}[label]
\DFimage[mode]{imagefile}[lof entry%text]{caption%text}[label]
\DFimage[mode]{imagefile}[lof entry%text]{caption%text}[label](height coor)<line corr>
\DFimage[%<mode%>]{%<imagefile%>}[%<lof entry%>]{%<caption%>}[%<label%>](%<height corr%>)<%<line corr%>>|%<width test%>|!%<precaption%>!

\begin{DFimage}[mode]{imagefile}{caption%text}
\begin{DFimage}[mode]{imagefile}[lof entry%text]{caption%text}
\begin{DFimage}[mode]{imagefile}{caption%text}[label]
\begin{DFimage}[mode]{imagefile}[lof entry%text]{caption%text}[label]
\begin{DFimage}[mode]{imagefile}[lof entry%text]{caption%text}[label](height coor)<line corr>
\begin{DFimage}[%<mode%>]{%<imagefile%>}[%<lof entry%>]{%<caption%>}[%<label%>](%<height corr%>)<%<line corr%>>|%<width test%>|!%<precaption%>!
\end{DFimage}

\cleartoeven{number}#*
\cleartopage#*
\CompStrings{string1}{string2}#*
\DFcaption[lof entry%text]{caption%text}#*
\DFcaption[lof entry%text]{caption%text}[label]#*l
\DFcaption{caption%text}#*
\DFcaption{caption%text}[label]#*l
\DFcaptionP[lof entry%text]{caption%text}#*
\DFcaptionP[lof entry%text]{caption%text}[label]#*l
\DFcaptionP{caption%text}#*
\DFcaptionP{caption%text}[label]#*l
\DFhalfheight#*
\DFhalfwidth#*
\DFheight#*
\DFheight#*
\DFscalefactor#*
\DFwarning{arg1}{arg2}#S
\DFwidth#*
\DisplayModeList#*
\externalmargin#*
\FigSpace#*
\fptest{test}{true}{false}#*
\FScaptionShift#*
\FSfigure{%<imagefile%>}[%<lof entry%>]{%<caption%>}[%<label%>](%<height corr%>)<%<line corr%>>|%<width test%>|!%<precaption%>!#*
\FSfigure{imagefile}[lof entry%text]{caption%text}#*
\FSfigure{imagefile}[lof entry%text]{caption%text}[label]#*
\FSfigure{imagefile}[lof entry%text]{caption%text}[label](height coor)<line corr>#*
\FSfigure{imagefile}{caption%text}#*
\FSfigure{imagefile}{caption%text}[label]#*
\HSfigure{%<imagefile%>}[%<lof entry%>]{%<caption%>}[%<label%>](%<height corr%>)<%<line corr%>>|%<width test%>|!%<precaption%>!#*
\HSfigure{imagefile}[lof entry%text]{caption%text}#*
\HSfigure{imagefile}[lof entry%text]{caption%text}[label]#*
\HSfigure{imagefile}[lof entry%text]{caption%text}[label](height coor)<line corr>#*
\HSfigure{imagefile}{caption%text}#*
\HSfigure{imagefile}{caption%text}[label]#*
\internalmargin#*
\NFfigure{%<imagefile%>}[%<lof entry%>]{%<caption%>}[%<label%>](%<height corr%>)<%<line corr%>>|%<width test%>|!%<precaption%>!#*
\NFfigure{imagefile}[lof entry%text]{caption%text}#*
\NFfigure{imagefile}[lof entry%text]{caption%text}[label]#*
\NFfigure{imagefile}[lof entry%text]{caption%text}[label](height coor)<line corr>#*
\NFfigure{imagefile}{caption%text}#*
\NFfigure{imagefile}{caption%text}[label]#*
\RFfigure{%<imagefile%>}[%<lof entry%>]{%<caption%>}[%<label%>](%<height corr%>)<%<line corr%>>|%<width test%>|!%<precaption%>!#*
\RFfigure{imagefile}[lof entry%text]{caption%text}#*
\RFfigure{imagefile}[lof entry%text]{caption%text}[label]#*
\RFfigure{imagefile}[lof entry%text]{caption%text}[label](height coor)<line corr>#*
\RFfigure{imagefile}{caption%text}#*
\RFfigure{imagefile}{caption%text}[label]#*
\RFx#*
\RFy#*
\SetList{cmd}{item1,item2,...}#*d
\spreadwidth#*
\SWcaptionShift#*
\SWfigure{%<imagefile%>}[%<lof entry%>]{%<caption%>}[%<label%>](%<height corr%>)<%<line corr%>>|%<width test%>|!%<precaption%>!#*
\SWfigure{imagefile}[lof entry%text]{caption%text}#*
\SWfigure{imagefile}[lof entry%text]{caption%text}[label]#*
\SWfigure{imagefile}[lof entry%text]{caption%text}[label](height coor)<line corr>#*
\SWfigure{imagefile}{caption%text}#*
\SWfigure{imagefile}{caption%text}[label]#*
\TestList{list}{string}{true}{false}#*
\THfigure{%<imagefile%>}[%<lof entry%>]{%<caption%>}[%<label%>](%<height corr%>)<%<line corr%>>|%<width test%>|!%<precaption%>!#*
\THfigure{imagefile}[lof entry%text]{caption%text}#*
\THfigure{imagefile}[lof entry%text]{caption%text}[label]#*
\THfigure{imagefile}[lof entry%text]{caption%text}[label](height coor)<line corr>#*
\THfigure{imagefile}{caption%text}#*
\THfigure{imagefile}{caption%text}[label]#*
\TScaptionwidth#*
\TWfigure{%<imagefile%>}[%<lof entry%>]{%<caption%>}[%<label%>](%<height corr%>)<%<line corr%>>|%<width test%>|!%<precaption%>!#*
\TWfigure{imagefile}[lof entry%text]{caption%text}#*
\TWfigure{imagefile}[lof entry%text]{caption%text}[label]#*
\TWfigure{imagefile}[lof entry%text]{caption%text}[label](height coor)<line corr>#*
\TWfigure{imagefile}{caption%text}#*
\TWfigure{imagefile}{caption%text}[label]#*
\VSfigure{%<imagefile%>}[%<lof entry%>]{%<caption%>}[%<label%>](%<height corr%>)<%<line corr%>>|%<width test%>|!%<precaption%>!#*
\VSfigure{imagefile}[lof entry%text]{caption%text}#*
\VSfigure{imagefile}[lof entry%text]{caption%text}[label]#*
\VSfigure{imagefile}[lof entry%text]{caption%text}[label](height coor)<line corr>#*
\VSfigure{imagefile}{caption%text}#*
\VSfigure{imagefile}{caption%text}[label]#*