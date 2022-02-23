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

\renewkeycommand{cmd}[keys=defaults]{def}#d
\renewkeycommand{cmd}[keys=defaults][args]{def}#d
\renewkeycommand{cmd}[keys=defaults][OptKey][args]{def}#d
\renewkeycommand[short-unexpand]{cmd}[keys=defaults]{def}#*d
\renewkeycommand[short-unexpand]{cmd}[keys=defaults][args]{def}#*d
\renewkeycommand[short-unexpand]{cmd}[keys=defaults][OptKey][args]{def}#*d
\renewkeycommand*{cmd}[keys=defaults]{def}#d
\renewkeycommand*{cmd}[keys=defaults][args]{def}#d
\renewkeycommand*{cmd}[keys=defaults][OptKey][args]{def}#d
\renewkeycommand*[short-unexpand]{cmd}[keys=defaults]{def}#*d
\renewkeycommand*[short-unexpand]{cmd}[keys=defaults][args]{def}#*d
\renewkeycommand*[short-unexpand]{cmd}[keys=defaults][OptKey][args]{def}#*d
\renewkeycommand+{cmd}[keys=defaults]{def}#d
\renewkeycommand+{cmd}[keys=defaults][args]{def}#d
\renewkeycommand+{cmd}[keys=defaults][OptKey][args]{def}#d
\renewkeycommand+[short-unexpand]{cmd}[keys=defaults]{def}#*d
\renewkeycommand+[short-unexpand]{cmd}[keys=defaults][args]{def}#*d
\renewkeycommand+[short-unexpand]{cmd}[keys=defaults][OptKey][args]{def}#*d

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

\newkeyenvironment{envname}[keys=defaults]{begindef}{enddef}#N
\newkeyenvironment{envname}[keys=defaults][args]{begindef}{enddef}#N
\newkeyenvironment{envname}[keys=defaults][OptKey][args]{begindef}{enddef}#N
\newkeyenvironment[short-unexpand]{envname}[keys=defaults]{begindef}{enddef}#*N
\newkeyenvironment[short-unexpand]{envname}[keys=defaults][args]{begindef}{enddef}#*N
\newkeyenvironment[short-unexpand]{envname}[keys=defaults][OptKey][args]{begindef}{enddef}#*N
\newkeyenvironment*{envname}[keys=defaults]{begindef}{enddef}#N
\newkeyenvironment*{envname}[keys=defaults][args]{begindef}{enddef}#N
\newkeyenvironment*{envname}[keys=defaults][OptKey][args]{begindef}{enddef}#N
\newkeyenvironment*[short-unexpand]{envname}[keys=defaults]{begindef}{enddef}#*N
\newkeyenvironment*[short-unexpand]{envname}[keys=defaults][args]{begindef}{enddef}#*N
\newkeyenvironment*[short-unexpand]{envname}[keys=defaults][OptKey][args]{begindef}{enddef}#*N
\newkeyenvironment+{envname}[keys=defaults]{begindef}{enddef}#N
\newkeyenvironment+{envname}[keys=defaults][args]{begindef}{enddef}#N
\newkeyenvironment+{envname}[keys=defaults][OptKey][args]{begindef}{enddef}#N
\newkeyenvironment+[short-unexpand]{envname}[keys=defaults]{begindef}{enddef}#*N
\newkeyenvironment+[short-unexpand]{envname}[keys=defaults][args]{begindef}{enddef}#*N
\newkeyenvironment+[short-unexpand]{envname}[keys=defaults][OptKey][args]{begindef}{enddef}#*N

\renewkeyenvironment{envname}[keys=defaults]{begindef}{enddef}#N
\renewkeyenvironment{envname}[keys=defaults][args]{begindef}{enddef}#N
\renewkeyenvironment{envname}[keys=defaults][OptKey][args]{begindef}{enddef}#N
\renewkeyenvironment[short-unexpand]{envname}[keys=defaults]{begindef}{enddef}#*N
\renewkeyenvironment[short-unexpand]{envname}[keys=defaults][args]{begindef}{enddef}#*N
\renewkeyenvironment[short-unexpand]{envname}[keys=defaults][OptKey][args]{begindef}{enddef}#*N
\renewkeyenvironment*{envname}[keys=defaults]{begindef}{enddef}#N
\renewkeyenvironment*{envname}[keys=defaults][args]{begindef}{enddef}#N
\renewkeyenvironment*{envname}[keys=defaults][OptKey][args]{begindef}{enddef}#N
\renewkeyenvironment*[short-unexpand]{envname}[keys=defaults]{begindef}{enddef}#*N
\renewkeyenvironment*[short-unexpand]{envname}[keys=defaults][args]{begindef}{enddef}#*N
\renewkeyenvironment*[short-unexpand]{envname}[keys=defaults][OptKey][args]{begindef}{enddef}#*N
\renewkeyenvironment+{envname}[keys=defaults]{begindef}{enddef}#N
\renewkeyenvironment+{envname}[keys=defaults][args]{begindef}{enddef}#N
\renewkeyenvironment+{envname}[keys=defaults][OptKey][args]{begindef}{enddef}#N
\renewkeyenvironment+[short-unexpand]{envname}[keys=defaults]{begindef}{enddef}#*N
\renewkeyenvironment+[short-unexpand]{envname}[keys=defaults][args]{begindef}{enddef}#*N
\renewkeyenvironment+[short-unexpand]{envname}[keys=defaults][OptKey][args]{begindef}{enddef}#*N

\commandkey{key%plain}
\getcommandkey{key%plain}
\ifcommandkey{key%plain}{true}{false}

\showcommandkeys{keys%plain}#*
\showcommandkey{key%plain}#*

\default#S
\next#S