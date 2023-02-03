# media9 package
# Matthew Bertucci 2022/08/12 for v1.25

#include:ocgbase
#include:pdfbase

#keyvals:\usepackage/media9#c
dvipdfmx
xetex
bigfiles
#endkeyvals

# Global/local options
#keyvals:\usepackage/media9#c,\includemedia#c
draft
final
playbutton=#fancy,plain,none
noplaybutton
activate=#onclick,pageopen,pagevisible
deactivate=#onclick,pageclose,pageinvisible
windowed=
transparent
passcontext
attachfiles
3Dplaytype=#linear,oscillating
3Dplaycount=%<integer%>
3Dplayspeed=%<number%>
3Dtoolbar
3Dnavpane
3Dpartsattrs=#restore,keep
3Dmenu
3Dbg=%<<r> <g> <b>%>
3Dlights=#None,White,Day,Night,Hard,Primary,Blue,Red,Cube,CAD,Headlamp
3Drender=#Solid,SolidWireframe,Transparent,TransparentWireframe,BoundingBox,TransparentBoundingBox,TransparentBoundingBoxOutline,Wireframe,ShadedWireframe,HiddenWireframe,Vertices,ShadedVertices,SolidOutline,Illustration,ShadedIllustration
#endkeyvals

\includemedia{poster text%text}{file or URL%file}
\includemedia[options%keyvals]{poster text%text}{file or URL%file}

\addmediapath{directory}

# Local-only options
#keyvals:\includemedia#c
label=%<label text%>
width=##L
height=##L
totalheight=##L
keepaspectratio
scale=%<factor%>
addresource=%<file%>
flashvars={%<var1=val1&var2=val2&...%>}
3Dcoo=%<<x> <y> <z>%>
3Dc2c=%<<x> <y> <z>%>
3Droll=%<roll%>
3Dc2w=%<camera-to-world matrix%>
3Dpsob=#Min,Max,W,H
3Droo=%<number%>
3Daac=%<angle%>
3Dortho=%<factor%>
3Dviews=%<views file%>
add3Djscript=%<3D JavaScript file%>
#endkeyvals

\mediabutton{button text%text}
\mediabutton[options%keyvals]{button text%text}

#keyvals:\mediabutton#c
overface=%<text or graphic%>
downface=%<text or graphic%>
tooltip=%<tip text%>
3Dgotoview=%<label text%>
3Dgotoview=%<label text%>:%<view spec%>
mediacommand=%<label text%>
mediacommand=%<label text%>:%<command%>
mediacommand=%<label text%>:%<command%>[(%<arg1%>)%<(arg2)...%>]
jsaction={%<JavaScript code%>}
jsaction=%<label text%>:{%<JavaScript code%>}
draft
final
#endkeyvals
