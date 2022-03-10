# psfragx package
# Matthew Bertucci 3/8/2022 for v1.1

#include:graphicx
#include:psfrag
#include:overpic

#keyvals:\usepackage/psfragx#c
sub
nosub
allcom
selcom
ovp
noovp
#endkeyvals

\includegraphicx{imagefile}#g
\includegraphicx[options%keyvals]{imagefile}#g
\includegraphicx[options%keyvals](psfrags){imagefile}#*g
\includegraphicx[options%keyvals](psfrags)<fg overpic>{imagefile}#*g
\includegraphicx[options%keyvals](psfrags)<fg overpic>[bg overpic]{imagefile}#*g

\begin{overpix}{imagefile}#\picture,pictureHighlight
\begin{overpix}[options%keyvals]{imagefile}#\picture,pictureHighlight
\begin{overpix}[options%keyvals]<fg overpic>{imagefile}#\picture,pictureHighlight
\begin{overpix}[options%keyvals]<fg overpic>[bg overpic]{imagefile}#\picture,pictureHighlight
\end{overpix}

#keyvals:\includegraphicx,\begin{overpix}
pfx#true,false
overwritepfx#true,false
pfxadd={%<psfrags%>}
ovp#true,false
overwriteovp#true,false
ovpbgd={%<picture commands%>}
ovpfgd={%<picture commands%>}
# options passed to overpic
abs#true,false
percent#true,false
permil#true,false
rel=%<number%>
grid#true,false
tics=%<number%>
unit=##L
# options passed to \includegraphics
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

\iflanguage{language}{true}{false}#*
\allmetacomments#*
\selectedmetacomments#*
\copypfxfromto{EPS file}{PFX file}#*
\setpfxinput{file}#*i
\setpfxoutput{file}#*i
\copypfxlines#*
\pfxinput{file}#*i
\ovpinput{file}#*i
\begin{onlylanguage}{language}#*
\end{onlylanguage}#*
\overpix#S
\endoverpix#S
\onlylanguage{language}#S
\endonlylanguage#S

# from psfragx.cfg
\providecolorcommands#*
\Beforepfxinput#*
\Afterpfxinput#*
\Beforeovpinput#*
\Afterovpinput#*