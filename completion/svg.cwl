# svg package
# Matthew Bertucci 1/30/2022 for v2.02k

#include:iftex
#include:scrbase
#include:pdftexcmds
#include:trimspaces
#include:graphicx
#include:shellesc
#include:ifplatform
#include:xcolor
#include:transparent
#include:pgfsys

#keyvals:\usepackage/svg#c
usexcolor=#true,on,yes,false,off,no
usetransparent=#true,on,yes,false,off,no
noxcolor
notransparent
#endkeyvals

## 2.1. General settings ##
\svgsetup{options%keyvals}
\svgpath{path%URL}

## 2.2. Options for the invocation of Inkscape ##
#keyvals:\usepackage/svg#c,\svgsetup#c
inkscape=#false,off,no,true,on,yes,newer,onlynewer,forced,force,overwrite,pdf,eps,ps,png,latex,nolatex,drawing,page,%<integer%>dpi
inkscapepath=#svgdir,svgpath,svgsubdir,svgsubpath,basedir,basepath,jobdir,jobpath,basesubdir,basesubpath,jobsubdir,jobsubpath,%<path%>
inkscapeexe=%<exec path%>
inkscapeversion=#0,1,auto
inkscapename=%<file name%>
inkscapeformat=#pdf,aps,ps,png
inkscapelatex#true,false
inkscapearea=#drawing,crop,page,nocrop
inkscapedpi=%<integer%>
inkscapeopt=%<Inkscape option%>
svgextension=%<extension%>
## 2.3. Options for the graphic inclusion ##
width=##L
height=##L
distort#true,false
scale=%<factor%>
pretex=%<code%>
apptex=%<code%>
draft#true,false
lastpage#true,false
#endkeyvals

## 2.4. Including SVG files ##
\includesvg{imagefile}#g
\includesvg[options%keyvals]{imagefile}#g

#keyvals:\includesvg
inkscape=#false,off,no,true,on,yes,newer,onlynewer,forced,force,overwrite,pdf,eps,ps,png,latex,nolatex,drawing,page,%<integer%>dpi
inkscapeformat=#pdf,aps,ps,png
inkscapelatex#true,false
inkscapearea=#drawing,crop,page,nocrop
inkscapedpi=%<integer%>
inkscapeopt=%<Inkscape option%>
svgextension=%<extension%>
width=##L
height=##L
distort#true,false
scale=%<factor%>
pretex=%<code%>
apptex=%<code%>
draft#true,false
lastpage#true,false
angle=%<degrees%>
origin=
#endkeyvals

## 2.5. Including already exported SVG files ##
\includeinkscape{imagefile}#g
\includeinkscape[options%keyvals]{imagefile}#g

#keyvals:\includeinkscape
inkscapeformat=#pdf,aps,ps,png
inkscapelatex#true,false
width=##L
height=##L
distort#true,false
scale=%<factor%>
pretex=%<code%>
apptex=%<code%>
draft#true,false
lastpage#true,false
angle=%<degrees%>
origin=
#endkeyvals

# deprecated
\setsvg{options}#S