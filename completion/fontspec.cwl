# fontspec package
# nja/17 July 2007 for fontspec v1.14
# muzimuzhi/30 Aug 2019 for fontspec v2.7c
# Matthew Bertucci 21 Dec 2024 for v2.9e
# url: http://www.ctan.org/tex-archive/help/Catalogue/entries/fontspec.html

#keyvals:\usepackage/fontspec#c
math
no-math
config
no-config
quiet
silent
verbose
#endkeyvals

## Sec. I.4 Interaction with LaTeX2e and other packages
\liningnums{text}
\strong{text}
\begin{strongenv}
\end{strongenv}
\strongfontdeclare{font-switching list}
\strongreset

## Sec. II.1 Main commands
\setmainfont{font}
\setmainfont{font}[font features%keyvals]
\setmainfont[font features%keyvals]{font}#*
\setmainfont[font features%keyvals]{font}[font features%keyvals]#S
\setromanfont{font}
\setromanfont{font}[font features%keyvals]
\setromanfont[font features%keyvals]{font}#*
\setromanfont[font features%keyvals]{font}[font features%keyvals]#S
\setsansfont{font}
\setsansfont{font}[font features%keyvals]
\setsansfont[font features%keyvals]{font}#*
\setsansfont[font features%keyvals]{font}[font features%keyvals]#S
\setmonofont{font}
\setmonofont{font}[font features%keyvals]
\setmonofont[font features%keyvals]{font}#*
\setmonofont[font features%keyvals]{font}[font features%keyvals]#S

\newfontfamily{command}{font}#d
\newfontfamily{command}{font}[font features%keyvals]#d
\newfontfamily{command}[font features%keyvals]{font}#*d
\newfontfamily{command}[font features%keyvals]{font}[font features%keyvals]#Sd
\setfontfamily{command}{font}#d
\setfontfamily{command}{font}[font features%keyvals]#d
\setfontfamily{command}[font features%keyvals]{font}#*d
\setfontfamily{command}[font features%keyvals]{font}[font features%keyvals]#Sd
\renewfontfamily{command}{font}
\renewfontfamily{command}{font}[font features%keyvals]
\renewfontfamily{command}[font features%keyvals]{font}#*
\renewfontfamily{command}[font features%keyvals]{font}[font features%keyvals]#S
\providefontfamily{command}{font}#d
\providefontfamily{command}{font}[font features%keyvals]#d
\providefontfamily{command}[font features%keyvals]{font}#*d
\providefontfamily{command}[font features%keyvals]{font}[font features%keyvals]#Sd

\fontspec{font}
\fontspec{font}[font features%keyvals]
\fontspec[font features%keyvals]{font}#*
\fontspec[font features%keyvals]{font}[font features%keyvals]#S

## Sec. II.2 Font selection
\IfFontExistsTF{font name}{true}{false}

## Sec. II.4 Commands to select single font faces
\newfontface{command}{font}#d
\newfontface{command}{font}[font features%keyvals]#d
\newfontface{command}[font features%keyvals]{font}#*d
\newfontface{command}[font features%keyvals]{font}[font features%keyvals]#Sd
\setfontface{command}{font}#d
\setfontface{command}{font}[font features%keyvals]#d
\setfontface{command}[font features%keyvals]{font}#*d
\setfontface{command}[font features%keyvals]{font}[font features%keyvals]#Sd
\renewfontface{command}{font}
\renewfontface{command}{font}[font features%keyvals]
\renewfontface{command}[font features%keyvals]{font}#*
\renewfontface{command}[font features%keyvals]{font}[font features%keyvals]#S
\providefontface{command}{font}#d
\providefontface{command}{font}[font features%keyvals]#d
\providefontface{command}[font features%keyvals]{font}#*d
\providefontface{command}[font features%keyvals]{font}[font features%keyvals]#Sd

