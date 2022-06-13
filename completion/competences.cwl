# competences package
# Matthew Bertucci 2022/06/12 for v1.0

#include:todonotes
#include:datatool
#include:etoolbox
#include:longtable

\declareprefix{prefix}
\declarecompetence{competence}
\addGlobalCompetence{competence}
\addGlobalCompetence[value]{competence}
\addcompetence{competence}
\addcompetence[value]{competence}
\tableaupartie{partie}
\tableauprefix{partie1,partie2,...}

# not documented
\begin{dummyEnv}#S
\end{dummyEnv}#S
\cstotal#*
\dummyMacro#S
\getCurrentSectionNumber#*
\getCurrentpartiedocument#*
\gptotal#*
\gtotal#*
\ifcompexists{arg1}{arg2}{arg3}#*
\ifpartexists{arg1}{arg2}{arg3}#*
\ifquestexists{arg1}{arg2}{arg3}#*
\partie#*
\pctotal#*
\pftotal#*
\ptotal#*
\quest#*
\sumcspartie{arg1}{arg2}#*
\sumpfpartie{arg1}{arg2}#*
\tableaucompetences#*
\total#*