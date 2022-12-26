# tsvtemplate package
# Matthew Bertucci 2022/12/22 for v1.0

#include:luatex
#include:environ

\begin{tsv template}{file}#i
\begin{tsv template}[colname1,colname2,...]{file}#i
\end{tsv template}

# from tsvtemplate.tex
\tsvtemplate{template}{file}#i
\tsvtemplate[colname1,colname2,...]{template}{file}#i
\applytemplate{separator}{colnames}{template}{file}#*i
\tsvloaded#S