# CWL for the pgfplotstable.sty package
# Matthew Bertucci updated 12/23/2021 for v1.18.1

### Dependency Tree ###
# pgfplotstable.sty
# ├── pgfplots.sty
# ├── array.sty
# └── pgfplotstable.code.tex
#     └── pgfplotstable.coltype.code.tex

#include:pgfplots
#include:array

\pgfplotstableset{options%keyvals}
\pgfplotstabletypeset{table}
\pgfplotstabletypeset[options%keyvals]{table}
\pgfplotstabletypesetfile{file}
\pgfplotstabletypesetfile[options%keyvals]{file}
\pgfplotstableread{table}{macro%cmd}#d

\pgfplotstablecol#*
\pgfplotstablecolname#*
\pgfplotstablerow#*
\pgfplotstablecols#*
\pgfplotstablerows#*
\pgfplotstablename#*
\pgfplotstablepartno#*

\pgfplotstablenew{row count}{macro%cmd}#d
\pgfplotstablenew[options%keyvals]{row count}{macro%cmd}#d
\pgfplotstablenew*{row count}{macro%cmd}#d
\pgfplotstablenew*[options%keyvals]{row count}{macro%cmd}#d
\pgfplotstablevertcat{table1%cmd}{table2}#d
\pgfplotstableclear{table}

\pgfplotstablecreatecol{new col name}{table}
\pgfplotstablecreatecol[options%keyvals]{new col name}{table}

\prevrow{col name}#*
\getprevrow{col name}{macro%cmd}#*d
\thisrow{col name}#*
\getthisrow{col name}{macro%cmd}#*d
\nextrow{col name}#*
\getnextrow{col name}{macro%cmd}#*d
\pgfmathaccuma#*
\pgfmathaccumb#*

\pgfplotstablesave{table}{output-file name}
\pgfplotstablesave[options%keyvals]{table}{output-file name}

\pgfplotstableforeachcolumn%<\table%>\as%<\macro%>{%<code%>}#*
\pgfplotstableforeachcolumnelement{%<col name%>}\of{%<\table%>}\as%<\macro%>{%<code%>}#*
\pgfplotstablemodifyeachcolumnelement{%<col name%>}\of{%<\table%>}\as%<\macro%>{%<code%>}#*
\pgfplotstablegetelem{%<row%>}{%<column%>}\of{%<\table%>}#*
\pgfplotstablegetcolumnnamebyindex{%<col index%>}\of{%<\table%>}\to%<\macro%>#*
\pgfplotstablegetrowsof{table}#*
\pgfplotstablegetcolsof{table}#*

\pgfplotstabletranspose{macro%cmd}{table}#d
\pgfplotstabletranspose[options%keyvals]{macro%cmd}{table}#d
\pgfplotstabletranspose*{macro%cmd}{table}#d
\pgfplotstabletranspose*[options%keyvals]{macro%cmd}{table}#d
\pgfplotstablesort{macro%cmd}{table}#d
\pgfplotstablesort[options%keyvals]{macro%cmd}{table}#d

