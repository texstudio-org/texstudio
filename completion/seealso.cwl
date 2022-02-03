# seealso package
# Matthew Bertucci 2/1/2022 for v1.2

#include:etoolbox
#include:kvoptions

#keyvals:\usepackage/seealso#c
override#true,false
activecr#true,false
#endkeyvals

\seepage{entry}{page number}
\seealsopage{entry}{page number}
\seenopage{entry}{page number}#*
\seealsonopage{entry}{page number}#*
\see{entry}{page number}#*
\seealso{entry}{page number}#*
\SeealsoPrintList#*
\DeclareSeealsoMacro%<\macro%>{%<seelist%>}{%<name%>}
\DeclareSeealsoMacro{cmd}#Sd
\seealsosetup{options%keyvals}
\seealsosetup[seelists]{options%keyvals}
#keyvals:\seealsosetup
name=%<name%>
listsep=%<sep%>
itemsep=%<sep%>
nameformat=%<format code%>
itemformat=%<format code%>
pageformat=%<format code%>
#endkeyvals
\SeealsoGobble{char}