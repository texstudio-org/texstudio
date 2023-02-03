# diadia package
# Matthew Bertucci 2022/12/13 for v1.1

#include:xkeyval
#include:pgfplots
#include:pgfplotstable
#include:pgfcalendar
#include:tabularx
#include:booktabs
#include:colortbl
#include:ifthen
#include:calc
#include:translations
#include:amsmath
#include:tcolorbox
#include:tcolorboxlibrarymany
#include:environ
#include:multicol
#include:amssymb
#include:pgfplotslibrarydateplot

#keyvals:\usepackage/diadia#c
tabstyle=#simple,advanced
tabcolor=#none,%color
plotstyle=#none,bloodsugar,bloodpressure,insulin,weight,cu,pulse,hbaonec
plotclosedcycle#true,false
mcnotewidth=##L
columnsep=##L
columnseprule=##L
columnseprulecolor=%<color command%>
#endkeyvals

\diadiatab{pgfplotstable options}{file}
\diadiatab[options%keyvals]{pgfplotstable options}{file}

#keyvals:\diadiatab#c
tabstyle=#simple,advanced
tabcolor=#none,%color
#endkeyvals

\begin{diadiaplot}{pgfplots options}#\pictureHighlight
\begin{diadiaplot}[options%keyvals]{pgfplots options}
\end{diadiaplot}

#keyvals:\begin{diadiaplot}#c
plotstyle=#none,bloodsugar,bloodpressure,insulin,weight,cu,pulse,hbaonec
plotclosedcycle#true,false
#endkeyvals

\diadiaaddplot{addplot options}{key mappings}{file}
\diadiaaddplot*{addplot options}{key mappings}{file}
\legend{list}

\annotation{x}{y}{annotation%text}
\annotation[TikZ options]{x}{y}{annotation%text}
\setlimit{limit list}
\setlimit[TikZ options]{limit list}

\begin{medicationchart}{tcolorbox options}{date}
\begin{medicationchart}[options%keyvals]{tcolorbox options}{date}
\end{medicationchart}

#keyvals:\begin{medicationchart}#c
mcnotewidth=##L
#endkeyvals

\mcentry{pharmaceutical}{morning}{noon}{evening}{night}{note%text}
\infobox{tcolorbox options}{date}{information%text}

\begin{diadiasidebyside}
\begin{diadiasidebyside}[options%keyvals]
\end{diadiasidebyside}

#keyvals:\begin{diadiasidebyside}#c
columnsep=##L
columnseprule=##L
columnseprulecolor=%<color command%>
#endkeyvals
