# songbook package
# Matthew Bertucci 2022/05/26 for v4.5

#include:calc
#include:conditionals
#include:ifthen
#include:xstring
#include:multicol

#keyvals:\usepackage/songbook#c
compactallsongs
printallsongs
chordbk
wordbk
overhead
#endkeyvals

## Environments ##
\begin{SBBracket}{tag}
\end{SBBracket}
\begin{SBBracket*}{tag}
\end{SBBracket*}
\begin{SBChorus}
\end{SBChorus}
\begin{SBChorus*}
\end{SBChorus*}
\begin{SBExtraKeys}{song content}
\end{SBExtraKeys}
\begin{SBOccurs}{occurrences}
\end{SBOccurs}
\begin{SBOpGroup}
\end{SBOpGroup}
\begin{SBSection}
\end{SBSection}
\begin{SBSection*}
\end{SBSection*}
\begin{SBVerse}
\end{SBVerse}
\begin{SBVerse*}
\end{SBVerse*}
\begin{song}{title%text}{key%plain}{copyright%text}{names}{scriptureref}{licensing%text}
\begin{song}[format string]{title%text}{key%plain}{copyright%text}{names}{scriptureref}{licensing%text}
\end{song}
\CBExcl
\OHExcl
\WBExcl
\WOExcl
\begin{songTranslation}{language}{title%text}{permission%text}{performer}
\end{songTranslation}
\begin{xlatn}{title%text}{permission%text}{performer}
\end{xlatn}

## Primary Songbook Macros ##
\CBPageBrk
\Ch{chord}{syllable}
\Chr{chord}{syllable}
\ChX{chord}{syllable}
\CSColBrk
\makeArtistIndex
\artistIndex{artist}{title and number%text}
\makeKeyIndex
\keyIndex{key and title%text}{number}
\makeTitleContents
\titleContents{number}{title%text}
\makeTitleContentsSkip
\titleContentsSkip{number}{title%text}
\makeTitleIndex
\titleIndex{title%text}{number}
\NotWOPageBrk
\OHContPgFtr
\OHContPgHdr
\OHPageBrk
\SBBridge{bridge}
\SBEnd{ending%text}
\SBEnd[words-only]{ending%text}
\SBIntro{intro%text}
\SBIntro[words-only]{intro%text}
\SBMargNote{text}
\SBRef{book title%text}{page or song number}
\SBem
\SBen
\STitle{song title%text}{key%plain}
\WBPageBrk
\WOPageBrk

## Miscellaneous Commands ##
\CpyRt{copyright info%text}
\FLineIdx{first line%text}
\SBChorusMarkright
\SBContinueMark
\SBSectionMarkright
\SBVerseMarkright
\SongMarkboth
\STitleMarkboth
\ScriptRef{scripture address}
\WAndM{lyricist and composer}

## Ifthen Commands ##
\ifSBinSongEnv
\SBinSongEnvtrue#*
\SBinSongEnvfalse#*
\ifChordBk
\ChordBktrue#*
\ChordBkfalse#*
\ifOverhead
\Overheadtrue#*
\Overheadfalse#*
\ifWordBk
\WordBktrue#*
\WordBkfalse#*
\ifWordsOnly
\WordsOnlytrue#*
\WordsOnlyfalse#*
\ifNotWordsOnly
\NotWordsOnlytrue#*
\NotWordsOnlyfalse#*
\ifCompactSongMode
\CompactSongModetrue#*
\CompactSongModefalse#*
\ifSongEject
\SongEjecttrue#*
\SongEjectfalse#*
\ifCompactAllMode
\CompactAllModetrue#*
\CompactAllModefalse#*
\ifExcludeSong
\ExcludeSongtrue#*
\ExcludeSongfalse#*
\ifPrintAllSongs
\PrintAllSongstrue#*
\PrintAllSongsfalse#*
\ifSamepageMode
\SamepageModetrue
\SamepageModefalse
\ifSBpaperAfour#*
\SBpaperAfourtrue#*
\SBpaperAfourfalse#*
\ifSBpaperAfive#*
\SBpaperAfivetrue#*
\SBpaperAfivefalse#*
\ifSBpaperBfive#*
\SBpaperBfivetrue#*
\SBpaperBfivefalse#*
\ifSBpaperLtr#*
\SBpaperLtrtrue#*
\SBpaperLtrfalse#*
\ifSBpaperLgl#*
\SBpaperLgltrue#*
\SBpaperLglfalse#*
\ifSBpaperExc#*
\SBpaperExctrue#*
\SBpaperExcfalse#*

