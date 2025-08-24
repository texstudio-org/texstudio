# xetexko package
# Matthew Bertucci 2025/08/24 for v4.6

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
\setmainhangulfont{font name}[font features%keyvals]
\setmainhangulfont[font features%keyvals]{font name}#*
\setmainhangulfont[font features%keyvals]{font name}[font features%keyvals]#S
\setmainhanjafont{font name}
\setmainhanjafont{font name}[font features%keyvals]
\setmainhanjafont[font features%keyvals]{font name}#*
\setmainhanjafont[font features%keyvals]{font name}[font features%keyvals]#S
\setsanshangulfont{font name}
\setsanshangulfont{font name}[font features%keyvals]
\setsanshangulfont[font features%keyvals]{font name}#*
\setsanshangulfont[font features%keyvals]{font name}[font features%keyvals]#S
\setsanshanjafont{font name}
\setsanshanjafont{font name}[font features%keyvals]
\setsanshanjafont[font features%keyvals]{font name}#*
\setsanshanjafont[font features%keyvals]{font name}[font features%keyvals]#S
\setmonohangulfont{font name}
\setmonohangulfont{font name}[font features%keyvals]
\setmonohangulfont[font features%keyvals]{font name}#*
\setmonohangulfont[font features%keyvals]{font name}[font features%keyvals]#S
\setmonohanjafont{font name}
\setmonohanjafont{font name}[font features%keyvals]
\setmonohanjafont[font features%keyvals]{font name}#*
\setmonohanjafont[font features%keyvals]{font name}[font features%keyvals]#S
\newhangulfontfamily{command}{font name}#d
\newhangulfontfamily{command}{font name}[font features%keyvals]#d
\newhangulfontfamily{command}[font features%keyvals]{font name}#*d
\newhangulfontfamily{command}[font features%keyvals]{font name}[font features%keyvals]#Sd
\newhanjafontfamily{command}{font name}#d
\newhanjafontfamily{command}{font name}[font features%keyvals]#d
\newhanjafontfamily{command}[font features%keyvals]{font name}#*d
\newhanjafontfamily{command}[font features%keyvals]{font name}[font features%keyvals]#Sd
\newhangulfontface{command}{font name}#d
\newhangulfontface{command}{font name}[font features%keyvals]#d
\newhangulfontface{command}[font features%keyvals]{font name}#*d
\newhangulfontface{command}[font features%keyvals]{font name}[font features%keyvals]#Sd
\newhanjafontface{command}{font name}#d
\newhanjafontface{command}{font name}[font features%keyvals]#d
\newhanjafontface{command}[font features%keyvals]{font name}#*d
\newhanjafontface{command}[font features%keyvals]{font name}[font features%keyvals]#Sd
\addhangulfontfeature{font features%keyvals}
\addhangulfontfeatures{font features%keyvals}#*
\addhanjafontfeature{font features%keyvals}
\addhanjafontfeatures{font features%keyvals}#*
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
\xetexkostretchshrink{glue}
\xetexkoprehanjaspacing
\xetexkoposthanjaspacing
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
\setmathhangulfont{font name}[font features%keyvals]
\setmathhangulfont[font features%keyvals]{font name}#*
\setmathhangulfont[font features%keyvals]{font name}[font features%keyvals]#S
\setmathhangulblock{begin}{end}
\jong
\jung
\rieul
\dotemph{text}
\dotemphraise#*
\dotemphchar#*
\xetexkoulemsupport#*
\hellipsis

#keyvals:\setmainhangulfont,\setmainhanjafont,\setsanshangulfont,\setsanshanjafont,\setmonohangulfont,\setmonohanjafont,\newhangulfontfamily,\newhanjafontfamily,\newhangulfontface,\newhanjafontface,\addhangulfontfeature,\addhangulfontfeatures,\addhanjafontfeature,\addhanjafontfeatures,\hangulfontspec,\adhochangulfont,\hanjafontspec,\adhochanjafont,\setmathhangulfont,\addfontfeature,\addfontfeatures,\defaultfontfeatures,\fontspec,\newfontface,\newfontfamily,\providefontface,\providefontfamily,\renewfontface,\renewfontfamily,\setboldmathrm,\setfontface,\setfontfamily,\setmainfont,\setmathrm,\setmathsf,\setmathtt,\setmonofont,\setromanfont,\setsansfont
# features specific to xetexko
InterHangul=##L
interhchar=##L
InterLatinCJK=##L
hu=##L
CharRaise=##L
charraise=##L
#endkeyvals

#keyvals:\setmainhangulfont,\setmainhanjafont,\setsanshangulfont,\setsanshanjafont,\setmonohangulfont,\setmonohanjafont,\newhangulfontfamily,\newhanjafontfamily,\newhangulfontface,\newhanjafontface,\addhangulfontfeature,\addhangulfontfeatures,\addhanjafontfeature,\addhanjafontfeatures,\hangulfontspec,\adhochangulfont,\hanjafontspec,\adhochanjafont,\setmathhangulfont
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
Mapping=%<xetex-only feature%>
Renderer=#Node,Base,Harfbuzz,OpenType,AAT,Graphite
%fontspecfeature
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
\가#S
\이#S
\은#S
\는#S
\을#S
\를#S
\와#S
\과#S
\으#S
\로#S
\라#S
\으로#S
\chinese#S
\japanese#S
\Schinese#S
\Tchinese#S
\typesethorizontal#S
\typesetvertical#S
\vertlatin{text}#S
\XeKocatcodeofATchar#S
\XeTeXcharclassAA#S
\XeTeXcharclassAC#S
\XeTeXcharclassAH#S
\XeTeXcharclassAM#S
\XeTeXcharclassAO#S
\XeTeXcharclassAP#S
\XeTeXcharclassBoundary#S
\XeTeXcharclassCJ#S
\XeTeXcharclassCL#S
\XeTeXcharclassCM#S
\XeTeXcharclassEX#S
\XeTeXcharclassFS#S
\XeTeXcharclassHG#S
\XeTeXcharclassID#S
\XeTeXcharclassIgnore#S
\XeTeXcharclassIS#S
\XeTeXcharclassJJ#S
\XeTeXcharclassLD#S
\XeTeXcharclassMD#S
\XeTeXcharclassNS#S
\XeTeXcharclassOP#S
\XeTeXcharclassSY#S
\XeTeXcharclassVC#S
\xetexkocharraise#S
\xetexkodefaulthangulfont#S
\xetexkodefaulthanguloption#S
\xetexkodefaulthanjafont#S
\xetexkodefaulthanjaoption#S
\xetexkohangulfont#S
\xetexkohangulfontfamily#S
\xetexkohanguloption#S
\xetexkohanjafont#S
\xetexkohanjafontfamily#S
\xetexkohanjaoption#S
\xetexkohu#S
\xetexkointerhchar#S
\xetexkomainhangulfont#S
\xetexkomainhanguloption#S
\xetexkomainhanjafont#S
\xetexkomainhanjaoption#S
\xetexkomathhangulfamily#S
\xetexkomonohangulfont#S
\xetexkomonohanguloption#S
\xetexkomonohanjafont#S
\xetexkomonohanjaoption#S
\xetexkosanshangulfont#S
\xetexkosanshanguloption#S
\xetexkosanshanjafont#S
\xetexkosanshanjaoption#S
\XKinterhangulbreak#S
\XKinterhanjabreak#S

# deprecated
\hangulnums#S
\hangulquotes#S
\hanjanums#S
\hanjaquotes#S
\latinnums#S
\latinquotes#S
\prevfontnums#S
\prevfontquotes#S
