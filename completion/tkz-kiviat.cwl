# tkz-kiviat package
# Matthew Bertucci 9/17/2021 for v0.1b

#include:tikz
#include:tikzlibrarybackgrounds

\tkzKiviatDiagram{name1,name2,...}#/tikzpicture
\tkzKiviatDiagram[options%keyvals]{name1,name2,...}#/tikzpicture

#keyvals:\tkzKiviatDiagram#c
lattice=
gap=
space=
label space=
step=
radial style=
label style=
#endkeyvals

\tkzKiviatLine[options%keyvals]{num1,num2,...}#/tikzpicture
\tkzKiviatLineFromFile[options%keyvals]{file1%file}{file2%file}#/tikzpicture

#keyvals:\tkzKiviatLine#c,\tkzKiviatLineFromFile#c
fill=
opacity=
#endkeyvals

\tkzKiviatGrad[options%keyvals](integer)#/tikzpicture

#keyvals:\tkzKiviatGrad#c
graduation distance=##L
prefix=
suffix=
unity=
#endkeyvals

\tkzKiviatDiagramFromFile{file}#/tikzpicture
\tkzKiviatDiagramFromFile[options%keyvals]{file}#/tikzpicture

#keyvals:\tkzKiviatDiagramFromFile#c
lattice=
gap=
space=
label space=
step=
#endkeyvals
