# zxjatype package
# Matthew Bertucci 2022/05/31 for v0.7

#include:ifxetex
#include:xeCJK

#keyvals:\usepackage/zxjatype#c
default
nodefault
CJKchecksingle
noCJKchecksingle
# options passed to xeCJK
LocalConfig=#true,false,%<name%>
xeCJKactive#true,false
CJKspace#true,false
CJKmath#true,false
CJKglue=%<glue%>
CJKecglue=%<glue%>
xCJKecglue=%<glue%>
CheckSingle#true,false
WindowPenalty=%<integer%>
PlainEquation#true,false
NewLineCS={%<commands%>}
NewLineCS+={%<commands%>}
NewLineCS-={%<commands%>}
EnvCS={%<commands%>}
EnvCS+={%<commands%>}
EnvCS-={%<commands%>}
InlineEnv={%<env1,env2,...%>}
InlineEnv+={%<env1,env2,...%>}
InlineEnv-={%<env1,env2,...%>}
AutoFallback#true,false
AutoFakeBold=%<true,false,or <number>%>
AutoFakeSlant=%<true,false,or <number>%>
EmboldenFactor=%<factor%>
SlantFactor=%<factor%>
PunctStyle=#quanjiao,banjiao,kaiming,hangmobanjiao,CCT,plain
PunctFamily=%<false or <family>%>
KaiMingPunct={%<punctuation%>}
KaiMingPunct+={%<punctuation%>}
KaiMingPunct-={%<punctuation%>}
LongPunct={%<punctuation%>}
LongPunct+={%<punctuation%>}
LongPunct-={%<punctuation%>}
MiddlePunct={%<punctuation%>}
MiddlePunct+={%<punctuation%>}
MiddlePunct-={%<punctuation%>}
PunctWidth=##L
PunctBoundWidth=##L
AllowBreakBetweenPuncts#true,false
RubberPunctSkip=#true,false,plus,minus
CheckFullRight#true,false
NoBreakCS={%<commands%>}
NoBreakCS+={%<commands%>}
NoBreakCS-={%<commands%>}
Verb=#true,false,env,env+
LoadFandol#true,false
#endkeyvals

\bxDebug{text}#S
\zxJaFamilyFontHook#*
\zxJaFamilyName#*
\inhibitglue
\setjamainfont{font name}
\setjamainfont{font name}[font features%keyvals]
\setjamainfont[font features%keyvals]{font name}#*
\setjasansfont{font name}
\setjasansfont{font name}[font features%keyvals]
\setjasansfont[font features%keyvals]{font name}#*
\setjamonofont{font name}
\setjamonofont{font name}[font features%keyvals]
\setjamonofont[font features%keyvals]{font name}#*
\setjafamilyfont{family}{font name}
\setjafamilyfont{family}{font name}[font features%keyvals]
\setjafamilyfont{family}[font features%keyvals]{font name}#*
\jafamily{family}
\zxjapanesestyle
\zxusejapaneseparameters
\zxuseoriginalparameters
\setjafontscale{factor}
\jafamilyinverbatim#*
\nojafamilyinverbatim#*
\>
\<
\textrawja{text}
\textrawen{text}
\begin{rawjatext}
\end{rawjatext}
\begin{rawentext}
\end{rawentext}

#keyvals:\setjamainfont,\setjasansfont,\setjamonofont,\setjafamilyfont
# keys unique to xeCJK
AutoFakeBold
AutoFakeSlant
FallBack
FallBack=%<font name%>
# keys from fontspec
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
Mapping=%<xetex-only feature%>
Renderer=#Node,Base,Harfbuzz,OpenType,AAT,Graphite
%fontspecfeature
#endkeyvals