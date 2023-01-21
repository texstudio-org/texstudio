# graphicsonthefly package
# ponte-vecchio 2023-01-17 for v0.9.6

#include:ifplatform
#include:graphicx

#keyvals:\usepackage/graphicsonthefly#c
renewall
animate
all
curl
nocoalesce
convert
#endkeyvals

## Animations
#ifOption:all
#include:animate
\animatedgifonthefly[options%keyvals]{fps}{image name}{start}{end}{URL}#U
\animatedgifonthefly*[options%keyvals]{fps}{image name}{start}{end}{URL}#*U
\animatedgif[options%keyvals]{fps}{image name}{start}{end}#U
\usegifonthefly[%<options%>]{%<fps,start,end%>}
# alias of \animatedgifonthefly
\animategraphicsonthefly[options%keyvals]{fps}{image name}{start}{end}{URL}#SU
\animategraphicsonthefly*[options%keyvals]{fps}{image name}{start}{end}{URL}#SU
#endif

#ifOption:animate
#include:animate
\animatedgifonthefly[options%keyvals]{fps}{image name}{start}{end}{URL}#U
\animatedgifonthefly*[options%keyvals]{fps}{image name}{start}{end}{URL}#*U
\animatedgif[options%keyvals]{fps}{image name}{start}{end}#U
\usegifonthefly[%<options%>]{%<fps,start,end%>}
# alias of \animatedgifonthefly
\animategraphicsonthefly[options%keyvals]{fps}{image name}{start}{end}{URL}#SU
\animategraphicsonthefly*[options%keyvals]{fps}{image name}{start}{end}{URL}#SU
#endif

#keyvals:\animatedgifonthefly#c,\animatedgifonthefly*#c,\animatedgif#c,\usegifonthefly#c,\animategraphicsonthefly#c,\animategraphicsonthefly*#c
label=%<label%>
type=%<file ext%>
poster
poster=#first,last,none,%<number%>
every=%<number%>
autopause
autoplay
autoresume
loop
palindrome
step
width=##L
height=##L
totalheight=##L
keepaspectratio
scale=%<factor%>
bb=%<llx lly urx ury%>
viewport=%<llx lly urx ury%>
trim=%<left bottom right top%>
clip
hiresbb
interpolate
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
controls=#all,true,on,none,false,off
controlsaligned=#left,left+%<<indent>%>,center,right,right+%<<indent>%>
buttonsize=##L
buttonbg=#%color
buttonfg=#%color
buttonalpha=%<opacity%>
draft
final
nomouse
method=#icon,widget,ocg
measure
alttext=#none,%<alt description%>
begin={%<begin code%>}
end={%<end code%>}
timeline=%<file%>
#endkeyvals

\includegraphicsonthefly{image name}{URL}#U
\includegraphicsonthefly[options%keyvals]{image name}{URL}#U
\includegraphicsonthefly*{image name}{URL}#U
\includegraphicsonthefly*[options%keyvals]{image name}{URL}#U
\prepareimgonthefly{image name}{URL}#U
\prepareimgonthefly*{image name}{URL}#U
\useimgonthefly[%<options%>]

#keyvals:\includegraphicsonthefly#c,\includegraphicsonthefly*#c,\useimgonthefly#c
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

# not documented
\CoalesceOption#S
\ConvertCommand#S
\RemoveCommand#S
\WgetCommand#S
