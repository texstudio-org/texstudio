# fixedpointarithmetic tikzlibrary
# 2022/11/21 for v3.1.9a

# loads fixedpointarithmetic pgflibrary

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
fixed point arithmetic={%<options%>}
#endkeyvals

\pgfmathfpscale#*
\pgfmathfpparse{expr}#*
\pgfmathfpscientific{x}{y}#*
\pgfmathfplessthan{x}{y}#*
\pgfmathfpgreaterthan{x}{y}#*
\pgfmathfpequalto{x}{y}#*
\pgfmathfpadd{x}{y}#*
\pgfmathfpsubtract{x}{y}#*
\pgfmathfpmultiply{x}{y}#*
\pgfmathfpdivide{x}{y}#*
\pgfmathfpabs{x}#*
\pgfmathfpneg{x}#*
\pgfmathfpround{x}#*
\pgfmathfpfloor{x}#*
\pgfmathfpceil{x}#*
\pgfmathfpmod{x}{y}#*
\pgfmathfpmax{x}{y}#*
\pgfmathfpmin{x}{y}#*
\pgfmathfppow{x}{y}#*
\pgfmathfpexp{x}#*
\pgfmathfpln{x}#*
\pgfmathfpsqrt{x}#*
\pgfmathfpveclen{x}{y}#*
\pgfmathfpsin{x}#*
\pgfmathfpcos{x}#*
\pgfmathfptan{x}#*
\pgfmathfpacos{x}#*
\pgfmathfpasin{x}#*
\pgfmathfpatan{x}#*
\pgfmathfpcot{x}#*
\pgfmathfpsec{x}#*
\pgfmathfpcosec{x}#*
\pgfmathfpdeg{x}#*
\pgfmathfprad{x}#*
\pgfmathfpsetseed{x}#*
\pgfmathfprnd#*
\pgfmathfprand#*