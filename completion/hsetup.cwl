# hsetup package
# Matthew Bertucci 2023/03/13 for v4.2

#include:ifthen
#include:graphicx
#include:class-letter
#include:babel
# loads french, german, and british options of babel

\addressA{text}#*
\addressB{text}#*
\addressC{text}#*
\border[voffset%l]{height%l}{imagefile}#g
\border{height%l}{imagefile}#g
\bottomC{text}#*
\bottomL{text}#*
\bottomR{text}#*
\centreA{text}#*
\centreB{text}#*
\centreC{text}#*
\centreD{text}#*
\centreE{text}#*
\centreF{text}#*
\centrepos{offset%l}
\extraA{text}#*
\extraB{text}#*
\extraC{text}#*
\logo[height%l]{imagefile}#g
\logo{imagefile}#g
\newfa#*
\newfb#*
\newfc#*
\newoption{name}{number}#*

# not documented
\addrbox#S
\centreoffset#S
\cmda{arg}#S
\cmdb{arg}#S
\dohead{arg1}{arg2}{arg3}{arg4}#S
\dotoadd{arg}#S
\draftfalse#S
\drafttrue#S
\hlangcnt#*
\hltype#*
\ifdraft#S
\logoheight#*
\logoname#*
\myc#S
\oldbls#S
\pindt#S
\sealbx#S
\settoadd{arg}#S
\tmpdima#S
\tmpdimb#S

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

# from german option of babel (repeats removed)
\captionsgerman#*
\dategerman#*
\extrasgerman#*
\noextrasgerman#*
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

# from british option of babel (repeats removed)
\captionsbritish#*
\datebritish#*
\extrasbritish#*
\noextrasbritish#*
\captionsenglish#*
\dateenglish#*
\extrasenglish#*
\noextrasenglish#*
\englishhyphenmins#S
\britishhyphenmins#S
\americanhyphenmins#S