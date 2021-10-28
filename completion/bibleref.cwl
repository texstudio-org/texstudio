# bibleref package
# Matthew Bertucci 10/23/2021 for v1.25

#include:ifthen
#include:fmtcount
#include:amsgen
#include:ifxetex

\bibleverse{book title}
\bibleverse{book title}(chapter:verse)

\BRvrsep#*
\BRvsep#*
\BRchsep#*
\BRchvsep#*
\BRperiod#*

\biblerefstyle{style}
\setbooktitle{name}{new title}
\setindexbooktitle{name}{title%plain}
\addbiblebook{name}{title%plain}
\newbiblerefstyle{style name}{commands}

\ibibleverse{book title}
\ibibleverse{book title}(chapter:verse)
\ibibleverse[format]{book title}(chapter:verse)
\bvidxpgformat#*
\ibiblechvs{book title}
\ibiblechvs{book title}(chapter:verse)
\ibiblechvs[format]{book title}(chapter:verse)
\ibiblevs{book title}
\ibiblevs{book title}(chapter:verse)
\ibiblevs[format]{book title}(chapter:verse)
\ibible{book title}
\ibible{book title}(chapter:verse)
\ibible[format]{book title}(chapter:verse)

\biblerefcategory{category title}
\biblerefcategory[sort key]{category title}

\biblerefindex#*
\biblerefmap{label}{new sort key}#*