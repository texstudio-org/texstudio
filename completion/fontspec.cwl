# fontspec package
# nja/17 July 2007 for fontspec v1.14
# muzimuzhi/30 Aug 2019 for fontspec v2.7c
# url: http://www.ctan.org/tex-archive/help/Catalogue/entries/fontspec.html

## Sec. I.4 Interaction with LaTeX2e and other pacakges
\liningnums{nums}
\emfontdeclare{font-switching list}
\emreset
\strong{text}
\begin{strongenv}
\end{strongenv}
\strongfontdeclare{font-switching list}
\strongreset

## Sec. II.1 Main commands
\setmainfont{font}
\setmainfont[font features]{font}*
\setmainfont{font}[font features%keyvals]
\setmainfont[font features]{font}[font features%keyvals]#*
\setromanfont{font}
\setromanfont[font features]{font}*
\setromanfont{font}[font features%keyvals]
\setromanfont[font features]{font}[font features%keyvals]#*
\setsansfont{font}
\setsansfont[font features]{font}*
\setsansfont{font}[font features%keyvals]
\setsansfont[font features]{font}[font features%keyvals]#*
\setmonofont{font}
\setmonofont[font features]{font}*
\setmonofont{font}[font features%keyvals]
\setmonofont[font features]{font}[font features%keyvals]#*

\newfontfamily{cmd}{font}#d
\newfontfamily{cmd}[font features]{font}#*d
\newfontfamily{cmd}{font}[font features%keyvals]#d
\newfontfamily{cmd}[font features]{font}[font features%keyvals]#*d
\setfontfamily{cmd}{font}#d
\setfontfamily{cmd}[font features]{font}#*d
\setfontfamily{cmd}{font}[font features%keyvals]#d
\setfontfamily{cmd}[font features]{font}[font features%keyvals]#*d
\renewfontfamily{cmd}{font}#d
\renewfontfamily{cmd}[font features]{font}#*d
\renewfontfamily{cmd}{font}[font features%keyvals]#d
\renewfontfamily{cmd}[font features]{font}[font features%keyvals]#*d
\providefontfamily{cmd}{font}#d
\providefontfamily{cmd}[font features]{font}#*d
\providefontfamily{cmd}{font}[font features%keyvals]#d
\providefontfamily{cmd}[font features]{font}[font features%keyvals]#*d

\fontspec{font}
\fontspec[font features]{font}#*
\fontspec{font}[font features%keyvals]
\fontspec[font features]{font}[font features%keyvals]#*

## Sec. II.2 Font selection
\IfFontExistsTF{font name}{true}{false}

## Sec. II.4 Commands to select single font faces
\newfontface{cmd}{font}#d
\newfontface{cmd}[font features]{font}#*d
\newfontface{cmd}{font}[font features%keyvals]#d
\newfontface{cmd}[font features]{font}[font features%keyvals]#*d
\setfontface{cmd}{font}#d
\setfontface{cmd}[font features]{font}#*d
\setfontface{cmd}{font}[font features%keyvals]#d
\setfontface{cmd}[font features]{font}[font features%keyvals]#*d
\renewfontface{cmd}{font}#d
\renewfontface{cmd}[font features]{font}#*d
\renewfontface{cmd}{font}[font features%keyvals]#d
\renewfontface{cmd}[font features]{font}[font features%keyvals]#*d
\providefontface{cmd}{font}#d
\providefontface{cmd}[font features]{font}#*d
\providefontface{cmd}{font}[font features%keyvals]#d
\providefontface{cmd}[font features]{font}[font features%keyvals]#*d

\setmathrm{font}
\setmathrm[font features]{font}#*
\setmathrm{font}[font features%keyvals]
\setmathrm[font features]{font}[font features%keyvals]#*
\setmathsf{font}
\setmathsf[font features]{font}#*
\setmathsf{font}[font features%keyvals]
\setmathsf[font features]{font}[font features%keyvals]#*
\setmathtt{font}
\setmathtt[font features]{font}#*
\setmathtt{font}[font features%keyvals]
\setmathtt[font features]{font}[font features%keyvals]#*
\setboldmathrm{font}
\setboldmathrm[font features]{font}#*
\setboldmathrm{font}[font features%keyvals]
\setboldmathrm[font features]{font}[font features%keyvals]#*

## Sec. III.1 Default settings
\defaultfontfeatures{font features%keyvals}
\defaultfontfeatures[font name list]{font features%keyvals}
\defaultfontfeatures+{font features%keyvals}
\defaultfontfeatures+[font name list]{font features%keyvals}

## Sec. III.2 Working with the currently selected features
\IfFontFeatureActiveTF{font feature}{true}{false}
\addfontfeatures{font features%keyvals}
\addfontfeature{font features%keyvals}

## Sec. V Commands for accents and symbols ('encodings')
\EncodingCommand{cmd}[num][default]{code}#*d
\EncodingAccent{cmd}{code}#*d
\EncodingSymbol{cmd}{code}#*d
\EncodingComposite{cmd}{letter}{slot}#*d
\EncodingCompositeCommand(cmd){letter}{code}#*d
\UndeclareSymbol{cmd}
\UndeclareAccent{cmd}
\UndeclareCommand{cmd}
\UndeclareComposite{cmd}{letter}

## Sec. VIII Customisation and programming interface
\newAATfeature{feature}{option}{feature code}{selector code}
\newopentypefeature{feature}{option}{feature tag}
\newfontfeature{name}{input string}
\newfontscript{fontspec name}{OpenType tag list}
\newfontlanguage{fontspec name}{OpenType tag list}
\aliasfontfeature{existing name}{new name}
\aliasfontfeatureoption{font feature}{existing name}{new name}

## common keyvals list, 
## both cmds and keys are in alphabetic order, except for engine specific keys
#keyvals:\addfontfeature,\addfontfeatures,\defaultfontfeatures,\fontspec,\newfontface,\newfontfamily,\providefontface,\providefontfamily,\renewfontface,\renewfontfamily,\setboldmathrm,\setfontface,\setfontfamily,\setmainfont,\setmathrm,\setmathsf,\setmathtt,\setmonofont,\setromanfont,\setsansfont
Alternate
Annotation
AutoFakeBold
AutoFakeSlant
BoldFeatures
BoldFont
BoldItalicFeatures
BoldItalicFont
BoldSlantedFeatures
BoldSlantedFont
CJKShape
CharacterVariant
CharacterWidth
Color
Colour
Contextuals
Diacritics
Extension
ExternalLocation
FakeBold
FakeSlant
FakeStretch
Font
FontFace={series}{shape}{font name}
Fractions
HyphenChar
IgnoreFontspecFile
ItalicFeatures
ItalicFont
Kerning
Language
LetterSpace
Letters
Ligatures
LocalForms
NFSSFamily
Numbers
OpticalSize
Ornament
PunctuationSpace
RawFeature
Scale
ScaleAgain
ScientificInferior
Script
Size
SizeFeatures
SlantedFeatures
SlantedFont
SmallCapsFeatures
SmallCapsFont
Style
StylisticAlternates
StylisticSet
UprightFeatures
UprightFont
Variant
Vertical
VerticalPosition
WordSpace
Mapping=%<xetex-only feature%>
Renderer=%<xetex-only feature%>
WordSpace=
#endkeyvals
