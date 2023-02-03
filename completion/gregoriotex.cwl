# gregoriotex package
# Matthew Bertucci 2022/05/07 for v6.0.0

#include:iftex
#include:xcolor
#include:luacolor
#include:kvoptions
#include:graphicx
#include:luatexbase
#include:luaotfload
#include:luamplib
#include:xstring

#keyvals:\usepackage/gregoriotex#c
debug
debug={%<types%>}
nevercompile
autocompile
forcecompile
allowdeprecated#true,false
#endkeyvals

# Dependency Tree (not including .sty files):
# gregoriotex-main.tex
# ├── gregoriotex-common.tex
# ├── gregoriotex-spaces.tex
# │   └── gregoriotex-gsp-default.tex
# ├── gregoriotex-chars.tex
# ├── gregoriotex-signs.tex
# ├── gregoriotex-syllable.tex
# ├── gregoriotex-symbols.tex
# └── gregoriotex-nabc.tex

# from gregoriotex.sty
grebackgroundcolor#B
gregoriocolor#B
\GreItalic{text}#*
\GreSmallCaps{text}#*
\GreBold{text}#*
\GreTypewriter{text}#*
\GreUnderline{text}#*
\GreColored{text}#*
\gresetlinecolor{color}

# from gregoriotex-main.tex
\GreScoreId#*
\GregorioTeXAPIVersion{version}#*
\GreNewLine#*
\GreNewParLine#*
\GreFinalNewLine#*
\greillumination{code}
\greannotation{text}
\greannotation[alignment%keyvals]{text}
#keyvals:\greannotation
c
l
r
#endkeyvals
\gresetannotationby{choice%keyvals}
#keyvals:\gresetannotationby
topline
bottomline
#endkeyvals
\gresetannotationvalign{choice%keyvals}
#keyvals:\gresetannotationvalign
top
baseline
bottom
#endkeyvals
\GreMode{arg1}{arg2}{arg3}#*
\gresetmodenumbersystem{choice%keyvals}
#keyvals:\gresetmodenumbersystem
roman-minuscule
roman-majuscule
arabic
#endkeyvals
\GreModeNumber{integer 1-8}#*
\GreAnnotationLines{line1%text}{line2%text}#*
\grecommentary{text}
\grecommentary[distance]{text}
\gresetabovelinestext{choice%keyvals}
#keyvals:\gresetabovelinestext,\gresetlines,\gresettranslation,\gresetclef,\gresetcustosalteration,\gresetlinesbehinddottedbar,\gresetlinesbehindpunctumcavum,\gresetlinesbehindalteration,\gresetlyrics,\gresetnotes,\gresetnabc
visible
invisible
#endkeyvals
\GreSetTextAboveLines{text}#*
\GreSetNabcAboveLines{Nabc names}#*
\gresetlines{choice%keyvals}
\GreFuseTwo{glyph1}{glyph2}#*
\GreFuse#*
\grechangeglyph{glyph name}{font name}{glyph or variant name}
\grechangecavumglyph{glyph name}{font name}{glyph or variant name}{hollow font name}{hollow glyph or variant name}
\greresetglyph{glyph name}
\greresetcavumglyph{glyph name}
\gresettranslationcentering{choice%keyvals}
#keyvals:\gresettranslationcentering
left
center
#endkeyvals
\gresetbreakintranslation{choice%keyvals}
#keyvals:\gresetbreakintranslation,\gresetbreakineuouae,\gresetgabcforcecenters
allow
prohibit
#endkeyvals
\gresettranslation{choice%keyvals}
\GreWriteTranslation{text}#*
\GreWriteTranslationWithCenterBeginning{text}#*
\GreTranslationCenterEnd#*
\gresetlastline{choice%keyvals}
#keyvals:\gresetlastline,\gresetbreakbeforeeuouae
justified
ragged
#endkeyvals
\gresetlineheightexpansion{choice%keyvals}
#keyvals:\gresetlineheightexpansion
variable
uniform
#endkeyvals
\gresetnoteadditionalspacelinestext{choice%keyvals}
#keyvals:\gresetnoteadditionalspacelinestext
automatic
manual
#endkeyvals
\GreCPDivisioMaiorDottedBackingFive#S
\GreCPDivisioMaiorDottedBackingFour#S
\GreCPDivisioMaiorDottedBackingThree#S
\GreCPDivisioMaiorDottedBackingTwo#S
\GreCPDivisioMaiorDottedFive#S
\GreCPDivisioMaiorDottedFour#S
\GreCPDivisioMaiorDottedThree#S
\GreCPDivisioMaiorDottedTwo#S
\GreCPDivisioMaiorFive#S
\GreCPDivisioMaiorFour#S
\GreCPDivisioMaiorThree#S
\GreCPDivisioMaiorTwo#S
\GreCPDivisioMinimaFive#S
\GreCPDivisioMinimaFour#S
\GreCPDivisioMinimaParenFive#S
\GreCPDivisioMinimaParenFour#S
\GreCPDivisioMinimaParenSix#S
\GreCPDivisioMinimaParenThree#S
\GreCPDivisioMinimaParenTwo#S
\GreCPDivisioMinimaSix#S
\GreCPDivisioMinimaThree#S
\GreCPDivisioMinimaTwo#S
\GreCPDivisioMinimisFive#S
\GreCPDivisioMinimisFour#S
\GreCPDivisioMinimisSix#S
\GreCPDivisioMinimisThree#S
\GreCPDivisioMinimisTwo#S
\GreCPDivisioMinorFive#S
\GreCPDivisioMinorFour#S
\GreCPDivisioMinorThree#S
\GreCPDivisioMinorTwo#S
\GreCPVirgulaFive#S
\GreCPVirgulaFour#S
\GreCPVirgulaParenFive#S
\GreCPVirgulaParenFour#S
\GreCPVirgulaParenSix#S
\GreCPVirgulaParenThree#S
\GreCPVirgulaParenTwo#S
\GreCPVirgulaSix#S
\GreCPVirgulaThree#S
\GreCPVirgulaTwo#S
\GreBeginScore{id}{high height}{low height}{translation:0 or 1}{abovelines:0 or 1}{filename}{staff lines}{before code}#*
\GreEndScore#*
\GreLastOfLine#*
\GreLastOfScore#*
\gresetbolshifts{choice%keyvals}
#keyvals:\gresetbolshifts,\greseteolshifts
enable
disable
#endkeyvals
\greseteolshifts{choice%keyvals}
\GreSuppressEolCustos#*
\greseteolcustos{choice%keyvals}
#keyvals:\greseteolcustos
auto
manual
#endkeyvals
\GreResetEolCustos#*
\greseteolcustosbeforeeuouae{choice%keyvals}
#keyvals:\greseteolcustosbeforeeuouae
suppressed
auto
#endkeyvals
\gresetbreakbeforeeuouae{choice%keyvals}
\GreAdHocSpaceEndOfElement{factor}{0 or 1}{number of notes}#*
\GreEndOfElement{integer}{0 or 1}{number of notes}#*
\GreEndOfGlyph{integer}#*
\GreBeginNLBArea{in neumes: 0 or 1}{from translation centering: 0 or 1}#*
\GreEndNLBArea{integer}{0 or 1}#*
\gresetbreakineuouae{choice%keyvals}
\GreBeginEUOUAE{integer}#*
\GreEndEUOUAE{integer}#*
\gretilde
\gresetgregoriofont{font name}
\gresetgregoriofont[alt font]{font name}
\gresetgregoriofontscaled{font name}{scale}
\gresetgregoriofontscaled[alt font]{font name}{scale}
\GreCPVirgaReversaAscendensOnDLine{code}#*
\greloadholehollowfonts{choice%keyvals}
#keyvals:\greloadholehollowfonts
true
false
#endkeyvals
\grechangestyle{element%keyvals}{code}
\grechangestyle{element%keyvals}{on code}[off code]
#keyvals:\grechangestyle
abovelinestext
additionalstafflines
annotation
commentary
elision
firstsyllable
firstsyllableinitial
firstword
highchoralsign
initial
lowchoralsign
modedifferentia
modeline
modemodifier
nabc
normalstafflines
translation
#endkeyvals
\grechangestaffsize{integer}
\gresetheadercapture{gabc header name}{csname}{options%keyvals}
#keyvals:\gresetheadercapture
name
string
#endkeyvals
\GreHeader{header name}{header value}#*
\gresetgregpath{file path%file}
\gresetcompilegabc{choice%keyvals}
#keyvals:\gresetcompilegabc
force
auto
never
#endkeyvals
\gregorioscore{file}#i
\gregorioscore[option%keyvals]{file}#i
#keyvals:\gregorioscore
n
a
f
#endkeyvals
\gabcsnippet{gabc}
\GreHyph#*
\greseteolhyphen{choice%keyvals}
#keyvals:\greseteolhyphen
normal
zero
#endkeyvals
\gresethyphen{choice%keyvals}
#keyvals:\gresethyphen,\gresetemptyfirstsyllablehyphen
force
auto
#endkeyvals
\GreBeginHeaders#*
\grebeforeheaders{code}
\GreEndHeaders#*
\greafterheaders{code}

