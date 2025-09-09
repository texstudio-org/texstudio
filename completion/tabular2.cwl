# tabular2 package
# Matthew Bertucci 2025/09/08 for v0.3

#include:l3draw

#keyvals:\usepackage/tabular2#c
rowsep=##L
colsep=##L
margin={%<%>}
vspace={%<%>}
minwidth=##L
lineskip=##L
#endkeyvals

\begin{xtable}
\begin{xtable}[options%keyvals]
\end{xtable}
\begin{data}
\begin{data}[options%keyvals]
\end{data}

#keyvals:\begin{xtable},\begin{data}
format=#inner,csv,json
title#true,false
header#true,false
sep=%<separator%>
loc={%<ref pos%>}
#endkeyvals

\excelcolname
\excelcolname[n]
\rowname{list of names}
\rowname[delimiter]{list of names}
\rowname(i){list of names}
\rowname(i)[delimiter]{list of names}
\colname{list of names}
\colname[delimiter]{list of names}
\colname(i){list of names}
\colname(i)[delimiter]{list of names}
\row{text}
\row[delimiter]{text}
\row(x,y){text}
\row(x,y)[delimiter]{text}
\col{text}
\col[delimiter]{text}
\col(x,y){text}
\col(x,y)[delimiter]{text}
\cell(x,y){text}
\savetable{name}
\loadtable{name}
\rowheight{style list}
\rowheight[global style]{style list}
\colwidth{style list}
\colwidth[global style]{style list}
\colwidth[global style][total width]{style list}
\rowalign{style list}
\rowalign[global style]{style list}
\colalign{style list}
\colalign[global style]{style list}
\printtable
\printtable[indent]
\printtable*
\printtable*[indent]
\rendertable
\rendertable[booktabs]
\rendertable[booktabs][%<middle line%>]
\rendertable[grid]{%<borders%>}
\rowborder{border list}
\rowborder[default]{border list}
\colborder{border list}
\colborder[default]{border list}
\linepatternset{name}{definition}
\linewdset{name}{width}
\linestyleset{name}{style}{width}{color}
\showtable
\logtable