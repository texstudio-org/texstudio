# emarks package
# Matthew Bertucci 2/22/2022 for v1.0

#include:etex

\marksthe{named-mark}{content}
\marksthe*{named-mark}{content}
\marksthecs{named-mark}{csname}
\marksthecs*{named-mark}{csname}

\thefirstmarks{named-mark}
\thebotmarks{named-mark}
\thetopmarks{named-mark}

\getthemarks{marks}{named-mark}{cmd}#d
\getthefirstmarks{named-mark}{cmd}#d
\getthebotmarks{named-mark}{cmd}#d
\getthetopmarks{named-mark}{cmd}#d
\firstmarks
\botmarks
\topmarks

\ifmarksvoid{marks}{named-mark}{true}{false}
\ifmarksequal{marks1}{marks2}{named-mark}{true}{false}
\showthemarks{named-mark}