# from gregoriotex-common.tex
# no user commands

# from gregoriotex-spaces.tex
\GreForceBreak#*
\GreNoBreak#*
\grechangestafflinethickness{integer}
\grebolshiftcleftype{choice%keyvals}
#keyvals:\grebolshiftcleftype
largest
current
#endkeyvals
\grelocalbolshiftcleftype
#keyvals:\grelocalbolshiftcleftype
largest
current
f
c
fb
cb
#endkeyvals
\GreProtrusionFactor{character}#*
\gresetprotrusionfactor{choice%keyvals}{factor}
#keyvals:\gresetprotrusionfactor
,
;
:
.
eolhyphen
default
#endkeyvals
\GreProtrusion{factor}{content}#*
\gresetledgerlineheuristic{choice%keyvals}
#keyvals:\gresetledgerlineheuristic
enable
disable
#endkeyvals
\GreSupposeHighLedgerLine#*
\GreSupposeLowLedgerLine#*
\grechangedim{dim name}{distance}{choice%keyvals}
#keyvals:\grechangedim,\grechangenextscorelinedim
fixed
scalable
inherited
#endkeyvals
\grechangecount{count name%keyvals}{value}
#keyvals:\grechangecount,\grechangenextscorelinecount
# counts
additionaltopspacethreshold
additionaltopspacealtthreshold
additionaltopspacenabcthreshold
noteadditionalspacelinestextthreshold
# penalties
brokenpenalty
clubpenalty
widowpenalty
emergencystretch
endafterbarpenalty
endafterbaraltpenalty
endofelementpenalty
endofsyllablepenalty
endofwordpenalty
hyphenpenalty
nobreakpenalty
newlinepenalty
finalpenalty
looseness
tolerance
pretolerance
#endkeyvals
\grescaledim{dim name}{choice%keyvals}
#keyvals:\grescaledim#c
yes
true
on
scalable
#endkeyvals
\grechangenextscorelinedim{line numbers}{dim name}{distance}{choice%keyvals}
\grechangenextscorelinecount{line numbers}{count name%keyvals}{value}
\greconffactor
\greloadspaceconf{config file id}

