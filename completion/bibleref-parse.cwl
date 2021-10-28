# bibleref-parse package
# Matthew Bertucci 10/23/2021 for v1.1

#include:etoolbox
#include:scrlfile
#include:bibleref

\biblerefparseset{options%keyvals}
\pbibleverse{passage}
\pbibleverse[options%keyvals]{passage}

#keyvals:\biblerefparseset,\pbibleverse
comma=#list,chvsep,likeBR,preferchvsep,preferlikeBR
#endkeyvals

\BRchvsep#*
\brpDefineBookPrefix{new book prefix}{book name}
\brpDefineBook{new book name}{book name}
\brpUndefBookPrefix{new book prefix}{book name}#*
\brpUndefBook{new book name}{book name}#*