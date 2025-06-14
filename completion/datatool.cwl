# datatool package
# Matthew Bertucci 2025/03/15 for v3.2

#include:ifthen
#include:xfor
#include:etoolbox
#include:tracklang
#include:datatool-base

### Options ###
#keyvals:\usepackage/datatool#c
delimiter=%<char%>
separator=%<char%>
# options passed to datatool-base
math=#l3fp,lua,fp,pgfmath
lang-warn#true,false
nolocale
locales={%<locales list%>}
lang={%<locales list%>}
verbose#true,false
initial-purify=#early,late
auto-reformat-types={%<list of types%>}
lists={%<keyvals%>}
compare={%<keyvals%>}
numeric={%<keyvals%>}
datetime={%<keyvals%>}
#endkeyvals

#keyvals:\DTLsetup,\usepackage/datatool#c
default-name=%<db name%>
new-value-expand#true,false
new-value-trim#true,false
store-datum#true,false
#endkeyvals

#keyvals:\DTLsetup
io={%<keyvals%>}
global#true,false
#endkeyvals

#ifOption:math=fp
#include:fp
#endif

#ifOption:math=pgfmath
#include:pgfrcs
#include:pgfkeys
#include:pgfmath
#endif

\dtlexpandnewvalue#*
\dtlnoexpandnewvalue#*

### Action Command ###
\DTLaction{action}
\DTLaction[settings%keyvals]{action}

#keyvals:\DTLaction
name=#%db
key=%<label%>
key2=%<label%>
column=%<integer%>
column2=%<integer%>
columns={%<list%>}
keys={%<list%>}
row=%<integer%>
row2=%<integer%>
assign={%<keyvals%>}
options={%<list%>}
value=%<value%>
expand-value=%<value%>
expand-once-value=%<value%>
type=#string,integer,int,decimal,real,currency
return={%<assign list%>}
datum={%<keyvals|true|false%>}
#endkeyvals

\DTLget{cmd}#d
\DTLget[property]{cmd}#d
\DTLuse{property}
\DTLifaction{property}{true}{false}#*

## Creating a New Database ##
\DTLnewdb{db%specialDef}#s#%db
\DTLgnewdb{db%specialDef}#s#%db
\DTLnewrow{db%special}
\DTLnewdbentry{db%special}{col key}{value}
\DTLpar#*
\DTLdeletedb{db%special}
\DTLgdeletedb{db%special}
\DTLcleardb{db%special}
\DTLgcleardb{db%special}
\DTLifdbexists{db%special}{true code}{false code}#*
\DTLifdbempty{db%special}{true code}{false code}#*
\DTLifhaskey{db%special}{col key}{true code}{false code}#*
\DTLrowcount{db%special}
\DTLcolumncount{db%special}
\DTLgetcolumnindex{cmd}{db%special}{col key}#d
\dtlcolumnindex{db%special}{col key}#*
\DTLgetkeyforcolumn{cmd}{db%special}{column index}#d
\DTLgetdatatype{cmd}{db%special}{col key}#d
\DTLunsettype#*
\DTLstringtype#*
\DTLinttype#*
\DTLrealtype#*
\DTLcurrencytype#*
\DTLsetheader{db%special}{col key}{header}
\DTLsetheader*{db%special}{col key}{header}
\DTLaddcolumn{db%special}{col key}
\DTLaddcolumn*{db%special}{col key}
\DTLaddcolumnwithheader{db%special}{col key}{header}
\DTLaddcolumnwithheader*{db%special}{col key}{header}

## Displaying the Contents of a Database ##
\DTLdisplaydb{db%special}
\DTLdisplaydb[omit list]{db%special}
\DTLdisplaydb*{db%special}
\DTLdisplaydb*[options%keyvals]{db%special}
\DTLdisplaylongdb{db%special}
\DTLdisplaylongdb[options%keyvals]{db%special}

#keyvals:\DTLdisplaydb*,\DTLdisplaylongdb
init=%<code%>
pre-content=%<code%>
per-row=%<number%>
row-idx-map-inline=%<definition%>
row-idx-map-function=%<cmd%>
post-row-inline=%<definition%>
post-row-function=%<cmd%>
string-align=%<col spec%>
integer-align=%<col spec%>
int-align=%<col spec%>
decimal-align=%<col spec%>
real-align=%<col spec%>
currency-align=%<col spec%>
inter-col=%<align spec%>
pre-col=%<align spec%>
post-col=%<align spec%>
align-specs=%<specs%>
pre-head=%<code%>
post-head=%<code%>
after-head=%<code%>
header-row=%<code%>
no-header#true,false
foot=%<code%>
row-condition-inline=%<definition%>
row-condition-function=%<cmd%>
omit-columns={%<index1,index2,...%>}
omit-keys={%<col key1,col key2,...%>}
only-columns={%<index1,index2,...%>}
only-keys={%<col key1,col key2,...%>}
#endkeyvals

