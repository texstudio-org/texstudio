# cvss package
# Matthew Bertucci 2022/11/10 for v1

#include:tcolorbox
# loads skins option of tcolorbox
#include:xstring
#include:hyperref

# from skins option of tcolorbox
#include:tikz

\cvssScore{CVSS string}
\cvssScorepretty{CVSS string}
\cvssLevel{CVSS string}
\cvssLevelpretty{CVSS string}
\cvssTag{CVSS string}
\cvssPrint{CVSS string}

\category{CVSS score}
\cvssFrame{CVSS score}

# not documented
\scoreLow#S
\scoreMed#S
\scoreHigh#S
\scoreCrit#S