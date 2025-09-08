# xepersian 23.7
# hadi_sfr (info@hadisafari.ir)
# updated 2025/09/08 for v25.09.03

# Equivalent Persian Commands, documentclasses and some other commands are not included

#include:fontspec
#include:unicode-persiancal
#include:unicode-persianmath
#include:bidi

#keyvals:\usepackage/xepersian#c
defaultlatinfontfeatures={%<font features%>}
extrafootnotefeatures
Kashida
quickindex-variant1
quickindex-variant2
localise
mathdigits=#automatic,default,persian
inlinemathdigits=#automatic,default,persian
displaymathdigits=#automatic,default,persian
RTLdocument
documentdirection=#righttoleft,lefttoright
tabledirection=#righttoleft,lefttoright
script=#latin,nonlatin
rldocument
footnoterule=#automatic,left,right,split,textwidth
footnotedirection=#righttoleft,lefttoright
debugfootnotedirection
abjadvariant=#one,two
mathfontsizescale=%<factor%>
fontsizescale=%<factor%>
fontsize=##L
latinfontsizescale=%<factor%>
baselineskipscale=%<factor%>
latinbaselineskipscale=%<factor%>
logo
pdfinfo
computeautoilg
DetectColumn
debugtextdigitfont
perpagefootnote
#endkeyvals

#ifOption:extrafootnotefeatures
\normalfootnotes
\twocolumnfootnotes
\threecolumnfootnotes
\fourcolumnfootnotes
\fivecolumnfootnotes
\sixcolumnfootnotes#*
\sevencolumnfootnotes#*
\eightcolumnfootnotes#*
\ninecolumnfootnotes#*
\tencolumnfootnotes#*
\RTLcolumnfootnotes
\LTRcolumnfootnotes
\paragraphfootnotes
\setLTRparagraphfootnotes
\setRTLparagraphfootnotes
# not documented
\AddExtraParaSkip{arg}#*
\extrafeetendmini#*
\extrafeetendminihook#*
\extrafeetins#*
\extrafeetinshook#*
\FeetAboveFloat#*
\FeetAtBottom#*
\FeetBelowFloat#*
\FeetBelowRagged#*
\footfootmark#*
\footfudgefactor#*
\footinsdim#*
\footmarkstyle{text}#*
\footmarkwidth#*
\footscript{arg}#*
\foottextfont#*
\LTRfootfootmark#*
\LTRfootmarkstyle{text}#*
\LTRfootscript{arg}#*
\LTRfoottextfont#*
\multiplefootnotemarker#*
\normalRTLparaLTRfootnotes#*
\RTLfootfootmark#*
\RTLfootmarkstyle{text}#*
\RTLfootscript{arg}#*
\RTLfoottextfont#*
\setSingleSpace{number}#*
#endif
#ifOption:extrafootnotefeatures=on
\normalfootnotes
\twocolumnfootnotes
\threecolumnfootnotes
\fourcolumnfootnotes
\fivecolumnfootnotes
\sixcolumnfootnotes#*
\sevencolumnfootnotes#*
\eightcolumnfootnotes#*
\ninecolumnfootnotes#*
\tencolumnfootnotes#*
\RTLcolumnfootnotes
\LTRcolumnfootnotes
\paragraphfootnotes
\setLTRparagraphfootnotes
\setRTLparagraphfootnotes
# not documented
\AddExtraParaSkip{arg}#*
\extrafeetendmini#*
\extrafeetendminihook#*
\extrafeetins#*
\extrafeetinshook#*
\FeetAboveFloat#*
\FeetAtBottom#*
\FeetBelowFloat#*
\FeetBelowRagged#*
\footfootmark#*
\footfudgefactor#*
\footinsdim#*
\footmarkstyle{text}#*
\footmarkwidth#*
\footscript{arg}#*
\foottextfont#*
\LTRfootfootmark#*
\LTRfootmarkstyle{text}#*
\LTRfootscript{arg}#*
\LTRfoottextfont#*
\multiplefootnotemarker#*
\normalRTLparaLTRfootnotes#*
\RTLfootfootmark#*
\RTLfootmarkstyle{text}#*
\RTLfootscript{arg}#*
\RTLfoottextfont#*
\setSingleSpace{number}#*
#endif

#ifOption:Kashida
\KashidaOn
\KashidaOff
#endif
#ifOption:Kashida=on
\KashidaOn
\KashidaOff
#endif

