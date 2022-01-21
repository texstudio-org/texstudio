# gamebooklib package
# Matthew Bertucci 1/18/2022 for v1.1

#include:environ
#include:macroswap
#include:ifthen
#include:lcg
#include:silence

#keyvals:\usepackage/gamebooklib#c
verbose
endpage
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
\gentryfooter#*
\thefncounter#*
\outputfootnotes{maxIdx}#*
\noentryfoot