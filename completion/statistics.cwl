# statistics package
# Matthew Bertucci 12/13/2021 for v2.2

#include:etoolbox
#include:siunitx
#include:tikz
#include:tikzlibrarydatavisualization
#include:tikzlibraryfit

\StatsSortData %<\macro%> = {%<data source%>}
\StatsSortData{cmd}#Sd
\StatsRangeData %<\macro%> = {%<data source%>} (%<range list%>)
\StatsRangeData{cmd}#Sd

\statisticssetup{options%keyvals}
\statisticssetup[module]{options%keyvals}

\StatsTable{data source}
\StatsTable[options%keyvals]{data source}
\StatsTable{data source}[options]#*
\StatsTable[options%keyvals]{data source}[options]#*

#keyvals:\statisticssetup#c,\StatsTable
values
values=%<row header text%>
counts
counts=%<row header text%>
frequencies
frequencies=%<row header text%>
icc
icc=%<row header text%>
icf
icf=%<row header text%>
dcc
dcc=%<row header text%>
dcf
dcf=%<row header text%>
novalues
nocounts
nofrequencies
noicc
nodcc
noicf
nodcf
values/header=%<row header text%>
counts/header=%<row header text%>
frequencies/header=%<row header text%>
icc/header=%<row header text%>
icf/header=%<row header text%>
dcc/header=%<row header text%>
dcf/header=%<row header text%>
values/format=%<formatting code%>
counts/format=%<formatting code%>
frequencies/format=%<formatting code%>
icc/format=%<formatting code%>
icf/format=%<formatting code%>
dcc/format=%<formatting code%>
dcf/format=%<formatting code%>
allcounts/format=%<formatting code%>
allfreqs/format=%<formatting code%>
allfreqs/format/percent
allfreqs/format/real
digits=%<integer%>
showonly={%<integer/range list%>}
showonly/hidden=%<formatting code%>
showonly/shown=%<formatting code%>
maxcols={%<integer list%>}
tablesep=%<TeX content%>
preline=%<array content%>
postline=%<array content%>
outline=%<array content%>
newline=%<array content%>
coltype=%<coltype%>
headcoltype=%<coltype%>
frame=#none,clean,full
valign=#t,c,b
#endkeyvals

\IN#*
\currentcolumn#*
\valuename#*
\countname#*
\freqname#*
\iccname#*
\icfname#*
\dccname#*
\dcfname#*
\firsthline#*
\lasthline#*

\StatsGraph{data source}
\StatsGraph[options%keyvals]{data source}
\StatsGraph{data source}[options]#*
\StatsGraph[options%keyvals]{data source}[options]#*

