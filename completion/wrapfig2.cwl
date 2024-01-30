# wrapfig2 package
# Matthew Bertucci 2024/01/22 for v7.0.0

#include:etoolbox
#include:float
#include:xcolor
#include:pict2e

#keyvals:\usepackage/wrapfig2#c
verbose
WFold
#endkeyvals

\begin{wrapfigure}{position%keyvals}
\begin{wrapfigure}{position%keyvals}{width}
\begin{wrapfigure}[lines]{position%keyvals}[overhang]{width}
\end{wrapfigure}

\begin{wraptable}{position%keyvals}
\begin{wraptable}{position%keyvals}{width}
\begin{wraptable}[lines]{position%keyvals}[overhang]{width}
\end{wraptable}

\begin{wraptext}{position%keyvals}
\begin{wraptext}{position%keyvals}{width}
\begin{wraptext}[lines]{position%keyvals}[overhang]{width}
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

\SetWFbgd{color}
\SetWFfrm{color}
\SetWFtxt{color}

\includeframedtext{text}
\includeframedtext[width]{text}
\includeframedtext[width]{text}[settings][radius%l]

\framedbox{frame width%l}{frame thickness%l}{frame sep%l}{text}
\framedbox{frame width%l}{frame thickness%l}{frame sep%l}[corner radius%l]{text}
\Frame{frame width%l}{frame height%l}{corner radius%l}
\Frame*{frame width%l}{frame height%l}{corner radius%l}

\wrapoverhang#*
\insertwidth#*
\WFinsertwidthL#*
\WFinsertwidthH#*
\WFscalefactor#*
\WFscalewidth#*
\WFclear#*
\textcorrection#S
\textplacement#S
\textoverhang#S
\WFfrthick#S
\WFfrgap#S
\WFfrwidth#S
\WFfrheight#S
\WFXR#S
\WFYD#S
\WFXL#S
\WFYU#S

WFbackground#B
WFframe#B
WFtext#B