#ifOption:localise
\eqcommand{command-name in Persian}{original LaTeX command-name}
\eqenvironment{environment-name in Persian}{original LaTeX environment-name}
\makezwnjletter#*
\EqEnvironment{environment-name in Persian}{original LaTeX environment-name}#*
#endif
#ifOption:localise=on
\eqcommand{command-name in Persian}{original LaTeX command-name}
\eqenvironment{environment-name in Persian}{original LaTeX environment-name}
\makezwnjletter#*
\EqEnvironment{environment-name in Persian}{original LaTeX environment-name}#*
#endif

#ifOption:DetectColumn
\DetectColumn{arg1}{arg2}
\DetectColumn[opt]{arg1}{arg2}
#endif
#ifOption:DetectColumn=on
\DetectColumn{arg1}{arg2}
\DetectColumn[opt]{arg1}{arg2}
#endif

#ifOption:perpagefootnote
#include:bidi-perpage
#endif
#ifOption:perpagefootnote=on
#include:bidi-perpage
#endif

\xepersianreleasename#*
\xepersianversion#*
\xepersiandate#*
\settextfont{font name}
\settextfont[options%keyvals]{font name}
\settextdigitfont{font name}#*
\settextdigitfont[options%keyvals]{font name}#*
\setdigitfont{font name}#*
\setdigitfont[options%keyvals]{font name}#*
\setlatintextfont{font name}
\setlatintextfont[options%keyvals]{font name}
\defpersianfont{command}{font name}#d
\defpersianfont{command}[options%keyvals]{font name}#d
\deflatinfont{command}{font name}#d
\deflatinfont{command}[options%keyvals]{font name}#d
\setpersiansansfont{font name}
\setpersiansansfont[options%keyvals]{font name}
\persiansffamily
\textpersiansf{text}
\setpersianmonofont{font name}
\setpersianmonofont[options%keyvals]{font name}
\persianttfamily
\textpersiantt{text}
\setiranicfont{font name}
\setiranicfont[options%keyvals]{font name}
\iranicfamily
\textiranic{text}
\setnavarfont{font name}#*
\setnavarfont[options%keyvals]{font name}#*
\navarfamily#*
\textnavar{text}#*
\setpookfont{font name}#*
\setpookfont[options%keyvals]{font name}#*
\pookfamily#*
\textpook{text}#*
\setsayehfont{font name}#*
\setsayehfont[options%keyvals]{font name}#*
\sayehfamily#*
\textsayeh{text}#*
\setlatinsansfont{font name}
\setlatinsansfont[options%keyvals]{font name}
\setlatinmonofont{font name}
\setlatinmonofont[options%keyvals]{font name}
\begin{latin}
\end{latin}
\begin{persian}
\end{persian}
\begin{latinitems}
\end{latinitems}
\begin{persianitems}
\end{persianitems}
\lr{text}
\rl{text}
\latintoday
\twocolumnstableofcontents
\XePersian
\plq
\prq
\Latincite{keylist}#c
\Latincite[add. text]{keylist}
\harfi{counter}
\harfinumeral{integer}
\adadi{counter}
\adadinumeral{integer}
\tartibi{counter}
\tartibinumeral{integer}
\Abjad{counter}#*
\Abjadnumeral{integer}#*
\abjad{counter}#*
\abjadnumeral{integer}#*
\ifwritexviii
\writexviiitrue#*
\writexviiifalse#*

