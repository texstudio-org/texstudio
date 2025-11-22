# ducksay package
# Matthew Bertucci 2025/11/22 for v2.8

#include:array
#include:grabbox

\DefaultAnimal{animal%keyvals}

\DucksayOptions{keyvals}

\AddAnimal{%<animal%>}%<ascii-art%>
\AddAnimal[%<options%>]{%<animal%>}%<ascii-art%>
\AddAnimal*{%<animal%>}%<ascii-art%>
\AddAnimal*[%<options%>]{%<animal%>}%<ascii-art%>
\AddColoredAnimal{%<animal%>}%<ascii-art%>
\AddColoredAnimal[%<options%>]{%<animal%>}%<ascii-art%>
\AddColoredAnimal*{%<animal%>}%<ascii-art%>
\AddColoredAnimal*[%<options%>]{%<animal%>}%<ascii-art%>

\AnimalOptions{animal}{options%keyvals}
\AnimalOptions*{animal}{options%keyvals}

\ducksay{message}
\ducksay[options%keyvals]{message}
\duckthink{message}
\duckthink[options%keyvals]{message}

#keyvals:\DucksayOptions#c,\AnimalOptions#c,\AnimalOptions*#c,\ducksay#c,\duckthink#c
ligatures=%<token list%>
no-tail
random#true,false
say
schroedinger
tail-1=%<token list%>
tail-2=%<token list%>
think
#endkeyvals

#keyvals:\DucksayOptions#c,\ducksay#c,\duckthink#c
arg=#box,tab,tab*
b
body=%<font%>
body*=%<font%>
body-align=#l,c,r
body-bigger=%<count%>
body-mirrored#true,false
body-to-msg=
body-x=##L
body-y=##L
bubble=%<font%>
bubble*=%<font%>
bubble-bot-kern=##L
bubble-delim-left-1=%<token list%>
bubble-delim-left-2=%<token list%>
bubble-delim-left-3=%<token list%>
bubble-delim-left-4=%<token list%>
bubble-delim-right-1=%<token list%>
bubble-delim-right-2=%<token list%>
bubble-delim-right-3=%<token list%>
bubble-delim-right-4=%<token list%>
bubble-delim-top=%<token list%>
bubble-side-kern=##L
bubble-top-kern=##L
c
col=
hpad=%<count%>
ht=%<count%>
ignore-body#true,false
msg=%<font%>
msg*=%<font%>
MSG=%<font%>
MSG*=%<font%>
msg-align=#l,c,r,j
msg-align-c=%<token list%>
msg-align-l=%<token list%>
msg-align-r=%<token list%>
msg-align-j=%<token list%>
msg-to-body=
no-bubble#true,false
none#true,false
out-h=
out-v=
out-x=##L
out-y=##L
strip-spaces#true,false
t
vpad=%<count%>
wd=%<count%>
wd*=##L
wd-eq-body#true,false
#endkeyvals

#keyvals:\DefaultAnimal#c,\ducksay#c,\duckthink#c
animal=%<animal%>
duck
small-duck
duck-family
small-rabbit
squirrel
cow
tux
head-in
platypus
pig
turtle
frog
snowman
bunny
dragon
sodomized
hedgehog
kangaroo
small-horse
dog
sheep
rabbit
snail
whale
snake
cat
sleepy-cat
schroedinger-dead
schroedinger-alive
crusader
knight
fairy
ghost
unicorn
r2d2
vader
yoda-head
small-yoda
yoda
only-tail
only-tail3
#endkeyvals
