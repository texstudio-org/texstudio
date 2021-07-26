# textpos package
# Matthew Bertucci 7/26/2021

#include:everyshi

\begin{textblock}{hsize}(hpos,vpos)
\end{textblock}
\begin{textblock*}{hsize}(hpos,vpos)
\end{textblock*}

\TPoptions{keyvals}

#keyvals:\TPoptions
absolute#true,false
overlay#true,false
verbose#true,false
showboxes#true,false
showtext#true,false
discardcontent#true,false
#endkeyvals

\TPGrid[x%l,y%l]{nhoriz}{nvert}
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
\textblockorigin
\textblockcolour{color}#*
\textblockcolor{color}
\textblockrulecolour{color}#*
\textblockrulecolor{color}
\tekstblokkulur{color}#*
\textblockrulecolor{color}#*
\tekstblokroolkulur{color}#*