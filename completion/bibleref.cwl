# bibleref package
# Matthew Bertucci 2022/05/30 for v1.25

#include:ifthen
#include:fmtcount
#include:amsgen
#include:ifxetex

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
\brabbrvname#*
\braltabbrvname#*
\BRbkchsep#*
\BRbooknumberstyle{text}#*
\BRbookof#*
\BRbooktitlestyle{text}#*
\BRchapterstyle{text}#*
\BRepistlenumberstyle{text}#*
\BRepistleof#*
\BRepistleto#*
\BRepistletothe#*
\brfullname#*
\BRgospel#*
\BRotherchapterstyle{text}#*
\BRversestyle{text}#*
\BRversesuffixstyle{text}#*
