# acmart class
# Matthew Bertucci 2023/03/26 for v1.89

#include:xkeyval
#include:xstring
#include:iftex
#include:class-amsart
#include:microtype
#include:etoolbox
#include:booktabs
#include:refcount
#include:totpages
#include:environ
#include:setspace
#include:textcase
#include:natbib
#include:hyperxmp
#include:hyperref
#include:graphicx
#include:xcolor
#include:geometry
#include:manyfoot
#include:cmap
#include:fontenc
# loads T1 option of fontenc
#include:newtxmath
#include:libertine
#include:zi4
#include:caption
#include:float
#include:comment
#include:fancyhdr

#keyvals:\documentclass/acmart#c
format=#manuscript,acmsmall,acmlarge,acmtog,sigconf,sigplan,acmengage,acmcp
manuscript#true,false
acmsmall#true,false
acmlarge#true,false
acmtog#true,false
sigconf#true,false
sigplan#true,false
review#true,false
screen#true,false
natbib#true,false
anonymous#true,false
authorversion#true,false
nonacm#true,false
timestamp#true,false
authordraft#true,false
acmthm#true,false
balance#true,false
pbalance#true,false
urlbreakonhyphens#true,false
8pt
9pt
10pt
11pt
12pt
draft
language=%<language%>
# options passed to amsart class
8pt
a4paper
centertags
e-only
final
fleqn
landscape
leqno
letterpaper
noamsfonts
nomath
notitlepage
onecolumn
oneside
portrait
reqno
tbtags
titlepage
twocolumn
twoside
#endkeyvals

#ifOption:authordraft
#include:draftwatermark
#endif
#ifOption:authordraft=true
#include:draftwatermark
#endif

#ifOption:format=acmtog
#include:balance
#endif
#ifOption:acmtog
#include:balance
#endif
#ifOption:acmtog=true
#include:balance
#endif

#ifOption:format=sigconf
#include:balance
#endif
#ifOption:sigconf
#include:balance
#endif
#ifOption:sigconf=true
#include:balance
#endif

#ifOption:format=sigplan
#include:balance
#endif
#ifOption:sigplan
#include:balance
#endif
#ifOption:sigplan=true
#include:balance
#endif

#ifOption:format=acmcp
#include:framed
#include:zref-savepos
#include:zref-user
#endif
#ifOption:acmcp
#include:framed
#include:zref-savepos
#include:zref-user
#endif
#ifOption:acmcp=true
#include:framed
#include:zref-savepos
#include:zref-user
#endif

#ifOption:pbalance
#include:pbalance
#endif
#ifOption:pbalance=true
#include:pbalance
#endif

\acmJournal{short name%keyvals}

#keyvals:\acmJournal#c
ACMJCSS
CIE
CSUR
DLT
DGOV
DTRAP
FAC
HEALTH
IMWUT
JACM
JATS
JDIQ
JEA
JERIC
JETC
JOCCH
JRC
PACMCGIT
PACMHCI
PACMMOD
PACMNET
PACMPL
POMACS
TAAS
TACCESS
TACO
TALG
TALLIP
TAP
TCPS
TDS
TEAC
TECS
TELO
THRI
TIIS
TIOT
TISSEC
TIST
TKDD
TMIS
TOCE
TOCHI
TOCL
TOCS
TOCT
TODAES
TODS
TOG
TOIS
TOIT
TOMACS
TOMM
TOMPECS
TOMS
TOPC
TOPLAS
TOPML
TOPS
TORS
TOS
TOSEM
TOSN
TQC
TRETS
TSAS
TSC
TSLP
TWEB
#endkeyvals

\acmConference{name}{date}{venue}
\acmConference[short name]{name}{date}{venue}
\acmBooktitle{title%text}
\editor{editor}
\subtitle{subtitle%text}
\orcid{orcid}
\affiliation{affiliation}
\affiliation[obeypunctuation=%<true|false%>]{%<affiliation%>}
\additionalaffiliation{affiliation}
\position{position}
\institution{institution}
\department{department}
\streetaddress{address}
\city{city}
\state{state}
\postcode{postcode}
\country{country}
\authorsaddresses{contact addresses}
\titlenote{text}
\subtitlenote{text}
\authornote{text}
\authornotemark
\authornotemark[number]
\acmVolume{volume number}#*
\acmNumber{issue number}#*
\acmArticle{article number}#*
\acmYear{year}#*
\acmMonth{month}#*
\acmArticleSeq{number}#*
\acmSubmissionID{ID}
\acmPrice{price}#*
\acmISBN{ISBN}#*
\acmDOI{DOI}#*
\acmBadge{imagefile}#*g
\acmBadge[URL]{imagefile}#*g
\acmBadgeR{imagefile}#Sg
\acmBadgeR[URL]{imagefile}#Sg
\acmBadgeL{imagefile}#Sg
\acmBadgeL[URL]{imagefile}#Sg
\startPage{page}#*
\begin{CCSXML}
\end{CCSXML}
\ccsdesc{text}
\ccsdesc[number]{text}

\setcopyright{type%keyvals}

