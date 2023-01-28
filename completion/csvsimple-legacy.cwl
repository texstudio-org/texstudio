# csvsimple-legacy package
# Matthew Bertucci 4/2/2022 for v2.3.0

#include:etoolbox
#include:ifthen
#include:pgfkeys
#include:pgfrcs
#include:shellesc

\csvreader{file}{assignments}{command list%definition}
\csvreader[options%keyvals]{file}{assignments}{command list%definition}

\csvcoli#*
\csvcolii#*
\csvcoliii#*
\csvcoliv#*
\csvcolv#*

\csvloop{options%keyvals}

\csvautotabular{file}
\csvautotabular[options%keyvals]{file}

\csvautolongtable{file}
\csvautolongtable[options%keyvals]{file}

\csvautobooktabular{file}
\csvautobooktabular[options%keyvals]{file}

\csvautobooklongtable{file}
\csvautobooklongtable[options%keyvals]{file}

\csvset{options%keyvals}

\csvstyle{key name%specialDef}{options%keyvals}#s#%csvstyle
\csvnames{key name%specialDef}{assignments%definition}#s#%csvstyle
\csvheadset{assignments%definition}

\csviffirstrow{then}{else}
\csvifoddrow{then}{else}
\csvfilteraccept
\csvfilterreject
\csvline
\thecsvrow
\thecsvcol#*
\thecsvinputline
\csvlinetotablerow

\ifcsvstrcmp{stringA}{stringB}{true}{false}
\ifcsvnotstrcmp{stringA}{stringB}{true}{false}
\ifcsvstrequal{stringA}{stringB}{true}{false}
\ifcsvprostrequal{stringA}{stringB}{true}{false}

#keyvals:\csvreader,\csvloop,\csvautotabular,\csvautolongtable,\csvautobooktabular,\csvautobooklongtable,\csvset,\csvstyle
before reading=%<code%>
after head=%<code%>
before filter=%<code%>
after filter=%<code%>
late after head=%<code%>
late after line=%<code%>
late after first line=%<code%>
late after last line=%<code%>
before line=%<code%>
before first line=%<code%>
command=%<code%>
after line=%<code%>
after first line=%<code%>
after reading=%<code%>
head#true,false
no head
column names={%<assignments%>}
column names reset
head to column names#true,false
head to column names prefix=%<text%>
check column count#true,false
no check column count 
column count=%<number%>
on column count error=%<code%>
warn on column count error
filter test=%<condition%>
filter strcmp={%<stringA%>}{%<stringB%>}
filter not strcmp={%<stringA%>}{%<stringB%>}
filter expr=%<condition%>
filter ifthen=%<boolean expr%>
filter=%<condition%>
filter equal={%<stringA%>}{%<stringB%>}
filter not equal={%<stringA%>}{%<stringB%>}
no filter
filter accept all 
filter reject all
full filter=%<code%>
range={%<range1,range2,...%>}
tabular=%<preamble%>
centered tabular=%<preamble%>
longtable=%<preamble%>
tabbing
centered tabbing
no table
before table=%<code%>
table head=%<code%>
table foot=%<code%>
after table=%<code%>
respect tab#true,false
respect percent#true,false
respect sharp#true,false
respect dollar#true,false
respect and#true,false
respect backslash#true,false
respect underscore#true,false
respect tilde#true,false
respect circumflex#true,false
respect leftbrace#true,false
respect rightbrace#true,false
respect all 
respect none
separator=#comma,semicolon,pipe,tab
every csv/.style={%<options%>}
default/.style={%<options%>}
file=%<file%>
preprocessed file=%<file%>
preprocessor=%<macro%>
no preprocessing
csvsorter command=%<system command%>
csvsorter configpath=%<path%>
csvsorter log=%<file%>
csvsorter token=%<file%>
sort by=%<file%>
new sorting rule={%<name%>}{%<file%>}
%csvstyle
#endkeyvals

#keyvals:\csvreader,\csvloop
autotabular=%<file%>
autolongtable=%<file%>
autobooktabular=%<file%>
autobooklongtable=%<file%>
#endkeyvals

# Let common tabular commands be used in \csvreader etc.
# Without listing them here, they're marked as incorrect outside tabular envs
\cline{i-j}
\hline
\tabularnewline
\toprule#S
\midrule#S
\bottomrule#S
\cmidrule#S
\morecmidrules#S
\specialrule#S
\addlinespace#S
