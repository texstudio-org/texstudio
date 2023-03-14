# gregoriosyms package
# Matthew Bertucci 2023/03/14 for v6.0.0

#include:iftex
#include:kvoptions
#include:luatexbase
#include:luaotfload
#include:luamplib
#include:xstring
#include:xcolor

#keyvals:\usepackage/gregoriosyms#c
debug
debug={%<types%>}
allowdeprecated#true,false
#endkeyvals

\gredefsymbol{csname}{font name}{glyph name or code point}
\gredefsizedsymbol{csname}{font name}{glyph name or code point}
\greABar{size}#*
\greRBar{size}#*
\greVBar{size}#*
\greABarSlant{size}#*
\greRBarSlant{size}#*
\greVBarSlant{size}#*
\greABarSC{size}#*
\greRBarSC{size}#*
\greVBarSC{size}#*
\greABarSmall{size}#*
\greRBarSmall{size}#*
\greVBarSmall{size}#*
\greABarSmallSlant{size}#*
\greRBarSmallSlant{size}#*
\greVBarSmallSlant{size}#*
\greABarSmallSC{size}#*
\greRBarSmallSC{size}#*
\greVBarSmallSC{size}#*
\greABarCaption{size}#*
\greRBarCaption{size}#*
\greVBarCaption{size}#*
\greABarCaptionSlant{size}#*
\greRBarCaptionSlant{size}#*
\greVBarCaptionSlant{size}#*
\greABarCaptionSC{size}#*
\greRBarCaptionSC{size}#*
\greVBarCaptionSC{size}#*
\greABarAlt{size}#*
\greRBarAlt{size}#*
\greVBarAlt{size}#*
\grebarredsymbol{definition}{symbol}{size}{hshift}{vshift}
\gredefbarredsymbol{csname}{definition}{symbol}{size}{hshift}{vshift}
\gresimpledefbarredsymbol{A, R, or V}{left shift}
\ABar#*
\VBar#*
\RBar#*
\grelatexsimpledefbarredsymbol{A, R, or V}{upmedium shift}{itmedium shift}{upbold shift}{itbold shift}
\gothRbar
\gothVbar
\GreDagger#*
\grecross
\grealtcross
\greheightstar
\gresixstar
\GreStar#*
\greLineOne{size}#*
\greLineTwo{size}#*
\greLineThree{size}#*
\greLineFour{size}#*
\greLineFive{size}#*
\greseparator{integer 1-5}{size}
\greOrnamentOne{size}#*
\greOrnamentTwo{size}#*
\greornamentation{integer 1-2}{size}
\gresetspecial{text%plain}{code}
\greunsetspecial{text%plain}
\GreSpecial{text%plain}#*

grebackgroundcolor#B
gregoriocolor#B