#keyvals:\setcopyright#c
none
acmcopyright
acmlicensed
rightsretained
usgov
usgovmixed
cagov
cagovmixed
licensedusgovmixed
licensedcagov
licensedcagovmixed
othergov
licensedothergov
iw3c2w3
iw3c2w3g
cc
#endkeyvals

\setcctype{type%keyvals}
\setcctype[version]{type%keyvals}

#keyvals:\setcctype
zero
by
by-sa
by-nd
by-nc
by-nc-sa
by-nc-nd
#endkeyvals

\copyrightyear{year}
\begin{teaserfigure}
\end{teaserfigure}

\settopmatter{settings%keyvals}

#keyvals:\settopmatter#c
printccs#true,false
printacmref#true,false
printfolios#true,false
authorsperrow=%<number%>
#endkeyvals

\received{date}
\received[stage]{date}
\setengagemetadata{name}{value}

\acmArticleType{type%keyvals}

#keyvals:\acmArticleType
Research
Review
Discussion
Invited
Position
#endkeyvals

\acmCodeLink{link%URL}#U
\acmDataLink{link%URL}#U

\Description{description%text}
\Description[short description%text]{description%text}

#keyvals:\theoremstyle#c
acmplain
acmdefinition
#endkeyvals

\begin{theorem}
\begin{theorem}[header%text]
\end{theorem}
\begin{conjecture}
\begin{conjecture}[header%text]
\end{conjecture}
\begin{proposition}
\begin{proposition}[header%text]
\end{proposition}
\begin{lemma}
\begin{lemma}[header%text]
\end{lemma}
\begin{corollary}
\begin{corollary}[header%text]
\end{corollary}
\begin{example}
\begin{example}[header%text]
\end{example}
\begin{definition}
\begin{definition}[header%text]
\end{definition}

\begin{printonly}
\end{printonly}
\begin{screenonly}
\end{screenonly}
\begin{anonsuppress}
\end{anonsuppress}
\anon{suppressed text%text}
\anon[substitute%text]{suppressed text%text}
\begin{acks}
\end{acks}
\grantsponsor{sponsorID}{name}{URL}#U
\grantnum{sponsorID}{number}
\grantnum[URL]{sponsorID}{number}#U

#keyvals:\citestyle#c
acmauthoryear
acmnumeric
#endkeyvals

#keyvals:\setcitestyle
nobibstyle
bibstyle
sort
nosort
compress
nocompress
sort&compress
mcite
merge
elide
longnamesfirst
nonamebreak=
#endkeyvals

\AtBeginMaketitle{code}

\begin{sidebar}
\end{sidebar}
\begin{marginfigure}
\end{marginfigure}
\begin{margintable}
\end{margintable}

\shortcite{keylist}#c
\shortcite[add.text]{keylist}

\citeA{keylist}#Sc
\citeA[postfix]{keylist}#S
\citeA[prefix][postfix]{keylist}#S
\citeANP{keylist}#Sc
\citeANP*{keylist}#Sc
\citeN{keylist}#Sc
\citeN[add. text]{keylist}#S
\citeNN{keylist}#Sc
\citeNP{keylist}#Sc
\citeNP*{keylist}#Sc
\citeyearNP{keylist}#Sc

\Sectionformat#S
\realSectionformat#S
\acksname#*
\copyrightpermissionfootnoterule#*
\noindentparagraph*{title}#*L5
\noindentparagraph[short title]{title}#*L5
\noindentparagraph{title}#*L5
\showeprint[prefix]{number}#*
\showeprint{number}#*

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

# these made available without #* for some language options (see below)
\translatedtitle{language}{title%text}#*
\translatedsubtitle{language}{subtitle%text}#*
\translatedkeywords{language}{keywords%text}#*
\begin{translatedabstract}{language}#*
\end{translatedabstract}#*

# common language options
#ifOption:language=english
#include:babel
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
\translatedtitle{language}{title%text}
\translatedsubtitle{language}{subtitle%text}
\translatedkeywords{language}{keywords%text}
\begin{translatedabstract}{language}
\end{translatedabstract}
#endif

#ifOption:language=french
#include:babel
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
\bibname#*
\AutoSpaceBeforeFDP#*
\begin{descriptionFB}
\begin{enumerateFB}
\begin{itemizeFB}
\begin{listFB}{symbol}
\begin{listORI}{symbol}#*
\boi
\bname{text}
\bsc{text}
\CaptionSeparator#*
\captionsfrench#*
\ccname#*
\chaptername#*
\circonflexe
\dateacadian#*
\datefrench#*
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
\extrasfrench#*
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
\noextrasfrench#*
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
\translatedtitle{language}{title%text}
\translatedsubtitle{language}{subtitle%text}
\translatedkeywords{language}{keywords%text}
\begin{translatedabstract}{language}
\end{translatedabstract}
#endif

#ifOption:language=german
#include:babel
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
\translatedtitle{language}{title%text}
\translatedsubtitle{language}{subtitle%text}
\translatedkeywords{language}{keywords%text}
\begin{translatedabstract}{language}
\end{translatedabstract}
#endif