# from gregoriotex-gsp-default.tex
# no user commands

# from gregoriotex-chars.tex
\gresetglyphstyle{choice%keyvals}
#keyvals:\gresetglyphstyle
default
medicaea
hufnagel
mensural
#endkeyvals

# from gregoriotex-signs.tex
\grebarbracewidth
\greprintsigns{choice%keyvals}{enable|disable}
#keyvals:\greprintsigns
vepisema
hepisema
mora
all
#endkeyvals
\GreDiscretionary{integer}{first arg}{third arg}#*
\gresetclef{choice%keyvals}
\GreSetLinesClef{type}{line}{0 or 1}{height}{secondary type}{secondary line}{secondary height}#*
\GreSetLargestClef{type}{line}{height}{secondary type}{secondary line}{secondary height}#*
\GreInitialClefPosition{primary line}{secondary line}#*
\GreSetInitialClef{type}{line}{height}{secondary type}{secondary line}{secondary height}{0 or 1}#*
\GreChangeClef{type}{line}{0 or 1}{height}{secondary type}{secondary line}{secondary height}#*
\GreCustos{height}{choice%keyvals}#*
\GreFinalCustos{height}{choice%keyvals}#*
\GreNextCustos{height}{choice%keyvals}#*
#keyvals:\GreCustos,\GreFinalCustos,\GreNextCustos
Flat
Natural
Sharp
#endkeyvals
\gresetcustosalteration{choice%keyvals}
\gresetbracerendering{metapost|font}
\gresetbracerendering[option%keyvals]{metapost|font}
#keyvals:\gresetbracerendering
brace
underbrace
curlybrace
barbrace
#endkeyvals
\GreOverCurlyBrace{width}{vshift}{hshift}{0 or 1}{0 or 1}#*
\GreOverBrace{width}{vshift}{hshift}{0 or 1}#*
\GreUnderBrace{width}{vshift}{hshift}{0 or 1}#*
\grebracemetapostpreamble{width}#*
\greslurheight#*
\GreSlur{height}{integer}{integer}{hdimen}{vdimen}{end height}#*
\GreVarBraceLength{id}#*
\GreVarBraceSavePos{id}{integer}{integer}#*
\GrePunctumMora{height}{integer}{0 or 1}{0 or 1}#*
\GreAugmentumDuplex{height1}{height2}{0 or 1}#*
\GreLowChoralSign{height}{sign}{0 or 1}#*
\GreHighChoralSign{height}{sign}{0 or 1}#*
\GreVEpisema{height}{type}#*
\GreBarBrace{type}#*
\GreBarVEpisema{type}#*
\GreAccentus{height}{type}#*
\GreSemicirculus{height}{type}#*
\GreCirculus{height}{type}#*
\GreReversedAccentus{height}{type}#*
\GreReversedSemicirculus{height}{type}#*
\GreMusicaFictaFlat{height}{type}#*
\GreMusicaFictaNatural{height}{type}#*
\GreMusicaFictaSharp{height}{type}#*
\GreAdditionalLine{type}{ambitus}{episema}#*
\GreDrawAdditionalLine{0 or 1}{distance}{integer}{distance}{integer}{distance}#*
\GreHEpisema{height}{type}{ambitus}{integer}{choice}{integer}{code}{nudge}{integer}#*
\gresethepisema{choice%keyvals}
#keyvals:\gresethepisema
bridge
break
#endkeyvals
\GreHEpisemaBridge{height}{0 or 1}{integer}{code}{nudge}{integer}#*
\gresetlinesbehinddottedbar{choice%keyvals}
\GreInVirgula{0 or 1}{code}{0 or 1}#*
\GreVirgula{0 or 1}{code}{0 or 1}#*
\GreInVirgulaHigh{0 or 1}{code}{0 or 1}#*
\GreVirgulaHigh{0 or 1}{code}{0 or 1}#*
\GreInVirgulaParen{0 or 1}{code}{0 or 1}#*
\GreVirgulaParen{0 or 1}{code}{0 or 1}#*
\GreInVirgulaParenHigh{0 or 1}{code}{0 or 1}#*
\GreVirgulaParenHigh{0 or 1}{code}{0 or 1}#*
\GreInDivisioMinimis{0 or 1}{code}{0 or 1}#*
\GreDivisioMinimis{0 or 1}{code}{0 or 1}#*
\GreInDivisioMinimisHigh{0 or 1}{code}{0 or 1}#*
\GreDivisioMinimisHigh{0 or 1}{code}{0 or 1}#*
\GreInDivisioMinima{0 or 1}{code}{0 or 1}#*
\GreDivisioMinima{0 or 1}{code}{0 or 1}#*
\GreInDivisioMinimaHigh{0 or 1}{code}{0 or 1}#*
\GreDivisioMinimaHigh{0 or 1}{code}{0 or 1}#*
\GreInDivisioMinimaParen{0 or 1}{code}{0 or 1}#*
\GreDivisioMinimaParen{0 or 1}{code}{0 or 1}#*
\GreInDivisioMinimaParenHigh{0 or 1}{code}{0 or 1}#*
\GreDivisioMinimaParenHigh{0 or 1}{code}{0 or 1}#*
\GreInDivisioMinor{0 or 1}{code}#*
\GreDivisioMinor{0 or 1}{code}#*
\GreInDivisioMaior{0 or 1}{code}#*
\GreDivisioMaior{0 or 1}{code}#*
\GreInDivisioMaiorDotted{0 or 1}{code}#*
\GreDivisioMaiorDotted{0 or 1}{code}#*
\GreDominica{type}{0 or 1}{code}#*
\GreInDominica{type}{0 or 1}{code}#*
\GreInDivisioFinalis{0 or 1}{code}#*
\GreDivisioFinalis{0 or 1}{code}#*
\gresetshiftaftermora{choice%keyvals}
#keyvals:\gresetshiftaftermora
always
notesonly
barsonly
notextonly
insideonly
never
#endkeyvals
\GreFinalDivisioFinalis{0 or 1}#*
\GreFinalDivisioMaior{0 or 1}#*
\gresetlinesbehindpunctumcavum{choice%keyvals}
\gresetlinesbehindalteration{choice%keyvals}
\GreFlat{height}{0 or 1}{before code}{after code}{info string}#*
\GreFlatParen{height}{0 or 1}{before code}{after code}{info string}#*
\GreNatural{height}{0 or 1}{before code}{after code}{info string}#*
\GreNaturalParen{height}{0 or 1}{before code}{after code}{info string}#*
\GreSharp{height}{0 or 1}{before code}{after code}{info string}#*
\GreSharpParen{height}{0 or 1}{before code}{after code}{info string}#*
\gresetpunctumcavum{choice%keyvals}
#keyvals:\gresetpunctumcavum
alternate
normal
#endkeyvals
\GreCavum{glyph name}#*
\GreBracket{0 or 1}{lowest height}{highest height}{info string}#*

