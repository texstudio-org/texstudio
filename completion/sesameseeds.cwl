# sesameseeds package
# Matthew Bertucci 2026/11/04 for v1.1

#include:tikz
#include:pgfopts

\nosesame
\sesameoff
\sesameon
\sesameseed[options%keyvals]{x}{y}
\sesameseed{x}{y}
\sesamesetup{options%keyvals}
\sesamesprinkle[options%keyvals]{x}{y}
\sesamesprinkle{x}{y}
\simitring[options%keyvals]{x}{y}
\simitring{x}{y}

#keyvals:\usepackage/sesameseeds#c,\sesamesetup,\sesamesprinkle,\simitring,\sesameseed
black=%<factor%>
crumbratio=%<factor%>
crumbs#true,false
firstpage#true,false
layer=#foreground|background
mess=#none,light,medium,heavy,catastrophic
off
probability=%<factor%>
randomseed=%<integer%>
roast=%<factor%>
seeds=%<integer%>
shadow=%<factor%>
size=%<factor%>
spread=##L
stray=%<factor%>
#endkeyvals

#keyvals:\sesamesprinkle,\simitring,\sesameseed
angle=%<degrees%>
count=%<integer%>
radius=##L
#endkeyvals