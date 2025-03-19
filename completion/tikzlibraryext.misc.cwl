# ext.misc tikzlibrary
# 2025/03/19 for v0.6

# loads ext.pgfkeys-plus pgfkeyslibrary

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
ext/full arc
ext/full arc=%<number%>
#endkeyvals

\pgfmathextstrrepeat{"text"}{number}#*
\pgfmathextisInString{"string"}{"text"}#*
\pgfmathextstrcat{"textA"}{"textB"}#*
\pgfmathextisEmpty{"text"}#*
\pgfmathextatanXY{x}{y}#*
\pgfmathextatanYX{y}{x}#*
\pgfmathextanglebetween{"p1"}{"p2"}#*
\pgfmathextqanglebetween{"p"}#*
\pgfmathextdistancebetween{"p1"}{"p2"}#*
\pgfmathextqdistancebetween{"p"}#*

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
