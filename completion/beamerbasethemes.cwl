# beamerbasethemes package
# Matthew Bertucci 1/30/2022 for v3.65

\usetheme{beamertheme}#u
\usetheme[options%keyvals]{beamertheme}
\usecolortheme{beamer color theme}#u
\usecolortheme[options%keyvals]{beamer color theme}
\usefonttheme{beamer font theme}#u
\usefonttheme[options%keyvals]{beamer font theme}
\useoutertheme{beamer outer theme}#u
\useoutertheme[options%keyvals]{beamer outer theme}
\useinnertheme{beamer inner theme}#u
\useinnertheme[options%keyvals]{beamer inner theme}

## Inner theme options ##
#keyvals:\useinnertheme/rounded
shadow#true,false
#endkeyvals

## Outer theme options ##
#keyvals:\useoutertheme/miniframes
footline=#empty,authorinstitute,authortitle,institutetitle,authorinstitutetitle
subsection#true,false
#endkeyvals

#keyvals:\useoutertheme/smoothbars
subsection#true,false
#endkeyvals

#keyvals:\useoutertheme/sidebar
height=##L
hideothersubsections
hideallsubsections
left
right
width=##L
#endkeyvals

#keyvals:\useoutertheme/tree
hooks#true,false
#endkeyvals

## Color theme options ##
#keyvals:\usecolortheme/structure
rgb={%<r,g,b%>}
RGB={%<r,g,b%>}
cmyk={%<c,m,y,k%>}
cmy={%<c,m,y%>}
hsb={%<h,s,b%>}
named=#%color
#endkeyvals

#keyvals:\usecolortheme/albatross,\usecolortheme/monarca
overlystylish
#endkeyvals

## Font theme options ##
#keyvals:\usefonttheme/serif
stillsansserifmath
stillsansserifsmall
stillsansseriflarge
stillsansseriftext
onlymath
#endkeyvals

#keyvals:\usefonttheme/structurebold,\usefonttheme/structureitalicserif,\usefonttheme/structuresmallcapsserif
onlysmall
onlylarge
#endkeyvals

## commands from inner, outer, color, and font themes (only defined if that theme is loaded) ##
# from sidebar outer theme
\beamersidebarwidth#S
\beamerheadheight#S

# from inmargin inner theme
\inserttitleindicator#S
\insertauthorindicator#S
\insertinstituteindicator#S
\insertdateindicator#S
