# hanjacnt package
# ponte-vecchio 2023-01-17 for v2.8

#keyvals:\usepackage/hhanjacnt#c
manspace
20
finhanja
#endkeyvals

#include:fontspec

## 2.1 Numbers
\NumHanja{%<number%>}
\NumHangul{%<number%>}
\NumHanjaBig{%<number%>}
\NumHangulBig{%<number%>}

## 2.2 Financial Hanja
#ifOption:finhanja
\FinHanjaMode
\FinHanjaMode{%<option%>%keyvals%}
#endif

#keyvals\FinHanjaMode#
full
var
fullvar
off
on
#endkeyvals

### 2.3 Spaces at 'man' (10,000) positions
#ifOption:manspace
\ManSpaceOn
\ManSpaceOff
#endif

### 2.4 Digit
\DigitHanja{%<number%>}
\HanjaZero{%<char%>}
\HanjaZeroFont{%<font%>}
\TwentyHanjaChar[%<options%>]

#keyvals\TwentyHanjaChar#c
2
10
20
30
21
31
#endkeyvals

### 2.5 Replace Hanja for a given number
\MarkHanja{%<name%>%keyvals}{%<hanja%>}

#keyvals\MarkHanja#c
default
one
two
three
four
five
six
seven
eight
nine
ten
hundred
thousand
shi
bae
chu
man
eok
cho
#endkeyvals

## 2.6 Counters
\HANJA{%<counter%>}#*
\HANGUL{%<counter%>}#*
\HANJADIG{%<counter%>}#*

## 2.7 Date-times in Hanja and Hangul
\HanjaYear{%<year%>}
\HanjaMonth{%<month%>}
\HanjaDay{%<day%>}
\HangulYear{%<year%>}
\HangulMonth{%<month%>}
\HangulDay{%<day%>}
\HanjaTodayWithGanji
\HangulTodayWithGanji
\HangulLunarToday
\HangulLunarTodayWithGanji
\HangulLunarDay{%<day%>}
\HangulDangiYear{%<year%>}
\HanjaDangiYear{%<year%>}
\HangulGanji
\HangulGanji{%<year%>}
\HanjaGanji
\HanjaGanji{%<year%>}

### 2.8 Selecting fonts
\NumHanjaFont{%<font%>}
\NumHanjaFont[%<features%>]{%<font%>}#*
\NumHanjaFont{%<font%>}[%<features%>%keyvals]
\NumHanjaFont[%<features%>]{%<font%>}[%<features%>%keyvals]#*

#keyvals:\NumHanjaFont#c
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
Opacity=%<factor%>
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
WordSpace=%<number%>
Mapping=%<xetex-only feature%>
Renderer=%<renderer%>
#endkeyvals