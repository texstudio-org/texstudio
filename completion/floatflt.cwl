# floatflt package
# Matthew Bertucci 1/9/2021 for v1.31

#keyvals:\usepackage/floatflt#c
rflt
lflt
vflt
#endkeyvals

\begin{floatingfigure}{width}
\begin{floatingfigure}[option%keyvals]{width}
\end{floatingfigure}

\begin{floatingtable}{tabular content%text}
\begin{floatingtable}[option%keyvals]{tabular content%text}
\end{floatingtable}

#keyvals:\begin{floatingfigure},\begin{floatingtable}
r
l
p
v
#endkeyvals

\fltitem{text}
\fltitem[space%l]{text}
\fltditem{label}{text}#l
\fltditem[space%l]{label}{text}#l

\figbox#*
\tabbox#*
\pagebox#*
\ffigcount#*
\ftabcount#*
\fftest#*
\hangcount#*
\nosuccesstryfig#*
\nosuccesstrytab#*
\figgutter#*
\tabgutter#*
\htdone#*
\pageht#*
\startpageht#*
\tabbredd#*
\floatfltwidth#*
\fltitemwidth#*
\iftryingfig#*
\tryingfigfalse#*
\tryingfigtrue#*
\iftryingtab#*
\tryingtabfalse#*
\tryingtabtrue#*
\ifdoingfig#*
\doingfigfalse#*
\doingfigtrue#*
\ifdoingtab#*
\doingtabfalse#*
\doingtabtrue#*
\iffigprocessing#*
\figprocessingfalse#*
\figprocessingtrue#*
\iftabprocessing#*
\tabprocessingfalse#*
\tabprocessingtrue#*
\ifpageafterfig#*
\pageafterfigfalse#*
\pageafterfigtrue#*
\ifpageaftertab#*
\pageaftertabfalse#*
\pageaftertabtrue#*
\ifoddpages#*
\oddpagesfalse#*
\oddpagestrue#*
\ifoutput#*
\outputfalse#*
\outputtrue#*
\outputpretest#*
\dofigtest#*
\dohangf#*
\dohangt#*
\dotabtest#*
\figinsert#*
\oldeverypar#S
\oldoutput#S
\tabinsert#*
\theOptionTest#*
\tryfig#*
\trytab#*