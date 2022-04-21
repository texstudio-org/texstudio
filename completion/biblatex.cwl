# biblatex package, available from ctan
# commands for biblatex users
# tbraun, 19.08.2009
# dbitouze, 14.02.2012
# Matthew Bertucci 07.02.2021 for v3.17

#include:pdftexcmds
#include:etoolbox
#include:keyval
#include:kvoptions
#include:logreq
#include:ifthen
#include:url

\bibname
\biblistname

## 3.1 Package Options ##
#keyvals:\usepackage/biblatex#c
backend=#bibtex,bibtex8,biber
style=%<file%>
bibstyle=%<file%>
citestyle=%<file%>
natbib#true,false
mcite#true,false
casechanger=#auto,latex2e,expl3
#endkeyvals

## 3.2 Global Customization ##
\ExecuteBibliographyOptions{options%keyvals}
\ExecuteBibliographyOptions[entrytype list]{options%keyvals}

#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c
sorting=#nty,nyt,nyvt,anyt,anyvt,ynt,ydnt,none,debug
sortcase#true,false
sortupper#true,false
sortlocale=
sortcites#true,false
sortsets#true,false
maxnames=%<integer%>
minnames=%<integer%>
maxbibnames=%<integer%>
minbibnames=%<integer%>
maxcitenames=%<integer%>
mincitenames=%<integer%>
maxsortnames=%<integer%>
minsortnames=%<integer%>
maxitems=%<integer%>
minitems=%<integer%>
autocite=#plain,inline,footnote,superscript
autopunct#true,false
language=#autobib,autocite,auto
clearlang#true,false
autolang=#none,hyphen,other,other*,langname
langhook=#captions,extras
block=#none,space,par,nbpar,ragged
locallabelwidth#true,false
notetype=#foot+end,footonly,endonly
hyperref=#true,false,auto,manual
backref#true,false
backrefstyle=#none,three,two,two+,three+,all+
backrefsetstyle=#=setonly,memonly,setormem,setandmem,memandset,setplusmem
backreffloats#true,false
indexing=#true,false,cite,bib
loadfiles#true,false
refsection=#none,part,chapter,chapter+,section,section+,subsection,subsection+
refsegment=#none,part,chapter,chapter+,section,section+,subsection,subsection+
citereset=#none,part,chapter,chapter+,section,section+,subsection,subsection+
abbreviate#true,false
date=#year,short,long,terse,comp,ymd,iso
labeldate=#year,short,long,terse,comp,ymd,iso
alldates=#year,short,long,terse,comp,iso
julian#true,false
gregorianstart=%<YYYY-MM-DD%>
datezeros#true,false
timezeros#true,false
timezones#true,false
seconds#true,false
dateabbrev#true,false
datecirca#true,false
dateuncertain#true,false
dateera=#astronomical,secular,christian
dateeraauto=%<integer%>
time=#12h,24h,24hcomp
labeltime=#12h,24h,24hcomp
alltimes=#12h,24h,24hcomp
dateusetime#true,false
labeldateusetime#true,false
alldatesusetime#true,false
defernumbers#true,false
punctfont#true,false
arxiv=#abs,ps,pdf,format
texencoding=
bibencoding=
safeinputenc#true,false
bibwarn#true,false
mincrossrefs=%<integer%>
minxrefs=%<integer%>
bibtexcaseprotection#true,false
isbn#true,false
url#true,false
doi#true,false
eprint#true,false
related#true,false
subentry#true,false
subentrycomp#true,false
dashed#true,false
mergedate=#false,minimum,basic,compact,maximum,true
ibidpage#true,false
citepages=#permit,suppress,omit,separate
strict#true,false
pagetracker=#true,false,page,spread
citecounter=#true,false,context
citetracker=#true,false,context,strict,constrict
ibidtracker=#true,false,context,strict,constrict
opcittracker=#true,false,context,strict,constrict
loccittracker=#true,false,context,strict,constrict
idemtracker=#true,false,context,strict,constrict
trackfloats#true,false
parentracker#true,false
maxparens=%<integer%>
terseinits#true,false
labelalpha#true,false
maxalphanames=%<integer%>
minalphanames=%<integer%>
labelnumber#true,false
noroman#true,false
labeltitle#true,false
labeltitleyear#true,false
labeldateparts#true,false
singletitle#true,false
uniquetitle#true,false
uniquebaretitle#true,false
uniquework#true,false
uniqueprimaryauthor#true,false
uniquename=#true,false,init,full,allinit,allfull,mininit,minfull
uniquelist=#true,false,minyear
nohashothers#true,false
nosortothers#true,false
useauthor#true,false
useeditor#true,false
usetranslator#true,false
useprefix#true,false
indexing=#true,false,cite,bib
skipbib#true,false
skipbiblist#true,false
skiplab#true,false
dataonly#true,false
#endkeyvals

## 3.7 Data Annotations ##
\iffieldannotation{annotation}{true}{false}#*
\iffieldannotation[field]{annotation}{true}{false}#*
\iffieldannotation[field][annotation name]{annotation}{true}{false}#*
\ifitemannotation{annotation}{true}{false}#*
\ifitemannotation[field]{annotation}{true}{false}#*
\ifitemannotation[field][annotation name]{annotation}{true}{false}#*
\ifitemannotation[field][annotation name][item]{annotation}{true}{false}#*
\ifpartannotation{part}{annotation}{true}{false}#*
\ifpartannotation[field]{part}{annotation}{true}{false}#*
\ifpartannotation[field][annotation name]{part}{annotation}{true}{false}#*
\ifpartannotation[field][annotation name][item]{part}{annotation}{true}{false}#*
\ifdateannotation{datetype}{annotation}{true}{false}#*
\ifdateannotation[annotation name]{datetype}{annotation}{true}{false}#*
\hasfieldannotation{true}{false}#*
\hasfieldannotation[field]{true}{false}#*
\hasfieldannotation[field][annotation name]{true}{false}#*
\hasitemannotation{true}{false}#*
\hasitemannotation[field]{true}{false}#*
\hasitemannotation[field][annotation name]{true}{false}#*
\hasitemannotation[field][annotation name][item]{true}{false}#*
\haspartannotation{part}{true}{false}#*
\haspartannotation[field]{part}{true}{false}#*
\haspartannotation[field][annotation name]{part}{true}{false}#*
\haspartannotation[field][annotation name][item]{part}{true}{false}#*
\hasdateannotation{datetype}{true}{false}#*
\hasdateannotation[annotation name]{datetype}{true}{false}#*

\getfieldannotation#*
\getfieldannotation[field]#*
\getfieldannotation[field][annotation name]#*
\getitemannotation#*
\getitemannotation[field]#*
\getitemannotation[field][annotation name]#*
\getitemannotation[field][annotation name][item]#*
\getpartannotation{part}#*
\getpartannotation[field]{part}#*
\getitemannotation[field][annotation name]{part}#*
\getitemannotation[field][annotation name][item]{part}#*
\getdateannotation{datetype}#*
\getdateannotation[annotation name]{datetype}#*

## 3.8 Bibliography Commands ##
\addbibresource{bibliographic resource}#b
\addbibresource[options%keyvals]{bibliographic resource}#b
\addglobalbib{bibliographic resource}#b
\addglobalbib[options%keyvals]{bibliographic resource}#b
\addsectionbib{bibliographic resource}#b
\addsectionbib[options%keyvals]{bibliographic resource}#b

#keyvals:\addbibresource,\addglobalbib,\addsectionbib
bibencoding=
label=##l
location=#local,remote
type=#file
datatype=#bibtex,biblatexml
glob#true,false
#endkeyvals

\bibliography{bib files}

\printbibliography
\printbibliography[options%keyvals]

#keyvals:\printbibliography
env=%<name%>
heading=%<name%>
title=%<text%>
label=##l
block=#none,space,par,nbpar,ragged
prenote=%<name%>
postnote=%<name%>
section=%<integer%>
segment=%<integer%>
type=%<entrytype%>
nottype=%<entrytype%>
subtype=%<subtype%>
notsubtype=%<subtype%>
keyword=%<keyword%>
notkeyword=%<keyword%>
category=%<category%>
notcategory=%<category%>
filter=%<name%>
check=%<name%>
resetnumbers=
omitnumbers#true,false
locallabelwidth#true,false
#endkeyvals

\bibbysection
\bibbysection[options%keyvals]
\bibbysegment
\bibbysegment[options%keyvals]
\bibbycategory
\bibbycategory[options%keyvals]

#keyvals:\bibbysection,\bibbysegment,\bibbycategory
env=%<name%>
heading=%<name%>
prenote=%<name%>
postnote=%<name%>
#endkeyvals

\printbibheading
\printbibheading[options%keyvals]

#keyvals:\printbibheading
heading=%<name%>
title=%<text%>
label=##l
#endkeyvals

\DeclarePrintbibliographyDefaults{options%keyvals}

#keyvals:\DeclarePrintbibliographyDefaults
env=%<name%>
heading=%<name%>
title=%<text%>
prenote=%<name%>
postnote=%<name%>
filter=%<name%>
#endkeyvals

\printbiblist{biblist}
\printbiblist[options%keyvals]{biblist}
\printshorthands
\printshorthands[options%keyvals]

#keyvals:\printbiblist,\printshorthands
env=%<name%>
heading=%<name%>
title=%<text%>
label=##l
block=#none,space,par,nbpar,ragged
prenote=%<name%>
postnote=%<name%>
section=%<integer%>
segment=%<integer%>
type=%<entrytype%>
nottype=%<entrytype%>
subtype=%<subtype%>
notsubtype=%<subtype%>
keyword=%<keyword%>
notkeyword=%<keyword%>
category=%<category%>
notcategory=%<category%>
filter=%<name%>
check=%<name%>
locallabelwidth#true,false
driver=
biblistfilter=
#endkeyvals

\begin{refsection}
\begin{refsection}[bib files]
\end{refsection}
\newrefsection
\newrefsection[bib files]
\endrefsection#*
\begin{refsegment}
\end{refsegment}
\newrefsegment
\endrefsegment#*
\therefsection#*
\therefsegment#*

\DeclareBibliographyCategory{category}
\addtocategory{category}{bibid}

\defbibenvironment{envname}{begincode}{endcode}{itemcode}
\defbibheading{name}{code}
\defbibheading{name}[title%text]{code}
\defbibnote{name}{text}
\defbibfilter{name}{expression}
\defbibcheck{name}{code}
\skipentry#*

\segment{integer}#*
\type{type}#*
\subtype{subtype}#*
\keyword{keyword}#*
\category{category}#*

\DeclareRefcontext{name}{options%keyvals}
\begin{refcontext}{name}
\begin{refcontext}[options%keyvals]{name}
\end{refcontext}
\newrefcontext{name}
\newrefcontext[options%keyvals]{name}
\endrefcontext#*
\assignrefcontextkeyws[options%keyvals]{keyword1,keyword2,...}#*
\assignrefcontextkeyws*[options%keyvals]{keyword1,keyword2,...}#*
\assignrefcontextcats[options%keyvals]{category1,category2,...}#*
\assignrefcontextcats*[options%keyvals]{category1,category2,...}#*
\assignrefcontextentries[options%keyvals]{entrykey1,entrykey2,...}#*
\assignrefcontextentries*[options%keyvals]{entrykey1,entrykey2,...}#*

