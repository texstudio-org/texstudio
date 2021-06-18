# tkz-kiviat package
# Matthew Bertucci 6/16/2021

#include:tikz

\tkzKiviatDiagram[local options%keyvals]{name1,name2,...}#/tikzpicture

#keyvals:\tkzKiviatDiagram#c
lattice=
gap=
space=
label space=
step=
radial style=
label style=
#endkeyvals

\tkzKiviatLine[local options%keyvals]{num1,num2,...}#/tikzpicture
\tkzKiviatLineFromFile[local options%keyvals]{file1}{file2}#/tikzpicture

#keyvals:\tkzKiviatLine#c,\tkzKiviatLineFromFile#c
fill=
opacity=
#endkeyvals

\tkzKiviatGrad[local options%keyvals]{integer}#/tikzpicture

#keyvals:\tkzKiviatGrad#c
graduation distance=##L
prefix=
suffix=
unity=
#endkeyvals

\tkzKiviatDiagramFromFile[local options%keyvals]{file}#/tikzpicture

#keyvals:\tkzKiviatDiagramFromFile#c
lattice=
gap=
space=
label space=
step=
#endkeyvals
