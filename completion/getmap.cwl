# getmap package
# Matthew Bertucci 2/5/2022 for v1.11

#include:xkeyval
#include:stringenc
#include:ifthen
#include:shellesc
#include:ifxetex

\getmap{address}
\getmap[options%keyvals]{address}

#keyvals:\usepackage/getmap#c,\getmap
mode=#osm,gm,gsv
inputencoding=%<encoding%>
overwrite#true,false
file=%<file name%>
key=%<service key%>
scale=%<number%>
zoom=%<number%>
xsize=%<width in pixels%>
ysize=%<height in pixels%>
imagetype=#png,png8,png32,jpeg,jpg,jpg-baseline,gif
type=#map,sat,hyb,roadmap,satellite,hybrid,terrain
color=%<color%>
number=%<number%>
language=%<lang code%>
markers={%<&markers=...%>}
visible={%<loc1|loc2|...%>}
path={%<&path=...%>}
pathfile=%<file name%>
heading=%<degrees%>
pitch=%<degrees%>
fov=%<degrees%>
#endkeyvals