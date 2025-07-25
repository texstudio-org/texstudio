# mathspec package
# Matthew Bertucci 12/30/2021 for v0.2b

#include:xetex
#include:amstext
#include:etoolbox
#include:ifxetex
#include:fontspec
#include:xkeyval

#keyvals:\usepackage/mathspec#c
normalskips
math
no-math
MnSymbol
# options passed to fontspec
tuenc
euenc
config
no-config
quiet
silent
#endkeyvals

#ifOption:MnSymbol
#include:MnSymbol
#endif

\setmathsfont(sets){font name}
\setmathsfont(sets)[font features%keyvals]{font name}
\setmathfont(sets){font name}
\setmathfont(sets)[font features%keyvals]{font name}
\setmathcal{font name}
\setmathcal[font features%keyvals]{font name}
\setmathbb{font name}
\setmathbb[font features%keyvals]{font name}
\setmathfrak{font name}
\setmathfrak[font features%keyvals]{font name}
\setallmainfonts(sets){font name}
\setallmainfonts(sets)[font features%keyvals]{font name}
\setprimaryfont{font name}
\setprimaryfont[font features%keyvals]{font name}
\setallsansfonts{font name}
\setallsansfonts[font features%keyvals]{font name}
\setallmonofonts{font name}
\setallmonofonts[font features%keyvals]{font name}

# these are already in fontspec.cwl
# \setmathrm{font name}
# \setmathrm[font features%keyvals]{font name}
# \setmathsf{font name}
# \setmathsf[font features%keyvals]{font name}
# \setmathtt{font name}
# \setmathtt[font features%keyvals]{font name}

#keyvals:\setmathsfont,\setmathfont,\setallmainfonts,\setprimaryfont
# shapes from mathspec
Uppercase=#Regular,Italic,PLain
Lowercase=#Regular,Italic,PLain
Arabic=#Regular,Italic,PLain
#endkeyvals

#keyvals:\setmathsfont,\setmathfont,\setmathrm,\setmathsf,\setmathtt,\setmathcal,\setmathbb,\setmathfrak,\setallmainfonts,\setprimaryfont,\setallsansfonts,\setallmonofonts
# other keys from fontspec
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

\exchangeforms{list%keyvals}

\Alpha#m
\Beta#m
\Epsilon#m
\Zeta#m
\Eta#m
\Iota#m
\Kappa#m
\Mu#m
\Nu#m
\Omicron#m
\omicron#m
\Rho#m
\Tau#m
\Chi#m
\Digamma#m
\digamma#m
\varbeta#m
\varkappa#m
\varTheta#m

\normalisevarforms
\normalisevarforms[list%keyvals]
\normalizevarforms
\normalizevarforms[list%keyvals]

#keyvals:\exchangeforms,\normalisevarforms,\normalizevarforms
beta
epsilon
theta
kappa
pi
rho
phi
Theta
#endkeyvals

\setminwhitespace
\setminwhitespace[number]

\XeTeXDeclareMathSymbol{arg1}{arg2}{arg3}{arg4}#S
\currentmathstyle#S
\themkern#*
\ernewcommand{cmd}{def}#*d
