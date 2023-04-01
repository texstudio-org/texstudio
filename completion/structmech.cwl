# structmech package
# Matthew Bertucci 2023/03/31 for v1.2

#include:ifthen
#include:kvoptions
#include:tikz
#include:tikzlibrarycalc
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarypositioning
#include:tikzlibrarydecorations.pathmorphing
#include:xkeyval
#include:xstring

\setstructmech{options%keyvals}

#keyvals:\usepackage/structmech#c,\setstructmech
fill=#%color
line=#%color
node=#%color
axis=#%color
rotation=#%color
convention=#*ign,direction
showvalue=#on,off
absvalue=#on,off
opacity=%<factor%>
linewidth=##L
#endkeyvals

\NodalForce{x,y}
\NodalForce[color]{x,y}
\NodalForce[color]{x,y}[Hlabel][Vlabel][Rlabel]
\NodalForce[color]{x,y}[Hlabel][Vlabel][Rlabel]{rotation}[scale]

\BasicForce{x1,y1}{x2,y2}{label}
\BasicForce[number%keyvals]{x1,y1}{x2,y2}{label}
\BasicForce[number%keyvals]{x1,y1}{x2,y2}{label}{TikZ keys}
\BasicForce[number%keyvals]{x1,y1}{x2,y2}{label}{TikZ keys}[label1][label2][label3]

#keyvals:\BasicForce
1
2L
2H
2
3
#endkeyvals

\UDL{x1,y1}{x2,y2}
\UDL[F]{%<x1,y1%>}{%<x2,y2%>}
\UDL[F]{x1,y1}{x2,y2}[label]
\UDL[F]{x1,y1}{x2,y2}[label]{scale}

\HingeSupport{x,y}
\HingeSupport[rotation]{x,y}
\HingeSupport[rotation]{x,y}{scale}
\FixedSupport{x,y}
\FixedSupport[rotation]{x,y}
\FixedSupport[rotation]{x,y}{scale}
\RollerSupport{x,y}
\RollerSupport[rotation]{x,y}
\RollerSupport[rotation]{x,y}{scale}
\SliderSupport{x,y}
\SliderSupport[rotation]{x,y}
\SliderSupport[rotation]{x,y}{scale}

\SleeveSupport{x,y}
\SleeveSupport[rotation]{x,y}
\SleeveSupport[rotation]{x,y}[gap%l]
\SleeveSupport[rotation]{x,y}[gap%l]{scale}

\Rigid{x,y}
\Rigid[rotation]{x,y}
\Rigid[rotation]{x,y}{scale}

\CoorOrigin{x,y}
\CoorOrigin[rotation]{x,y}
\CoorOrigin[rotation]{x,y}[xlabel][ylabel]
\CoorOrigin[rotation]{x,y}[xlabel][ylabel]{scale}

\IForceA{x1,y1}{x2,y2}{force-lower}{force-higher}
\IForceA[color]{x1,y1}{x2,y2}{force-lower}{force-higher}
\IForceA[color]{x1,y1}{x2,y2}{force-lower}{force-higher}{scale}

\IForceB{x1,y1}{x2,y2}{moment-lower}{moment-higher}{increment}
\IForceB[color]{x1,y1}{x2,y2}{moment-lower}{moment-higher}{increment}
\IForceB[color]{x1,y1}{x2,y2}{moment-lower}{moment-higher}{increment}{scale}

\BeamDeformP{x1,y1}{x2,y2}{disp-lower}{disp-higher}
\BeamDeformP[color]{x1,y1}{x2,y2}{disp-lower}{disp-higher}
\BeamDeformP[color]{x1,y1}{x2,y2}{disp-lower}[rot-lower]{disp-higher}[rot-higher]
\BeamDeformP[color]{x1,y1}{x2,y2}{disp-lower}[rot-lower]{disp-higher}[rot-higher]{scale}

\BeamDeformR{x1,y1}{x2,y2}
\BeamDeformR[color]{x1,y1}{x2,y2}
\BeamDeformR[color]{x1,y1}{x2,y2}[rot-lower][rot-higher]
\BeamDeformR[color]{x1,y1}{x2,y2}[rot-lower][rot-higher]{scale}

\Dashpot{x1,y1}{x2,y2}
\Dashpot{x1,y1}{x2,y2}{scale}
\Dashpot[color]{x1,y1}{x2,y2}
\Dashpot[color]{x1,y1}{x2,y2}{scale}

\Spring{x1,y1}{x2,y2}
\Spring{x1,y1}{x2,y2}{scale}
\Spring[color]{x1,y1}{x2,y2}
\Spring[color]{x1,y1}{x2,y2}{scale}

\Angle#S
\FAC#S
\Length#S
\lvla#S
\lvlb#S
\absvalue#S
\axisColor#S
\convention#S
\fillColor#S
\fillOpacity#S
\lineColor#S
\lineWidth#S
\nodeColor#S
\rotationColor#S
\showvalue#S
\unitL#S