# from gregoriotex-syllable.tex
\gresetpointandclick{choice%keyvals}
#keyvals:\gresetpointandclick
on
off
#endkeyvals
\GreGlyphHeights{high height}{low height}#*
\GreGlyph{char}{glyphnum}{code}{integer}{before code}{after code}{info string}#*
\gresetlyrics{choice%keyvals}
\gresetnotes{choice%keyvals}
\GreFirstWord{text}#*
\GreFirstSyllable{text}#*
\GreFirstSyllableInitial{letter}#*
\GreElision{text}#*
\GreSetFixedTextFormat{integer}#*
\GreSetFixedNextTextFormat{integer}#*
\GreUnstyled{text}#*
\GreGABCForceCenters
\GreGABCNextForceCenters
\gresetgabcforcecenters{choice%keyvals}
\GreSetThisSyllable{first letters}{middle letters}{end letters}{first letter}{all but first letters}#*
\GreSetNextSyllable{first letters}{middle letters}{end letters}{first letter}{all but first letters}#*
\gresetlyriccentering{choice%keyvals}
#keyvals:\gresetlyriccentering
vowel
syllable
firstletter
#endkeyvals
\gresetclivisalignment{choice%keyvals}
#keyvals:\gresetclivisalignment
always
never
special
#endkeyvals
\gresetemptyfirstsyllablehyphen{choice%keyvals}
\GreForceHyphen#*
\GreEmptyFirstSyllableHyphen#*
\gresetunbreakablesyllablenotes{int1}{int2}{int3}
\GreSyllableNoteCount{integer}#*
\gresetsyllablerewriting{choice%keyvals}
#keyvals:\gresetsyllablerewriting
auto
off
#endkeyvals
\GreClearSyllableText#*
\GreSyllable{macro}{}{style cs}{0 or 1}{macros}{info string}{integer pair}{other macros}{notes}#*
\GreNextSyllableBeginsEUOUAE{id}{0 or 1}#*
\GreLastSyllableBeforeEUOUAE{id}{0 or 1}#*
\gresetbarspacing{choice%keyvals}
#keyvals:\gresetbarspacing
new
old
#endkeyvals
\GreBarSyllable{macro}{}{style cs}{0 or 1}{macros}{info string}{integer pair}{other macros}{bar line}#*
\GreNoNoteSyllable{macro}{}{style cs}{0 or 1}{macros}{info string}{integer pair}{other macros}{bar line}#*
\gresetinitiallines{number}
\GreSetFirstSyllableText{initial}{first letter}{other letters}{sep initial parts}{nosep initial parts}{extra macros}#*
\GreSetNoFirstSyllableText#*
\GreUpcomingNewLineForcesCustos{0 or 1}#*
\GreScoreOpening{after init code}{after notes code}{before init code}{syllable cs}{first syllable code}#*

