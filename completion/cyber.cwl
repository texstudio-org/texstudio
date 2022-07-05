# cyber package
# Matthew Bertucci 2022/07/04 for v2.2

#include:longtable
#include:color
#include:index
#include:fancyhdr
#include:graphicx

\documents{requirement type}{requirement name}
\notapplicable{requirement type}{requirement name}
\implements{requirement type}{requirement name}
\doneby{who}{requirement type}{requirement name}
\bydefault{product}{requirement type}{requirement name}
\unimplemented{requirement type}{requirement name}{reason%text}

\articlesecuritylabel{text}
\booksecuritylabel{text}

\distributionA{other information%text}
\distributionB{reason why%text}{controlling office%text}
\distributionC{reason why%text}{controlling office%text}
\distributionD{reason why%text}{controlling office%text}
\distributionE{reason why%text}{controlling office%text}
\distributionF{controlling office%text}

\makedodtitle
\narrowermargins

\begin{changelog}
\end{changelog}
\change{date}{name}{change%text}

\begin{executivesummary}
\end{executivesummary}
\executivesummaryiacontrol{IA control id}{IA control name}

\requirementsdocument{document id}{header%text}{prefix}

\ifCyberindexingenabled#*
\Cyberindexingenabledtrue
\Cyberindexingenabledfalse

# not in main documentation
\complianceaux#S
\foreach{macro}{arg1}{arg2}{item1,item2,...}#*
\requirement{document id}{requirement name}#*
\namedrequirement{index name}{prefix}{requirement name}#*
\addtosectionname{arg}#S
\iaindexheadstyle{text}#*
\indexhelper{index name}{implementation status}{requirement name}#*
\marginhelper{index name}{prefix}{requirement name}#*
\compliancehelper{index name}{compliance status}{requirement name}#*
\explanationshelper{index name}{explanation}{requirement name}#*
\sectionnamehelper{index name}{}{requirement name}#*
\iamarginsize#*
\prescribed{requirement type}{requirement name}#*
\documented{requirement type}{requirement name}#*
\version{version}#*