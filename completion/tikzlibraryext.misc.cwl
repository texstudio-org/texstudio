# ext.misc tikzlibrary
# 2022/12/09 for v0.4.2

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