# gamebooklib package
# Matthew Bertucci 2022/05/29 for v1.3

#include:environ
#include:macroswap
#include:ifthen
#include:lcg
#include:silence

#keyvals:\usepackage/gamebooklib#c
verbose
endpage
jukebox
footnote
noshuffle
# options passed to lcg
counter=%<counter%>
first=%<integer%>
last=%<integer%>
seed=%<integer%>
quiet
#endkeyvals

\begin{gentry}{entrylabel}
\begin{gentry}[index]{entrylabel}
\begin{gentry}[index]{entrylabel}[title%text]
\end{gentry}
\thegentryctr#*
\gentryidx#*
\gentrycode#*
\gentryidxu#*
\gentryidxs#*
\gentrytitle#*
\nextidx#*
\thegentries
\gentrycount#*
\gentryheader{counterIdx}{fixedIdx}{code}{title%text}#*
\gentryshouldoutput#*
\gentryfooter#*
\thefncounter#*
\outputfootnotes{maxIdx}#*
\noentryfoot
