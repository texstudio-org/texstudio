# langscibook class
# Matthew Bertucci 2023/02/12 for v2023-02-08

#include:xetex
#include:silence
#include:etoolbox
#include:langsci-affiliations
#include:xspace
#include:kvoptions
#include:class-scrbook
#include:xstring
#include:graphicx
#include:hyphenat
#include:tikz
#include:tikzlibrarypositioning
#include:tikzlibrarycalc
#include:url
#include:calc
#include:geometry
#include:ifxetex
#include:amssymb
#include:amsmath
#include:unicode-math
#include:metalogo
#include:microtype
#include:xcolor
#include:pst-barcode
#include:datetime
#include:scrlayer-scrpage
#include:epigraph
#include:babel
# loads english option of babel
#include:biblatex
# loads style=langsci-unified and natbib=true options of biblatex
#include:floatrow
#include:rotating
#include:booktabs
#include:setspace
#include:caption
#include:index
#include:hyperref
#include:bookmark
#include:chngcntr
# inputs langsci-series.def

#keyvals:\documentclass/langscibook#c
arabicfont
babelshorthands
biblatex
biblatexbackend=#bibtex,bibtex8,biber
booklanguage=%<language%>
chinesefont
classicfloatnumbers
collection
collectiontoclong
copyright=%<copyright%>
decapbib
draftmode
hebrewfont
japanesefont
koreanfont
minimal
multiauthors
newtxmath
nobabel
nonewtxmath
oldstylenumbers
openreview
output=#book,paper,minimal,guidelines
proofs
showindex
smallfont
spinewidth=##L
syriacfont
tblseight
infn
uniformtopskip
#endkeyvals

#ifOption:arabicfont
#include:langsci-bidi
\arabicfont
\textarab{text%plain}
#endif

#ifOption:babelshorthands
# loads ngerman option of babel
\captionsngerman#*
\datengerman#*
\extrasngerman#*
\noextrasngerman#*
\dq
\ntosstrue#*
\ntossfalse#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
\mdqon#*
\mdqoff#*
#repl:"a ä
#repl:"e ë
#repl:"i ï
#repl:"o ö
#repl:"u ü
#repl:"A Ä
#repl:"E Ë
#repl:"I Ï
#repl:"O Ö
#repl:"U Ü
#repl:"s ß
#repl:"z ß
#repl:"S SS
#repl:"Z SZ
#repl:"|
#repl:"= -
#repl:"~ -
#repl:""
#repl:"/ /
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »
#endif

#ifOption:booklanguage=chinese
#include:xeCJK
#endif

