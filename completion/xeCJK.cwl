# xeCJK package
# Darcy Hu <hot123tea123@gmail.com> 2016
#modified zepinglee 30 Jan 2021

#include:fontspec

## 3.1
\xeCJKsetup{options%keyvals}
#keyvals:\xeCJKsetup
xeCJKactive=#true,false
#
CJKspace=#true,false
CJKmath=#true,false
CJKglue=
CJKecglue=
xCJKecglue=
#
CheckSingle=#true,false
WindowPenalty=
PlainEquation=#true,false
NewLineCS=
NewLineCS+=
NewLineCS-=
EnvCS=
EnvCS+=
EnvCS-=
InlineEnv=
InlineEnv+=
InlineEnv-=
#
AutoFallback=#true,false
AutoFakeBold=
AutoFakeSlant=
EmboldenFactor=
SlantFactor=
#
PunctStyle=#quanjiao,banjiao,kaiming,hangbaobanjiao,CCT,plain
PunctFamily=
KaiMingPunct=
KaiMingPunct+=
KaiMingPunct-=
LongPunct=
LongPunct+=
LongPunct-=
MiddlePunct=
MiddlePunct+=
MiddlePunct-=
PunctWidth=
PunctBoundWidth=
AllowBreakBetweenPuncts=#true,false
RubberPunctSkip=#true,false,plus,minus
CheckFullRight=#true,false
NoBreakCS=
NoBreakCS+=
NoBreakCS-=
#
Verb=#true,false,env,env+
LoadFandol=#true,false
#endkeyvals

## 3.2
\setCJKmainfont{font name}
\setCJKmainfont{font name}[font features%keyvals]

\setCJKsansfont{font name}
\setCJKsansfont{font name}[font features%keyvals]

\setCJKmonofont{font name}
\setCJKmonofont{font name}[font features%keyvals]

\setCJKfamilyfont{family}{font name}
\setCJKfamilyfont{family}{font name}[font features%keyvals]

\CJKfamily{family}
\CJKfamily+{family}#*
\CJKfamily-{family}#*

\newCJKfontfamily{cmd}{font name}#d
\newCJKfontfamily{cmd}{font name}[font features%keyvals]#d
\newCJKfontfamily[family]{cmd}{font name}#*d
\newCJKfontfamily[family]{cmd}[font features%keyvals]{font name}#*d

\CJKfontspec{font name}
\CJKfontspec{font name}[font features%keyvals]

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
\setCJKmathfont{font name}[font features%keyvals]#*

\setCJKfallbackfamilyfont{family}{font name}#*
\setCJKfallbackfamilyfont{family}{font name}[font features%keyvals]#*

## 3.3
\xeCJKDeclareSubCJKBlock{block}{block range}#*
\xeCJKDeclareSubCJKBlock*{block}{block range}#*

\xeCJKCancelSubCJKBlock{blocks}#*
\xeCJKCancelSubCJKBlock*{blocks}#*

\xeCJKRestoreSubCJKBlock{blocks}#*
\xeCJKRestoreSubCJKBlock*{blocks}#*

## 3.4
\xeCJKDeclareCharClass{class}{class range}#*
\xeCJKDeclareCharClass*{class}{class range}#*

\xeCJKResetCharClass#*
\xeCJKResetPunctClass#*

\normalspacechars{char list}#*

## 3.5
\xeCJKsetwidth{punt list}{length}#*
\xeCJKsetwidth*{punt list}{length}#*

\xeCJKsetkern{first punct}{second punct}{length}#*

\xeCJKDeclarePunctStyle{style}{keyvals}#*
\xeCJKEditPunctStyle{style}{keyvals}#*

## 3.7
\xeCJKVerbAddon#*
\xeCJKOffVerbAddon#*

\xeCJKnobreak#*

\xeCJKShipoutHook#*

## font feature keyvals list
#keyvals:\setCJKmainfont,\setCJKsansfont,\setCJKmonofont,\setCJKfamilyfont,\newCJKfontfamily,\CJKfontspec,\defaultCJKfontfeatures,\addCJKfontfeatures,\setCJKmathfont,\setCJKfallbackfamilyfont
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
FallBack
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
Mapping=#fullwidth-stop,full-stop,han-trad,han-simp
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
