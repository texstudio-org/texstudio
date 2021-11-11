# placeat package
# Matthew Bertucci 11/10/2021 for v0.1d1

#include:luatexbase
#include:luacode
#include:atbegshi

\placeat(x,y){content}
\placeat(x,y){content}[name]
\placeat(x,y)[content-left]{content}
\placeat(x,y)[content-left]{content}[name]
\placeat{x}{y}{content}#*
\placeat{x}{y}{content}[name]#*
\placeat{x}{y}[content-left]{content}#*
\placeat{x}{y}[content-left]{content}[name]#*

\placerelto[name](x,y){content}
\placerelto[name](x,y){content}[name]
\placerelto[name]{x}{y}{content}#*
\placerelto[name]{x}{y}{content}[name]#*

\placeminipageat{x}{y}{content}
\placeminipageat{x}{y}[width]{content}

\placeatsetup{options%keyvals}

#keyvals:\placeatsetup
gridnumber=
gridnumberx=
gridnumbery=
nogrid
drawgrid
numnumgrid
alphanumgrid
offsetx=
offsety=
startzero
linewidth=
gridlinewidth=
arrowheadlength=
#endkeyvals

\placelineat(x1,y1)(x2,y2)
\placelineat[color](x1,y1)(x2,y2)
\placearrowat(x1,y1)(x2,y2)
\placearrowat[color](x1,y1)(x2,y2)
\placecircleat(x,y){r}
\placecircleat[color](x,y){r}
\placefilledcircleat(x,y){r}
\placefilledcircleat[color](x,y){r}
\placesquareat(x,y){r}
\placesquareat[color](x,y){r}
\placerectangleat(x1,y1)(x2,y2)
\placerectangleat[color](x1,y1)(x2,y2)
\placefilledrectangleat(x1,y1)(x2,y2)
\placefilledrectangleat[color](x1,y1)(x2,y2)
\placecurveat(x1,y1)(x2,y2)(x3,y3)(x4,y4)
\placecurveat[color](x1,y1)(x2,y2)(x3,y3)(x4,y4)
\placeroundedat(x1,y1)(x2,y2)#*
\placeroundedat[color](x1,y1)(x2,y2)#*

\placeatthreenumbers{arg1}{arg2}{arg3}#*
\firstof{arg1}{arg2}#*
\secondof{arg1}{arg2}#*
\drawgridnum#*
\drawgrid#*