#keyvals:\DTLdisplaydb*
tabular-env=%<envname%>
#endkeyvals

#keyvals:\DTLdisplaylongdb
longtable-env=%<envname%>
caption=%<text%>
cont-caption=%<text%>
contcaption=%<text%>
short-caption=%<text%>
shortcaption=%<text%>
label=##l
last-foot=%<text%>
lastfoot=%<text%>
#endkeyvals

\dtlcolumnheader{align}{text}#*
\dtladdheaderalign{cmd}{type}{col num}{max cols}#*
\dtlheaderformat{text}#*
\dtlstringformat{text}#*
\dtlintformat{text}#*
\dtlrealformat{text}#*
\dtlcurrencyformat{text}#*
\dtldisplaystarttab#*
\dtldisplayafterhead#*
\dtldisplayendtab#*
\dtldisplaystartrow#*
\dtldisplaydbenv#*
\dtldisplayvalign#*
\dtldisplaylongdbenv#*
\dtlstringalign#*
\dtlintalign#*
\dtlrealalign#*
\dtlcurrencyalign#*
\dtlbeforecols#*
\dtlbetweencols#*
\dtlaftercols#*
\dtldisplaycr#*
\DTLdisplaydbAddItem{cmd}{item}{fmt cmd}{type}{row num}{row idx}{col num}{col idx}#*
\dtladdalign{cmd}{type}{col index}{max cols}#*
\DTLdisplaydbAddBegin{cmd}{align spec}{header}#*
\DTLdisplaydbAddEnd{cmd}#*
\DTLdisplaylongdbAddBegin{cmd}{align spec}{header}#*
\DTLdisplaylongdbAddEnd{cmd}#*
\DTLdisplayTBrowidxmap{index}#*

## Iterating Through a Database ##
\DTLmapdata{loop body}
\DTLmapdata[keyvals]{loop body}
\begin{DTLenvmapdata}
\begin{DTLenvmapdata}[keyvals]
\end{DTLenvmapdata}

#keyvals:\DTLmapdata,\begin{DTLenvmapdata}
name=%<value%>
read-only#true,false
allow-edits#true,false
#endkeyvals

\DTLmapdatabreak
\DTLmapget{keyvals}

#keyvals:\DTLmapget
key=%<value%>
column=%<index%>
return=%<cmd%>
#endkeyvals

\DTLmaprow{cmd}{body}
\DTLmaprowbreak
\DTLmapgetvalues{assign list}
\DTLrmrow
\DTLrmentry{keyvals}
\DTLsetentry{keyvals}

#keyvals:\DTLrmentry,\DTLsetentry
column=%<index%>
key=%<col key%>
#endkeyvals

#keyvals:\DTLsetentry
value=%<value%>
expand-value=%<value%>
expand-once-value=%<value%>
#endkeyvals

# older commands
\DTLforeach{db%special}{assign list}{text}#*
\DTLforeach[condition]{db%special}{assign list}{text}#*
\DTLforeach*{db%special}{assign list}{text}#*
\DTLforeach*[condition]{db%special}{assign list}{text}#*
\begin{DTLenvforeach}{db%special}{assign list}#*
\begin{DTLenvforeach}[condition]{db%special}{assign list}#*
\end{DTLenvforeach}#*
\begin{DTLenvforeach*}{db%special}{assign list}#*
\begin{DTLenvforeach*}[condition]{db%special}{assign list}#*
\end{DTLenvforeach*}
\DTLsavelastrowcount{cmd}#*d
\dtlforeachlevel#*
\theDTLrowi#*
\theDTLrowii#*
\theDTLrowiii#*
\theDTLrow#*
\DTLrowreset#*
\DTLrowincr#*
\DTLtherow#*
\DTLcurrentindex#*
\DTLiffirstrow{true code}{false code}#*
\DTLiflastrow{true code}{false code}#*
\DTLifoddrow{true code}{false code}#*
\dtlkey#*
\dtlcol#*
\dtltype#*
\dtlheader#*
\DTLappendtorow{col key}{value}#*
\DTLreplaceentryforrow{col key}{value}#*
\DTLremoveentryfromrow{col key}#*
\DTLremovecurrentrow#*

## Null Values ##
\DTLifnull{cmd}{true code}{false code}#*
\DTLifnullorempty{cmd}{true code}{false code}#*
\dtlnovalue#*
\DTLstringnull#*
\DTLnumbernull#*

