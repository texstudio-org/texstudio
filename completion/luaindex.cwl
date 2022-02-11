# luaindex package
# Matthew Bertucci 2/8/2022 for v0.1b

#include:ifluatex
#include:luatexbase
#include:scrbase

\setupluaindex{options%keyvals}

#keyvals:\usepackage/luaindex#c,\setupluaindex,\newindex
sortorder=%<sort entry%>
locale=%<locale specifier%>
pageformat=%<command%>
singlepass
#endkeyvals

\see{text}{page}#*
\seealso{text}{page}#*
\seename#*
\alsoname#*

\newindex{index name}
\newindex[options%keyvals]{index name}

\luaindex{index name}{entry}#*
\luaindex{index name}[options%keyvals]{entry}#*
\luasubindex{index name}{entry}{subentry}#*
\luasubindex{index name}[options%keyvals]{entry}{subentry}#*
\luasubindex{index name}[options%keyvals]{entry}[options]{subentry}#*
\luasubsubindex{index name}{entry}{subentry}{subsubentry}#*
\luasubsubindex{index name}[options%keyvals]{entry}{subentry}{subsubentry}#*
\luasubsubindex{index name}[options%keyvals]{entry}[options]{subentry}[options]{subsubentry}#*
\index[options%keyvals]{entry}
\subindex{entry}{subentry}
\subindex[options%keyvals]{entry}{subentry}
\subindex[options%keyvals]{entry}[options]{subentry}
\subsubindex{entry}{subentry}{subsubentry}
\subsubindex[options%keyvals]{entry}{subentry}{subsubentry}
\subsubindex[options%keyvals]{entry}[options]{subentry}[options]{subsubentry}

#keyvals:\luaindex,\luasubindex,\luasubsubindex,\index,\subindex,\subsubindex
sort=%<sort entry%>
pageformat=%<command%>
locale=%<locale specifier%>
#endkeyvals

\printindex
\printindex[options%keyvals]

#keyvals:\printindex
index=%<index name%>
singlepass#true,false
#endkeyvals

\indexgroup{group}
\indexspace#*
\symbolsname#*
\numbersname#*
\indexpagenumbers{page number}
\indexpagenumber{page number}#*
\indexpagenumbersep#*