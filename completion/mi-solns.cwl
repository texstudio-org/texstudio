# mi-solns package
# Matthew Bertucci 2022/05/21 for v0.6

#include:shellesc

\addToMINullify#*
\copyfileCmdEx
\copyfileCmdQz
\copySolnsOff
\copySolnsOn
\declQSLIn{arg1}#*
\declQSLOut{qsl-out}
\declSOLIn{arg1}#*
\declSOLOut{sol-out}
\eqargi#S
\eqMrkSolnCpyEx{arg1}#*
\eqMrkSolnCpyQz{arg1}#*
\eqMrkSolnCpySQ{arg1}#*
\examSolnHeadFmt#*
\gobbleiiendgroup{arg1}#*
\gobbleiiendinput{arg1}#*
\gobbleiiterminex{arg1}#*
\ifmifound#*
\ifnotamiop#*
\ignoreques
\ignoreterminex
\insExSoln[inserts]{name}
\insExSoln{name}
\insQzSoln[inserts]{name}
\insQzSoln{name}
\insSqSoln[inserts]{name}
\insSqSoln{name}
\mifoundfalse#*
\mifoundtrue#*
\miqslin#*
\miqslout
\miReadOffMsg#*
\misolin#*
\misolout
\mrkForIns{name}
\notamiopfalse#*
\notamioptrue#*
\readSolnsOff
\readSolnsOn
\reqDate#*
\writeToSolnFile#*