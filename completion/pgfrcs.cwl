# pgfrcs package
# muzimuzhi, 7 Jul 2020, tikz-pgf 3.1.5b
# Matthew Bertucci 2023/01/15 for v3.1.10

# pgfrcs.sty
# ├── pgfutil-common.tex
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
curvilinear
datavisualization.barcharts
datavisualization.formats.functions
datavisualization.polar
decorations.footprints
decorations.fractals
decorations.markings
decorations.pathmorphing
decorations.pathreplacing
decorations.shapes
decorations.text
fadings
fixedpointarithmetic
fpu
graphdrawing.circular
graphdrawing
graphdrawing.examples
graphdrawing.force
graphdrawing.layered
graphdrawing.trees
intersections
lindenmayersystems
luamath
patterns
patterns.meta
plothandlers
plotmarks
profiler
shadings
shapes
shapes.arrows
shapes.callouts
shapes.gates.ee
shapes.gates.ee.IEC
shapes.gates.logic
shapes.gates.logic.IEC
shapes.gates.logic.US
shapes.geometric
shapes.misc
shapes.multipart
shapes.symbols
svg.path
timelines
transformations.mirror
#endkeyvals

\usepgfmodule{module names%keyvals}#*
#keyvals:\usepgfmodule#c
animations
bending
datavisualization
decorations
matrix
nonlineartransformations
oo
parser
plot
shapes
sorting
#endkeyvals

\pgfutilensuremath{formula}#*
\pgfutilpreparefilename{file name}#*
\pgfretvalquoted#*
\pgfutilconvertdcolon#*
\pgfutilifcontainsmacro{token list}{true}{false}#*
\pgfutilifstartswith{start with pattern}{token list}{true}{false}#*
\pgfutilstrreplace{search}{replacement}{string}#*
\pgfutilsolvetwotwoleq{2x2 matrix entries}{2x1 matrix entries}#*
\pgfutilsolvetwotwoleqfloat{2x2 matrix entries}{2x1 matrix entries}#*

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
\pgfversiondate#*
\pgfrevisiondate#*
