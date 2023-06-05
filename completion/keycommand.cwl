# keycommand package
# Matthew Bertucci 2/22/2022 for v3.1415

#include:etex
#include:kvsetkeys
#include:xkeyval
#include:etoolbox

\newkeycommand{cmd}[keys=defaults]{def}#d
\newkeycommand{cmd}[keys=defaults][args]{def}#d
\newkeycommand{cmd}[keys=defaults][OptKey][args]{def}#d
\newkeycommand[short-unexpand]{cmd}[keys=defaults]{def}#*d
\newkeycommand[short-unexpand]{cmd}[keys=defaults][args]{def}#*d
\newkeycommand[short-unexpand]{cmd}[keys=defaults][OptKey][args]{def}#*d
\newkeycommand*{cmd}[keys=defaults]{def}#d
\newkeycommand*{cmd}[keys=defaults][args]{def}#d
\newkeycommand*{cmd}[keys=defaults][OptKey][args]{def}#d
\newkeycommand*[short-unexpand]{cmd}[keys=defaults]{def}#*d
\newkeycommand*[short-unexpand]{cmd}[keys=defaults][args]{def}#*d
\newkeycommand*[short-unexpand]{cmd}[keys=defaults][OptKey][args]{def}#*d
\newkeycommand+{cmd}[keys=defaults]{def}#d
\newkeycommand+{cmd}[keys=defaults][args]{def}#d
\newkeycommand+{cmd}[keys=defaults][OptKey][args]{def}#d
\newkeycommand+[short-unexpand]{cmd}[keys=defaults]{def}#*d
\newkeycommand+[short-unexpand]{cmd}[keys=defaults][args]{def}#*d
\newkeycommand+[short-unexpand]{cmd}[keys=defaults][OptKey][args]{def}#*d

\renewkeycommand{cmd}[keys=defaults]{def}
\renewkeycommand{cmd}[keys=defaults][args]{def}
\renewkeycommand{cmd}[keys=defaults][OptKey][args]{def}
\renewkeycommand[short-unexpand]{cmd}[keys=defaults]{def}#*
\renewkeycommand[short-unexpand]{cmd}[keys=defaults][args]{def}#*
\renewkeycommand[short-unexpand]{cmd}[keys=defaults][OptKey][args]{def}#*
\renewkeycommand*{cmd}[keys=defaults]{def}
\renewkeycommand*{cmd}[keys=defaults][args]{def}
\renewkeycommand*{cmd}[keys=defaults][OptKey][args]{def}
\renewkeycommand*[short-unexpand]{cmd}[keys=defaults]{def}#*
\renewkeycommand*[short-unexpand]{cmd}[keys=defaults][args]{def}#*
\renewkeycommand*[short-unexpand]{cmd}[keys=defaults][OptKey][args]{def}#*
\renewkeycommand+{cmd}[keys=defaults]{def}
\renewkeycommand+{cmd}[keys=defaults][args]{def}
\renewkeycommand+{cmd}[keys=defaults][OptKey][args]{def}
\renewkeycommand+[short-unexpand]{cmd}[keys=defaults]{def}#*
\renewkeycommand+[short-unexpand]{cmd}[keys=defaults][args]{def}#*
\renewkeycommand+[short-unexpand]{cmd}[keys=defaults][OptKey][args]{def}#*

\providekeycommand{cmd}[keys=defaults]{def}#d
\providekeycommand{cmd}[keys=defaults][args]{def}#d
\providekeycommand{cmd}[keys=defaults][OptKey][args]{def}#d
\providekeycommand[short-unexpand]{cmd}[keys=defaults]{def}#*d
\providekeycommand[short-unexpand]{cmd}[keys=defaults][args]{def}#*d
\providekeycommand[short-unexpand]{cmd}[keys=defaults][OptKey][args]{def}#*d
\providekeycommand*{cmd}[keys=defaults]{def}#d
\providekeycommand*{cmd}[keys=defaults][args]{def}#d
\providekeycommand*{cmd}[keys=defaults][OptKey][args]{def}#d
\providekeycommand*[short-unexpand]{cmd}[keys=defaults]{def}#*d
\providekeycommand*[short-unexpand]{cmd}[keys=defaults][args]{def}#*d
\providekeycommand*[short-unexpand]{cmd}[keys=defaults][OptKey][args]{def}#*d
\providekeycommand+{cmd}[keys=defaults]{def}#d
\providekeycommand+{cmd}[keys=defaults][args]{def}#d
\providekeycommand+{cmd}[keys=defaults][OptKey][args]{def}#d
\providekeycommand+[short-unexpand]{cmd}[keys=defaults]{def}#*d
\providekeycommand+[short-unexpand]{cmd}[keys=defaults][args]{def}#*d
\providekeycommand+[short-unexpand]{cmd}[keys=defaults][OptKey][args]{def}#*d

