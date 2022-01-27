# graphpaper class
# Matthew Bertucci 11/12/2021 for v1.0

#keyvals:\documentclass/graphpaper#c
a4paper
a3paper
letterpaper
#endkeyvals

#include:xkeyval
#include:geometry
#include:euclideangeometry
#include:graphicx
#include:xcolor

\bilinear
\semilogx{decades along x}
\semilogy{decades along y}
\loglog{decades along x}{decades along y}
\loglog[0 or 1]{decades along x}{decades along y}
\polar
\logpolar{decades along radius}
\smith
\setxside{length}
\setyside{length}
\setminimumdistance{length}
\setgridcolor{color}
\setmajorlinethickness{length}
\setmediumlinethickness{length}
\setminorlinethickness{length}
\customcode{picture env cmds}
\customcode[0 or 1]{picture env cmds}

\GradPolar{number}#*
\GradResist{number}#*
\CalcRxx{number}#*
\PolarChart[diameter]{decades}#*
\PolarChart{decades}#*
\SmithChart[diameter]#*
\WhileDoOne[step]{init value}{final value}{code}#*
\WhileDoOne{init value}{final value}{code}#*
\WhileDoTwo[step]{init value}{final value}{code}#*
\WhileDoTwo{init value}{final value}{code}#*
\Xcircle{number}#*
\Ycircle{number}#*
\Ycircle{number}*#*
\carta[0 or 1]{x-decades}{y-decades}#*
\carta{x-decades}{y-decades}#*

\A#S
\Auxx#S
\Czero#S
\LAng#S
\LPLA#S
\LnDieci#S
\Logaritmo#S
\LowResZero#S
\Rbox#S
\RotLab#S
\Rout#S
\RoutCifre#S
\RoutTak#S
\Rxx#S
\Scala#S
\ScalaDecade#S
\SmithChart#S
\decx#S
\decxx#S
\decy#S
\decyy#S
\factor#S
\hlines#S
\minimumdistance#S
\minorticklength#S
\plstep#S
\ticklength#S
\vlines#S
\xlength#S
\xlinsq#S
\xmindiv#S
\xmindivfloat#S
\xstep#S
\xtick#S
\ylength#S
\yline#S
\ylinsq#S
\ymindiv#S
\ymindivfloat#S
\ystep#S
\ytickstart#S
\ytickstop#S
\yytickstop#S
