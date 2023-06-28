# topiclongtable package
# Matthew Bertucci 12/12/2021 for v1.3.2

#include:zref-abspage
#include:array
#include:multirow
#include:longtable

\begin{topiclongtable}{preamble}#\tabular
\end{topiclongtable}
\endfirstfoot#/topiclongtable
\endlastfoot#/topiclongtable
\endfirsthead#/topiclongtable
\endfoot#/topiclongtable
\endhead#/topiclongtable
\Topic#t
\Topic[content]#t
\TopicLine#t
\TopicSetContinuationCode{code}
\TopicSetVPos{vpos%keyvals}
#keyvals:\TopicSetVPos
b
c
t
#endkeyvals
\TopicSetWidth{width spec%keyvals}
#keyvals:\TopicSetWidth
=
*
#endkeyvals