#keyvals:\settextfont,\settextdigitfont,\setdigitfont,\setlatintextfont,\defpersianfont,\deflatinfont,\setpersiansansfont,\setpersianmonofont,\setiranicfont,\setnavarfont,\setpookfont,\setsayehfont,\setlatinsansfont,\setlatinmonofont,\redeflatinfont,\redefpersianfont
Alternate=%<feature%>
Annotation=
AutoFakeBold=%<number%>
AutoFakeSlant=%<number%>
BoldFeatures={%<features%>}
BoldFont=%<font name%>
BoldItalicFeatures={%<features%>}
BoldItalicFont=%<font name%>
BoldSlantedFeatures={%<features%>}
BoldSlantedFont=%<font name%>
BoldSwashFeatures={%<features%>}
BoldSwashFont=%<font name%>
CJKShape=#Traditional,Simplified,JIS1978,JIS1983,JIS1990,Expert,NLC
CharacterVariant=%<number%>
CharacterVariant={%<glyph num list%>:%<variety num%>}
CharacterWidth=#Proportional,Full,Half,Thurd,Quarter,AlternateProportional,AlternateHalf,ResetAll
Color=#%color
Colour=#%color
Contextuals=#Swash,SwashOff,Alternate,AlternateOff,WordInitial,WordInitialOff,WordFinal,WordFinalOff,LineFinal,LineFinalOff,Inner,InnerOff,ResetAll
Diacritics=#MarkToBase,MarkToMark,AboveBase,BelowBase,ResetAll
Extension=%<extension%>
FakeBold=%<number%>
FakeSlant=%<number%>
FakeStretch=%<number%>
Font=%<font name%>
FontFace={%<series%>}{%<shape%>}{%<font name%>}
Fractions=#On,Off,Reset,Alternate,ResetAll
HyphenChar=%<character%>
IgnoreFontspecFile
Instance=%<instance%>
ItalicFeatures={%<features%>}
ItalicFont=%<font name%>
Kerning=#On,Off,Reset,Uppercase,ResetAll
KpseOnly
Language=%<language%>
LetterSpace=%<number%>
Letters=#SmallCaps,PetiteCaps,UppercaseSmallCaps,UppercasePetiteCaps,Unicase,Uppercase,Lowercase,ResetAll
Ligatures=#Required,Common,Contextual,Rare,Discretionary,Historic,TeX
LocalForms=#On,Off,Reset
NFSSFamily=%<font family%>
Numbers=#Uppercase,UppercaseOff,Lowercase,LowercaseOff,Lining,LiningOff,OldStyle,OldStyleOff,Proportional,ProportionalOff,Monospaced,MonospacedOff,SlashedZero,SlashedZeroOff,Arabic,ArabicOff,ResetAll
Opacity=%<factor%>
OpticalSize=%<size%>
Ornament=
Path=%<file path%>
PunctuationSpace=%<number%>
RawAxis={%<tag=number%>}
RawFeature=%<feature tag%>
Scale=%<number%>
ScaleAgain=%<number%>
Script=%<name%>
Size=%<number%>
SizeFeatures={%<features%>}
Slant=%<number%>
SlantedFeatures={%<features%>}
SlantedFont=%<font name%>
SmallCapsFeatures={%<features%>}
SmallCapsFont=%<font name%>
Style=#Alternate,Italic,Ruby,Swash,Cursive,Historic,Titling,Uppercase,HorizontalKana,VerticalKana,ResetAll
StylisticAlternates=%<feature%>
StylisticSet=%<set number%>
SwashFeatures={%<features%>}
SwashFont=%<font name%>
UprightFeatures={%<features%>}
UprightFont=%<font name%>
Variant=%<integer%>
Vertical=#RotatedGlyphs,AlternatesForRotation,Alternates,KanaAlternates,Kerning,AlternateMetrics,HalfMetrics,ProportionalMetrics,ResetAll
VerticalPosition=#Superior,Inferior,Numerator,Denominator,ScientificInferior,Ordinal,ResetAll
Weight=%<number%>
Width=%<number%>
WordSpace=%<number%>
Mapping=%<xetex-only feature%>
Renderer=#Node,Base,Harfbuzz,OpenType,AAT,Graphite
%fontspecfeature
#endkeyvals

# not documented
\begin{latin*}#*
\end{latin*}#*
\begin{persian*}#*
\end{persian*}#*
\bibname#*
\ccname#*
\chaptername#*
\datename#*
\enclname#*
\headtoname#*
\IfxepersianPackageVersion{version}{true}{false}#*
\IfxepersianPackageVersionBefore{version}{true}{false}#*
\IfxepersianPackageVersionLater{version}{true}{false}#*
\iranicdefault#*
\LatinAlphs#*
\latinfont#*
\navardefault#*
\originaltoday#S
\pagename#*
\PersianAlphs#*
\persianfont#*
\persiansfdefault#*
\persianttdefault#*
\pookdefault#*
\proofname#*
\redeflatinfont{command}{font name}#*
\redeflatinfont{command}[options%keyvals]{font name}#*
\redefpersianfont{command}{font name}#*
\redefpersianfont{command}[options%keyvals]{font name}#*
\resetlatinfont#*
\sayehdefault#*
\setfontsize[opt]{arg}#*
\setfontsize{arg}#*
\setpersianfont#*
\TextDigitFontOff#*
\TextDigitFontOn#*
