# jupynotex package
# Matthew Bertucci 2025/04/27 for v1.1

#include:tcolorbox
#include:pgfopts

#keyvals:\usepackage/jupynotex#c
output-text-limit=%<integer%>
cells-id-template=%<template%>
first-cell-id-template=%<template%>
#endkeyvals

\jupynotex{file}
\jupynotex[cells]{file}