#ifOption:booklanguage=french
\frenchsetup{options%keyvals}
\frenchbsetup{options%keyvals}#*
#keyvals:\frenchsetup,\frenchbsetup
ShowOptions#true,false
StandardLayout#true,false
GlobalLayoutFrench#true,false
IndentFirst#true,false
PartNameFull#true,false
ListItemsAsPar#true,false
StandardListSpacing#true,false
StandardItemizeEnv#true,false
StandardEnumerateEnv#true,false
StandardItemLabels#true,false
ItemLabels=
ItemLabeli=
ItemLabelii=
ItemLabeliii=
ItemLabeliv=
StandardLists#true,false
ListOldLayout#true,false
FrenchFootnotes#true,false
AutoSpaceFootnotes#true,false
AutoSpacePunctuation#true,false
ThinColonSpace#true,false
OriginalTypewriter#true,false
UnicodeNoBreakSpaces#true,false
og=
fg=
INGuillSpace#true,false
EveryParGuill=#open,close,none
EveryLineGuill=#open,close,none
InnerGuillSingle#true,false
ThinSpaceInFrenchNumbers#true,false
SmallCapsFigTabCaptions#true,false
CustomiseFigTabCaptions#true,false
OldFigTabCaptions#true,false
FrenchSuperscripts#true,false
LowercaseSuperscripts#true,false
SuppressWarning#true,false
#endkeyvals
\AddThinSpaceBeforeFootnotes#*
\alsoname#*
\at
\AutoSpaceBeforeFDP#*
\begin{descriptionFB}
\begin{enumerateFB}
\begin{itemizeFB}
\begin{listFB}{symbol}
\begin{listORI}{symbol}#*
\boi
\bsc{text}
\CaptionSeparator#*
\captionsfrench
\ccname#*
\chaptername#*
\circonflexe
\dateacadian#*
\datefrench
\DecimalMathComma
\degre#*
\degres
\descindentFB#*
\dotFFN#*
\enclname#*
\end{descriptionFB}
\end{enumerateFB}
\end{itemizeFB}
\end{listFB}
\end{listORI}#*
\extrasfrench
\FBcolonspace
\FBdatebox#*
\FBdatespace#*
\FBeverylineguill#*
\FBfigtabshape#*
\FBfnindent#*
\FBFrenchFootnotesfalse#*
\FBFrenchFootnotestrue#*
\FBFrenchSuperscriptstrue#*
\FBGlobalLayoutFrenchtrue#*
\FBgspchar#*
\FBguillopen#*
\FBguillspace
\FBInnerGuillSinglefalse#*
\FBInnerGuillSingletrue#*
\FBListItemsAsParfalse#*
\FBListItemsAsPartrue#*
\FBLowercaseSuperscriptstrue#*
\FBmedkern#*
\FBPartNameFulltrue#*
\FBsetspaces[language]{type}{width}{stretch}{shrink}#*
\FBsetspaces{type}{width}{stretch}{shrink}#*
\FBSmallCapsFigTabCaptionstrue#*
\FBStandardEnumerateEnvtrue#*
\FBStandardItemizeEnvtrue#*
\FBStandardItemLabelstrue#*
\FBStandardLayouttrue#*
\FBStandardListSpacingtrue#*
\FBStandardListstrue#*
\FBsupR#*
\FBsupS#*
\FBtextellipsis#*
\FBthickkern#*
\FBthinspace
\FBthousandsep#*
\FBWarning{message%text}#*
\fg
\fgi#*
\fgii#*
\fprimo)
\frenchdate{day}{month}{year}
\FrenchEnumerate{arg}#*
\FrenchFootnotes#*
\FrenchLabelItem#*
\frenchpartfirst#*
\frenchpartsecond#*
\FrenchPopularEnumerate{arg}#*
\frenchtoday
\Frlabelitemi#*
\Frlabelitemi#*
\Frlabelitemii#*
\Frlabelitemii#*
\Frlabelitemiii#*
\Frlabelitemiii#*
\Frlabelitemiv#*
\Frlabelitemiv#*
\frquote{text}
\fup{text}
\glossaryname#*
\headtoname#*
\ieme
\iemes
\ier
\iere
\ieres
\iers
\ifFBAutoSpaceFootnotes#*
\ifFBCompactItemize#*
\ifFBCustomiseFigTabCaptions#*
\ifFBfrench#*
\ifFBFrenchFootnotes#*
\ifFBFrenchSuperscripts#*
\ifFBGlobalLayoutFrench#*
\ifFBIndentFirst#*
\ifFBINGuillSpace#*
\ifFBListItemsAsPar#*
\ifFBListOldLayout#*
\ifFBLowercaseSuperscripts#*
\ifFBLuaTeX#*
\ifFBOldFigTabCaptions#*
\ifFBOriginalTypewriter#*
\ifFBPartNameFull#*
\ifFBReduceListSpacing#*
\ifFBShowOptions#*
\ifFBSmallCapsFigTabCaptions#*
\ifFBStandardEnumerateEnv#*
\ifFBStandardItemizeEnv#*
\ifFBStandardItemLabels#*
\ifFBStandardLayout#*
\ifFBStandardLists#*
\ifFBStandardListSpacing#*
\ifFBSuppressWarning#*
\ifFBThinColonSpace#*
\ifFBThinSpaceInFrenchNumbers#*
\ifFBunicode#*
\ifFBXeTeX#*
\ifLaTeXe#*
\kernFFN#*
\labelindentFB#*
\labelwidthFB#*
\leftmarginFB#*
\listfigurename#*
\listindentFB#*
\No
\no
\NoAutoSpaceBeforeFDP#*
\NoAutoSpacing
\NoEveryParQuote#*
\noextrasfrench
\nombre{arg}#*
\nos
\Nos
\og
\ogi#*
\ogii#*
\pagename#*
\parindentFFN#*
\partfirst#*
\partfirst#*
\partnameord#*
\partsecond#*
\partsecond#*
\prefacename#*
\primo
\proofname#*
\quarto
\rmfamilyFB#*
\secundo
\seename#*
\sffamilyFB#*
\StandardFootnotes#*
\StandardMathComma
\tertio
\tild
\ttfamilyFB#*
\up{text}
\xspace
#endif

