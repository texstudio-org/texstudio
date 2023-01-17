# graphicsonthefly package
# ponte-vecchio 2023-01-17 for v0.9.6

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
\animatedgifonthefly[%<options%>]{%<fps%>}{%<image name%>}{%<start%>}{%<end%>}{%<url%>}
\animatedgif{%<fps%>}{%<image name%>}{%<start%>}{%<end%>}{%<url%>}
\usegifonthefly[%<options%>]{%<image name%>}{%<url%>}
#endif

#ifOption:animate
#include:animate
\animatedgifonthefly[%<options%>]{%<fps%>}{%<image name%>}{%<start%>}{%<end%>}{%<url%>}
\animatedgif{%<fps%>}{%<image name%>}{%<start%>}{%<end%>}{%<url%>}
\usegifonthefly[%<options%>]{%<image name%>}{%<url%>}
#endif

#keyvals:\animatedgifonthefly#c,\usegifonthefly#c
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

\includegraphicsonthefly[%<options%>]{%<image name%>}{%<url%>}
\includegraphicsonthefly*[%<options%>]{%<image name%>}{%<url%>}
\prepareimgonthefly{%<image name%>}{%<url%>}
\prepareimgonthefly*{%<image name%>}{%<url%>}
\useimageonthefly[%<options%>]

#keyvals:\includegraphicsonthefly#c,\useimageonthefly#c
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