\newkeyenvironment{envname}[keys=defaults]{begdef}{enddef}#N
\newkeyenvironment{envname}[keys=defaults][args]{begdef}{enddef}#N
\newkeyenvironment{envname}[keys=defaults][OptKey][args]{begdef}{enddef}#N
\newkeyenvironment[short-unexpand]{envname}[keys=defaults]{begdef}{enddef}#*N
\newkeyenvironment[short-unexpand]{envname}[keys=defaults][args]{begdef}{enddef}#*N
\newkeyenvironment[short-unexpand]{envname}[keys=defaults][OptKey][args]{begdef}{enddef}#*N
\newkeyenvironment*{envname}[keys=defaults]{begdef}{enddef}#N
\newkeyenvironment*{envname}[keys=defaults][args]{begdef}{enddef}#N
\newkeyenvironment*{envname}[keys=defaults][OptKey][args]{begdef}{enddef}#N
\newkeyenvironment*[short-unexpand]{envname}[keys=defaults]{begdef}{enddef}#*N
\newkeyenvironment*[short-unexpand]{envname}[keys=defaults][args]{begdef}{enddef}#*N
\newkeyenvironment*[short-unexpand]{envname}[keys=defaults][OptKey][args]{begdef}{enddef}#*N
\newkeyenvironment+{envname}[keys=defaults]{begdef}{enddef}#N
\newkeyenvironment+{envname}[keys=defaults][args]{begdef}{enddef}#N
\newkeyenvironment+{envname}[keys=defaults][OptKey][args]{begdef}{enddef}#N
\newkeyenvironment+[short-unexpand]{envname}[keys=defaults]{begdef}{enddef}#*N
\newkeyenvironment+[short-unexpand]{envname}[keys=defaults][args]{begdef}{enddef}#*N
\newkeyenvironment+[short-unexpand]{envname}[keys=defaults][OptKey][args]{begdef}{enddef}#*N

\renewkeyenvironment{envname}[keys=defaults]{begdef}{enddef}
\renewkeyenvironment{envname}[keys=defaults][args]{begdef}{enddef}
\renewkeyenvironment{envname}[keys=defaults][OptKey][args]{begdef}{enddef}
\renewkeyenvironment[short-unexpand]{envname}[keys=defaults]{begdef}{enddef}#*
\renewkeyenvironment[short-unexpand]{envname}[keys=defaults][args]{begdef}{enddef}#*
\renewkeyenvironment[short-unexpand]{envname}[keys=defaults][OptKey][args]{begdef}{enddef}#*
\renewkeyenvironment*{envname}[keys=defaults]{begdef}{enddef}
\renewkeyenvironment*{envname}[keys=defaults][args]{begdef}{enddef}
\renewkeyenvironment*{envname}[keys=defaults][OptKey][args]{begdef}{enddef}
\renewkeyenvironment*[short-unexpand]{envname}[keys=defaults]{begdef}{enddef}#*
\renewkeyenvironment*[short-unexpand]{envname}[keys=defaults][args]{begdef}{enddef}#*
\renewkeyenvironment*[short-unexpand]{envname}[keys=defaults][OptKey][args]{begdef}{enddef}#*
\renewkeyenvironment+{envname}[keys=defaults]{begdef}{enddef}
\renewkeyenvironment+{envname}[keys=defaults][args]{begdef}{enddef}
\renewkeyenvironment+{envname}[keys=defaults][OptKey][args]{begdef}{enddef}
\renewkeyenvironment+[short-unexpand]{envname}[keys=defaults]{begdef}{enddef}#*
\renewkeyenvironment+[short-unexpand]{envname}[keys=defaults][args]{begdef}{enddef}#*
\renewkeyenvironment+[short-unexpand]{envname}[keys=defaults][OptKey][args]{begdef}{enddef}#*

\commandkey{key%plain}
\getcommandkey{key%plain}
\ifcommandkey{key%plain}{true}{false}

\showcommandkeys{keys%plain}#*
\showcommandkey{key%plain}#*

\default#S
\next#S
