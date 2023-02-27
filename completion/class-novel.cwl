# novel class
# Matthew Bertucci 2023/02/24 for v1.80

# Code broken into several sty files which are accounted
# for here rather than having their own cwls.

## from novel.cls ##
#include:luatex
#include:ifluatex
#include:ifxetex
#include:luatex85
#include:pdftexcmds
#include:etoolbox
#include:xifthen
#include:xstring
#include:fp
#include:xfp
#include:keyval
#include:silence
#include:textpos
#include:calc
#include:atbegshi
#include:letltxmacro
#include:xparse
#include:noindentafter
#include:changepage
#include:magaz
#include:xcolor
#include:adjustbox
#include:eso-pic
#include:pdfpages
#include:fontspec
#include:unicode-math
#include:polyglossia
#include:lipsum

#keyvals:\documentclass/novel#c
draft
sandbox
shademargins
cropmarks
cropview
closecrop
xml
coverart
mtoff
test
unblock
revert
#endkeyvals

\thepdfminorversion#S
\gsetlength{cmd}{length}#*
\ifdraftdoc#*
\draftdoctrue#*
\draftdocfalse#*
\ifmsdoc#*
\msdoctrue#*
\msdocfalse#*
\thesandboxcount#*
\testsuiteoops{arg}#*
\mustbelibertinus#S
\mustbelmodern#S

## from novel-FileData.sty ##
\SetTitle{title%text}
\theTitle
\thetitle#*
\SetAuthor{author}
\theAuthor
\theauthor#*
\SetSubtitle{subtitle%text}
\subtitle{subtitle%text}#*
\theSubtitle
\thesubtitle#*
\SetApplication{text}
\SetProducer{text}
\SetPDFX{compliance standard}
\SetPDFX[ouput intent]{compliance standard}

## from novel-LayoutSettings.sty ##
\SetTrimSize{width}{height}
\SetMargins{top%l}{outer%l}{bottom%l}{inner%l}
\SetMargin{top%l}{outer%l}{bottom%l}{inner%l}#S
\SetUnsafeZone{top%l}{outer%l}{bottom%l}{inner%l}
\SetMediaSize{width}{height}
\SetLinesPerPage{integer}
\SetFontSize{length}
\ifWithinFrontmatter#*
\WithinFrontmattertrue#*
\WithinFrontmatterfalse#*
\ifWithinMainmatter#*
\WithinMainmattertrue#*
\WithinMainmatterfalse#*
\mainmatter
\backmatter
\HUGE
\frontmatter
\chapter{title%text}#*
\begin{labeling}#*
\end{labeling}#*
\begin{labeling*}#*
\end{labeling*}#*

## from novel-Fonts.sty ##
#include:microtype
\CreateFontFeature{code}{substitutions}
\SetChapterFont{font}
\SetChapterFont[features%keyvals]{font}
\SetDecoFont{font}
\SetDecoFont[features%keyvals]{font}
\SetHeadFont{font}
\SetHeadFont[features%keyvals]{font}
\SetMasterFont{font}#S
\SetMasterFont[features%keyvals]{font}#S
\SetParentFont{font}
\SetParentFont[features%keyvals]{font}
\SetSubchFont{font}
\SetSubchFont[features%keyvals]{font}
\NewFontFamily{cmd}{font family}#d
\NewFontFamily{cmd}[features%keyvals]{font family}#d
\NewFontFace{cmd}{font}#d
\NewFontFamily{cmd}[features%keyvals]{font}#d
\SetSansFont{font}
\SetSansFont[features%keyvals]{font}
\SetMonoFont{font}
\SetMonoFont[features%keyvals]{font}
\SetMathFont{font}
\SetMathFont[features%keyvals]{font}
\AddFontFeatures{features%keyvals}
\AddFontFeature{features%keyvals}
#keyvals:\SetChapterFont,\SetDecoFont,\SetHeadFont,\SetMasterFont,\SetParentFont,\SetSubchFont,\NewFontFamily,\NewFontFamily,\SetSansFont,\SetMonoFont,\SetMathFont,\AddFontFeatures,\AddFontFeature
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
Numbers=#Uppercase,Lowercase,Lining,OldStyle,Proportional,Monospaced,SlashedZero,Arabic,ResetAll
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
UprightFeatures={%<features%>}
UprightFont=%<font name%>
Variant=%<integer%>
Vertical=#RotatedGlyphs,AlternatesForRotation,Alternates,KanaAlternates,Kerning,AlternateMetrics,HalfMetrics,ProportionalMetrics,ResetAll
VerticalPosition=#Superior,Inferior,Numerator,Denominator,ScientificInferior,Ordinal,ResetAll
WordSpace=%<number%>
Mapping=%<xetex-only feature%>
Renderer=%<renderer%>
#endkeyvals
\SetDropCapColor{color}
\SetDropCapColor[color model]{color}
\SetDropCapFont{font}
\mainfont#*
\parentfontfeatures#*
\parentfontname#*
\smcp{text}#*

## from novel-DropCap.sty ##
\theNDCDefaultLines#*
\theNDCDefaultDepth#*
\NDCDefaultVoffset#*
\NDCDefaultHoffset#*
\NDCDefaultScale#*
\NDCDefaultBloat#*
\NDCDefaultGap#*
\NDCboxwidth#*
\NDCboxheight#*
\NDCboxdepth#*
\dropcap{letter or image}
\dropcap[options%keyvals]{letter or image}
\dropcap*{letter or image}
\dropcap*[options%keyvals]{letter or image}
#keyvals:\dropcap,\dropcap*
lines=%<integer%>
gap=##L
hoffset=##L
voffset=##L
ante={%<text%>}
ante*={%<text%>}
scale=%<number%>
bloat=%<number%>
depth=%<integer%>
#endkeyvals

