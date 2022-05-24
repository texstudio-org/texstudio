# eq-pin2corr package
# Matthew Bertucci 2022/05/21 for v2.0

#include:exerquiz
#include:eq-save

#keyvals:\usepackage/eq-pin2corr#c
showscore
!showscore
#endkeyvals

\classPINVar{class pin var}
\CorrBtnActionsJSSave#*
\CorrBtnActionsPwdJS#*
\declPINId{pin num}{hash string}
\declRePINId{pin num}{hash string}
\eQzBtnActnsPIN#*
\eQzBtnActnsSave#*
\FreezeQuizfalse#*
\FreezeQuiztrue#*
\FreezeThisQuiz
\FreezeThisQuizNot
\hashPINId#*
\hashRePINId#*
\ifFreezeQuiz#*
\ifPINSecurity#*
\ifPINshowScore#*
\makeEndQuizPIN#*
\nMaxRetakes{qz name}
\numPINId
\numRePINId
\PINclassPV#*
\PINgobii#*
\PINgobiii#*
\PINSecurityfalse#*
\PINSecuritytrue#*
\PINshowScorefalse#*
\PINshowScoretrue#*
\postSubmitQuizPIN#*
\qzResetTally
\qzResetTally[eforms params]
\qzTallyTotalDefaults#*
\restorBeginQuiz
\restoreCorrBtn
\restoreEndQuiz
\SaveAndSendMsg#*
\setMaxRetakes{qz name}{num}
\showScoreOff
\showScoreOn
\useBeginQuizCnt
\useBeginQuizPIN
\usePINCorrBtn
\useWarnEndQuiz