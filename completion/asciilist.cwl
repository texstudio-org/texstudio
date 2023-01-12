# asciilist package
# Matthew Bertucci 1/13/2022 for v2.2b

#include:etoolbox
#include:trimspaces

\begin{AsciiList}{item chars}
\begin{AsciiList}[environments%keyvals]{item chars}
\end{AsciiList}

\AsciiListFromFile{item chars}{file}#i
\AsciiListFromFile[environments%keyvals]{item chars}{file}#i
\AsciiListFromFiles{item chars}{file list}#i
\AsciiListFromFiles[environments%keyvals]{item chars}{file list}#i

#keyvals:\begin{AsciiList}#c,\AsciiListFromFile#c,\AsciiListFromFiles#c,\AsciiListSetEnvironments#c,\NewAsciiListEnv#c
chapter
section
subsection
subsubsection
section*
subsection*
subsubsection*
paragraph
Heading
Heading*
description
Description
itemize
enumerate
compactenum
compactenum<%<label%>>
compactitem
compactitem<%<label%>>
compactdesc
CompactDesc
Heading
Heading<%<level%>>
Heading*
Heading*<%<level%>>
%asciiregisteredenv
#endkeyvals

\AsciiListSetAutochars{chars}

\UP
\UP[integer]
\UPTO{integer}

\begin{AsciiDocList}
\begin{AsciiDocList}[char1=env1,...%keyvals]
\end{AsciiDocList}

\AsciiDocListFromFile{file}#i
\AsciiDocListFromFile[char1=env1,...%keyvals]{file}#i
\AsciiDocListFromFiles{file}#i
\AsciiDocListFromFiles[char1=env1,...%keyvals]{file}#i

#keyvals:\begin{AsciiDocList}#c,\AsciiDocListFromFile#c,\AsciiDocListFromFiles#c,\AsciiDocListSetEnvironments#c,\NewAsciiDocListEnv#c
*=%<envname%>
-=%<envname%>
!=%<envname%>
/=%<envname%>
+=%<envname%>
?=%<envname%>
;=%<envname%>
#endkeyvals

\AsciiListRegisterEnv{envname%specialDef}{begindef%definition}{enddef%definition}{itemdef%definition}#s#%asciiregisteredenv
\AsciiListRegisterDescEnv{envname%specialDef}#*s#%asciiregisteredenv
\AsciiListEndArg{command}
\AsciiListEndOArg{command}

\AsciiListSetEnvironments{environments%keyvals}
\NewAsciiListEnv{item chars}{envname}#N
\NewAsciiListEnv[environments%keyvals]{item chars}{envname}#N

\AsciiDocListSetEnvironments{char1=env1,...%keyvals}
\NewAsciiDocListEnv{envname}#N
\NewAsciiDocListEnv[char1=env1,...%keyvals]{envname}#N