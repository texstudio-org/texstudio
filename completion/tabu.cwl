# tabu package
# j. sundermeyer  30.3.2013
#
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
\preamble
\tabuphantomline
\tabulinesep = %<dimen%>
\abovetabulinesep
\belowtabulinesep
\extrarowsep =%<dimen%>
\extrarowsep =^%<dimen%>
\extrarowsep =_%<dimen%>
\extrarowsep =_%<dimen%>^%<dimen%>
\taburulecolor{color}
\taburulecolor|doubleRuleSepColor|{color}
\tabureset
\newtabulinestyle{style}
\everyrow{code}
\taburowcolors [<%first line%>] %<number%> {%<first%> .. %<last%>}
\taburowcolors %<number%> {%<first%> .. %<last%>}
\rowfont[alignment]{fontSpec}
\tabudecimal{code}