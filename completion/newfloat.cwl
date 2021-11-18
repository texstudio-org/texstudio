# newfloat package
# Matthew Bertucci 11/17/2021 for v1.1

#include:keyval

\newfloatsetup{options%keyvals}

#keyvals:\newfloatsetup
within=%<<counter> or none%>
chapterlistsgap=##L
#endkeyvals

\DeclareFloatingEnvironment{envname}#N
\DeclareFloatingEnvironment[options%keyvals]{envname}#N

\SetupFloatingEnvironment{envname}{options%keyvals}

#keyvals:\DeclareFloatingEnvironment,\SetupFloatingEnvironment
fileext=%<file extension%>
listname=%<list name%>
name=%<name%>
placement=%<combination of htbp%>
within=%<<counter> or none%>
chapterlistsgaps=#on,off
without
planb#true,false
planb-fileext=%<file extension%>
#endkeyvals

\ForEachFloatingEnvironment{code}
\PrepareListOf{envname}{code}