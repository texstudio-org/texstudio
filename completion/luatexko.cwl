# luatexko package
# Matthew Bertucci 2025/08/27 for v4.5

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
\setmainhangulfont{font name}[font features%keyvals]
\setmainhangulfont[font features%keyvals]{font name}#*
\setmainhangulfont[font features%keyvals]{font name}[font features%keyvals]#S
\setmainhanjafont{font name}
\setmainhanjafont{font name}[font features%keyvals]
\setmainhanjafont[font features%keyvals]{font name}#*
\setmainhanjafont[font features%keyvals]{font name}[font features%keyvals]#S
\setmainfallbackfont{font name}
\setmainfallbackfont{font name}[font features%keyvals]
\setmainfallbackfont[font features%keyvals]{font name}#*
\setmainfallbackfont[font features%keyvals]{font name}[font features%keyvals]#S
\setsanshangulfont{font name}
\setsanshangulfont{font name}[font features%keyvals]
\setsanshangulfont[font features%keyvals]{font name}#*
\setsanshangulfont[font features%keyvals]{font name}[font features%keyvals]#S
\setsanshanjafont{font name}
\setsanshanjafont{font name}[font features%keyvals]
\setsanshanjafont[font features%keyvals]{font name}#*
\setsanshanjafont[font features%keyvals]{font name}[font features%keyvals]#S
\setsansfallbackfont{font name}
\setsansfallbackfont{font name}[font features%keyvals]
\setsansfallbackfont[font features%keyvals]{font name}#*
\setsansfallbackfont[font features%keyvals]{font name}[font features%keyvals]#S
\setmonohangulfont{font name}
\setmonohangulfont{font name}[font features%keyvals]
\setmonohangulfont[font features%keyvals]{font name}#*
\setmonohangulfont[font features%keyvals]{font name}[font features%keyvals]#S
\setmonohanjafont{font name}
\setmonohanjafont{font name}[font features%keyvals]
\setmonohanjafont[font features%keyvals]{font name}#*
\setmonohanjafont[font features%keyvals]{font name}[font features%keyvals]#S
\setmonofallbackfont{font name}
\setmonofallbackfont{font name}[font features%keyvals]
\setmonofallbackfont[font features%keyvals]{font name}#*
\setmonofallbackfont[font features%keyvals]{font name}[font features%keyvals]#S
\newhangulfontfamily{command}{font name}#d
\newhangulfontfamily{command}{font name}[font features%keyvals]#d
\newhangulfontfamily{command}[font features%keyvals]{font name}#*d
\newhangulfontfamily{command}[font features%keyvals]{font name}[font features%keyvals]#Sd
\newhanjafontfamily{command}{font name}#d
\newhanjafontfamily{command}{font name}[font features%keyvals]#d
\newhanjafontfamily{command}[font features%keyvals]{font name}#*d
\newhanjafontfamily{command}[font features%keyvals]{font name}[font features%keyvals]#Sd
\newfallbackfontfamily{command}{font name}#d
\newfallbackfontfamily{command}{font name}[font features%keyvals]#d
\newfallbackfontfamily{command}[font features%keyvals]{font name}#*d
\newfallbackfontfamily{command}[font features%keyvals]{font name}[font features%keyvals]#Sd
\newhangulfontface{command}{font name}#d
\newhangulfontface{command}{font name}[font features%keyvals]#d
\newhangulfontface{command}[font features%keyvals]{font name}#*d
\newhangulfontface{command}[font features%keyvals]{font name}[font features%keyvals]#Sd
\newhanjafontface{command}{font name}#d
\newhanjafontface{command}{font name}[font features%keyvals]#d
\newhanjafontface{command}[font features%keyvals]{font name}#*d
\newhanjafontface{command}[font features%keyvals]{font name}[font features%keyvals]#Sd
\newfallbackfontface{command}{font name}#d
\newfallbackfontface{command}{font name}[font features%keyvals]#d
\newfallbackfontface{command}[font features%keyvals]{font name}#*d
\newfallbackfontface{command}[font features%keyvals]{font name}[font features%keyvals]#Sd
\addhangulfontfeature{font features%keyvals}
\addhangulfontfeatures{font features%keyvals}#*
\addhanjafontfeature{font features%keyvals}
\addhanjafontfeatures{font features%keyvals}#*
\addfallbackfontfeature{font features%keyvals}
\addfallbackfontfeatures{font features%keyvals}#*
\hangulfontspec{font name}
\hangulfontspec{font name}[font features%keyvals]
\hangulfontspec[font features%keyvals]{font name}#*
\hangulfontspec[font features%keyvals]{font name}[font features%keyvals]#S
\adhochangulfont{font name}#*
\adhochangulfont{font name}[font features%keyvals]#*
\adhochangulfont[font features%keyvals]{font name}#*
\adhochangulfont[font features%keyvals]{font name}[font features%keyvals]#S
\hanjafontspec{font name}
\hanjafontspec{font name}[font features%keyvals]
\hanjafontspec[font features%keyvals]{font name}#*
\hanjafontspec[font features%keyvals]{font name}[font features%keyvals]#S
\adhochanjafont{font name}#*
\adhochanjafont{font name}[font features%keyvals]#*
\adhochanjafont[font features%keyvals]{font name}#*
\adhochanjafont[font features%keyvals]{font name}[font features%keyvals]#S
\fallbackfontspec{font name}
\fallbackfontspec{font name}[font features%keyvals]
\fallbackfontspec[font features%keyvals]{font name}#*
\fallbackfontspec[font features%keyvals]{font name}[font features%keyvals]#S
\adhocfallbackfont{font name}#*
\adhocfallbackfont{font name}[font features%keyvals]#*
\adhocfallbackfont[font features%keyvals]{font name}#*
\adhocfallbackfont[font features%keyvals]{font name}[font features%keyvals]#S
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
\setmathhangulfont{font name}[font features%keyvals]
\setmathhangulfont[font features%keyvals]{font name}#*
\setmathhangulfont[font features%keyvals]{font name}[font features%keyvals]#S
\setmathhangulblock{begin}{end}
\luatexhangulnormalize=%<0 or 1%>
\luatexuhcinputencoding=%<0 or 1%>
\hellipsis

