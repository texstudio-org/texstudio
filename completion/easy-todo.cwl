# easy-todo package
# Matthew Bertucci 12/13/2021

#include:color
#include:tocloft
#include:ifthen
#include:ifdraft

#keyvals:\usepackage/easy-todo#c
chapter
section
obeyFinal
enable
disable
#endkeyvals

\todo{note%todo}#D
\todoi{note%todo}#D
\todoii{note%todo}{information%text}#D
\listoftodos

\todoindextitle#*
\todoindexpagetitle#*
\todocolor#*
\listoftodosname#*