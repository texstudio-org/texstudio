# external tcolorboxlibrary
# 2022/12/12 for v5.1.1

#include:incgraph
# loads processing tcolorbox library

\tcbEXTERNALIZE
\begin{tcbexternal}{name}
\begin{tcbexternal}[options%keyvals]{name}
\end{tcbexternal}
\begin{extcolorbox}{name}
\begin{extcolorbox}[options%keyvals]{name}[tcolorbox options]
\end{extcolorbox}
\begin{extikzpicture}{name}
\begin{extikzpicture}[options%keyvals]{name}[tikz options]
\end{extikzpicture}
\tcbifexternal{true}{false}
\newtcbexternalizeenvironment{newenv%envname}{env}{options%keyvals}{begdef}{enddef}#N
\renewtcbexternalizeenvironment{newenv%envname}{env}{options%keyvals}{begdef}{enddef}
\newtcbexternalizetcolorbox{newenv%envname}{env}{options%keyvals}{begin end options}#N
\renewtcbexternalizetcolorbox{newenv%envname}{env}{options%keyvals}{begin end options}

#keyvals:\begin{tcbexternal},\begin{extcolorbox},\begin{extikzpicture},\newtcbexternalizeenvironment,\renewtcbexternalizeenvironment,\newtcbexternalizetcolorbox,\renewtcbexternalizetcolorbox
runner=%<file name%>
prefix=%<text%>
externalize#true,false
force remake#true,false
!
-
name=%<name%>
safety=%<length%>
environment=%<envname%>
environment with percent#true,false
minipage
minipage=##L
plain
compiler=%<text%>
runs=%<number%>
input source on error#true,false
preclass={%<code%>}
PassOptionsToPackage={%<options%>}{%<package%>}
PassOptionsToClass={%<options%>}{%<class%>}
clear preclass
preamble={%<code%>}
preamble tcbset={%<options%>}
clear preamble
#endkeyvals

#keyvals:\tcbset
external/runner=%<file name%>
external/prefix=%<text%>
external/externalize#true,false
external/force remake#true,false
external/!
external/-
external/name=%<name%>
external/safety=%<length%>
external/environment=%<envname%>
external/environment with percent#true,false
external/minipage
external/minipage=##L
external/plain
external/compiler=%<text%>
external/runs=%<number%>
external/input source on error#true,false
external/preclass={%<code%>}
external/PassOptionsToPackage={%<options%>}{%<package%>}
external/PassOptionsToClass={%<options%>}{%<class%>}
external/clear preclass
external/preamble={%<code%>}
external/preamble tcbset={%<options%>}
external/clear preamble
#endkeyvals

#keyvals:\tcbset,\begin{tcblisting},\tcbinputlisting,\newtcblisting,\renewtcblisting,\newtcbinputlisting,\renewtcbinputlisting,\DeclareTCBListing,\NewTCBListing,\RenewTCBListing,\ProvideTCBListing,\DeclareTCBInputListing,\NewTCBInputListing,\RenewTCBInputListing,\ProvideTCBInputListing
externalize listing=%<name%>
externalize listing!=%<name%>
#endkeyvals

#keyvals:\tcbset,\begin{dispExample*}
externalize example=%<name%>
externalize example!=%<name%>
#endkeyvals

# from processing tcolorbox library
#include:pdftexcmds
#include:shellesc
\tcbprocmdfivesum#S
\tcbiffileprocess{condition}{source}{md5-file}{target}{true}{false}#*
