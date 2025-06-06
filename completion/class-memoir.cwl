# updated 2025/03/06 for v3.8.3

#include:iftex
#include:array
#include:dcolumn
#include:delarray
#include:tabularx
#include:booktabs
#include:textcase
#include:etoolbox
#include:xpatch
#include:nameref
#include:verbatim
#include:shortvrb

#keyvals:\documentclass/memoir
10pt
11pt
12pt
14pt
17pt
20pt
25pt
30pt
36pt
48pt
60pt
9pt
a3paper
a4paper
a5paper
a6paper
a7paper
article
b3paper
b4paper
b5paper
b6paper
b7paper
broadsheetpaper
crownvopaper
dbillpaper
demyvopaper
draft
ebook
executivepaper
extrafontsizes
final
fleqn
foolscapvopaper
fullptlayout
imperialvopaper
landscape
largecrownvopaper
largepostvopaper
ledgerpaper
legalpaper
leqno
letterpaper
mcrownvopaper
mdemyvopaper
mediumvopaper
mlargecrownvopaper
ms
msmallroyalvopaper
oldfontcommands
oldpaper
onecolumn
oneside
openany
openbib
openleft
openright
postvopaper
pottvopaper
royalvopaper
showtrims
smalldemyvopaper
smallroyalvopaper
statementpaper
superroyalvopaper
twocolumn
twoside
#endkeyvals

