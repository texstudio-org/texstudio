# stanli package
# Matthew Bertucci 12/20/2021 for v3.0

#include:ifthen
#include:tikz
#include:tikzlibraryshapes
#include:tikzlibrarypositioning
#include:tikzlibraryautomata
#include:tikzlibrarycalc
#include:tikzlibrary3d
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibrarypatterns
#include:xargs
#include:verbatim

## 2d elements ##
\point{name}{x}{y};

\beam{type%keyvals}{init point}{end point};
\beam{type%keyvals}{init point}{end point}[rounded init point];
\beam{type%keyvals}{init point}{end point}[rounded init point][rounded end point];
#keyvals:\beam#c,\dbeam#c
1
2
3
4
#endkeyvals

\support{type%keyvals}{insertion point};
\support{type%keyvals}{insertion point}[rotation];
#keyvals:\support#c
1
2
3
4
5
6
#endkeyvals

\hinge{1}{%<insertion point%>};
\hinge{2}{%<insertion point%>}[%<init point%>][%<end point%>][%<orientation%>];
\hinge{3}{%<insertion point%>}[%<rotation%>];
\hinge{4}{%<insertion point%>}[%<rotation%>];
\hinge{5}{%<insertion point%>}[%<init point%>][%<end point%>];

\load{type%keyvals}{insertion point};
\load{type%keyvals}{insertion point}[rotation];
\load{type%keyvals}{insertion point}[rotation][length or angle];
\load{type%keyvals}{insertion point}[rotation][length or angle][load distance];
#keyvals:\load#c
1
2
3
#endkeyvals

\lineload{1}{%<init point%>}{%<end point%>}[%<init force%>][%<end force%>][%<force interval%>];
\lineload{2}{%<init point%>}{%<end point%>}[%<init force%>][%<end force%>][%<force interval%>];
\lineload{3}{%<init point%>}{%<end point%>}[%<init force%>][%<end force%>][%<force interval%>];
\lineload{4}{%<init point%>}{%<end point%>}[%<force interval%>][%<force length%>];

\temperature{init point}{end point}{temp below}{temp above};
\temperature{init point}{end point}{temp below}{temp above}[temp pos][temp val below][temp val above];
\temperature{init point}{end point}{temp below}{temp above}[temp pos][temp val below][temp val above][text orient below][text orient above];

\internalforces{init point}{end point}{init val}{end val};
\internalforces{init point}{end point}{init val}{end val}[parabola height];
\internalforces{init point}{end point}{init val}{end val}[parabola height][color];
\internalforces{init point}{end point}{init val}{end val}[parabola height][color][bend pos];

\dimensioning{type%keyvals}{init point}{end point}{distance};
\dimensioning{type%keyvals}{init point}{end point}{distance}[measure];
#keyvals:\dimensioning#c
1
2
3
#endkeyvals

\influenceline{init point}{end point}{distance};
\influenceline{init point}{end point}{distance}[arrow pos];

\notation{1}{%<insertion point%>}{%<labelling%>}[%<orientation%>];
\notation{2}{%<insertion point%>}{%<labelling%>}[%<orientation%>];
\notation{3}{%<init point%>}{%<end point%>}[%<labelling%>][%<pos%>][%<orientation%>];
\notation{4}{%<init point%>}{%<end point%>}[%<labelling%>][%<pos%>][%<orientation%>][%<text orientation%>];
\notation{5}{%<init point%>}{%<end point%>}[%<labelling%>][%<pos%>][%<orientation%>][%<text orientation%>];
\notation{6}{%<insertion point%>}{%<labelling%>};

\addon{1}{%<insertion point%>}{%<end point%>}{%<pos%>};
\addon{2}{%<insertion point%>}{%<init point%>}{%<end point%>}[%<orientation%>];
\addon{3}{%<insertion point%>}{%<init point%>}{%<end point%>}[%<orientation%>];

\scaling{factor};

## 3d elements ##
\dpoint{name}{x}{y}{z};

