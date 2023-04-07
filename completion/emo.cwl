# emo package
# Matthew Bertucci 2023/04/03 for v0.2

#include:inputenc
#include:iftex
#include:graphicx
#include:xcolor

#keyvals:\usepackage/emo#c
extra
index
#endkeyvals

#ifOption:extra
#include:xspace
\lingchi
\YHWH
#endif

#ifOption:index
#include:index
#endif

\emo{emoji-name%keyvals}

#keyvals:\emo#c
keycap-one
biohazard
balance-scale
check-mark
eu
foggy
globe-africa-europe
classical-building
desert-island
stadium
rainbow-flag
label
eye
busts
collision
currency-exchange
floppy-disk
triangular-ruler
pager
loupe-left
detective
wastebasket
enraged-face
stop-sign
robot
handshake
exploding-head
parrot
judge
roll-of-paper
receipt
#endkeyvals