#keyvals:\pgfplotstableset#c,\pgfplotstabletypeset#c,\pgfplotstabletypesetfile#c,\pgfplotstablenew#c,\pgfplotstablenew*#c,\pgfplotstablesave#c,\pgfplotstabletranspose#c,\pgfplotstabletranspose*#c,\pgfplotstablesort#c
col sep=#space,tab,comma,semicolon,colon,braces,&,ampersand
trim cells#true,false
header=#true,false,has colnames
format=#auto,inline,file
row sep=#newline,\\
ignore chars={%<char1,char2,...%>}
white space chars={%<char1,char2,...%>}
text special chars={%<char1,char2,...%>}
comment chars={%<char1,char2,...%>}
percent is letter#true,false
text indicator=%<char%>
skip first n=%<integer%>
search path=%<path%>
search path/implicit .#true,false
columns={%<colname1,colname2,...%>}
columns/%<colname%>/.style={%<options%>}
display columns/%<index%>/.style={%<options%>}
every col no %<index%>/.style={%<options%>}
column type=%<tabular col type%>
column type/.add={%<before%>}{%<after%>}
column name=%<TeX display colname%>
multicolumn names=%<tabular col type%>
dec sep align=%<header col type%>
sci sep align=%<header col type%>
dcolumn={%<tabular col type%>}{%<type for colname%>}
sort#true,false
every first column/.style={%<options%>}
every last column/.style={%<options%>}
every even column/.style={%<options%>}
every column/.style={%<options%>}
every odd column/.style={%<options%>}
before row={%<code%>}
after row={%<code%>}
every even row/.style={%<options%>}
every odd row/.style={%<options%>}
every head row/.style={%<options%>}
every first row/.style={%<options%>}
every last row/.style={%<options%>}
every row no %<index%>/.style={%<options%>}
every nth row={%<integer%>}{%<options%>}
every nth row={%<integer[shift]%>}{%<options%>}
every row %<index%> column %<index%>/.style={%<options%>}
every row %<index%> column %<colname%>/.style={%<options%>}
every row no %<index%> column no %<index%>/.style={%<options%>}
font=%<font commands%>
begin table={%<code%>}
end table={%<code%>}
outfile=%<file%>
include outfiles#true,false
force remake#true,false
write to macro=%<\macro%>
skip coltypes#true,false
typeset#true,false
debug#true,false
TeX comment=%<comment sign%>
fixed
fixed zerofill#true,false
sci
sci zerofill#true,false
zerofill#true,false
std
std=%<lower e%>
std=%<lower e%>:%<upper e%>
relative*=%<exponent base 10%>
relative style={%<options%>}
fixed relative
int detect
int trunc
frac
frac TeX=%<\macro%>
frac denom=%<integer%>
frac whole#true,false
frac shift=%<integer%>
precision=%<number%>
sci precision=%<number%>
read comma as period#true,false
set decimal separator=%<text%>
dec sep=%<text%>
set thousands separator=%<text%>
1000 sep=%<text%>
1000 sep in fractionals#true,false
min exponent for 1000 sep=%<number%>
use period
use comma
skip 0.#true,false
showpos#true,false
print sign#true,false
sci 10e
sci 10^e
sci E
sci subscript
sci superscript
sci generic={%<keys%>}
retain unit mantissa#true,false
assume math mode#true,false
verbatim
assign cell content/.code={%<code%>}
numeric type
string type
verb string type
numeric as string type
date type=%<date format%>
preproc cell content/.code={%<code%>}
string replace={%<cell match%>}{%<cell replacement%>}
string replace*={%<pattern%>}{%<cell replacement%>}
clear infinite
preproc/expr={%<math expr%>}
multiply by=%<real number%>
divide by=%<real number%>
sqrt
multiply -1
row predicate/.code={%<code%>}
skip rows between index={%<begin%>}{%<end%>}
select equal part entry of={%<part no%>}{%<part count%>}
unique=%<colname%>
postproc cell content/.code={%<code%>}
empty cells with=%<replacement%>
set content=%<content%>
fonts by sign={%<positive-code%>}{%<negative-code%>}
create on use/%<colname%>/.style={%<options%>}
disable rowcol styles#true,false
reset styles
#endkeyvals

#keyvals:\pgfplotstableset#c
alias/%<colname%>/.initial=%<real colname%>
every table=%<file%>
#endkeyvals

#keyvals:\pgfplotstablecreatecol#c
set=%<value%>
set list={%<val1,val2,...%>}
copy=%<colname%>
copy column from table={%<table%>}{%<colname%>}
expr={%<math expr%>}
expr accum={%<math expr%>}{%<accum init%>}
quotient=%<colname%>
iquotient=%<colname%>
dyadic refinement rate=%<colname%>
idyadic refinement rate=%<colname%>
gradient={%<col x%>}{%<col y%>}
gradient loglog={%<col x%>}{%<col y%>}
gradient semilogx={%<col x%>}{%<col y%>}
gradient semilogy={%<col x%>}{%<col y%>}
linear regression
function graph cut y={%<cut value%>}{%<common options%>}{%<one keyval set for each plot%>}
function graph cut x={%<cut value%>}{%<common options%>}{%<one keyval set for each plot%>}
#endkeyvals

#keyvals:\pgfplotstabletranspose#c,\pgfplotstabletranspose*#c,\pgfplotstableset#c
colnames from=%<colname%>
input colnames to=%<colname%>
#endkeyvals

#keyvals:\pgfplotstablesort#c,\pgfplotstableset#c
sort key=%<column%>
sort key from=%<table%>
sort cmp=#fixed <,fixed >,int <,int >,float <,float >,date <,date >,string <,string >
#endkeyvals

# following need pgfcalendar
\monthname#S
\monthshortname#S
\weekday#S
\weekdayname#S
\weekdayshortname#S

## Not documented ##
# from pgfplotstable.code.tex
\ifpgfplotstabletypesetdebug#*
\pgfplotstabletypesetdebugtrue#*
\pgfplotstabletypesetdebugfalse#*
\ifpgfplotstabletypesetskipcoltypes#*
\pgfplotstabletypesetskipcoltypestrue#*
\pgfplotstabletypesetskipcoltypesfalse#*
\ifpgfplotstabletypesetresult#*
\pgfplotstabletypesetresulttrue#*
\pgfplotstabletypesetresultfalse#*
\ifpgfplotstableuserow#*
\pgfplotstableuserowtrue#*
\pgfplotstableuserowfalse#*
\prevrowno{col name}#*
\thisrowno{col name}#*
\nextrowno{col name}#*
\pgfplotstableresetcolortbloverhangright#*
\pgfplotstableresetcolortbloverhangleft#*
\pgfmatharga#S
\pgfmathargb#S
# from pgfplotstable.coltype.code.tex
\pgfplotstablecoltype#*
\endpgfplotstablecoltype#*