## Counters ##
\theSBSongCnt#*
\theSBSectionCnt#*
\theSBVerseCnt#*

## Spacing Commands ##
\HangAmt#*
\LeftMarginSBBracket#*
\LeftMarginSBChorus#*
\LeftMarginSBSection#*
\LeftMarginSBVerse#*
\SBChordRaise#*
\SBRuleRaiseAmount#*
\SpaceAboveSTitle#*
\SpaceAfterTitleBlk#*
\SpaceAfterChorus#*
\SpaceAfterOpGroup#*
\SpaceAfterSection#*
\SpaceAfterSBBracket#*
\SpaceAfterSong#*
\SpaceAfterVerse#*
\SpaceBeforeSBBracket#*

## String Constants ##
\OHContPgFtrTag#*
\OHContPgHdrTag#*
\SBBaseLang#*
\SBBridgeTag#*
\SBChorusTag#*
\SBContinueTag#*
\SBEndTag#*
\SBIntersyllableRule#*
\SBIntroTag#*
\SBPubDom#*
\SBUnknownTag#*
\SBWAndMTag#*

## Font Handling ##
\ChBassFont#*
\ChBkFont#*
\ChFont#*
\CpyRtFont#*
\CpyRtInfoFont#*
\SBBracketTagFont#*
\SBBridgeTagFont#*
\SBChorusTagFont#*
\SBDefaultFont#*
\SBEndTagFont#*
\SBIntroTagFont#*
\SBLyricNoteFont#*
\SBMargNoteFont#*
\SBOccursBrktFont#*
\SBOccursTagFont#*
\SBRefFont#*
\SBVerseNumberFont#*
\SBSectionNumberFont#*
\STitleFont#*
\STitleKeyFont#*
\STitleNumberFont#*
\ScriptRefFont#*
\WandMFont#*

## Deprecated Commands ##
\ChordBk#S
\False#S
\Overhead#S
\SongEject#S
\True#S
\WordBk#S
\WordsOnly#S

## not in main documentation ##
\ChBassFontCS#S
\ChBassFontSav#S
\ChBkFontCS#S
\ChBkFontSav#S
\chCriticDim#S
\ChFontCS#S
\ChFontSav#S
\chMiniSpace#S
\chSpaceDim#S
\chSpaceTolerance#S
\chSpaceToleranceSav#S
\evensidemarginSav#S
\HangAmtSav#S
\LeftMarginSBChorusSav#S
\LeftMarginSBSectionSav#S
\LeftMarginSBVerseSav#S
\marginparsepSav#S
\marginparwidthSav#S
\sbBaselineSkipAmt#S
\sbChord{arg1}#S
\SBDefaultFontCS#S
\SBDefaultFontSav#S
\SBFontSavVar#S
\SBinSongEnv#S
\SBOccursBrktFontCS#S
\SBOccursBrktFontSav#S
\SBOHContTagFont#S
\SBOldChordRaise#S
\sbSetsbBaselineSkipAmt#S
\SBtocSEntry{arg1}{arg2}{arg3}#S
\Songbook#S
\textwidthSav#S
\theSongComposer#S
\theSongComposerU#S
\theSongCopyRt#S
\theSongKey#S
\theSongLicense#S
\theSongScriptRef#S
\theSongTitle#S
\theXlatnBy#S
\theXlatnLang#S
\theXlatnPerm#S
\theXlatnTitle#S