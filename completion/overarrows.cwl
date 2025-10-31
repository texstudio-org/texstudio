# overarrows package
# Matthew Bertucci 2025/10/24 for v1.5

#include:amsmath
#include:etoolbox
#include:esvect
#include:pgfkeys

#keyvals:\usepackage/overarrows#c
esvect
noesvect
esvecta
esvectb
esvectc
esvectd
esvecte
esvectf
esvectg
esvecth
old-arrows
tikz
pstricks
pstarrows
subscripts
subother
subactive
debug
overrightarrow
underrightarrow
overleftarrow
underleftarrow
overleftrightarrow
underleftrightarrow
overrightharpoonup
underrightharpoonup
overrightharpoondown
underrightharpoondown
overleftharpoonup
underleftharpoonup
overleftharpoondown
underleftharpoondown
overbar
underbar
overcommands
undercommands
allcommands
#endkeyvals

#ifOption:old-arrows
#include:old-arrows
# loads old option of old-arrows
\vardownarrow#m
\vargets#m
\varhookleftarrow#m
\varhookrightarrow#m
\varleftarrow#m
\varleftarrowfill
\varleftrightarrow#m
\varlonghookleftarrow#m
\varlonghookrightarrow#m
\varlongleftarrow#m
\varlongleftrightarrow#m
\varlongmapsfrom#m
\varlongmapsto#m
\varlongrightarrow#m
\varmapsfrom#m
\varmapsto#m
\varmapstochar#*m
\varnearrow#m
\varnwarrow#m
\varoverleftarrow{arg}
\varoverleftrightarrow{arg}#m
\varoverrightarrow{arg}
\varrightarrow#m
\varrightarrowfill
\varsearrow#m
\varswarrow#m
\varto#m
\varunderleftrightarrow{arg}#m
\varunderleftarrow{arg}#m
\varunderrightarrow{arg}#m
\varuparrow#m
\varupdownarrow#m
\varvarinjlim#m
\varvarprojlim#m
\varxhookleftarrow[sub]{sup}#m
\varxhookrightarrow[sub]{sup}#m
\varxleftarrow[sub]{sup}#m
\varxleftrightarrow[sub]{sup}#m
\varxmapsfrom[sub]{sup}#m
\varxmapsto[sub]{sup}#m
\varxrightarrow[sub]{sup}#m
#endif

#ifOption:tikz
#include:tikz
#endif

#ifOption:pstricks
#include:pstricks-add
#endif

#ifOption:pstarrows
#include:pict2e
#endif

#ifOption:overrightarrow
\overrightarrow*{arg}_{sub}#m
#endif

#ifOption:underrightarrow
\underrightarrow*{arg}_{sub}#m
#endif

#ifOption:overleftarrow
\overleftarrow*{arg}_{sub}#m
#endif

#ifOption:underleftarrow
\underleftarrow*{arg}_{sub}#m
#endif

#ifOption:overleftrightarrow
\overleftrightarrow*{arg}_{sub}#m
#endif

#ifOption:underleftrightarrow
\underleftrightarrow*{arg}_{sub}#m
#endif

#ifOption:overrightharpoonup
\overrightharpoonup{arg}#m
\overrightharpoonup*{arg}_{sub}#m
#endif

#ifOption:underrightharpoonup
\overrightharpoonup{arg}#m
\overrightharpoonup*{arg}_{sub}#m
#endif

#ifOption:overrightharpoondown
\overrightharpoondown{arg}#m
\overrightharpoondown*{arg}_{sub}#m
#endif

#ifOption:underrightharpoondown
\underrightharpoondown{arg}#m
\underrightharpoondown*{arg}_{sub}#m
#endif

#ifOption:overleftharpoonup
\overleftharpoonup{arg}#m
\overleftharpoonup*{arg}_{sub}#m
#endif

#ifOption:underleftharpoonup
\underleftharpoonup{arg}#m
\underleftharpoonup*{arg}_{sub}#m
#endif

#ifOption:overleftharpoondown
\overleftharpoondown{arg}#m
\overleftharpoondown*{arg}_{sub}#m
#endif

#ifOption:underleftharpoondown
\underleftharpoondown{arg}#m
\underleftharpoondown*{arg}_{sub}#m
#endif

#ifOption:overbar
\overbar{arg}#m
\overbar*{arg}_{sub}#m
#endif

#ifOption:underbar
\underbar{arg}#m
\underbar*{arg}_{sub}#m
#endif

#ifOption:overcommands
\overrightarrow*{arg}_{sub}#m
\overleftarrow*{arg}_{sub}#m
\overleftrightarrow*{arg}_{sub}#m
\overrightharpoonup{arg}#m
\overrightharpoonup*{arg}_{sub}#m
\overrightharpoondown{arg}#m
\overrightharpoondown*{arg}_{sub}#m
\overleftharpoonup{arg}#m
\overleftharpoonup*{arg}_{sub}#m
\overleftharpoondown{arg}#m
\overleftharpoondown*{arg}_{sub}#m
\overbar{arg}#m
\overbar*{arg}_{sub}#m
#endif

