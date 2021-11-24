# dataref package
# Matthew Bertucci 11/22/2021 for v0.6

#include:pgf
#include:iftex
#include:kvoptions
#include:etoolbox

#ifOption:usagereport
#include:xtab
#include:booktabs
\drefusagereport
#endif

\drefset{name}{value}
\drefset[options%keyvals]{name}{value}
\drefsave{name}{value}
\drefsave[options%keyvals]{name}{value}
\drefinput{file}#i
\drefinput[prefix]{file}#i
\dref{name}
\dref[options%keyvals]{name}
\dref*{name}
\dref*[options%keyvals]{name}
\drefvalueof{name}
\drefref{name}
\drefsethelp{pattern}{text}
\drefhelp{name}
\drefresult
\drefcalc{expression}
\drefcalc[options%keyvals]{expression}
\drefcalc*{expression}
\drefcalc*[options%keyvals]{expression}
\drefformat{number}
\drefcalc*[options%keyvals]{number}
\drefrel{key or value}
\drefrel[options%keyvals]{key or value}
\drefrel*{key or value}
\drefrel*[options%keyvals]{key or value}
\drefrow{csv list}{key template}
\drefrow[options%keyvals]{csv list}{key template}
\drefrow*{csv list}{key template}
\drefassert{expression}
\drefkeys{options%keyvals}

#keyvals:\drefset#c,\drefsave#c,\dref#c,\dref*#c,\drefcalc#c,\drefcalc*#c,\drefrel#c,\drefrel*#c,\drefrow#c,\drefkeys#c
set=%<key%>
save=%<key%>
to macro=%<macro%>
prefix=%<key prefix%>
ignoremissing#true,false
defaultvalue=%<value%>
unit=%<unit%>
unit/format=#false,plain,siunitx
unit/format default=#false,plain,siunitx
unit/new scala={%<scala%>}
unit/scale to=%<unit%>
unit/scale to auto
unit/scale to auto=%<number%>
scale by=%<key or value%>
percent
negate
divide by=%<key or value%>
abs
factor of=%<key or value%>
percent of=%<key or value%>
increase from=%<key or value%>
decrease from=%<key or value%>
increase factor from=%<key or value%>
decrease factor from=%<key or value%>
increase percent from=%<key or value%>
decrease percent from=%<key or value%>
noassert#true,false
annotate=#none,footnote,pdfcomment,typeout
#endkeyvals