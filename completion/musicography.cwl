# musicography package
# Matthew Bertucci 2/15/2022

#include:stackengine

#keyvals:\usepackage/musicography#c
bigger
#endkeyvals

\ifLargeFont#*
\LargeFonttrue#*
\LargeFontfalse#*

\musFont#*
\musFontBig#*
\musFontLarge#*
\musNumFont{text}#*
\musSymbol{kern before}{raise}{kern after}{symbol}#*
\musSymbol[font cmds]{kern before}{raise}{kern after}{symbol}#*
\musAccidental{symbol code}

\musFlat
\musDoubleFlat
\musSharp
\musDoubleSharp
\musNatural
\fl
\sh
\na

\musStemmedNote{symbol}#*
\musFlaggedNote{symbol1}{symbol2}#*
\musDottedNote{symbol}#*

\musStem#*
\musSegno#*
\musDot#*

\musWhole
\musHalf
\musQuarter
\musEighth
\musSixteenth
\musThirtySecond
\musSixtyFourth

\musWholeDotted
\musHalfDotted
\musQuarterDotted
\musEighthDotted
\musSixteenthDotted
\musThirtySecondDotted
\musSixtyFourthDotted

\musStack{arg}#*
\musStack[font cmd]{arg}#*
\musSymbolMeter{symbol}#*
\meterCplus{symbol}#*

\musMeter{upper}{lower}

\musFigFont#*
\musFig{content}
\noFig
\noFig[text%plain]

\meterC
\meterCutC
\meterCThree
\meterCThreeTwo
\meterCZ
\meterO

\musSemibreve#*
\musMinim#*
\musSemiminim#*
\musCorchea#*
\musFusa#*
\musSemibreveDotted#*
\musMinimDotted#*
\musSeminiminimDotted#*
\musCorcheaDotted#*
\musFusaDotted#*