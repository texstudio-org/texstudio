# scrambledenvs package
# Matthew Bertucci 10/4/2021 for v1.1.0

#include:ifthen
#include:forloop
#include:pgfmath

\newscrambledenv{envname}#N
\defaultlabelfont{font cmds}#*
\defaultrefprefix{prefix}#*
\defaultreffont{font cmds}#*
\defaultprintenv{open env code}{close env code}#*
\defaultprintitem{item cmds}#*