\setmathrm{font}
\setmathrm{font}[font features%keyvals]
\setmathrm[font features%keyvals]{font}#*
\setmathrm[font features%keyvals]{font}[font features%keyvals]#S
\setmathsf{font}
\setmathsf{font}[font features%keyvals]
\setmathsf[font features%keyvals]{font}#*
\setmathsf[font features%keyvals]{font}[font features%keyvals]#S
\setmathtt{font}
\setmathtt{font}[font features%keyvals]
\setmathtt[font features%keyvals]{font}#*
\setmathtt[font features%keyvals]{font}[font features%keyvals]#S
\setboldmathrm{font}
\setboldmathrm{font}[font features%keyvals]
\setboldmathrm[font features%keyvals]{font}#*
\setboldmathrm[font features%keyvals]{font}[font features%keyvals]#S

## Sec. III.1 Default settings
\defaultfontfeatures{font features%keyvals}
\defaultfontfeatures[font name list]{font features%keyvals}
\defaultfontfeatures+{font features%keyvals}
\defaultfontfeatures+[font name list]{font features%keyvals}

## Sec. III.2 Working with the currently selected features
\IfFontFeatureActiveTF{font feature}{true code}{false code}
\addfontfeatures{font features%keyvals}
\addfontfeature{font features%keyvals}#*

## Sec. V Commands for accents and symbols ('encodings')
\EncodingCommand{command}[num][default]{code}#*d
\EncodingAccent{command}{code}#*d
\EncodingSymbol{command}{code}#*d
\EncodingComposite{command}{letter}{slot}#*d
\EncodingCompositeCommand(command){letter}{code}#*d
\UndeclareSymbol{command}
\UndeclareAccent{command}
\UndeclareCommand{command}
\UndeclareComposite{command}{letter}

## Sec. VIII Customisation and programming interface
\newAATfeature{feature}{option}{feature code}{selector code}
\newopentypefeature{feature}{option}{feature tag}
\newfontfeature{name%specialDef}{input string}#s#%fontspecfeature
\newfontscript{fontspec name}{OpenType tag list}
\newfontlanguage{fontspec name}{OpenType tag list}
\aliasfontfeature{existing name%specialDef}{new name}#s#%fontspecfeature
\aliasfontfeatureoption{font feature}{existing name}{new name}

## common keyvals list, 
## both commands and keys are in alphabetic order, except for engine specific keys
#keyvals:\addfontfeature,\addfontfeatures,\defaultfontfeatures,\fontspec,\newfontface,\newfontfamily,\providefontface,\providefontfamily,\renewfontface,\renewfontfamily,\setboldmathrm,\setfontface,\setfontfamily,\setmainfont,\setmathrm,\setmathsf,\setmathtt,\setmonofont,\setromanfont,\setsansfont
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

# not documented
\cyrillicencoding#*
\latinencoding#*
\UTFencname#*
\emfontdeclare{font-switching list}#*
\FontspecSetCheckBoolFalse#*
\FontspecSetCheckBoolTrue#*
\scitdefault#*
\scsldefault#*
\scswdefault#*

# from tuenc.def
\UnicodeEncodingName#*
\UnicodeFontTeXLigatures#*
\UnicodeFontFile{arg1}{arg2}#*
\UnicodeFontName{arg1}{arg2}#*
\DeclareUnicodeAccent{command}{encoding}{char code}#*d
\DeclareUnicodeCommand{command}{slot}#*d
\DeclareUnicodeComposite{command}{letter}{definition}#*d
\DeclareUnicodeSymbol{command}{definition}#*d
\textquotedbl#n
\guillemetleft#n
\guillemotleft#*n
\guillemetright#n
\guillemotright#*n
\DH#n
\TH#n
\dh#n
\th#n
\DJ#n
\dj#n
\NG#n
\ng#n
\quotesinglbase#n
\quotedblbase#n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#*n
\hwithstroke#*n
\k{arg}#n