#ifOption:booklanguage=german
\captionsgerman#*
\dategerman#*
\extrasgerman#*
\noextrasgerman#*
\dq
\tosstrue#*
\tossfalse#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
\mdqon#*
\mdqoff#*
\ck#*
#repl:"a ä
#repl:"e ë
#repl:"i ï
#repl:"o ö
#repl:"u ü
#repl:"A Ä
#repl:"E Ë
#repl:"I Ï
#repl:"O Ö
#repl:"U Ü
#repl:"s ß
#repl:"z ß
#repl:"ck ck
#repl:"ff ff
#repl:"ll ll
#repl:"mm mm
#repl:"nn nn
#repl:"pp pp
#repl:"rr rr
#repl:"tt tt
#repl:"FF FF
#repl:"LL LL
#repl:"MM MM
#repl:"NN NN
#repl:"PP PP
#repl:"RR RR
#repl:"TT TT
#repl:"S SS
#repl:"Z SZ
#repl:"|
#repl:"= -
#repl:"~ -
#repl:""
#repl:"/ /
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »
#endif

#ifOption:chinesefont
\cn
#endif

#ifOption:hebrewfont
\hebrewfont
#endif

#ifOption:japanesefont
\jpn
#endif

#ifOption:koreanfont
\krn
#endif

#ifOption:newtxmath
#include:newtxmath
#endif

#ifOption:proofs
#include:lineno
#endif

#ifOption:showindex
#include:soul
\isold{entry}#S
\ilold{entry}#S
\iaold{entry}#S
#endif

#ifOption:syriacfont
\syriacfont
#endif

#ifOption:tblseight
\cn
#endif

#ifOption:uniformtopskip
\lsSaveValueTopSkip#*
\lsSaveValueTextTop#*
\lsSaveValueTextBottom#*
\restorebottom#*
\sloppybottom#*
#endif