#keyvals:\DeclareRefcontext,\begin{refcontext},\newrefcontext,\assignrefcontextkeyws,\assignrefcontextkeyws*,\assignrefcontextcats,\assignrefcontextcats*,\assignrefcontextentries,\assignrefcontextentries*
sorting=%<name%>
sortingnamekeytemplatename=%<name%>
uniquenametemplatename=%<name%>
labelalphanametemplatename=%<name%>
nametemplates=%<name%>
labelprefix=%<string%>
#endkeyvals

#keyvals:\assignrefcontextkeyws,\assignrefcontextkeyws*,\assignrefcontextcats,\assignrefcontextcats*,\assignrefcontextentries,\assignrefcontextentries*
name=%<refcontextname%>
#endkeyvals

\defbibentryset{bibid}{key1,key2,...}

## 3.9 Citation Commands ##
\cite[prenote][postnote]{bibid}#C
\cite[postnote]{bibid}#C
\cite{bibid}#C
\Cite[prenote][postnote]{bibid}#C
\Cite[postnote]{bibid}#C
\Cite{bibid}#C

\parencite[prenote][postnote]{bibid}#C
\parencite[postnote]{bibid}#C
\parencite{bibid}#C
\Parencite[prenote][postnote]{bibid}#C
\Parencite[postnote]{bibid}#C
\Parencite{bibid}#C

\footcite[prenote][postnote]{bibid}#C
\footcite[postnote]{bibid}#C
\footcite{bibid}#C
\footcitetext[prenote][postnote]{bibid}#C
\footcitetext[postnote]{bibid}#C
\footcitetext{bibid}#C

\textcite[prenote][postnote]{bibid}#C
\textcite[postnote]{bibid}#C
\textcite{bibid}#C
\Textcite[prenote][postnote]{bibid}#C
\Textcite[postnote]{bibid}#C
\Textcite{bibid}#C

\smartcite[prenote][postnote]{bibid}#C
\smartcite[postnote]{bibid}#C
\smartcite{bibid}#C
\Smartcite[prenote][postnote]{bibid}#C
\Smartcite[postnote]{bibid}#C
\Smartcite{bibid}#C

\cite*[prenote][postnote]{bibid}#C
\cite*[postnote]{bibid}#C
\cite*{bibid}#C

\parencite*[prenote][postnote]{bibid}#C
\parencite*[postnote]{bibid}#C
\parencite*{bibid}#C

\supercite{bibid}#C

