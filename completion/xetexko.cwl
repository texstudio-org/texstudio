# xetexko package
# Matthew Bertucci 2022/05/05 for v4.1

#include:xetex
#include:fontspec
#include:kolabels-utf

#keyvals:\usepackage/xetexko#c
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
\setsanshangulfont{font name}
\setsanshangulfont[font features%keyvals]{font name}
\setsanshanjafont{font name}
\setsanshanjafont[font features%keyvals]{font name}
\setmonohangulfont{font name}
\setmonohangulfont[font features%keyvals]{font name}
\setmonohanjafont{font name}
\setmonohanjafont[font features%keyvals]{font name}
\newhangulfontfamily{command}{font name}#d
\newhangulfontfamily{command}[font features%keyvals]{font name}#d
\newhanjafontfamily{command}{font name}#d
\newhanjafontfamily{command}[font features%keyvals]{font name}#d
\newhangulfontface{command}{font name}#d
\newhangulfontface{command}[font features%keyvals]{font name}#d
\newhanjafontface{command}{font name}#d
\newhanjafontface{command}[font features%keyvals]{font name}#d
\addhangulfontfeature{font features%keyvals}
\addhangulfontfeatures{font features%keyvals}#*
\addhanjafontfeature{font features%keyvals}
\addhanjafontfeatures{font features%keyvals}#*
\hangulfontspec{font name}
\hangulfontspec[font features%keyvals]{font name}
\adhochangulfont{font name}#*
\adhochangulfont[font features%keyvals]{font name}#*
\hanjafontspec{font name}
\hanjafontspec[font features%keyvals]{font name}
\adhochanjafont{font name}#*
\adhochanjafont[font features%keyvals]{font name}#*
\hanjabyhangulfont
\xetexkofontregime[options%keyvals]{regime}
\latinalphs
\latinparens
\latincolons
\latinhyphens
\latinpuncts
\latincjksymbols
\hangulalphs
\hangulparens
\hangulcolons
\hangulhyphens
\hangulpuncts
\hangulcjksymbols
\hanjaalphs
\hanjaparens
\hanjacolons
\hanjahyphens
\hanjapuncts
\hanjacjksymbols
\prevfontalphs
\prevfontparens
\prevfontcolons
\prevfonthyphens
\prevfontpuncts
\prevfontcjksymbols
\latinmarks
\hangulmarks
\hanjamarks
\prevfontmarks
\everyhangul{code}
\everyhanja{code}
\disablekoreanfonts
\disablecjksymbolspacing
\enablecjksymbolspacing
\compresspunctuations
\nocompresspunctuations
\disablehangulspacing
\disablehangulspacingandlinebreak
\enablehangulspacingandlinebreak
\verticaltypesetting
\begin{verticaltypesetting}#*
\end{verticaltypesetting}#*
\begin{vertical}{dimen%l}
\end{vertical}
\begin{horizontal}{dimen%l}
\end{horizontal}
\removeclassicspaces
\typesetclassic
\typesetmodern
\inhibitglue
\hangingpunctuations
\hangingpunctuation#*
\sethangingratio"%<charnum%>=%<ratio%>
\unsethangingratio"%<charnum%>
\setmathhangulfont{font name}
\setmathhangulfont[font features%keyvals]{font name}
\setmathhangulblock{begin}{end}
\jong
\jung
\rieul
\dotemph{text}
\dotemphraise#*
\dotemphchar#*
\xetexkoulemsupport#*
\hellipsis

#keyvals:\setmainhangulfont,\setmainhanjafont,\setsanshangulfont,\setsanshanjafont,\setmonohangulfont,\setmonohanjafont,\newhangulfontfamily,\newhanjafontfamily,\newhangulfontface,\newhanjafontface,\addhangulfontfeature,\addhangulfontfeatures,\addhanjafontfeature,\addhanjafontfeatures,\hangulfontspec,\adhochangulfont,\hanjafontspec,\adhochanjafont,\setmathhangulfont
# features specific to luatexko
InterHangul=##L
interhchar=##L
InterLatinCJK=##L
hu=##L
CharRaise=##L
charraise=##L
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

#keyvals:\xetexkofontregime
alphs=#latin,hangul,hanja,prevfont
parens=#latin,hangul,hanja,prevfont
colons=#latin,hangul,hanja,prevfont
hyphens=#latin,hangul,hanja,prevfont
puncts=#latin,hangul,hanja,prevfont
cjksymbols=#latin,hangul,hanja,prevfont
#endkeyvals

# not documented
\가#*
\이#*
\은#*
\는#*
\을#*
\를#*
\와#*
\과#*
\으#*
\로#*
\라#*
\으로#*
\chinese#*
\japanese#*
\Schinese#*
\Tchinese#*
\typesethorizontal#*
\typesetvertical#*
\vertlatin{text}#*
\XeKocatcodeofATchar#*
\XeTeXcharclassAA#*
\XeTeXcharclassAC#*
\XeTeXcharclassAH#*
\XeTeXcharclassAM#*
\XeTeXcharclassAO#*
\XeTeXcharclassAP#*
\XeTeXcharclassBoundary#*
\XeTeXcharclassCJ#*
\XeTeXcharclassCL#*
\XeTeXcharclassCM#*
\XeTeXcharclassEX#*
\XeTeXcharclassFS#*
\XeTeXcharclassHG#*
\XeTeXcharclassID#*
\XeTeXcharclassIgnore#*
\XeTeXcharclassIS#*
\XeTeXcharclassJJ#*
\XeTeXcharclassLD#*
\XeTeXcharclassMD#*
\XeTeXcharclassNS#*
\XeTeXcharclassOP#*
\XeTeXcharclassSY#*
\XeTeXcharclassVC#*
\xetexkocharraise#*
\xetexkodefaulthangulfont#*
\xetexkodefaulthanguloption#*
\xetexkodefaulthanjafont#*
\xetexkodefaulthanjaoption#*
\xetexkohangulfont#*
\xetexkohangulfontfamily#*
\xetexkohanguloption#*
\xetexkohanjafont#*
\xetexkohanjafontfamily#*
\xetexkohanjaoption#*
\xetexkohu#*
\xetexkointerhchar#*
\xetexkomainhangulfont#*
\xetexkomainhanguloption#*
\xetexkomainhanjafont#*
\xetexkomainhanjaoption#*
\xetexkomathhangulfamily#*
\xetexkomonohangulfont#*
\xetexkomonohanguloption#*
\xetexkomonohanjafont#*
\xetexkomonohanjaoption#*
\xetexkosanshangulfont#*
\xetexkosanshanguloption#*
\xetexkosanshanjafont#*
\xetexkosanshanjaoption#*
\XKinterhangulbreak#*
\XKinterhanjabreak#*

# deprecated
\hangulnums#S
\hangulquotes#S
\hanjanums#S
\hanjaquotes#S
\latinnums#S
\latinquotes#S
\prevfontnums#S
\prevfontquotes#S