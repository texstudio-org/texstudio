# mode: listings.sty
# dani/2006-02-18; Matthew Bertucci 2021-08-28 for v1.8d

\lstloadlanguages{lang1,lang2,...%keyvals}

#keyvals:\lstloadlanguages#c
ABAP
[R/2 4.3]ABAP
[R/2 5.0]ABAP
[R/3 3.1]ABAP
[R/3 4.6C]ABAP
[R/3 6.10]ABAP
ACM
ACSL
ACMscript
Ada
[2005]Ada
[83]Ada
[95]Ada
Algol
[60]Algol
[68]Algol
Ant
Assembler
[Motorola68k]Assembler
[x86masm]Assembler
Awk
[gnu]Awk
[POSIX]Awk
bash
Basic
[Visual]Basic
C
[ANSI]C
[Handel]C
[Objective]C
[Sharp]C
C++
[11]C++
[ANSI]C++
[GNU]C++
[ISO]C++
[Visual]C++
Caml
[light]Caml
[Objective]Caml
CIL
Clean
Cobol
[1974]Cobol
[1985]Cobol
[ibm]Cobol
Comal 80
command.com
[WinXP]command.com
Comsol
csh
Delphi
Eiffel
Elan
elisp
erlang
Euphoria
Fortran
[03]Fortran
[08]Fortran
[77]Fortran
[90]Fortran
[95]Fortran
GAP
GCL
Gnuplot
Go
hansl
Haskell
HTML
IDL
[empty]IDL
[CORBA]IDL
inform
Java
[empty]Java
[AspectJ]Java
JVMIS
ksh
Lingo
Lisp
[empty]Lisp
[Auto]Lisp
LLVM
Logo
Lua
[5.0]Lua
[5.1]Lua
[5.2]Lua
[5.3]Lua
make
[empty]make
[gnu]make
Mathematica
[1.0]Mathematica
[11.0]Mathematica
[3.0]Mathematica
[5.2]Mathematica
Matlab
Mercury
MetaPost
Miranda
Mizar
ML
Modula-2
MuPAD
NASTRAN
Oberon-2
OCL
[decorative]OCL
[OMG]OCL
Octave
OORexx
Oz
Pascal
[Borland6]Pascal
[Standard]Pascal
[XSC]Pascal
Perl
PHP
PL/I
Plasm
PostScript
POV
Prolog
Promela
PSTricks
Python
R
Reduce
Rexx
[empty]Rexx
[VM/XA]Rexx
RSL
Ruby
S
[empty]S
[PLUS]S
SAS
Scala
Scilab
sh
SHELXL
Simula
[67]Simula
[CII]Simula
[DEC]Simula
[IBM]Simula
SPARQL
SQL
Swift
tcl
[empty]tcl
[tk]tcl
TeX
[AlLaTeX]TeX
[common]TeX
[LaTeX]TeX
[plain]TeX
[primitive]TeX
VBScript
Verilog
VHDL
[empty]VHDL
[AMS]VHDL
VRML
[97]VRML
XML
XSLT
#endkeyvals

\lstset{keyvals}
\lstinline|%<code%>|
\lstinline[%<options%>]|%<code%>|
\lstinline[options%keyvals]{verbatimSymbol}#S
\begin{lstlisting}#V
\begin{lstlisting}[options%keyvals]#V
\end{lstlisting}
\lstinputlisting{file}
\lstinputlisting[options%keyvals]{file}

