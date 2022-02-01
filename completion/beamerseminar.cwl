# beamerseminar package
# tbraun 11/5/2006
# added commands for beamer emulation package
# Matthew Bertucci updated 1/30/2022 for v3.65

#keyvals:\usepackage/beamerseminar#c
accumulated
#endkeyvals

\begin{slide}
\end{slide}
\begin{slide*}
\end{slide*}
\overlay{number}
\newslide
\red
\blue
\green
\ifarticle
\articletrue#*
\articlefalse#*
\ifslidesonly
\slidesonlytrue#*
\slidesonlyfalse#*
\ifslide
\slidetrue#*
\slidefalse#*
\ifportrait#*
\portraittrue#*
\portraitfalse#*
\ifcenterslides#*
\centerslidestrue#*
\centerslidesfalse#*
\semin#*
\semcm#*
# does nothing
\ptsize{arg}#S
