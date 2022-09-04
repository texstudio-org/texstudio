# srdp-tables package
# Matthew Bertucci 2022/09/01 for v2021/11/09

#keyvals:\usepackage/srdp-tables#c
delarray
linegoal
scantokens
debugshow
#endkeyvals

#ifOption:delarray
#include:delarray
#endif

#ifOption:linegoal
#include:linegoal
#endif

\begin{tabu}{preamble}#\tabular
\begin{tabu} to %<width%> {%<preamble%>}#\tabular
\begin{tabu} spread %<width%> {%<preamble%>}#\tabular
\end{tabu}
\begin{longtabu}{preamble}#\tabular,longtable
\begin{longtabu} to %<width%> {%<preamble%>}#\tabular,longtable
\begin{longtabu} spread %<width%> {%<preamble%>}#\tabular,longtable
\end{longtabu}
\tabulinestyle{style}
\usetabu{username}
\tabucline{%<from%>-%<to%>}
\tabucline[%<spec%>]{%<from%>-%<to%>}
\savetabu{username}
\preamble{username}
\tabuphantomline
\tabulinesep = %<dimen%>
\extrarowdepth
\abovetabulinesep
\belowtabulinesep
\tabustrutrule
\extrarowsep =%<dimen%>
\extrarowsep =^%<dimen%>
\extrarowsep =_%<dimen%>
\extrarowsep =_%<dimen%>^%<dimen%>
\taburulecolor{color}
\taburulecolor|%<doubleRuleSepColor%>|{%<color%>}
\tabureset
\newtabulinestyle{style}
\everyrow{code}
\taburowcolors [%<first line%>] %<number%> {%<first%> .. %<last%>}
\taburowcolors %<number%> {%<first%> .. %<last%>}
\rowfont[alignment]{fontSpec}
\tabudecimal{code}
\firstline#*
\lastline#*
\iftabuscantokens#*
\tabuscantokenstrue#*
\tabuscantokensfalse#*
\tabucolumn{arg}#*
\tabucolX#*
\tabudefaulttarget#*
\tabuDisableCommands#*
\tabuendlongtrial#*
\tabulineoff#*
\tabulineon#*
\tabuthepreamble#*
\thetaburow#*
\tracingtabu#*