#keyvals:\setmainhangulfont,\setmainhanjafont,\setmainfallbackfont,\setsanshangulfont,\setsanshanjafont,\setsansfallbackfont,\setmonohangulfont,\setmonohanjafont,\setmonofallbackfont,\newhangulfontfamily,\newhanjafontfamily,\newfallbackfontfamily,\newhangulfontface,\newhanjafontface,\newfallbackfontface,\addhangulfontfeature,\addhangulfontfeatures,\addhanjafontfeature,\addhanjafontfeatures,\addfallbackfontfeature,\addfallbackfontfeatures,\hangulfontspec,\adhochangulfont,\hanjafontspec,\adhochanjafont,\fallbackfontspec,\adhocfallbackfont,\setmathhangulfont,\addfontfeature,\addfontfeatures,\defaultfontfeatures,\fontspec,\newfontface,\newfontfamily,\providefontface,\providefontfamily,\renewfontface,\renewfontfamily,\setboldmathrm,\setfontface,\setfontfamily,\setmainfont,\setmathrm,\setmathsf,\setmathtt,\setmonofont,\setromanfont,\setsansfont
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
#endkeyvals

#keyvals:\setmainhangulfont,\setmainhanjafont,\setmainfallbackfont,\setsanshangulfont,\setsanshanjafont,\setsansfallbackfont,\setmonohangulfont,\setmonohanjafont,\setmonofallbackfont,\newhangulfontfamily,\newhanjafontfamily,\newfallbackfontfamily,\newhangulfontface,\newhanjafontface,\newfallbackfontface,\addhangulfontfeature,\addhangulfontfeatures,\addhanjafontfeature,\addhanjafontfeatures,\addfallbackfontfeature,\addfallbackfontfeatures,\hangulfontspec,\adhochangulfont,\hanjafontspec,\adhochanjafont,\fallbackfontspec,\adhocfallbackfont,\setmathhangulfont
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

# not documented
\ifluatexkorunningselectfont#S
\japanese#S
\korean#S
\koreanlanguage#S
\luatexkoautojosaattr#S
\luatexkoclassicattr#S
\luatexkodefaultfallbackfont#S
\luatexkodefaulthangulfont#S
\luatexkodefaulthanjafont#S
\luatexkodoluacode{lua code}#S
\luatexkodotemphattr#S
\luatexkodotemphcount#S
\luatexkofallbackfont#S
\luatexkofallbackfontattr#S
\luatexkofallbackselectfont#S
\luatexkohangulbyhangulattr#S
\luatexkohangulbyhangulfont#S
\luatexkohangulfont#S
\luatexkohangulfontattr#S
\luatexkohangulnormalize#S
\luatexkohangulpunctuations#S
\luatexkohangulselectfont#S
\luatexkohanjabyhanjaattr#S
\luatexkohanjabyhanjafont#S
\luatexkohanjafont#S
\luatexkohanjafontattr#S
\luatexkohanjaselectfont#S
\luatexkohorizboxmoveright#S
\luatexkoinhibitglueattr#S
\luatexkojosaactivate#S
\luatexkojosaactive#S
\luatexkolangCJK#S
\luatexkoleaderstype#S
\luatexkomarkoverwith{arg1}{arg2}#S
\luatexkomonohangulfont#S
\luatexkorotatebox{arg}#S
\luatexkorubyalloc#S
\luatexkorubyattr#S
\luatexkorubycount#S
\luatexkorunningselectfontfalse#S
\luatexkorunningselectfonttrue#S
\luatexkoselectfont#S
\luatexkostretchfactor#S
\luatexkouhcinputencoding#S
\luatexkoulinecount#S
\luatexkounrotatebox{arg}#S
\Schinese#S
\Tchinese#S
