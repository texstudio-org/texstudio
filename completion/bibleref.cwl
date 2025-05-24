# bibleref package
# Matthew Bertucci 2025/05/18 for v1.26.0

#include:ifthen
#include:fmtcount
#include:amsgen
#include:ifxetex
#include:xstring

#keyvals:\usepackage/bibleref#c,\biblerefstyle
default
jerusalem
anglosaxon
JEH
MHRA
NTG
MLA
chicago
text
splitmultiplerefinindex
%biblerefstyle
#endkeyvals

\bibleverse{book title}
\bibleverse{book title}(chapter:verse)

\BRvrsep#*
\BRvsep#*
\BRchsep#*
\BRchvsep#*
\BRperiod#*

\biblerefstyle{style name%keyvals}
\setbooktitle{name}{new title}
\setindexbooktitle{name}{title%plain}
\addbiblebook{name}{title%plain}
\brthreeabbrvname
\newbiblerefstyle{style name%specialDef}{commands}#s#%biblerefstyle

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

# not documented
\brabbrvname#S
\braltabbrvname#S
\BRbkchsep#S
\BRbooknumberstyle{text}#S
\BRbookof#S
\BRbooktitlestyle{text}#S
\BRchapterstyle{text}#S
\BRepistlenumberstyle{text}#S
\BRepistleof#S
\BRepistleto#S
\BRepistletothe#S
\brfullname#S
\BRgospel#S
\BRotherchapterstyle{text}#S
\BRversestyle{text}#S
\BRversesuffixstyle{text}#S
