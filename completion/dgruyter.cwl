# dgruyter package
# Matthew Bertucci 2022/05/25 for v2.00

#include:cmap
#include:amsmath
#include:tipa
#include:fontenc
# loads T1 option of fontenc
#include:textcomp
#include:zi4
#include:amssymb
#include:babel
# loads english option of babel
#include:ragged2e
#include:footmisc
#include:amsthm
#include:graphicx
#include:array
#include:multirow
#include:tabularx
#include:bigstrut
#include:supertabular
#include:booktabs
#include:multicol
#include:caption
#include:sidecap
#include:rotating
#include:makeidx
#include:lineno
#include:url
#include:hyperref
#include:doi
#include:manyfoot
#include:authblk
#include:lastpage
#include:environ

#keyvals:\usepackage/dgruyter#c
small
medium
big
margincol
online
print
printona4
work
#endkeyvals

#ifOption:margincol
#include:changepage
#endif

#keyvals:\theoremstyle#c
dgdef
dgthm
#endkeyvals

\begin{note}
\begin{note}[vignette choice%keyvals]
\end{note}

#keyvals:\begin{note}#c
DG_attention
DG_exercise
DG_information
DG_notice
DG_question
#endkeyvals

\starttabularbody#t
\baretabulars
\layouttabulars

\articletype{text}
\articlesubtype{text}
\openaccess
\runningauthor{names}
\runningtitle{text}
\subtitle{text}
\abstract{text}
\keywords{keywords%text}
\transabstract{text}
\transabstract[language]{text}
\transkeywords{keywords%text}
\transkeywords[language]{keywords%text}
\correctionnote{text}
\correctionnote[heading%text]{text}
\classification{text}
\classification[system]{text}
\communicated{text}
\dedication{text}
\received{date}
\accepted{date}
\journalname{name%text}
\journalyear{year}
\journalvolume{volume}
\journalissue{issue}
\startpage{text}
\aop
\DOI{DOI}
\contributioncopyright{year}{holder}{text}
\contributioncopyright[imagefile]{year}{holder}{text}#g

\begin{acknowledgement}
\end{acknowledgement}
\begin{funding}
\end{funding}
\begin{conflictofinterest}
\end{conflictofinterest}
\articlenote{text}

\begin{thegraphicalabstractsection}
\end{thegraphicalabstractsection}
\graphicalabstract{names}{title%text}{metainfo}{abstract%text}{imagefile}#g

\begin{contributors}
\begin{contributors}[heading%text]
\end{contributors}
\contributor{name}{address}{email%URL}{imagefile}{short vita%text}#g

\reviewauthor{name}
\reviewinfo{text}
\furtherreview{text}{name}{address}{DOI}

\transtitle{text}
\distributionseries{series%text}
\seriestitle{text}
\transseriestitle{text}
\seriessubtitle{text}
\serieseditor{name}
\seriesvolume{volume}
\editor{name}
\collaborator{name}
\edition{text}
\publisherlogo{logo choice%keyvals}
\authorinfo{text}

#keyvals:\publisherlogo#c
dg-degruyter
dg-mouton
dg-saur
#endkeyvals

\isbn{ISBN}
\eisbnpdf{eISBN}
\eisbnepub{eISBN}
\issn{ISSN}
\copyrightyear{year}
\copyrighttext{text}
\cover{name}
\typesetter{name}
\printbind{name}

\begin{advertisement}
\begin{advertisement}[heading%text]
\end{advertisement}
\otherpubl{title%text}{authors}{ISBN info}
\otherpubl[imagefile]{title%text}{authors}{ISBN info}#g
\otherpubl[imagefile][volume]{title%text}{authors}{ISBN info}#g
\makeadvertisement

\partmotto{text}

\contribution#L1
\makecontributiontitle
\contributionauthor{name}
\contributionauthor[mark]{name}
\contributionauthor*{name}
\contributiontitle{text}
\contributionsubtitle{text}
\contributionnote{text}
\markleft{text}

# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n

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

# not documented
\acceptedname#*
\acknowledgementname#*
\addissuecontentsline{arg1}{arg2}#*
\addissuetwocolcontentsline{arg1}{arg2}#*
\adverttitlename#*
\baretablefirsthead{text}#*
\baretablehead{text}#*
\baretablelasttail{text}#*
\baretabletail{text}#*
\begin{legaltext}#*
\end{legaltext}#*
\classificationname#*
\communicatedname#*
\conflictofinterestname#*
\CorrAuth#*
\correctionnotename#*
\footinsauthor#*
\footinsnote#*
\Footnotetextauthor{marker}{text}#*
\Footnotetextnote{marker}{text}#*
\fundingname#*
\generaltitledef{arg1}#*
\graphicalabstractname#*
\gridwidth#*
\Hyphen#S
\idxlevel#*
\indexpreamble#*
\issuename#*
\issuetableofcontents#*
\keywordsname#*
\laytablefirsthead{text}#*
\laytablehead{text}#*
\laytablelasttail{text}#*
\laytabletail{text}#*
\listauthorname#*
\notename#*
\partnumberline{arg1}#*
\receivedname#*
\recital{text}#*
\reviewedbyname#*
\revised{date}#*
\revisedname#*
\rls#S
\setisbn{ISBN}#*
\showinmm{arg}#*
\sidecaptionrelwidth#*
\sidecaptionsep#*
\tablefont#*
\tableheadfont#*
\tailrule#*
\thefrontmatterpage#*
\theinchapequation#*
\theinchapfigure#*
\theinchapsection#*
\theinchaptable#*
\theplainequation#*
\theplainfigure#*
\theplainsection#*
\theplaintable#*
\volumename#*
\xeisbnpdf{ISBN}#*