\abnormalparskip{length}#*
\abovecolumnspenalty#*
\abscolnamefont#*
\abscoltextfont#*
\abslabeldelim{text}#*
\absleftindent#*
\absnamepos#*
\absparindent#*L
\absparsep#*L
\absrightindent#*L
\abstitleskip#*L
\abstractcol#*
\abstractintoc#*
\abstractnamefont#*
\abstractnum#*
\abstractrunin#*
\abstracttextfont#*
\addappheadtotoc#*
\added{change-id}#*
\addperiod{text}#*
\addtonotes{text}#*
\addtopsmarks{pagestyle%keyvals}{prepend}{append}#*
\addtostream{stream}{text}#*
\afterbookskip#*
\afterchapskip#*
\afterchapternum#*
\afterchaptertitle#*
\afterepigraphskip#*
\afterloftitle#*
\afterlottitle#*
\afterparaskip#*
\afterpartskip#*
\afterPoemTitle#*
\afterPoemTitlenum#*
\afterPoemTitleskip#*
\afterpoemtitleskip#*
\aftersecskip#*
\aftersubparaskip#*
\aftersubsecskip#*
\aftersubsubsecskip#*
\aftertoctitle#*
\aliaspagestyle{alias%keyvals}{original}#*
\alsoname#*
\amname#*
\andnext#*
\anyptfilebase#*
\anyptsize#*
\appendixpage#*
\appendixpage*#*
\appendixpagename#*
\appendixrefname#*
\appendixtocname#*
\Aref{key}#r
\arraytostring{array name}{result%cmd}#*d
\AtBeginClass{class}{code}#*
\AtBeginFile{file}{code}#*
\AtBeginPackage{package}{code}#*
\atcentercr#*
\AtEndClass{class}{code}#*
\AtEndFile{file}{code}#*
\AtEndPackage{package}{code}#*
\atendtheglossaryhook#*
\autocols{preamble}{numOfCols}{style}{entries%text}
\autocols[width]{preamble}{numOfCols}{style}{entries%text}
\autorows{preamble}{numOfCols}{style}{entries%text}
\autorows[width]{preamble}{numOfCols}{style}{entries%text}
\backmatter
\beforebookskip#*
\beforechapskip#*
\beforeepigraphskip#*
\beforeparaskip#*
\beforepartskip#*
\beforePoemTitleskip#*
\beforepoemtitleskip#*
\beforesecskip#*
\beforesubparaskip#*
\beforesubsecskip#*
\beforesubsubsecskip#*
\begin{adjustwidth*}{left%l}{right%l}
\begin{adjustwidth}{left%l}{right%l}
\begin{altverse}
\begin{appendices}
\begin{bibitemlist}
\begin{blockdescription}
\begin{boxedverbatim*}#V
\begin{boxedverbatim}#V
\begin{comment}
\begin{ctabular}{preamble}#\tabular
\begin{ctabular}[position]{preamble}#\tabular
\begin{DoubleSpace*}
\begin{DoubleSpace}
\begin{epigraphs}
\begin{fboxverbatim}#V
\begin{flexlabelled}
\begin{framed}
\begin{hangparas}
\begin{KeepFromToc}
\begin{labelled}
\begin{leftbar}
\begin{marginfigure}
\begin{margintable}
\begin{midsloppypar}
\begin{onecolabstract}
\begin{OnehalfSpace*}
\begin{OnehalfSpace}
\begin{patverse*}
\begin{patverse}
\begin{qframe}
\begin{qshade}
\begin{shaded}
\begin{sidecaption}{title%text}
\begin{sidecaption}{title%text}[label%labeldef]
\begin{sidecaption}[fortoc]{title%text}
\begin{sidecaption}[fortoc]{title%text}[label%labeldef]
\begin{sidecontcaption}{title%text}
\begin{sidecontcaption}{title%text}[label%labeldef]
\begin{sidelegend}{title%text}
\begin{sidelegend}{title%text}[label%labeldef]
\begin{sidenamedlegend}{title%text}
\begin{sidenamedlegend}{title%text}[label%labeldef]
\begin{SingleSpace}
\begin{snugshade}
\begin{Spacing}{factor}
\begin{subappendices}
\begin{subfloat}
\begin{symbols}
\begin{theglossary}
\begin{titlingpage*}
\begin{titlingpage}
\begin{verbatimoutput}{file}#V
\begin{vminipage}
\begin{vplace}
\begin{writeverbatim}{stream}#V
\begintheglossaryhook#*
\bibintoc#*
\bibitemsep#*
\biblistextra#*
\bibmark#*
\bibname#*
\bibsection#*
\bicaption{short1%text}{long1%text}{name%text}{long2%text}
\bicaption[label%labeldef]{short1%text}{long1%text}{name%text}{long2%text}
\bicontcaption{long1%text}{name%text}{long2%text}
\binding#*
\bionenumcaption{short1%text}{long1%text}{name%text}{short2%text}{long2%text}#*
\bionenumcaption[label%labeldef]{short1%text}{long1%text}{name%text}{short2%text}{long2%text}#*
\bitwonumcaption{short1%text}{long1%text}{name%text}{short2%text}{long2%text}#*
\bitwonumcaption[label%labeldef]{short1%text}{long1%text}{name%text}{short2%text}{long2%text}#*
\bktabrule{width}#*
\blockdescriptionlabel{label}#*
\book{title}
\bookblankpage#*
\bookname#*
\booknamefont#*
\booknamenum#*
\booknumberline{number}#*
\booknumberlinebox#*
\booknumberlinehook{number}#*
\booknumfont#*
\bookpageend#*
\bookpagemark{title%text}#*
\bookrefname#*
\booktitlefont#*
\bottomsectionpenalty#*
\bottomsectionskip#*
\boxedverbatiminput{file}
\boxedverbatiminput*{file}
\boxverbflag#*
\Bref{key}#r
\bs#*
\bvbox#*
\bvboxsep#*
\bvendofpage{text}#*
\bvendrulehook#*
\bvleftsidehook#*
\bvnumbersinside#*
\bvnumbersoutside#*
\bvnumlength#*
\bvrightsidehook#*
\bvsides#*
\bvtopandtail#*
\bvtopmidhook#*
\bvtopofpage{text}#*
\bvtoprulehook#*
\calccentering{length}#*
\cancelthanksrule#*
\captiondelim{delim}#*
\captionnamefont{font}#*
\captionsize#*
\captionstyle{style}#*
\captionstyle[shortstyle]{style}#*
\captiontitlefinal{text}#*
\captiontitlefont{font}#*
\captionwidth{length}#*
\cardinal{number}#*
\centerfloat#*
\centerlastline#*
\cftaddnumtitleline{ext}{kind}{num}{title%text}{page}#*
\cftaddtitleline{ext}{kind}{title%text}{page}#*
\cftappendixname#*
\cftbeforebookpenalty*
\cftbeforebookskip#*
\cftbeforechapterpenalty#*
\cftbeforechapterskip#*
\cftbeforefigureskip#*
\cftbeforeparagraphskip#*
\cftbeforepartpenalty#*
\cftbeforepartskip#*
\cftbeforesectionskip#*
\cftbeforesubparagraphskip#*
\cftbeforesubsectionskip#*
\cftbeforesubsubsectionskip#*
\cftbeforetableskip#*
\cftbookafterpnum#*
\cftbookaftersnum#*
\cftbookaftersnumb#*
\cftbookbreak#*
\cftbookdotsep#*
\cftbookfillnum{arg}#*
\cftbookfont#*
\cftbookformatpnum{number}#*
\cftbookformatpnumhook{number}#*
\cftbookindent#*
\cftbookleader#*
\cftbookname#*
\cftbooknumwidth#*
\cftbookpagefont#*
\cftbookpresnum#*
\cftchapterafterpnum#*
\cftchapteraftersnum#*
\cftchapteraftersnumb#*
\cftchapterbreak#*
\cftchapterdotsep#*
\cftchapterfillnum{arg}#*
\cftchapterfont#*
\cftchapterformatpnum{number}#*
\cftchapterformatpnumhook{number}#*
\cftchapterindent#*
\cftchapterleader#*
\cftchaptername#*
\cftchapternumwidth#*
\cftchapterpagefont#*
\cftchapterpresnum#*
\cftdot#*
\cftdotfill{length}#*
\cftdotsep#*
\cftfigureafterpnum#*
\cftfigureaftersnum#*
\cftfigureaftersnumb#*
\cftfiguredotsep#*
\cftfigurefillnum{arg}#*
\cftfigurefont#*
\cftfigureformatpnum{number}#*
\cftfigureformatpnumhook{number}#*
\cftfigureindent#*
\cftfigureleader#*
\cftfigurename#*
\cftfigurenumwidth#*
\cftfigurepagefont#*
\cftfigurepresnum#*
\cftinsert{name}#*
\cftinsertcode{name}{code}#*
\cftinserthook{file}{name}#*
\cftinserthook*{file}{name}#*
\cftlocalchange{ext}{pnumwidth}{toc}#*
\cftnodots#*
\cftpagenumbersoff{kind}#*
\cftpagenumberson{kind}#*
\cftparagraphafterpnum#*
\cftparagraphaftersnum#*
\cftparagraphaftersnumb#*
\cftparagraphdotsep#*
\cftparagraphfillnum{arg}#*
\cftparagraphfont#*
\cftparagraphformatpnum{number}#*
\cftparagraphformatpnumhook{number}#*
\cftparagraphindent#*
\cftparagraphleader#*
\cftparagraphname#*
\cftparagraphnumwidth#*
\cftparagraphpagefont#*
\cftparagraphpresnum#*
\cftparfillskip#*
\cftparskip#*
\cftpartafterpnum#*
\cftpartaftersnum#*
\cftpartaftersnumb#*
\cftpartbreak#*
\cftpartdotsep#*
\cftpartfillnum{pnum}#*
\cftpartfont#*
\cftpartformatpnum{pnum}#*
\cftpartformatpnumhook{number}#*
\cftpartindent#*
\cftpartleader#*
\cftpartname#*
\cftpartnumwidth#*
\cftpartpagefont#*
\cftpartpresnum#*
\cftsectionafterpnum#*
\cftsectionaftersnum#*
\cftsectionaftersnumb#*
\cftsectiondotsep#*
\cftsectionfillnum{arg}#*
\cftsectionfont#*
\cftsectionformatpnum{number}#*
\cftsectionformatpnumhook{number}#*
\cftsectionindent#*
\cftsectionleader#*
\cftsectionname#*
\cftsectionnumwidth#*
\cftsectionpagefont#*
\cftsectionpresnum#*
\cftsetindents{kind}{indent}{numwidth}#*
\cftsubparagraphafterpnum#*
\cftsubparagraphaftersnum#*
\cftsubparagraphaftersnumb#*
\cftsubparagraphdotsep#*
\cftsubparagraphfillnum{arg}#*
\cftsubparagraphfont#*
\cftsubparagraphformatpnum{number}#*
\cftsubparagraphformatpnumhook{number}#*
\cftsubparagraphindent#*
\cftsubparagraphleader#*
\cftsubparagraphname#*
\cftsubparagraphnumwidth#*
\cftsubparagraphpagefont#*
\cftsubparagraphpresnum#*
\cftsubsectionafterpnum#*
\cftsubsectionaftersnum#*
\cftsubsectionaftersnumb#*
\cftsubsectiondotsep#*
\cftsubsectionfillnum{arg}#*
\cftsubsectionfont#*
\cftsubsectionformatpnum{number}#*
\cftsubsectionformatpnumhook{number}#*
\cftsubsectionindent#*
\cftsubsectionleader#*
\cftsubsectionname#*
\cftsubsectionnumwidth#*
\cftsubsectionpagefont#*
\cftsubsectionpresnum#*
\cftsubsubsectionafterpnum#*
\cftsubsubsectionaftersnum#*
\cftsubsubsectionaftersnumb#*
\cftsubsubsectiondotsep#*
\cftsubsubsectionfillnum{arg}#*
\cftsubsubsectionfont#*
\cftsubsubsectionformatpnum{number}#*
\cftsubsubsectionformatpnumhook{number}#*
\cftsubsubsectionindent#*
\cftsubsubsectionleader#*
\cftsubsubsectionname#*
\cftsubsubsectionnumwidth#*
\cftsubsubsectionpagefont#*
\cftsubsubsectionpresnum#*
\cfttableafterpnum#*
\cfttableaftersnum#*
\cfttableaftersnumb#*
\cfttabledotsep#*
\cfttablefillnum{arg}#*
\cfttablefont#*
\cfttableformatpnum{number}#*
\cfttableformatpnumhook{number}#*
\cfttableindent#*
\cfttableleader#*
\cfttablename#*
\cfttablenumwidth#*
\cfttablepagefont#*
\cfttablepresnum#*
\cftwhatismyname#*
\changecaptionwidth#*
\changed{change-id}#*
\changeglossactual{char}#*
\changeglossactual[file]{char}#*
\changeglossnum{thecounter}#*
\changeglossnum[file]{thecounter}#*
\changeglossnumformat{format}#*
\changeglossnumformat[file]{format}#*
\changeglossref{thecounter}#*
\changeglossref[file]{thecounter}#*
\changemarks#*
\changepage{textheight}{textwidth}{evensidemargin}{oddsidemargin}{columnsep}{topmargin}{headheight}{headsep}{footskip}#*
\changetext{textheight}{textwidth}{evensidemargin}{oddsidemargin}{columnsep}#*
\changetocdepth{integer}#*
\chapindent#*
\chapnamefont#*
\chapnumfont#*
\chapter[toc-title%text][head-title%text]{title}#L1
\chapter[toc-title%text]{title}#L1
\chapterheadstart#*
\chaptermark{code}#*
\chaptername#*
\chapternamenum#*
\chapternumberline{number}#*
\chapternumberlinebox#*
\chapternumberlinehook{number}#*
\chapterprecis{text}#*
\chapterprecishere{text}#*
\chapterprecistoc{text}#*
\chapterrefname#*
\chapterstyle{style%keyvals}
#keyvals:\chapterstyle
article
asu
asuappendix
bianchi
bringhurst
brotherton
chappell
companion
crosshead
culver
dash
default
demo
demo2
demo3
dowding
ell
fred
ger
hangnum
komalike
lyhne
madsen
ntglike
pedersen
reparticle
section
southall
tandh
thatcher
veelo
verville
wilsondob
%chapterstyle
#endkeyvals
\chaptitlefont#*
\checkandfixthelayout#*
\checkandfixthelayout[algorithm%keyvals]#*
#keyvals:\checkandfixthelayout
fixed
classic
lines
nearest
#endkeyvals
\checkarrayindex{array name}{index}#*
\checkifinteger{number}#*
\checkoddpage#*
\checkthelayout#*
\checkthelayout[algorithm%keyvals]#*
#keyvals:\checkthelayout
fixed
classic
lines
nearest
#endkeyvals
\citeindexfile#*
\clearforchapter#*
\clearmark{mark}#*
\clearplainmark{mark}#*
\cleartoevenpage#*
\cleartoevenpage[text]#*
\cleartooddpage#*
\cleartooddpage[text]#*
\cleartorecto#*
\cleartoverso#*
\closeinputstream{stream}#*
\closeoutputstream{stream}#*
\cmd{cmd}#*
\cmdprint{cmd}#*
\colorchapnum#*
\colorchaptitle#*
\commentsoff{name}#*
\commentson{name}#*
\contcaption{text}
\continuousmarks#*
\continuousnotenums#*
\contsubbottom{text}
\contsubbottom[short text%text]{text}
\contsubbottom[short text%text][subtitle%text]{text}
\contsubcaption{text}
\contsubcaption[short text%text]{text}
\contsubtop{text}
\contsubtop[short text%text]{text}
\contsubtop[short text%text][subtitle%text]{text}
\copypagestyle{copy%specialDef}{original%keyvals}#*s#%pagestyle
\cplabel#*
\createmark{sec}{marks%keyvals}{show}{prefix}{postfix}#*
\createplainmark{type}{marks%keyvals}{text}#*
#keyvals:\createmark,\createplainmark
left
both
right
#endkeyvals
\Cref{key}#r
\crtok#*
\cs{csname}
\ctableftskip#*
\ctabrightskip#*
\ctabsetlines#*
\defaultlists#*
\defaultsecnum#*
\deleted{change-id}#*
\DisemulatePackage{package}#*
\doccoltocetc#*
\DoubleSpacing#*
\DoubleSpacing*#*
\dropchapter{length}#*
\droptitle#*
\easypagecheck#*
\emptythanks#*
\EmulatedPackage{package}#*
\EmulatedPackage{package}[date]#*
\EmulatedPackageWithOptions{options}{package}#*
\EmulatedPackageWithOptions{options}{package}[date]#*
\end{adjustwidth*}
\end{adjustwidth}
\end{altverse}
\end{appendices}
\end{bibitemlist}
\end{blockdescription}
\end{boxedverbatim*}
\end{boxedverbatim}
\end{comment}
\end{ctabular}
\end{DoubleSpace*}
\end{DoubleSpace}
\end{epigraphs}
\end{fboxverbatim}
\end{flexlabelled}
\end{framed}
\end{hangparas}
\end{KeepFromToc}
\end{labelled}
\end{leftbar}
\end{marginfigure}
\end{margintable}
\end{midsloppypar}
\end{onecolabstract}
\end{OnehalfSpace*}
\end{OnehalfSpace}
\end{patverse*}
\end{patverse}
\end{qframe}
\end{qshade}
\end{shaded}
\end{sidecaption}
\end{sidecontcaption}
\end{sidelegend}
\end{sidenamedlegend}
\end{SingleSpace}
\end{snugshade}
\end{Spacing}
\end{subappendices}
\end{subfloat}
\end{symbols}
\end{theglossary}
\end{titlingpage*}
\end{titlingpage}
\end{verbatimoutput}
\end{vminipage}
\end{vplace}
\end{writeverbatim}
\endMakeFramed#*
\ensureonecol#*
\epigraph{text}{source}
\epigraphflush#*
\epigraphfontsize{fontsize}#*
\epigraphforheader{text}#*
\epigraphforheader[distance%l]{text}#*
\epigraphhead{text}#*
\epigraphhead[distance%l]{text}#*
\epigraphpicture#*
\epigraphposition{flush}#*
\epigraphrule#*
\epigraphsize#*
\epigraphsourceposition{flush}#*
\epigraphtextposition{flush}#*
\epigraphwidth#*
\everylistparindent#*
\extrafeetendmini#*
\extrafeetendminihook#*
\extrafeetins#*
\extrafeetinshook#*
\extrafeetminihook#*
\extrafeetreinshook#*
\fancybreak{text}#*
\fancybreak*{text}#*
\fcardinal{number}#*
\feetabovefloat#*
\feetatbottom#*
\feetbelowfloat#*
\feetbelowragged#*
\figurerefname#*
\firmlist#*
\firmlists#*
\FirstFrameCommand#*
\fixdvipslayout#*
\fixheaderwidths#*
\fixpdflayout#*
\fixthelayout#*
\flagverse{flag}#*
\flegfigure#*
\flegtable#*
\flegtocfigure{title%text}#*
\flegtoctable{title%text}#*
\FloatBlock#*
\FloatBlockAllowAbove#*
\FloatBlockAllowBelow#*
\flushleftright#*
\fnumbersep#*
\footfootmark#*
\footfudgefiddle#*
\footinsdim#*
\footmarksep#*
\footmarkstyle{style}#*
\footmarkwidth#*
\footnotesatfoot#*
\footnotesinmargin#*
\footparindent#*
\footruleheight#*
\footruleskip#*
\footscript#*
\foottextfont#*
\foottopagenote#*
\fordinal{number}#*
\foremargin#*
\FrameCommand#*
\FrameHeightAdjust#*
\framepichead#*
\framepichook#*
\framepictextfoot#*
\FrameRestore#*
\FrameRule#*
\FrameSep#*
\fref{key}#r
\frontmatter
\frontmatter*
\Ftrimpicbl#*
\getarrayelement{array name}{index}{result}#*
\getthelinenumber{counter}{start}#*
\glossary{term}{description%text}#*
\glossary[file]{term}{description%text}#*
\glossary[file](key%plain){term}{description%text}#*
\glossarycolsep#*
\glossaryintoc#*
\glossarymark#*
\glossaryname#*
\glossaryrule#*
\glossaryspace#*
\glossitem{term}{description%text}{ref}{num}#*
\gobm{number}#*
\hangcaption#*
\hangfrom{text}#*
\hangpara{indent%l}{number}#*
\hangsecnum#*
\hangsubcaption#*
\headdrop#*
\headnameref#*
\headstyles{name}#*
\headwidth#*
\hideindexmarks#*
\hmpunct#*
\HUGE
\hyperlink{target name}{link text%text}#*
\hyperpage{arg}#*
\hyperspindexpage#*
\idtextinnotes{id}#*
\ifaltindent#S
\altindenttrue#S
\altindentfalse#S
\ifanappendix#*
\anappendixtrue#S
\anappendixfalse#S
\ifartopt#*
\artopttrue#S
\artoptfalse#S
\ifbounderror#*
\bounderrortrue#S
\bounderrorfalse#S
\ifbvcountinside#S
\bvcountinsidetrue#S
\bvcountinsidefalse#S
\ifbvcountlines#*
\bvcountlinestrue#*
\bvcountlinesfalse#*
\ifbvperpage#*
\bvperpagetrue#*
\bvperpagefalse#*
\ifchangemarks#S
\changemarkstrue#S
\changemarksfalse#S
\ifcntrmod#S
\cntrmodtrue#S
\cntrmodfalse#S
\ifdonemaincaption#S
\donemaincaptiontrue#S
\donemaincaptionfalse#S
\ifdraftdoc#*
\draftdoctrue#S
\draftdocfalse#S
\ifextrafontsizes#S
\extrafontsizestrue#S
\extrafontsizesfalse#S
\ifheadnameref#S
\headnamereftrue#S
\headnamereffalse#S
\ifinteger#*
\integertrue#S
\integerfalse#S
\iflowernumtoname#S
\lowernumtonametrue#S
\lowernumtonamefalse#S
\ifmakeordinal#S
\makeordinaltrue#S
\makeordinalfalse#S
\ifmemhyperindex#S
\memhyperindextrue#S
\memhyperindexfalse#S
\ifmemlandscape#S
\memlandscapetrue#S
\memlandscapefalse#S
\ifmempagenotes#S
\mempagenotestrue#S
\mempagenotesfalse#S
\ifmemtortm#*
\memtortmtrue#S
\memtortmfalse#S
\ifminusnumber#S
\minusnumbertrue#S
\minusnumberfalse#S
\ifmsdoc#S
\msdoctrue#S
\msdocfalse#S
\ifnamesubappendix#S
\namesubappendixtrue#S
\namesubappendixfalse#S
\ifnobibintoc#*
\nobibintoctrue#S
\nobibintocfalse#S
\ifnoglossaryintoc#S
\noglossaryintoctrue#S
\noglossaryintocfalse#S
\ifnoindexintoc#S
\noindexintoctrue#S
\noindexintocfalse#S
\ifnotcntrmod#S
\notcntrmodtrue#S
\notcntrmodfalse#S
\ifnotnumtonameallcaps#S
\notnumtonameallcapstrue#S
\notnumtonameallcapsfalse#S
\ifoddpage#*
\oddpagetrue#S
\oddpagefalse#S
\ifonecolglossary#S
\onecolglossarytrue#S
\onecolglossaryfalse#S
\ifonecolindex#S
\onecolindextrue#S
\onecolindexfalse#S
\ifonlyfloats{true}{false}#*
\ifpattern#S
\patterntrue#S
\patternfalse#S
\ifpriornum#S
\priornumtrue#S
\priornumfalse#S
\ifraggedbottomsection#S
\raggedbottomsectiontrue#S
\raggedbottomsectionfalse#S
\ifreportnoidxfile#S
\reportnoidxfiletrue#S
\reportnoidxfilefalse#S
\ifreversesidepar#S
\reversesidepartrue#S
\reversesideparfalse#S
\ifsamename#*
\samenametrue#S
\samenamefalse#S
\ifscapmargleft#*
\scapmarglefttrue#*
\scapmargleftfalse#*
\ifshowheadfootloc#S
\showheadfootloctrue#S
\showheadfootlocfalse#S
\ifshowindexmark#S
\showindexmarktrue#S
\showindexmarkfalse#S
\ifshowtextblockloc#S
\showtextblockloctrue#S
\showtextblocklocfalse#S
\ifshowtrims#S
\showtrimstrue#S
\showtrimsfalse#S
\ifsidebaroneside#S
\sidebaronesidetrue#S
\sidebaronesidefalse#S
\ifsideparswitch#S
\sideparswitchtrue#S
\sideparswitchfalse#S
\ifstarpattern#S
\starpatterntrue#S
\starpatternfalse#S
\IfStreamOpen{stream}{true}{false}#*
\ifstrictpagecheck#*
\strictpagechecktrue#S
\strictpagecheckfalse#S
\ignorenoidxfile#*
\iiirdstring#*
\iindstring#*
\indentafterchapter#*
\indentcaption{length}#*
\indentpattern{digits}#*
\indexcolsep#*
\indexintoc#*
\indexmark#*
\indexmarkstyle#*
\indexrule#*
\insertchapterspace#*
\iscntrmod{counter}{number}#*
\isopage{spine%l}#*
\iststring#*
\itemsepi#*
\itemsepii#*
\itemsepiii#*
\justlastraggedleft#*
\keepthetitle#*
\killtitle#*
\label(bookmark){label%labeldef}#*
\LastFrameCommand#*
\lastlineparrule#*
\lastlinerulefill#*
\lcminusname#*
\leadpagetoclevel#*
\leavespergathering{number}#*
\leftcenterright#*
\leftspringright{lfrac}{rfrac}{ltext}{rtext}#*
\legend{text}#*
\letcountercounter{counter1}{counter2}#*
\linemodnum#*
\linenottooshort#*
\linenottooshort[length]#*
\linenumberfont{font}#*
\linenumberfrequency{integer}#*
\linespercol#*
\lofheadstart#*
\lofmark#*
\loosesubcaptions#*
\lotheadstart#*
\lotmark#*
\lowermargin#*
\Ltrimpicbl#*
\Ltrimpicbr#*
\Ltrimpictl#*
\Ltrimpictr#*
\lxvchars#*
\mainmatter
\mainmatter*
\makechapterstyle{name%specialDef}{code}#*s#%chapterstyle
\makeevenfoot{pagestyle%keyvals}{left}{center}{right}#*
\makeevenhead{pagestyle%keyvals}{left}{center}{right}#*
\makefootmark{text}#*
\makefootmarkhook#*
\makefootrule{pagestyle%keyvals}{width}{thickness%l}{skip%l}#*
\MakeFramed{settings}#*
\makeheadfootruleprefix{pagestyle%keyvals}{for headrule}{for footrule}#*
\makeheadfootstrut{pagestyle%keyvals}{head strut}{foot strut}#*
\makeheadfootvposition{pagestyle%keyvals}{arg2}{arg3}#*
\makeheadposition{pagestyle%keyvals}{eheadpos}{oheadpos}{efootpos}{ofootpos}#*
\makeheadrule{pagestyle}{width}{thickness%l}#*
\makeheadstyles{name}{code}#*
\makeindex[file]#*
\makememglossaryhook#*
\makememindexhook#*
\makeoddfoot{pagestyle%keyvals}{left}{center}{right}#*
\makeoddhead{pagestyle%keyvals}{left}{center}{right}#*
\makepagenote#*
\makepagestyle{name%specialDef}#*s#%pagestyle
\makepsmarks{pagestyle%keyvals}{code}#*
\makerunningfootwidth{pagestyle%keyvals}{width}#*
\makerunningheadwidth{pagestyle%keyvals}{width}#*
\makerunningwidth{pagestyle%keyvals}{headwidth%l}#*
\makerunningwidth{pagestyle%keyvals}[footwidth%l]{headwidth%l}#*
\makesidefootmark{text}#*
\makesidefootmarkhook#*
\makethanksmark#*
\makethanksmarkhook#*
\maketitlehooka#*
\maketitlehookb#*
\maketitlehookc#*
\maketitlehookd#*
\marg{arg}
\marginfloatmarginmacro#*
\marginparmargin{placement}#*
\MarkDeprecated{command}{text}#S
\MarkDeprecated*{command}{text}#S
\maxsecnumdepth{secname%keyvals}#*
#keyvals:\maxsecnumdepth
book
part
chapter
section
subsection
subsubsection
paragraph
subparagraph
all
none
#endkeyvals
\maxtocdepth{secname}#*
\medievalpage{spine%l}#*
\memappchapinfo{chapter}{for toc}{for head}{title%text}#*
\memappchapstarinfo{for toc}{title%text}#*
\memapppageinfo{title%text}#*
\memapppagestarinfo{title%text}#*
\membicaptioninfo{type}{thetype}{short1}{title1}{short2}{title2}#*
\membionenumcaptioninfo{type}{thetype}{short1}{title1}{short2}{title2}#*
\membitwonumcaptioninfo{type}{thetype}{short1}{title1}{short2}{title2}#*
\membookinfo{thebook}{for toc}{title%text}#*
\membookstarinfo{title%text}#*
\memcaptioninfo{type}{thetype}{for toc}{title%text}#*
\memchapinfo{chapter}{for toc}{for head}{title%text}#*
\memchapstarinfo{for toc}{title%text}#*
\memcline{width}{i-j}#*
\memdskips#*
\memdskipstretch#*
\memendofchapterhook#*
\memfblineboxa{arg}#*
\memfblineboxtwo{arg}#*
\memfblistfixparams#*
\memfontenc#*
\memfontfamily#*
\memfontpack#*
\memglodesc{description}#*
\memglofile#S
\memglonum{number}#*
\memgloref{ref}#*
\memgloterm{term}#*
\memgobble{arg}#*
\memhline#*
\memhline[width]#*
\memifmacroused{cmd}#*
\memjustarg{arg}#*
\memleadpageinfo{pagestyle%keyvals}{name}{title%text}#*
\memleadpagestarinfo{pagestyle%keyvals}{name}{title%text}#*
\memlegendinfo{title%text}#*
\memletcmdtxt{cmd}{csname}#*d
\memlettxttxt{csname1}{csname2}#*
\memlettxtcmd{csname}{cmd}#*
\memlistsubcaptions#*
\memnamedlegendinfo{for toc}{title%text}#*
\memoirpostopthook#*
\memorigdbs#*
\memorigpar#*
\mempartinfo{part}{for toc}{title%text}#*
\mempartstarinfo{title%text}#*
\memPD#*
\mempnofilewarn#*
\mempoeminfo{title%text}#*
\mempoemstarinfo{title%text}#*
\memPoemTitleinfo{thepoem}{for toc}{for head}{title%text}#*
\memPoemTitlestarinfo{for toc}{title%text}#*
\mempostaddapppagetotochook#*
\mempostaddbooktotochook#*
\mempostaddchaptertotochook#*
\mempostaddparttotochook#*
\mempreaddapppagetotochook#*
\mempreaddbooktotochook#*
\mempreaddchaptertotochook#*
\mempreaddparttotochook#*
\MemRestoreOrigMakecase#*
\memRTLleftskip#*
\memRTLmainraggedleft#*
\memRTLmainraggedright#*
\memRTLraggedleft#*
\memRTLraggedright#*
\memRTLrightskip#*
\memRTLvleftskip#*
\memRTLvrightskip#*
\memsavefootnote#S
\memsavepagenote#S
\memsecinfo{name}{thename}{for toc}{for head}{title%text}#*
\memsecstarinfo{name}{title%text}#*
\memsetcounter{counter}{value}#*
\memsetlengthmax{length}{value1}{value2}#*
\memsetlengthmin{length}{value1}{value2}#*
\memsetmacrounused{cmd}#*
\memsetmacroused{cmd}#*
\memUChead#*
\memversion#*
\memwritetoglo{key%plain}{name}{desc}{ref}{number}#*
\mergepagefloatstyle{style}{textstyle}{floatstyle}#*
\meta{arg}
\midbicaption{text}
\midbookskip#*
\midchapskip#*
\MidFrameCommand#*
\midpartskip#*
\midPoemTitleskip#*
\midsloppy#*
\miniscule#*
\minusname#*
\movetoevenpage#*
\movetoevenpage[text]#*
\movetooddpage#*
\movetooddpage[text]#*
\mpjustification#*
\msdoublespacing#*
\mssinglespacing#*
\multfootsep#*
\multiplefootnotemarker#*
\namedlegend#*
\namedsubappendices#*
\namenumberand#*
\namenumbercomma#*
\nametest{string1}{string2}#*
\Needspace{length}#*
\Needspace*{length}#*
\needspace{length}#*
\newarray{array name}{low}{high}#*
\newcomment{envname}#*N
\newfixedcaption{cmd}{float}#*d
\newfixedcaption[cap-cmd]{cmd}{float}#*d
\newfloat{envname}{ext}{capname}#*N
\newfloat[within]{envname}{ext}{capname}#*N
\newfootnoteseries{series}#*
\newinputstream{stream}#*
\newleadpage*[pagestyle%keyvals]{cmd}{title}#*d
\newleadpage*{cmd}{title}#*d
\newleadpage[pagestyle%keyvals]{cmd}{title}#*d
\newleadpage{cmd}{title}#*d
\newlistentry{counter}{ext}{level-1}#*
\newlistentry[within]{counter}{ext}{level-1}#*
\newlistof{csname}{ext}{name}#*
\newoutputstream{stream}#*
\newpmemlabel{arg1}{arg2}#*
\newsubfloat{float}#*
\nNamec#*
\nNamei#*
\nNameii#*
\nNameiii#*
\nNameiv#*
\nNameix#*
\nNamel#*
\nNamelx#*
\nNamelxx#*
\nNamelxxx#*
\nNamem#*
\nNamemm#*
\nNamemmm#*
\nNameo#*
\nNamev#*
\nNamevi#*
\nNamevii#*
\nNameviii#*
\nNamex#*
\nNamexc#*
\nNamexi#*
\nNamexii#*
\nNamexiii#*
\nNamexiv#*
\nNamexix#*
\nNamexl#*
\nNamexv#*
\nNamexvi#*
\nNamexvii#*
\nNamexviii#*
\nNamexx#*
\nNamexxx#*
\nobibintoc#*
\nobookblankpage#*
\nobvbox#*
\nochangemarks#*
\noDisplayskipStretch#*
\noglossaryintoc#*
\noindentafterchapter#*
\noindexintoc#*
\nonzeroparskip#*
\nopartblankpage#*
\nopfbreakOutput#*
\noprelistbreak#*
\normalbottomsection#*
\normalcaption#*
\normalcaptionwidth#*
\normalrulethickness
\normalsubcaption#*
\notedivision#*
\noteidinnotes{number}{id}#*
\noteinnotes{number}#*
\notenuminnotes{number}#*
\notenumintext{number}#*
\notepageref#*
\notesname#*
\nouppercaseheads#*
\nthNamei#*
\nthNameii#*
\nthNameiii#*
\nthNameiv#*
\nthNameix#*
\nthNamel#*
\nthNamelx#*
\nthNamelxx#*
\nthNamelxxx#*
\nthNameo#*
\nthNamev#*
\nthNamevi#*
\nthNamevii#*
\nthNameviii#*
\nthNamexc#*
\nthNamexii#*
\nthNamexl#*
\nthNamexx#*
\nthNamexxx#*
\nthstring#*
\numberlinebox{length}{code}#*
\numberlinehook{number}#*
\NumberPoemTitle#*
\numdigits{number}#*
\NumToName{number}#*
\numtoName{number}#*
\numtoname{number}#*
\oarg{arg}
\onecolglossary#*
\onecolindex#*
\onecoltocetc#*
\OnehalfSpacing#*
\OnehalfSpacing*#*
\onelineskip
\openany#*
\openinputfile{file}{stream}#*
\openleft#*
\openoutputfile{file}{stream}#*
\openright#*
\ordinal{number}#*
\OrdinalToName{number}#*
\ordinaltoName{number}#*
\ordinaltoname{number}#*
\ordscript{chars}#*
\ordstring#S
\overridescapmargin{margin%l}#*
\pageai#*
\pageaii#*
\pageaiii#*
\pageaiv#*
\pageao#*
\pageav#*
\pageavi#*
\pageavii#*
\pagebi#*
\pagebii#*
\pagebiii#*
\pagebiv#*
\pagebo#*
\pagebroadsheet#*
\pagebv#*
\pagebvi#*
\pagebvii#*
\pagecrownvo#*
\pagedbill#*
\pagedemyvo#*
\pageexecutive#*
\pagefoolscapvo#*
\pageimperialvo#*
\pageinnotes{page number}#*
\pagelargecrownvo#*
\pagelargepostvo#*
\pageledger#*
\pagelegal#*
\pageletter#*
\pagemcrownvo#*
\pagemdemyvo#*
\pagemediumvo#*
\pagemlargecrownvo#*
\pagemsmallroyalvo#*
\pagename#*
\pagenote#*
\pagenoteanchor{arg}#*
\pagenotehyperanchor{arg}#*
\pagenotesubhead{chapapp}{number}{title%text}#*
\pagenotesubheadstarred{chapapp}{number}{title%text}#*
\pagenumbering*{numstyle%keyvals}
\pageold#*
\pagepostvo#*
\pagepottvo#*
\pagerefname#*
\pageroyalvo#*
\pagesmalldemyvo#*
\pagesmallroyalvo#*
\pagestatement#*
\pagesuperroyalvo#*
\pagetofootnote#*
\paragraph[toc-title%text][head-title%text]{title}#L5
\paragraphfootnotes#*
\paragraphfootstyle{style}#*
\paraheadstyle#*
\parahook#*
\paraindent#*L
\parg{arg}
\parnopar#*
\parsepi#*
\parsepii#*
\partblankpage#*
\partmark{code}#*
\partnamefont#*
\partnamenum#*
\partnumberline{number}#*
\partnumberlinebox{length}{code}#*
\partnumberlinehook{number}#*
\partnumfont#*
\partopsepii#*
\partopsepiii#*
\partpageend#*
\partrefname#*
\parttitlefont#*
\pfbreak#*
\pfbreak*#*
\pfbreakdisplay{text}#*
\pfbreakOutput#*
\pfbreakskip#*
\phantomsection#*
\plainbreak{number}#*
\plainfancybreak{space}{number}{text}#*
\plainfootnotes#*
\plainfootstyle{series}#*
\PlainPoemTitle#*
\pmemlabel{label}#*
\pmemlabelref{key}#*
\pmname#*
\pnchap#*
\pnschap#*
\PoemTitle{title}#*
\PoemTitle[for toc%text]{title}#*
\PoemTitle[for toc%text][for head%text]{title}#*
\PoemTitle*{title}#*
\PoemTitle*[for toc%text]{title}#*
\PoemTitle*[for toc%text][for head%text]{title}#*
\poemtitle#*
\PoemTitlefont#*
\poemtitlefont#*
\PoemTitleheadstart#*
\poemtitlemark{for head}#*
\PoemTitlenumfont#*
\poemtitlepstyle#*
\poemtitlestarmark{for head}#*
\poemtitlestarpstyle#*
\poemtoc#*
\postauthor{text}#*
\postautotab#*
\postbibhook#*
\postcaption{text}
\postchapterprecis#*
\postdate{text}#*
\postnoteinnotes#*
\postnotetext#*
\posttitle{text}#*
\preauthor{text}#*
\preautotab#*
\prebibhook#*
\precaption{text}
\prechapterprecis#*
\prechapterprecisshift#*
\precisfont#*
\precistocfont#*
\precistocformat#*
\precistoctext{text}#*
\predate{text}#*
\pref{key}#r
\Pref{key}#r
\preglossaryhook#*
\preindexhook#*
\prenoteinnotes#*
\prenotetext#*
\pretitle{text}#*
\printbookname#*
\printbooknum#*
\printbooktitle{title%text}#*
\printchaptername#*
\printchapternonum#*
\printchapternum#*
\printchaptertitle{title%text}#*
\printglossary#*
\printglossary[file]#*
\printindex#*
\printindex[file]#*
\printloftitle{title%text}#*
\printlottitle{title%text}#*
\printpageinnotes{page number}#*
\printpageinnoteshyperref{page number}#*
\printpagenotes#*
\printpagenotes*#*
\printpartname#*
\printpartnum#*
\printparttitle{title%text}#*
\printPoemTitlenonum#*
\printPoemTitlenum#*
\printPoemTitletitle{title%text}#*
\printtime#*
\printtime*#*
\printtoctitle{title%text}#*
\providecounter{counter}#*
\providecounter{counter}[within]#*
\provideenvironment{envname}[args][default]{begdef}{enddef}#*N
\provideenvironment{envname}[args]{begdef}{enddef}#*N
\provideenvironment{envname}{begdef}{enddef}#*N
\providefixedcaption{cmd}{float}#*d
\providefixedcaption[cap-cmd]{cmd}{float}#*d
\providelength{cmd}#*d
\qitem{text}{source%text}#*
\qitemlabel{text}#*
\quarkmarks#*
\raggedbottomsection#*
\raggedrightthenleft#*
\raggedwrap#*
\raggedyright#*
\raggedyright[space%l]#*
\ragrparindent#*
\readaline{stream}#*
\readboxedverbatim{stream}#*
\readboxedverbatim*{stream}#*
\readstream{stream}#*
\readverbatim{stream}#*
\readverbatim*{stream}#*
\refixpagelayout#*
\registrationColour{mark}#*
\renewfixedcaption{cmd}{float}#*
\renewfixedcaption[cap-cmd]{cmd}{float}#*
\renewleadpage*[pagestyle%keyvals]{cmd}{title%text}#*
\renewleadpage*{cmd}{title%text}#*
\renewleadpage[pagestyle%keyvals]{cmd}{title%text}#*
\renewleadpage{cmd}{title%text}#*
\reparticle#*
\reportnoidxfile#*
\RequireAtEndClass{class}{code}#*
\RequireAtEndPackage{package}{code}#*
\resetbvlinenumber#*
\restoreapp#*
\restorefromonecol#*
\restorepagenumber#*
\restoretrivseps#*
\russianpar#*
\savepagenumber#*
\savetrivseps#*
\saythanks#*
\secheadstyle#*
\sechook#*
\secindent#*L
\section[toc-title%text][head-title%text]{title}#L2
\sectionname#S
\sectionrefname#*
\see{text}{page number}#*
\seealso{text}{page number}#*
\seename#*
\semiisopage#*
\semiisopage[spine%l]#*
\setafterparaskip{skip%l}#*
\setaftersecskip{skip%l}#*
\setaftersubparaskip{skip%l}#*
\setaftersubsecskip{skip%l}#*
\setaftersubsubsecskip{skip%l}#*
\setarrayelement{array name}{index}{text}#*
\setbeforeparaskip{skip%l}#*
\setbeforesecskip{skip%l}#*
\setbeforesubparaskip{skip%l}#*
\setbeforesubsecskip{skip%l}#*
\setbeforesubsubsecskip{skip%l}#*
\setbiblabel{style}#*
\setbinding{length}#*
\setbvlinenums{first}{start at}#*
\setcftvspacecmd{macro}#*
\setcolsepandrule{colsep%l}{thickness}#*
\setDisplayskipStretch{factor}#*
\setfillsize{T}{C}{L}{R}{r}#*
\setfloatadjustment{float name}{code}#*
\setFloatBlockFor{sectional name}#*
\setfloatlocations{float}{locs}#*
\setFloatSpacing{factor}#*
\setfootins{length normal}{length minipage}#*
\setfootnoterule{vfill}{uplift}{width}{thickness}#*
\sethangfrom{code}#*
\setheaderspaces{headdrop%l}{headsep%l}{ratio}#*
\setheadfoot{headheight%l}{footskip%l}#*
\setlrmargins{spine%l}{edge%l}{ratio}#*
\setlrmarginsandblock{spine%l}{edge%l}{ratio}#*
\setlxvchars#*
\setlxvchars[fontspec]#*
\setmarginfloatcaptionadjustment{float}{code}#*
\setmarginnotes{separation%l}{width}{psuh%l}#*
\setmpbools#*
\setmpjustification{left}{right}#*
\setnzplist#*
\setpagebl{height}{width}{ratio}#*
\setpagebm{height}{width}{ratio}#*
\setpagebr{height}{width}{ratio}#*
\setpagecc{height}{width}{ratio}#*
\setpagemm{height}{width}{ratio}#S
\setpageml{height}{width}{ratio}#*
\setpagemr{height}{width}{ratio}#*
\setPagenoteSpacing{factor}#*
\setpagetl{height}{width}{ratio}#*
\setpagetm{height}{width}{ratio}#*
\setpagetr{height}{width}{ratio}#*
\setparaheadstyle{font}#*
\setparahook{text}#*
\setparaindent{length}#*
\setpnumwidth{length}#*
\setrectanglesize{height}{width}{ratio}#*
\setrmarg{length}#*
\setsecheadstyle{font}#*
\setsechook{text}#*
\setsecindent{length}#*
\setsecnumdepth{secname%keyvals}#*
#keyvals:\setsecnumdepth
book
part
chapter
section
subsection
subsubsection
paragraph
subparagraph
all
none
#endkeyvals
\setsecnumformat{code}#*
\setsidebarheight{height}#*
\setsidebars{hsep}{width}{vsep}{topsep}{font}{height}#*
\setsidecappos{pos}#*
\setsidecaps{sep}{width}#*
\setsidefeet{hsep}{width}{vsep}{adj}{font}{height}#*
\setsidefootheight{height}#*
\setSingleSpace{factor}#*
\setSpacing{factor}#*
\setspbools#*
\setspcode#*
\setstocksize{height}{width}#*
\setsubparaheadstyle{font}#*
\setsubparahook{text}#*
\setsubparaindent{length}#*
\setsubsecheadstyle{font}#*
\setsubsechook{text}#*
\setsubsecindent{length}#*
\setsubsubsecheadstyle{font}#*
\setsubsubsechook{text}#*
\setsubsubsecindent{length}#*
\setthesection#*
\settocdepth{secname}#*
\settocdepth*{secname}#*
\settocpreprocessor{type}{code}#*
\settrimmedsize{height}{width}{ratio}#*
\settrims{top}{foredge}#*
\settypeblocksize{height}{width}{ratio}#*
\settypeoutlayoutunit{unit}#*
\setulmargins{upper%l}{lower%l}{ratio}#*
\setulmarginsandblock{upper%l}{lower%l}{ratio}#*
\setupcomment#*
\setverbatimfont{font}#*
\setverselinenums{first}{start at}#*
\setxlvchars#*
\setxlvchars[fontspec]#*
\shortsubcaption#*
\showheadfootlocoff#*
\showheadfootlocon#*
\showindexmarks#*
\showtextblocklocoff#*
\showtextblocklocon#*
\showtrimsoff#*
\showtrimson#*
\sidebar{text}#*
\sidebarfont#*
\sidebarform#*
\sidebarhsep#*
\sidebarmargin{margin%l}#*
\sidebartopsep#*
\sidebarvsep#*
\sidebarwidth#*
\sidecapfloatwidth#*
\sidecapmargin{margin%l}#*
\sidecapraise#*
\sidecapsep#*
\sidecapsep#*
\sidecapstyle#*
\sidecapwidth#*
\sidecontents#*
\sidefootadjust#*
\sidefootcontents#*
\sidefootfootmark#*
\sidefootform#*
\sidefootheight#*
\sidefoothsep#*
\sidefootins#*
\sidefootmargin{margin%l}#*
\sidefootmarksep#*
\sidefootmarkstyle{code}
\sidefootmarkwidth#*
\sidefootnote{text}#*
\sidefootnote[num]{text}#*
\sidefootnotemark#*
\sidefootnotemark[num]#*
\sidefootnotetext{text}#*
\sidefootnotetext[num]{text}#*
\sidefootparindent#*
\sidefootscript#*
\sidefoottextfont#*
\sidefootvsep#*
\sidefootwidth#*
\sideins#*
\sidepar#*
\sideparfont#*
\sideparform#*
\sideparmargin{margin%l}#*
\sideparvshift#*
\SingleSpacing#*
\slashfrac{top}{bottom}
\slashfracstyle{fraction}#*
\sloppybottom#*
\sourceatright{text}#*
\sourceatright[length]{text}#*
\sourceflush#*
\specialindex{file}{counter}{stuff}#*
\spinemargin#*
\Sref{key}#r
\stanzaskip#*
\startnoteentry#S
\startnoteentrystart{arg1}{arg2}{arg3}{arg4}#S
\stockai#*
\stockaii#*
\stockaiii#*
\stockaiv#*
\stockao#*
\stockav#*
\stockavi#*
\stockavii#*
\stockbi#*
\stockbii#*
\stockbiii#*
\stockbiv#*
\stockbo#*
\stockbroadsheet#*
\stockbv#*
\stockbvi#*
\stockbvii#*
\stockcrownvo#*
\stockdbill#*
\stockdemyvo#*
\stockexecutive#*
\stockfoolscapvo#*
\stockimperialvo#*
\stocklargecrownvo#*
\stocklargepostvo#*
\stockledger#*
\stocklegal#*
\stockletter#*
\stockmcrownvo#*
\stockmdemyvo#*
\stockmediumvo#*
\stockmlargecrownvo#*
\stockmsmallroyalvo#*
\stockold#*
\stockpostvo#*
\stockpottvo#*
\stockroyalvo#*
\stocksmalldemyvo#*
\stocksmallroyalvo#*
\stockstatement#*
\stocksuperroyalvo#*
\strictpagecheck#*
\stringtoarray{array name}{string}#*
\subbottom{text}
\subbottom[short text%text]{text}
\subbottom[short text%text][subtitle%text]{text}
\subcaption{text}
\subcaption[short text%text]{text}
\subcaptionfont{font}#*
\subcaptionlabelfont{font}#*
\subcaptionref{key}#r
\subcaptionsize{size}#*
\subcaptionstyle{style}#*
\subconcluded#*
\subfloatbottomskip#*
\subfloatcapmargin#*
\subfloatcapskip#*
\subfloatcaptopadj#*
\subfloatlabelskip#*
\subfloattopskip#*
\subparagraph[toc-title%text][head-title%text]{title}#L6
\subparaheadstyle#*
\subparahook#*
\subparaindent#*
\subsecheadstyle#*
\subsechook#*
\subsecindent#*L
\subsection[toc-title%text][head-title%text]{title}#L3
\subsubsecheadstyle#*
\subsubsechook#*
\subsubsecindent#*
\subsubsection[toc-title%text][head-title%text]{title}#L4
\subtop{text}
\subtop[short text%text]{text}
\subtop[short text%text][subtitle%text]{text}
\symboldef{symbol}{meaning}#*
\symbollabel{arg}#*
\symbolthanksmark#*
\tablerefname#*
\tamark#*
\teennumbername{arg}#*
\teenordinalname{arg}#*
\teenstring#*
\tensnumbername{arg1}{arg2}#*
\tensordinalname{arg1}{arg2}#*
\tensunitsep#*
\textflush#*
\thanksfootmark#*
\thanksgap{gap%l}#*
\thanksheadextra{pre}{post}#*
\thanksmark{n}#*
\thanksmarksep#*L
\thanksmarkseries{format}#*
\thanksmarkstyle{defn}#*
\thanksmarkwidth#*L
\thanksrule#*
\thanksscript{text}#*
\theauthor#*
\thebook#*
\thebvlinectr#S
\thechapter#*
\thechrsinstr#S
\thedate#*
\theHbook#*
\theHchapter#*
\theHpoem#*
\theHpoemline#*
\theHverse#*
\thelastpage#*
\thelastsheet#*
\themaxsecnumdepth#*
\thememfbvline#S
\thememfvsline#S
\thepagenote#*
\thepagenoteshadow#S
\thepoem#*
\thepoemline#*
\thesheetsequence#*
\thesidefootnote#*
\thesidempfn#S
\thestoredpagenumber#S
\thetitle#*
\theverse#*
\thevslineno#S
\threecolumnfootnotes#*
\threecolumnfootstyle{series}#*
\tiethstring#*
\tightlist#*
\tightlists#*
\tightsubcaptions#*
\titleref{key}#r
\titleref*{key}#r
\titlingpageend#*
\tmarkbl#*
\tmarkbm#*
\tmarkbr#*
\tmarkml#*
\tmarkmr#*
\tmarktl#*
\tmarktm#*
\tmarktr#*
\tocbaseline#*
\tocentryskip#*
\tocheadstart#*
\tocmark#*
\tocnameref#*
\tocskip{skip%l}#*
\topsepi#*
\topsepii#*
\topsepiii#*
\traditionalparskip#*
\tref{key}#r
\trimedge#*
\trimFrame#*
\trimLmarks#*
\trimmark#*
\trimmarks#*
\trimmarkscolor#*
\trimNone#*
\trimtop#*
\trimXmarks#*
\twocolglossary#*
\twocolindex#*
\twocoltocetc#*
\twocolumnfootnotes#*
\twocolumnfootstyle{series}#*
\typeoutlayout#*
\typeoutstandardlayout#*
\ucminusname#*
\undodrop#*
\unitnumbername{number}#*
\unitordinalname{number}#*
\unletcounter{counter}#*
\unnamedsubappendices#*
\uppercaseheads#*
\uppermargin#*
\usethanksrule#*
\verbfootnote#*
\verselinebreak#*
\verselinebreak[length]#*
\verselinenumbersleft#*
\verselinenumbersright#*
\versewidth#*
\vgap#*
\vin#*
\vindent#*
\vinphantom{text}#*
\vleftmargin#*
\vleftofline{text}#*
\vleftskip#*
\vlvnumfont#*
\vrightskip#*
\xindyindex#*
\xlvchars#*
\zerotrivseps#*

