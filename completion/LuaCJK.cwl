# LuaCJK package
# Matthew Bertucci 2026/11/12 for v0.0.1

#include:luatex
#include:fontspec

\addCJKfontfeatures*{font features%keyvals}
\addCJKfontfeatures{font features%keyvals}
\CJKfamilydefault#*
\CJKfamily{family}
\CJKfontspec[font features%keyvals]{font}
\CJKfontspec{font}
\CJKrmdefault#*
\CJKsfdefault#*
\CJKttdefault#*
\defaultCJKfontfeatures{font features%keyvals}
\fangsong
\heiti
\kaishu
\lishu
\LuaCJKCancelSubCJKBlock{block list}
\LuaCJKDeclareCharClass{class}{range list}
\LuaCJKDeclarePunctClass{group}{range list}
\LuaCJKDeclarePunctStyle{name}{keyvals}
\LuaCJKDeclareSubCJKBlock{block}{range list}
\LuaCJKdisable
\LuaCJKEditPunctStyle{style}{keyvals}
\LuaCJKenable
\LuaCJKnobreak{text}
\LuaCJKOffVerbAddon
\LuaCJKResetCharClass
\LuaCJKRestoreSubCJKBlock{block list}
\LuaCJKsetkern{before}{after}{length}
\LuaCJKsetup{keyvals}
\LuaCJKsetwidth*{punct list}{length}
\LuaCJKsetwidth{punct list}{length}
\LuaCJKShipoutHook{code}
\LuaCJKVerbAddon
\LuaCJKversion#*
\newCJKfontfamily[family]{command}[font features%keyvals]{font}#d
\newCJKfontfamily[family]{command}{font}#d
\newCJKfontfamily{command}[font features%keyvals]{font}#d
\newCJKfontfamily{command}{font}#d
\normalspacedchars{char list}
\setCJKfallbackfamilyfont{family}[font features%keyvals]{font}#*
\setCJKfallbackfamilyfont{family}[font features%keyvals]{font}[font features%keyvals]#S
\setCJKfallbackfamilyfont{family}{font}
\setCJKfallbackfamilyfont{family}{font}[font features%keyvals]
\setCJKfamilyfont{family}[font features%keyvals]{font}#*
\setCJKfamilyfont{family}[font features%keyvals]{font}[font features%keyvals]#S
\setCJKfamilyfont{family}{font}
\setCJKfamilyfont{family}{font}[font features%keyvals]
\setCJKmainfont[font features%keyvals]{font}#*
\setCJKmainfont[font features%keyvals]{font}[font features%keyvals]#S
\setCJKmainfont{font}
\setCJKmainfont{font}[font features%keyvals]
\setCJKmathfont[font features%keyvals]{font}#*
\setCJKmathfont[font features%keyvals]{font}[font features%keyvals]#S
\setCJKmathfont{font}
\setCJKmathfont{font}[font features%keyvals]
\setCJKmonofont[font features%keyvals]{font}#*
\setCJKmonofont[font features%keyvals]{font}[font features%keyvals]#S
\setCJKmonofont{font}
\setCJKmonofont{font}[font features%keyvals]
\setCJKsansfont[font features%keyvals]{font}#*
\setCJKsansfont[font features%keyvals]{font}[font features%keyvals]#S
\setCJKsansfont{font}
\setCJKsansfont{font}[font features%keyvals]
\songti
\youyuan


#keyvals:\addCJKfontfeatures,\addCJKfontfeatures*,\CJKfontspec,\defaultCJKfontfeatures,\newCJKfontfamily,\setCJKfallbackfamilyfont,\setCJKfamilyfont,\setCJKmainfont,\setCJKmathfont,\setCJKmonofont,\setCJKsansfont
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
Renderer=#Node,Base,Harfbuzz,OpenType,AAT,Graphite
%fontspecfeature
#endkeyvals

