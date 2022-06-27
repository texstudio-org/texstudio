# pdfextra package
# Matthew Bertucci 2022/06/26 for v0.2

#include:luatex

\attach[name]
\DDDannot{name}
\DDDcontext{name}
\DDDview[view name][keyvals]
\defaultpageactions[additional action specs]
\defaultpageduration[duration]
\defaultpagerotate[rotation spec]
\dljavascript[name]{script%definition}
\duplexdisplay
\filedef/%<⟨type⟩%>[%<name%>]{%<path or URL%>}
\fullscreen
\hlink[action spec]{text}
\hyperlinks %<\incolor \outcolor%>
\initpageattributes#*
\lininglinks
\nolininglinks
\openaction[action spec]
\pageactions[additional action specs]
\pageattributes#*
\pageduration[duration]
\pagerotate[rotation spec]
\pdfaction[action spec]
\pdfextraloaded#S
\render[name][options%keyvals]{appearance}
\render[name]{appearance}
\renditionautoplay
\RM[name][options%keyvals]{appearance}
\RM[name]{appearance}
\sdef{string%definition}{body}
\showattached
\showoutlines
\transition[transition spec]
\transitions[transition spec]

#keyvals:\DDDview
projection=#perspective,ortho
scale=%<factor%>
FOV=%<number 0-180%>
background=%<OpTeX color%>
rendermode=#Solid,SolidWireframe,Transparent,TransparentWireframe,BoundingBox,TransparentBoundingBox,Wireframe,ShadedWireframe,Vertices,ShadedVertices,Illustration,SolidOutline,ShadedIllustration
lighting=#White,Day,Night,Hard,Primary,Blue,Red,Cube,CAD,Headlamp
method=#media9,manual,u3d
u3dpath=%<path%>
coo=%<x y z%>
roo=%<number%>
c2c=%<x y z%>
#endkeyvals

#keyvals:\render
controls#true,false
volume=%<number 0-100%>
repeat=%<integer%>
background=%<OpTeX color%>
opacity=%<factor%>
aactions=\renditionautoplay
name=%<string%>
#endkeyvals

#keyvals:\RM
activation=#explicit,auto
deactivation=#explicit,auto
toolbar#true,false
views={%<name1,name2,...%>}
scripts={%<name1,name2,...%>}
name=%<string%>
background=%<OpTeX color%>
#endkeyvals