#keyvals:\pagenumbering*#c
arabic
roman
Roman
alph
Alph
#endkeyvals

#keyvals:\pagestyle#c,\thispagestyle#c,\addtopsmarks#c,\aliaspagestyle#c,\copypagestyle#c,\makeevenfoot#c,\makeevenhead#c,\makefootrule#c,\makeheadfootruleprefix#c,\makeheadfootstrut#c,\makeheadfootvposition#c,\makeheadposition#c,\makeheadrule#c,\makeoddfoot#c,\makeoddhead#c,\makepsmarks#c,\makerunningfootwidth#c,\makerunningheadwidth#c,\makerunningwidth#c,\makerunningwidth#c,\memleadpageinfo#c,\memleadpagestarinfo#c,\newleadpage#c,\newleadpage*#c,\renewleadpage#c,\renewleadpage*#c
plain
empty
headings
myheadings
simple
ruled
Ruled
companion
book
chapter
cleared
part
title
titlingpage
%pagestyle
#endkeyvals

# deprecated
\addtodef{cmd}{prepend}{append}#S
\addtodef*{cmd}{prepend}{append}#S
\addtoiargdef{cmd}{prepend}{append}#S
\addtoiargdef*{cmd}{prepend}{append}#S
\newloglike{cmd}{string}#Sd
\newloglike*{cmd}{string}#Sd
\patchcmdError{arg1}{arg2}#S
\patchcommand{cmd}{start code}{end code}#S
\provideloglike{cmd}{string}#Sd
\tabsoff#S
\tabson#S
\setverbatimbreak#S
\verbatimbreakchar#S
\wrappingoff#S
\wrappingon#S
\wrapright#S
