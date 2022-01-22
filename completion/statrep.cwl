# statrep package
# Matthew Bertucci 11/3/2021 for v1.07

#include:verbatim
#include:graphicx
#include:xkeyval
#include:calc
#include:ifthen
#include:sas
#include:longfigure

#keyvals:\usepackage/statrep#c
generate#true,false
color#true,false
figname=%<counter%>
resetby=%<counter%>
set
final
errorshow
pausing
#endkeyvals

\begin{Datastep}#V
\begin{Datastep}[options%keyvals]#V
\end{Datastep}

#keyvals:\begin{Datastep}
program
display
first=%<n%>
last=%<m%>
fontsize=
#endkeyvals

\begin{Sascode}#V
\begin{Sascode}[options%keyvals]#V
\end{Sascode}

#keyvals:\begin{Sascode}
store=%<name%>
program
display
fontsize=
#endkeyvals

\Listing{name}
\Listing[options%keyvals]{name}
\Graphic{name}
\Graphic[options%keyvals]{name}

#keyvals:\Listing,\Graphic
caption={%|}
firstobj=
lastobj=
objects=
options=#autopage,graph,list,newpage,nopage,onebox,skipfirst,skiplast,table
pattern=
store=%<name%>
style=
type=#listing,graph
#endkeyvals

#keyvals:\Listing
dest=
fontsize=
linesize=
pagesize=
#endkeyvals

#keyvals:\Graphic
dpi=
height=##L
scale=
width=##L
#endkeyvals

\SRcaptionfont#*
\SRcaptioncontinuedfont#*
\SRcontinuedname#*
\SRdefaultdests#*
\SRdpi#*
\SRgraphicdir#*
\SRgraphtype#*
\SRlatexdir#*
\SRlatexstyle#*
\SRodsgraphopts#*
\SRintertext#*
\SRlinesize#*
\SRlistingdir#*
\SRmacropath#*
\SRmacroinclude#*
\SRpagesize#*
\SRparindent#*
\SRprogramline#*
\SRprogramname#*
\SRstyle#*
\SRtempfilename#*
\SRverbfont#*

\dosloppy#*
\unsloppy#*
\Boxlisting{file name}#*
\Boxgraphic{file name}#*
