# external tikzlibrary
# 2022/11/21 for v3.1.9a

#include:pdftexcmds
#include:atveryend

\tikzexternalize
\tikzexternalize[options%keyvals]

#keyvals:\tikzexternalize#c
system call={%<template%>}
shell escape={%<command-line arg%>}
aux in dpth#true,false
prefix=%<file name prefix%>
figure name=%<name%>
disable dependency files
force remake#true,false
remake next#true,false
export next#true,false
export#true,false
up to date check=imple,md5,diff
figure list#true,false
mode=#only graphics,no graphics,only pictures,graphics if exists,list only,list and make
verbose IO#true,false
verbose optimize#true,false
verbose#true,false
optimize#true,false
optimize command away={%<command%>}{%<arg count%>}
only named
#endkeyvals

\tikzexternalrealjob
\tikzexternalcheckshellescape#*
\tikzsetexternalprefix{prefix}
\tikzsetnextfilename{file name%file}
\tikzsetfigurename{name}
\tikzappendtofigurename{suffix}
\tikzpicturedependsonfile{file name%file}
\tikzexternalimgextension#*
\tikzexternalfiledependsonfile{external graphics}{file name%file}
\tikzexternaldisable
\tikzexternalenable
\tikzifexternalizing{true code}{false code}
\tikzifexternalizingnext{true code}{false code}
\iftikzexternalremakenext#S
\tikzexternalremakenexttrue#S
\tikzexternalremakenextfalse#S
\iftikzexternalexportnext#S
\tikzexternalexportnexttrue#S
\tikzexternalexportnextfalse#S
\tikzifexternalizingcurrent{true code}{false code}#S
\tikzifexternaljobnamematches{jobname}{true code}{false code}#S
\tikzifexternalizehasbeencalled{true code}{false code}#S
\tikzexternallocked#S
\tikzexternalgetnextfilename{macro%cmd}#Sd
\tikzexternalgetcurrentfilename{macro%cmd}#Sd
\tikzexternaldepext#S
\tikzexternalmakefiledefaultdeprule#S
\tikzexternalifwritesmakefile{true code}{false code}#S
\tikzexternalwritetomakefile{code}#S