\dbeam{type%keyvals}{init point}{end point};
\dbeam{type%keyvals}{init point}{end point}[rounded init point];
\dbeam{type%keyvals}{init point}{end point}[rounded init point][rounded end point];

\daxis{1}{%<insertion point%>}[%<x orient.%>][%<y orient.%>][%<z orient.%>];
\daxis{2}{%<plane%>}[%<insertion point%>][%<end point%>][%<pos%>][%<x orient.%>][%<y orient.%>][%<z orient.%>][%<change y with z%>];
\daxis{3}{%<plane%>}[%<insertion point%>][%<end point%>][%<pos%>][%<rot1%>][%<rot2%>][%<rot3%>][%<rotB%>];

\dsupport{1}{%<insertion point%>}[%<x dir%>][%<y dir%>][%<z dir%>];
\dsupport{2}{%<insertion point%>}[%<plane%>]
\dsupport{3}{%<insertion point%>}[%<x dir%>][%<y dir%>][%<z dir%>];
\dsupport{4}{%<insertion point%>}[%<x dir%>][%<y dir%>][%<z dir%>];
\dsupport{5}{%<insertion point%>}[%<x dir%>][%<y dir%>][%<z dir%>];

\dhinge{1}{%<insertion point%>};
\dhinge{2}{%<insertion point%>}[%<init point%>][%<end point%>][%<orientation%>];
\dhinge{3}{%<insertion point%>}[%<rotation%>];
\dhinge{4}{%<insertion point%>}[%<init point%>][%<end point%>];

\dload{type%keyvals}{insertion point};
\dload{type%keyvals}{insertion point}[rotA];
\dload{type%keyvals}{insertion point}[rotA][rotB];
\dload{type%keyvals}{insertion point}[rotA][rotB][length];
\dload{type%keyvals}{insertion point}[rotA][length][distance];
#keyvals:\dload#c
1
2
3
4
#endkeyvals

\dlineload{1}{%<plane%>}[%<plane dist%>]{%<init point%>}{%<end point%>}[%<init force%>][%<end force%>][%<force interval%>];
\dlineload{2}{%<plane%>}[%<plane dist%>]{%<init point%>}{%<end point%>}[%<init force%>][%<end force%>][%<force interval%>];
\dlineload{3}{%<plane%>}[%<plane dist%>]{%<init point%>}{%<end point%>}[%<init force%>][%<end force%>][%<lineload dist%>][%<force interval%>];
\dlineload{4}{%<plane%>}[%<plane dist%>]{%<init point%>}{%<end point%>}[%<force interval%>][%<force length%>];
\dlineload{5}{%<rotA%>}[%<rotB%>]{%<init point%>}{%<end point%>}[%<init force%>][%<end force%>][%<lineload dist%>][%<force interval%>];
\dlineload{6}{%<rotA%>}[%<rotB%>]{%<init point%>}{%<end point%>}[%<force interval%>][%<force length%>];

\dinternalforces{plane}{init point}{end point}{init val}{end val};
\dinternalforces{plane}[plane dist]{init point}{end point}{init val}{end val};
\dinternalforces{plane}[plane dist]{init point}{end point}{init val}{end val}[parabola height];
\dinternalforces{plane}[plane dist]{init point}{end point}{init val}{end val}[parabola height][color];
\dinternalforces{plane}[plane dist]{init point}{end point}{init val}{end val}[parabola height][color][bend pos];

\ddimensioning{plane}{init point}{end point}{distance};
\ddimensioning{plane}[plane dist]{init point}{end point}{distance};
\dimensioning{plane}[plane dist]{init point}{end point}{distance}[measure];
\dimensioning{plane}[plane dist]{init point}{end point}{distance}[measure][help line length];

\dnotation{1}{%<insertion point%>}{%<labelling%>}[%<orientation%>];
\dnotation{2}{%<insertion point%>}{%<labelling%>}[%<orientation%>];
\dnotation{3}{%<init point%>}{%<end point%>}[%<labelling%>][%<pos%>][%<orientation%>];
\dnotation{4}{%<init point%>}{%<end point%>}[%<labelling%>][%<pos%>][%<orientation%>][%<text orientation%>];
\dnotation{5}{%<init point%>}{%<end point%>}[%<labelling%>][%<pos%>][%<orientation%>][%<text orientation%>];
\dnotation{6}{%<insertion point%>}{%<labelling%>};

