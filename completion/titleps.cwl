# titleps package
# Matthew Bertucci 12/3/2021 for v2.14

#keyvals:\usepackage/titleps#c
psfloats
outermarks
topmarks
botmarks
innermarks
extramarks
nopatches
#endkeyvals

\newpagestyle{name%specialDef}{commands}#s#%titlepspagestyle
\newpagestyle{name%specialDef}[global-style]{commands}
\renewpagestyle{name}{commands}
\renewpagestyle{name}[global-style]{commands}

#keyvals:\pagestyle#c
%titlepspagestyle
#endkeyvals

\sethead{odd-left}{odd-center}{odd-right}
\sethead[even-left][even-center][even-right]{odd-left}{odd-center}{odd-right}
\sethead*{odd-left}{odd-center}{odd-right}
\setfoot{odd-left}{odd-center}{odd-right}
\setfoot[even-left][even-center][even-right]{odd-left}{odd-center}{odd-right}
\setfoot*{odd-left}{odd-center}{odd-right}

\parttitle#*
\chaptertitle#*
\sectiontitle#*
\subsectiontitle#*
\subsubsectiontitle#*
\paragraphtitle#*
\subparagraphtitle#*
\ifthepart{true}{false}#*
\ifthechapter{true}{false}#*
\ifthesection{true}{false}#*
\ifthesubsection{true}{false}#*
\ifthesubsubsection{true}{false}#*
\iftheparagraph{true}{false}#*
\ifthesubparagraph{true}{false}#*

\settitlemarks{level-name,sublevel-name,...}
\settitlemarks*{level-name,sublevel-name,...}

\headrule
\footrule
\setheadrule{length}
\setfootrule{length}
\makeheadrule#*
\makefootrule#*

\setmarkboth{code}
\resetmarkboth

\widenhead{odd-left}{odd-right}
\widenhead[even-left][even-right]{odd-left}{odd-right}
\widenhead*{even-right/odd-left}{even-left/odd-right}
\setheadindent#S

\TitlepsPatchSection{level}#*
\TitlepsPatchSection*{level}#*

\bottitlemarks
\toptitlemarks
\firsttitlemarks
\nexttoptitlemarks
\outertitlemarks
\innertitlemarks

\newtitlemark{command}
\newtitlemark*{variable}

\pretitlemark{level}{text}
\pretitlemark*{level}{text}

\ifsamemark{group}{command}{true}{false}#*

#ifOption:psfloats
\setfloathead{odd-left}{odd-center}{odd-right}{extra}
\setfloathead[even-left][even-center][even-right]{odd-left}{odd-center}{odd-right}{extra}[floats]
\setfloathead*{odd-left}{odd-center}{odd-right}{extra}
\setfloatfoot{odd-left}{odd-center}{odd-right}{extra}
\setfloatfoot[even-left][even-center][even-right]{odd-left}{odd-center}{odd-right}{extra}[floats]
\setfloatfoot*{odd-left}{odd-center}{odd-right}{extra}
\nextfloathead{odd-left}{odd-center}{odd-right}{extra}
\nextfloathead[even-left][even-center][even-right]{odd-left}{odd-center}{odd-right}{extra}[floats]
\nextfloathead*{odd-left}{odd-center}{odd-right}{extra}
\nextfloatfoot{odd-left}{odd-center}{odd-right}{extra}
\nextfloatfoot[even-left][even-center][even-right]{odd-left}{odd-center}{odd-right}{extra}[floats]
\nextfloatfoot*{odd-left}{odd-center}{odd-right}{extra}
#endif

#ifOption:extramarks
\newshortmark{command}
\botshortmark{command}
\firstshortmark{command}
\nexttopshortmark{command}
\preshortmark{command}
\shortmark{command}
\topshortmark{command}
\newmarkset{markset}
\newextramark{markset}{command}
\newextramark*{markset}{command}
\botextramarks{markset}
\topextramarks{markset}
\firstextramarks{markset}
\nexttopextramarks{markset}
\outerextramarks{markset}
\innerextramarks{markset}
\extramark{counter}
\preextramark
\preshortmark
\settitlemarks*{level-name,sublevel-name,...}
#endif

\iftitle{arg}#*
\usepage#S
\setmarks#S