# langscibook class commands
\abstract{text}
\AdditionalFontImprint{font name}#*
\affiliation{affiliation}
\appendixsection{title}
\appendixsectionformat#*
\appendixsectionmarkformat#*
\appendixsubsection{title}
\authorToBib
\BackBody{text}
\backcover*{width}
\backcover{width}
\BackTitle{text}
\begin{modquote}
\begin{modquote}[width]
\begin{paperappendix}
\bleed#*
\BookDOI{DOI}
\ccby#*
\ccbynd#*
\ccbysa#*
\chapref{label}#r
\ChapterDOI{DOI}
\chaptersubtitle{text}
\coverbottomtext
\coverbottomtext[color]
\covergeometry{margin%l}{height}{width}
\coversetup
\eachwordone#*
\end{modquote}
\end{paperappendix}
\epigram{text}
\epigramsource{source}
\figref{label}#r
\fontstemp#S
\footnoteindex{arg1}{arg2}#*
\frontcovertoptext[color]{width}{fontsize%l}
\frontcovertoptext{width}{fontsize%l}
\githubtext#*
\ia{author entry}
\iai{author entry}
\iasa{entry}{seealso}
\igobble{arg}#*
\il{language entry}
\ili{language entry}
\illustrator{name}
\ilsa{entry}{seealso}
\includechapterfooterlogo#*
\includepaper{file}#i
\includepublisherlogo#*
\includespinelogo#*
\includestoragelogo#*
\infn{page}{text}
\is{subject entry}
\ISBNdigital{ISBN}
\ISBNhardcover{ISBN}
\ISBNsoftcover{ISBN}
\ISBNsoftcoverus{ISBN}
\isi{subject entry}
\issa{entry}{seealso}
\langsciseealso#*
\logotext#*
\lsAbbreviationsTitle#*
\lsAcknowledgementTitle#*
\lsAdditionalFontsImprint#*
\lsBackBody#*
\lsBackBodyFont#*
\lsBackPage#*
\lsBackTitle#*
\lsBackTitleFont#*
\lsBiblatexBackend#*
\lsBookDOI#*
\lsBookLanguage#*
\lsBookLanguageChinese#*
\lsBookLanguageEnglish#*
\lsBookLanguageFrench#*
\lsBookLanguageGerman#*
\lsBookLanguagePortuguese#*
\lsBookLanguageSpanish#*
\lsChapterDOI#*
\lsChapterFooterSize#*
\lsCollectionEditor#*
\lsCollectionMetadataToBibliography{bibdata}#*
\lsCollectionPaperAbstract#*
\lsCollectionPaperAuthor#*
\lsCollectionPaperCitation#*
\lsCollectionPaperCitationText#*
\lsCollectionPaperFirstPage#*
\lsCollectionPaperFooterTitle#*
\lsCollectionPaperHeaderTitle#*
\lsCollectionPaperLastPage#*
\lsCollectionTitle#*
\lsConditionalSetupForPaper#*
\lsConditionalSetupForPaper[bib resource]#*
\lsCopyright#*
\lsCoverAuthorFont#*
\lsCoverBlockColor#*
\lsCoverFontColor#*
\lsCoverSeriesFont#*
\lsCoverSeriesHistoryFont#*
\lsCoverSubTitleFont#*
\lsCoverTitleFont{font commands}#*
\lsCoverTitleFontBaselineskip#*
\lsCoverTitleFontSize#*
\lsCoverTitleSizes{fontsize%l}{baselineskip%l}#*
\lsDedication#*
\lsDedicationFont#*
\lsDetermineMultiauthors#*
\lsEditorPrefix#*
\lsEditorSuffix#*
\lsFontsize#*
\lsFrontPage#*
\lsID#*
\lsImpressum#*
\lsImpressumCitationText#*
\lsImpressumExtra#*
\lsIndexTitle#*
\lsInsideFont#*
\lsISBNcover#*
\lsISBNdigital#*
\lsISBNhardcover[addon]{ISBN}
\lsISBNhardcoverTwoDigitAddon#*
\lsISBNsoftcover#*
\lsISBNsoftcoverus#*
\lsISSN#*
\lsISSNelectronic#*
\lsISSNprint#*
\lsLanguageIndexTitle#*
\lsLicenseInformation{copyright}#*
\lsNameIndexTitle#*
\lsOutput#*
\lsOutputBook#*
\lsOutputCoverBODhc#*
\lsOutputCoverBODsc#*
\lsOutputCoverCS#*
\lsOutputGuidelines#*
\lsOutputPaper#*
\lsp#*
\lsPageStyleEmpty#*
\lsPrefaceTitle#*
\LSPTmp#*
\lsReferencesTitle#*
\lsSaveValueTextBottom#*
\lsSaveValueTextTop#*
\lsSaveValueTopSkip#*
\lsSchmutztitel#*
\lsSeeAlsoTerm
\lsSeries#*
\lsSeriesHistory#*
\lsSeriesHistoryWheel[maxitems]{items}#*
\lsSeriesHistoryWheel{items}#*
\lsSeriesNumber#*
\lsSeriesText#*
\lsSpineAuthor#*
\lsSpineAuthorFont#*
\lsSpineTitle#*
\lsSpineTitleFont#*
\lsSpinewidth#*
\lsSubjectIndexTitle#*
\lsURL#*
\lsYear#*
\name[index entry]{first name}{last name}
\name{first name}{last name}
\newlineCover#*
\newlineSpine#*
\newlineTOC#*
\normalparindent#*
\openreviewer{name}
\paperhivetext#*
\papernote{text}
\partref{label}#r
\proofreader{name}
\publisherstreetaddress#*
\publisherurl#*
\sectref{label}#r
\seealso{text}{page number}
\seitenbreite#*
\seitenhoehe#*
\Series{series}
\SeriesNumber{number}
\setuptitle#*
\shorttitlerunninghead{text}
\SpineAuthor{author}
\SpineTitle{text}
\spinewidth#*
\storageinstitution#*
\subsubsubsection*{title}#L5
\subsubsubsection[short title]{title}#L5
\subsubsubsection{title}#L5
\subsubsubsectionmark{code}
\subsubsubsubsection*{title}#L6
\subsubsubsubsection[short title]{title}#L6
\subsubsubsubsection{title}#L6
\subsubsubsubsectionmark{code}
\tabref{label}#r
\tblseight#*
\tempnumber#S
\theappendixsection#*
\titleTemp#*
\titleToHead#*
\titleToToC#*
\totalheight#*
\totalwidth#*
\translator{name}
\typesetter{name}
\URL{URL}#U
\xelatex

