# chextras package
# Matthew Bertucci 2023/03/14 for v1.01

#include:inputenc
#include:fontenc
# loads T1 option of fontenc
#include:lmodern
#include:babel

#keyvals:\usepackage/chextras#c
nomath
lighttt
variablett
oldstyle
german
french
italian
english
black
gray
color
stdshape
stdspace
stdfield
stdparis
stddimen
stdskips
stdmgpar
stdlists
stdlabel
stditems
stdnotes
stdrules
#endkeyvals

#ifOption:black
#include:hyperref
# loads colorlinks option of hyperref
#include:color
#endif

#ifOption:gray
#include:hyperref
# loads colorlinks option of hyperref
#include:color
#endif

#ifOption:color
#include:hyperref
# loads colorlinks option of hyperref
#include:color
#endif

\rmosfamily
\sfosfamily
\ttosfamily
\textrmos{text}
\textsfos{text}
\textttos{text}
\rmosdefault#*
\sfosdefault#*
\ttosdefault#*
\sishape
\textsi{text}
\sidefault#*
\authorname#*
\titlename#*
\datename#*
\up{text}
\bsc{text}
\no
\ier

# deprecated
\conc{arg}#S
\conc[opt]{arg}#S
\letterindent#S
\fromheight#S
\toheight#S

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

# babel options
#ifOption:german
\captionsgerman
\dategerman
\extrasgerman
\noextrasgerman
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

#ifOption:french
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
#endif

#ifOption:italian
\captionsitalian#*
\dateitalian#*
\extrasitalian#*
\noextrasitalian#*
\italianhyphenmins#*
\setactivedoublequote
\setISOcompliance#*
\IntelligentComma
\NoIntelligentComma
\XXIletters
\XXVIletters
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
\ap{text%plain}
\ped{text%plain}
\unit{unit}
\virgola
\virgoladecimale
\LtxSymbCaporali#*
\CaporaliFrom{encoding}{family}{open guill slot}{close guill slot}#*
#endif

#ifOption:english
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
#endif