# from gregoriotex-symbols.tex
\gredefsymbol{csname}{font name}{glyph name or code point}
\gredefsizedsymbol{csname}{font name}{glyph name or code point}
\greABar{size}#*
\greRBar{size}#*
\greVBar{size}#*
\greABarSlant{size}#*
\greRBarSlant{size}#*
\greVBarSlant{size}#*
\greABarSC{size}#*
\greRBarSC{size}#*
\greVBarSC{size}#*
\greABarSmall{size}#*
\greRBarSmall{size}#*
\greVBarSmall{size}#*
\greABarSmallSlant{size}#*
\greRBarSmallSlant{size}#*
\greVBarSmallSlant{size}#*
\greABarSmallSC{size}#*
\greRBarSmallSC{size}#*
\greVBarSmallSC{size}#*
\greABarCaption{size}#*
\greRBarCaption{size}#*
\greVBarCaption{size}#*
\greABarCaptionSlant{size}#*
\greRBarCaptionSlant{size}#*
\greVBarCaptionSlant{size}#*
\greABarCaptionSC{size}#*
\greRBarCaptionSC{size}#*
\greVBarCaptionSC{size}#*
\greABarAlt{size}#*
\greRBarAlt{size}#*
\greVBarAlt{size}#*
\grebarredsymbol{definition}{symbol}{size}{hshift}{vshift}
\gredefbarredsymbol{csname}{definition}{symbol}{size}{hshift}{vshift}
\gresimpledefbarredsymbol{A, R, or V}{left shift}
\ABar#*
\VBar#*
\RBar#*
\grelatexsimpledefbarredsymbol{A, R, or V}{upmedium shift}{itmedium shift}{upbold shift}{itbold shift}
\gothRbar
\gothVbar
\GreDagger#*
\grecross
\grealtcross
\greheightstar
\gresixstar
\GreStar#*
\greLineOne{size}#*
\greLineTwo{size}#*
\greLineThree{size}#*
\greLineFour{size}#*
\greLineFive{size}#*
\greseparator{integer 1-5}{size}
\greOrnamentOne{size}#*
\greOrnamentTwo{size}#*
\greornamentation{integer 1-2}{size}
\gresetspecial{text%plain}{code}
\greunsetspecial{text%plain}
\GreSpecial{text%plain}#*

# from gregoriotex-nabc.tex
\gresetnabcfont{font name%keyvals}{size}
#keyvals:\gresetnabcfont
gregall
grelaon
gresgmodern
#endkeyvals
\GreNABCChar{nabc code}#*
\gresetnabc{nabc voice number}{choice%keyvals}
\GreNABCNeumes{line}{nabc code}{high pitch}{low pitch}#*
\GreScoreNABCLines{number}#*






