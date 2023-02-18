# changelog package
# Matthew Bertucci 2023/02/17 for v2.5.0

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
remark=%<text%>
remarks={%<text1,text2,...%>}
simple#true,false
short#true,false
#endkeyvals

#keyvals:\shortversion
changes=%<change text%>
#endkeyvals

\added
\changed
\deprecated
\removed
\fixed
\security
\misc

\newchangelogsection{command}{description%text}#d

\begin{changelogdescription}#*
\end{changelogdescription}#*
\begin{changelogitemize}#*
\end{changelogitemize}#*
\changelogyanked#*
\changelogremark{remark%text}#*
