# ext.misc tikzlibrary
# 2023/03/19 for v0.5.0

# loads ext.pgfkeys-plus pgfkeyslibrary

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
full arc
full arc=%<number%>
#endkeyvals

\pgfmathstrrepeat{"text"}{number}#*
\pgfmathisInString{"string"}{"text"}#*
\pgfmathstrcat{"textA"}{"textB"}#*
\pgfmathisEmpty{"text"}#*
\pgfmathatanXY{x}{y}#*
\pgfmathatanYX{y}{x}#*
\pgfmathanglebetween{"p1"}{"p2"}#*
\pgfmathqanglebetween{"p"}#*
\pgfmathdistancebetween{"p1"}{"p2"}#*
\pgfmathqdistancebetween{"p"}#*

# from pgffor-ext.code.tex
#keyvals:\foreach#c
no separator
normal list
#endkeyvals
