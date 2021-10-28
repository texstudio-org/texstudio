# xargs package
# Matthew Bertucci 10/27/2021 for v1.1

#include:xkeyval

\newcommandx{cmd}[args][list%keyvals]{def}#d
\newcommandx{cmd}[args]{def}#*d
\newcommandx{cmd}{def}#*d
\newcommandx*{cmd}[args][list%keyvals]{def}#d
\newcommandx*{cmd}[args]{def}#*d
\newcommandx*{cmd}{def}#*d
\renewcommandx{cmd}[args][list%keyvals]{def}#d
\renewcommandx{cmd}[args]{def}#*d
\renewcommandx{cmd}{def}#*d
\renewcommandx*{cmd}[args][list%keyvals]{def}#d
\renewcommandx*{cmd}[args]{def}#*d
\renewcommandx*{cmd}{def}#*d
\providecommandx{cmd}[args][list%keyvals]{def}#d
\providecommandx{cmd}[args]{def}#*d
\providecommandx{cmd}{def}#*d
\providecommandx*{cmd}[args][list%keyvals]{def}#d
\providecommandx*{cmd}[args]{def}#*d
\providecommandx*{cmd}{def}#*d
\newenvironmentx{envname}[args][list%keyvals]{begdef}{enddef}#N
\newenvironmentx{envname}[args]{begdef}{enddef}#*N
\newenvironmentx{envname}{begdef}{enddef}#*N
\newenvironmentx*{envname}[args][list%keyvals]{begdef}{enddef}#N
\newenvironmentx*{envname}[args]{begdef}{enddef}#*N
\newenvironmentx*{envname}{begdef}{enddef}#*N
\renewenvironmentx{envname}[args][list%keyvals]{begdef}{enddef}#N
\renewenvironmentx{envname}[args]{begdef}{enddef}#*N
\renewenvironmentx{envname}{begdef}{enddef}#*N
\renewenvironmentx*{envname}[args][list%keyvals]{begdef}{enddef}#N
\renewenvironmentx*{envname}[args]{begdef}{enddef}#*N
\renewenvironmentx*{envname}{begdef}{enddef}#*N
\DeclareRobustCommandx{cmd}[args][list%keyvals]{def}#*d
\DeclareRobustCommandx{cmd}[args]{def}#*d
\DeclareRobustCommandx{cmd}{def}#*d
\DeclareRobustCommandx*{cmd}[args][list%keyvals]{def}#*d
\DeclareRobustCommandx*{cmd}[args]{def}#*d
\DeclareRobustCommandx*{cmd}{def}#*d
\CheckCommandx{cmd}[args][list%keyvals]{def}#*
\CheckCommandx{cmd}[args]{def}#*
\CheckCommandx{cmd}{def}#*
\CheckCommandx*{cmd}[args][list%keyvals]{def}#*
\CheckCommandx*{cmd}[args]{def}#*
\CheckCommandx*{cmd}{def}#*

#keyvals:\newcommandx#c,\newcommandx*#c,\renewcommandx#c,\renewcommandx*#c,\providecommandx#c,\providecommandx*#c,\newenvironmentx#c,\newenvironmentx*#c,\renewenvironmentx#c,\renewenvironmentx*#c,\DeclareRobustCommandx#c,\DeclareRobustCommandx*#c,\CheckCommandx#c,\CheckCommandx*#c
%<num%>=%<val%>
usedefault
usedefault=%<flag%>
addprefix=%<prefix cmds%>
#endkeyvals