# lwarp package
# Matthew Bertucci 2022/11/22 for v0.909

#include:iftex
#include:ifpdf
#include:ifptex
#include:etoolbox
#include:xpatch
#include:ifplatform
#include:letltxmacro
#include:fontenc
# fontenc loaded with T1 option
#include:inputenc
#include:newunicodechar
#include:upquote
#include:kvoptions
#include:comment
#include:calc
#include:xstring
#include:environ

# loaded for HTML output only
#include:geometry
#include:gettitlestring
#include:everyhook
#include:xifthen
#include:verbatim
#include:refcount
#include:newfloat
#include:printlen
#include:capt-of
#include:cleveref
#include:array

\lwarpsetup{options%keyvals}

#keyvals:\usepackage/lwarp#c,\lwarpsetup
mathsvg
mathjax
latexmk#true,false
dvips#true,false
dvipdfm#true,false
dvipdfmx#true,false
HomeHTMLFilename=%<file name%>
HTMLFilename=%<file prefix%>
ImagesName=%<file prefix%>
ImagesDirectory=%<directory%>
PrintLatexCmd=%<shell command%>
HTMLLatexCmd=%<shell command%>
makeindex#true,false
makeindexStyle=%<.ist file%>
xindy#true,false
xindyStyle=%<.xdy file%>
xindyLanguage=%<language%>
xindyCodepage=%<codepage%>
xindex#true,false
xindexConfig=%<file name%>
PrintIndexCmd=%<shell command%>
HTMLIndexCmd=%<shell command%>
LatexmkIndexCmd=%<shell command%>
IndexRef#true,false
GlossaryCmd=%<shell command%>
OSWindows
pdftotextEnc=%<encoding%>
lwarpmk
warpdisable
warpprint
warpHTML
BaseJobname=%<jobname%>
#endkeyvals

\HTMLFirstPageTop{contents%text}
\HTMLFirstPageBottom{contents%text}
\linkhomename
\linkpreviousname
\linknextname
\theSideTOCDepth
\sidetocname
\theFileDepth
\FilenameLimit
\theFootnoteDepth
\IndexPageSeparator
\IndexRangeSeparator
\CSSFilename{filename.css%file}
\MathJaxFilename{filename%file}
\HTMLLanguage{language tag}
\HTMLTitle{title%text}
\HTMLTitleBeforeSection
\HTMLTitleAfterSection
\HTMLAuthor{author}
\HTMLDescription{description%text}
\HTMLPageTop{contents%text}
\HTMLPageBottom{contents%text}
\LinkHome
\LinkPrevious
\LinkNext
\ImageAltText
\ThisAltText{text}
\MathImageAltText
\PackageDiagramAltText
\AltTextOpen
\AltTextClose
\HTMLnewcolumntype{name}{definition}
\HTMLnewcolumntype{name}[args]{definition}
\HTMLnewcolumntype{name}[args][default]{definition}
\begin{warpprint}
\end{warpprint}
\begin{warpHTML}
\end{warpHTML}
\warpprintonly{contents%text}
\warpHTMLonly{contents%text}
\begin{BlockClass}{css class}
\begin{BlockClass}[style]{css class}
\end{BlockClass}
\InlineClass{css class}{text}
\InlineClass[web css style]{css class}{text}
\InlineClass(wp css style){css class}{text}#*
\InlineClass(wp css style)[web css style]{css class}{text}
\begin{warpall}
\end{warpall}
\begin{warpMathJax}
\end{warpMathJax}
\begin{warpsvg}
\end{warpsvg}
\marginparBlock{right%text}
\marginparBlock[left%text]{right%text}
\UseMinipageWidths 
\IgnoreMinipageWidths
\fboxBlock{text}
\FilenameSimplify{text}
\FilenameSimplify*{text}
\FilenameNullify{macros}
\ForceHTMLPage
\ForceHTMLTOC
\AddSubtitlePublished#*