# from english option of babel
\captionsenglish#*
\dateenglish#*
\extrasenglish#*
\noextrasenglish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*

lsLightBlue#B
lsMidBlue#B
lsMidDarkBlue#B
lsDarkBlue#B
lsNightBlue#B
lsYellow#B
lsLightOrange#B
lsMidOrange#B
lsDarkOrange#B
lsRed#B
lsLightWine#B
lsMidWine#B
lsDarkWine#B
lsSoftGreen#B
lsLightGreen#B
lsMidGreen#B
lsRichGreen#B
lsDarkGreenOne#B
lsDarkGreenTwo#B
lsNightGreen#B
lsLightGray#B
lsGuidelinesGray#B
lsDOIGray#B
RED#B
langscicol1#B
langscicol2#B
langscicol3#B
langscicol4#B
langscicol5#B
langscicol6#B
langscicol7#B
langscicol8#B
langscicol9#B
langscicol10#B
langscicol11#B
langscicol12#B
langscicol13#B
langscicol14#B
langscicol15#B
langscicol16#B
langscicol17#B
langscicol18#B
langscicol19#B
langscicol20#B

## from style=langsci-unified option of biblatex
# from langsci-unified.bbx
\mkbibdateunified{year}{month}{day}#*
# from langsci-unified.cbx
\citetv[prenote][postnote]{bibid}#C
\citetv[postnote]{bibid}#C
\citetv{bibid}#C
\textcitetv[prenote][postnote]{bibid}#C
\textcitetv[postnote]{bibid}#C
\textcitetv{bibid}#C
\parencitetv[prenote][postnote]{bibid}#C
\parencitetv[postnote]{bibid}#C
\parencitetv{bibid}#C
\fullciteFooter[prenote][postnote]{bibid}#C
\fullciteFooter[postnote]{bibid}#C
\fullciteFooter{bibid}#C
\fullciteImprint[prenote][postnote]{bibid}#C
\fullciteImprint[postnote]{bibid}#C
\fullciteImprint{bibid}#C
\CiteFullAuthorList[prenote][postnote]{bibid}#C
\CiteFullAuthorList[postnote]{bibid}#C
\CiteFullAuthorList{bibid}#C
\posscitet[prenote][postnote]{bibid}#C
\posscitet[postnote]{bibid}#C
\posscitet{bibid}#C
\posscitealt[prenote][postnote]{bibid}#C
\posscitealt[postnote]{bibid}#C
\posscitealt{bibid}#C
\possciteauthor[prenote][postnote]{bibid}#C
\possciteauthor[postnote]{bibid}#C
\possciteauthor{bibid}#C

