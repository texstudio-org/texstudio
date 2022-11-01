# luatexko package
# Matthew Bertucci 2022/11/01 for v3.5

#include:luatexbase
#include:fontspec
#include:kolabels-utf

#keyvals:\usepackage/luatexko#c
hangul
hanja
#endkeyvals

#ifOption:hangul
#include:konames-utf
#endif

\setmainhangulfont{font name}
\setmainhangulfont[font features%keyvals]{font name}
\setmainhanjafont{font name}
\setmainhanjafont[font features%keyvals]{font name}
\setmainfallbackfont{font name}
\setmainfallbackfont[font features%keyvals]{font name}
\setsanshangulfont{font name}
\setsanshangulfont[font features%keyvals]{font name}
\setsanshanjafont{font name}
\setsanshanjafont[font features%keyvals]{font name}
\setsansfallbackfont{font name}
\setsansfallbackfont[font features%keyvals]{font name}
\setmonohangulfont{font name}
\setmonohangulfont[font features%keyvals]{font name}
\setmonohanjafont{font name}
\setmonohanjafont[font features%keyvals]{font name}
\setmonofallbackfont{font name}
\setmonofallbackfont[font features%keyvals]{font name}
\newhangulfontfamily{command}{font name}#d
\newhangulfontfamily{command}[font features%keyvals]{font name}#d
\newhanjafontfamily{command}{font name}#d
\newhanjafontfamily{command}[font features%keyvals]{font name}#d
\newfallbackfontfamily{command}{font name}#d
\newfallbackfontfamily{command}[font features%keyvals]{font name}#d
\newhangulfontface{command}{font name}#d
\newhangulfontface{command}[font features%keyvals]{font name}#d
\newhanjafontface{command}{font name}#d
\newhanjafontface{command}[font features%keyvals]{font name}#d
\newfallbackfontface{command}{font name}#d
\newfallbackfontface{command}[font features%keyvals]{font name}#d
\addhangulfontfeature{font features%keyvals}
\addhangulfontfeatures{font features%keyvals}#*
\addhanjafontfeature{font features%keyvals}
\addhanjafontfeatures{font features%keyvals}#*
\addfallbackfontfeature{font features%keyvals}
\addfallbackfontfeatures{font features%keyvals}#*
\hangulfontspec{font name}
\hangulfontspec[font features%keyvals]{font name}
\adhochangulfont{font name}#*
\adhochangulfont[font features%keyvals]{font name}#*
\hanjafontspec{font name}
\hanjafontspec[font features%keyvals]{font name}
\adhochanjafont{font name}#*
\adhochanjafont[font features%keyvals]{font name}#*
\fallbackfontspec{font name}
\fallbackfontspec[font features%keyvals]{font name}
\adhocfallbackfont{font name}#*
\adhocfallbackfont[font features%keyvals]{font name}#*
\hangulbyhangulfont=%<0 or 1%>
\hanjabyhanjafont=%<0 or 1%>
\hangulpunctuations=%<0 or 1%>
\registerpunctuations{code1,code2,...}
\registerhangulpunctuations{code1,code2,...}#*
\unregisterpunctuations{code1,code2,...}
\unregisterhangulpunctuations{code1,code2,...}#*
\registerbreakableafter{code1,code2,...}
\registerbreakablebefore{code1,code2,...}
\typesetclassic
\typesetmodern
\typesetvertical
\inhibitglue
\begin{vertical}{dimen%l}
\end{vertical}
\verticaltypesetting
\begin{verticaltypesetting}
\end{verticaltypesetting}
\begin{horizontal}{dimen%l}
\end{horizontal}
\dotemph{character}
\dotemphraise#*
\dotemphchar#*
\ruby{characters}{annotation}
\rubyfont#*
\rubysize#*
\rubysep#*
\rubynooverlap
\rubyoverlap
\xxruby{characters}{annotation}
\basestr#*
\rubystr#*
\uline{text}
\sout{text}
\soutdown#*
\uuline{text}
\xout{text}
\uwave{text}
\dashuline{text}
\dotuline{text}
\ulinedown#*
\ulinewidth#*
\markoverwith{mark code}{text}#*
\josaignoreparens=%<0 or 1%>
\는#*
\은#*
\을#*
\를#*
\와#*
\과#*
\가#*
\이#*
\라#*
\으#*
\로#*
\으로#*
\이라#*
\setmathhangulfont{font name}
\setmathhangulfont[font features%keyvals]{font name}
\setmathhangulblock{begin}{end}
\luatexhangulnormalize=%<0 or 1%>
\luatexuhcinputencoding=%<0 or 1%>
\hellipsis

#keyvals:\setmainhangulfont,\setmainhanjafont,\setmainfallbackfont,\setsanshangulfont,\setsanshanjafont,\setsansfallbackfont,\setmonohangulfont,\setmonohanjafont,\setmonofallbackfont,\newhangulfontfamily,\newhanjafontfamily,\newfallbackfontfamily,\newhangulfontface,\newhanjafontface,\newfallbackfontface,\addhangulfontfeature,\addhangulfontfeatures,\addhanjafontfeature,\addhanjafontfeatures,\addfallbackfontfeature,\addfallbackfontfeatures,\hangulfontspec,\adhochangulfont,\hanjafontspec,\adhochanjafont,\fallbackfontspec,\adhocfallbackfont,\setmathhangulfont
# features specific to luatexko
InterHangul=##L
InterLatinCJK=##L
CharRaise=##L
RemoveClassicSpaces
CompressPunctuations
Expansion
Protrusion=
InterCharacter=##L
InterCharStretch=##L
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
Renderer=%<renderer%>
#endkeyvals

# not documented
\ifluatexkorunningselectfont#*
\japanese#*
\korean#*
\koreanlanguage#*
\luatexkoautojosaattr#*
\luatexkoclassicattr#*
\luatexkodefaultfallbackfont#*
\luatexkodefaulthangulfont#*
\luatexkodefaulthanjafont#*
\luatexkodoluacode{lua code}#*
\luatexkodotemphattr#*
\luatexkodotemphcount#*
\luatexkofallbackfont#*
\luatexkofallbackfontattr#*
\luatexkofallbackselectfont#*
\luatexkogetrubybasechar{arg1}{arg2}#*
\luatexkogetrubyrubychar{arg1}{arg2}#*
\luatexkohangulbyhangulattr#*
\luatexkohangulbyhangulfont#*
\luatexkohangulfont#*
\luatexkohangulfontattr#*
\luatexkohangulnormalize#*
\luatexkohangulpunctuations#*
\luatexkohangulselectfont#*
\luatexkohanjabyhanjaattr#*
\luatexkohanjabyhanjafont#*
\luatexkohanjafont#*
\luatexkohanjafontattr#*
\luatexkohanjaselectfont#*
\luatexkohorizboxmoveright#*
\luatexkojosaactivate#*
\luatexkojosaactive#*
\luatexkolangCJK#*
\luatexkoleaderstype#*
\luatexkomarkoverwith{arg1}{arg2}#*
\luatexkomonohangulfont#*
\luatexkorotatebox{arg}#*
\luatexkorubyalloc#*
\luatexkorubyattr#*
\luatexkorubycount#*
\luatexkorunningselectfontfalse#*
\luatexkorunningselectfonttrue#*
\luatexkoselectfont#*
\luatexkostretchfactor#*
\luatexkouhcinputencoding#*
\luatexkoulinecount#*
\luatexkounrotatebox{arg}#*
\luatexkoxxruby#*
\Schinese#*
\Tchinese#*
