# multimedia package
# benibela 08 Jun 2011 (see svn r2094)
# muzimuzhi 25 Jun 2020

#include:keyval
#include:ifpdf

\movie[options%keyvals]{poster text%text}{movie filename%file}
\movie{poster text%text}{movie filename%file}
#keyvals:\movie
autostart
borderwidth=##L
depth=##L
duration=%<time%>s
externalviewer
height=##L
label=##l
loop
once
open
palindrome
poster
repeat
showcontrols#true,false
start=%<time%>s
width=##L
#endkeyvals

\hyperlinkmovie[options%keyvals]{movie label}{text}
\hyperlinkmovie{movie label}{text}
#keyvals:\hyperlinkmovie
duration=%<time%>s
loop
once
palindrome
pause
play
repeat
resume
showcontrols#true,false
start=%<time%>s
stop
#endkeyvals

\sound[options%keyvals]{sound poster text}{sound filename}
\sound{sound poster text}{sound filename}
#keyvals:\sound
autostart
automute
bitspersample=#8,16
channels=#1,2
depth=##L
encoding=#Raw,Signed,muLaw,aLaw
externalviewer
height=##L
inlinesound
label=##l
loop
mixsound#true,false
repeat
samplingrate=%<number%>
width=##L
#endkeyvals

\hyperlinksound[options%keyvals]{sound label}{text}
\hyperlinksound{sound label}{text}
\hyperlinkmute{text}
#keyvals:\hyperlinksound
loop
mixsound#true,false
repeat
#endkeyvals
