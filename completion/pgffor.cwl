# pgffor package
# muzimuzhi, 8 Aug 2020, pgffor in tikz v3.1.5b

#include:pgfrcs
#include:pgfkeys
#include:pgfmath

\foreach %<\macro%> in {%<list%>}{%<code%>}
\foreach [%<options%>] %<\macro%> in {%<list%>}{%<code%>}
\foreach{cmd}#Sd
\foreach[options%keyvals]{cmd}#Sd
\breakforeach#*

#keyvals:\foreach#c
var=%<variable%>
evaluate=%<variable%>
evaluate=%<variable%> as %<macro%>
evaluate=%<variable%> as %<macro%> using %<formula%>
remember=%<variable%> as %<macro%>
remember=%<variable%> as %<macro%> (initially %<value%>)
count=%<macro%>
count=%<macro%> from %<value%>
parse#true,false
expand list#true,false
#endkeyvals