#ifOption:undercommands
\underrightarrow*{arg}_{sub}#m
\underleftarrow*{arg}_{sub}#m
\underleftrightarrow*{arg}_{sub}#m
\underrightharpoonup{arg}#m
\underrightharpoonup*{arg}_{sub}#m
\underrightharpoondown{arg}#m
\underrightharpoondown*{arg}_{sub}#m
\underleftharpoonup{arg}#m
\underleftharpoonup*{arg}_{sub}#m
\underleftharpoondown{arg}#m
\underleftharpoondown*{arg}_{sub}#m
\underbar{arg}#m
\underbar*{arg}_{sub}#m
#endif

#ifOption:allcommands
\overrightarrow*{arg}_{sub}#m
\overleftarrow*{arg}_{sub}#m
\overleftrightarrow*{arg}_{sub}#m
\overrightharpoonup{arg}#m
\overrightharpoonup*{arg}_{sub}#m
\overrightharpoondown{arg}#m
\overrightharpoondown*{arg}_{sub}#m
\overleftharpoonup{arg}#m
\overleftharpoonup*{arg}_{sub}#m
\overleftharpoondown{arg}#m
\overleftharpoondown*{arg}_{sub}#m
\overbar{arg}#m
\overbar*{arg}_{sub}#m
\underrightarrow*{arg}_{sub}#m
\underleftarrow*{arg}_{sub}#m
\underleftrightarrow*{arg}_{sub}#m
\underrightharpoonup{arg}#m
\underrightharpoonup*{arg}_{sub}#m
\underrightharpoondown{arg}#m
\underrightharpoondown*{arg}_{sub}#m
\underleftharpoonup{arg}#m
\underleftharpoonup*{arg}_{sub}#m
\underleftharpoondown{arg}#m
\underleftharpoondown*{arg}_{sub}#m
\underbar{arg}#m
\underbar*{arg}_{sub}#m
#endif

\NewOverArrowCommand{command}{keyvals}#d
\NewOverArrowCommand[method]{command}{keyvals}#d
\RenewOverArrowCommand{command}{keyvals}
\RenewOverArrowCommand[method]{command}{keyvals}
\ProvideOverArrowCommand{command}{keyvals}#d
\ProvideOverArrowCommand[method]{command}{keyvals}#d
\DeclareOverArrowCommand{command}{keyvals}#d
\DeclareOverArrowCommand[method]{command}{keyvals}#d

#keyvals:\NewOverArrowCommand,\RenewOverArrowCommand,\ProvideOverArrowCommand,\DeclareOverArrowCommand
min length=%<number%>
arrow under
arrow under=#autoconfig,noconfig
shift left=%<number%>
shift right=%<number%>
shift leftright=%<number%>
center arrow
left arrow
right arrow
before arrow=%<vertical material%>
after arrow=%<vertical material%>
space before arrow=##L
space after arrow=##L
detect subscripts#true,false
start=%<command%>
middle=%<command%>
end=%<command%>
trim start=%<number%>
trim middle=%<number%>
trim end=%<number%>
trim=%<number%>
no trimming
middle config=#auto,relbar,relbareda,harrowextender
amsmath
amsmath=#mimic,strict
esvect
esvect=#mimic,strict
tikz options={%<TikZ options%>}
path options={%<path options%>}
path={%<path spec%>}
add tikz options={%<TikZ options%>}
add path options={%<path options%>}
arrows={%<arrow spec%>}
line thickness=##L
thinner
tikz command={%<TikZ command%>}
pstricks command={%<pstricks command%>}
arrow={%<arrow%>}
psset={%<pstricks options%>}
picture command={%<picture command%>}
geometry={%<picture geometry spec%>}
stack macro={%<stack definition%>}
arrow macro={%<arrow definition%>}
no stack macro hook={%<code%>}
no arrow macro hook={%<code%>}
fill macro={%<definition%>}
#endkeyvals

\TestOverArrow{arrow command%cmd}
\TestOverArrow[pattern]{arrow command%cmd}
\TestOverArrow*{arrow command%cmd}
\TestOverArrow*[pattern]{arrow command%cmd}
\xjoinrel
\xjoinrel[number]
\smallermathstyle
\arrowmathstyle
\baselinebar
\overarrowlength#L
\overarrowthickness#L
\overarrowsmallerthickness#L
\esvectvv{arg}#*
\esvectvv*{arg}{sub}#*
\SetOverArrowsSubscriptCommand{command}#*
\SetOverArrowsMethod{name}{keys def}#*
\SetOverArrowsMethod{name}[pre code]{keys def}#*
\SetOverArrowsMethod[stack mechanism]{name}{keys def}#*
\SetOverArrowsMethod[stack mechanism]{name}[pre code]{keys def}#*
\SetOverArrowsMethod*{name}{keys def}#*
\SetOverArrowsMethod*{name}[pre code]{keys def}#*
