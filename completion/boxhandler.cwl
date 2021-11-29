# boxhandler package
# Matthew Bertucci 11/27/2021 for v1.30

#include:ifthen
#include:pbox

\bxtable{caption%text}{boxed object%text}
\bxtable[loc%keyvals]{caption%text}{boxed object%text}
\bxfigure{caption%text}{boxed object%text}
\bxfigure[loc%keyvals]{caption%text}{boxed object%text}

#keyvals:\bxtable,\bxfigure,\nextTable,\nextFigure
ht
hb
t
b
p
#endkeyvals

\relaxCaptionWidth
\relaxCaptionWidth[length]
\limitCaptionWidth
\limitCaptionWidth[length]
\constrainCaptionWidth
\constrainCaptionWidth[min-length%l][max-length%l]

\captionStyle{offset type%keyvals}{alignment type}
#keyvals:\captionStyle
o
n
#endkeyvals

\hyperactive#*
\hyperactive[length]#*

\captionGap#*
\TableDeadMargin#*
\FigureDeadMargin#*
\theabovecaptionskipterm#*
\thebelowcaptionskipterm#*
\CaptionFontSize#*
\TableFontSize#*
\LRTablePlacement#*
\LRFigurePlacement#*
\CaptionJustification#*

\WrapperOn
\WrapperOn[default]
\WrapperOff
\Wrapper{custom wrapper%text}
\WrapperTextStyle#*

\holdTables
\holdFigures
\clearTables
\clearFigures
\killlistoftables
\killlistoffigures
\killtableofcontents
\holdlistoftables
\holdlistoffigures
\clearlistoftables
\clearlistoffigures
\nextTable
\nextTable[loc%keyvals]
\nextFigure
\nextFigure[loc%keyvals]

\DeadMargin#*
\CaptionBoxWidth#*
\theTableIndex#*
\theFigureIndex#*
\theTableClearedIndex#*
\theFigureClearedIndex#*
\thepromptTablesFlag#*
\thepromptFiguresFlag#*
\StoreTable{caption}{boxed object}{wrapper%cmd}{wrapper status%cmd}#*d
\StoreFigure{caption}{boxed object}{wrapper%cmd}{wrapper status%cmd}#*d
\SaveCBox{cmd}{boxed object}#*d
\ReciteTable{caption}{cmd}{width}{wrapper}{wrapper status}#*
\ReciteTable[loc%keyvals]{caption}{cmd}{width}{wrapper}{wrapper status}#*
\ReciteFigure{caption}{cmd}{wdth}{wrapper}{wrapper status}#*
\ReciteFigure[loc%keyvals]{caption}{cmd}{width}{wrapper}{wrapper status}#*
\theClearedTable{caption}{cmd}{width}{wrapper}{wrapper status}#*
\theClearedTable[loc%keyvals]{caption}{cmd}{wdth}{wrapper}{wrapper status}#*
\theClearedFigure{caption}{cmd}{wdth}{wrapper}{wrapper status}#*
\theClearedFigure[loc%keyvals]{caption}{cmd}{wdth}{wrapper}{wrapper status}#*

\thelofInvocations#*
\thelofPrints#*
\thelotInvocations#*
\thelotPrints#*
\wrapper#*

\FigCaptionWidthLabel#S
\FigureBoxLabel#S
\FigureCaptionLabel#S
\FigureWrapper#S
\TableBoxLabel#S
\TableCaptionLabel#S
\TableWrapper#S
\TblCaptionWidthLabel#S
\WrapperStatus#S
\WrapperText#S
\WrapperTextDefault#S
\oldlistoffigures#S
\oldlistoftables#S
\oldabovecaptionskip#S
\oldbelowcaptionskip#S

# deprecated
\arltable#S
\arlfigure#S