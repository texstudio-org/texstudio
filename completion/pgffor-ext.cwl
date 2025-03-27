# pgffor-ext package
# Matthew Bertucci 2025/03/18 for v0.6.0

#include:pgffor

#keyvals:\foreach#c
ext/xparser={%<arg spec%>}{%<foreach value%>}
ext/xparser Om
#endkeyvals

# from pgffor-ext.code.tex
#keyvals:\foreach#c
ext/use int=%<<start> to <end>%>
ext/use int=%<<start> to <end> step <delta>%>
ext/use float=%<<start> to <end>%>
ext/use float=%<<start> to <end> step <delta>%>
ext/no separator
ext/normal list
#endkeyvals

# from tikzext-util.tex
\tikzextversion#S
\tikzextversionnumber#S
\tikzextset{options%keyvals}
\pgfextset{options%keyvals}
