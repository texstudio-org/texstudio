# ncchdr package
# Matthew Bertucci 2/3/2022 for v1.04

#include:nccheadings
#include:nccfancyhdr

#keyvals:\usepackage/ncchdr#c
empty
plain
myheadings
headings
title
#endkeyvals

#ifOption:title
\lefttitlemark
\titlemark
\righttitlemark
#endif