# various commands emulating packages when not loaded (or otherwise obscure commands)
\arrayrulecolor[model]{color}#*
\arrayrulecolor{color}#*
\arrayrulecolornexttoken[model]{color}#*
\arrayrulecolornexttoken{color}#*
\attribution{text}#*
\BaseJobname#*
\begin{fcolorminipage}#*
\begin{lateximage}#*
\BlockClassSingle{css class}{text}#*
\CaptionSeparator#*
\cdashline#*
\csNewCommandCopycs{dest csname}{source csname}#*
\CustomizeMathJax{macros}#*
\defaddtocounter{name}{value}#*
\displaymathnormal#*
\displaymathother#*
\doublerulesepcolor[model]{color}#*
\doublerulesepcolor{color}#*
\doublerulesepcolornexttoken[model]{color}#*
\doublerulesepcolornexttoken{color}#*
\end{fcolorminipage}#*
\end{lateximage}#*
\firsthdashline#*
\footnotename#*
\fup{text}#*
\hdashline#*
\HomeHTMLFilename#*
\HTMLentity{tag}#*
\HTMLFilename#*
\HTMLunicode{arg1}#*
\hyperindexformat{arg1}{arg2}#*
\hyperindexref{arg}#*
\hypertoc{depth}{type}{name}{page}#*
\hypertocfloat{depth}{type}{ext of parent}{caption}{page}#*
\inlinemathnormal#*
\inlinemathother#*
\lasthdashline#*
\lasthdashline[optarg1]#*
\LateximageFontScale#*
\LateximageFontSizeName#*
\ldelim#*
\LWRabsorbnumber{arg}#*
\LWRabsorboption{arg}#*
\LWRabsorbquotenumber#*
\LWRabsorbtwooptions[opt]{arg}#*
\LWRabsorbtwooptions{arg}#*
\LWRamp#*
\LWRdollar#*
\LWRfootnote#*
\LWRframebox{content%text}#*
\LWRhash#*
\LWRleftbrace#*
\LWRopquote#*
\LWRopseq#*
\LWRorighspace#*
\LWRpercent#*
\LWRPrintStack#*
\LWRref#*
\LWRrightbrace#*
\LWRsetnextfloat{autopage}{float autoID}#*
\LWRtexttitlecase{text}#*
\macrotocsname{macro}#*
\mcolrowcell#*
\midrule{arg1}#*
\minipagefullwidth#*
\morecmidrules#*
\mrowcell#*
\multicolumnrow{cols}{halign}[vpos]{numrows}[bigstruts]{width}[fixup]{text}#*
\multicolumnrow{cols}{halign}{numrows}{width}{text}#*
\NewEnvironmentCopy{dest%envname}{source}#*N
\nexttoken#*
\nohyperpage{arg1}#*
\OSPathSymbol#*
\pagerefPageFor#*
\postbookname#*
\postchaptername#*
\postparagraphname#*
\postpartname#*
\postsectionname#*
\postsubparagraphname#*
\postsubsectionname#*
\postsubsubsectionname#*
\prebookname#*
\prechaptername#*
\preparagraphname#*
\prepartname#*
\presectionname#*
\presubparagraphname#*
\presubsectionname#*
\presubsubsectionname#*
\printauthor#*
\printdate#*
\printpublished#*
\printsubtitle#*
\printthanks#*
\printtitle#*
\rdelim#*
\ResumeTabular#*
\rowcolor#*
\SetHTMLFileNumber{number}#*
\simplechapterdelim#*
\specialrule{arg1}{arg2}{arg3}#*
\StartDefiningMath#*
\StartDefiningTabulars#*
\StopDefiningMath#*
\StopDefiningTabulars#*
\TabularMacro%<\macro%>#*
\texorpdfstring#*
\theauthor#*
\thefootnoteReset
\theHTMLAuthor
\theHTMLSection#*
\theHTMLTitle#*
\theHTMLTitleSection#*
\theHTMLTitleSeparator#*
\thelofdepth
\thelotdepth
\theMathJaxequation#*
\theMathJaxsection#*
\theMathJaxsubequations#*
\thetitle#*
\ThisComment#*
\tmpb#*
\toprule{arg1}#*
\tracinglwarp#*
\up{text}#*
\VerbatimHTMLWidth#*
\FBmedkern#S
\FBthickkern#S
\HTMLleftmargini#S
\HTMLvleftskip#S
\LTcaptype#S

# from T1 option of fontenc
\DH#n
\NG#n
\dj#n
\ng#n
\k{arg}#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\quotedblbase#n
\quotesinglbase#n
\textquotedbl#n
\DJ#n
\th#n
\TH#n
\dh#n
\Hwithstroke#*n
\hwithstroke#*n
\textogonekcentered{arg}#*n
\guillemetleft#n
\guillemetright#n
