# xeCJK package
# Darcy Hu <hot123tea123@gmail.com> 2016
#modified zepinglee 30 Jan 2021
# updated 7 June 2022 for v3.9.0

#include:xetex
#include:xtemplate
#include:fontspec

# package only keys
#keyvals:\usepackage/xeCJK#c
LocalConfig=#true,false,%<name%>
#endkeyvals

## 3.1
\xeCJKsetup{options%keyvals}
#keyvals:\xeCJKsetup,\usepackage/xeCJK#c
xeCJKactive#true,false
#
CJKspace#true,false
CJKmath#true,false
CJKglue=%<glue%>
CJKecglue=%<glue%>
xCJKecglue=%<glue%>
#
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
#
AutoFallback#true,false
AutoFakeBold=%<true,false,or <number>%>
AutoFakeSlant=%<true,false,or <number>%>
EmboldenFactor=%<factor%>
SlantFactor=%<factor%>
#
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
#
Verb=#true,false,env,env+
LoadFandol#true,false
#endkeyvals

# key completion does not work in final arg so alternative syntax used below
## 3.2
\setCJKmainfont{font name}
\setCJKmainfont{font name}[font features]#*
\setCJKmainfont[font features%keyvals]{font name}

\setCJKsansfont{font name}
\setCJKsansfont{font name}[font features]#*
\setCJKsansfont[font features%keyvals]{font name}

\setCJKmonofont{font name}
\setCJKmonofont{font name}[font features]#*
\setCJKmonofont[font features%keyvals]{font name}

\setCJKfamilyfont{family}{font name}
\setCJKfamilyfont{family}{font name}[font features]#*
\setCJKfamilyfont{family}[font features%keyvals]{font name}

\CJKfamily{family}
\CJKfamily+{family}#*
\CJKfamily-{family}#*

\newCJKfontfamily{cmd}{font name}#d
\newCJKfontfamily{cmd}[font features%keyvals]{font name}#d
\newCJKfontfamily[family]{cmd}{font name}#*d
\newCJKfontfamily[family]{cmd}[font features%keyvals]{font name}#d

\CJKfontspec{font name}
\CJKfontspec{font name}[font features]#*
\CJKfontspec[font features%keyvals]{font name}

\defaultCJKfontfeatures{font features%keyvals}#*

\addCJKfontfeatures{font features%keyvals}#*
\addCJKfontfeatures*{font features%keyvals}#*
\addCJKfontfeatures[blocks]{font features%keyvals}#*
\addCJKfontfeatures*[blocks]{font features%keyvals}#*

\CJKrmdefault#S
\CJKsfdefault#S
\CJKttdefault#S

\CJKfamilydefault#S

\setCJKmathfont{font name}#*
\setCJKmathfont{font name}[font features]#*
\setCJKmathfont[font features%keyvals]{font name}#*

\setCJKfallbackfamilyfont{family}{font name}#*
\setCJKfallbackfamilyfont{family}{font name}[font features]#*
\setCJKfallbackfamilyfont{family}[font features%keyvals]{font name}#*

## 3.3
\xeCJKDeclareSubCJKBlock{block}{block range}#*
\xeCJKDeclareSubCJKBlock*{block}{block range}#*

\xeCJKCancelSubCJKBlock{blocks}#*
\xeCJKCancelSubCJKBlock*{blocks}#*

\xeCJKRestoreSubCJKBlock{blocks}#*
\xeCJKRestoreSubCJKBlock*{blocks}#*

## 3.4
\xeCJKDeclareCharClass{char class}{class range}#*
\xeCJKDeclareCharClass*{char class}{class range}#*

\xeCJKResetCharClass#*
\xeCJKResetPunctClass#*

\normalspacechars{char list}#*

## 3.5
\xeCJKsetwidth{punct list}{length}#*
\xeCJKsetwidth*{punct list}{length}#*

\xeCJKsetkern{first punct}{second punct}{length}#*

\xeCJKDeclarePunctStyle{style}{keyvals}#*
\xeCJKEditPunctStyle{style}{keyvals}#*

#keyvals:\xeCJKDeclarePunctStyle,\xeCJKEditPunctStyle
enabled-global-setting#true,false
fixed-punct-width=##L
fixed-punct-ratio=%<real%>
mixed-punct-width=##L
mixed-punct-ratio=%<real%>
middle-punct-width=##L
middle-punct-ratio=%<real%>
fixed-margin-width=##L
fixed-margin-ratio=%<real%>
mixed-margin-width=##L
mixed-margin-ratio=%<real%>
middle-margin-width=##L
middle-margin-ratio=%<real%>
bound-punct-width=##L
bound-punct-ratio=%<real%>
bound-margin-width=##L
bound-margin-ratio=%<real%>
enabled-hanging#true,false
add-min-bound-to-margin#true,false
optimize-margin#true,false
margin-minimum=##L
enabled-kerning#true,false
min-bound-to-kerning#true,false
kerning-total-width=##L
kerning-total-ratio=%<real%>
same-align-margin=##L
same-align-ratio=%<real%>
different-align-margin=##L
different-align-ratio=%<real%>
kerning-margin-width=##L
kerning-margin-ratio=%<real%>
optimize-kerning #true,false
kerning-margin-minimum=##L
#endkeyvals

## 3.7
\xeCJKVerbAddon#*
\xeCJKOffVerbAddon#*

\xeCJKnobreak#*

\xeCJKShipoutHook#*

## font feature keyvals list
#keyvals:\setCJKmainfont,\setCJKsansfont,\setCJKmonofont,\setCJKfamilyfont,\newCJKfontfamily,\CJKfontspec,\defaultCJKfontfeatures,\addCJKfontfeatures,\setCJKmathfont,\setCJKfallbackfamilyfont
Alternate=%<feature%>
Annotation=
AutoFakeBold
AutoFakeBold=%<number%>
AutoFakeSlant
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
FallBack
FallBack=%<font name%>
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
Mapping=#fullwidth-stop,full-stop,han-trad,han-simp
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
