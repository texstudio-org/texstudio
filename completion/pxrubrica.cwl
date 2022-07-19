# pxrubrica package
# Matthew Bertucci 2022/07/17 for v1.3d

#include:keyval

\ruby{kanji}{ruby}
\ruby[option%keyvals]{kanji}{ruby}
\jruby{kanji}{ruby}#*
\jruby[option%keyvals]{kanji}{ruby}#*
\aruby{text}{ruby}
\aruby[option%keyvals]{text}{rub
y}
\truby{kanji}{upper ruby}{lower ruby}
\truby[option%keyvals]{kanji}{upper ruby}{lower ruby}
\atruby{text}{upper ruby}{lower ruby}
\atruby[option%keyvals]{text}{upper ruby}{lower ruby}
\rubysetup{option%keyvals}

#keyvals:\ruby#c,\jruby#c,\aruby#c,\truby#c,\atruby#c,\rubysetup#c
-
c
h
H
m
g
j
M
J
P
S
e
E
f
F
|-|
(-)
<->
<-|
|->
-||
||-
<-||
||->
#endkeyvals

\rubyfontsetup{font commands}
\rubybigintrusion{number}
\rubysmallintrusion{number}
\rubymaxmargin{number}
\rubyintergap{number}
\rubyusejghost
\rubynousejghost
\rubyuseaghost
\rubynouseaghost
\rubysafemode
\rubynosafemode
\rubysizeratio{number}
\rubystretchprop{X}{Y}{Z}
\rubystretchprophead{Y}{Z}
\rubystretchpropend{X}{Y}
\rubyyheightratio{number}
\rubytheightratio{number}

\kenten{text}
\kenten[option%keyvals]{text}
\jkenten{text}#*
\jkenten[option%keyvals]{text}#*
\kentensetup{option%keyvals}

#keyvals:\kenten#c,\jkenten#c,\kentensetup#c
p
s
f
F
P
S
#endkeyvals

\kspan{text}
\kspan*{text}

\kentenmarkinyoko{symbol choice}
\kentensubmarkinyoko{symbol choice}
\kentenmarkintate{symbol choice}
\kentensubmarkintate{symbol choice}
\kentenfontsetup{font commands}
\kentenintergap{number}
\kentensizeratio{number}

\kentenrubycombination{choice%keyvals}

#keyvals:\kentenrubycombination#c
ruby
both
#endkeyvals

\kentenrubyintergap{number}

# not documented
\pdfstringdefPreHook#S
\rubyadjustatlineedge#*
\rubybreakjukugo#*
\rubyfontsize#*
\rubynoadjustatlineedge#*
\rubynobreakjukugo#*
\rubyuseextra{arg}#*