#keyvals:\statisticssetup#c,\StatsGraph
picture={%<TikZ options%>}
picture/reset
axissystem={%<TikZ axis options%>}
axissystem/reset
width=##L
height
tikzinfo'={%<TikZ picture code%>}
tikzinfo'/reset
tikzinfo={%<TikZ picture code%>}
tikzinfo/reset
style={%<TikZ path options%>}
style/reset
comb/style={%<TikZ path options%>}
comb/style/reset
histogram/style={%<TikZ path options%>}
histogram/style/reset
cumulative/style={%<TikZ path options%>}
cumulative/style/reset
showonly={%<integer/range list%>}
counts
counts=%<label%>
frequencies
frequencies=%<label%>
comb/counts
comb/counts=%<label%>
comb/frequencies
comb/frequencies=%<label%>
histogram/counts
histogram/counts=%<label%>
histogram/frequencies
histogram/frequencies=%<label%>
cumulative/counts
cumulative/counts=%<label%>
cumulative/frequencies
cumulative/frequencies=%<label%>
counts/label=%<label%>
frequencies/label=%<label%>
comb/counts/label=%<label%>
comb/frequencies/label=%<label%>
histogram/counts/label=%<label%>
histogram/frequencies/label=%<label%>
cumulative/counts/label=%<label%>
cumulative/frequencies/label=%<label%>
y/label=%<label%>
comb/y/label=%<label%>
histogram/y/label=%<label%>
cumulative/y/label=%<label%>
counts/axis={%<TikZ axis options%>}
frequencies/axis={%<TikZ axis options%>}
comb/counts/axis={%<TikZ axis options%>}
comb/frequencies/axis={%<TikZ axis options%>}
histogram/counts/axis={%<TikZ axis options%>}
histogram/frequencies/axis={%<TikZ axis options%>}
cumulative/counts/axis={%<TikZ axis options%>}
cumulative/frequencies/axis={%<TikZ axis options%>}
counts/axis/reset
frequencies/axis/reset
comb/counts/axis/reset
comb/frequencies/axis/reset
histogram/counts/axis/reset
histogram/frequencies/axis/reset
cumulative/counts/axis/reset
cumulative/frequencies/axis/reset
y/axis={%<TikZ axis options%>}
y/axis/reset
comb/axis={%<TikZ axis options%>}
comb/axis/reset
histogram/axis={%<TikZ axis options%>}
histogram/axis/reset
cumulative/axis={%<TikZ axis options%>}
cumulative/axis/reset
counts/format=%<formatting code%>
frequencies/format=%<formatting code%>
y/format=%<formatting code%>
comb/counts/format=%<formatting code%>
comb/frequencies/format=%<formatting code%>
comb/y/format=%<formatting code%>
histogram/counts/format=%<formatting code%>
histogram/frequencies/format=%<formatting code%>
histogram/y/format=%<formatting code%>
cumulative/counts/format=%<formatting code%>
cumulative/frequencies/format=%<formatting code%>
cumulative/y/format=%<formatting code%>
frequencies/format/real=%<places%>
comb/frequencies/format/real=%<places%>
histogram/frequencies/format/real=%<places%>
cumulative/frequencies/format/real=%<places%>
frequencies/format/percent=%<places%>
comb/frequencies/format/percent=%<places%>
histogram/frequencies/format/percent=%<places%>
cumulative/frequencies/format/percent=%<places%>
counts/margin=%<expr%>
frequencies/margin=%<expr%>
y/margin=%<expr%>
comb/counts/margin=%<expr%>
comb/frequencies/margin=%<expr%>
comb/y/margin=%<expr%>
histogram/counts/margin=%<expr%>
histogram/frequencies/margin=%<expr%>
histogram/y/margin=%<expr%>
cumulative/counts/margin=%<expr%>
cumulative/frequencies/margin=%<expr%>
cumulative/y/margin=%<expr%>
values/label=%<label%>
x/label=%<label%>
comb/values/label=%<label%>
comb/x/label=%<label%>
histogram/values/label=%<label%>
histogram/x/label=%<label%>
cumulative/values/label=%<label%>
cumulative/x/label=%<label%>
values/axis={%<TikZ axis options%>}
x/axis={%<TikZ axis options%>}
comb/values/axis={%<TikZ axis options%>}
comb/x/axis={%<TikZ axis options%>}
histogram/values/axis={%<TikZ axis options%>}
histogram/x/axis={%<TikZ axis options%>}
cumulative/values/axis={%<TikZ axis options%>}
cumulative/x/axis={%<TikZ axis options%>}
values/axis/reset
x/axis/reset
comb/values/axis/reset
comb/x/axis/reset
histogram/values/axis/reset
histogram/x/axis/reset
cumulative/values/axis/reset
cumulative/x/axis/reset
values/format=%<formatting code%>
x/format=%<formatting code%>
comb/values/format=%<formatting code%>
comb/x/format=%<formatting code%>
histogram/values/format=%<formatting code%>
histogram/x/format=%<formatting code%>
cumulative/values/format=%<formatting code%>
cumulative/x/format=%<formatting code%>
values/margin=%<expr%>
x/margin=%<expr%>
comb/values/margin=%<expr%>
comb/x/margin=%<expr%>
histogram/values/margin=%<expr%>
histogram/x/margin=%<expr%>
cumulative/values/margin=%<expr%>
cumulative/x/margin=%<expr%>
cumulative#true,false
decreasing#true,false
histogram/areas#true,false
histogram/areas/style={%<TikZ node options%>}
histogram/areas/style/reset
histogram/counts/autostep
histogram/counts/autostep=%<fp expr%>
histogram/frequencies/autostep
histogram/frequencies/autostep=%<fp expr%>
histogram/y/autostep
histogram/y/autostep=%<fp expr%>
histogram/legend={%<legend keys%>}
histogram/legend/x
histogram/legend/x=%<fp expr%>
histogram/legend/w
histogram/legend/w=%<fp expr%>
histogram/legend/y=%<fp expr%>
histogram/legend/h=%<fp expr%>
histogram/legend/area=%<fp expr%>
histogram/legend/options={%<TikZ node options%>}
histogram/legend/options/reset
histogram/legend/label=%<TikZ label value%>
#endkeyvals

\ccountname#*
\cfreqname#*
\min#*
\max#*
\range#*
\xstep#*
\total#*
