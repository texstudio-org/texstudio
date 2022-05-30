# bibleref-parse package
# Matthew Bertucci 2022/05/30 for v1.1

#include:etoolbox
#include:scrlfile
#include:bibleref

\biblerefparseset{options%keyvals}
\pbibleverse{passage}
\pbibleverse[options%keyvals]{passage}
\BRbksep#*
\pibibleverse{passage}
\pibibleverse[options%keyvals]{passage}
\pibiblechvs{passage}
\pibiblechvs[options%keyvals]{passage}
\pibiblevs{passage}
\pibiblevs[options%keyvals]{passage}

#keyvals:\usepackage/bibleref-parse#c,\biblerefparseset,\pbibleverse,\pibibleverse,\pibiblechvs,\pibiblevs
comma=#list,chvsep,likeBR,preferchvsep,preferlikeBR
#endkeyvals

\brpDefineBookPrefix{new book prefix}{book name}
\brpDefineBook{new book name}{book name}
\brpUndefBookPrefix{new book prefix}{book name}
\brpUndefBook{new book name}{book name}

\BRadditionsto#*
