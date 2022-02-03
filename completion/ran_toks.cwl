# ran_toks package
# Matthew Bertucci 2/1/2022 for v1.4

#include:verbatim

#keyvals:\usepackage/ran_toks#c
usedbapp
#endkeyvals

\ranToks{%<name%>}{{%<token1%>}{%<token2%>}%<...{tokenN}%>}
\nToksFor{name}
\useRanTok{number}
\useRanTok[name]{number}
\useRTName{name}
\reorderRanToks{name}
\copyRanToks{name1}{name2}
\bRTVToks{name}
\begin{rtVW}
\end{rtVW}
\eRTVToks
\RTVWHook#*
\rtVWHook{code}
\displayListRandomly{name}
\displayListRandomly[prior]{name}
\displayListRandomly[prior][post]{name}
\displayListRandomly[prior][post]{name}
\first#*
\last#*
\lessone#*
\begin{rtVWi}
\end{rtVWi}
\begin{rtVWii}
\end{rtVWii}
\rtTokByNum{number}
\rtTokByNum[name]{number}
\ranToksOff
\ranToksOn
\useLastAsSeed
\useThisSeed{init seed value}

#ifOption:usedbapp
\useTheseDBs{db1,db2,...}
\useProbDBs{db1,db2,...}#*
\ProbDBWarningMsg{message%text}#S
\viewDB{name}#*
\nSTOP#S
\ranIndex#S
#endif

\uniqueXDBChoicesOn
\uniqueXDBChoicesOff
\InputUsedIDs

\ifrtdebug#*
\rtdebugtrue#*
\rtdebugfalse#*
\ifwerandomize#*
\werandomizetrue#*
\werandomizefalse#*
\ifsaveseed#*
\saveseedtrue#*
\saveseedfalse#*
\rtPkgInpt#S
\readsavfile#*
\InitSeedValue#*
\lastRandomNum#*
\inputRandomSeed#*
\useRandomSeed{init seed value}#*
\begin{verbatimwrite}#S
\end{verbatimwrite}#S
\verbatimwrite#S
\endverbatimwrite#S
\reVerbEnd#*
\wrtprobids#*
\ifviewIDs#*
\viewIDstrue#*
\viewIDsfalse#*
\ifxDBUnique#*
\xDBUniquetrue#*
\xDBUniquefalse#*
\xdbunique#S
\wrtProbIds{arg}
\rtVWId{arg}
\rtVW#S
\endrtVW#S
\rtVWi#S
\endrtVWi#S
\rtVWii#S
\endrtVWii#S
\makeInfoAWarning#S
\pkgNotifType#S
\rtcsarg{arg1}{arg2}#S
\Indx#*

# from random.tex
\randomi#*
\nextrandom#*
\setrannum{count register}{min}{max}#*
\setrandim{dimen register}{min}{max}#*
\pointless#*
\PoinTless#S
\ranval#*