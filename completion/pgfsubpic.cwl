# pgfsubpic package
# Matthew Bertucci 4/13/2022 for v1.1

#include:pgf

# from pgfsubpic.tex
\begin{pgfsubpicture}#*
\end{pgfsubpicture}#*
\pgfsubpicture#S
\endpgfsubpicture#S
\subpictureid#*
\pgfnewsubpicture{name}#*
\pgfsavesubpicture{name}#*
\pgfmergesubpicture{name}#*
\pgfrestoresubpicture{name}#*
\pgfplacesubpicture#*
\fallback#S
\pgffitsubpicture{southwest}{northeast}#*
\pgfnodedelete{name}#*
\pgfnodeifexists{name}{true}{false}#*