\daddon{1}{%<plane%>}[%<plane dist%>]{%<insertion point%>}{%<end point%>}{%<pos%>};
\daddon{2}{%<plane%>}[%<plane dist%>]{%<insertion point%>}{%<init point%>}{%<end point%>}[%<orientation%>];
\daddon{3}{%<plane%>}[%<plane dist%>]{%<insertion point%>}{%<init point%>}{%<end point%>}[%<orientation%>];

\setcoords{x angle}{y angle}
\setcoords{x angle}{y angle}[x dir][y dir][z dir]
\setcoords{x angle}{y angle}[x dir][y dir][z dir][z angle]

\setaxis{1}
\setaxis{2}
\setaxis{3}[%<Xlabel%>][%<Ylabel%>][%<Zlabel%>][%<xlabel%>][%<ylabel%>][%<zlabel%>]
\setaxis{4}[%<x orient.%>][%<y orient.%>][%<z orient.%>]

\showpoint

\dscaling{type%keyvals}{factor}
#keyvals:\dscaling#c
1
2
3
4
5
6
#endkeyvals

## parameters ##
\DaddonLength#*
\DaxisDistance#*
\DaxisLength#*
\DbigLineWidth#*
\DdimensioningBar#*
\DforceDistance#*
\DforceLength#*
\DhelpVarA#*
\DhelpVarB#*
\DhelpVarC#*
\DhingeAxialHeight#*
\DhingeAxialLength#*
\DhingeBigRadius#*
\DhingeCornerLength#*
\DhingeRadius#*
\DhugeLineWidth#*
\DlineloadDistance#*
\DlineloadDistanceMM#*
\DlineloadForce#*
\DlineloadInterval#*
\DlocalaxisLength#*
\DnormalLineWidth#*
\DnoteRadius#*
\DscalingParameter#*
\DshowPointParameter#*
\DsmallLineWidth#*
\DspringAmplitude#*
\DspringLength#*
\DspringPostLength#*
\DspringPreLength#*
\DspringSegmentLength#*
\DsupportGap#*
\DsupportLength#*
\DtinyLineWidth#*
\DxAngle#*
\DxLength#*
\DxNodePos#*
\DxVarA#*
\DxVarB#*
\DyAngle#*
\DyLength#*
\DyNodePos#*
\DyVarA#*
\DyVarB#*
\DzAngle#*
\DzLength#*
\DzNodePos#*
\DzVarA#*
\DzVarB#*
\barAngle#*
\barGap#*
\bigLineWidth#*
\colorGray#*
\dimensioningBar#*
\forceDistance#*
\forceLength#*
\hatchingAmplitude#*
\hatchingAngle#*
\hatchingLength#*
\helpVarA#*
\helpVarB#*
\hingeAxialHeight#*
\hingeAxialLength#*
\hingeCornerLength#*
\hingeRadius#*
\hugeLineWidth#*
\lineloadDistance#*
\lineloadForce#*
\lineloadInterval#*
\momentAngle#*
\momentDistance#*
\normalLineWidth#*
\pathdrawcolor#*
\pathfillcolor#*
\scalingParameter#*
\smallLineWidth#*
\springAmplitude#*
\springLength#*
\springPostLength#*
\springPreLength#*
\springSegmentLength#*
\supportBasicHeight#*
\supportBasicLength#*
\supportGap#*
\supportHatchingHeight#*
\supportHatchingLength#*
\supportHeight#*
\supportLength#*
\temperatureHeight#*
\tinyLineWidth#*

## other ##
\tdplotmult{macro%cmd}{x}{y}#*d
\tdplotresetrotatedcoordsorigin#*
\tdplotsetrotatedcoordsorigin{point}#*
\tdplotsetrotatedcoords{angle1}{angle2}{angle3}#*
\tdplotsinandcos{macor1%cmd}{macor2%cmd}{angle}#*d
