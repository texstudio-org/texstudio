# pstring package
# Matthew Bertucci 2/19/2022

#include:ifpdf
#include:pgfcore

#keyvals:\usepackage/pstring#c
pstricks
pgf
#endkeyvals

#ifOption:pstricks
#include:pstricks
#include:pst-node
\pstr{string spec%formula}
\pstr[raise%l]{string spec%formula}
\pstr[raise%l][nodesep%l]{string spec%formula}
#endif

\pstrSetLabelStyle{style cmds}
\pstrSetArrowColor{color}
\pstrSetArrowLineWidth{width}
\pstrSetArrowAngle{angle}
\pstrSetArrowLabel{label}
\pstrSetArrowLineStyle{line style%keyvals}

#keyvals:\pstrSetArrowLineStyle#c
solid
dotted
dashed
none
#endkeyvals

\Pstr{string spec%formula}
\Pstr[raise%l]{string spec%formula}
\Pstr[raise%l][nodesep%l]{string spec%formula}

\nd#*
\arrow{source}{target}{angle}{label}{linecolor}{linestyle}#*
\txt{text%plain}#*

# not documented
\TheAtCode#S
\act#S
\angleA#S
\angleB#S
\bendpt#S
\cptC#S
\cptD#S
\linestyle#S
\link#S
\linkNoStar{arg1}{arg2}#S
\linkStar{arg1}{arg2}#S
\linkparam#S
\lnklabel#S
\lnklabelNoStar{arg1}#S
\lnklabelStar{arg1}#S
\maxdim#S
\ncHarc#S
\opt#S
\options#S
\percentchar#S
\ptA#S
\ptB#S
\reste#S
\suite#S
\text#S
\ifRequestPSengine#S
\RequestPSenginetrue#S
\RequestPSenginefalse#S
\ifRequestPGFengine#S
\RequestPGFenginetrue#S
\RequestPGFenginefalse#S
\ifLoadPSengine#S
\LoadPSenginetrue#S
\LoadPSenginefalse#S
\ifLoadPGFengine#S
\LoadPGFenginetrue#S
\LoadPGFenginefalse#S
\ifwriteprologuefile#S
\writeprologuefiletrue#S
\writeprologuefilefalse#S