# from natbib=true option of biblatex
\citet[prenote][postnote]{bibid}#C
\citet[postnote]{bibid}#C
\citet{bibid}#C
\citet*[prenote][postnote]{bibid}#C
\citet*[postnote]{bibid}#C
\citet*{bibid}#C
\citep[prenote][postnote]{bibid}#C
\citep[postnote]{bibid}#C
\citep{bibid}#C
\citep*[prenote][postnote]{bibid}#C
\citep*[postnote]{bibid}#C
\citep*{bibid}#C
\citealt[prenote][postnote]{bibid}#C
\citealt[postnote]{bibid}#C
\citealt{bibid}#C
\citealt*[prenote][postnote]{bibid}#C
\citealt*[postnote]{bibid}#C
\citealt*{bibid}#C
\citealp[prenote][postnote]{bibid}#C
\citealp[postnote]{bibid}#C
\citealp{bibid}#C
\citealp*[prenote][postnote]{bibid}#C
\citealp*[postnote]{bibid}#C
\citealp*{bibid}#C
\citeauthor[prenote][postnote]{bibid}#C
\citeauthor[postnote]{bibid}#C
\citeauthor{bibid}#C
\citeauthor*[prenote][postnote]{bibid}#C
\citeauthor*[postnote]{bibid}#C
\citeauthor*{bibid}#C
\citeyearpar[prenote][postnote]{bibid}#C
\citeyearpar[postnote]{bibid}#C
\citeyearpar{bibid}#C
\Citet[prenote][postnote]{bibid}#C
\Citet[postnote]{bibid}#C
\Citet{bibid}#C
\Citet*[prenote][postnote]{bibid}#C
\Citet*[postnote]{bibid}#C
\Citet*{bibid}#C
\Citep[prenote][postnote]{bibid}#C
\Citep[postnote]{bibid}#C
\Citep{bibid}#C
\Citep*[prenote][postnote]{bibid}#C
\Citep*[postnote]{bibid}#C
\Citep*{bibid}#C
\Citealt[prenote][postnote]{bibid}#C
\Citealt[postnote]{bibid}#C
\Citealt{bibid}#C
\Citealt*[prenote][postnote]{bibid}#C
\Citealt*[postnote]{bibid}#C
\Citealt*{bibid}#C
\Citealp[prenote][postnote]{bibid}#C
\Citealp[postnote]{bibid}#C
\Citealp{bibid}#C
\Citealp*[prenote][postnote]{bibid}#C
\Citealp*[postnote]{bibid}#C
\Citealp*{bibid}#C
\citefullauthor[prenote][postnote]{bibid}#C
\citefullauthor[postnote]{bibid}#C
\citefullauthor{bibid}#C
\Citefullauthor[prenote][postnote]{bibid}#C
\Citefullauthor[postnote]{bibid}#C
\Citefullauthor{bibid}#C
\citetext{text}
\defcitealias{bibid}{alias}
\citetalias{bibid}
\citepalias{bibid}

# from langsci-series.def
\ahl#*
\algad#*
\calseries#*
\cam#*
\cfls#*
\cib#*
\classics#*
\cmle#*
\cogl#*
\dummyseries#*
\eotms#*
\eotmsig#*
\eurosla#*
\ela#*
\guidelines#*
\hpls#*
\loc#*
\lsSeriesColor#*
\lsSeriesFontColor#*
\lsSeriesTitle#*
\lv#*
\mi#*
\nc#*
\ogl#*
\ogs#*
\orl#*
\osl#*
\pmwe#*
\rcg#*
\scl#*
\sidl#*
\silp#*
\tbls#*
\tgdi#*
\tmnlp#*
\tpd#*