### keyvals for both \lstset and individual listings
#keyvals:\lstset,\lstinline,\begin{lstlisting},\lstinputlisting,\lstMakeShortInline
inputpath=%<path%>
aboveskip=##L
belowskip=##L
lineskip=##L
boxpos=#b,c,t
print#true,false
showlines#true,false
emptylines=%<number%>
emptylines=*%<number%>
gobble=%<number%>
style=%<style name%>
language=%<language%>
language=[%<dialect%>]%<language%>
alsolanguage=%<language%>
alsolanguage=[%<dialect%>]%<language%>
defaultdialect=[%<dialect%>]%<language%>
printpod#true,false
usekeywordsintag#true,false
tagstyle=%<style%>
markfirstintag=%<style%>
makemacrouse#true,false
basicstyle=%<style%>
identifierstyle=%<style%>
commentstyle=%<style%>
stringstyle=%<style%>
keywordstyle=%<style%>
keywordstyle=[%<number%>]%<style%>
keywordstyle=[%<number%>]*%<style%>
ndkeywordstyle=%<style%>
classoffset=%<number%>
texcsstyle=%<style%>
texcsstyle=[%<class number%>]%<style%>
texcsstyle=*[%<class number%>]%<style%>
directivestyle=%<style%>
emph={%<identifier list%>}
emph=[%<number%>]{%<identifier list%>}
moreemph={%<identifier list%>}
moreemph=[%<number%>]{%<identifier list%>}
deleteemph={%<identifier list%>}
deleteemph=[%<number%>]{%<identifier list%>}
emphstyle={%<style%>}
emphstyle=[%<number%>]{%<style%>}
delim=
moredelim=
deletedelim=
extendedchars#true,false
inputencoding=%<encoding%>
upquote#true,false
tabsize=%<number%>
showtabs#true,false
tab=%<tokens%>
showspaces#true,false
showstringspaces#true,false
formfeed=%<tokens%>
numbers=#none,left,right
stepnumber=%<number%>
numberfirstline#true,false
numberstyle=%<style%>
numbersep=##L
numberblanklines#true,false
firstnumber=
name=%<name%>
title=%<title text%>
caption={%<caption text%>}
caption={[%<short%>]%<caption text%>}
label=##l
nolol#true,false
numberbychapter#true,false
captionpos=%<subset of tb%>
abovecaptionskip=##L
belowcaptionskip=##L
linewidth=##L
xleftmargin=##L
xrightmargin=##L
resetmargins#true,false
breaklines#true,false
breakatwhitespace#true,false
prebreak=%<tokens%>
postbreak=%<tokens%>
breakindent=##L
breakautoindent#true,false
frame=
frameround=
framesep=##L
rulesep=##L
framerule=##L
framexleftmargin=##L
framexrightmargin=##L
framextopmargin=##L
framexbottommargin=##L
backgroundcolor=#%color
rulecolor=#%color
fillcolor=#%color
rulesepcolor=#%color
frameshape={%<top shape%>}{%<left shape%>}{%<right shape%>}{%<bottom shape%>}
index=
moreindex=
deleteindex=
indexstyle=
columns=
flexiblecolumns#true,false
keepspaces#true,false
basewidth=##L
fontadjust#true,false
texcl#true,false
mathescape#true,false
escapechar=%<character%>
escapeinside=
escapebegin=%<tokens%>
escapeend=%<tokens%>
fancyvrb#true,false
fvcmdparams=
morefvcmdparams=
literate=
rangebeginprefix=
rangebeginsuffix=
rangeendprefix=
rangeendsuffix=
rangeprefix=
rangesuffix=
includerangemarker#true,false
multicols=%<number%>
#endkeyvals

### keyvals for individual listings only
#keyvals:\lstinline,\begin{lstlisting},\lstinputlisting,\lstMakeShortInline
float
float=%<subset of tbph%>
float=*%<subset of tbph%>
floatplacement=
firstline=%<number%>
lastline=%<number%>
linerange={%<first1-last1,first2-last2,...%>}
consecutivenumbers#true,false
#endkeyvals

\lstdefinestyle{style name}{keyvals}#*
\thelstnumber#*
\lstlistoflistings
\lstlistlistingname#*
\lstlistingname#*
\lstlistingnamestyle#*
\thelstlisting#*
\lstname#*
\lstindexmacro{arg}#*

\lstnewenvironment{envname}[args][default]{starting code}{ending code}#*N
\lstnewenvironment{envname}[args]{starting code}{ending code}#*N
\lstnewenvironment{envname}{starting code}{ending code}#*N

\lstMakeShortInline[%<options%>]%<<character>%>#*
\lstDeleteShortInline%<<character>%>#*

\lstdefinelanguage{language name}{keyvals}#*
\lstalias{alias}{language}#*

#keyvals:\lstdefinelanguage,\lstset,\lstinputlisting
keywordsprefix=%<prefix%>
keywords={%<list of keywords%>}
keywords=[%<number%>]{%<list of keywords%>}
morekeywords={%<list of keywords%>}
morekeywords=[%<number%>]{%<list of keywords%>}
deletekeywords={%<list of keywords%>}
deletekeywords=[%<number%>]{%<list of keywords%>}
ndkeywords={%<list of keywords%>}
moreendkeywords={%<list of keywords%>}
deleteendkeywords={%<list of keywords%>}
texcs=
moretexcs=
deletetxcs=
directives=
moredirectives=
deletedirectives=
sensitive#true,false
alsoletter={%<character sequence%>}
alsodigit={%<character sequence%>}
alsoother={%<character sequence%>}
otherkeywords={%<keywords%>}
tag=
string=
morestring=
deletestring=
comment=
morecomment=
deletecomment=
keywordcomment={%<keywords%>}
morekeywordcomment={%<keywords%>}
deletekeywordcomment={%<keywords%>}
keywordcommentsemicolon={%<keywords%>}{%<keywords%>}{%<keywords%>}
podcomment#true,false
#endkeyvals

\lstaspectfiles#*
\lstlanguagefiles#*

#ifOption:procnames
#keyvals:\lstset,\lstinline,\begin{lstlisting},\lstinputlisting
procnamekeys={%<keywords%>}
moreprocnamekeys={%<keywords%>}
deleteprocnamekeys={%<keywords%>}
procnamestyle=%<style%>
indexprocnames#true,false
#endkeyvals
#endif

#ifOption:hyper
#keyvals:\lstset,\lstinline,\begin{lstlisting},\lstinputlisting
hyperref={%<identifiers%>}
morehyperref={%<identifiers%>}
deletehyperref={%<identifiers%>}
hyperanchor=
hyperlink=
#endkeyvals
#endif

#ifOption:lgrind
#keyvals:\lstset,\lstinline,\begin{lstlisting},\lstinputlisting
lgrindef=%<language%>
#endkeyvals
\lstlgrindeffile
#endif

#ifOption:formats
\lstdefineformat{name}{format}
#endif
