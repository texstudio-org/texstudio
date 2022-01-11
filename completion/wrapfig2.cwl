# wrapfig2 package
# Matthew Bertucci 1/9/2021 for v4.0.1

#include:etoolbox
#include:xfp
#include:xparse

#keyvals:\usepackage/wrapfig2#c
verbose
#endkeyvals

\begin{wrapfigure}{position%keyvals}
\begin{wrapfigure}{position%keyvals}{width}
\begin{wrapfigure}[lines]{position%keyvals}[overhang]{width}
\end{wrapfigure}

\begin{wraptable}{position%keyvals}
\begin{wraptable}{position%keyvals}{width}
\begin{wraptable}[lines]{position%keyvals}[overhang]{width}
\end{wraptable}

\begin{wraptext}
\begin{wraptext}[position]
\begin{wraptext}[%<position%>]|%<width%>|<%<line corr%>>(%<caption label%>)
\end{wraptext}

\begin{wrapfloat}{object}{position%keyvals}
\begin{wrapfloat}{object}{position%keyvals}{width}
\begin{wrapfloat}{object}[lines]{position%keyvals}[overhang]{width}
\end{wrapfloat}

#keyvals:\begin{wrapfigure},\begin{wraptable},\begin{wrapfloat}
l
r
L
R
i
o
I
O
#endkeyvals

\wrapoverhang#*
\insertwidth#*
\WFclear#*
\textcorrection#*
\textplacement#*