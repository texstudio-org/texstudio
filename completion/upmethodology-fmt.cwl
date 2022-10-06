# upmethodology-fmt package
# Matthew Bertucci 2022/10/05 for release 2022/10/04

#include:upmethodology-p-common
#include:graphicx
#include:subcaption
#include:tabularx
#include:multicol
#include:colortbl
#include:picinpar
#include:amsmath
#include:amsthm
#include:thmtools
#include:pifont
#include:setspace
#include:varioref
#include:txfonts
#include:relsize
#include:xkeyval
#include:hyphenat
#include:bbm
#include:environ

#keyvals:\usepackage/upmethodology-fmt#c
french
francais
english
standardlists
#endkeyvals

\textsup{text%plain}
\textsub{text%plain}
\Emph{text}
\trademark
\regmark
\smalltrade
\smallreg
\smallcopy
\ust
\und
\urd
\uth
\R
\N
\Z
\C
\Q
\powerset
\sgn#m
\begin{graphicspathcontext}{path%definition}
\end{graphicspathcontext}
\mfigure{options%keyvals}{imagefile}{caption%text}{label}#g
\mfigure[position]{options%keyvals}{imagefile}{caption%text}{label}#g
\mfigure*{options%keyvals}{imagefile}{caption%text}{label}#g
\mfigure*[position]{options%keyvals}{imagefile}{caption%text}{label}#g
\figref{label}
\figpageref{label}
\msubfigure{options%keyvals}{imagefile}{caption%text}#g
\begin{mfigures}{caption%text}{label}
\begin{mfigures}[position]{caption%text}{label}
\end{mfigures}
\begin{mfigures*}{caption%text}{label}
\begin{mfigures*}[position]{caption%text}{label}
\end{mfigures*}
\DeclareGraphicsExtensionsWtex{extensions}
\includegraphicswtex{imagefile}#g
\includegraphicswtex[options%keyvals]{imagefile}#g
\includefigurewtex{imagefile}#*g
\includefigurewtex[options%keyvals]{imagefile}#*g
\figmath{id}{expr%formula}
\figtext{id}{expr}
\mfigurewtex{options%keyvals}{imagefile}{caption%text}{label}#g
\mfigurewtex[position]{options%keyvals}{imagefile}{caption%text}{label}#g
\mfigurewtex*{options%keyvals}{imagefile}{caption%text}{label}#g
\mfigurewtex*[position]{options%keyvals}{imagefile}{caption%text}{label}#g
backtableheader#B
fronttableheader#B
\tabularheaderstyle{text}#*
\tabulartitlespec{colspec}
\begin{mtabular}{N}{cols}#\tabular
\begin{mtabular}[width]{N}{cols}#\tabular
\end{mtabular}
\tabulartitle{title%text}#/mtabular
\tabulartitleinside{title%text}#/mtabular
\tabularheader{%<header1%>}{%<header2%>}%<...{headerN}%>
\tabularrowheader{title%text}#/mtabular
\begin{mtable}{width}{N}{cols}{caption%text}{label}#\tabular
\begin{mtable}[options%keyvals]{width}{N}{cols}{caption%text}{label}#\tabular
\end{mtable}
\captionastitle#/mtable
\tablenote{text}#/mtable
\tabref{label}
\tabpageref{label}
sectiontitlecolor#B
chaptertitlecolor#B
parttitlecolor#B
\parttoc{title}#L0
\parttoc[short title]{title}#L0
\parttoc*{title}#L0
\parttoc*[short title]{title}#L0
\chaptertoc{title}#L1
\chaptertoc[short title]{title}#L1
\chaptertoc*{title}#L1
\chaptertoc*[short title]{title}#L1
\sectiontoc{title}#L2
\sectiontoc[short title]{title}#L2
\sectiontoc*{title}#L2
\sectiontoc*[short title]{title}#L2
\subsectiontoc{title}#L3
\subsectiontoc[short title]{title}#L3
\subsectiontoc*{title}#L3
\subsectiontoc*[short title]{title}#L3
\subsubsectiontoc{title}#L4
\subsubsectiontoc[short title]{title}#L4
\subsubsectiontoc*{title}#L4
\subsubsectiontoc*[short title]{title}#L4
\chapterfull{title}{header%text}#L1
\chapterfull[short title]{title}{header%text}#L1
\chapterfull*{title}{header%text}#L1
\chapterfull*[short title]{title}{header%text}#L1
\sectionfull{title}{header%text}#L2
\sectionfull[short title]{title}{header%text}#L2
\sectionfull*{title}{header%text}#L2
\sectionfull*[short title]{title}{header%text}#L2
\bibsize{size cmd}
\savecounter{counter}
\restorecounter{counter}
\saveenumcounter
\restoreenumcounter
\setenumcounter{value}
\getenumcounter
\savefootnote{text}{id}
\savefootnote*{text}{id}
\reffootnote{id}
\begin{umlinpar}{imagefile}#g
\begin{umlinpar}[width]{imagefile}#g
\end{umlinpar}
\makedate{day}{month}{year}
\extractyear{date}
\extractmonth{date}
\extractday{date}
\makenamespacing{text%plain}
\upmmakename{first}{last}{separator}
\upmmakename[von]{first}{last}{separator}
\upmmakenamestar{first}{last}{separator}#*
\upmmakenamestar[von]{first}{last}{separator}#*
\makename{first}{last}
\makename[von]{first}{last}
\makelastname{last name}
\makelastname[von]{last name}
\makefirstname{first name}
\prname{first}{last}
\prname[von]{first}{last}
\prname*{first}{last}
\prname*[von]{first}{last}
\drname{first}{last}
\drname[von]{first}{last}
\drname*{first}{last}
\drname*[von]{first}{last}
\phdname{first}{last}
\phdname[von]{first}{last}
\phdname*{first}{last}
\phdname*[von]{first}{last}
\scdname{first}{last}
\scdname[von]{first}{last}
\scdname*{first}{last}
\scdname*[von]{first}{last}
\mdname{first}{last}
\mdname[von]{first}{last}
\mdname*{first}{last}
\mdname*[von]{first}{last}
\pengname{first}{last}
\pengname[von]{first}{last}
\pengname*{first}{last}
\pengname*[von]{first}{last}
\iengname{first}{last}
\iengname[von]{first}{last}
\iengname*{first}{last}
\iengname*[von]{first}{last}
\inlineenumerationlabel{text}#*
\begin{inlineenumeration}
\end{inlineenumeration}
\enumdescriptionlabel{text}#*
\enumdescriptioncounterseparator#*
\enumdescriptionlabelseparator#*
\begin{description}[separator]
\begin{enumdescriptionx}
\begin{enumdescriptionx}[type]
\end{enumdescriptionx}
\begin{enumdescription}{counter prefix}{counter postfix}
\begin{enumdescription}[type]{counter prefix}{counter postfix}
\end{enumdescription}
\begin{enumerate}[labeltype]
\begin{upmfontsize}{size cmd}#*
\end{upmfontsize}#*
\begin{framedminipage}{width}
\end{framedminipage}
\begin{framedcolorminipage}{width}{border color}{background color}
\begin{framedcolorminipage}{width}{color}{color}#S
\end{framedcolorminipage}
highlightboxbackground_caution#B
highlightboxforeground_caution#B
highlightboxborder_caution#B
highlightboxbackground_info#B
highlightboxforeground_info#B
highlightboxborder_info#B
highlightboxbackground_question#B
highlightboxforeground_question#B
highlightboxborder_question#B
\begin{upmcaution}
\begin{upmcaution}[width]
\end{upmcaution}
\begin{upminfo}
\begin{upminfo}[width]
\end{upminfo}
\begin{upmquestion}
\begin{upmquestion}[width]
\end{upmquestion}
\url{URL}#U
\href{URL}{text%plain}#U
\textdown{text}
definitionbackground#B
definitionheaderforeground#B
definitionborder#B
definitiontextforeground#B
\definitionname#*
\listdefinitionname#*
#keyvals:\theoremstyle#c
upmdefinition
#endkeyvals
\declareupmtheorem{envname}{label%text}{list title%text}#N
\declareupmtheorem[theoremstyle]{envname}{label%text}{list title%text}#N
\upmtheoremopt{arg}#*
\begin{definition}
\begin{definition}[header%text]
\end{definition}
emphboxbackground#B
emphboxborder#B
emphboxtext#B
emphboxbackgroundb#B
emphboxbackgroundc#B
\begin{emphbox}
\begin{emphbox}[width]
\end{emphbox}
\begin{titleemphbox}{title%text}
\begin{titleemphbox}[width]{title%text}
\end{titleemphbox}
\begin{titleemphbox2}{title%text}
\begin{titleemphbox2}[width]{title%text}
\end{titleemphbox2}
\begin{titleemphbox3}{title%text}
\begin{titleemphbox3}[width]{title%text}
\end{titleemphbox3}
\overridedescriptionenvironment#*
\restoredescriptionenvironment#*

#keyvals:\mfigure,\mfigure*,\msubfigure,\mfigurewtex,\mfigurewtex*
alt={%<alt text%>}
bb=%<llx lly urx ury%>
bbllx=
bblly=
bburx=
bbury=
natwidth=
natheight=
hiresbb#true,false
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
viewport=%<llx lly urx ury%>
trim=%<llx lly urx ury%>
angle=%<degrees%>
origin=
width=##L
height=##L
totalheight=##L
keepaspectratio#true,false
scale=%<factor%>
clip#true,false
draft#true,false
type=%<file type%>
ext=%<file extension%>
read=%<read-file extension%>
command=
quiet
page=%<page number%>
interpolate#true,false
decodearray={%<color array%>}
#endkeyvals

#keyvals:\includegraphicswtex,\includefigurewtex
width=##L
height=##L
#endkeyvals

#keyvals:\begin{mtable}
size=%<size cmd%>
h
t
b
p
H
ht
hb
hp
hH
h!
tb
tp
tH
t!
bp
bH
b!
pH
p!
H!
htb
htp
htH
ht!
tbp
tbH
tb!
bpH
bp!
pH!
htbp
htbH
htb!
tbpH
tbp!
bpH!
htbpH
htbp!
htbpH!
#endkeyvals
