# tikzexternal package
# Matthew Bertucci 2022/12/11 for v3.19a

#include:graphicx

\tikzexternalize
\tikzexternalize[options%keyvals]
\tikzsetnextfilename{file name%file}
\tikzsetexternalprefix{prefix}
\tikzsetfigurename{name}
\tikzappendtofigurename{suffix}
\begin{tikzpicture}#\pictureHighlight
\begin{tikzpicture}[options%keyvals]
\end{tikzpicture}
\tikzpicture#S
\endtikzpicture#S
\tikz
\tikz[options%keyvals]
\tikzset{options%keyvals}
\beginpgfgraphicnamed{file name prefix}#*
\endpgfgraphicnamed#*
\tikzifinpicture{in code}{out code}#*
\pgfincludeexternalgraphics{imagefile}#*g
\pgfexternalreaddpth{imagefile}#*
\pgfretval#*
