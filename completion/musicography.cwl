# musicography package
# Matthew Bertucci 2023/09/11

#include:stackengine
#include:graphicx
#include:setspace

#keyvals:\usepackage/musicography#c
bigger
#endkeyvals

\ifLargeFont#*
\LargeFonttrue#*
\LargeFontfalse#*

\musFont#*
\musFontBig#*
\musFontLarge#*
\musNumFont#*
\musSymbol{kern before}{raise}{kern after}{symbol}#*
\musSymbol[font cmds]{kern before}{raise}{kern after}{symbol}#*
\musAccidentalFont#*
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

\musBreve
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

\musStack{arg}
\musStack{arg}[align]
\musStack[font cmd]{arg}
\musStack[font cmd]{arg}[align]
\musSymbolMeter{symbol}
\meterPlus{meter}{symbol}
\meterThree
\meterThreeTwo
\meterCplus{symbol}
\meterCutCplus{symbol}
\meterCutCThree
\meterCutCThreeTwo

\musMeter{upper}{lower}
\musMeter[font cmd]{upper}{lower}

\musFigFont#*
\musFigSize#*
\musFig{content}
\musFig[align]{content}
\noFig
\noFig[text%plain]

\meterC
\meterCutC
\meterCThree
\meterCThreeTwo
\meterZfont#*
\meterZsymbol#*
\meterCZ
\meterO

\musDegree{numeral}
\musPitch{pitch}{octave}

\symbolList{font cmd}{number}#*
\musixSymbolList#*

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
