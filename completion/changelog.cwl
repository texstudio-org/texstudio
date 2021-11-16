# changelog package
# Matthew Bertucci 11/16/2021 for v2.4.0

#include:xparse
#include:xkeyval
#include:translations

\begin{changelog}
\begin{changelog}[options%keyvals]
\end{changelog}

\begin{version}
\begin{version}[options%keyvals]
\end{version}

\shortversion{options%keyvals}

#keyvals:\begin{changelog}
section#true,false
sectioncmd=%<command%>
title=%<text%>
label=##l
#endkeyvals

#keyvals:\begin{changelog},\begin{version},\shortversion
version=%<version%>
v=%<version%>
author=%<author%>
date=%<date%>
yanked#true,false
simple#true,false
short#true,false
#endkeyvals

#keyvals:\shortversion
changes=%<changes text%>
#endkeyvals

\added
\changed
\deprecated
\removed
\fixed
\security
\misc

\changelogyanked

\begin{changelogdescription}#*
\end{changelogdescription}#*
\begin{changelogitemize}#*
\end{changelogitemize}#*