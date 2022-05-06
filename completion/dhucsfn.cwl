# dhucsfn package
# Matthew Bertucci 2022/05/04 for v1.0

#keyvals:\usepackage/dhucsfn#c
superscript
parenthesis
hang
multipara
para
leftflush
indent
leftflushindent
hangpar
varhangpar
#endkeyvals

#ifOption:multipara
#include:fnpara
#endif

#ifOption:para
#include:fnpara
#endif

\footnumbersep#*

\filedate#S
\fileversion#S