# tikzpeople package
# Matthew Bertucci 9/4/2021 for v0.4

#include:tikz
#include:calc
#include:etoolbox
#include:tikzlibrarydecorations.markings
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibrarycalc
#include:tikzlibrarypositioning

#keyvals:\usepackage/tikzpeople#c
draft
demo
nobeards
saturated
#endkeyvals

#ifOption:demo
\alltikzpeople{width}{node options}
\alltikzpeople*{width}{node options}
\tikzpeoplecolors{shape name}
#endif

#keyvals:\node#c
shape=%<shape name%>
alice
bob
bride
builder
businessman
charlie
chef
conductor
cowboy
criminal
dave
devil
duck
graduate
groom
guard
jester
judge
maninblack
mexican
nun
nurse
physician
pilot
police
priest
sailor
santa
surgeon
evil
female
good
mirrored
monitor
saturated
shield
sword
hat=#%color
hair=#%color
shirt=#%color
cross=#%color
collar=#%color
skin=#%color
details=#%color
undershirt=#%color
veil=#%color
pearls=#%color
trousers=#%color
tie=#%color
monogram=#%color
buttons=#%color
hatbadge=#%color
hatshield=#%color
stitching=#%color
vest=#%color
patches=#%color
bill=#%color
tongue=#%color
stripes=#%color
lining=#%color
pattern=#%color
hairshadow=#%color
earpiece=#%color
glasses=#%color
ringtop=#%color
ringmid=#%color
ringbot=#%color
plaid=#%color
badgeclip=#%color
badgename=#%color
redcross=#%color
badge=#%color
stethoscope=#%color
tube=#%color
decoration=#%color
visor=#%color
straps=#%color
beard=#%color
mask=#%color
monogramtext=%<text%>
badgetext=%<text%>
#endkeyvals