## Special Values ##
\dtlspecialvalue{text}#*

## Arithmetical Computations on Database Entries ##
\DTLsumforkeys{db%special}{key list}{cmd}#d
\DTLsumforkeys[condition]{db%special}{key list}{cmd}#d
\DTLsumforkeys[condition][assign list]{db%special}{key list}{cmd}#d
\DTLsumcolumn{db%special}{col key}{cmd}#d
\DTLmeanforkeys{db%special}{key list}{cmd}#d
\DTLmeanforkeys[condition]{db%special}{key list}{cmd}#d
\DTLmeanforkeys[condition][assign list]{db%special}{key list}{cmd}#d
\DTLmeanforcolumn{db%special}{col key}{cmd}#d
\DTLvarianceforkeys{db%special}{key list}{cmd}#d
\DTLvarianceforkeys[condition]{db%special}{key list}{cmd}#d
\DTLvarianceforkeys[condition][assign list]{db%special}{key list}{cmd}#d
\DTLvarianceforcolumn{db%special}{col key}{cmd}#d
\DTLsdforkeys{db%special}{key list}{cmd}#d
\DTLsdforkeys[condition]{db%special}{key list}{cmd}#d
\DTLsdforkeys[condition][assign list]{db%special}{key list}{cmd}#d
\DTLsdforcolumn{db%special}{col key}{cmd}#d
\DTLminforkeys{db%special}{key list}{cmd}#d
\DTLminforkeys[condition]{db%special}{key list}{cmd}#d
\DTLminforkeys[condition][assign list]{db%special}{key list}{cmd}#d
\DTLminforcolumn{db%special}{col key}{cmd}#d
\DTLmaxforkeys{db%special}{key list}{cmd}#d
\DTLmaxforkeys[condition]{db%special}{key list}{cmd}#d
\DTLmaxforkeys[condition][assign list]{db%special}{key list}{cmd}#d
\DTLmaxforcolumn{db%special}{col key}{cmd}#d
\DTLcomputebounds{db%special}{x key}{y key}{minX%cmd}{minY%cmd}{maxX%cmd}{maxY%cmd}#*d

## Sorting a Database ##
\DTLsortdata{db%special}{criteria}
\DTLsortdata[options%keyvals]{db%special}{criteria}

#keyvals:\DTLsortdata
function=%<function%>
encap=%<cmd%>
replace=#null,null or empty#c
missing-column-action=#error,warn,ignore
save-group-key=%<col key%>
save-group-column=%<col index%>
save-group
save-sort-key=%<col key%>
save-sort-column=%<col index%>
save-sort
#endkeyvals

# older commands
\dtlsort{criteria}{db%special}{handler}#*
\dtlsort[replacements]{criteria}{db%special}{handler}#*
\DTLsort{criteria}{db%special}#*
\DTLsort[replacements]{criteria}{db%special}#*
\DTLsort*{criteria}{db%special}#*
\DTLsort*[replacements]{criteria}{db%special}#*

## Database Files (I/O) ##
\DTLdbProvideData#*
\DTLdbNewRow#*
\DTLdbNewEntry{col key}{value}#*
\DTLdbSetHeader{col key}{header}#*
\DTLreconstructdatabase{num rows}{num cols}{header code}{body code}{key-index code}#*
\dtldbheaderreconstruct{col index}{key%plain}{type}{header}#*
\dtldbreconstructkeyindex{key%plain}{col index}#*
\dtldbrowreconstruct{row index}{row code}#*
\dtldbcolreconstruct{col index}{content}#*
\dtldbvaluereconstruct{string}#*
\dtldbdatumreconstruct{string}{numeric}{currency}{type}#*
\dtldefaultkey#*
\DTLrawmap{original}{replacement}#*
\DTLsetdelimiter{char}#*
\DTLsetseparator{char}#*
\DTLsettabseparator#*
\DTLread{file}
\DTLread[options%keyvals]{file}
\dtllastloadeddb#*
\DTLwrite{file}
\DTLwrite[options%keyvals]{file}

#keyvals:\DTLread,\DTLwrite,\DTLloaddb,\DTLloadrawdb
auto-keys#true,false
autokeys#true,false
delimiter=%<char%>
expand=#none,protected,full
format=#csv,tsv,dtltex-2,dtltex-3,dtltex,dbtex-2,dbtex-3,dbtex
name=%<db name%>
no-header#true,false
noheader#true,false
separator=%<char%>
#endkeyvals

