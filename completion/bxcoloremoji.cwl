# bxcoloremoji package
# Matthew Bertucci 2024/11/11 for v1.0

#include:etoolbox
#include:keyval
#include:graphicx
#include:color
#include:twemojis

#keyvals:\usepackage/bxcoloremoji#c
jatype=#auto,true,false
names#true,false
nodvidriver
resetdvidriver
preload-names=#auto,true,false
bbparam=#auto,true,false
bxghost=#auto,true,false
pua=
#endkeyvals

#ifOption:bxghost=true
#include:bxghost
#endif

\coloremojisetup{keyvals}
\coloremoji{emoji name}
\coloremoji[keyvals]{emoji name}
\coloremoji*{emoji name}
\coloremoji*[keyvals]{emoji name}
\coloremojicode{code value list}
\coloremojicode[keyvals]{code value list}
\coloremojicode*{code value list}
\coloremojicode*[keyvals]{code value list}
\coloremojikeycapof{number}
\coloremojikeycapof[keyvals]{number}
\coloremojikeycapof*{number}
\coloremojikeycapof*[keyvals]{number}
\coloremojikeycap{counter}
\coloremojikeycap[keyvals]{counter}
\coloremojikeycap*{counter}
\coloremojikeycap*[keyvals]{counter}

#keyvals:\usepackage/bxcoloremoji#c,\coloremojisetup,\coloremoji,\coloremoji*,\coloremojicode,\coloremojicode*,\coloremojikeycapof,\coloremojikeycapof*,\coloremojikeycap,\coloremojikeycap*
twemojis
family=%<family%>
no-image
twemoji-pdf
twemoji-png
size=##L
size*=##L
scale=%<factor%>
#endkeyvals

#keyvals:\pagenumbering#c
coloremojikeycap
#endkeyvals

\coloremojifill{emoji name}
\coloremojiline
\begin{coloremojilist}{emoji name}
\end{coloremojilist}
\begin{coloremojiautolist}{emoji name}
\end{coloremojiautolist}
\coloremojicodefill{code value list}
\coloremojicodeline{code value list}
\begin{coloremojicodelist}{code value list}
\end{coloremojicodelist}
\begin{coloremojicodeautolist}{code value list}
\end{coloremojicodeautolist}

# deprecated/not documented
\coloremojiucs{code value list}#S
\coloremojiucs[keyvals]{code value list}#S
\coloremojiucsfill{code value list}#S
\coloremojiucsline{code value list}#S
\begin{coloremojiucslist}{code value list}#S
\end{coloremojiucslist}#S
\begin{coloremojiucsautolist}{code value list}#S
\end{coloremojiucsautolist}#S
\coloremojiLoadAllNames#S
\coloremojiZWJSymbolColor#S
\bxcoloremojiUndeclareOrder{arg}#S
\bxcoloremojiTestOrder{arg1}{arg2}#S
\bxDebug{arg}#S