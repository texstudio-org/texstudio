# graphpaper class
# Matthew Bertucci 4/25/2022 for v1.1

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

gridcolor#B

\A#S
\Adue#S
\Auxx#S
\Cifre#S
\Czero#S
\Dec#S
\decx#S
\decxx#S
\decy#S
\decyy#S
\factor#S
\hlines#S
\I#S
\Idue#S
\IIdue#S
\Inter#S
\J#S
\LAng#S
\LnDieci#S
\Logaritmo#S
\LowResUno#S
\LowResZero#S
\LPLA#S
\lwa#S
\lwb#S
\lwc#S
\mb#S
\Mdue#S
\mindistanceunit#S
\minimumdistance#S
\minorticklength#S
\ml#S
\Mod#S
\mr#S
\mt#S
\plstep#S
\pmargin#S
\Rbox#S
\RotLab#S
\Rout#S
\RoutCifre#S
\RoutTak#S
\Rxx#S
\Rzero#S
\Scala#S
\ScalaDecade#S
\SmithChart#S
\ticklength#S
\vlines#S
\xlength#S
\xlinsq#S
\xmindiv#S
\xmindivfloat#S
\xsideunit#S
\xstep#S
\xtick#S
\ylength#S
\yline#S
\ylinsq#S
\ymindiv#S
\ymindivfloat#S
\ysideunit#S
\ystep#S
\ytickstart#S
\ytickstop#S
\yytickstop#S
