# verbasef package
# Matthew Bertucci 2022/06/20 for v1.1

#include:vrbexin
#include:verbatim
#include:here

\VautoSubF{startline}{endline}{file}{caption}{label}
\VautoSubF[lines-numbered]{startline}{endline}{file}{caption}{label}
\VautoSfFont{font commands}
\VautoSfFont[linenum-font-commands]{font-commands}
\VautoPl{placement}
\VautoLines{lines-per-page}
\VautoLines[first-page-lines]{lines-per-page}

# not documented
\VautoSubFF{font commands}#*
\VautoSubFF[linenum-font-commands]{font-commands}#*
\ifsubstr{string}{substring}{true}{false}#*
\subz#S
\xxparse#S
