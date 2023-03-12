# nwejmart class
# Matthew Bertucci 4/11/2022 for v1.0.4

#include:l3keys2e
#include:etoolbox
#include:class-book
#include:nag
#include:fontenc
# loads T1 option of fontenc
#include:kpfonts
#include:titlesec
# loads pagestyles option of titlesec
#include:graphicx
#include:adjustbox
#include:xr
#include:footmisc
#include:marginnote
#include:refcount
#include:xcolor
#include:afterpage
#include:ifoddpage
#include:placeins
#include:xspace
#include:csquotes
#include:array
#include:booktabs
#include:mathtools
#include:ntheorem
# loads thmmarks option of ntheorem
#include:esvect
#include:geometry
#include:translations
#include:currfile
#include:fmtcount
#include:babel
# loads english option of babel
#include:varioref
#include:subcaption
#include:tocvsec2
#include:tocloft
#include:etoc
#include:microtype
#include:datetime2
#include:enumitem
# loads inline option of enumitem
#include:environ
#include:footnote
#include:biblatex
#include:hyperref
#include:hypcap
#include:bookmark
#include:glossaries
#include:cleveref

#keyvals:\documentclass/nwejmart#c
english
french
german
dutch
10pt
11pt
12pt
draft
#endkeyvals

#ifOption:french
# from french option of babel
\frenchsetup{options%keyvals}
\frenchbsetup{options%keyvals}#S
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
\at
\AutoSpaceBeforeFDP#*
\begin{descriptionFB}
\begin{enumerateFB}
\begin{itemizeFB}
\begin{listFB}{symbol}
\begin{listORI}{symbol}#*
\bname{text}
\boi
\bsc{text}
\CaptionSeparator#*
\captionsfrench#*
\circonflexe
\dateacadian#*
\datefrench#*
\DecimalMathComma
\degre#*
\degres
\descindentFB#*
\dotFFN#*
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
\parindentFFN#*
\partfirst#*
\partfirst#*
\partnameord#*
\partsecond#*
\partsecond#*
\primo
\quarto
\rmfamilyFB#*
\secundo
\sffamilyFB#*
\StandardFootnotes#*
\StandardMathComma
\tertio
\tild
\ttfamilyFB#*
\up{text}
#endif

#ifOption:german
\captionsngerman#*
\datengerman#*
\extrasngerman#*
\noextrasngerman#*
\dq
\tosstrue#*
\tossfalse#*
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
#ifOption:ngerman
\captionsngerman#*
\datengerman#*
\extrasngerman#*
\noextrasngerman#*
\dq
\tosstrue#*
\tossfalse#*
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

#ifOption:dutch
\captionsdutch#*
\datedutch#*
\extrasdutch#*
\noextrasdutch#*
\dutchhyphenmins#*
#repl:"a ä
#repl:"e ë
#repl:"i ï
#repl:"o ö
#repl:"u ü
#repl:"y ij
#repl:"Y IJ
#repl:"|
#repl:"- -
#repl:"~ -
#repl:""
#repl:"` „
#repl:"' “
\refpagename#*
#endif

\articlesetup{options%keyvals}

#keyvals:\articlesetup
gradient=#grad,nabla
#endkeyvals

\title[titre alternatif tdm%text]{titre%text}
\title[titre alternatif tdm%text][titre alternatif entête%text]{titre%text}
\subtitle{sous-titre%text}
\subtitle[sous-titre alternatif tdm%text]{sous-titre%text}

\author[options%keyvals]{Nom,Prénom}

#keyvals:\author
affiliation={%<affiliation%>}
affiliation=[%<tag%>]{%<affiliation%>}
affiliationtagged={%<tag%>}
#endkeyvals

