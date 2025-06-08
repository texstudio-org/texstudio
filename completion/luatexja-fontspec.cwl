# luatexja-fontspec package
# Matthew Bertucci 2024/07/15

#include:l3keys2e
#include:luatexja
#include:fontspec

#keyvals:\usepackage/luatexja-fontspec#c
match#true,false
scale=%<factor%>
# options passed to fontspec
tuenc
euenc
math
no-math
config
no-config
quiet
silent
#endkeyvals

\Cjascale

\jfontspec{font}
\jfontspec{font}[font features%keyvals]
\jfontspec[font features%keyvals]{font}#*
\jfontspec[font features%keyvals]{font}[font features%keyvals]#S
\setmainjfont{font}
\setmainjfont{font}[font features%keyvals]
\setmainjfont[font features%keyvals]{font}#*
\setmainjfont[font features%keyvals]{font}[font features%keyvals]#S
\setsansjfont{font}
\setsansjfont{font}[font features%keyvals]
\setsansjfont[font features%keyvals]{font}#*
\setsansjfont[font features%keyvals]{font}[font features%keyvals]#S
\setmonojfont{font}
\setmonojfont{font}[font features%keyvals]
\setmonojfont[font features%keyvals]{font}#*
\setmonojfont[font features%keyvals]{font}[font features%keyvals]#S
\newjfontfamily{cmd}{font}#d
\newjfontfamily{cmd}{font}[font features%keyvals]#d
\newjfontfamily{cmd}[font features%keyvals]{font}#*d
\newjfontfamily{cmd}[font features%keyvals]{font}[font features%keyvals]#Sd
\renewjfontfamily{cmd}{font}
\renewjfontfamily{cmd}{font}[font features%keyvals]
\renewjfontfamily{cmd}[font features%keyvals]{font}#*
\renewjfontfamily{cmd}[font features%keyvals]{font}[font features%keyvals]#S
\setjfontfamily{cmd}{font}#d
\setjfontfamily{cmd}{font}[font features%keyvals]#d
\setjfontfamily{cmd}[font features%keyvals]{font}#*d
\setjfontfamily{cmd}[font features%keyvals]{font}[font features%keyvals]#Sd
\providejfontfamily{cmd}{font}#d
\providejfontfamily{cmd}{font}[font features%keyvals]#d
\providejfontfamily{cmd}[font features%keyvals]{font}#*d
\providejfontfamily{cmd}[font features%keyvals]{font}[font features%keyvals]#Sd
\newjfontface{cmd}{font}#d
\newjfontface{cmd}{font}[font features%keyvals]#d
\newjfontface{cmd}[font features%keyvals]{font}#*d
\newjfontface{cmd}[font features%keyvals]{font}[font features%keyvals]#Sd
\renewjfontface{cmd}{font}
\renewjfontface{cmd}{font}[font features%keyvals]
\renewjfontface{cmd}[font features%keyvals]{font}#*
\renewjfontface{cmd}[font features%keyvals]{font}[font features%keyvals]#S
\setjfontface{cmd}{font}#d
\setjfontface{cmd}{font}[font features%keyvals]#d
\setjfontface{cmd}[font features%keyvals]{font}#*d
\setjfontface{cmd}[font features%keyvals]{font}[font features%keyvals]#Sd
\providejfontface{cmd}{font}#d
\providejfontface{cmd}{font}[font features%keyvals]#d
\providejfontface{cmd}[font features%keyvals]{font}#*d
\providejfontface{cmd}[font features%keyvals]{font}[font features%keyvals]#Sd
\defaultjfontfeatures{font features%keyvals}
\defaultjfontfeatures[font name list]{font features%keyvals}
\defaultjfontfeatures+{font features%keyvals}
\defaultjfontfeatures+[font name list]{font features%keyvals}
\addjfontfeatures{font features%keyvals}
\addjfontfeature{font features%keyvals}#S

#keyvals:\jfontspec,\setmainjfont,\setsansjfont,\setmonojfont,\newjfontfamily,\renewjfontfamily,\setjfontfamily,\newjfontface,\defaultjfontfeatures,\addjfontfeatures,\addjfontfeature
# features specific to luatexja
CID=%<name%>
JFM=%<name%>
JFM-var=%<name%>
NoEmbed
Kanjiskip#true,false
TateFeatures={%<features%>}
TateFont=%<font%>
YokoFeatures={%<features%>}
AltFont={%<specification%>}
# regular fontspec font features
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
Renderer=#Node,Base,Harfbuzz,OpenType,AAT,Graphite
%fontspecfeature
#endkeyvals