#keyvals:\DTLread,\DTLloaddb,\DTLloadrawdb
convert-numbers#true,false
csv-blank=#ignore,empty-row,end
csv-content=#tex,literal,no-parse
csv-escape-chars=#double-delim,delim,delim+bksl,none
csv-skip-lines=%<integer%>
data-types={%<list%>}
headers={%<header1,header2,...%>}
keys={%<key1,key2,...%>}
load-action=#detect,create,append,overwrite,old-style
only-reformat-columns={%<list%>}
omitlines=%<integer%>
trim#true,false
#endkeyvals

#keyvals:\DTLwrite
add-delimiter=#always,never,detect
overwrite=#error,warn,allow
#endkeyvals

# older commands
\DTLloaddbtex{cmd}{file}#*d
\DTLloaddb{db%specialDef}{file}#*s#%db
\DTLloaddb[options%keyvals]{db%specialDef}{file}#*s#%db
\DTLloadrawdb{db%specialDef}{file}#*s#%db
\DTLloadrawdb[options%keyvals]{db%specialDef}{file}#*s#%db
\DTLsavedb{db%special}{filename}#*
\DTLsaverawdb{db%special}{filename}#*
\DTLprotectedsaverawdb{db%special}{filename}#*
\DTLsavetexdb{db%special}{filename}#*

## Advanced Database Commands ##
\dtlgetrowindex{row cmd%cmd}{db%special}{col index}{value}#*d
\DTLgetrowindex{row cmd%cmd}{db%special}{col index}{value}#*d
\DTLgetrowindex*{row cmd%cmd}{db%special}{col index}{value}#*d
\xdtlgetrowindex{row cmd%cmd}{db%special}{col index}{value}#*d
\DTLgetvalue{cmd}{db%special}{row index}{col index}#*d
\DTLgetlocation{row cmd%cmd}{col cmd%cmd}{db%special}{value}#*d
\DTLassignfirstmatch{db%special}{col key}{value}{assign list}#*
\dtlswaprows{db%special}{row1 index}{row2 index}#*
\dtlcurrentrow#*
\dtlbeforerow#*
\dtlafterrow#*
\dtlrownum#*
\dtlcolumnnum#*
\dtldbname#*
\dtlgetentryfromcurrentrow{cmd}{col index}#*d
\DTLassignfromcurrentrow{assign list}#*
\dtlgetrow{db%special}{row index}#*
\dtlgetrowforvalue{db%special}{col index}{value}#*
\edtlgetrowforvalue{db%special}{col index}{value}#*
\DTLassign{db%special}{row index}{assign list}#*
\dtlrecombine#*
\dtlrecombineomitcurrent#*
\dtlreplaceentryincurrentrow{new value}{col index}#*
\dtlappendentrytocurrentrow{col key}{value}#*
\dtlupdateentryincurrentrow{col key}{value}#*
\dtlremoveentryincurrentrow{col index}#*
\dtlswapentriesincurrentrow{col1 index}{col2 index}#*
\dtlforeachkey(key cmd,col cmd,type cmd,header cmd)\in{db%special}\do{body}#*
\in{db%special}#S
\do{body}#S
\dtlforcolumn{cmd}{db%special}{col key}{body}#*d
\dtlforcolumnidx{cmd}{db%special}{col index}{body}#*d

## Miscellaneous ##
\DTLforeachkeyinrow{cmd}{text}#*d
\dtlgetentryfromrow{cmd}{col index}{row toks}#*d
\dtlshowdbkeys{db%special}#*
\dtlshowdb{db%special}#*
\dtlshowtype{db%special}{col key}#*
\theHDTLrow#*
\theHDTLrowi#*
\theHDTLrowii#*
\theHDTLrowiii#*

# not documented/deprecated
\DTLaddentryforrow{db%special}{assign list}{condition}{col key}{value}#S
\DTLfetch{db%special}{col1 name}{col1 value}{col2 name}#S
\DTLgetkeydata{col key}{db%special}{col cmd%cmd}{type cmd%cmd}{header cmd%cmd}#Sd
\DTLgetrowforkey{cmd}{db%special}{ref key}{ref value}#Sd
\DTLgetvalueforkey{cmd}{col key}{db%special}{ref key}{ref value}#Sd
\DTLmaketabspace#S
\DTLnewdbonloadfalse#S
\DTLnewdbonloadtrue#S
\DTLremoverow{db%special}{row index}#S
\dtlautokeysfalse#S
\dtlautokeystrue#S
\dtlnoheaderfalse#S
\dtlnoheadertrue#S
\dtlsplitrow{row specs}{col index}{before cmd%cmd}{after cmd%cmd}#Sd
\ifDTLnewdbonload#S
\ifdtlautokeys#S
\ifdtlnoheader#S
\xDTLassignfirstmatch{db%special}{col key}{value}{assign list}#S
