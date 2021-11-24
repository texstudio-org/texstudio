# moderncvcollection package
# Matthew Bertucci 11/22/2021 for v2.2.0

#include:ifthen

\collectionnew{name}#*
\collectionadd{name}{item to add}#*
\collectionadd[key%plain]{name}{item to add}#*
\collectioncount{name}#*
\collectiongetitem{name}{element id}#*
\collectiongetkey{name}{element id}#*
\collectionloopbreak#*
\collectionloop{name}{operation sequence}#*
\collectionloopid#*
\collectionloopitem#*
\collectionloopkey#*
\collectionfindbykey{name}{key%plain}#*