## from novel-TextMacros.sty ##
\straightquote#*
\straightdblquote#*
\midcase{text}
\decoglyph{char number}
\memo{arg}#*
\stake
\allsmcp{text}
\oldscshape#*
\flexbox{contents%text}#*
\flexbox[width]{contents%text}#*
\bigemdash
\bigemdash[yoffset,thickness]
\charscale{text}
\charscale[scale,hoffset,voffset]{text}
\charscale*{text}
\charscale*[scale,hoffset,voffset]{text}
\TotalYpos#*
\PosTolerance#*
\begin{parascale}
\begin{parascale}[scale]
\end{parascale}
\getParapos#*
\CurrentParapos#*
\ParaHowdown#*
\ParaLinesdown#*
\ParaResidual#*
\ParaComplain#*
\ParaDeficit#*
\begin{toc}{extra margins}
\begin{toc}[extra entry sep]{extra margins}
\end{toc}
\tocitem{description%text}{page number}
\tocitem[chapter number]{description%text}{page number}
\tocitem*{description%text}{page number}
\tocitem*[chapter number]{description%text}{page number}
\begin{legalese}
\end{legalese}
\hangleft{contents%text}#*
\showlength{length}{units}#*
\showlength[decimal places]{length}{units}#*
\lnum{numbers}
\yadacurrentcount#*
\yadaendcount#*
\novelyadayada#*
\novelyadayada[integer]#*
\novelyadayada*#*
\novelyadayada*[integer]#*
\sidebyside{content1%text}{content2%text}
\sidebyside[a,b,c,d]{content1%text}{content2%text}
\nfs#*
\nbs#*
\normalparindent#*
\normalxheight#*
\normalXheight#*
\normalscxheight#*
\normalAringheight#*
\normaldescender#*
\forceindent#*
\backindent#*

## from novel-HeadFootStyles.sty ##
#include:fancyhdr
\SetHeadFootStyle{style number}
\SetHeadStyle#S
\SetHeadJump{number}
\SetFootJump{number}
\SetLooseHead{number}
\SetEmblems{verso}{recto}
\SetEmblem#S
\SetPageNumberStyle{code}
\pagenumberstyle#S
\dropfolionow#S
\NewVersoHeadText{text}#*
\versoheadtext#*
\SetVersoHeadText{text}#*
\RenewVersoHeadText{text}#*
\NewRectoHeadText{text}#*
\rectoheadtext#*
\SetRectoHeadText{text}#*
\RenewRectoHeadText{text}#*

## from novel-ChapterScene.sty ##
\SetChapterStartStyle{style}
\SetChapterStart#S
\SetChapterStartHeight{lines}
\SetScenebreakIndent{true or false}
\scenebreak
\sceneline
\scenestars
\getBreakpos{arg}#*
\CurrentBreakpos#*
\FirstLine*{text}#*
\oldFirstLine{text}#S
\FirstLineFoo{text}#S
\thenovelcn#*
\begin{ChapterStart}
\begin{ChapterStart}[lines]
\begin{ChapterStart}[lines][style]
\end{ChapterStart}
\ChapterTitle{title}#L1
\ChapterTitle[alignment%keyvals]{title}#L1
\ChapterSubtitle{text}
\ChapterSubtitle[alignment%keyvals]{text}
#keyvals:\ChapterTitle,\ChapterSubtitle
l
c
r
#endkeyvals
\ChapterDeco{text}
\ChapterDeco[alignment scale]{text}
\QuickChapter{title}
\QuickChapter[line length%l]{title}
\cleartorecto
\cleartoend
\thisline#*

# deprecated
\IndentAfterScenebreak#S

## from novel-Images.sty ##
#include:luacode
#include:wrapfig
\PDFHasDisallowedColorspaceTF{string}#*
\PDFVerifyInfoFieldTF{string1}{string2}{string3}#*
\ScriptCoverImage{imagefile}#*g
\imagewidth#*
\imageheight#*
\imagehoffset#*
\imagevoffset#*
\imagestarred#*
\imagefilename#*
\InlineImage{imagefile}#g
\InlineImage[hoffset,voffset]{imagefile}#g
\InlineImage*{imagefile}#g
\InlineImage*[hoffset,voffset]{imagefile}#g
\floatlocation{float}{pos}#*
\FloatImage{imagefile}#g
\FloatImage[pos,xoffset,yoffset]{imagefile}#g
\WrapImage{imagefile}#g
\WrapImage[position%keyvals]{imagefile}#g
#keyvals:\WrapImage
l
r
o
i
L
R
O
I
#endkeyvals
\wrapimage#S
\novelgetbytes{arg1}{arg2}{arg3}#*
\novelbytesare#*
\novelpngbitdepth{arg}#*
\novelpngcolortype{arg}#*
\SetKnownGoodImages{imagefile list}

## from novel-Footnotes.sty ##
\sups{text}#*
\subs{text}#*
\realmarker
\fakemarker
\SetMarkerStyle{astersk,dagger,number}
\SetMarkerStyle[real,fake]{astersk,dagger,number}
\SetMarkers#S
\endnote{comment%text}
\endnotetext{number}{text}
\Resetendnote#*
\ResetFootnoteSymbol#*
\ResetFootnote#*
\nentext{arg1}{arg2}#*

## from novel-CalculateLayout.sty ##
# no user commands

## from novel-PostLayout.sty ##
# no user commands

## from novel-pdfx.sty ##
#include:hyperref
# no user commands
