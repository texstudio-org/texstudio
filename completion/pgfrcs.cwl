# pgfrcs package
# muzimuzhi, 7 Jul 2020, tikz-pgf 3.1.5b
# Matthew Bertucci 11/16/2021 for v3.1.9a

# pgfrcs.sty
# ├── pgfutil-common.tex
# │   └── pgfutil-common-lists.tex
# ├── pgfutil-latex.def
# │   └── everyshi.sty
# └── pgfrcs.code.tex
#     └── pgf.revision.tex

## from pgfutil-common.tex
\pgferror{error text%text}#*
\pgfwarning{warning text%text}#*

\usepgflibrary{list of libraries%keyvals}#*
#keyvals:\usepgflibrary#c
arrows.meta
graphdrawing
shapes.gates.logic
shapes.gates.logic.US
shapes.gates.logic.IEC
shapes.gates.ee
shapes.gates.ee.IEC
decorations.pathmorphing
decorations.pathreplacing
decorations.markings
decorations.footprints
decorations.shapes
decorations.text
decorations.fractals
fadings
fixedpointarithmetic
fpu
lindenmayersystems
patterns
patterns.meta
plothandlers
plotmarks
profiler
shadings
shapes.geometric
shapes.symbols
shapes.arrows
shapes.multipart
shapes.callouts
shapes.misc
shapes.misc
intersections
curvilinear
#endkeyvals

\usepgfmodule{module names%keyvals}#*
#keyvals:\usepgfmodule#c
parser
oo
decorations
shapes
matrix
nonlineartransformations
plot
animations
#endkeyvals

\pgfutilensuremath{formula}#*
\pgfutilpreparefilename{file name}#*
\pgfutilifcontainsmacro{token list}{true}{false}#*
\pgfutilifstartswith{start with pattern}{token list}{true}{false}#*
\pgfutilstrreplace{search}{replacement}{string}#*
\pgfutilsolvetwotwoleq{2x2 matrix entries}{2x1 matrix entries}#*
\pgfutilsolvetwotwoleqfloat{2x2 matrix entries}{2x1 matrix entries}#*

# from pgfutil-common-lists.tex
\pgfapplistnewempty{applist name}#*
\pgfapplistpushback %<item to append%>\to %<applist name%>#*
\pgfapplistlet{cmd}=%<applist name%>#*
\pgfprependlistnewempty{prelist name}#*
\pgfprependlistpushfront %<item to prepend%>\to %<prelist name%>#*
\pgfprependlistlet{cmd}=%<prelist name%>#*

## from pgfutil-latex.def
#include:everyshi

## from pgfrcs.code.tex
\pgftypesetversion#*
\pgfrcsloaded#*
\pgfrcsatcode#*
\ProvidesFileRCS{file name}#*
\ProvidesPackageRCS{pkg name}#*
\ProvidesClassRCS{class name}#*

# from pgf.revision.tex
\pgfrevision#*
\pgfversion#*
\pgfversiondatetime#*
\pgfrevisiondatetime#*
\pgfversiondate#*
\pgfrevisiondate#*
