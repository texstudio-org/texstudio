# emo package
# Matthew Bertucci 2023/04/26 for v0.4

#include:inputenc
#include:iftex
#include:graphicx
#include:xcolor

#keyvals:\usepackage/emo#c
extra
index
debug
#endkeyvals

#ifOption:extra
#include:xspace
\lingchi
\YHWH
#keyvals:\emo#c
lingchi
YHWH
#endkeyvals
#endif

#ifOption:index
#include:index
#endif

\emo{emoji-name%keyvals}

#keyvals:\emo#c
keycap-one
biohazard
balance-scale
check-mark-button
check-mark
cross-mark
plus
eu
japanese-bargain-button
foggy
globe-africa-europe
party-popper
classical-building
desert-island
stadium
rainbow-flag
label
baby-chick
eye
busts
collision
currency-exchange
floppy-disk
chart-increasing
triangular-ruler
pager
loupe-left
detective
wastebasket
enraged-face
stop-sign
robot
handshake
person-facepalming
zany-face
exploding-head
pleading-face
parrot
judge
roll-of-paper
receipt
#endkeyvals