\cites{bibid}{bibid}#C
\cites(pre){bibid}{bibid}#*C
\cites(pre)(post){bibid}{bibid}#C
\cites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\cites[pre]{bibid}[pre]{bibid}#*C
\cites[pre][post]{bibid}[pre][post]{bibid}#*C
\cites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\Cites{bibid}{bibid}#C
\Cites(pre){bibid}{bibid}#*C
\Cites(pre)(post){bibid}{bibid}#C
\Cites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\Cites[pre]{bibid}[pre]{bibid}#*C
\Cites[pre][post]{bibid}[pre][post]{bibid}#*C
\Cites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\parencites{bibid}{bibid}#C
\parencites(pre){bibid}{bibid}#*C
\parencites(pre)(post){bibid}{bibid}#C
\parencites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\parencites[pre]{bibid}[pre]{bibid}#*C
\parencites[pre][post]{bibid}[pre][post]{bibid}#*C
\parencites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\Parencites{bibid}{bibid}#C
\Parencites(pre){bibid}{bibid}#*C
\Parencites(pre)(post){bibid}{bibid}#C
\Parencites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\Parencites[pre]{bibid}[pre]{bibid}#*C
\Parencites[pre][post]{bibid}[pre][post]{bibid}#*C
\Parencites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\footcites{bibid}{bibid}#C
\footcites(pre){bibid}{bibid}#*C
\footcites(pre)(post){bibid}{bibid}#C
\footcites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\footcites[pre]{bibid}[pre]{bibid}#*C
\footcites[pre][post]{bibid}[pre][post]{bibid}#*C
\footcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\footcitetexts{bibid}{bibid}#C
\footcitetexts(post){bibid}{bibid}#*C
\footcitetexts(pre)(post){bibid}{bibid}#C
\footcitetexts(pre)(post)[post]{bibid}[post]{bibid}#*C
\footcitetexts[post]{bibid}[post]{bibid}#*C
\footcitetexts[pre][post]{bibid}[pre][post]{bibid}#*C
\footcitetexts(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\smartcites{bibid}{bibid}#C
\smartcites(pre){bibid}{bibid}#*C
\smartcites(pre)(post){bibid}{bibid}#C
\smartcites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\smartcites[pre]{bibid}[pre]{bibid}#*C
\smartcites[pre][post]{bibid}[pre][post]{bibid}#*C
\smartcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\Smartcites{bibid}{bibid}#C
\Smartcites(pre){bibid}{bibid}#*C
\Smartcites(pre)(post){bibid}{bibid}#C
\Smartcites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\Smartcites[pre]{bibid}[pre]{bibid}#*C
\Smartcites[pre][post]{bibid}[pre][post]{bibid}#*C
\Smartcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\textcites{bibid}{bibid}#C
\textcites(pre){bibid}{bibid}#*C
\textcites(pre)(post){bibid}{bibid}#C
\textcites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\textcites[pre]{bibid}[pre]{bibid}#*C
\textcites[pre][post]{bibid}[pre][post]{bibid}#*C
\textcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\Textcites{bibid}{bibid}#C
\Textcites(pre){bibid}{bibid}#*C
\Textcites(pre)(post){bibid}{bibid}#C
\Textcites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\Textcites[pre]{bibid}[pre]{bibid}#*C
\Textcites[pre][post]{bibid}[pre][post]{bibid}#*C
\Textcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\supercites{bibid}{bibid}#C
\supercites(pre){bibid}{bibid}#*C
\supercites(pre)(post){bibid}{bibid}#C
\supercites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\supercites[pre]{bibid}[pre]{bibid}#*C
\supercites[pre][post]{bibid}[pre][post]{bibid}#*C
\supercites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\autocite[prenote][postnote]{bibid}#C
\autocite[postnote]{bibid}#C
\autocite{bibid}#C
\Autocite[prenote][postnote]{bibid}#C
\Autocite[postnote]{bibid}#C
\Autocite{bibid}#C
\autocite*[prenote][postnote]{bibid}#C
\autocite*[postnote]{bibid}#C
\autocite*{bibid}#C
\Autocite*[prenote][postnote]{bibid}#C
\Autocite*[postnote]{bibid}#C
\Autocite*{bibid}#C

\autocites{bibid}{bibid}#C
\autocites(pre){bibid}{bibid}#*C
\autocites(pre)(post){bibid}{bibid}#C
\autocites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\autocites[pre]{bibid}[pre]{bibid}#*C
\autocites[pre][post]{bibid}[pre][post]{bibid}#*C
\autocites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\Autocites{bibid}{bibid}#C
\Autocites(pre){bibid}{bibid}#*C
\Autocites(pre)(post){bibid}{bibid}#C
\Autocites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\Autocites[pre]{bibid}[pre]{bibid}#*C
\Autocites[pre][post]{bibid}[pre][post]{bibid}#*C
\Autocites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\citeauthor[prenote][postnote]{bibid}#C
\citeauthor[postnote]{bibid}#C
\citeauthor{bibid}#C
\Citeauthor[prenote][postnote]{bibid}#C
\Citeauthor[postnote]{bibid}#C
\Citeauthor{bibid}#C
\citeauthor*[prenote][postnote]{bibid}#C
\citeauthor*[postnote]{bibid}#C
\citeauthor*{bibid}#C
\Citeauthor*[prenote][postnote]{bibid}#C
\Citeauthor*[postnote]{bibid}#C
\Citeauthor*{bibid}#C

\citetitle[prenote][postnote]{bibid}#C
\citetitle[postnote]{bibid}#C
\citetitle{bibid}#C
\citetitle*[prenote][postnote]{bibid}#C
\citetitle*[postnote]{bibid}#C
\citetitle*{bibid}#C

\citeyear[prenote][postnote]{bibid}#C
\citeyear[postnote]{bibid}#C
\citeyear{bibid}#C
\citeyear*[prenote][postnote]{bibid}#C
\citeyear*[postnote]{bibid}#C
\citeyear*{bibid}#C

\citedate[prenote][postnote]{bibid}#C
\citedate[postnote]{bibid}#C
\citedate{bibid}#C
\citedate*[prenote][postnote]{bibid}#C
\citedate*[postnote]{bibid}#C
\citedate*{bibid}#C

\citeurl[prenote][postnote]{bibid}#C
\citeurl[postnote]{bibid}#C
\citeurl{bibid}#C

\parentext{text}#*
\brackettext{text}#*

\nocite{bibid}#C

\fullcite[prenote][postnote]{bibid}#C
\fullcite[postnote]{bibid}#C
\fullcite{bibid}#C

\footfullcite[prenote][postnote]{bibid}#C
\footfullcite[postnote]{bibid}#C
\footfullcite{bibid}#C

\volcite{volume}{bibid}#C
\volcite[prenote]{volume}{bibid}#C
\volcite{volume}[pages]{bibid}#C
\volcite[prenote]{volume}[pages]{bibid}#C
\Volcite{volume}{bibid}#C
\Volcite[prenote]{volume}{bibid}#C
\Volcite{volume}[pages]{bibid}#C
\Volcite[prenote]{volume}[pages]{bibid}#C

\volcites{volume}{bibid}{volume}{bibid}#C
\volcites(pre){volume}{bibid}{volume}{bibid}#*C
\volcites(pre)(post){volume}{bibid}{volume}{bibid}#C
\volcites(pre)(post)[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\volcites[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\volcites[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#*C
\volcites(pre)(post)[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#C

\Volcites{volume}{bibid}{volume}{bibid}#C
\Volcites(pre){volume}{bibid}{volume}{bibid}#*C
\Volcites(pre)(post){volume}{bibid}{volume}{bibid}#C
\Volcites(pre)(post)[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\Volcites[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\Volcites[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#*C
\Volcites(pre)(post)[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#C

\pvolcite{volume}{bibid}#C
\pvolcite[prenote]{volume}{bibid}#C
\pvolcite{volume}[pages]{bibid}#C
\pvolcite[prenote]{volume}[pages]{bibid}#C
\Pvolcite{volume}{bibid}#C
\Pvolcite[prenote]{volume}{bibid}#C
\Pvolcite{volume}[pages]{bibid}#C
\Pvolcite[prenote]{volume}[pages]{bibid}#C

\pvolcites{volume}{bibid}{volume}{bibid}#C
\pvolcites(pre){volume}{bibid}{volume}{bibid}#*C
\pvolcites(pre)(post){volume}{bibid}{volume}{bibid}#C
\pvolcites(pre)(post)[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\pvolcites[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\pvolcites[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#*C
\pvolcites(pre)(post)[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#C

\Pvolcites{volume}{bibid}{volume}{bibid}#C
\Pvolcites(pre){volume}{bibid}{volume}{bibid}#*C
\Pvolcites(pre)(post){volume}{bibid}{volume}{bibid}#C
\Pvolcites(pre)(post)[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\Pvolcites[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\Pvolcites[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#*C
\Pvolcites(pre)(post)[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#C

\fvolcite{volume}{bibid}#C
\fvolcite[prenote]{volume}{bibid}#C
\fvolcite{volume}[pages]{bibid}#C
\fvolcite[prenote]{volume}[pages]{bibid}#C
\Fvolcite{volume}{bibid}#C
\Fvolcite[prenote]{volume}{bibid}#C
\Fvolcite{volume}[pages]{bibid}#C
\Fvolcite[prenote]{volume}[pages]{bibid}#C

\fvolcites{volume}{bibid}{volume}{bibid}#C
\fvolcites(pre){volume}{bibid}{volume}{bibid}#*C
\fvolcites(pre)(post){volume}{bibid}{volume}{bibid}#C
\fvolcites(pre)(post)[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\fvolcites[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\fvolcites[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#*C
\fvolcites(pre)(post)[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#C

\Fvolcites{volume}{bibid}{volume}{bibid}#C
\Fvolcites(pre){volume}{bibid}{volume}{bibid}#*C
\Fvolcites(pre)(post){volume}{bibid}{volume}{bibid}#C
\Fvolcites(pre)(post)[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\Fvolcites[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\Fvolcites[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#*C
\Fvolcites(pre)(post)[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#C

\svolcite{volume}{bibid}#C
\svolcite[prenote]{volume}{bibid}#C
\svolcite{volume}[pages]{bibid}#C
\svolcite[prenote]{volume}[pages]{bibid}#C
\Svolcite{volume}{bibid}#C
\Svolcite[prenote]{volume}{bibid}#C
\Svolcite{volume}[pages]{bibid}#C
\Svolcite[prenote]{volume}[pages]{bibid}#C

\svolcites{volume}{bibid}{volume}{bibid}#C
\svolcites(pre){volume}{bibid}{volume}{bibid}#*C
\svolcites(pre)(post){volume}{bibid}{volume}{bibid}#C
\svolcites(pre)(post)[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\svolcites[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\svolcites[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#*C
\svolcites(pre)(post)[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#C

\Svolcites{volume}{bibid}{volume}{bibid}#C
\Svolcites(pre){volume}{bibid}{volume}{bibid}#*C
\Svolcites(pre)(post){volume}{bibid}{volume}{bibid}#C
\Svolcites(pre)(post)[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\Svolcites[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\Svolcites[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#*C
\Svolcites(pre)(post)[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#C

\tvolcite{volume}{bibid}#C
\tvolcite[prenote]{volume}{bibid}#C
\tvolcite{volume}[pages]{bibid}#C
\tvolcite[prenote]{volume}[pages]{bibid}#C
\Tvolcite{volume}{bibid}#C
\Tvolcite[prenote]{volume}{bibid}#C
\Tvolcite{volume}[pages]{bibid}#C
\Tvolcite[prenote]{volume}[pages]{bibid}#C

\tvolcites{volume}{bibid}{volume}{bibid}#C
\tvolcites(pre){volume}{bibid}{volume}{bibid}#*C
\tvolcites(pre)(post){volume}{bibid}{volume}{bibid}#C
\tvolcites(pre)(post)[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\tvolcites[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\tvolcites[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#*C
\tvolcites(pre)(post)[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#C

\Tvolcites{volume}{bibid}{volume}{bibid}#C
\Tvolcites(pre){volume}{bibid}{volume}{bibid}#*C
\Tvolcites(pre)(post){volume}{bibid}{volume}{bibid}#C
\Tvolcites(pre)(post)[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\Tvolcites[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\Tvolcites[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#*C
\Tvolcites(pre)(post)[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#C

\avolcite{volume}{bibid}#C
\avolcite[prenote]{volume}{bibid}#C
\avolcite{volume}[pages]{bibid}#C
\avolcite[prenote]{volume}[pages]{bibid}#C
\Avolcite{volume}{bibid}#C
\Avolcite[prenote]{volume}{bibid}#C
\Avolcite{volume}[pages]{bibid}#C
\Avolcite[prenote]{volume}[pages]{bibid}#C

\avolcites{volume}{bibid}{volume}{bibid}#C
\avolcites(pre){volume}{bibid}{volume}{bibid}#*C
\avolcites(pre)(post){volume}{bibid}{volume}{bibid}#C
\avolcites(pre)(post)[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\avolcites[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\avolcites[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#*C
\avolcites(pre)(post)[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#C

\Avolcites{volume}{bibid}{volume}{bibid}#C
\Avolcites(pre){volume}{bibid}{volume}{bibid}#*C
\Avolcites(pre)(post){volume}{bibid}{volume}{bibid}#C
\Avolcites(pre)(post)[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\Avolcites[pre]{volume}{bibid}[pre]{volume}{bibid}#*C
\Avolcites[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#*C
\Avolcites(pre)(post)[pre][post]{volume}{bibid}[pre][post]{volume}{bibid}#C

\notecite[prenote][postnote]{bibid}#C
\notecite[postnote]{bibid}#C
\notecite{bibid}#C
\Notecite[prenote][postnote]{bibid}#C
\Notecite[postnote]{bibid}#C
\Notecite{bibid}#C

\pnotecite[prenote][postnote]{bibid}#C
\pnotecite[postnote]{bibid}#C
\pnotecite{bibid}#C
\Pnotecite[prenote][postnote]{bibid}#C
\Pnotecite[postnote]{bibid}#C
\Pnotecite{bibid}#C

\fnotecite[prenote][postnote]{bibid}#C
\fnotecite[postnote]{bibid}#C
\fnotecite{bibid}#C

\citename[prenote][postnote]{bibid}[format]{name list}#C
\citename[postnote]{bibid}[format]{name list}#C
\citename[postnote]{bibid}{name list}#C
\citename{bibid}[format]{name list}#C
\citename{bibid}{name list}#C

\citelist[prenote][postnote]{bibid}[format]{literal list}#C
\citelist[postnote]{bibid}[format]{literal list}#C
\citelist[postnote]{bibid}{literal list}#C
\citelist{bibid}[format]{literal list}#C
\citelist{bibid}{literal list}#C

\citefield[prenote][postnote]{bibid}[format]{field}#C
\citefield[postnote]{bibid}[format]{field}#C
\citefield[postnote]{bibid}{field}#C
\citefield{bibid}[format]{field}#C
\citefield{bibid}{field}#C

\citereset
\citereset*
\mancite

\pno
\ppno
\nopp
\psq
\psqq
\pnfmt{text}#*
\RN{integer}
\Rn{integer}

#ifOption:natbib
# from blx-natbib.def
\citet[prenote][postnote]{bibid}#C
\citet[postnote]{bibid}#C
\citet{bibid}#C
\citet*[prenote][postnote]{bibid}#C
\citet*[postnote]{bibid}#C
\citet*{bibid}#C
\citep[prenote][postnote]{bibid}#C
\citep[postnote]{bibid}#C
\citep{bibid}#C
\citep*[prenote][postnote]{bibid}#C
\citep*[postnote]{bibid}#C
\citep*{bibid}#C
\citealt[prenote][postnote]{bibid}#C
\citealt[postnote]{bibid}#C
\citealt{bibid}#C
\citealt*[prenote][postnote]{bibid}#C
\citealt*[postnote]{bibid}#C
\citealt*{bibid}#C
\citealp[prenote][postnote]{bibid}#C
\citealp[postnote]{bibid}#C
\citealp{bibid}#C
\citealp*[prenote][postnote]{bibid}#C
\citealp*[postnote]{bibid}#C
\citealp*{bibid}#C
\citeauthor[prenote][postnote]{bibid}#C
\citeauthor[postnote]{bibid}#C
\citeauthor{bibid}#C
\citeauthor*[prenote][postnote]{bibid}#C
\citeauthor*[postnote]{bibid}#C
\citeauthor*{bibid}#C
\citeyearpar[prenote][postnote]{bibid}#C
\citeyearpar[postnote]{bibid}#C
\citeyearpar{bibid}#C
\Citet[prenote][postnote]{bibid}#C
\Citet[postnote]{bibid}#C
\Citet{bibid}#C
\Citet*[prenote][postnote]{bibid}#C
\Citet*[postnote]{bibid}#C
\Citet*{bibid}#C
\Citep[prenote][postnote]{bibid}#C
\Citep[postnote]{bibid}#C
\Citep{bibid}#C
\Citep*[prenote][postnote]{bibid}#C
\Citep*[postnote]{bibid}#C
\Citep*{bibid}#C
\Citealt[prenote][postnote]{bibid}#C
\Citealt[postnote]{bibid}#C
\Citealt{bibid}#C
\Citealt*[prenote][postnote]{bibid}#C
\Citealt*[postnote]{bibid}#C
\Citealt*{bibid}#C
\Citealp[prenote][postnote]{bibid}#C
\Citealp[postnote]{bibid}#C
\Citealp{bibid}#C
\Citealp*[prenote][postnote]{bibid}#C
\Citealp*[postnote]{bibid}#C
\Citealp*{bibid}#C
\citefullauthor[prenote][postnote]{bibid}#C
\citefullauthor[postnote]{bibid}#C
\citefullauthor{bibid}#C
\Citefullauthor[prenote][postnote]{bibid}#C
\Citefullauthor[postnote]{bibid}#C
\Citefullauthor{bibid}#C
\citetext{text}
\defcitealias{bibid}{alias}
\citetalias{bibid}
\citepalias{bibid}
#endif
#ifOption:natbib=true
# from blx-natbib.def
\citet[prenote][postnote]{bibid}#C
\citet[postnote]{bibid}#C
\citet{bibid}#C
\citet*[prenote][postnote]{bibid}#C
\citet*[postnote]{bibid}#C
\citet*{bibid}#C
\citep[prenote][postnote]{bibid}#C
\citep[postnote]{bibid}#C
\citep{bibid}#C
\citep*[prenote][postnote]{bibid}#C
\citep*[postnote]{bibid}#C
\citep*{bibid}#C
\citealt[prenote][postnote]{bibid}#C
\citealt[postnote]{bibid}#C
\citealt{bibid}#C
\citealt*[prenote][postnote]{bibid}#C
\citealt*[postnote]{bibid}#C
\citealt*{bibid}#C
\citealp[prenote][postnote]{bibid}#C
\citealp[postnote]{bibid}#C
\citealp{bibid}#C
\citealp*[prenote][postnote]{bibid}#C
\citealp*[postnote]{bibid}#C
\citealp*{bibid}#C
\citeauthor[prenote][postnote]{bibid}#C
\citeauthor[postnote]{bibid}#C
\citeauthor{bibid}#C
\citeauthor*[prenote][postnote]{bibid}#C
\citeauthor*[postnote]{bibid}#C
\citeauthor*{bibid}#C
\citeyearpar[prenote][postnote]{bibid}#C
\citeyearpar[postnote]{bibid}#C
\citeyearpar{bibid}#C
\Citet[prenote][postnote]{bibid}#C
\Citet[postnote]{bibid}#C
\Citet{bibid}#C
\Citet*[prenote][postnote]{bibid}#C
\Citet*[postnote]{bibid}#C
\Citet*{bibid}#C
\Citep[prenote][postnote]{bibid}#C
\Citep[postnote]{bibid}#C
\Citep{bibid}#C
\Citep*[prenote][postnote]{bibid}#C
\Citep*[postnote]{bibid}#C
\Citep*{bibid}#C
\Citealt[prenote][postnote]{bibid}#C
\Citealt[postnote]{bibid}#C
\Citealt{bibid}#C
\Citealt*[prenote][postnote]{bibid}#C
\Citealt*[postnote]{bibid}#C
\Citealt*{bibid}#C
\Citealp[prenote][postnote]{bibid}#C
\Citealp[postnote]{bibid}#C
\Citealp{bibid}#C
\Citealp*[prenote][postnote]{bibid}#C
\Citealp*[postnote]{bibid}#C
\Citealp*{bibid}#C
\citefullauthor[prenote][postnote]{bibid}#C
\citefullauthor[postnote]{bibid}#C
\citefullauthor{bibid}#C
\Citefullauthor[prenote][postnote]{bibid}#C
\Citefullauthor[postnote]{bibid}#C
\Citefullauthor{bibid}#C
\citetext{text}
\defcitealias{bibid}{alias}
\citetalias{bibid}
\citepalias{bibid}
#endif

#ifOption:mcite
\mcite[prenote][postnote]{bibid}#C
\mcite[postnote]{bibid}#C
\mcite{bibid}#C
\Mcite[prenote][postnote]{bibid}#C
\Mcite[postnote]{bibid}#C
\Mcite{bibid}#C

\mparencite[prenote][postnote]{bibid}#C
\mparencite[postnote]{bibid}#C
\mparencite{bibid}#C
\Mparencite[prenote][postnote]{bibid}#C
\Mparencite[postnote]{bibid}#C
\Mparencite{bibid}#C

\mfootcite[prenote][postnote]{bibid}#C
\mfootcite[postnote]{bibid}#C
\mfootcite{bibid}#C
\mfootcitetext[prenote][postnote]{bibid}#C
\mfootcitetext[postnote]{bibid}#C
\mfootcitetext{bibid}#C

\mtextcite[prenote][postnote]{bibid}#C
\mtextcite[postnote]{bibid}#C
\mtextcite{bibid}#C
\Mtextcite[prenote][postnote]{bibid}#C
\Mtextcite[postnote]{bibid}#C
\Mtextcite{bibid}#C

\msupercite{bibid}#C

\mcite*[prenote][postnote]{bibid}#C
\mcite*[postnote]{bibid}#C
\mcite*{bibid}#C

\mparencite*[prenote][postnote]{bibid}#C
\mparencite*[postnote]{bibid}#C
\mparencite*{bibid}#C

\mautocite[prenote][postnote]{bibid}#C
\mautocite[postnote]{bibid}#C
\mautocite{bibid}#C
\Mautocite[prenote][postnote]{bibid}#C
\Mautocite[postnote]{bibid}#C
\Mautocite{bibid}#C
\mautocite*[prenote][postnote]{bibid}#C
\mautocite*[postnote]{bibid}#C
\mautocite*{bibid}#C
\Mautocite*[prenote][postnote]{bibid}#C
\Mautocite*[postnote]{bibid}#C
\Mautocite*{bibid}#C
#endif
#ifOption:mcite=true
\mcite[prenote][postnote]{bibid}#C
\mcite[postnote]{bibid}#C
\mcite{bibid}#C
\Mcite[prenote][postnote]{bibid}#C
\Mcite[postnote]{bibid}#C
\Mcite{bibid}#C

\mparencite[prenote][postnote]{bibid}#C
\mparencite[postnote]{bibid}#C
\mparencite{bibid}#C
\Mparencite[prenote][postnote]{bibid}#C
\Mparencite[postnote]{bibid}#C
\Mparencite{bibid}#C

\mfootcite[prenote][postnote]{bibid}#C
\mfootcite[postnote]{bibid}#C
\mfootcite{bibid}#C
\mfootcitetext[prenote][postnote]{bibid}#C
\mfootcitetext[postnote]{bibid}#C
\mfootcitetext{bibid}#C

\mtextcite[prenote][postnote]{bibid}#C
\mtextcite[postnote]{bibid}#C
\mtextcite{bibid}#C
\Mtextcite[prenote][postnote]{bibid}#C
\Mtextcite[postnote]{bibid}#C
\Mtextcite{bibid}#C

\msupercite{bibid}#C

\mcite*[prenote][postnote]{bibid}#C
\mcite*[postnote]{bibid}#C
\mcite*{bibid}#C

\mparencite*[prenote][postnote]{bibid}#C
\mparencite*[postnote]{bibid}#C
\mparencite*{bibid}#C

\mautocite[prenote][postnote]{bibid}#C
\mautocite[postnote]{bibid}#C
\mautocite{bibid}#C
\Mautocite[prenote][postnote]{bibid}#C
\Mautocite[postnote]{bibid}#C
\Mautocite{bibid}#C
\mautocite*[prenote][postnote]{bibid}#C
\mautocite*[postnote]{bibid}#C
\mautocite*{bibid}#C
\Mautocite*[prenote][postnote]{bibid}#C
\Mautocite*[postnote]{bibid}#C
\Mautocite*{bibid}#C
#endif

## 3.10 Localization Commands ##
\DefineBibliographyStrings{language}{definitions}
\DefineBibliographyExtras{language}{code}
\UndefineBibliographyExtras{language}{code}
\DefineHyphenationExceptions{language}{text}
\NewBibliographyString{bibid}#C

## 3.11 Entry Querying Commands ##
\ifentryseen{entrykey}{true}{false}#*
\ifentryinbib{entrykey}{true}{false}#*
\ifentrycategory{entrykey}category}{true}{false}#*
\ifentrykeyword{entrykey}{keyword}{true}{false}#*

## 3.12 Formatting Commands ##
\bibsetup#*
\bibfont#*
\citesetup#*
\newblockpunct#*
\newunitpunct#*
\finentrypunct#*
\entrysetpunct#*
\bibnamedelima#*
\bibnamedelimb#*
\bibnamedelimc#*
\bibnamedelimd#*
\bibnamedelimi#*
\bibinitperiod#*
\bibinitdelim#*
\bibinithyphendelim#*
\bibindexnamedelima#*
\bibindexnamedelimb#*
\bibindexnamedelimc#*
\bibindexnamedelimd#*
\bibindexnamedelimi#*
\bibindexinitperiod#*
\bibindexinitdelim#*
\bibindexinithyphendelim#*
\revsdnamepunct#*
\bibnamedash#*
\labelnamepunct#*
\subtitlepunct#*
\intitlepunct#*
\bibpagespunct#*
\bibpagerefpunct#*
\bibeidpunct#*
\multinamedelim#*
\finalnamedelim#*
\revsdnamedelim#*
\andothersdelim#*
\multilistdelim#*
\finallistdelim#*
\andmoredelim#*
\multicitedelim#*
\multiciterangedelim#*
\multicitesubentrydelim#*
\multicitesubentryrangedelim#*
\supercitedelim#*
\superciterangedelim#*
\supercitesubentrydelim#*
\supercitesubentryrangedelim#*
\compcitedelim#*
\textcitedelim#*
\nametitledelim#*
\nameyeardelim#*
\namelabeldelim#*
\nonameyeardelim#*
\authortypedelim#*
\editortypedelim#*
\translatortypedelim#*
\labelalphaothers#*
\sortalphaothers#*
\volcitedelim#*
\mkvolcitenote{volume}{pages}#*
\prenotedelim#*
\postnotedelim#*
\extpostnotedelim#*
\multiprenotedelim#*
\multipostnotedelim#*
\mkbibnamefamily{text}#*
\mkbibnamegiven{text}#*
\mkbibnameprefix{text}#*
\mkbibnamesuffix{text}#*
\mkbibcompletenamefamily#*
\mkbibcompletenamefamilygiven#*
\mkbibcompletenamegivenfamily#*
\mkbibcompletename#*
\datecircadelim#*
\dateeradelim#*
\dateuncertainprint#*
\enddateuncertainprint#*
\datecircaprint#*
\enddatecircaprint#*
\datecircaprintiso#*
\enddatecircaprintiso#*
\dateeraprint{yearfield}#*
\dateeraprintpre#*
\relatedpunct#*
\relateddelim#*
\begrelateddelim#*
\bibleftparen#*
\bibrightparen#*
\bibleftbracket#*
\bibrightbracket#*

\DeclareDelimFormat{name}{code}#*
\DeclareDelimFormat[context]{name}{code}#*
\DeclareDelimFormat*{name}{code}#*
\DeclareDelimFormat*[context]{name}{code}#*
\DeclareDelimAlias{alias}{delim}#*
\DeclareDelimAlias[alias context]{alias}[delim context]{delim}#*
\DeclareDelimAlias*[alias context]{alias}[delim context]{delim}#*
\printdelim{name}#*
\printdelim[context]{name}#*
\delimcontext{context}#*
\DeclareDelimcontextAlias{alias}{name}#*

\bibrangedash#*
\bibrangessep#*
\bibdatesep#*
\bibdaterangesep#*
\mkbibdatelong{year}{month}{day}#*
\mkbibdateshort{year}{month}{day}#*
\mkbibtimezone{timezone}#*
\bibdateuncertain#*
\bibdateeraprefix#*
\bibdateeraendprefix#*
\bibtimesep#*
\bibutctimezone#*
\bibtimezonesep#*
\bibtzminsep#*
\bibdatetimesep #*
\finalandcomma#*
\finalandsemicolon#*
\mkbibordinal{integer}#*
\mkbibmascord{integer}#*
\mkbibfemord{integer}#*
\mkbibneutord{integer}#*
\mkbibordedition{integer}#*
\mkbibordseries{integer}#*

\bibhang#*
\biblabelsep#*
\bibitemsep#*
\bibnamesep#*
\bibinitsep#*
\bibparsep#*
\biburlbigskip#*
\biburlnumskip#*
\biburlucskip#*
\biburllcskip#*

\bibellipsis#*
\noligature#*
\hyphenate#*
\hyphen#*
\nbhyphen#*
\nohyphenation#*
\textnohyphenation{text}#*
\mknumalph{integer}#*
\mkbibacro{text}#*
\autocap{character}#*

## 3.13 Language-specific Notes ##
# Spanish
\forceE#*
\forceY#*

## 3.15 Hints and Caveats ##
# koma-script classes
\ifkomabibtotoc{true}{false}#*
\ifkomabibtotocnumbered{true}{false}#*
# memoir class
\ifmemoirbibintoc{true}{false}#*

## 4.2 Bibliography Styles ##
\RequireBibliographyStyle{style}#*
\InitializeBibliographyStyle{code}#*
\DeclareBibliographyDriver{entrytype}{code}#*
\DeclareBibliographyAlias{alias}{entrytype}#*
\DeclareBibliographyOption{key%plain}{code}#*
\DeclareBibliographyOption[datatype]{key%plain}{code}#*
\DeclareBibliographyOption{key%plain}[value]{code}#*
\DeclareBibliographyOption[datatype]{key%plain}[value]{code}#*
\DeclareTypeOption{key%plain}{code}#*
\DeclareTypeOption[datatype]{key%plain}{code}#*
\DeclareTypeOption{key%plain}[value]{code}#*
\DeclareTypeOption[datatype]{key%plain}[value]{code}#*
\DeclareEntryOption{key%plain}{code}#*
\DeclareEntryOption[datatype]{key%plain}{code}#*
\DeclareEntryOption{key%plain}[value]{code}#*
\DeclareEntryOption[datatype]{key%plain}[value]{code}#*
\DeclareBiblatexOption{scope}{key%plain}{code}#*
\DeclareBiblatexOption{scope}[datatype]{key%plain}{code}#*
\DeclareBiblatexOption{scope}{key%plain}[value]{code}#*
\DeclareBiblatexOption{scope}[datatype]{key%plain}[value]{code}#*

## 4.3 Citation Styles ##
\RequireCitationStyle{style}#*
\InitializeCitationStyle{code}#*
\OnManualCitation{code}#*
\DeclareCiteCommand{cmd}{precode}{loopcode}{sepcode}{postcode}#*d
\DeclareCiteCommand{cmd}[wrapper]{precode}{loopcode}{sepcode}{postcode}#*d
\DeclareCiteCommand*{cmd}{precode}{loopcode}{sepcode}{postcode}#*d
\DeclareCiteCommand*{cmd}[wrapper]{precode}{loopcode}{sepcode}{postcode}#*d
\DeclareMultiCiteCommand{cmd}{cite}{delimiter}#*d
\DeclareMultiCiteCommand{cmd}[wrapper]{cite}{delimiter}#*d
\DeclareAutoCiteCommand{name}{cite}{multicite}#*
\DeclareAutoCiteCommand{name}[position%keyvals]{cite}{multicite}#*
#keyvals:\DeclareAutoCiteCommand
r
l
f
#endkeyvals
\DeclareCitePunctuationPosition{cmd}{position%keyvals}#*d
#keyvals:\DeclareCitePunctuationPosition
r
l
f
c
o
d
#endkeyvals

## 4.4 Data Interface ##
\DeprecateField{field}{message}#*
\DeprecateList{list}{message}#*
\DeprecateName{name}{message}#*
\DeprecateFieldWithReplacement{field}{replacement}#*
\DeprecateListWithReplacement{list}{replacement}#*
\DeprecateNameWithReplacement{name}{replacement}#*
\printfield{field}#*
\printfield[format]{field}#*
\printlist{literal list}#*
\printlist[format]{literal list}#*
\printlist[format][start-stop]{literal list}#*
\printnames{name list}#*
\printnames[format]{name list}#*
\printnames[format][start-stop]{name list}#*
\printtext{text}#*
\printtext[format]{text}#*
\printfile{file}#*
\printfile[format]{file}#*
\printdate#*
\printdateextra#*
\printlabeldate#*
\printlabeldateextra#*
\printorigdate#*
\printeventdate#*
\printurldate#*
\printtime#*
\printorigtime#*
\printeventtime#*
\printurltime#*
\indexfield{field}#*
\indexfield[format]{field}#*
\indexlist{literal list}#*
\indexlist[format]{literal list}#*
\indexlist[format][start-stop]{literal list}#*
\indexnames{name list}#*
\indexnames[format]{name list}#*
\indexnames[format][start-stop]{name list}#*
\entrydata{key%plain}{code}#*
\entrydata*{key%plain}{code}#*
\entryset{precode}{postcode}#*
\DeclareFieldInputHandler{field}{code}#*
\DeclareListInputHandler{list}{code}#*
\DeclareNameInputHandler{name}{code}#*

# Formatting Directives
\DeclareFieldFormat[entrytype, ...]{format}{code}#*
\DeclareFieldFormat*{format}{code}#*
\DeclareListFormat[entrytype, ...]{format}{code}#*
\DeclareListFormat*{format}{code}#*
\DeclareNameFormat[entrytype, ...]{format}{code}#*
\DeclareNameFormat*{format}{code}#*
\DeclareListWrapperFormat[entrytype, ...]{format}{code}#*
\DeclareListWrapperFormat*{format}{code}#*
\DeclareNameWrapperFormat[entrytype, ...]{format}{code}#*
\DeclareNameWrapperFormat*{format}{code}#*
\DeclareIndexFieldFormat[entrytype, ...]{format}{code}#*
\DeclareIndexFieldFormat*{format}{code}#*
\DeclareIndexListFormat[entrytype, ...]{format}{code}#*
\DeclareIndexListFormat*{format}{code}#*
\DeclareIndexNameFormat[entrytype, ...]{format}{code}#*
\DeclareIndexNameFormat*{format}{code}#*
\DeclareFieldAlias[entry type]{alias}[format entry type]{format}#*
\DeclareFieldAlias{alias}{format}#*
\DeclareListAlias[entry type]{alias}[format entry type]{format}#*
\DeclareListAlias{alias}{format}#*
\DeclareNameAlias[entry type]{alias}[format entry type]{format}#*
\DeclareNameAlias{alias}{format}#*
\DeclareListWrapperAlias[entry type]{alias}[format entry type]{format}#*
\DeclareListWrapperAlias{alias}{format}#*
\DeclareNameWrapperAlias[entry type]{alias}[format entry type]{format}#*
\DeclareNameWrapperAlias{alias}{format}#*
\DeclareIndexFieldAlias[entry type]{alias}[format entry type]{format}#*
\DeclareIndexFieldAlias{alias}{format}#*
\DeclareIndexListAlias[entry type]{alias}[format entry type]{format}#*
\DeclareIndexListAlias{alias}{format}#*
\DeclareIndexNameAlias[entry type]{alias}[format entry type]{format}#*
\DeclareIndexNameAlias{alias}{format}#*
\DeprecateFieldFormatWithReplacement[entry type]{alias}[format entry type]{format}#*
\DeprecateFieldFormatWithReplacement{alias}{format}#*
\DeprecateListFormatWithReplacement[entry type]{alias}[format entry type]{format}#*
\DeprecateListFormatWithReplacement{alias}{format}#*
\DeprecateNameFormatWithReplacement[entry type]{alias}[format entry type]{format}#*
\DeprecateNameFormatWithReplacement{alias}{format}#*
\DeprecateListWrapperFormatWithReplacement[entry type]{alias}[format entry type]{format}#*
\DeprecateListWrapperFormatWithReplacement{alias}{format}#*
\DeprecateNameWrapperFormatWithReplacement[entry type]{alias}[format entry type]{format}#*
\DeprecateNameWrapperFormatWithReplacement{alias}{format}#*
\DeprecateIndexFieldFormatWithReplacement[entry type]{alias}[format entry type]{format}#*
\DeprecateIndexFieldFormatWithReplacement{alias}{format}#*
\DeprecateIndexListFormatWithReplacement[entry type]{alias}[format entry type]{format}#*
\DeprecateIndexListFormatWithReplacement{alias}{format}#*
\DeprecateIndexNameFormatWithReplacement[entry type]{alias}[format entry type]{format}#*
\DeprecateIndexNameFormatWithReplacement{alias}{format}#*

## 4.5 Customization ##
\DeclareDatafieldSet{name}{specification}#*
\member#*
\member[options%keyvals]#*
#keyvals:\member
fieldtype=
datatype=
field=
#endkeyvals
\DeclareSourcemap{specification}#*
\maps{elements}#*
\maps[options%keyvals]{elements}#*
#keyvals:\maps
datatype=#bibtex,biblatexml
overwrite#true,false
#endkeyvals
\map{restrictions,steps}#*
\map[options%keyvals]{restrictions,steps}#*
#keyvals:\map
overwrite#true,false
foreach=%<loopval%>
refsection=%<integer%>
#endkeyvals
\regexp{regexp}#*
\perdatasource{datasource}#*
\pertype{entrytype}#*
\pernottype{entrytype}#*
\step#*
\step[options%keyvals]#*
#keyvals:\step
typesource=%<entrytype%>
typetarget=%<entrytype%>
fieldsource=%<entryfield%>
notfield=%<entryfield%>
fieldtarget=%<entryfield%>
match=%<regexp%>
matchi=%<regexp%>
notmatch=%<regexp%>
notmatchi=%<regexp%>
replace=%<regexp%>
fieldset=%<entryfield%>
fieldvalue=%<string%>
entryclone=%<clonekey%>
entrynew=%<entrynewkey%>
entrynewtype=%<string%>
entrytarget=%<string%>
cited#true,false
nocited#true,false
citedornocited#true,false
allnocited#true,false
starnocited#true,false
entrynocite#true,false
entrynull#true,false
append#true,false
appendstrict#true,false
final#true,false
null#true,false
origfield#true,false
origfieldval#true,false
origentrytype#true,false
#endkeyvals
\DeclareStyleSourcemap{specification}#*
\DeclareDriverSourcemap{specification}#*
\DeclareDriverSourcemap[datatype=driver]{specification}#*
\DeclareDatamodelConstant{name}{constantdef}#*
\DeclareDatamodelConstant[options%keyvals]{name}{constantdef}#*
#keyvals:\DeclareDatamodelConstant
type=#string,list
#endkeyvals
\DeclareDatamodelEntrytypes{entrytypes}#*
\DeclareDatamodelEntrytypes[options%keyvals]{entrytypes}#*
#keyvals:\DeclareDatamodelEntrytypes
skipout#true,false
#endkeyvals
\DeclareDatamodelFields{fields}#*
\DeclareDatamodelFields[options%keyvals]{fields}#*
#keyvals:\DeclareDatamodelFields
type=%<field type%>
format=%<field format%>
datatype=%<field datatype%>
nullok#true,false
skipout#true,false
label#true,false
#endkeyvals
\DeclareDatamodelEntryfields{fields}#*
\DeclareDatamodelEntryfields[entrytypes]{fields}#*
\DeclareDatamodelConstraints{specification}#*
\DeclareDatamodelEntryfields[entrytypes]{specification}#*
\constraint{elements}#*
\constraint[options%keyvals]{elements}#*
#keyvals:\constraint
type=#data,mandatory,conditional
datatype=#integer,isbn,issn,ismn,datepart,pattern
rangemin=%<number%>
rangemax=%<number%>
pattern=
#endkeyvals
\constraintfieldsor{fields}#*
\constraintfieldsxor{fields}#*
\antecedent{fields}#*
\antecedent[options%keyvals]{fields}#*
\consequent{fields}#*
\consequent[options%keyvals]{fields}#*
#keyvals:\antecedent,\consequent
quantifier=#all,one,none
#endkeyvals
\constraintfield{field}#*
\ResetDatamodelEntrytypes#*
\ResetDatamodelFields#*
\ResetDatamodelEntryfields#*
\ResetDatamodelConstraints#*

\DeclareLabelalphaTemplate{specification}#*
\DeclareLabelalphaTemplate[entrytypes]{specification}#*
\labelelement{elements}#*
\field{field}#*
\field[options%keyvals]{field}#*
#keyvals:\field
final#true,false
lowercase#true,false
strwidth=%<integer%>
strside=#left,right
padside=#left,right
padchar=%<character%>
uppercase#true,false
varwidth#true,false
varwidthnorm#true,false
varwidthlist#true,false
strwidthmax=%<integer%>
strfixedcount=%<integer%>
ifnames=%<range%>
names=%<range%>
namessep=%<string%>
noalphaothers#true,false
#endkeyvals
\literal{characters}#*
\DeclareLabelalphaNameTemplate{specification}#*
\DeclareLabelalphaNameTemplate[name]{specification}#*
\namepart{namepart}#*
\namepart[options%keyvals]{namepart}#*
#keyvals:\namepart
use#true,false
pre#true,false
compound#true,false
strwidth=%<integer%>
strside=#left,right
inits#true,false
base#true,false
disambiguation=#none,init,initorfull,full
#endkeyvals
\DeclareNolabel{specification}#*
\nolabel{regexp}#*
\DeclareNolabelwidthcount{specification}#*
\nolabelwidthcount{regexp}#*

\DeclareSortingTemplate{name}{specification}#*
\DeclareSortingTemplate[options%keyvals]{name}{specification}#*
#keyvals:\DeclareSortingTemplate
locale=
#endkeyvals
\sort{elements}#*
\sort[options%keyvals]{elements}#*
#keyvals:\sort
locale=
direction=#ascending,descending
final#true,false
sortcase#true,false
sortupper#true,false
#endkeyvals
\citeorder#*
\DeclareSortingNamekeyTemplate{specification}#*
\DeclareSortingNamekeyTemplate[name]{specification}#*
\keypart{part}#*
\DeclareSortExclusion{entrytype list}{field list}#*
\DeclareSortInclusion{entrytype list}{field list}#*
\DeclarePresort{string}#*
\DeclarePresort[entrytype list]{string}#*
\DeclareSortTranslit{specification}#*
\DeclareSortTranslit[entrytype]{specification}#*
\translit{field}{from}{to}#*
\translit[lang ids]{field}{from}{to}#*

\DeclareBiblistFilter{name}{specification}#*
\filter{filter}#*
\filter[filterspec%keyvals]{filter}#*
#keyvals:\filter
type=
nottype=
subtype=
notsubtype=
keyword=
notkeyword=
field=
notfield=
#endkeyvals
\filteror{type}{filters}#*

\DeclareNoinit{specification}#*
\noinit{regexp}#*

\DeclareNosort{specification}#*
\nosort{field}{regexp}#*

\DeclareLabelname{specification}#*
\DeclareLabelname[entrytype list]{specification}#*
\DeclareLabeldate{specification}#*
\DeclareLabeldate[entrytype list]{specification}#*
\DeclareExtradate{specification}#*
\DeclareLabeltitle{specification}#*
\DeclareLabeltitle[entrytype list]{specification}#*

\DefaultInheritance{options%keyvals}#*
\DefaultInheritance[exceptions]{options%keyvals}#*
\except{source}{target}{options%keyvals}#*
#keyvals:\DefaultInheritance,\except
all#true,false
override#true,false
ignore=%<csv list of uniqueness options%>
#endkeyvals
\DeclareDataInheritance{source}{target}{rules}#*
\DeclareDataInheritance[options%keyvals]{source}{target}{rules}#*
#keyvals:\DeclareDataInheritance
ignore=%<csv list of uniqueness options%>
#endkeyvals
\inherit{source}{target}#*
\inherit[options%keyvals]{source}{target}#*
#keyvals:\inherit
override#true,false
#endkeyvals
\noinherit{source}#*
\ResetDataInheritance#*

## 4.6 Auxiliary Commands ##
\thefield{field}#*
\strfield{field}#*
\csfield{field}#*
\usefield{cmd}{field}#*
\thelist{literal list}#*
\strlist{literal list}#*
\thefirstlistitem{literal list}#*
\strfirstlistitem{literal list}#*
\usefirstlistitem{cmd}{literal list}#*
\thename{name list}#*
\strname{name list}#*
\savefield{field}{cmd}#*d
\savefield*{field}{cmd}#*d
\savelist{literal list}{cmd}#*d
\savelist*{literal list}{cmd}#*d
\savename{name list}{cmd}#*d
\savename*{name list}{cmd}#*d
\savefieldcs{field}{csname}#*
\savefieldcs*{field}{csname}#*
\savelistcs{literal list}{csname}#*
\savelistcs*{literal list}{csname}#*
\savenamecs{name list}{csname}#*
\savenamecs*{name list}{csname}#*
\restorefield{field}{cmd}#*
\restorelist{literal list}{cmd}#*
\restorename{name list}{cmd}#*
\clearfield{field}#*
\clearlist{literal list}#*
\clearname{name list}#*

\ifdatejulian{true}{false}#*
\ifdateera{era}{true}{false}#*
\ifdatecirca{true}{false}#*
\ifdateuncertain{true}{false}#*
\ifenddateuncertain{true}{false}#*
\ifdateunknown{true}{false}#*
\ifenddateunknown{true}{false}#*
\iflabeldateisdate{true}{false}#*
\ifdatehasyearonlyprecision{datetype}{true}{false}#*
\ifdatehastime{datetype}{true}{false}#*
\ifdateshavedifferentprecision{datetype1}{datetype2}{true}{false}#*
\ifdateyearsequal{datetype1}{datetype2}{true}{false}#*
\ifdatesequal{datetype1}{datetype2}{true}{false}#*
\ifdaterangesequal{datetype1}{datetype2}{true}{false}#*
\ifcaselang{true}{false}#*
\ifcaselang[language]{true}{false}#*
\ifsortingnamekeytemplatename{string}{true}{false}#*
\ifuniquenametemplatename{string}{true}{false}#*
\iflabelalphanametemplatename{string}{true}{false}#*
\iffieldundef{field}{true}{false}#*
\iflistundef{literal list}{true}{false}#*
\ifnameundef{name list}{true}{false}#*
\iffieldsequal{field1}{field2}{true}{false}#*
\iflistsequal{literal list1}{literal list2}{true}{false}#*
\ifnamesequal{name list1}{name list2}{true}{false}#*
\iffieldequals{field}{cmd}{true}{false}#*
\iflistequals{literal list}{cmd}{true}{false}#*
\ifnameequals{name list}{cmd}{true}{false}#*
\iffieldequalcs{field}{csname}{true}{false}#*
\iflistequalcs{literal list}{csname}{true}{false}#*
\ifnameequalcs{name list}{csname}{true}{false}#*
\iffieldequalstr{field}{string}{true}{false}#*
\iffieldxref{field}{true}{false}#*
\iflistxref{literal list}{true}{false}#*
\ifnamexref{name list}{true}{false}#*
\ifcurrentfield{field}{true}{false}#*
\ifcurrentlist{literal list}{true}{false}#*
\ifcurrentname{name list}{true}{false}#*
\ifuseprefix{true}{false}#*
\ifuseauthor{true}{false}#*
\ifuseeditor{true}{false}#*
\ifusetranslator{true}{false}#*
\ifcrossrefsource{true}{false}#*
\ifxrefsource{true}{false}#*
\ifsingletitle{true}{false}#*
\ifnocite{true}{false}#*
\ifuniquetitle{true}{false}#*
\ifuniquebaretitle{true}{false}#*
\ifuniquework{true}{false}#*
\ifuniqueprimaryauthor{true}{false}#*
\ifandothers{list}{true}{false}#*
\ifmorenames{true}{false}#*
\ifmoreitems{true}{false}#*
\ifterseinits{true}{false}#*
\ifentrytype{type}{true}{false}#*
\ifkeyword{keyword}{true}{false}#*
\ifentrykeyword{entrykey}{keyword}{true}{false}#*
\ifcategory{category}{true}{false}#*
\ifentrycategory{entrykey}{category}{true}{false}#*
\ifciteseen{true}{false}#*
\ifentryseen{entrykey}{true}{false}#*
\ifentryinbib{entrykey}{true}{false}#*
\iffirstcitekey{true}{false}#*
\iflastcitekey{true}{false}#*
\ifciteibid{true}{false}#*
\ifciteidem{true}{false}#*
\ifopcit{true}{false}#*
\ifloccit{true}{false}#*
\iffirstonpage{true}{false}#*
\ifsamepage{instance1}{instance2}{true}{false}#*
\ifinteger{string}{true}{false}#*
\hascomputableequivalent{string}{true}{false}#*
\ifiscomputable{string}{true}{false}#*
\getcomputableequivalent{string}{macro%cmd}#*d
\ifnumeral{string}{true}{false}#*
\ifnumerals{string}{true}{false}#*
\ifpages{string}{true}{false}#*
\iffieldint{field}{true}{false}#*
\iffieldnum{field}{true}{false}#*
\iffieldnums{field}{true}{false}#*
\iffieldpages{field}{true}{false}#*
\ifbibstring{string}{true}{false}#*
\ifbibxstring{string}{true}{false}#*
\iffieldbibstring{field}{true}{false}#*
\iffieldplusstringbibstring{field}{string}{true}{false}#*
\ifdriver{entrytype}{true}{false}#*
\ifcapital{true}{false}#*
\ifcitation{true}{false}#*
\ifvolcite{true}{false}#*
\ifbibliography{true}{false}#*
\ifnatbibmode{true}{false}#*
\ifciteindex{true}{false}#*
\ifbibindex{true}{false}#*
\iffootnote{true}{false}#*
\thecitecounter
\themaxcitecounter
\theuniquename
\theuniquelist
\theparenlevel

\ifboolexpr{expression}{true}{false}#*
\ifthenelse{tests}{true}{false}#*

\newbibmacro{name%cmd}{definition}#*d
\newbibmacro{name%cmd}[args]{definition}#*d
\newbibmacro{name%cmd}[args][default]{definition}#*d
\newbibmacro*{name%cmd}{definition}#*d
\newbibmacro*{name%cmd}[args]{definition}#*d
\newbibmacro*{name%cmd}[args][default]{definition}#*d
\renewbibmacro{name%cmd}{definition}#*d
\renewbibmacro{name%cmd}[args]{definition}#*d
\renewbibmacro{name%cmd}[args][default]{definition}#*d
\renewbibmacro*{name%cmd}{definition}#*d
\renewbibmacro*{name%cmd}[args]{definition}#*d
\renewbibmacro*{name%cmd}[args][default]{definition}#*d
\providebibmacro{name%cmd}{definition}#*d
\providebibmacro{name%cmd}[args]{definition}#*d
\providebibmacro{name%cmd}[args][default]{definition}#*d
\providebibmacro*{name%cmd}{definition}#*d
\providebibmacro*{name%cmd}[args]{definition}#*d
\providebibmacro*{name%cmd}[args][default]{definition}#*d
\letbibmacro{alias%cmd}{name}#*d
\letbibmacro*{alias%cmd}{name}#*d
\usebibmacro{name}#*
\usebibmacro*{name}#*
\savecommand{cmd}#*
\restorecommand{cmd}#*
\savebibmacro{name}#*
\restorebibmacro{name}#*
\savefieldformat{format}#*
\savefieldformat[entrytype]{format}#*
\restorefieldformat{format}#*
\restorefieldformat[entrytype]{format}#*
\savelistformat{format}#*
\savelistformat[entrytype]{format}#*
\restorelistformat{format}#*
\restorelistformat[entrytype]{format}#*
\savenameformat{format}#*
\savenameformat[entrytype]{format}#*
\restorenameformat{format}#*
\restorenameformat[entrytype]{format}#*
\savelistwrapperformat{format}#*
\savelistwrapperformat[entrytype]{format}#*
\restorelistwrapperformat{format}#*
\restorelistwrapperformat[entrytype]{format}#*
\savenamewrapperformat{format}#*
\savenamewrapperformat[entrytype]{format}#*
\restorenamewrapperformat{format}#*
\restorenamewrapperformat[entrytype]{format}#*
\ifbibmacroundef{name}{true}{false}#*
\iffieldformatundef{name}{true}{false}#*
\iffieldformatundef[entrytype]{name}{true}{false}#*
\iflistformatundef{name}{true}{false}#*
\iflistformatundef[entrytype]{name}{true}{false}#*
\ifnameformatundef{name}{true}{false}#*
\ifnameformatundef[entrytype]{name}{true}{false}#*
\iflistwrapperformatundef{name}{true}{false}#*
\iflistwrapperformatundef[entrytype]{name}{true}{false}#*
\ifnamewrapperformatundef{name}{true}{false}#*
\ifnamewrapperformatundef[entrytype]{name}{true}{false}#*
\usedriver{code}{entrytype}#*
\bibhypertarget{name}{text}#*
\bibhyperlink{name}{text}#*
\bibhyperref{text}#*
\bibhyperref[entrykey]{text}#*
\ifhyperref{true}{false}#*
\docsvfield{field}#*
\forcsvfield{handler}{field}#*
\MakeCapital{text}#*
\MakeSentenceCase{text}#*
\MakeSentenceCase*{text}#*
\mkpageprefix{text}#*
\mkpageprefix[pagination]{text}#*
\mkpageprefix[pagination][postpro]{text}#*
\mkpagetotal{text}#*
\mkpagetotal[pagination]{text}#*
\mkpagetotal[pagination][postpro]{text}#*
\mkcomprange{text}#*
\mkcomprange[postpro]{text}#*
\mkcomprange[postpro][itempostpro]{text}#*
\mkcomprange*{text}#*
\mkcomprange*[postpro]{text}#*
\mkcomprange*[postpro][itempostpro]{text}#*
\mknormrange{text}#*
\mknormrange[postpro]{text}#*
\mknormrange[postpro][itempostpro]{text}#*
\mknormrange*{text}#*
\mknormrange*[postpro]{text}#*
\mknormrange*[postpro][itempostpro]{text}#*
\mkfirstpage{text}#*
\mkfirstpage[postpro]{text}#*
\mkfirstpage[postpro][itempostpro]{text}#*
\mkfirstpage*{text}#*
\mkfirstpage*[postpro]{text}#*
\mkfirstpage*[postpro][itempostpro]{text}#*
\rangelen{rangefield}#*
\DeclareNumChars{characters}#*
\DeclareNumChars*{characters}#*
\DeclareRangeChars{characters}#*
\DeclareRangeChars*{characters}#*
\DeclareRangeCommands{cmds}#*
\DeclareRangeCommands*{cmds}#*
\DeclarePageCommands{cmds}#*
\DeclarePageCommands*{cmds}#*
\NumCheckSetup{code}#*
\NumsCheckSetup{code}#*
\PagesCheckSetup{code}#*
\DeclareBabelToExplLanguageMapping{babel language}{expl language}#*
\UndeclareBabelToExplLanguageMapping{babel language}#*
\DeclareCaseLangs{languages}#*
\DeclareCaseLangs*{languages}#*
\BibliographyWarning{message%text}#*
\pagetrackertrue#*
\pagetrackerfalse#*
\citetrackertrue#*
\citetrackerfalse#*
\backtrackertrue#*
\backtrackerfalse#*

## 4.7 Punctuation and Spacing ##
\newblock#*
\newunit#*
\finentry#*
\setunit{punctuation}#*
\setunit*{punctuation}#*
\printunit{punctuation}#*
\printunit*{punctuation}#*
\setpunctfont{cmd}#*
\resetpunctfont#*
\ifpunct{true}{false}#*
\ifterm{true}{false}#*
\ifpunctmark{character}{true}{false}#*
\ifprefchar{true}{false}#*

\adddot#*
\addcomma#*
\addsemicolon#*
\addcolon#*
\addperiod#*
\addexclam#*
\addquestion#*
\isdot#*
\nopunct#*

\unspace#*
\addspace#*
\addnbspace#*
\addthinspace#*
\addnbthinspace#*
\addlowpenspace#*
\addhighpenspace#*
\addlpthinspace#*
\addhpthinspace#*
\addabbrvspace#*
\addabthinspace#*
\adddotspace#*
\addslash#*

\DeclarePrefChars{characters}#*
\DeclarePrefChars*{characters}#*
\DeclareAutoPunctuation{characters}#*
\DeclareCapitalPunctuation{characters}#*
\DeclarePunctuationPairs{identifier}{characters}#*
\DeclareQuotePunctuation{characters}#*
\uspunctuation#*
\stdpunctuation#*

\bibsentence#*
\midsentence#*
\midsentence*#*

## 4.8 Localization Strings ##
\bibstring{string key}#*
\bibstring[wrapper]{string key}#*
\biblstring{string key}#*
\biblstring[wrapper]{string key}#*
\bibsstring{string key}#*
\bibsstring[wrapper]{string key}#*
\bibcpstring{string key}#*
\bibcpstring[wrapper]{string key}#*
\bibcplstring{string key}#*
\bibcplstring[wrapper]{string key}#*
\bibcpsstring{string key}#*
\bibcpsstring[wrapper]{string key}#*
\bibucstring{string key}#*
\bibucstring[wrapper]{string key}#*
\bibuclstring{string key}#*
\bibuclstring[wrapper]{string key}#*
\bibuscstring{string key}#*
\bibuscstring[wrapper]{string key}#*
\biblcstring{string key}#*
\biblcstring[wrapper]{string key}#*
\biblclstring{string key}#*
\biblclstring[wrapper]{string key}#*
\biblcsstring{string key}#*
\biblcsstring[wrapper]{string key}#*
\bibxstring{string key}#*
\bibxstring[wrapper]{string key}#*
\bibxlstring{string key}#*
\bibxlstring[wrapper]{string key}#*
\bibxsstring{string key}#*
\bibxsstring[wrapper]{string key}#*
\mainlang#*
\textmainlang{text}#*
\texouterlang{text}#*

## 4.9 Localization Modules ##
\DeclareLanguageMapping{language}{file}#*
\DeclareLanguageMappingSuffix{suffix}#*

## 4.10 Formatting Commands ##
\mkbibemph{text}#*
\mkbibitalic{text}#*
\mkbibbold{text}#*
\mkbibquote{text}#*
\mkbibparens{text}#*
\mkbibbrackets{text}#*
\bibopenparen#*
\bibcloseparen#*
\bibopenbracket#*
\bibclosebracket#*
\mkbibfootnote{text}#*
\mkbibfootnotetext{text}#*
\mkbibendnote{text}#*
\mkbibendnotetext{text}#*
\bibfootnotewrapper{text}#*
\bibendnotewrapper{text}#*
\mkbibsuperscript{text}#*
\mkbibmonth{integer}#*
\mkbibseason{string}#*
\mkyearzeros{integer}#*
\mkmonthzeros{integer}#*
\mkdayzeros{integer}#*
\mktimezeros{integer}#*
\forcezerosy{integer}#*
\forcezerosmdt{integer}#*
\stripzeros{integer}#*

\labelnumberwidth#*
\labelalphawidth#*
\currentlang#*
\currentfield#*
\currentlist#*
\currentname#*

\AtBeginBibliography{code}#*
\AtBeginShorthands{code}#*
\AtBeginBiblist{biblistname}{code}#*
\AtEveryBibitem{code}#*
\AtEveryLositem{code}#*
\AtEveryBiblistitem{biblistname}{code}#*
\AtNextBibliography{code}#*
\AtUsedriver{code}#*
\AtUsedriver*{code}#*
\AtEveryCite{code}#*
\AtEveryCitekey{code}#*
\AtEveryMultiCite{code}#*
\AtNextCite{code}#*
\AtEachCitekey{code}#*
\AtNextCitekey{code}#*
\AtNextMultiCite{code}#*
\AtVolcite{code}#*
\AtVolcite*{code}#*
\AtDataInput{code}#*
\AtDataInput[entrytype]{code}#*
\UseBibitemHook#*
\UseUsedriverHook#*
\UseEveryCiteHook#*
\UseEveryCitekeyHook#*
\UseEveryMultiCiteHook#*
\UseNextCiteHook#*
\UseNextCitekeyHook#*
\UseNextMultiCiteHook#*
\UseVolciteHook#*
\DeferNextCitekeyHook#*
\AtEveryEntrykey{code}{success}{failure}#*

## 4.11 Hints and Caveats ##
\DeclareUniquenameTemplate{specification}#*
\DeclareUniquenameTemplate[name]{specification}#*

# miscellaneous
\mkdaterangeshort{datetype}#*
\mkdaterangelong{datetype}#*
\mkdaterangeterse{datetype}#*
\mkdaterangecomp{datetype}#*
\mkdaterangeshortextra{datetype}#*
\mkdaterangelongextra{datetype}#*
\mkdaterangeterseextra{datetype}#*
\mkdaterangecompextra{datetype}#*
\mkdaterangefull{short|long}{datetype}#*
\mkdaterangefullextra{short|long}{datetype}#*
\mkdaterangetrunc{short|long}{datetype}#*
\mkdaterangetruncextra{short|long}{datetype}#*
\mkdaterangeyear{datetype}#*
\mkdaterangeymd{datetype}#*
\mkdaterangeymdextra{datetype}#*
\mkdaterangeyearextra{datetype}#*
\mkdaterangeiso{datetype}#*
\mkdaterangeisoextra{datetype}#*
\BiblatexHungarianWarningOff#*
\BiblatexLatvianWarningOff#*
\BiblatexSplitbibDefernumbersWarningOff#*

### biblatex-apa v9.15 ###
#ifOption:style=apa
#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c
apamaxprtauth=%<number%>
#endkeyvals
# from apa.bbx
\foreverunspace#*
\printtexte{text}#*
\printtexte[format]{text}#*
\maxprtauth#*
\apanum{num}#*
\mkdaterangeapalong{datetype}#*
\mkdaterangeapalongextra{datetype}#*
\begrelateddelimcommenton#*
\begrelateddelimreviewof#*
\begrelateddelimreprintfrom#*
\urldatecomma#*
# from apa.cbx
\apashortdash#*
\citeresetapa#*
\fullcitebib[prenote][postnote]{bibid}#*C
\fullcitebib[postnote]{bibid}#*C
\fullcitebib{bibid}#*C
\nptextcite[prenote][postnote]{bibid}#C
\nptextcite[postnote]{bibid}#C
\nptextcite{bibid}#C
\nptextcites{bibid}{bibid}#*C
\nptextcites(pre){bibid}{bibid}#*C
\nptextcites(pre)(post){bibid}{bibid}#*C
\nptextcites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\nptextcites[pre]{bibid}[pre]{bibid}#*C
\nptextcites[pre][post]{bibid}[pre][post]{bibid}#*C
\nptextcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#*C
#endif

### biblatex-ieee v1.3f ###
#ifOption:style=ieee
\mkpagegrouped{text}#*
\mkonepagegrouped{text}#*
#endif
#ifOption:style=ieee-alphabetic
\mkpagegrouped{text}#*
\mkonepagegrouped{text}#*
#endif

### biblatex-mla v2.0 ###
#ifOption:style=mla-strict
# loads mla.cbx
#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c
# from mla-strict.bbx
annotation#true,false
showlocation#true,false
longdash#true,false
noremoteinfo#true,false
isan#true,false
ismn#true,false
isrn#true,false
issn#true,false
# from mla.cbx
firstlonghand#true,false
nofullfootnote#true,false
mancitepar#true,false
footnoterulestrict#true,false
mladraft
#endkeyvals
# from mla-strict.bbx
\openrangeformat{arg}#*
\openrangemark#*
\mlanamedash#*
# from mla.cbx
\splitfootnoterule#S
\pagefootnoterule#S
\mlasymbolfootnote#S
\themladraftnote#S
\headlesscite[prenote][postnote]{bibid}#C
\headlesscite[postnote]{bibid}#C
\headlesscite{bibid}#C
\headlessfullcite[prenote][postnote]{bibid}#C
\headlessfullcite[postnote]{bibid}#C
\headlessfullcite{bibid}#C
\titleandsubtitle[prenote][postnote]{bibid}#*C
\titleandsubtitle[postnote]{bibid}#*C
\titleandsubtitle{bibid}#*C
#endif

#ifOption:style=mla
# loads mla-strict.bbx
#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c
# from mla-strict.bbx
annotation#true,false
showlocation#true,false
longdash#true,false
noremoteinfo#true,false
isan#true,false
ismn#true,false
isrn#true,false
issn#true,false
# from mla.cbx
firstlonghand#true,false
nofullfootnote#true,false
mancitepar#true,false
footnoterulestrict#true,false
mladraft
#endkeyvals
# from mla-strict.bbx
\openrangeformat{arg}#*
\openrangemark#*
\mlanamedash#*
# from mla.cbx
\splitfootnoterule#S
\pagefootnoterule#S
\mlasymbolfootnote#S
\themladraftnote#S
\headlesscite[prenote][postnote]{bibid}#C
\headlesscite[postnote]{bibid}#C
\headlesscite{bibid}#C
\headlessfullcite[prenote][postnote]{bibid}#C
\headlessfullcite[postnote]{bibid}#C
\headlessfullcite{bibid}#C
\titleandsubtitle[prenote][postnote]{bibid}#*C
\titleandsubtitle[postnote]{bibid}#*C
\titleandsubtitle{bibid}#*C
#endif

#ifOption:style=mla-new
# this just loads mla style
#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c
# from mla-strict.bbx
annotation#true,false
showlocation#true,false
longdash#true,false
noremoteinfo#true,false
isan#true,false
ismn#true,false
isrn#true,false
issn#true,false
# from mla.cbx
firstlonghand#true,false
nofullfootnote#true,false
mancitepar#true,false
footnoterulestrict#true,false
mladraft
#endkeyvals
# from mla-strict.bbx
\openrangeformat{arg}#*
\openrangemark#*
\mlanamedash#*
# from mla.cbx
\splitfootnoterule#S
\pagefootnoterule#S
\mlasymbolfootnote#S
\themladraftnote#S
\headlesscite[prenote][postnote]{bibid}#C
\headlesscite[postnote]{bibid}#C
\headlesscite{bibid}#C
\headlessfullcite[prenote][postnote]{bibid}#C
\headlessfullcite[postnote]{bibid}#C
\headlessfullcite{bibid}#C
\titleandsubtitle[prenote][postnote]{bibid}#*C
\titleandsubtitle[postnote]{bibid}#*C
\titleandsubtitle{bibid}#*C
#endif

### biblatex-nature v1.3d ###
#ifOption:style=nature
#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c
articletitle#true,false
intitle#true,false
#endkeyvals
#endif

### biblatex-philosophy v1.9.8f ###
#ifOption:style=philosophy-classic
\sdcite{bibid}#C
\footcitet{bibid}#C
#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c,\printbibliography
relatedformat=#semicolon,parens,brackets
publocformat=#publocyear,locpubyear,loccolonpub
volnumformat=#strings,parens,plain
volumeformat=#arabic,roman,romanscRoman
editionformat=#arabic,roman,romansc,Roman,superscript
scauthors=#bib,cite,bibcite,citefn,bibcitefn,all
lowscauthors#true,false
shorthandintro#true,false
inbeforejournal#true,false
classical#true,false
library#true,false
annotation#true,false
latinemph#true,false
square#true,false
nodate#true,false
#endkeyvals
\annotationfont#*
\libraryfont#*
\volnumpunct#*
\editorstrgdelim#*
#endif

#ifOption:style=philosophy-modern
\sdcite{bibid}#C
\footcitet{bibid}#C
#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c,\printbibliography
relatedformat=#semicolon,parens,brackets
publocformat=#publocyear,locpubyear,loccolonpub
volnumformat=#strings,parens,plain
volumeformat=#arabic,roman,romanscRoman
editionformat=#arabic,roman,romansc,Roman,superscript
scauthors=#bib,cite,bibcite,citefn,bibcitefn,all
lowscauthors#true,false
shorthandintro#true,false
inbeforejournal#true,false
classical#true,false
library#true,false
annotation#true,false
latinemph#true,false
square#true,false
nodate#true,false
yearleft#true,false
restoreclassic#true,false
#endkeyvals
\annotationfont#*
\libraryfont#*
\volnumpunct#*
\editorstrgdelim#*
#endif

#ifOption:style=philosophy-verbose
\ccite{bibid}#C
#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c,\printbibliography
relatedformat=#semicolon,parens,brackets
publocformat=#publocyear,locpubyear,loccolonpub
volnumformat=#strings,parens,plain
volumeformat=#arabic,roman,romanscRoman
editionformat=#arabic,roman,romansc,Roman,superscript
scauthors=#bib,cite,bibcite,citefn,bibcitefn,all
lowscauthors#true,false
shorthandintro#true,false
inbeforejournal#true,false
classical#true,false
library#true,false
annotation#true,false
latinemph#true,false
iviemph#true,false
commacit#true,false
#endkeyvals
\annotationfont#*
\libraryfont#*
\volnumpunct#*
\editorstrgdelim#*
#endif

### biblatex-publist v1.26 ###
#ifOption:style=publist
# from publist.bbx
#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c
plauthorname=%<surname%>
plauthorfirstname=%<first name%>
plauthornameprefix=%<von part%>
plauthorhandling=#omit,highlight
nameorder=#family-given,given-family
boldyear#true,false
pubstateextra#true,false
marginyear#true,false
plnumbered=#true,false,reset
reversenumbering#true,false
plauthorfirstinit#true,false
prinfo#true,false
linktitleall#true,false
linktitledoi#true,false
linktitleurl#true,false
linktitleisbn#true,false
linktitleissn#true,false
#endkeyvals
\plauthorname{surname}
\plauthorname[first name]{surname}
\plauthorname[first name][von part]{surname}
\plnameomission#*
\plmarginyear{text}#*
\plauthorhl{text}#*
\extralabelnumberwidth#*
\shiftbplnum{integer}
\publistbasestyle#*
\plisbnlink{ISBN%URL}#*U
\plissnlink{ISSN%URL}#*U
\mkbibdesc{number}#*
\mkbibsecstart{number}#*
\printprinfo{string}#*
\thenonplauthors#*
\thenonpleditors#*
\theplauthor#*
\thepleditor#*
\theplauthors#*
\thepleditors#*
\therealliststop#*
\thenonplauthor#*
\thenonpleditor#*
# from publist.cbx
\citeitem[prenote][postnote]{bibid}#*C
\citeitem[postnote]{bibid}#*C
\citeitem{bibid}#C
\shiftciteitem{integer}
\mkrefdesc{number}#*
#endif

#ifOption:bibstyle=publist
# from publist.bbx
#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c
plauthorname=%<surname%>
plauthorfirstname=%<first name%>
plauthornameprefix=%<von part%>
plauthorhandling=#omit,highlight
nameorder=#family-given,given-family
boldyear#true,false
pubstateextra#true,false
marginyear#true,false
plnumbered=#true,false,reset
reversenumbering#true,false
plauthorfirstinit#true,false
prinfo#true,false
linktitleall#true,false
linktitledoi#true,false
linktitleurl#true,false
linktitleisbn#true,false
linktitleissn#true,false
#endkeyvals
\plauthorname{surname}
\plauthorname[first name]{surname}
\plauthorname[first name][von part]{surname}
\plnameomission#*
\plmarginyear{text}#*
\plauthorhl{text}#*
\extralabelnumberwidth#*
\shiftbplnum{integer}
\publistbasestyle#*
\plisbnlink{ISBN%URL}#*U
\plissnlink{ISSN%URL}#*U
\mkbibdesc{number}#*
\mkbibsecstart{number}#*
\printprinfo{string}#*
\thenonplauthors#*
\thenonpleditors#*
\theplauthor#*
\thepleditor#*
\theplauthors#*
\thepleditors#*
\therealliststop#*
\thenonplauthor#*
\thenonpleditor#*
#endif

### biblatex-science v1.2 ###
#ifOption:style=science
#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c
articletitle#true,false
#endkeyvals
#endif
