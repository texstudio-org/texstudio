# csvsimple-l3 package
# Matthew Bertucci 2023/05/09 for v2.4.0

\csvreader{file}{assignments%definition}{command list%definition}
\csvreader[options%keyvals]{file}{assignments%definition}{command list%definition}

\csvcoli#*
\csvcolii#*
\csvcoliii#*
\csvcoliv#*
\csvcolv#*

\csvloop{options%keyvals}

\csvautotabular{file}
\csvautotabular[options%keyvals]{file}
\csvautotabular*{file}
\csvautotabular*[options%keyvals]{file}

\csvautolongtable{file}
\csvautolongtable[options%keyvals]{file}
\csvautolongtable*{file}
\csvautolongtable*[options%keyvals]{file}

\csvautobooktabular{file}
\csvautobooktabular[options%keyvals]{file}
\csvautobooktabular*{file}
\csvautobooktabular*[options%keyvals]{file}

\csvautobooklongtable{file}
\csvautobooklongtable[options%keyvals]{file}
\csvautobooklongtable*{file}
\csvautobooklongtable*[options%keyvals]{file}

\csvset{options%keyvals}

\csvstyle{key name%specialDef}{options%keyvals}#s#%csvstyle
\csvnames{key name%specialDef}{assignments%definition}#s#%csvstyle
\csvfilterbool{key name%specialDef}{boolean expr}#s#%csvstyle

\ifcsvoddrow{then}{else}
\ifcsvfirstrow{then}{else}
\csvfilteraccept
\csvfilterreject
\csvline
\csvlinetotablerow
\thecsvrow
\thecsvcolumncount
\thecsvinputline

\csvsortingrule{name}{file}
\csvdatacollection
\csvexpval%<\macro%>
\csvexpnot%<\macro%>
\csvcollectn{code}
\csvcollectx{code}
\csvcollectV%<\macro%>

\ifcsvstrcmp{stringA}{stringB}{true}{false}
\ifcsvnotstrcmp{stringA}{stringB}{true}{false}
\ifcsvstrequal{stringA}{stringB}{true}{false}
\ifcsvprostrequal{stringA}{stringB}{true}{false}
\ifcsvfpcmp{floating point expr}{true}{false}
\ifcsvintcmp{integer expr}{true}{false}

#keyvals:\csvreader,\csvloop,\csvautotabular,\csvautotabular*,\csvautolongtable,\csvautolongtable*,\csvautobooktabular,\csvautobooktabular*,\csvautobooklongtable,\csvautobooklongtable*,\csvset,\csvstyle
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
column names detection#true,false
check column count#true,false
no check column count 
column count=%<number%>
on column count error=%<code%>
warn on column count error
filter strcmp={%<stringA%>}{%<stringB%>}
filter not strcmp={%<stringA%>}{%<stringB%>}
filter equal={%<stringA%>}{%<stringB%>}
filter not equal={%<stringA%>}{%<stringB%>}
filter fp=%<floating point expr%>
filter bool=%<boolean expr%>
and filter strcmp={%<stringA%>}{%<stringB%>}
or filter strcmp={%<stringA%>}{%<stringB%>}
and filter not strcmp={%<stringA%>}{%<stringB%>}
or filter not strcmp={%<stringA%>}{%<stringB%>}
and filter fp=%<floating point expr%>
or filter fp=%<floating point expr%>
and filter bool=%<boolean expr%>
or filter bool=%<boolean expr%>
filter test=%<condition%>
filter ifthen=%<boolean expr%>
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
tabularray=%<preamble%>
long tabularray=%<preamble%>
centered tabularray=%<preamble%>
no table
before table=%<code%>
table head=%<code%>
table foot=%<code%>
after table=%<code%>
table centered#true,false
generic table=%<name%>
generic collected table=%<name%>
generic table options={%<code%>}
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
separator=#comma,semicolon,pipe,tab,space
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
collect data#true,false
data collection=%<macro%>
%csvstyle
#endkeyvals

#keyvals:\csvreader,\csvloop
autotabular=%<file%>
autotabular*=%<file%>
autolongtable=%<file%>
autolongtable*=%<file%>
autobooktabular=%<file%>
autobooktabular*=%<file%>
autobooklongtable=%<file%>
autobooklongtable*=%<file%>
#endkeyvals

# deprecated
\csvifoddrow{then}{else}#S
\csviffirstrow{then}{else}#S

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
