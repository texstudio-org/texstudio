# dps package
# Matthew Bertucci 2022/05/10 for v1.7

#include:xkeyval
#include:web
#include:eforms
#include:graphicx
#include:verbatim
#include:calc
#include:multicol
#include:multido

#keyvals:\usepackage/dps#c
nonrandomized
!nonrandomized
viewmode
!viewmode
showletters
!showletters
showanswerlabels
!showanswerlabels
showanswerkey
!showanswerkey
usebtnappr
uselayers
savedata
!savedata
lang=#english,german,custom
#endkeyvals

#ifOption:usebtnappr
#include:icon-appr
# loads usebtnappr.def
\quesNumTxt{text}#*
\quesNumTxTPost#*
\begin{setContent}{name}
\end{setContent}
\ltrToNum{arg}#*
\dpsEmbedIcons
\TFOR#S
\dpsQuesIcon{name}{width}{height}
\dpsQuesIcon[modifications]{name}{width}{height}
\dpsOtherIcon{name}{width}{height}
\dpsOtherIcon[modifications]{name}{width}{height}
\placeQuesIcon{placement cmds}
\placeOtherIcon{placement cmds}
\dpsEmbedSideShow{n}{imagefile}#g
\dpsEmbedSideShow[ext]{n}{imagefile}#g
\dpsNumSideShowPics#*
\tileKVs{arg}#S
\insertSideshow{rows}{cols}{width}{height}
\iconPresets#*
#endif

#ifOption:uselayers
# loads useocgappr.def
\fmtOCGQues{formatting cmds}
\dpsQuesLayer{arg}
\placeQuesLayer{formatting cmds}
\placeOtherLayer{formatting cmds}
\insertQuesLayer{arg}
\quesNumTxt{text}#*
\quesNumTxTPost#*
\begin{setContent}{name}
\end{setContent}
\scArg#S
\insertSideshow{rows}{cols}{imagefile}#g
\insertSideshow{rows}{cols}[options%keyvals]{imagefile}#g
#keyvals:\insertSideshow
alt={%<alt text%>}
bb=%<llx lly urx ury%>
bbllx=
bblly=
bburx=
bbury=
natwidth=
natheight=
hiresbb#true,false
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
viewport=%<llx lly urx ury%>
trim=%<llx lly urx ury%>
angle=%<degrees%>
origin=
width=##L
height=##L
totalheight=##L
keepaspectratio#true,false
scale=%<factor%>
clip#true,false
draft#true,false
type=%<file type%>
ext=%<file extension%>
read=%<read-file extension%>
command=
quiet
page=%<page number%>
interpolate#true,false
decodearray={%<color array%>}
#endkeyvals
#endif

\AnswerKey
\setdpsfootskip{skip}
\DeclarePuzzle{{%<letter1%>}{%<name1%>}{%<letter2%>}{%<name2%>}%<...%>}
\nPuzzleCols{n}
\sideshowPackaged
\begin{Composing}
\end{Composing}
\begin{cQ}{name}
\end{cQ}
\begin{cA}{name}
\begin{cA}[alt-letter]{name}
\end{cA}
\writeComposingEnv
\insertPuzzle{n}
\PuzzleAppearance{modifications}
\rowsep{skip}
\wdPuzzleFields{length}
\htPuzzleFields{length}
\displayRandomizedQuestions
\QuesAppearance{modifications}
\widestFmtdQNum{string}
\htOfQ{length}
\displayRandomizedAnswers
\displayRandomizedAnswersLeftPanel
\displayRandomizedAnswersRightPanel
\AnsAppearance{modifications}
\ltrFmtA{definition}
\widestFmtdALtr{string}
\htOfA{length}
\placeMessageField{width}{height}
\placeMessageField[modifications]{width}{height}
\useRandomSeed{seed}
\inputRandomSeed
\useLastSeed
\printDPS{width}{height}
\printDPS[modifications]{width}{height}
\resetDPS{width}{height}
\resetDPS[modifications]{width}{height}
\dpsResetHook{JS code%definition}
\dpsFinishedEvent{JS code%definition}
\dpsfinishedevent#*
\randomizePicMappings
\sortPicMappings
\clearOnCloseOrSave
\threshold{n}
\dsthreshold#*
\penaltypoints{n}
\dspenaltypoints#*
\passing{n}
\dspassing#*

# from random.tex
\randomi#*
\nextrandom#*
\setrannum{count register}{min}{max}#*
\setrandim{dimen register}{min}{max}#*
\pointless#*
\PoinTless#S
\ranval#*

# not documented
\afterQhookA{arg1}#S
\aPenaltyMsgs#S
\aPenaltyScale#S
\argi#S
\Awidth#S
\bRandPicMaps#S
\checkboxTmp#S
\chooseQ#S
\ComposingEnvMsg#S
\congratFinished#S
\dpsA{arg1}{arg2}#S
\dpsAitemOptArg#S
\DPSIndxList#S
\dpsInputBtnAppr#S
\dpsInputOcgAppr#S
\dpsLastSeed{seed}#*
\DPSNamesList#S
\dpsQ{arg1}#S
\dpsWCSWrnMsg#S
\finalPenaltyScore#S
\getLetterNext#S
\lastOnLeft#S
\lngthOfMsg#S
\msgi#S
\msgii#S
\nCols#S
\nextPuzzleChar#*
\nextPuzzleLetter#*
\nextPuzzlePair#*
\OnFocusQhookAA#S
\puzzleParameters#*
\Qht#S
\Qwidth#S
\redefnextrandomAsNeeded#*
\regretPleased#S
\reportPenaltyPoints#S
\signInMsg#S
\textfieldTmp#S
\triedTooMuch#S
\WriteBookmarks#S