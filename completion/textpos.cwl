# textpos package
# Matthew Bertucci 7/26/2021 for v1.10

#include:everyshi
#include:keyval

#keyvals:\usepackage/textpos#c
showboxes
noshowtext
absolute
overlay
verbose
quiet
#endkeyvals

\begin{textblock}{hsize}(hpos,vpos)
\begin{textblock}{hsize}[ho,vo](hpos,vpos)
\end{textblock}
\begin{textblock*}{hsize}(hpos,vpos)
\begin{textblock*}{hsize}[ho,vo](hpos,vpos)
\end{textblock*}

\TPoptions{options%keyvals}

#keyvals:\TPoptions
absolute#true,false
overlay#true,false
verbose#true,false
showboxes#true,false
showtext#true,false
discardcontent#true,false
#endkeyvals

\TPGrid{nhoriz}{nvert}
\TPGrid[x,y]{nhoriz}{nvert}
\TPShowGrid{nhoriz}{nvert}
\TPMargin{size%l}
\TPMargin*{size%l}
\TPReferencePosition{val1,val2}
\TPHorizModule
\TPVertModule
\TPshowboxestrue
\TPshowboxesfalse
\TPboxrulesize
\textblocklabel{label%plain}
\showtextsize
\textblockorigin{hpos}{vpos}
\textblockcolour{color}#*
\textblockcolor{color}
\textblockrulecolour{color}#*
\textblockrulecolor{color}
\tekstblokkulur{color}#*
\textblockrulecolor{color}#*
\tekstblokroolkulur{color}#*