# expl3 interface
\fontspec_font_if_exist:nF {%<⟨font name⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_font_if_exist:nT {%<⟨font name⟩%>} {%<⟨true code⟩%>}#/%expl3
\fontspec_font_if_exist:nTF {%<⟨font name⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_gset_family:Nnn %<⟨family⟩%> {%<⟨features⟩%>} {%<⟨font name⟩%>}#/%expl3
\fontspec_gset_fontface:NNnn %<⟨face⟩%> %<⟨family⟩%> {%<⟨features⟩%>} {%<⟨font name⟩%>}#/%expl3
\fontspec_if_aat_feature:nnF {%<⟨feature⟩%>} {%<⟨option⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_aat_feature:nnT {%<⟨feature⟩%>} {%<⟨option⟩%>} {%<⟨true code⟩%>}#/%expl3
\fontspec_if_aat_feature:nnTF {%<⟨feature⟩%>} {%<⟨option⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_current_feature:nF {%<⟨feature tag⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_current_feature:nT {%<⟨feature tag⟩%>} {%<⟨true code⟩%>}#/%expl3
\fontspec_if_current_feature:nTF {%<⟨feature tag⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_current_language:nF {%<⟨lang tag⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_current_language:nT {%<⟨lang tag⟩%>} {%<⟨true code⟩%>}#/%expl3
\fontspec_if_current_language:nTF {%<⟨lang tag⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_current_script:nF {%<⟨script tag⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_current_script:nT {%<⟨script tag⟩%>} {%<⟨true code⟩%>}#/%expl3
\fontspec_if_current_script:nTF {%<⟨script tag⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_feature:nF {%<⟨feature tag⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_feature:nnnF {%<⟨script tag⟩%>} {%<⟨lang tag⟩%>} {%<⟨feature tag⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_feature:nnnT {%<⟨script tag⟩%>} {%<⟨lang tag⟩%>} {%<⟨feature tag⟩%>} {%<⟨true code⟩%>}#/%expl3
\fontspec_if_feature:nnnTF {%<⟨script tag⟩%>} {%<⟨lang tag⟩%>} {%<⟨feature tag⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_feature:nT {%<⟨feature tag⟩%>} {%<⟨true code⟩%>}#/%expl3
\fontspec_if_feature:nTF {%<⟨feature tag⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_fontspec_font:F {%<⟨false code⟩%>}#/%expl3
\fontspec_if_fontspec_font:T {%<⟨true code⟩%>}#/%expl3
\fontspec_if_fontspec_font:TF {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_language:nF {%<⟨lang tag⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_language:nnF {%<⟨script tag⟩%>} {%<⟨lang tag⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_language:nnT {%<⟨script tag⟩%>} {%<⟨lang tag⟩%>} {%<⟨true code⟩%>}#/%expl3
\fontspec_if_language:nnTF {%<⟨script tag⟩%>} {%<⟨lang tag⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_language:nT {%<⟨lang tag⟩%>} {%<⟨true code⟩%>}#/%expl3
\fontspec_if_language:nTF {%<⟨lang tag⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_opentype:F {%<⟨false code⟩%>}#/%expl3
\fontspec_if_opentype:T {%<⟨true code⟩%>}#/%expl3
\fontspec_if_opentype:TF {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_script:nF {%<⟨script tag⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_script:nT {%<⟨script tag⟩%>} {%<⟨true code⟩%>}#/%expl3
\fontspec_if_script:nTF {%<⟨script tag⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_if_small_caps:F {%<⟨false code⟩%>}#/%expl3
\fontspec_if_small_caps:T {%<⟨true code⟩%>}#/%expl3
\fontspec_if_small_caps:TF {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\fontspec_set_family:Nnn %<⟨family⟩%> {%<⟨features⟩%>} {%<⟨font name⟩%>}#/%expl3
\fontspec_set_fontface:NNnn %<⟨face⟩%> %<⟨family⟩%> {%<⟨features⟩%>} {%<⟨font name⟩%>}#/%expl3
\g_fontspec_encoding_tl#/%expl3
\l_fontspec_family_tl#/%expl3
\l_fontspec_font#/%expl3