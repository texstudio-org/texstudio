# richtext package
# Matthew Bertucci 2022/05/10 for v1.1.1

#include:xkeyval
#include:ifpdf
#include:ifxetex
#include:eforms

\rtpara{name%specialDef}{richtext paragraph%text}#s#%rtpara
\rtpara[options%keyvals]{name%specialDef}{richtext paragraph%text}#s#%rtpara
\span{options%keyvals}{richtext string%text}

\useRV{name%keyvals}
\useV{name%keyvals}

#keyvals:\useRV,\useV,\displayRV,\displayV
%rtpara
#endkeyvals

\sub{text}
\sup{text}
\spc
\br

\RV{rich value}
\DS{default style}
\useDefaultDS
\setDefaultStyle{name%specialDef}{options%keyvals}#s#%rtdefaultstyle
\useDS{name%keyvals}

#keyvals:\useDS
%rtdefaultstyle
#endkeyvals

\setRVVContent{name%specialDef}{{name1}{name2}...}#s#%rvvcontent
\useRVContent{name%keyvals}
\useVContent{name%keyvals}

#keyvals:\useRVContent,\useVContent
%rvvcontent
#endkeyvals

\begin{displayRtPara}{name}
\end{displayRtPara}
\begin{displayRtPara*}{name}
\end{displayRtPara*}

\displayRV{name%keyvals}
\displayV{name%keyvals}

#keyvals:\rtpara,\span,\setDefaultStyle
font=%<font name%>
size=%<number%>
raise=%<number%>
ulstyle=#none,ul,2ul,wul,2wul
style={%<bold, italic, and/or strikeit%>}
color=%<rrggbb%>
url={%<URL%>}
raw=%<CSS2 markup%>
#endkeyvals

#keyvals:\rtpara
halign=#left,center,right,justify
valign=#top,middle,bottom
margleft=%<number%>
margright=%<number%>
indent=#none,first,hanging
indentby=%<number%>
margtop=%<number%>
margbottom=%<number%>
linespacing=#single,oneandhalf,double,exact
lineheight=%<number%>
#endkeyvals

# not documented
\contName#*
\displayRtParaName#*
\makePDFSp#*
\makeTeXSp#*
\makeTeXSpPrnt#*
\resetRtFontKeys#*
\rtpdfSPDef#*
\rtpdfSPDefPrnt#*
\rvorvstring{arg1}{arg2}#*