\keywords{mots clés%text}
\keywords[variante des mots clés]{mots clés%text}
\msc{msc}
\acknowledgments{remerciements%text}
\section[titre alternatif tdm%text][titre alternatif entête%text]{title}#L2
\I
\E
\E[argument%formula]
\log*#m
\ln*#m
\bbN#m
\bbZ#m
\bbD#m
\bbQ#m
\bbR#m
\bbC#m
\bbK#m
\set{définition%plain}#m
\set{définition%plain}[caractérisation]#m
\cotan#m
\arccosh#m
\arcsinh#m
\ch#m
\sh#m
\Argch#m
\Argsh#m
\arctanh#m
\Argth#m
\norm{argument}#m
\norm[paramètre de taille]{argument}#m
\norm*{argument}#m
\lnorm{argument}#m
\lnorm[paramètre de taille]{argument}#m
\lnorm*{argument}#m
\llnorm{argument}#m
\llnorm[paramètre de taille]{argument}#m
\llnorm*{argument}#m
\lpnorm{argument}#m
\lpnorm[paramètre de taille]{argument}#m
\lpnorm*{argument}#m
\supnorm{argument}#m
\supnorm[paramètre de taille]{argument}#m
\supnorm*{argument}#m
\abs{argument}#m
\abs[paramètre de taille]{argument}#m
\abs*{argument}#m
\prt{argument}#m
\prt[paramètre de taille]{argument}#m
\prt*{argument}#m
\brk{argument}#m
\brk[paramètre de taille]{argument}#m
\brk*{argument}#m
\brc{argument}#m
\brc[paramètre de taille]{argument}#m
\brc*{argument}#m
\leqgeq{argument}#m
\leqgeq[paramètre de taille]{argument}#m
\leqgeq*{argument}#m
\lrangle{argument}#m
\lrangle[paramètre de taille]{argument}#m
\lrangle*{argument}#m

\NewPairedDelimiter{command}{options%keyvals}#d

#keyvals:\NewPairedDelimiter
left=%<delimiter%>
right=%<delimiter%>
subscript=%<indice%>
#endkeyvals

\dif#m
\grad#m
\Div#m
\curl#m
\supp#m
\BinaryOperators{opérateurs binaires}
\begin{theorem}
\begin{theorem}[header%text]
\end{theorem}
\begin{theorem*}
\begin{theorem*}[header%text]
\end{theorem*}
\begin{corollary}
\begin{corollary}[header%text]
\end{corollary}
\begin{corollary*}
\begin{corollary*}[header%text]
\end{corollary*}
\begin{conjecture}
\begin{conjecture}[header%text]
\end{conjecture}
\begin{conjecture*}
\begin{conjecture*}[header%text]
\end{conjecture*}
\begin{proposition}
\begin{proposition}[header%text]
\end{proposition}
\begin{proposition*}
\begin{proposition*}[header%text]
\end{proposition*}
\begin{lemma}
\begin{lemma}[header%text]
\end{lemma}
\begin{lemma*}
\begin{lemma*}[header%text]
\end{lemma*}
\begin{axiom}
\begin{axiom}[header%text]
\end{axiom}
\begin{axiom*}
\begin{axiom*}[header%text]
\end{axiom*}
\begin{definition}
\begin{definition}[header%text]
\end{definition}
\begin{definition*}
\begin{definition*}[header%text]
\end{definition*}
\begin{remark}
\begin{remark}[header%text]
\end{remark}
\begin{remark*}
\begin{remark*}[header%text]
\end{remark*}
\begin{example}
\begin{example}[header%text]
\end{example}
\begin{example*}
\begin{example*}[header%text]
\end{example*}
\begin{notation}
\begin{notation}[header%text]
\end{notation}
\begin{notation*}
\begin{notation*}[header%text]
\end{notation*}
\begin{proof}
\begin{proof}[header%text]
\end{proof}

\newtheorem[options%keyvals]{envname}#N

#keyvals:\newtheorem
style=#theorem,definition,proof
title=%<titre récurrent%>
title-plural=%<forme plurielle du titre récurrent%>
#endkeyvals

\begin{assertions}
\end{assertions}
\begin{hypotheses}
\end{hypotheses}
\begin{conditions}
\end{conditions}

\newenumeration{envname}#N
\newenumeration[options%keyvals]{envname}#N
\renewenumeration{envname}
\renewenumeration[options%keyvals]{envname}

#keyvals:\newenumeration,\renewenumeration
label=%<label%>
singular=%<forme singulière de l'énumération%>
plural=%<forme plurielle de l'énumération%>
#endkeyvals

\ie
\ie*
\Ie
\Ie*
\century{numéro}
\century*{numéro}
\aside{text}
\aside*{text}
\nwejm
\nwejm*

# not documented
\dates{keyvals}#*
#keyvals:\dates
received=%<YYYY-MM-DD%>
accepted=%<YYYY-MM-DD%>
online=%<YYYY-MM-DD%>
#endkeyvals
\fixpagenumber{number}#*
\fontdesignertext{text}#*
\graphicdesigntext{text}#*
\mkbibnamelast{arg}#*

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

# from pagestyles option of titlesec
#include:titleps

# from thmmarks option of ntheorem
\theoremsymbol{symbol}

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

# from inline option of enumitem
\begin{enumerate*}
\begin{enumerate*}[options%keyvals]
\end{enumerate*}
\begin{itemize*}
\begin{itemize*}[options%keyvals]
\end{itemize*}
\begin{description*}
\begin{description*}[options%keyvals]
\end{description*}
