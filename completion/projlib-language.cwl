# projlib-language package
# Matthew Bertucci 2022/04/04 for 2022/03/28 release

#include:l3keys2e
#include:fontenc
# loads T1 option of fontenc
#include:babel
# loads italian, portuguese, brazilian, spanish, ngerman, french, and english options of babel
#include:setspace

#keyvals:\usepackage/projlib-language#c
English
French
German
Italian
Portuguese
Brazilian
Spanish
Chinese
TChinese
Japanese
Russian
#endkeyvals

\AddLanguageSetting{settings}
\AddLanguageSetting[language]{settings}
\DefineMultilingualText{command}{keyvals}#d
\ProjLibLanguageSet{object}{language}{setting}
\UseLanguage{language}
\UseOtherLanguage{language}{content%text}

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

# from babel options
# french
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
\bibname#*
\begin{descriptionFB}
\begin{enumerateFB}
\begin{itemizeFB}
\begin{listFB}{symbol}
\begin{listORI}{symbol}#*
\boi
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

# portuguese
\captionsportuguese#*
\dateportuguese#*
\extrasportuguese#*
\noextrasportuguese#*
\ord
\orda
\ro#*
\ra#*

# brazilian
\captionsbrazilian
\datebrazilian
\extrasbrazilian
\noextrasbrazilian

# italian
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
\ap{arg}
\ped{arg}
\unit{arg}#*
\virgola
\virgoladecimale
\LtxSymbCaporali#*
\CaporaliFrom{encoding}{family}{open guill slot}{close guill slot}#*

# ngerman
\captionsngerman#*
\datengerman#*
\extrasngerman#*
\noextrasngerman#*
\dq
\ntosstrue#*
\ntossfalse#*
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

# english
\captionsenglish#*
\dateenglish#*
\extrasenglish#*
\noextrasenglish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*

# following babel options only loaded if using unicode engine,
# so listed here only if explicitly loaded as package option

#ifOption:Japanese
\captionsjapanese#*
\datejapanese#*
\extrasjapanese#*
\noextrasjapanese#*
#endif

#ifOption:Russian
\cyrdash
\asbuk{counter}
\Asbuk{counter}
\Russian
\sh#m
\ch#m
\tg#m
\ctg#m
\arctg#m
\arcctg#m
\th#m
\cth#m
\cosec#m
\Prob#m
\Variance#m
\NOD#m
\nod#m
\NOK#m
\nok#m
\Proj#m
\cyrillicencoding#*
\cyrillictext#*
\cyr#*
\textcyrillic{text}
\dq
\captionsrussian#*
\daterussian#*
\extrasrussian#*
\noextrasrussian#*
\CYRA#*
\CYRB#*
\CYRV#*
\CYRG#*
\CYRGUP#*
\CYRD#*
\CYRE#*
\CYRIE#*
\CYRZH#*
\CYRZ#*
\CYRI#*
\CYRII#*
\CYRYI#*
\CYRISHRT#*
\CYRK#*
\CYRL#*
\CYRM#*
\CYRN#*
\CYRO#*
\CYRP#*
\CYRR#*
\CYRS#*
\CYRT#*
\CYRU#*
\CYRF#*
\CYRH#*
\CYRC#*
\CYRCH#*
\CYRSH#*
\CYRSHCH#*
\CYRYU#*
\CYRYA#*
\CYRSFTSN#*
\CYRERY#*
\cyra#*
\cyrb#*
\cyrv#*
\cyrg#*
\cyrgup#*
\cyrd#*
\cyre#*
\cyrie#*
\cyrzh#*
\cyrz#*
\cyri#*
\cyrii#*
\cyryi#*
\cyrishrt#*
\cyrk#*
\cyrl#*
\cyrm#*
\cyrn#*
\cyro#*
\cyrp#*
\cyrr#*
\cyrs#*
\cyrt#*
\cyru#*
\cyrf#*
\cyrh#*
\cyrc#*
\cyrch#*
\cyrsh#*
\cyrshch#*
\cyryu#*
\cyrya#*
\cyrsftsn#*
\cyrery#*
\cdash#*
\tocname#*
\authorname#*
\acronymname#*
\lstlistingname#*
\lstlistlistingname#*
\notesname#*
\nomname#*
#endif