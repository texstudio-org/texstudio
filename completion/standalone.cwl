# standalone package
# Fran J. Sanchez 30/10/2021 for v1.3a
# Matthew Bertucci 3/26/2022; class-standalone.cwl added and commands/keys moved accordingly

#include:adjustbox
#include:currfile
#include:filemod-expmin
#include:gincltex
#include:ifluatex
#include:ifpdf
#include:ifxetex
#include:shellesc
#include:trimclip
#include:varwidth
#include:xkeyval

#keyvals:\usepackage/standalone
subpreambles#true,false
sort#true,false
print#true,false
comments#true,false
nocomments
obeyclassoptions#true,false
#endkeyvals

# only some package options available to \standaloneconfig and \includestandalone
#keyvals:\usepackage/standalone,\standaloneconfig,\includestandalone
group#true,false
mode=#tex,image,image|tex,build,buildmissing,buildnew
extension=%<extension%>
build={%<build options%>}
#endkeyvals

## also any options in \includegraphics
\includestandalone{file}#i
\includestandalone[options%keyvals]{file}#i

#keyvals:\includestandalone
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

\standaloneconfig{options%keyvals}

\standaloneignore#*
\begin{standalone}#*
\end{standalone}#*
\ifstandalone#*
\standalonetrue#*
\standalonefalse#*
\ifstandalonebeamer#*
\standalonebeamertrue#*
\standalonebeamerfalse#*
\IfStandalone{code for standalone}{code for main document}#*
\onlyifstandalone{code}#*
