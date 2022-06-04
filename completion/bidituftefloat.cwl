# bidituftefloat package
# Matthew Bertucci 2022/06/03 for v0.2

#include:xifthen
#include:ragged2e
#include:geometry
#include:changepage
#include:optparams
#include:placeins
#include:fancyhdr

#keyvals:\usepackage/bidituftefloat#c
reversegeometry
#endkeyvals

\begin{fullwidth}
\end{fullwidth}
\begin{marginfigure}
\begin{marginfigure}[offset%l]
\end{marginfigure}
\begin{margintable}
\begin{margintable}[offset%l]
\end{margintable}

\floatalignment#*
\forcerectofloat
\forceversofloat
\gsetlength{length cmd}{length}#*
\morefloats
\newlinetospace{arg}#*
\setcaptionfont{font commands}
\setfloatalignment{pos%keyvals}
#keyvals:\setfloatalignment#c
t
b
#endkeyvals

\bidituftefloatDebugInfoNL{text}#S
\bidituftefloatError{error text%text}{help text%text}#S
\bidituftefloatInfoNL{text}#S
\bidituftefloatRecalculate#S