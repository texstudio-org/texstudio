# fncychap package
# Matthew Bertucci 2/5/2022 for v1.34

#keyvals:\usepackage/fncychap#c
Sonny
Lenny
PetersLenny
Bjornstrup
Glenn
Conny
Rejne
Bjarne
#endkeyvals

\mghrulefill{width}
\ChNameUpperCase
\ChNameLowerCase
\ChNameAsIs
\ChTitleUpperCase
\ChTitleLowerCase
\ChTitleAsIs
\ChRuleWidth{width}
\ChNameVar{code}
\ChNumVar{code}
\ChTitleVar{code}
\TheAlphaChapter

\DOCH#*
\DOTI{arg}#*
\DOTIS{arg}#*
\mylen#*
\myhi#*
\px#*
\py#*
\pxx#*
\pyy#*
\RW#*
\CNV#*
\CNoV#*
\CTV#*
\FmN{arg}#*
\FmTi{arg}#*

#ifOption:PetersLenny
\bl#*
\BL{width}
\br#*
\BR{width}
\tl#*
\TL{width}
\trr#*
\TR{width}
\blrule#*
\BLrule{width}
#endif

#ifOption:Bjornstrup
#include:color
#endif

#ifOption:Glenn
\backskip
#endif

#ifOption:Bjarne
\AlphaDecNo
\AlphaNo
\theAlphaCnt
\theAlphaDecCnt
#endif

\ifusecolor#*
\usecolortrue#*
\usecolorfalse#*
\ifUCN#*
\UCNtrue#*
\UCNfalse#*
\ifLCN#*
\LCNtrue#*
\LCNfalse#*
\ifinapp#*
\inapptrue#*
\inappfalse#*
\ifUCT#*
\UCTtrue#*
\UCTfalse#*
\ifLCT#*
\LCTtrue#*
\LCTfalse#*