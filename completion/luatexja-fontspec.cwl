# luatexja-fontspec package
# Matthew Bertucci 4/9/2022

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
\jfontspec[font features%keyvals]{font}
\setmainjfont{font}
\setmainjfont[font features%keyvals]{font}
\setsansjfont{font}
\setsansjfont[font features%keyvals]{font}
\setmonojfont{font}
\setmonojfont[font features%keyvals]{font}
\newjfontfamily{cmd}{font}#d
\newjfontfamily{cmd}[font features%keyvals]{font}#d
\renewjfontfamily{cmd}{font}
\renewjfontfamily{cmd}[font features%keyvals]{font}
\setjfontfamily{cmd}{font}#d
\setjfontfamily{cmd}[font features%keyvals]{font}#d
\newjfontface{cmd}{font}#d
\newjfontface{cmd}[font features%keyvals]{font}#d
\defaultjfontfeatures{font features%keyvals}
\defaultjfontfeatures[font name list]{font features%keyvals}
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
Contextuals=#Swash,Alternate,WordInitial,WordFinal,LineFinal,Inner,ResetAll
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
ItalicFeatures={%<features%>}
ItalicFont=%<font name%>
Kerning=#On,Off,Reset,Uppercase,ResetAll
Language=%<language%>
LetterSpace=%<number%>
Letters=#SmallCaps,PetiteCaps,UppercaseSmallCaps,UppercasePetiteCaps,Unicase,ResetAll
Ligatures=#Required,Common,Contextual,Rare,Discretionary,Historic,TeX
LocalForms=#On,Off,Reset
NFSSFamily=%<font family%>
Numbers=#Uppercase,UppercaseOff,Lowercase,LowercaseOff,Lining,LiningOff,OldStyle,OldStyleOff,Proportional,ProportionalOff,Monospaced,MonospacedOff,SlashedZero,SlashedZeroOff,Arabic,ArabicOff,ResetAll
OpticalSize=%<size%>
Ornament=
Path=%<file path%>
PunctuationSpace=%<number%>
RawFeature=%<feature tag%>
Scale=%<number%>
ScaleAgain=%<number%>
Script=%<name%>
Size=%<number%>
SizeFeatures={%<features%>}
SlantedFeatures={%<features%>}
SlantedFont=%<font name%>
SmallCapsFeatures={%<features%>}
SmallCapsFont=%<font name%>
Style=#Alternate,Italic,Ruby,Swash,Cursive,Historic,Titling,HorizontalKana,VerticalKana,ResetAll
StylisticAlternates=%<feature%>
StylisticSet=%<set number%>
SwashFeatures={%<features%>}
SwashFont=%<font name%>
UprightFeatures={%<features%>}
UprightFont=%<font name%>
Variant=%<integer%>
Vertical=#RotatedGlyphs,AlternatesForRotation,Alternates,KanaAlternates,Kerning,AlternateMetrics,HalfMetrics,ProportionalMetrics,ResetAll
VerticalPosition=#Superior,Inferior,Numerator,Denominator,ScientificInferior,Ordinal,ResetAll
WordSpace=%<number%>
Mapping=%<xetex-only feature%>
Renderer=%<renderer%>
#endkeyvals
