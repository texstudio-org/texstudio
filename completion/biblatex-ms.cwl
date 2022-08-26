# biblatex-ms package
# Matthew Bertucci 2022/08/25 for v4.0

## Note: biblatex-ms is the experimental multiscript version of biblatex,
## so though it does not actually load biblatex, the cwl is just #include:biblatex
## and the added features (as well as the options since those must be listed manually)

#include:biblatex

#keyvals:\usepackage/biblatex-ms#c
backend=#bibtex,bibtex8,biber
style=#authoryear,authortitle,alphabetic,numeric,alphabetic-verb,authortitle-comp,authortitle-ibid,authortitle-icomp,authortitle-tcomp,authortitle-terse,authortitle-ticomp,authoryear-comp,authoryear-ibid,authoryear-icomp,debug,draft,numeric-comp,numeric-verb,reading,verbose,verbose-ibid,verbose-inote,verbose-note,verbose-trad1,verbose-trad2,verbose-trad3
bibstyle=#authoryear,authortitle,numeric,alphabetic,verbose,reading,draft,debug
citestyle=#authoryear,authortitle,alphabetic,numeric,numeric-comp,numeric-verb,alphabetic-verb,authoryear-comp,authoryear-ibid,authoryear-icomp,authortitle-comp,authortitle-ibid,authortitle-icomp,authortitle-terse,authortitle-tcomp,authortitle-ticomp,verbose,verbose-ibid,verbose-note,verbose-inote,verbose-trad1,verbose-trad2,verbose-trad3,reading,draft,debug
natbib#true,false
mcite#true,false
casechanger=#auto,latex2e,expl3
datamodel=%<model%>
#endkeyvals

#keyvals:\usepackage/biblatex-ms#c
sorting=#nty,nyt,nyvt,anyt,anyvt,ynt,ydnt,none,debug
sortcase#true,false
sortupper#true,false
sortlocale=
sortcites#true,false
sortsets#true,false
pluralothers#true,false
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
eventdate=#year,short,long,terse,comp,ymd,iso
origdate=#year,short,long,terse,comp,ymd,iso
urldate=#year,short,long,terse,comp,ymd,iso
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
eventtime=#12h,24h,24hcomp
origtime=#12h,24h,24hcomp
urltime=#12h,24h,24hcomp
alltimes=#12h,24h,24hcomp
dateusetime#true,false
labeldateusetime#true,false
eventdateusetime#true,false
origdateusetime#true,false
urldateusetime#true,false
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
giveninits#true,false
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

#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
autofieldlang=#none,hyphen,other,other*,langname
autofieldlangstrings#true,false
dynamiclabel#true,false
msform=%<form%>
mslang=%<BCP47tag%>
#endkeyvals

\alternate{form}{BCP47tag}#*
\citefield[prenote][postnote]{bibid}[format][msform][mslang]{field}#C
\citefield{bibid}[format][msform][mslang]{field}#C
\citelist[prenote][postnote]{bibid}[format][msform][mslang]{literal list}#C
\citelist{bibid}[format][msform][mslang]{literal list}#C
\citename[prenote][postnote]{bibid}[format][msform][mslang]{name list}#C
\citename{bibid}[format][msform][mslang]{name list}#C
\csfield[msform][mslang]{field}#*
\currentmsform#*
\currentmsforms#*
\currentmslang#*
\currentmslangs#*
\DeclareExtradateContext[entrytype1,entrytype2,...]{specification}#*
\DeclareExtradateContext{specification}#*
\DeclareMsselect{langid}{specification}#*
\docsvfield[msform][mslang]{field}#*
\fieldhascomputableequivalent[msform][mslang]{field}{true}{false}#*
\fieldmsforms{entryfield}#*
\fieldmslangs{entryfield}#*
\forcsvfield{handler}[msform][mslang]{field}#*
\getfieldannotation[msform][mslang]#*
\getfieldannotation[msform][mslang][field]#*
\getfieldannotation[msform][mslang][field][annotation name]#*
\getitemannotation[msform][mslang]#*
\getitemannotation[msform][mslang][field]#*
\getitemannotation[msform][mslang][field][annotation name]#*
\getitemannotation[msform][mslang][field][annotation name][item]#*
\getpartannotation[msform][mslang][field][annotation name][item]{part}#*
\getpartannotation[msform][mslang][field][annotation name]{part}#*
\getpartannotation[msform][mslang][field]{part}#*
\getpartannotation[msform][mslang]{part}#*
\hasfieldannotation[msform][mslang][field][annotation name]{true}{false}#*
\hasfieldannotation[msform][mslang][field]{true}{false}#*
\hasfieldannotation[msform][mslang]{true}{false}#*
\hasitemannotation[msform][mslang][field][annotation name][item]{true}{false}#*
\hasitemannotation[msform][mslang][field][annotation name]{true}{false}#*
\hasitemannotation[msform][mslang][field]{true}{false}#*
\hasitemannotation[msform][mslang]{true}{false}#*
\haspartannotation[msform][mslang][field][annotation name][item]{part}{true}{false}#*
\haspartannotation[msform][mslang][field][annotation name]{part}{true}{false}#*
\haspartannotation[msform][mslang][field]{part}{true}{false}#*
\haspartannotation[msform][mslang]{part}{true}{false}#*
\ifentryfieldundef{entryfield}{true}{false}#*
\iffieldannotation[msform][mslang][field][annotation name]{annotation}{true}{false}#*
\iffieldannotation[msform][mslang][field]{annotation}{true}{false}#*
\iffieldannotation[msform][mslang]{annotation}{true}{false}#*
\iffieldbibstring[msform][mslang]{field}{true}{false}#*
\iffieldequalcs[msform][mslang]{field}{csname}{true}{false}#*
\iffieldequals[msform][mslang]{field}{cmd}{true}{false}#*
\iffieldequalstr[msform][mslang]{field}{string}{true}{false}#*
\iffieldint[msform][mslang]{field}{true}{false}#*
\iffieldiscomputable[msform][mslang]{field}{true}{false}#*
\iffieldnum[msform][mslang]{field}{true}{false}#*
\iffieldnums[msform][mslang]{field}{true}{false}#*
\iffieldpages[msform][mslang]{field}{true}{false}#*
\iffieldplusstringbibstring[msform][mslang]{field}{string}{true}{false}#*
\iffieldsequal[msform1][mslang1]{field1}[msform2][mslang2]{field2}{true}{false}#*
\iffieldundef[msform][mslang]{field}{true}{false}#*
\iffieldxref[msform][mslang]{field}{true}{false}#*
\ifitemannotation[msform][mslang][field][annotation name][item]{annotation}{true}{false}#*
\ifitemannotation[msform][mslang][field][annotation name]{annotation}{true}{false}#*
\ifitemannotation[msform][mslang][field]{annotation}{true}{false}#*
\ifitemannotation[msform][mslang]{annotation}{true}{false}#*
\iflistequalcs[msform][mslang]{literal list}{csname}{true}{false}#*
\iflistequals[msform][mslang]{literal list}{cmd}{true}{false}#*
\iflistsequal[msform1][mslang1]{literal list1}[msform2][mslang2]{literal list2}{true}{false}#*
\iflistundef[msform][mslang]{literal list}{true}{false}#*
\iflistxref[msform][mslang]{literal list}{true}{false}#*
\ifmsentryfield{entryfield}{true}{false}#*
\ifnameequalcs[msform][mslang]{name list}{csname}{true}{false}#*
\ifnameequals[msform][mslang]{name list}{cmd}{true}{false}#*
\ifnamesequal[msform1][mslang1]{name list1}[msform2][mslang2]{name list2}{true}{false}#*
\ifnameundef[msform][mslang]{name list}{true}{false}#*
\ifnamexref[msform][mslang]{name list}{true}{false}#*
\ifpartannotation[msform][mslang][field][annotation name][item]{part}{annotation}{true}{false}#*
\ifpartannotation[msform][mslang][field][annotation name]{part}{annotation}{true}{false}#*
\ifpartannotation[msform][mslang][field]{part}{annotation}{true}{false}#*
\ifpartannotation[msform][mslang]{part}{annotation}{true}{false}#*
\indexfield[format][msform][mslang]{field}#*
\indexlist[format][start-stop][msform][mslang]{literal list}#*
\indexnames[format][start-stop][msform][mslang]{name list}#*
\maplangtag{BCP47tag}{langid}#*
\mslang{BCP47tag}#*
\printfield[format][msform][mslang]{field}#*
\printlist[format][start-stop][msform][mslang]{literal list}#*
\printnames[format][start-stop][msform][mslang]{name list}#*
\restorefield[msform][mslang]{field}{cmd}#*
\restorelist[msform][mslang]{literal list}{cmd}#*
\restorename[msform][mslang]{name list}{cmd}#*
\savefield[msform][mslang]{field}{cmd}#*d
\savefield[msform]{field}{cmd}#*d
\savefieldcs[msform][mslang]{field}{csname}#*
\savelist[msform][mslang]{literal list}{cmd}#*d
\savelist[msform]{literal list}{cmd}#*d
\savelistcs[msform][mslang]{literal list}{csname}#*
\savename[msform][mslang]{name list}{cmd}#*d
\savename[msform]{name list}{cmd}#*d
\savenamecs[msform][mslang]{name list}{csname}#*
\strfield[msform][mslang]{field}#*
\strfirstlistitem[msform][mslang]{literal list}#*
\strlist[msform][mslang]{literal list}#*
\strname[msform][mslang]{name list}#*
\thefield[msform][mslang]{field}#*
\thefirstlistitem[msform][mslang]{literal list}#*
\thelist[msform][mslang]{literal list}#*
\thename[msform][mslang]{name list}#*
\uniquepart{namepart}#*
\usefield{command}[msform][mslang]{field}#*
\usefirstlistitem{command}[msform][mslang]{literal list}#*

#keyvals:\DeclareRefcontext,\begin{refcontext},\newrefcontext,\localrefcontext,\assignrefcontextkeyws,\assignrefcontextkeyws*,\assignrefcontextcats,\assignrefcontextcats*,\assignrefcontextentries,\assignrefcontextentries*,\GenRefcontextData
msform=%<form%>
mslang=%<BCP47tag%>
#endkeyvals

#keyvals:\step
fieldsourcemsform=%<msform%>
fieldsourcemslang=%<mslang%>
fieldtargetmsform=%<msform%>
fieldtargetmslang=%<mslang%>
#endkeyvals

#keyvals:\field
form=%<string%>
lang=%<BCP47tag%>
#endkeyvals

# options
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

### biblatex-abnt v3.4 ###
#ifOption:style=abnt
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from abnt.bbx
ittitles#true,false
scbib#true,false
nosl#true,false
nosn#true,false
noslsn#true,false
repeattitles#true,false
repeatfirstfields#true,false
repeatfields#true,false
usedashes#true,false
indent#true,false
extradate#true,false
extrayear#true,false
justify#true,false
pretty#true,false
citecount#true,false
# from abnt.cbx
sccite#true,false
#endkeyvals
# from abnt.bbx
#include:xpatch
\origbibsetup#S
\FirstWordUpper{text}#*
\FirstWordSC{text}#*
\FirstWordLCSC{text}#*
\traceparam{arg}#S
\paramL#S
\traceparamA#S
\traceparamB#S
\traceparamS#S
\traceparamC{arg}#S
\traceparamD{arg}#S
\traceparamE#S
\smartuppercase{text}#*
\smartlowercase{text}#*
\smartlcsc{text}#*
\smartsc{text}#*
\UpperOrSC{text}#*
\NormalOrSC{text}#*
\iffieldregex{field}{regex}{true}{false}#*
\iffieldendswithpunct{field}{true}{false}#*
\IfGivenIsInitial{arg1}{arg2}#*
\multinamedelimorig#S
\finalnamedelimorig#S
\abntnum{number}#*
\bibnameunderscore#*
\nopunctdash#*
# from abnt.cbx
\UpperOrSCCite{text}#*
\NormalOrSCCite{text}#*
\IfGivenIsInit{arg1}{arg2}#*
\origmkbibnamefamily#S
\origmkbibnamegiven#S
\origmkbibnameprefix#S
\origmkbibnamesuffix#S
\FirstWord{text}#*
\addapud#*
\apud{bibid}{bibid}#C
\apud(post){bibid}{bibid}#*C
\apud(pre)(post){bibid}{bibid}#C
\apud(pre)(post)[post]{bibid}[post]{bibid}#*C
\apud[post]{bibid}[post]{bibid}#*C
\apud[pre][post]{bibid}[pre][post]{bibid}#*C
\apud(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\plaincite[prenote][postnote]{bibid}#*C
\plaincite[postnote]{bibid}#*C
\plaincite{bibid}#*C
\citelastname[prenote][postnote]{bibid}#*C
\citelastname[postnote]{bibid}#*C
\citelastname{bibid}#*C
\textapud{bibid}{bibid}#C
\textapud{bibid}[post]{bibid}#*C
\textapud[post]{bibid}{bibid}#*C
\textapud[post]{bibid}[post]{bibid}#C
\textapud[pre][post]{bibid}[pre][post]{bibid}#C
\citeyearorsh*[prenote][postnote]{bibid}#*C
\citeyearorsh*[postnote]{bibid}#*C
\citeyearorsh*{bibid}#*C
#endif

#ifOption:style=abnt-ibid
# loads abnt.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from abnt.bbx
ittitles#true,false
scbib#true,false
nosl#true,false
nosn#true,false
noslsn#true,false
repeattitles#true,false
repeatfirstfields#true,false
repeatfields#true,false
usedashes#true,false
indent#true,false
extradate#true,false
extrayear#true,false
justify#true,false
pretty#true,false
citecount#true,false
# from abnt.cbx
sccite#true,false
#endkeyvals
# from abnt.bbx
#include:xpatch
\origbibsetup#S
\FirstWordUpper{text}#*
\FirstWordSC{text}#*
\FirstWordLCSC{text}#*
\traceparam{arg}#S
\paramL#S
\traceparamA#S
\traceparamB#S
\traceparamS#S
\traceparamC{arg}#S
\traceparamD{arg}#S
\traceparamE#S
\smartuppercase{text}#*
\smartlowercase{text}#*
\smartlcsc{text}#*
\smartsc{text}#*
\UpperOrSC{text}#*
\NormalOrSC{text}#*
\iffieldregex{field}{regex}{true}{false}#*
\iffieldendswithpunct{field}{true}{false}#*
\IfGivenIsInitial{arg1}{arg2}#*
\multinamedelimorig#S
\finalnamedelimorig#S
\abntnum{number}#*
\bibnameunderscore#*
\nopunctdash#*
# from abnt-ibid.cbx
\UpperOrSCCite{text}#*
\NormalOrSCCite{text}#*
\IfInitial{arg1}{arg2}{arg3}#*
\origmkbibnamefamily#S
\origmkbibnamegiven#S
\origmkbibnameprefix#S
\origmkbibnamesuffix#S
\mkidem{arg}#*
\mkibid{arg}#*
\mkopcit{arg}#*
\mkloccit{arg}#*
\addapud#*
\apud{bibid}{bibid}#C
\apud(post){bibid}{bibid}#*C
\apud(pre)(post){bibid}{bibid}#C
\apud(pre)(post)[post]{bibid}[post]{bibid}#*C
\apud[post]{bibid}[post]{bibid}#*C
\apud[pre][post]{bibid}[pre][post]{bibid}#*C
\apud(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
#endif

#ifOption:style=abnt-numeric
# loads abnt.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from abnt.bbx
ittitles#true,false
scbib#true,false
nosl#true,false
nosn#true,false
noslsn#true,false
repeattitles#true,false
repeatfirstfields#true,false
repeatfields#true,false
usedashes#true,false
indent#true,false
extradate#true,false
extrayear#true,false
justify#true,false
pretty#true,false
citecount#true,false
# from abnt-numeric.cbx
comp#true,false
#endkeyvals
# from abnt.bbx
#include:xpatch
\origbibsetup#S
\FirstWordUpper{text}#*
\FirstWordSC{text}#*
\FirstWordLCSC{text}#*
\traceparam{arg}#S
\paramL#S
\traceparamA#S
\traceparamB#S
\traceparamS#S
\traceparamC{arg}#S
\traceparamD{arg}#S
\traceparamE#S
\smartuppercase{text}#*
\smartlowercase{text}#*
\smartlcsc{text}#*
\smartsc{text}#*
\UpperOrSC{text}#*
\NormalOrSC{text}#*
\iffieldregex{field}{regex}{true}{false}#*
\iffieldendswithpunct{field}{true}{false}#*
\IfGivenIsInitial{arg1}{arg2}#*
\multinamedelimorig#S
\finalnamedelimorig#S
\abntnum{number}#*
\bibnameunderscore#*
\nopunctdash#*
#endif

### biblatex-acmart v0.1 ###
#ifOption:style=acmauthoryear
# from acmauthoryear.bbx
\newcommaunit#*
\newcommaunit*#*
\newcommaunitStar#S
\newcommaunitNoStar#S
# loads software.bbx
#include:xurl
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
halid#true,false
swhid#true,false
shortswhid#true,false
swlabels#true,false
vcs#true,false
license#true,false
#endkeyvals
# from acmauthoryear.cbx
#include:xpatch
\citeyearpar[prenote][postnote]{bibid}#*C
\citeyearpar[postnote]{bibid}#*C
\citeyearpar{bibid}#*C
\citep[prenote][postnote]{bibid}#*C
\citep[postnote]{bibid}#*C
\citep{bibid}#*C
\citet[prenote][postnote]{bibid}#*C
\citet[postnote]{bibid}#*C
\citet{bibid}#*C
#endif

#ifOption:style=acmnumeric
# from acmnumeric.bbx
# loads trad-plain.bbx
\volumenumberdelim#*
\newcommaunit#*
\newcommaunit*#*
\newcommaunitStar#S
\newcommaunitNoStar#S
# loads software.bbx
#include:xurl
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
halid#true,false
swhid#true,false
shortswhid#true,false
swlabels#true,false
vcs#true,false
license#true,false
#endkeyvals
#endif

### biblatex-archaeologie v2.4.5 ###
#ifOption:style=archaeologie
#include:ulem
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from archaeologie.bbx
bibancient#true,false
bibcorpora#true,false
lstabbrv#true,false
lstlocations#true,false
lstpublishers#true,false
bibfullname#true,false
scshape#true,false
edby#true,false
publisher#true,false
translation#true,false
yearseries#true,false
width=##L
counter#true,false
jstor#true,false
arachne#true,false
zenon#true,false
urn#true,false
biblabel=#plain,bold,brackets,parens
inreferencesasfullcite#true,false
eventdatelanguage#true,false
# from archaeologie.cbx
citeauthorformat=#initials,full,family,firstfulltheninitials,firstfullthenfamily
seenote#true,false
yearinparens#true,false
nametracker#true,false
#endkeyvals
# from archaeologie.bbx
\archDate#S
\archVersion#S
\archaeologieversion#*
\archaeologiedate#*
\labwidthsameline#*
\labwidthsamelineVALUE#S
\archaeologieoptions#*
\archaeologieoptions[plain]%|#*
\seperator#*
\maintitlepunct#*
\locationdelim#*
\relateddelimmultivolume#*
\volnumdelim#*
\yearnumdelim#*
\jourvoldelim#*
\bibdatesubseqesep#*
\bibdaterangesepx{arg}#*
\begin{fullexpotherlanguage}{language}#*
\end{fullexpotherlanguage}#*
# from archaeologie.cbx
\labelyeardelim#*
\citeauthorformatVALUE#S
\citetranslator[prenote][postnote]{bibid}#C
\citetranslator[postnote]{bibid}#C
\citetranslator{bibid}#C
\citetranslator*[prenote][postnote]{bibid}#C
\citetranslator*[postnote]{bibid}#C
\citetranslator*{bibid}#C
#endif

### biblatex-archaeology v2.2 ###
#ifOption:style=aefkw
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=afwl
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=amit
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=archa
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=dguf
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=dguf-alt
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=dguf-apa
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=eaz
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=eaz-alt
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=foe
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=jb-halle
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=jb-kreis-neuss
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=karl
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
\ifuselabeltitle{true}{false}#*
#endif

#ifOption:style=kunde
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=maja
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=mpk
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=mpkoeaw
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=niedersachsen
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=nnu
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=offa
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=rgk-inline
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=rgk-numeric
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=rgk-verbose
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
\ifuselabeltitle{true}{false}#*
#endif

#ifOption:style=rgk-inline-old
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=rgk-numeric-old
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
\ifuselabeltitle{true}{false}#*
#endif

#ifOption:style=rgk-verbose-old
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=rgzm-inline
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=rgzm-inline
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=rgzm-verbose
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=ufg-muenster-inline
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=ufg-muenster-numeric
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=ufg-muenster-verbose
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
\ifuselabeltitle{true}{false}#*
#endif

#ifOption:style=volkskunde
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=zaak
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

#ifOption:style=zaes
#include:biblatex-archaeology
\archaeobibstyletitle#*
\archaeocitestyletitle#*
#endif

### biblatex-apa v9.15 ###
#ifOption:style=apa
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
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
\nptextcites(post){bibid}{bibid}#*C
\nptextcites(pre)(post){bibid}{bibid}#*C
\nptextcites(pre)(post)[post]{bibid}[post]{bibid}#*C
\nptextcites[post]{bibid}[post]{bibid}#*C
\nptextcites[pre][post]{bibid}[pre][post]{bibid}#*C
\nptextcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#*C
#endif

### biblatex-arthistory-bonn v1.2 ###
#ifOption:style=arthistory-bonn
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from arthistory-bonn.bbx
width=##L
publisher#true,false
jstor#true,false
urn#true,false
arthist#true,false
enddot#true,false
pagesfull#true,false
# from arthistory-bonn.cbx
firstcitefull#true,false
allnamesfamilygiven#true,false
namelinked#true,false
#endkeyvals
# from arthistory-bonn.bbx
#include:csquotes
\arthistoryversion#S
\arthistorydate#S
\labwidthsameline#*
\titleaddondelim#*
\volnumdelim#*
\jourvoldelim#*
\volissuedelim#*
\exhibbibdaterangesep#*
# from arthistory-bonn.cbx
#include:xpatch
#endif

### biblatex-bath v6.0 ###
#ifOption:style=bath
# from bath.bbx
#include:xpatch
#include:xstring
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
nonodate#true,false
#endkeyvals
\Version#S
\dononameyeardelim#*
\mknoyeardaterangefull{arg1}{arg2}#*
\mknoyeardaterangetrunc{arg1}{arg2}#*
\ifrelatedloop{true}{false}#*
#endif

### biblatex-caspervector v0.3.5 ###
#ifOption:style=caspervector
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
utf8#true,false
gbk#true,false
cparen#true,false
#endkeyvals
#endif

#ifOption:style=caspervector-ay
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
utf8#true,false
gbk#true,false
cparen#true,false
#endkeyvals
#endif

### biblatex-chem v1.1z ###
#ifOption:style=chem-acs
# from chem-acs.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articletitle#true,false
chaptertitle#true,false
pageranges#true,false
biblabel=#parens,brackets,plain,dot
#endkeyvals
#endif

#ifOption:style=chem-angew
# from chem-angew.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articletitle#true,false
chaptertitle#true,false
pageranges#true,false
biblabel=#parens,brackets,plain,dot
#endkeyvals
\mkbibnocomma{arg}#*
# from chem-angew.cbx
\mkbibsuperbracket{arg}#*
#endif

#ifOption:style=chem-biochem
# from chem-biochem.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articletitle#true,false
chaptertitle#true,false
pageranges#true,false
biblabel=#parens,brackets,plain,dot
#endkeyvals
#endif

#ifOption:style=chem-rsc
# from chem-rsc.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articletitle#true,false
chaptertitle#true,false
pageranges#true,false
biblabel=#parens,brackets,plain,dot
#endkeyvals
\mkgroupeddigits{arg}#*
#endif

### biblatex-claves v1.2.0 ###
#ifOption:bibstyle=claves
#include:xpatch
\AddBiblatexClavis{abbrev}
\multiclavesseparator#*
\clavisseparator#*
\clavisformat{text}#*
\citeallclaves
\clavesadddashinset
#endif

### biblatex-dw v1.7 ###
#ifOption:style=authortitle-dw
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from standard-dw.bbx
acronyms#true,false
shorthandinbib#true,false
shorthandwidth=##L
shortjournal#true,false
terselos#true,false
xref#true,false
pagetotal#true,false
journalnumber=#standard,afteryear,date
bernhard#true,false
series=#standard,afteryear,beforeedition
seriesformat=#standard,parens
# from authortitle-dw.bbx
annotation#true,false
edbyidem#true,false
editionstring#true,false
edsuper#true,false
idembib#true,false
library#true,false
nolocation#true,false
nopublisher#true,false
oldauthor#true,false
origfields#true,false
pseudoauthor#true,false
origfieldsformat=#parens,brackets,punct
namefont=#smallcaps,italic,bold,normal
firstnamefont=#smallcaps,italic,bold,normal
idemfont=#smallcaps,italic,bold,normal
ibidemfont=#smallcaps,italic,bold,normal
idembibformat=#idem,dash
editorstring=#parens,brackets,normal
editorstringfont=#normal,namefont
# from standard-dw.cbx
citedas#true,false
edstringincitations#true,false
omiteditor#true,false
shorthandibid#true,false
citeauthor=#namefont,namefontfoot,normalfont
citeauthorname=#normal,firstfull,full
ibidpage#true,false
pageref#true,false
citepages=#permit,suppress,omit,separate
# from authortitle-dw.cbx
addyear#true,false
firstfull#true,false
inreference=#normal,full
#endkeyvals
# from standard-dw.bbx
\shorthandsep#*
\jourvolstring#*
\jourvolnumsep#*
\journumstring#*
\seriespunct#*
\sernumstring#*
\shorthandpunct#*
\shorthandinbibpunct#*
# from authortitle-dw.bbx
\titleaddonpunct#*
\locationdatepunct#*
\locationpublisherpunct#*
\publisherdatepunct#*
\origfieldspunct#*
\bibleftpseudo#*
\bibrightpseudo#*
\bibrevsdnamedelim#*
\bibmultinamedelim#*
\bibfinalnamedelim#*
\annotationfont#*
\libraryfont#*
\mkidem{arg}#*
# from standard-dw.cbx
\citenamepunct#*
\citerevsdnamedelim#*
\citemultinamedelim#*
\citefinalnamedelim#*
\textcitesdelim#*
\mkibid{arg}#*
# from authortitle-dw.cbx
\titleyeardelim#*
#endif

#ifOption:style=footnote-dw
# loads authortitle-dw.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from standard-dw.bbx
acronyms#true,false
shorthandinbib#true,false
shorthandwidth=##L
shortjournal#true,false
terselos#true,false
xref#true,false
pagetotal#true,false
journalnumber=#standard,afteryear,date
bernhard#true,false
series=#standard,afteryear,beforeedition
seriesformat=#standard,parens
# from authortitle-dw.bbx
annotation#true,false
edbyidem#true,false
editionstring#true,false
edsuper#true,false
idembib#true,false
library#true,false
nolocation#true,false
nopublisher#true,false
oldauthor#true,false
origfields#true,false
pseudoauthor#true,false
origfieldsformat=#parens,brackets,punct
namefont=#smallcaps,italic,bold,normal
firstnamefont=#smallcaps,italic,bold,normal
idemfont=#smallcaps,italic,bold,normal
ibidemfont=#smallcaps,italic,bold,normal
idembibformat=#idem,dash
editorstring=#parens,brackets,normal
editorstringfont=#normal,namefont
# from standard-dw.cbx
citedas#true,false
edstringincitations#true,false
omiteditor#true,false
shorthandibid#true,false
citeauthor=#namefont,namefontfoot,normalfont
citeauthorname=#normal,firstfull,full
ibidpage#true,false
pageref#true,false
citepages=#permit,suppress,omit,separate
#endkeyvals
# from standard-dw.bbx
\shorthandsep#*
\jourvolstring#*
\jourvolnumsep#*
\journumstring#*
\seriespunct#*
\sernumstring#*
\shorthandpunct#*
\shorthandinbibpunct#*
# from authortitle-dw.bbx
\titleaddonpunct#*
\locationdatepunct#*
\locationpublisherpunct#*
\publisherdatepunct#*
\origfieldspunct#*
\bibleftpseudo#*
\bibrightpseudo#*
\bibrevsdnamedelim#*
\bibmultinamedelim#*
\bibfinalnamedelim#*
\annotationfont#*
\libraryfont#*
\mkidem{arg}#*
# from standard-dw.cbx
\citenamepunct#*
\citerevsdnamedelim#*
\citemultinamedelim#*
\citefinalnamedelim#*
\textcitesdelim#*
\mkibid{arg}#*
# from footnote-dw.cbx
\mkfootnotecite{arg}#*
\mkparencite{arg}#*
\footnotecheck#*
#endif

### biblatex-enc v1.0 ###
#ifOption:style=enc
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from enc.bbx
annotatedBibliography#true,false
# from enc.cbx
postnote=#afterparen,inparen
#endkeyvals
# from enc.bbx
\thebibitem#*
\thelositem#*
\begin{theshorthands}
\end{theshorthands}
# from enc.cbx
\mkibid{arg}#*
#endif

### biblatex-ext v0.16 ###
# all ext- styles load ext-biblatex-aux.def and ext-standard.bbx
#ifOption:style=ext-numeric
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-numeric-comp
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-numeric-verb
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-alphabetic
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-alphabetic-verb
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

# all ext-authoryear- styles load ext-authoryear-common.bbx which loads ext-dashed-common.bbx
#ifOption:style=ext-authoryear
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authoryear-comp
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authoryear-ibid
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authoryear-ecomp
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authoryear-iecomp
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authoryear-terse
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authoryear-tcomp
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authoryear-tecomp
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authoryear-ticomp
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authoryear-tiecomp
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

# all ext-authortitle- styles load ext-authortitle-common.bbx which loads ext-dashed-common.bbx
#ifOption:style=ext-authortitle
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authortitle-comp
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authortitle-ibid
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authortitle-icomp
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authortitle-terse
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authortitle-tcomp
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authortitle-ticomp
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-verbose
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-verbose-ibid
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-verbose-note
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-verbose-inote
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-verbose-trad1
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-verbose-trad2
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-verbose-trad3
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

# all ext-authornumber- styles load ext-authortitle-common.bbx which loads ext-dashed-common.bbx
#ifOption:style=ext-authornumber
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authornumber
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authornumber-comp
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authornumber-ecomp
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authornumber-terse
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authornumber-tcomp
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

#ifOption:style=ext-authornumber-tecomp
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

### biblatex-fiwi v1.7 ###
#ifOption:style=fiwi
#include:ragged2e
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from fiwi.bbx
ignoreaddendum=#true,false,cite,bib,both
ignoreforeword=#true,false,cite,bib,both
ignoreafterword=#true,false,cite,bib,both
ignoreintroduction=#true,false,cite,bib,both
ignoreparatext=#true,false,cite,bib,both
publisher#true,false
parensvolume#true,false
script#true,false
actor#true,false
ignorearticle#true,false
partofcited#true,false
germ#true,false
translatedas#true,false
directorreplace#true,false
noseries#true,false
series#true,false
nopublisher#true,false
parensfilmnote#true,false
filmruntime#true,false
citeprefix#true,false
yearatbeginning#true,false
origyearwithyear#true,false
origyearsuperscript#true,false
pages=#true,false,cite,bib,both
origcite=#true,false,superscript
# from fiwi.cbx
filmindex=#true,complete
splitfilmindex#true,false
titleindex=#true,subitem,both
fullcitefilm#true,false
compactcite#true,false
citefilm=#normal,country,full,complete
xindy#true,false
#endkeyvals
# from fiwi.bbx
\filmruntime#*
\nopublisher#*
\noseries#*
\nociteprefix#*
\ignoreaddendumtrue
\ignoreaddendumfalse
\ignoreforewordtrue
\ignoreforewordfalse
\ignoreafterwordtrue
\ignoreafterwordfalse
\ignoreintroductiontrue
\ignoreintroductionfalse
\ignorepublisherfalse
\ignorepublishertrue
\ignoreaddresstrue
\ignoreaddressfalse
\ignorelocationtrue
\ignorelocationfalse
\ifpseudo{true}{false}#*
\mkfinalnamedelimfirst{text}#*
\mkibid{text}#*
\film{text}
# from fiwi.cbx
\fullcitefilm#*
\completecitefilm#*
\sortentry{arg}#*
\xindy#*
\citets{bibid}{bibid}#*C
\citets(post){bibid}{bibid}#*C
\citets(pre)(post){bibid}{bibid}#*C
\citets(pre)(post)[post]{bibid}[post]{bibid}#*C
\citets[post]{bibid}[post]{bibid}#*C
\citets[pre][post]{bibid}[pre][post]{bibid}#*C
\citets(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#*C
\Citets{bibid}{bibid}#*C
\Citets(post){bibid}{bibid}#*C
\Citets(pre)(post){bibid}{bibid}#*C
\Citets(pre)(post)[post]{bibid}[post]{bibid}#*C
\Citets[post]{bibid}[post]{bibid}#*C
\Citets[pre][post]{bibid}[pre][post]{bibid}#*C
\Citets(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#*C
\citealts{bibid}{bibid}#*C
\citealts(post){bibid}{bibid}#*C
\citealts(pre)(post){bibid}{bibid}#*C
\citealts(pre)(post)[post]{bibid}[post]{bibid}#*C
\citealts[post]{bibid}[post]{bibid}#*C
\citealts[pre][post]{bibid}[pre][post]{bibid}#*C
\citealts(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#*C
\Citealts{bibid}{bibid}#*C
\Citealts(post){bibid}{bibid}#*C
\Citealts(pre)(post){bibid}{bibid}#*C
\Citealts(pre)(post)[post]{bibid}[post]{bibid}#*C
\Citealts[post]{bibid}[post]{bibid}#*C
\Citealts[pre][post]{bibid}[pre][post]{bibid}#*C
\Citealts(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#*C
\mkbibindextruename{arg1}{arg2}{arg3}{arg4}#*
\inparencite{bibid}#C
\inparencite[postnote]{bibid}#C
\inparencite[prenote][postnote]{bibid}#C
\citealtnoibidem{bibid}#*C
\citealtnoibidem[postnote]{bibid}#*C
\citealtnoibidem[prenote][postnote]{bibid}#*C
\citetnoibidem{bibid}#*C
\citetnoibidem[postnote]{bibid}#*C
\citetnoibidem[prenote][postnote]{bibid}#*C
\citeepisode{bibid}#C
\citefilm{bibid}#C
\citecfilm{bibid}#C
\citefullfilm{bibid}#C
\citefilmnoindex{bibid}#*C
#endif

#ifOption:style=fiwi2
# from fiwi2.bbx
# loads fiwi-yearbeginning.bbx (which loads fiwi.bbx)
#include:ragged2e
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from fiwi.bbx
ignoreaddendum=#true,false,cite,bib,both
ignoreforeword=#true,false,cite,bib,both
ignoreafterword=#true,false,cite,bib,both
ignoreintroduction=#true,false,cite,bib,both
ignoreparatext=#true,false,cite,bib,both
publisher#true,false
parensvolume#true,false
script#true,false
actor#true,false
ignorearticle#true,false
partofcited#true,false
germ#true,false
translatedas#true,false
directorreplace#true,false
noseries#true,false
series#true,false
nopublisher#true,false
parensfilmnote#true,false
filmruntime#true,false
citeprefix#true,false
yearatbeginning#true,false
origyearwithyear#true,false
origyearsuperscript#true,false
pages=#true,false,cite,bib,both
origcite=#true,false,superscript
# from fiwi2.cbx (loads fiwi.cbx)
filmindex=#true,complete
splitfilmindex#true,false
titleindex=#true,subitem,both
fullcitefilm#true,false
compactcite#true,false
citefilm=#normal,country,full,complete
xindy#true,false
#endkeyvals
# from fiwi.bbx
\filmruntime#*
\nopublisher#*
\noseries#*
\nociteprefix#*
\ignoreaddendumtrue
\ignoreaddendumfalse
\ignoreforewordtrue
\ignoreforewordfalse
\ignoreafterwordtrue
\ignoreafterwordfalse
\ignoreintroductiontrue
\ignoreintroductionfalse
\ignorepublisherfalse
\ignorepublishertrue
\ignoreaddresstrue
\ignoreaddressfalse
\ignorelocationtrue
\ignorelocationfalse
\ifpseudo{true}{false}#*
\mkfinalnamedelimfirst{text}#*
\mkibid{text}#*
\film{text}
# from fiwi2.cbx (loads fiwi.cbx)
\fullcitefilm#*
\completecitefilm#*
\sortentry{arg}#*
\xindy#*
\citets{bibid}{bibid}#*C
\citets(post){bibid}{bibid}#*C
\citets(pre)(post){bibid}{bibid}#*C
\citets(pre)(post)[post]{bibid}[post]{bibid}#*C
\citets[post]{bibid}[post]{bibid}#*C
\citets[pre][post]{bibid}[pre][post]{bibid}#*C
\citets(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#*C
\Citets{bibid}{bibid}#*C
\Citets(post){bibid}{bibid}#*C
\Citets(pre)(post){bibid}{bibid}#*C
\Citets(pre)(post)[post]{bibid}[post]{bibid}#*C
\Citets[post]{bibid}[post]{bibid}#*C
\Citets[pre][post]{bibid}[pre][post]{bibid}#*C
\Citets(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#*C
\citealts{bibid}{bibid}#*C
\citealts(post){bibid}{bibid}#*C
\citealts(pre)(post){bibid}{bibid}#*C
\citealts(pre)(post)[post]{bibid}[post]{bibid}#*C
\citealts[post]{bibid}[post]{bibid}#*C
\citealts[pre][post]{bibid}[pre][post]{bibid}#*C
\citealts(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#*C
\Citealts{bibid}{bibid}#*C
\Citealts(post){bibid}{bibid}#*C
\Citealts(pre)(post){bibid}{bibid}#*C
\Citealts(pre)(post)[post]{bibid}[post]{bibid}#*C
\Citealts[post]{bibid}[post]{bibid}#*C
\Citealts[pre][post]{bibid}[pre][post]{bibid}#*C
\Citealts(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#*C
\mkbibindextruename{arg1}{arg2}{arg3}{arg4}#*
\inparencite{bibid}#C
\inparencite[postnote]{bibid}#C
\inparencite[prenote][postnote]{bibid}#C
\citealtnoibidem{bibid}#*C
\citealtnoibidem[postnote]{bibid}#*C
\citealtnoibidem[prenote][postnote]{bibid}#*C
\citetnoibidem{bibid}#*C
\citetnoibidem[postnote]{bibid}#*C
\citetnoibidem[prenote][postnote]{bibid}#*C
\citeepisode{bibid}#C
\citefilm{bibid}#C
\citecfilm{bibid}#C
\citefullfilm{bibid}#C
\citefilmnoindex{bibid}#*C
#endif

### biblatex-gb7714-2015 v1.1i ###
#ifOption:style=gb7714-2015
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from gb7714-2015.bbx
citexref#true,false
gbmedium#true,false
gbannote#true,false
gbfieldtype#true,false
gbfnperpage#true,false
gbfootbib#true,false
gbstyle#true,false
gbtype#true,false
gbcodegbk#true,false
gbstrict#true,false
gbtitlelink#true,false
gbctexset#true,false
gbnoauthor#true,false
gbfieldstd#true,false
gbpub#true,false
gbpunctin#true,false
gblanorder=#chineseahead,englishahead,%<string%>
gbcitelocal=#gb7714-2015,chinese,english
gbbiblocal=#gb7714-2015,chinese,english
gblocal=#gb7714-2015,chinese,english
gbbiblabel=#bracket,parens,plain,dot,box,circle
gbnamefmt=#uppercase,lowercase,givenahead,familyahead,pinyin,quanpin,reverseorder
gbalign=#right,left,center,gb7714-2015,gb7714-2015ay
# from gb7714-2015.cbx
gblabelref#true,false
gbcitecomp#true,false
gbcitelabel=#bracket,parens,plain,dot,box,circle
#endkeyvals
# from gb7714-2015.bbx
#include:xstring
\versionofgbtstyle#S
\versionofbiblatex#S
\defversion{arg1}{arg2}{arg3}#S
\switchversion{arg1}{arg2}#S
\testCJKfirst{field}#*
\multivolparser{arg}#*
\multinumberparser{arg}#*
\footbibmargin#*
\footbiblabelsep#*
\execgbfootbib#*
\thegbnamefmtcase#*
\mkgbnumlabel{arg}#*
\thegbalignlabel#*
\thegbcitelocalcase#*
\thegbbiblocalcase#*
\lancnorder#S
\lanjporder#S
\lankrorder#S
\lanenorder#S
\lanfrorder#S
\lanruorder#S
\execlanodeah#*
\thelanordernum#*
\execlanodudf{string}#*
\setlocalbibstring{string}{text}
\setlocalbiblstring{string}{text}
\dealsortlan#*
\bibitemindent#*
\biblabelextend#*
\setaligngbstyle#*
\lengthid#*
\lengthlw#*
\itemcmd#*
\setaligngbstyleay#*
\publocpunct#*
\bibtitlefont#*
\bibauthorfont#*
\bibpubfont#*
\execgbfdfmtstd#*
\aftertransdelim#*
\gbcaselocalset#*
\gbpinyinlocalset#*
\gbquanpinlocalset#*
\defdoublelangentry{match}{fieldvalue}
\entrykeya#S
\entrykeyb#S
\userfieldabcde#S
# from gb7714-2015.cbx
\mkbibleftborder#*
\mkbibrightborder#*
\mkbibsuperbracket{text}#*
\mkbibsuperscriptusp{text}#*
\upcite{bibid}#*C
\upcite[postnote]{bibid}#*C
\upcite[prenote][postnote]{bibid}#*C
\pagescite{bibid}#C
\pagescite[postnote]{bibid}#C
\pagescite[prenote][postnote]{bibid}#C
\yearpagescite{bibid}#C
\yearpagescite[postnote]{bibid}#C
\yearpagescite[prenote][postnote]{bibid}#C
\yearcite{bibid}#C
\yearcite[postnote]{bibid}#C
\yearcite[prenote][postnote]{bibid}#C
\authornumcite{bibid}#C
\authornumcite[postnote]{bibid}#C
\authornumcite[prenote][postnote]{bibid}#C
\citet{bibid}#*C
\citet[postnote]{bibid}#*C
\citet[prenote][postnote]{bibid}#*C
\citep{bibid}#*C
\citep[postnote]{bibid}#*C
\citep[prenote][postnote]{bibid}#*C
\citetns{bibid}#*C
\citetns[postnote]{bibid}#*C
\citetns[prenote][postnote]{bibid}#*C
\citepns{bibid}#*C
\citepns[postnote]{bibid}#*C
\citepns[prenote][postnote]{bibid}#*C
\inlinecite{bibid}#*C
\inlinecite[postnote]{bibid}#*C
\inlinecite[prenote][postnote]{bibid}#*C
\citec{bibid}#C
\citec[postnote]{bibid}#C
\citec[prenote][postnote]{bibid}#C
\citecs{bibid}{bibid}#C
\citecs(post){bibid}{bibid}#*C
\citecs(pre)(post){bibid}{bibid}#C
\citecs(pre)(post)[post]{bibid}[post]{bibid}#*C
\citecs[post]{bibid}[post]{bibid}#*C
\citecs[pre][post]{bibid}[pre][post]{bibid}#*C
\citecs(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\authornumcites{bibid}{bibid}#C
\authornumcites(post){bibid}{bibid}#*C
\authornumcites(pre)(post){bibid}{bibid}#C
\authornumcites(pre)(post)[post]{bibid}[post]{bibid}#*C
\authornumcites[post]{bibid}[post]{bibid}#*C
\authornumcites[pre][post]{bibid}[pre][post]{bibid}#*C
\authornumcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
#endif

#ifOption:style=gb7714-2015ay
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from gb7714-2015ay.bbx
gbmedium#true,false
gbannote#true,false
gbfieldtype#true,false
gbfnperpage#true,false
gbfootbib#true,false
gbstyle#true,false
gbtype#true,false
gbcodegbk#true,false
gbstrict#true,false
gbtitlelink#true,false
gbctexset#true,false
gbnoauthor#true,false
gbfieldstd#true,false
gbpub#true,false
gbpunctin#true,false
gblanorder=#chineseahead,englishahead,%<string%>
gbcitelocal=#gb7714-2015,chinese,english
gbbiblocal=#gb7714-2015,chinese,english
gblocal=#gb7714-2015,chinese,english
gbbiblabel=#bracket,parens,plain,dot,box,circle
gbnamefmt=#uppercase,lowercase,givenahead,familyahead,pinyin,quanpin,reverseorder
gbalign=#right,left,center,gb7714-2015,gb7714-2015ay
# from gb7714-2015ay.cbx
gblabelref#true,false
gbcitelabel=#bracket,parens,plain,dot,box,circle
#endkeyvals
# from gb7714-2015ay.bbx
#include:xstring
\versionofgbtstyle#S
\versionofbiblatex#S
\defversion{arg1}{arg2}{arg3}#S
\switchversion{arg1}{arg2}#S
\testCJKfirst{field}#*
\multivolparser{arg}#*
\multinumberparser{arg}#*
\footbibmargin#*
\footbiblabelsep#*
\execgbfootbib#*
\thegbnamefmtcase#*
\mkgbnumlabel{arg}#*
\thegbalignlabel#*
\thegbcitelocalcase#*
\thegbbiblocalcase#*
\lancnorder#S
\lanjporder#S
\lankrorder#S
\lanenorder#S
\lanfrorder#S
\lanruorder#S
\execlanodeah#*
\thelanordernum#*
\execlanodudf{string}#*
\setlocalbibstring{string}{text}
\setlocalbiblstring{string}{text}
\dealnoathor#*
\dealsortlan#*
\bibitemindent#*
\therefnumeric#*
\biblabelextend#*
\setaligngbnumeric#*
\setaligngbstyle#*
\lengthid#*
\lengthlw#*
\itemcmd#*
\publocpunct#*
\bibtitlefont#*
\bibauthorfont#*
\bibpubfont#*
\execgbfdfmtstd#*
\aftertransdelim#*
\gbcaselocalset#*
\gbpinyinlocalset#*
\gbquanpinlocalset#*
\defdoublelangentry{match}{fieldvalue}
\entrykeya#S
\entrykeyb#S
\userfieldabcde#S
# from gb7714-2015ay.cbx
\mkbibleftborder#*
\mkbibrightborder#*
\compextradelim#*
\upcite{bibid}#*C
\upcite[postnote]{bibid}#*C
\upcite[prenote][postnote]{bibid}#*C
\pagescite{bibid}#C
\pagescite[postnote]{bibid}#C
\pagescite[prenote][postnote]{bibid}#C
\yearpagescite{bibid}#C
\yearpagescite[postnote]{bibid}#C
\yearpagescite[prenote][postnote]{bibid}#C
\yearcite{bibid}#C
\yearcite[postnote]{bibid}#C
\yearcite[prenote][postnote]{bibid}#C
\authornumcite{bibid}#C
\authornumcite[postnote]{bibid}#C
\authornumcite[prenote][postnote]{bibid}#C
\citet{bibid}#*C
\citet[postnote]{bibid}#*C
\citet[prenote][postnote]{bibid}#*C
\citep{bibid}#*C
\citep[postnote]{bibid}#*C
\citep[prenote][postnote]{bibid}#*C
\citets{bibid}{bibid}#*C
\citets(post){bibid}{bibid}#*C
\citets(pre)(post){bibid}{bibid}#*C
\citets(pre)(post)[post]{bibid}[post]{bibid}#*C
\citets[post]{bibid}[post]{bibid}#*C
\citets[pre][post]{bibid}[pre][post]{bibid}#*C
\citets(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#*C
\citetns{bibid}#*C
\citetns[postnote]{bibid}#*C
\citetns[prenote][postnote]{bibid}#*C
\citepns{bibid}#*C
\citepns[postnote]{bibid}#*C
\citepns[prenote][postnote]{bibid}#*C
\inlinecite{bibid}#*C
\inlinecite[postnote]{bibid}#*C
\inlinecite[prenote][postnote]{bibid}#*C
\citec{bibid}#C
\citec[postnote]{bibid}#C
\citec[prenote][postnote]{bibid}#C
\citecs{bibid}{bibid}#C
\citecs(post){bibid}{bibid}#*C
\citecs(pre)(post){bibid}{bibid}#C
\citecs(pre)(post)[post]{bibid}[post]{bibid}#*C
\citecs[post]{bibid}[post]{bibid}#*C
\citecs[pre][post]{bibid}[pre][post]{bibid}#*C
\citecs(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\authornumcites{bibid}{bibid}#C
\authornumcites(post){bibid}{bibid}#*C
\authornumcites(pre)(post){bibid}{bibid}#C
\authornumcites(pre)(post)[post]{bibid}[post]{bibid}#*C
\authornumcites[post]{bibid}[post]{bibid}#*C
\authornumcites[pre][post]{bibid}[pre][post]{bibid}#*C
\authornumcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
#endif

#ifOption:style=gb7714-2015ms
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from gb7714-2015ms.bbx
gbmedium#true,false
gbannote#true,false
gbfieldtype#true,false
gbfnperpage#true,false
gbfootbib#true,false
gbstyle#true,false
gbtype#true,false
gbcodegbk#true,false
gbstrict#true,false
gbtitlelink#true,false
gbctexset#true,false
gbnoauthor#true,false
gbfieldstd#true,false
gbpub#true,false
gbpunctin#true,false
gblanorder=#chineseahead,englishahead,%<string%>
gbcitelocal=#gb7714-2015,chinese,english
gbbiblocal=#gb7714-2015,chinese,english
gblocal=#gb7714-2015,chinese,english
gbbiblabel=#bracket,parens,plain,dot,box,circle
gbnamefmt=#uppercase,lowercase,givenahead,familyahead,pinyin,quanpin,reverseorder
gbalign=#right,left,center,gb7714-2015,gb7714-2015ay
# from gb7714-2015ms.cbx (loads gb7714-2015.cbx)
gblabelref#true,false
gbcitecomp#true,false
gbcitelabel=#bracket,parens,plain,dot,box,circle
#endkeyvals
# from gb7714-2015ms.bbx
#include:xstring
\versionofgbtstyle#S
\versionofbiblatex#S
\testCJKfirst{field}#*
\multivolparser{arg}#*
\multinumberparser{arg}#*
\footbibmargin#*
\footbiblabelsep#*
\execgbfootbib#*
\thegbnamefmtcase#*
\mkgbnumlabel{arg}#*
\thegbalignlabel#*
\thegbcitelocalcase#*
\thegbbiblocalcase#*
\setlocalbibstring{string}{text}
\setlocalbiblstring{string}{text}
\bibitemindent#*
\biblabelextend#*
\setaligngbstyle#*
\lengthid#*
\lengthlw#*
\itemcmd#*
\setaligngbstyleay#*
\publocpunct#*
\bibtitlefont#*
\bibauthorfont#*
\bibpubfont#*
\gbcaselocalset#*
\gbpinyinlocalset#*
\gbquanpinlocalset#*
\defdoublelangentry{match}{fieldvalue}
\entrykeya#S
\entrykeyb#S
\userfieldabcde#S
\localsetchinesecode#*
\aftertransdelim#*
# from gb7714-2015ms.cbx (loads gb7714-2015.cbx)
\mkbibleftborder#*
\mkbibrightborder#*
\mkbibsuperbracket{text}#*
\mkbibsuperscriptusp{text}#*
\upcite{bibid}#*C
\upcite[postnote]{bibid}#*C
\upcite[prenote][postnote]{bibid}#*C
\pagescite{bibid}#C
\pagescite[postnote]{bibid}#C
\pagescite[prenote][postnote]{bibid}#C
\yearpagescite{bibid}#C
\yearpagescite[postnote]{bibid}#C
\yearpagescite[prenote][postnote]{bibid}#C
\yearcite{bibid}#C
\yearcite[postnote]{bibid}#C
\yearcite[prenote][postnote]{bibid}#C
\authornumcite{bibid}#C
\authornumcite[postnote]{bibid}#C
\authornumcite[prenote][postnote]{bibid}#C
\citet{bibid}#*C
\citet[postnote]{bibid}#*C
\citet[prenote][postnote]{bibid}#*C
\citep{bibid}#*C
\citep[postnote]{bibid}#*C
\citep[prenote][postnote]{bibid}#*C
\citetns{bibid}#*C
\citetns[postnote]{bibid}#*C
\citetns[prenote][postnote]{bibid}#*C
\citepns{bibid}#*C
\citepns[postnote]{bibid}#*C
\citepns[prenote][postnote]{bibid}#*C
\inlinecite{bibid}#*C
\inlinecite[postnote]{bibid}#*C
\inlinecite[prenote][postnote]{bibid}#*C
\citec{bibid}#C
\citec[postnote]{bibid}#C
\citec[prenote][postnote]{bibid}#C
\citecs{bibid}{bibid}#C
\citecs(post){bibid}{bibid}#*C
\citecs(pre)(post){bibid}{bibid}#C
\citecs(pre)(post)[post]{bibid}[post]{bibid}#*C
\citecs[post]{bibid}[post]{bibid}#*C
\citecs[pre][post]{bibid}[pre][post]{bibid}#*C
\citecs(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\authornumcites{bibid}{bibid}#C
\authornumcites(post){bibid}{bibid}#*C
\authornumcites(pre)(post){bibid}{bibid}#C
\authornumcites(pre)(post)[post]{bibid}[post]{bibid}#*C
\authornumcites[post]{bibid}[post]{bibid}#*C
\authornumcites[pre][post]{bibid}[pre][post]{bibid}#*C
\authornumcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
#endif

#ifOption:style=gb7714-2015mx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from gb7714-2015mx.bbx
gbmedium#true,false
gbannote#true,false
gbfieldtype#true,false
gbfnperpage#true,false
gbfootbib#true,false
gbstyle#true,false
gbtype#true,false
gbcodegbk#true,false
gbstrict#true,false
gbtitlelink#true,false
gbctexset#true,false
gbnoauthor#true,false
gbfieldstd#true,false
gbpub#true,false
gbpunctin#true,false
gblanorder=#chineseahead,englishahead,%<string%>
gbcitelocal=#gb7714-2015,chinese,english
gbbiblocal=#gb7714-2015,chinese,english
gblocal=#gb7714-2015,chinese,english
gbbiblabel=#bracket,parens,plain,dot,box,circle
gbnamefmt=#uppercase,lowercase,givenahead,familyahead,pinyin,quanpin,reverseorder
gbalign=#right,left,center,gb7714-2015,gb7714-2015ay
#endkeyvals
# from gb7714-2015mx.bbx
#include:xstring
\versionofgbtstyle#S
\versionofbiblatex#S
\testCJKfirst{field}#*
\multivolparser{arg}#*
\multinumberparser{arg}#*
\footbibmargin#*
\footbiblabelsep#*
\execgbfootbib#*
\thegbnamefmtcase#*
\mkgbnumlabel{arg}#*
\thegbalignlabel#*
\thegbcitelocalcase#*
\thegbbiblocalcase#*
\lancnorder#S
\lanjporder#S
\lankrorder#S
\lanenorder#S
\lanfrorder#S
\lanruorder#S
\execlanodeah#*
\thelanordernum#*
\execlanodudf{string}#*
\setlocalbibstring{string}{text}
\setlocalbiblstring{string}{text}
\dealnoathor#*
\dealsortlan#*
\bibitemindent#*
\biblabelextend#*
\setaligngbstyle#*
\lengthid#*
\lengthlw#*
\itemcmd#*
\setaligngbstyleay#*
\publocpunct#*
\bibtitlefont#*
\bibauthorfont#*
\bibpubfont#*
\gbcaselocalset#*
\gbpinyinlocalset#*
\gbquanpinlocalset#*
\defdoublelangentry{match}{fieldvalue}
\entrykeya#S
\entrykeyb#S
\userfieldabcde#S
\aftertransdelim#*
\setaystylesection{number}
# from gb7714-2015mx.cbx
\mkbibsuperbracket{text}#*
\upcite{bibid}#*C
\upcite[postnote]{bibid}#*C
\upcite[prenote][postnote]{bibid}#*C
\pagescite{bibid}#C
\pagescite[postnote]{bibid}#C
\pagescite[prenote][postnote]{bibid}#C
\yearpagescite{bibid}#C
\yearpagescite[postnote]{bibid}#C
\yearpagescite[prenote][postnote]{bibid}#C
\yearcite{bibid}#C
\yearcite[postnote]{bibid}#C
\yearcite[prenote][postnote]{bibid}#C
\authornumcite{bibid}#C
\authornumcite[postnote]{bibid}#C
\authornumcite[prenote][postnote]{bibid}#C
\citet{bibid}#*C
\citet[postnote]{bibid}#*C
\citet[prenote][postnote]{bibid}#*C
\citep{bibid}#*C
\citep[postnote]{bibid}#*C
\citep[prenote][postnote]{bibid}#*C
\citetns{bibid}#*C
\citetns[postnote]{bibid}#*C
\citetns[prenote][postnote]{bibid}#*C
\citepns{bibid}#*C
\citepns[postnote]{bibid}#*C
\citepns[prenote][postnote]{bibid}#*C
\inlinecite{bibid}#*C
\inlinecite[postnote]{bibid}#*C
\inlinecite[prenote][postnote]{bibid}#*C
#endif

#ifOption:style=gb7714-CCNU
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from gb7714-CCNU.bbx (loads gb7714-2015)
CCNUpunctcn#true,false
# from gb7714-2015.bbx
citexref#true,false
gbmedium#true,false
gbannote#true,false
gbfieldtype#true,false
gbfnperpage#true,false
gbfootbib#true,false
gbstyle#true,false
gbtype#true,false
gbcodegbk#true,false
gbstrict#true,false
gbtitlelink#true,false
gbctexset#true,false
gbnoauthor#true,false
gbfieldstd#true,false
gbpub#true,false
gbpunctin#true,false
gblanorder=#chineseahead,englishahead,%<string%>
gbcitelocal=#gb7714-2015,chinese,english
gbbiblocal=#gb7714-2015,chinese,english
gblocal=#gb7714-2015,chinese,english
gbbiblabel=#bracket,parens,plain,dot,box,circle
gbnamefmt=#uppercase,lowercase,givenahead,familyahead,pinyin,quanpin,reverseorder
gbalign=#right,left,center,gb7714-2015,gb7714-2015ay
# from gb7714-CCNU.cbx (loads gb7714-2015.cbx)
gblabelref#true,false
gbcitecomp#true,false
gbcitelabel=#bracket,parens,plain,dot,box,circle
#endkeyvals
# from gb7714-CCNU.bbx (loads gb7714-2015)
\gbpunctdot#*
\gbpunctdotlanen#*
\gbpunctmark#*
\gbpunctcomma#*
\gbpunctcommalanen#*
\gbpunctcolon#*
\gbpunctcolonlanen#*
\gbpunctsemicolon#*
\gbpunctsemicolonlanen#*
\gbpunctparenl#*
\gbpunctparenr#*
\execpuncten#*
# from gb7714-2015.bbx
#include:xstring
\versionofgbtstyle#S
\versionofbiblatex#S
\defversion{arg1}{arg2}{arg3}#S
\switchversion{arg1}{arg2}#S
\testCJKfirst{field}#*
\multivolparser{arg}#*
\multinumberparser{arg}#*
\footbibmargin#*
\footbiblabelsep#*
\execgbfootbib#*
\thegbnamefmtcase#*
\mkgbnumlabel{arg}#*
\thegbalignlabel#*
\thegbcitelocalcase#*
\thegbbiblocalcase#*
\lancnorder#S
\lanjporder#S
\lankrorder#S
\lanenorder#S
\lanfrorder#S
\lanruorder#S
\execlanodeah#*
\thelanordernum#*
\execlanodudf{string}#*
\setlocalbibstring{string}{text}
\setlocalbiblstring{string}{text}
\dealsortlan#*
\bibitemindent#*
\biblabelextend#*
\setaligngbstyle#*
\lengthid#*
\lengthlw#*
\itemcmd#*
\setaligngbstyleay#*
\publocpunct#*
\bibtitlefont#*
\bibauthorfont#*
\bibpubfont#*
\execgbfdfmtstd#*
\aftertransdelim#*
\gbcaselocalset#*
\gbpinyinlocalset#*
\gbquanpinlocalset#*
\defdoublelangentry{match}{fieldvalue}
\entrykeya#S
\entrykeyb#S
\userfieldabcde#S
# from gb7714-CCNU.cbx (loads gb7714-2015.cbx)
\mkbibleftborder#*
\mkbibrightborder#*
\mkbibsuperbracket{text}#*
\mkbibsuperscriptusp{text}#*
\upcite{bibid}#*C
\upcite[postnote]{bibid}#*C
\upcite[prenote][postnote]{bibid}#*C
\pagescite{bibid}#C
\pagescite[postnote]{bibid}#C
\pagescite[prenote][postnote]{bibid}#C
\yearpagescite{bibid}#C
\yearpagescite[postnote]{bibid}#C
\yearpagescite[prenote][postnote]{bibid}#C
\yearcite{bibid}#C
\yearcite[postnote]{bibid}#C
\yearcite[prenote][postnote]{bibid}#C
\authornumcite{bibid}#C
\authornumcite[postnote]{bibid}#C
\authornumcite[prenote][postnote]{bibid}#C
\citet{bibid}#*C
\citet[postnote]{bibid}#*C
\citet[prenote][postnote]{bibid}#*C
\citep{bibid}#*C
\citep[postnote]{bibid}#*C
\citep[prenote][postnote]{bibid}#*C
\citetns{bibid}#*C
\citetns[postnote]{bibid}#*C
\citetns[prenote][postnote]{bibid}#*C
\citepns{bibid}#*C
\citepns[postnote]{bibid}#*C
\citepns[prenote][postnote]{bibid}#*C
\inlinecite{bibid}#*C
\inlinecite[postnote]{bibid}#*C
\inlinecite[prenote][postnote]{bibid}#*C
\citec{bibid}#C
\citec[postnote]{bibid}#C
\citec[prenote][postnote]{bibid}#C
\citecs{bibid}{bibid}#C
\citecs(post){bibid}{bibid}#*C
\citecs(pre)(post){bibid}{bibid}#C
\citecs(pre)(post)[post]{bibid}[post]{bibid}#*C
\citecs[post]{bibid}[post]{bibid}#*C
\citecs[pre][post]{bibid}[pre][post]{bibid}#*C
\citecs(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\authornumcites{bibid}{bibid}#C
\authornumcites(post){bibid}{bibid}#*C
\authornumcites(pre)(post){bibid}{bibid}#C
\authornumcites(pre)(post)[post]{bibid}[post]{bibid}#*C
\authornumcites[post]{bibid}[post]{bibid}#*C
\authornumcites[pre][post]{bibid}[pre][post]{bibid}#*C
\authornumcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
#endif

#ifOption:style=gb7714-NWAFU
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from gb7714-NWAFU.bbx (loads gb7714-2015.bbx)
citexref#true,false
gbmedium#true,false
gbannote#true,false
gbfieldtype#true,false
gbfnperpage#true,false
gbfootbib#true,false
gbstyle#true,false
gbtype#true,false
gbcodegbk#true,false
gbstrict#true,false
gbtitlelink#true,false
gbctexset#true,false
gbnoauthor#true,false
gbfieldstd#true,false
gbpub#true,false
gbpunctin#true,false
gblanorder=#chineseahead,englishahead,%<string%>
gbcitelocal=#gb7714-2015,chinese,english
gbbiblocal=#gb7714-2015,chinese,english
gblocal=#gb7714-2015,chinese,english
gbbiblabel=#bracket,parens,plain,dot,box,circle
gbnamefmt=#uppercase,lowercase,givenahead,familyahead,pinyin,quanpin,reverseorder
gbalign=#right,left,center,gb7714-2015,gb7714-2015ay
# from gb7714-NWAFU.cbx (loads gb7714-2015ay.cbx)
gblabelref#true,false
gbcitelabel=#bracket,parens,plain,dot,box,circle
#endkeyvals
# from gb7714-NWAFU.bbx (loads gb7714-2015.bbx)
\nwafubibfont#*
# from gb7714-2015.bbx
#include:xstring
\versionofgbtstyle#S
\versionofbiblatex#S
\defversion{arg1}{arg2}{arg3}#S
\switchversion{arg1}{arg2}#S
\testCJKfirst{field}#*
\multivolparser{arg}#*
\multinumberparser{arg}#*
\footbibmargin#*
\footbiblabelsep#*
\execgbfootbib#*
\thegbnamefmtcase#*
\mkgbnumlabel{arg}#*
\thegbalignlabel#*
\thegbcitelocalcase#*
\thegbbiblocalcase#*
\lancnorder#S
\lanjporder#S
\lankrorder#S
\lanenorder#S
\lanfrorder#S
\lanruorder#S
\execlanodeah#*
\thelanordernum#*
\execlanodudf{string}#*
\setlocalbibstring{string}{text}
\setlocalbiblstring{string}{text}
\dealsortlan#*
\bibitemindent#*
\biblabelextend#*
\setaligngbstyle#*
\lengthid#*
\lengthlw#*
\itemcmd#*
\setaligngbstyleay#*
\publocpunct#*
\bibtitlefont#*
\bibauthorfont#*
\bibpubfont#*
\execgbfdfmtstd#*
\aftertransdelim#*
\gbcaselocalset#*
\gbpinyinlocalset#*
\gbquanpinlocalset#*
\defdoublelangentry{match}{fieldvalue}
\entrykeya#S
\entrykeyb#S
\userfieldabcde#S
# from gb7714-NWAFU.cbx (loads gb7714-2015ay.cbx)
\mkbibleftborder#*
\mkbibrightborder#*
\compextradelim#*
\upcite{bibid}#*C
\upcite[postnote]{bibid}#*C
\upcite[prenote][postnote]{bibid}#*C
\pagescite{bibid}#C
\pagescite[postnote]{bibid}#C
\pagescite[prenote][postnote]{bibid}#C
\yearpagescite{bibid}#C
\yearpagescite[postnote]{bibid}#C
\yearpagescite[prenote][postnote]{bibid}#C
\yearcite{bibid}#C
\yearcite[postnote]{bibid}#C
\yearcite[prenote][postnote]{bibid}#C
\authornumcite{bibid}#C
\authornumcite[postnote]{bibid}#C
\authornumcite[prenote][postnote]{bibid}#C
\citet{bibid}#*C
\citet[postnote]{bibid}#*C
\citet[prenote][postnote]{bibid}#*C
\citep{bibid}#*C
\citep[postnote]{bibid}#*C
\citep[prenote][postnote]{bibid}#*C
\citets{bibid}{bibid}#*C
\citets(post){bibid}{bibid}#*C
\citets(pre)(post){bibid}{bibid}#*C
\citets(pre)(post)[post]{bibid}[post]{bibid}#*C
\citets[post]{bibid}[post]{bibid}#*C
\citets[pre][post]{bibid}[pre][post]{bibid}#*C
\citets(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#*C
\citetns{bibid}#*C
\citetns[postnote]{bibid}#*C
\citetns[prenote][postnote]{bibid}#*C
\citepns{bibid}#*C
\citepns[postnote]{bibid}#*C
\citepns[prenote][postnote]{bibid}#*C
\inlinecite{bibid}#*C
\inlinecite[postnote]{bibid}#*C
\inlinecite[prenote][postnote]{bibid}#*C
\citec{bibid}#C
\citec[postnote]{bibid}#C
\citec[prenote][postnote]{bibid}#C
\citecs{bibid}{bibid}#C
\citecs(post){bibid}{bibid}#*C
\citecs(pre)(post){bibid}{bibid}#C
\citecs(pre)(post)[post]{bibid}[post]{bibid}#*C
\citecs[post]{bibid}[post]{bibid}#*C
\citecs[pre][post]{bibid}[pre][post]{bibid}#*C
\citecs(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\authornumcites{bibid}{bibid}#C
\authornumcites(post){bibid}{bibid}#*C
\authornumcites(pre)(post){bibid}{bibid}#C
\authornumcites(pre)(post)[post]{bibid}[post]{bibid}#*C
\authornumcites[post]{bibid}[post]{bibid}#*C
\authornumcites[pre][post]{bibid}[pre][post]{bibid}#*C
\authornumcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
#endif

#ifOption:style=gb7714-SEU
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from gb7714-SEU.bbx (loads gb7714-2015)
citexref#true,false
gbmedium#true,false
gbannote#true,false
gbfieldtype#true,false
gbfnperpage#true,false
gbfootbib#true,false
gbstyle#true,false
gbtype#true,false
gbcodegbk#true,false
gbstrict#true,false
gbtitlelink#true,false
gbctexset#true,false
gbnoauthor#true,false
gbfieldstd#true,false
gbpub#true,false
gbpunctin#true,false
gblanorder=#chineseahead,englishahead,%<string%>
gbcitelocal=#gb7714-2015,chinese,english
gbbiblocal=#gb7714-2015,chinese,english
gblocal=#gb7714-2015,chinese,english
gbbiblabel=#bracket,parens,plain,dot,box,circle
gbnamefmt=#uppercase,lowercase,givenahead,familyahead,pinyin,quanpin,reverseorder
gbalign=#right,left,center,gb7714-2015,gb7714-2015ay
# from gb7714-SEU.cbx (loads gb7714-2015.cbx)
gblabelref#true,false
gbcitecomp#true,false
gbcitelabel=#bracket,parens,plain,dot,box,circle
#endkeyvals
# from gb7714-SEU.bbx (loads gb7714-2015)
#include:xstring
\versionofgbtstyle#S
\versionofbiblatex#S
\defversion{arg1}{arg2}{arg3}#S
\switchversion{arg1}{arg2}#S
\testCJKfirst{field}#*
\multivolparser{arg}#*
\multinumberparser{arg}#*
\footbibmargin#*
\footbiblabelsep#*
\execgbfootbib#*
\thegbnamefmtcase#*
\mkgbnumlabel{arg}#*
\thegbalignlabel#*
\thegbcitelocalcase#*
\thegbbiblocalcase#*
\lancnorder#S
\lanjporder#S
\lankrorder#S
\lanenorder#S
\lanfrorder#S
\lanruorder#S
\execlanodeah#*
\thelanordernum#*
\execlanodudf{string}#*
\setlocalbibstring{string}{text}
\setlocalbiblstring{string}{text}
\dealsortlan#*
\bibitemindent#*
\biblabelextend#*
\setaligngbstyle#*
\lengthid#*
\lengthlw#*
\itemcmd#*
\setaligngbstyleay#*
\publocpunct#*
\bibtitlefont#*
\bibauthorfont#*
\bibpubfont#*
\execgbfdfmtstd#*
\aftertransdelim#*
\gbcaselocalset#*
\gbpinyinlocalset#*
\gbquanpinlocalset#*
\defdoublelangentry{match}{fieldvalue}
\entrykeya#S
\entrykeyb#S
\userfieldabcde#S
# from gb7714-SEU.cbx (loads gb7714-2015.cbx)
\mkbibleftborder#*
\mkbibrightborder#*
\mkbibsuperbracket{text}#*
\mkbibsuperscriptusp{text}#*
\upcite{bibid}#*C
\upcite[postnote]{bibid}#*C
\upcite[prenote][postnote]{bibid}#*C
\pagescite{bibid}#C
\pagescite[postnote]{bibid}#C
\pagescite[prenote][postnote]{bibid}#C
\yearpagescite{bibid}#C
\yearpagescite[postnote]{bibid}#C
\yearpagescite[prenote][postnote]{bibid}#C
\yearcite{bibid}#C
\yearcite[postnote]{bibid}#C
\yearcite[prenote][postnote]{bibid}#C
\authornumcite{bibid}#C
\authornumcite[postnote]{bibid}#C
\authornumcite[prenote][postnote]{bibid}#C
\citet{bibid}#*C
\citet[postnote]{bibid}#*C
\citet[prenote][postnote]{bibid}#*C
\citep{bibid}#*C
\citep[postnote]{bibid}#*C
\citep[prenote][postnote]{bibid}#*C
\citetns{bibid}#*C
\citetns[postnote]{bibid}#*C
\citetns[prenote][postnote]{bibid}#*C
\citepns{bibid}#*C
\citepns[postnote]{bibid}#*C
\citepns[prenote][postnote]{bibid}#*C
\inlinecite{bibid}#*C
\inlinecite[postnote]{bibid}#*C
\inlinecite[prenote][postnote]{bibid}#*C
\citec{bibid}#C
\citec[postnote]{bibid}#C
\citec[prenote][postnote]{bibid}#C
\citecs{bibid}{bibid}#C
\citecs(post){bibid}{bibid}#*C
\citecs(pre)(post){bibid}{bibid}#C
\citecs(pre)(post)[post]{bibid}[post]{bibid}#*C
\citecs[post]{bibid}[post]{bibid}#*C
\citecs[pre][post]{bibid}[pre][post]{bibid}#*C
\citecs(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\authornumcites{bibid}{bibid}#C
\authornumcites(post){bibid}{bibid}#*C
\authornumcites(pre)(post){bibid}{bibid}#C
\authornumcites(pre)(post)[post]{bibid}[post]{bibid}#*C
\authornumcites[post]{bibid}[post]{bibid}#*C
\authornumcites[pre][post]{bibid}[pre][post]{bibid}#*C
\authornumcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
#endif

#ifOption:style=chinese-erj
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from chinese-erj.bbx (loads gb7714-2015ay.bbx)
erjpunctcn#true,false
# from gb7714-2015ay.bbx
gbmedium#true,false
gbannote#true,false
gbfieldtype#true,false
gbfnperpage#true,false
gbfootbib#true,false
gbstyle#true,false
gbtype#true,false
gbcodegbk#true,false
gbstrict#true,false
gbtitlelink#true,false
gbctexset#true,false
gbnoauthor#true,false
gbfieldstd#true,false
gbpub#true,false
gbpunctin#true,false
gblanorder=#chineseahead,englishahead,%<string%>
gbcitelocal=#gb7714-2015,chinese,english
gbbiblocal=#gb7714-2015,chinese,english
gblocal=#gb7714-2015,chinese,english
gbbiblabel=#bracket,parens,plain,dot,box,circle
gbnamefmt=#uppercase,lowercase,givenahead,familyahead,pinyin,quanpin,reverseorder
gbalign=#right,left,center,gb7714-2015,gb7714-2015ay
# from chinese-erj.cbx (loads gb7714-2015ay.cbx)
erjcitepunctcn#true,false
# from gb7714-2015ay.cbx
gblabelref#true,false
gbcitelabel=#bracket,parens,plain,dot,box,circle
#endkeyvals
# from chinese-erj.bbx (loads gb7714-2015ay.bbx)
#include:mfirstuc
\gbpunctdot#*
\gbpunctmark#*
\gbpunctcomma#*
\gbpunctcommalanen#*
\gbpunctcolon#*
\gbpunctcolonlanen#*
\gbpunctsemicolon#*
\gbpunctttl#*
\gbpunctttr#*
\execerjpuncten#*
\thenumberwithoutzero#*
# from gb7714-2015ay.bbx
#include:xstring
\versionofgbtstyle#S
\versionofbiblatex#S
\defversion{arg1}{arg2}{arg3}#S
\switchversion{arg1}{arg2}#S
\testCJKfirst{field}#*
\multivolparser{arg}#*
\multinumberparser{arg}#*
\footbibmargin#*
\footbiblabelsep#*
\execgbfootbib#*
\thegbnamefmtcase#*
\mkgbnumlabel{arg}#*
\thegbalignlabel#*
\thegbcitelocalcase#*
\thegbbiblocalcase#*
\lancnorder#S
\lanjporder#S
\lankrorder#S
\lanenorder#S
\lanfrorder#S
\lanruorder#S
\execlanodeah#*
\thelanordernum#*
\execlanodudf{string}#*
\setlocalbibstring{string}{text}
\setlocalbiblstring{string}{text}
\dealnoathor#*
\dealsortlan#*
\bibitemindent#*
\therefnumeric#*
\biblabelextend#*
\setaligngbnumeric#*
\setaligngbstyle#*
\lengthid#*
\lengthlw#*
\itemcmd#*
\publocpunct#*
\bibtitlefont#*
\bibauthorfont#*
\bibpubfont#*
\execgbfdfmtstd#*
\aftertransdelim#*
\gbcaselocalset#*
\gbpinyinlocalset#*
\gbquanpinlocalset#*
\defdoublelangentry{match}{fieldvalue}
\entrykeya#S
\entrykeyb#S
\userfieldabcde#S
# from chinese-erj.cbx (loads gb7714-2015ay.cbx)
\erjpunctmarkcite#*
\erjpunctsemicoloncite#*
\erjpunctparenlcite#*
\erjpunctparenrcite#*
\execerjpunctencite#*
# from gb7714-2015ay.cbx
\mkbibleftborder#*
\mkbibrightborder#*
\compextradelim#*
\upcite{bibid}#*C
\upcite[postnote]{bibid}#*C
\upcite[prenote][postnote]{bibid}#*C
\pagescite{bibid}#C
\pagescite[postnote]{bibid}#C
\pagescite[prenote][postnote]{bibid}#C
\yearpagescite{bibid}#C
\yearpagescite[postnote]{bibid}#C
\yearpagescite[prenote][postnote]{bibid}#C
\yearcite{bibid}#C
\yearcite[postnote]{bibid}#C
\yearcite[prenote][postnote]{bibid}#C
\authornumcite{bibid}#C
\authornumcite[postnote]{bibid}#C
\authornumcite[prenote][postnote]{bibid}#C
\citet{bibid}#*C
\citet[postnote]{bibid}#*C
\citet[prenote][postnote]{bibid}#*C
\citep{bibid}#*C
\citep[postnote]{bibid}#*C
\citep[prenote][postnote]{bibid}#*C
\citets{bibid}{bibid}#*C
\citets(post){bibid}{bibid}#*C
\citets(pre)(post){bibid}{bibid}#*C
\citets(pre)(post)[post]{bibid}[post]{bibid}#*C
\citets[post]{bibid}[post]{bibid}#*C
\citets[pre][post]{bibid}[pre][post]{bibid}#*C
\citets(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#*C
\citetns{bibid}#*C
\citetns[postnote]{bibid}#*C
\citetns[prenote][postnote]{bibid}#*C
\citepns{bibid}#*C
\citepns[postnote]{bibid}#*C
\citepns[prenote][postnote]{bibid}#*C
\inlinecite{bibid}#*C
\inlinecite[postnote]{bibid}#*C
\inlinecite[prenote][postnote]{bibid}#*C
\citec{bibid}#C
\citec[postnote]{bibid}#C
\citec[prenote][postnote]{bibid}#C
\citecs{bibid}{bibid}#C
\citecs(post){bibid}{bibid}#*C
\citecs(pre)(post){bibid}{bibid}#C
\citecs(pre)(post)[post]{bibid}[post]{bibid}#*C
\citecs[post]{bibid}[post]{bibid}#*C
\citecs[pre][post]{bibid}[pre][post]{bibid}#*C
\citecs(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\authornumcites{bibid}{bibid}#C
\authornumcites(post){bibid}{bibid}#*C
\authornumcites(pre)(post){bibid}{bibid}#C
\authornumcites(pre)(post)[post]{bibid}[post]{bibid}#*C
\authornumcites[post]{bibid}[post]{bibid}#*C
\authornumcites[pre][post]{bibid}[pre][post]{bibid}#*C
\authornumcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
#endif

### biblatex-german-legal v002 ###
#ifOption:style=german-legal-book
#include:xpatch
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
edsuper#true,false
#endkeyvals
# loads ext-authortitle.bbx and ext-authortitle.cbx
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
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

### biblatex-iso690 v0.4.1 ###
#ifOption:style=iso-alphabetic
# loads iso.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from iso.bbx
spacecolon#true,false
pagetotal#true,false
shortnumeration#true,false
thesisinfoinnotes#true,false
articlepubinfo#true,false
currentlang#true,false
noenddot#true,false
#endkeyvals
# from iso.bbx
\stdidentifierspunct#*
\dateaddonpunct#*
\numerationpunct#*
\addspacecolon#*
\familynameformat{text}#*
\mainlangbibstring{string}#*
\mainlangbibstring[wrapper]{string}#*
\mainlangbiblstring{string}#*
\mainlangbiblstring[wrapper]{string}#*
\mainlangbibsstring{string}#*
\mainlangbibsstring[wrapper]{string}#*
\mkmlpagetotal{text}#*
\mkmlpagetotal[pagination]{text}#*
\mkmlpageprefix{prefix}#*
\mkmlpageprefix[pagination]{prefix}#*
\addspcolon#*
\mkopenendeddaterange#*
#endif

#ifOption:style=iso-authortitle
# loads iso.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from iso.bbx
spacecolon#true,false
pagetotal#true,false
shortnumeration#true,false
thesisinfoinnotes#true,false
articlepubinfo#true,false
currentlang#true,false
noenddot#true,false
#endkeyvals
# from iso.bbx
\stdidentifierspunct#*
\dateaddonpunct#*
\numerationpunct#*
\addspacecolon#*
\familynameformat{text}#*
\mainlangbibstring{string}#*
\mainlangbibstring[wrapper]{string}#*
\mainlangbiblstring{string}#*
\mainlangbiblstring[wrapper]{string}#*
\mainlangbibsstring{string}#*
\mainlangbibsstring[wrapper]{string}#*
\mkmlpagetotal{text}#*
\mkmlpagetotal[pagination]{text}#*
\mkmlpageprefix{prefix}#*
\mkmlpageprefix[pagination]{prefix}#*
\addspcolon#*
\mkopenendeddaterange#*
#endif

#ifOption:style=iso-authoryear
# loads iso.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from iso.bbx
spacecolon#true,false
pagetotal#true,false
shortnumeration#true,false
thesisinfoinnotes#true,false
articlepubinfo#true,false
currentlang#true,false
noenddot#true,false
#endkeyvals
# from iso-authoryear.bbx
\ifdatehasyearonly{true}{false}#*
# from iso.bbx
\stdidentifierspunct#*
\dateaddonpunct#*
\numerationpunct#*
\addspacecolon#*
\familynameformat{text}#*
\mainlangbibstring{string}#*
\mainlangbibstring[wrapper]{string}#*
\mainlangbiblstring{string}#*
\mainlangbiblstring[wrapper]{string}#*
\mainlangbibsstring{string}#*
\mainlangbibsstring[wrapper]{string}#*
\mkmlpagetotal{text}#*
\mkmlpagetotal[pagination]{text}#*
\mkmlpageprefix{prefix}#*
\mkmlpageprefix[pagination]{prefix}#*
\addspcolon#*
\mkopenendeddaterange#*
#endif

#ifOption:style=iso-numeric
# loads iso.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from iso.bbx
spacecolon#true,false
pagetotal#true,false
shortnumeration#true,false
thesisinfoinnotes#true,false
articlepubinfo#true,false
currentlang#true,false
noenddot#true,false
#endkeyvals
# from iso.bbx
\stdidentifierspunct#*
\dateaddonpunct#*
\numerationpunct#*
\addspacecolon#*
\familynameformat{text}#*
\mainlangbibstring{string}#*
\mainlangbibstring[wrapper]{string}#*
\mainlangbiblstring{string}#*
\mainlangbiblstring[wrapper]{string}#*
\mainlangbibsstring{string}#*
\mainlangbibsstring[wrapper]{string}#*
\mkmlpagetotal{text}#*
\mkmlpagetotal[pagination]{text}#*
\mkmlpageprefix{prefix}#*
\mkmlpageprefix[pagination]{prefix}#*
\addspcolon#*
\mkopenendeddaterange#*
#endif

### biblatex-juradiss v0.23 ###
#ifOption:style=biblatex-juradiss
# loads authortitle-dw.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from standard-dw.bbx
acronyms#true,false
shorthandinbib#true,false
shorthandwidth=##L
shortjournal#true,false
terselos#true,false
xref#true,false
pagetotal#true,false
journalnumber=#standard,afteryear,date
bernhard#true,false
series=#standard,afteryear,beforeedition
seriesformat=#standard,parens
# from authortitle-dw.bbx
annotation#true,false
edbyidem#true,false
editionstring#true,false
edsuper#true,false
idembib#true,false
library#true,false
nolocation#true,false
nopublisher#true,false
oldauthor#true,false
origfields#true,false
pseudoauthor#true,false
origfieldsformat=#parens,brackets,punct
namefont=#smallcaps,italic,bold,normal
firstnamefont=#smallcaps,italic,bold,normal
idemfont=#smallcaps,italic,bold,normal
ibidemfont=#smallcaps,italic,bold,normal
idembibformat=#idem,dash
editorstring=#parens,brackets,normal
editorstringfont=#normal,namefont
# from standard-dw.cbx
citedas#true,false
edstringincitations#true,false
omiteditor#true,false
shorthandibid#true,false
citeauthor=#namefont,namefontfoot,normalfont
citeauthorname=#normal,firstfull,full
ibidpage#true,false
pageref#true,false
citepages=#permit,suppress,omit,separate
# from authortitle-dw.cbx
addyear#true,false
firstfull#true,false
inreference=#normal,full
#endkeyvals
# from standard-dw.bbx
\shorthandsep#*
\jourvolstring#*
\jourvolnumsep#*
\journumstring#*
\seriespunct#*
\sernumstring#*
\shorthandpunct#*
\shorthandinbibpunct#*
# from authortitle-dw.bbx
\titleaddonpunct#*
\locationdatepunct#*
\locationpublisherpunct#*
\publisherdatepunct#*
\origfieldspunct#*
\bibleftpseudo#*
\bibrightpseudo#*
\bibrevsdnamedelim#*
\bibmultinamedelim#*
\bibfinalnamedelim#*
\annotationfont#*
\libraryfont#*
\mkidem{arg}#*
# from biblatex-juradiss.cbx
\qverweis{label}#r
#endif

### biblatex-jura2 v0.4 ###
#ifOption:style=jura2
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from jura2.bbx
citedbytitle#true,false
howcited#true,false
bearbeiterin#true,false
fshowcited#true,false
# from jura2.cbx
citedbypage#true,false
#endkeyvals
# from jura2.cbx
\oldpostnotedelim#S
\mkpostnote{arg}#*
\footcite[(%<postnote:prefix%>)%<postnote:stem%>]{%<bibid%>}
# loads ext-authortitle-ibid.bbx and ext-authortitle-ibid.cbx
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

### biblatex-lncs v0.5 ###
#ifOption:style=lncs
# from lncs.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
acronym#true,false
series=#short,full,no
conference=#long,full,acronym
#endkeyvals
#endif

### biblatex-lni v0.5 ###
#ifOption:style=LNI
# from LNI.bbx
\LNIversion#S
\LNIdate#S
\volnumdelim#*
\aftertitledelim#*
#endif

### biblatex-manuscripts-philology v2.1.2 ###
#ifOption:bibstyle=manuscripts
#include:xpatch
\shcite{bibid}#C
\shcite[postnote]{bibid}#C
\shcite[prenote][postnote]{bibid}#C
\detailscite{bibid}#C
\detailscite[postnote]{bibid}#C
\detailscite[prenote][postnote]{bibid}#C
\detailscites{bibid}{bibid}#C
\detailscites(post){bibid}{bibid}#*C
\detailscites(pre)(post){bibid}{bibid}#C
\detailscites(pre)(post)[post]{bibid}[post]{bibid}#*C
\detailscites[post]{bibid}[post]{bibid}#*C
\detailscites[pre][post]{bibid}[pre][post]{bibid}#*C
\detailscites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\collectionshelfmarkpunct#*
\datingpagespunct#*
\librarycollectionpunct#*
\mkcolumns{text}#*
\mklayer{text}#*
\mkcolumnslayer{text}#*
\mklocation{text}#*
\mkmanuscriptdescriptionlabel{text}#*
\mkmanuscriptdescriptionlabelparagraphed{text}#*
\mkshcite{text}#*
\locationlibrarypunct#*
\manuscriptdescriptionlabelpunct#*
\moreinterpunct#*
\pagetotalpagespunct#*
\columnslayerpunct#*
\multidetailscitedelim#*
\recto#*
\verso#*
\manuscriptaddshortened{arg}#*
#endif
#ifOption:bibstyle=manuscripts-noautoshorthand
#include:xpatch
\shcite{bibid}#C
\shcite[postnote]{bibid}#C
\shcite[prenote][postnote]{bibid}#C
\detailscite{bibid}#C
\detailscite[postnote]{bibid}#C
\detailscite[prenote][postnote]{bibid}#C
\detailscites{bibid}{bibid}#C
\detailscites(post){bibid}{bibid}#*C
\detailscites(pre)(post){bibid}{bibid}#C
\detailscites(pre)(post)[post]{bibid}[post]{bibid}#*C
\detailscites[post]{bibid}[post]{bibid}#*C
\detailscites[pre][post]{bibid}[pre][post]{bibid}#*C
\detailscites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\collectionshelfmarkpunct#*
\datingpagespunct#*
\librarycollectionpunct#*
\mkcolumns{text}#*
\mklayer{text}#*
\mkcolumnslayer{text}#*
\mklocation{text}#*
\mkmanuscriptdescriptionlabel{text}#*
\mkmanuscriptdescriptionlabelparagraphed{text}#*
\mkshcite{text}#*
\locationlibrarypunct#*
\manuscriptdescriptionlabelpunct#*
\moreinterpunct#*
\pagetotalpagespunct#*
\columnslayerpunct#*
\multidetailscitedelim#*
\recto#*
\verso#*
\manuscriptaddshortened{arg}#*
#endif

### biblatex-mla v2.0 ###
#ifOption:style=mla-strict
# loads mla.cbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
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
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
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
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
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
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articletitle#true,false
intitle#true,false
#endkeyvals
#endif

### biblatex-nejm v0.5 ###
#ifOption:style=nejm
# from nejm.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articledoi#true,false
articlein#true,false
printlang#true,false
#endkeyvals
\biblatexnejmversionbbx#S
\biblatexnejmpackagenamebbx#S
\biblatexnejmsvnbbx#S
#endif

### oscola v1.7 ###
#ifOption:style=oscola
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from oscola.bbx
caseshorthands#true,false
ecli=#yes,no,only
ibidstyle=#lc,uc
shortindex#true,false
# from oscola.cbx
eutreaty#true,false
#endkeyvals
# from oscola.bbx
\oldbibnamedelima#S
\oldbibnamedelimb#S
\oldbibnamedelimc#S
\oldbibnamedelimd#S
\oldbibnamedelimi#S
\bbxinitsep#*
\bibyearwatershed#*
\nameaddonpseud#*
\subtypemag#*
\subtypenewsp#*
\subtypeclassic#*
\subtypebiblical#*
\subtypeearlybook#*
\subtypevideo#*
\entrytypearchive#*
\subtypevolume#*
\subtypeonline#*
\subtypedatabase#*
\subtypeblog#*
\subtypelistmessage#*
\subtypebooklike#*
\subtypepublicdocument#*
\authortypeanon#*
\authortypeunsure#*
\authortyperedundant#*
\authortypealternate#*
\authortypejournal#*
\subtypeintro#*
\subtypeexcerpt#*
\subtypenone#*
\edtypecorp#*
\entrytypeper#*
\entrytypemanual#*
\entrytypecoll#*
\entrytypebook#*
\subtypeprimarylegislation#*
\subtypesecondarylegislation#*
\subtypecourtrules#*
\entrytyperef#*
\entrytypeproc#*
\entrytypereport#*
\entrytypebooklet#*
\entrytypemisc#*
\entrytypeonline#*
\entrytypevideo#*
\entrytypeaudio#*
\entrytypebookinbook#*
\entrytypearticle#*
\entrytypelegislation#*
\entrytypeletter#*
\entrytypeperformance#*
\optionaddoriginal#*
\optionnoreprints#*
\optionorigfirst#*
\optiontransfromorig#*
\optionorigtransas#*
\optiondoubledate#*
\noplace#*
\nopublisher#*
\officialjournaltitle#*
\ojspecedtitle#*
\ecrreporttitle#*
\commission#*
\Commission#*
\pcijrep#*
\explanatorynote#*
\eudirective#*
\euregulation#*
\eudecision#*
\treatysubtype#*
\comdocsubtype#*
\jurisechr#*
\eutreaty#*
\casenote#*
\pagemarkings#*
\paragraphmarkings#*
\paragraphtext#*
\seriesa#*
\echrreports#*
\decisionsandreports#*
\collectionofdecisions#*
\parliamentarytype#*
\houseofcommons#*
\houseoflords#*
\undoctype#*
\extracitedelim#*
\casenotetext#*
\firstpublishedstr#*
\legalstarturl#*
\legalendurl#*
\paratextformatted{text}#*
\csusebibmacro{name}#*
\forbbxrange#*
\rangesplit{arg}#*
\formatpostnote{text}#*
\ifnumeralfirst{arg1}{arg2}{arg3}#*
\ifnumeralsfirst{arg1}{arg2}{arg3}#*
\numeraljustfirst{arg1}{arg2}{arg3}#*
\siganddate{arg}#*
\treatypartysep#*
\SetStandardIndices#*
\DeclareIndexAssociation{category}{index}
\ShowIndexAssociation{category}#*
\legislationindex#*
\iflistcontains{arg1}{arg2}{true}{false}#*
\printindexearly
\printindexearly[name]
# from oscola.cbx
\DNI
\reponly[prenote][postnote]{bibid}#*C
\reponly[postnote]{bibid}#*C
\reponly{bibid}#*C
\footciteref[prenote][postnote]{bibid}#*C
\footciteref[postnote]{bibid}#*C
\footciteref{bibid}#*C
\dopipedlist#*
\setuppostnotes#*
\postnotefirst#*
\postnotesecond#*
\citeinindex[prenote][postnote]{bibid}#C
\citeinindex[postnote]{bibid}#C
\citeinindex{bibid}#C
\citeinindexnum[prenote][postnote]{bibid}#*C
\citeinindexnum[postnote]{bibid}#*C
\citeinindexnum{bibid}#*C
\indexonly[prenote][postnote]{bibid}#C
\indexonly[postnote]{bibid}#C
\indexonly{bibid}#C
#endif

### biblatex-oxalph v2.2 ###
#ifOption:style=oxalph
# loads oxyear bibliography style
#include:xpatch
#include:xstring
#include:graphicx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
anon=#literal,long,short
bookseries=#in,out
court-plain#true,false
ecli=#yes,only,no
isourls#true,false
issuedate-plain#true,false
issuestyle=#slash,colon,comma,parens
mergedate=#maximum,compact,basic,minimum,year,false
nolocation
nonodate#true,false
nopublisher
norelatedin#true,false
relationpunct=#period,comma,semicolon,colon,space
thesis=#in,out,plain
timefirst#true,false
usenametitles#true,false
#endkeyvals
# from oxref.bbx
\casenote#*
\casenotetext#*
\collectionofdecisions#*
\collectionshelfmarkpunct#*
\columnslayerpunct#*
\commission#*
\Commission#*
\datingpagespunct#*
\decisionsandreports#*
\echrreports#*
\ecrreporttitle#*
\explanatorynote#*
\ifabbrev{field}{true}{false}#*
\iflistcontains{list}{string}#*
\legreport#*
\librarycollectionpunct#*
\locationlibrarypunct#*
\mkbibnametitle{text}#*
\mkrawpageprefix#*
\mkrawpageprefix[type]#*
\officialjournaltitle#*
\ojspecedtitle#*
\oxrefand#*
\oxrefanon#*
\pagetotalpagespunct#*
\paragraphmarkings#*
\parliamentarytype#*
\recordseriespunct#*
\recto#*
\relatedtypepunct#*
\seriesa#*
\siganddate{arg}#*
\subtypecourtrules#*
\subtypenewsp#*
\subtypeprimarylegislation#*
\thelocpubpairs#*
\thenamepairs#*
\titlebyauthordelim#*
\treatypartysep#*
\treatysubtype#*
\Version#S
\verso#*
# from english-oxref.lbx
\mkusbibordinal{number}#*
# from oxyear.bbx
\iflabeldateisanydate{true}{false}#*
\iflabeldateispubstate{true}{false}#*
\mknoyeardaterangefull{arg1}{arg2}#*
\mknoyeardaterangetrunc{arg1}{arg2}#*
#endif

#ifOption:style=oxyear
# loads oxref bibliography style
#include:xpatch
#include:xstring
#include:graphicx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
anon=#literal,long,short
bookseries=#in,out
court-plain#true,false
ecli=#yes,only,no
isourls#true,false
issuedate-plain#true,false
issuestyle=#slash,colon,comma,parens
mergedate=#maximum,compact,basic,minimum,year,false
nolocation
nonodate#true,false
nopublisher
norelatedin#true,false
relationpunct=#period,comma,semicolon,colon,space
thesis=#in,out,plain
timefirst#true,false
usenametitles#true,false
#endkeyvals
# from oxref.bbx
\casenote#*
\casenotetext#*
\collectionofdecisions#*
\collectionshelfmarkpunct#*
\columnslayerpunct#*
\commission#*
\Commission#*
\datingpagespunct#*
\decisionsandreports#*
\echrreports#*
\ecrreporttitle#*
\explanatorynote#*
\ifabbrev{field}{true}{false}#*
\iflistcontains{list}{string}#*
\legreport#*
\librarycollectionpunct#*
\locationlibrarypunct#*
\mkbibnametitle{text}#*
\mkrawpageprefix#*
\mkrawpageprefix[type]#*
\officialjournaltitle#*
\ojspecedtitle#*
\oxrefand#*
\oxrefanon#*
\pagetotalpagespunct#*
\paragraphmarkings#*
\parliamentarytype#*
\recordseriespunct#*
\recto#*
\relatedtypepunct#*
\seriesa#*
\siganddate{arg}#*
\subtypecourtrules#*
\subtypenewsp#*
\subtypeprimarylegislation#*
\thelocpubpairs#*
\thenamepairs#*
\titlebyauthordelim#*
\treatypartysep#*
\treatysubtype#*
\Version#S
\verso#*
# from english-oxref.lbx
\mkusbibordinal{number}#*
# from oxyear.bbx
\iflabeldateisanydate{true}{false}#*
\iflabeldateispubstate{true}{false}#*
\mknoyeardaterangefull{arg1}{arg2}#*
\mknoyeardaterangetrunc{arg1}{arg2}#*
#endif

#ifOption:style=oxnotes
# loads oxref bibliography style
#include:xpatch
#include:xstring
#include:graphicx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
anon=#literal,long,short
bookseries=#in,out
court-plain#true,false
ecli=#yes,only,no
isourls#true,false
issuedate-plain#true,false
issuestyle=#slash,colon,comma,parens
nolocation
nopublisher
norelatedin#true,false
relationpunct=#period,comma,semicolon,colon,space
scnames#true,false
thesis=#in,out,plain
timefirst#true,false
usenametitles#true,false
#endkeyvals
# from oxref.bbx
\casenote#*
\casenotetext#*
\collectionofdecisions#*
\collectionshelfmarkpunct#*
\columnslayerpunct#*
\commission#*
\Commission#*
\datingpagespunct#*
\decisionsandreports#*
\echrreports#*
\ecrreporttitle#*
\explanatorynote#*
\ifabbrev{field}{true}{false}#*
\iflistcontains{list}{string}#*
\legreport#*
\librarycollectionpunct#*
\locationlibrarypunct#*
\mkbibnametitle{text}#*
\mkrawpageprefix#*
\mkrawpageprefix[type]#*
\officialjournaltitle#*
\ojspecedtitle#*
\oxrefand#*
\oxrefanon#*
\pagetotalpagespunct#*
\paragraphmarkings#*
\parliamentarytype#*
\recordseriespunct#*
\recto#*
\relatedtypepunct#*
\seriesa#*
\siganddate{arg}#*
\subtypecourtrules#*
\subtypenewsp#*
\subtypeprimarylegislation#*
\thelocpubpairs#*
\thenamepairs#*
\titlebyauthordelim#*
\treatypartysep#*
\treatysubtype#*
\Version#S
\verso#*
# from english-oxref.lbx
\mkusbibordinal{number}#*
#endif

#ifOption:style=oxnum
# loads oxref bibliography style
#include:xpatch
#include:xstring
#include:graphicx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
anon=#literal,long,short
bookseries=#in,out
court-plain#true,false
ecli=#yes,only,no
isourls#true,false
issuedate-plain#true,false
issuestyle=#slash,colon,comma,parens
nolocation
nopublisher
norelatedin#true,false
relationpunct=#period,comma,semicolon,colon,space
scnames#true,false
thesis=#in,out,plain
timefirst#true,false
usenametitles#true,false
#endkeyvals
# from oxref.bbx
\casenote#*
\casenotetext#*
\collectionofdecisions#*
\collectionshelfmarkpunct#*
\columnslayerpunct#*
\commission#*
\Commission#*
\datingpagespunct#*
\decisionsandreports#*
\echrreports#*
\ecrreporttitle#*
\explanatorynote#*
\ifabbrev{field}{true}{false}#*
\iflistcontains{list}{string}#*
\legreport#*
\librarycollectionpunct#*
\locationlibrarypunct#*
\mkbibnametitle{text}#*
\mkrawpageprefix#*
\mkrawpageprefix[type]#*
\officialjournaltitle#*
\ojspecedtitle#*
\oxrefand#*
\oxrefanon#*
\pagetotalpagespunct#*
\paragraphmarkings#*
\parliamentarytype#*
\recordseriespunct#*
\recto#*
\relatedtypepunct#*
\seriesa#*
\siganddate{arg}#*
\subtypecourtrules#*
\subtypenewsp#*
\subtypeprimarylegislation#*
\thelocpubpairs#*
\thenamepairs#*
\titlebyauthordelim#*
\treatypartysep#*
\treatysubtype#*
\Version#S
\verso#*
# from english-oxref.lbx
\mkusbibordinal{number}#*
#endif

### biblatex-philosophy v1.9.8f ###
#ifOption:style=philosophy-classic
\sdcite{bibid}#C
\footcitet{bibid}#C
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c,\printbibliography
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
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c,\printbibliography
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
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c,\printbibliography
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

### biblatex-phys v1.1b ###
#ifOption:style=phys
# from phys.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articletitle#true,false
chaptertitle#true,false
pageranges#true,false
biblabel=#superscript,brackets
#endkeyvals
\mkibid{arg}#*
#endif

### biblatex-publist v1.26 ###
#ifOption:style=publist
# from publist.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
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
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
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

### biblatex-realauthor v2.7.1a ###
#ifOption:bibstyle=realauthor
#include:xpatch
\mkbibrealauthor{arg}#*
\mkrealauthor{arg}#*
\realauthorequalsign#*
\mkbibrealeditor{arg}#*
\mkrealeditor{arg}#*
\realeditorequalsign#*
#endif

### biblatex-sbl v0.13 ###
#ifOption:style=sbl
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from biblatex-sbl.def (loaded by sbl.bbx)
accessdate#true,false
citepages=#sbl,permit,omit,separate
eprintdate=#year,short,long,terse,comp,iso8601
fullbibrefs#true,false
idemtracker=#true,false,context,strict,constrict,citation,sbl
sblfootnotes#true,false
shorthand=#true,false,short,intro
useshorttitle#true,false
usefullcite#true,false
usevolume#true,false
useseries#true,false
#endkeyvals
# from biblatex-sbl.def (loaded by sbl.bbx)
\printsblversion#S
\printsbldate#S
\xprintsbldateiso#S
\xprintsbldateau#S
\ifciteidemsbl{true}{false}#*
\namedashpunct#*
\lexiconfinalnamedelim#*
\volpostnotedelim#*
\mkibid{arg}#*
\addskipentry{arg}#*
\addincludeentry{arg}#*
\abbrevwidth#*
\setmaxlength{length1}{length2}#*
\iffirstcharsec{arg}{true}{false}#*
\iffirstcharnum{arg}{true}{false}#*
\thecurrentpublisher#*
\thecurrentlocation#*
\thecurrentorganization#*
\thecurrentinstitution#*
\thepublishertotal#*
\thelocationtotal#*
\theorganizationtotal#*
\theinstitutiontotal#*
\savepostnotes#*
\postnotefirst#*
\postnotelast#*
\splitpostnote#*
\volsplitpostnote{arg1}{arg2}#*
\volvol#S
\setuppostnotes#*
# from sbl.cbx
\citefullauthor{bibid}#C
\citefullauthor[postnote]{bibid}#C
\citefullauthor[prenote][postnote]{bibid}#C
\citefullauthor*{bibid}#C
\citefullauthor*[postnote]{bibid}#C
\citefullauthor*[prenote][postnote]{bibid}#C
\Citefullauthor{bibid}#C
\Citefullauthor[postnote]{bibid}#C
\Citefullauthor[prenote][postnote]{bibid}#C
\Citefullauthor*{bibid}#C
\Citefullauthor*[postnote]{bibid}#C
\Citefullauthor*[prenote][postnote]{bibid}#C
\citejournal{bibid}#C
\citeseries{bibid}#C
\citeshorthand{bibid}#C
\bibentrycite{bibid}#*C
\biblistcite{bibid}#*C
\DeclareNestableCiteCommand{cmd}{def}#*d
#endif

### biblatex-science v1.2 ###
#ifOption:style=science
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articletitle#true,false
#endkeyvals
#endif

### biblatex-socialscienceshuberlin v0.0.1 ###
#ifOption:style=socialscienceshuberlin
# from socialscienceshuberlin.bbx
#include:xcolor
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
colornames#true,false
#endkeyvals
\socialscienceshuberlinversion#S
\socialscienceshuberlindate#S
sshuberlincolor#B
# loads ext-authoryear.bbx and ext-authoryear.cbx
\mkoutercitedelims{arg}#*
\mkinnercitedelims{arg}#*
\mkouterparencitedelims{arg}#*
\mkinnerparencitedelims{arg}#*
\mkoutertextcitedelims{arg}#*
\mkinnertextcitedelims{arg}#*
\mkouterfootcitedelims{arg}#*
\mkinnerfootcitedelims{arg}#*
\mkoutersupercitedelims{arg}#*
\namenumberdelim#*
\nonamenumberdelim#*
\innametitledelim#*
\extradateonlycompcitedelim#*
\extradateonlycompciterangedelim#*
\extranameonlycompcitedelim#*
\extranameonlycompciterangedelim#*
# from ext-dashed-common.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
dashed=#true,false,fullhash,bibnamehash
#endkeyvals
# from ext-biblatex-aux.def
\DeclareOuterCiteDelims{cite cmd}{open delim}{close delim}
\DeclareInnerCiteDelims{cite cmd}{open delim}{close delim}
\UndeclareOuterCiteDelims{cite cmd}
\UndeclareInnerCiteDelims{cite cmd}
\UndeclareCiteDelims{cite cmd}
\DeclareOuterCiteDelimsAlias{cite alias}{cite cmd}
\DeclareOuterCiteDelimsAlias*{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias{cite alias}{cite cmd}
\DeclareInnerCiteDelimsAlias*{cite alias}{cite cmd}
\RegisterCiteDelims{modifier}{cite cmd}
\mkextblxsupercite{text}#*
\mkextblxfootcite{text}#*
\mkextblxfootcitetext{text}#*
\mksmartcite{text}#*
# from ext-standard.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
articlein#true,false
citexref#true,false
innamebeforetitle#true,false
innameidem#true,false
maintitleaftertitle#true,false
introcite=#false,plain,label
#endkeyvals
\mkibid{arg}#*
\introcitepunct#*
\introcitebreak#*
\introcitewidth#*
\introcitesep#*
\AtIntrocite{code}
\AtIntrocite*{code}
\AtXrefcite{code}
\AtXrefcite*{code}
\titleaddonpunct#*
\titlemaintitledelim#*
\maintitletitledelim#*
\voltitledelim#*
\jourvoldelim#*
\jourserdelim#*
\servoldelim#*
\volnumdatedelim#*
\volnumdelim#*
\sernumdelim#*
\locdatedelim#*
\locpubdelim#*
\publocdelim#*
\pubdatedelim#*
#endif

### biblatex-software v1.2-4 ###
#ifOption:bibstyle=software
# from software.bbx
#include:xurl
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
halid#true,false
swhid#true,false
shortswhid#true,false
swlabels#true,false
vcs#true,false
license#true,false
#endkeyvals
#endif

### biblatex-spbasic v0.04 ###
#ifOption:style=biblatex-spbasic
# from biblatex-spbasic.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
pubstate#true,false
#endkeyvals
#endif

### thuthesis v1.0 ###
#ifOption:style=thuthesis-author-year
# loads gb7714-2015ay.bbx and gb7714-2015ay.cbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from gb7714-2015ay.bbx
gbmedium#true,false
gbannote#true,false
gbfieldtype#true,false
gbfnperpage#true,false
gbfootbib#true,false
gbstyle#true,false
gbtype#true,false
gbcodegbk#true,false
gbstrict#true,false
gbtitlelink#true,false
gbctexset#true,false
gbnoauthor#true,false
gbfieldstd#true,false
gbpub#true,false
gbpunctin#true,false
gblanorder=#chineseahead,englishahead,%<string%>
gbcitelocal=#gb7714-2015,chinese,english
gbbiblocal=#gb7714-2015,chinese,english
gblocal=#gb7714-2015,chinese,english
gbbiblabel=#bracket,parens,plain,dot,box,circle
gbnamefmt=#uppercase,lowercase,givenahead,familyahead,pinyin,quanpin,reverseorder
gbalign=#right,left,center,gb7714-2015,gb7714-2015ay
# from gb7714-2015ay.cbx
gblabelref#true,false
gbcitelabel=#bracket,parens,plain,dot,box,circle
#endkeyvals
# from gb7714-2015ay.bbx
#include:xstring
\versionofgbtstyle#S
\versionofbiblatex#S
\defversion{arg1}{arg2}{arg3}#S
\switchversion{arg1}{arg2}#S
\testCJKfirst{field}#*
\multivolparser{arg}#*
\multinumberparser{arg}#*
\footbibmargin#*
\footbiblabelsep#*
\execgbfootbib#*
\thegbnamefmtcase#*
\mkgbnumlabel{arg}#*
\thegbalignlabel#*
\thegbcitelocalcase#*
\thegbbiblocalcase#*
\lancnorder#S
\lanjporder#S
\lankrorder#S
\lanenorder#S
\lanfrorder#S
\lanruorder#S
\execlanodeah#*
\thelanordernum#*
\execlanodudf{string}#*
\setlocalbibstring{string}{text}
\setlocalbiblstring{string}{text}
\dealnoathor#*
\dealsortlan#*
\bibitemindent#*
\therefnumeric#*
\biblabelextend#*
\setaligngbnumeric#*
\setaligngbstyle#*
\lengthid#*
\lengthlw#*
\itemcmd#*
\publocpunct#*
\bibtitlefont#*
\bibauthorfont#*
\bibpubfont#*
\execgbfdfmtstd#*
\aftertransdelim#*
\gbcaselocalset#*
\gbpinyinlocalset#*
\gbquanpinlocalset#*
\defdoublelangentry{match}{fieldvalue}
\entrykeya#S
\entrykeyb#S
\userfieldabcde#S
# from gb7714-2015ay.cbx
\mkbibleftborder#*
\mkbibrightborder#*
\compextradelim#*
\upcite{bibid}#*C
\upcite[postnote]{bibid}#*C
\upcite[prenote][postnote]{bibid}#*C
\pagescite{bibid}#C
\pagescite[postnote]{bibid}#C
\pagescite[prenote][postnote]{bibid}#C
\yearpagescite{bibid}#C
\yearpagescite[postnote]{bibid}#C
\yearpagescite[prenote][postnote]{bibid}#C
\yearcite{bibid}#C
\yearcite[postnote]{bibid}#C
\yearcite[prenote][postnote]{bibid}#C
\authornumcite{bibid}#C
\authornumcite[postnote]{bibid}#C
\authornumcite[prenote][postnote]{bibid}#C
\citet{bibid}#*C
\citet[postnote]{bibid}#*C
\citet[prenote][postnote]{bibid}#*C
\citep{bibid}#*C
\citep[postnote]{bibid}#*C
\citep[prenote][postnote]{bibid}#*C
\citets{bibid}{bibid}#*C
\citets(post){bibid}{bibid}#*C
\citets(pre)(post){bibid}{bibid}#*C
\citets(pre)(post)[post]{bibid}[post]{bibid}#*C
\citets[post]{bibid}[post]{bibid}#*C
\citets[pre][post]{bibid}[pre][post]{bibid}#*C
\citets(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#*C
\citetns{bibid}#*C
\citetns[postnote]{bibid}#*C
\citetns[prenote][postnote]{bibid}#*C
\citepns{bibid}#*C
\citepns[postnote]{bibid}#*C
\citepns[prenote][postnote]{bibid}#*C
\inlinecite{bibid}#*C
\inlinecite[postnote]{bibid}#*C
\inlinecite[prenote][postnote]{bibid}#*C
\citec{bibid}#C
\citec[postnote]{bibid}#C
\citec[prenote][postnote]{bibid}#C
\citecs{bibid}{bibid}#C
\citecs(post){bibid}{bibid}#*C
\citecs(pre)(post){bibid}{bibid}#C
\citecs(pre)(post)[post]{bibid}[post]{bibid}#*C
\citecs[post]{bibid}[post]{bibid}#*C
\citecs[pre][post]{bibid}[pre][post]{bibid}#*C
\citecs(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\authornumcites{bibid}{bibid}#C
\authornumcites(post){bibid}{bibid}#*C
\authornumcites(pre)(post){bibid}{bibid}#C
\authornumcites(pre)(post)[post]{bibid}[post]{bibid}#*C
\authornumcites[post]{bibid}[post]{bibid}#*C
\authornumcites[pre][post]{bibid}[pre][post]{bibid}#*C
\authornumcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
#endif

#ifOption:style=thuthesis-bachelor
# loads gb7714-2015.bbx and gb7714-2015.cbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from gb7714-2015.bbx
citexref#true,false
gbmedium#true,false
gbannote#true,false
gbfieldtype#true,false
gbfnperpage#true,false
gbfootbib#true,false
gbstyle#true,false
gbtype#true,false
gbcodegbk#true,false
gbstrict#true,false
gbtitlelink#true,false
gbctexset#true,false
gbnoauthor#true,false
gbfieldstd#true,false
gbpub#true,false
gbpunctin#true,false
gblanorder=#chineseahead,englishahead,%<string%>
gbcitelocal=#gb7714-2015,chinese,english
gbbiblocal=#gb7714-2015,chinese,english
gblocal=#gb7714-2015,chinese,english
gbbiblabel=#bracket,parens,plain,dot,box,circle
gbnamefmt=#uppercase,lowercase,givenahead,familyahead,pinyin,quanpin,reverseorder
gbalign=#right,left,center,gb7714-2015,gb7714-2015ay
# from gb7714-2015.cbx
gblabelref#true,false
gbcitecomp#true,false
gbcitelabel=#bracket,parens,plain,dot,box,circle
#endkeyvals
# from gb7714-2015.bbx
#include:xstring
\versionofgbtstyle#S
\versionofbiblatex#S
\defversion{arg1}{arg2}{arg3}#S
\switchversion{arg1}{arg2}#S
\testCJKfirst{field}#*
\multivolparser{arg}#*
\multinumberparser{arg}#*
\footbibmargin#*
\footbiblabelsep#*
\execgbfootbib#*
\thegbnamefmtcase#*
\mkgbnumlabel{arg}#*
\thegbalignlabel#*
\thegbcitelocalcase#*
\thegbbiblocalcase#*
\lancnorder#S
\lanjporder#S
\lankrorder#S
\lanenorder#S
\lanfrorder#S
\lanruorder#S
\execlanodeah#*
\thelanordernum#*
\execlanodudf{string}#*
\setlocalbibstring{string}{text}
\setlocalbiblstring{string}{text}
\dealsortlan#*
\bibitemindent#*
\biblabelextend#*
\setaligngbstyle#*
\lengthid#*
\lengthlw#*
\itemcmd#*
\setaligngbstyleay#*
\publocpunct#*
\bibtitlefont#*
\bibauthorfont#*
\bibpubfont#*
\execgbfdfmtstd#*
\aftertransdelim#*
\gbcaselocalset#*
\gbpinyinlocalset#*
\gbquanpinlocalset#*
\defdoublelangentry{match}{fieldvalue}
\entrykeya#S
\entrykeyb#S
\userfieldabcde#S
# from gb7714-2015.cbx
\mkbibleftborder#*
\mkbibrightborder#*
\mkbibsuperbracket{text}#*
\mkbibsuperscriptusp{text}#*
\upcite{bibid}#*C
\upcite[postnote]{bibid}#*C
\upcite[prenote][postnote]{bibid}#*C
\pagescite{bibid}#C
\pagescite[postnote]{bibid}#C
\pagescite[prenote][postnote]{bibid}#C
\yearpagescite{bibid}#C
\yearpagescite[postnote]{bibid}#C
\yearpagescite[prenote][postnote]{bibid}#C
\yearcite{bibid}#C
\yearcite[postnote]{bibid}#C
\yearcite[prenote][postnote]{bibid}#C
\authornumcite{bibid}#C
\authornumcite[postnote]{bibid}#C
\authornumcite[prenote][postnote]{bibid}#C
\citet{bibid}#*C
\citet[postnote]{bibid}#*C
\citet[prenote][postnote]{bibid}#*C
\citep{bibid}#*C
\citep[postnote]{bibid}#*C
\citep[prenote][postnote]{bibid}#*C
\citetns{bibid}#*C
\citetns[postnote]{bibid}#*C
\citetns[prenote][postnote]{bibid}#*C
\citepns{bibid}#*C
\citepns[postnote]{bibid}#*C
\citepns[prenote][postnote]{bibid}#*C
\inlinecite{bibid}#*C
\inlinecite[postnote]{bibid}#*C
\inlinecite[prenote][postnote]{bibid}#*C
\citec{bibid}#C
\citec[postnote]{bibid}#C
\citec[prenote][postnote]{bibid}#C
\citecs{bibid}{bibid}#C
\citecs(post){bibid}{bibid}#*C
\citecs(pre)(post){bibid}{bibid}#C
\citecs(pre)(post)[post]{bibid}[post]{bibid}#*C
\citecs[post]{bibid}[post]{bibid}#*C
\citecs[pre][post]{bibid}[pre][post]{bibid}#*C
\citecs(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\authornumcites{bibid}{bibid}#C
\authornumcites(post){bibid}{bibid}#*C
\authornumcites(pre)(post){bibid}{bibid}#C
\authornumcites(pre)(post)[post]{bibid}[post]{bibid}#*C
\authornumcites[post]{bibid}[post]{bibid}#*C
\authornumcites[pre][post]{bibid}[pre][post]{bibid}#*C
\authornumcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
#endif

#ifOption:style=thuthesis-numeric
# loads gb7714-2015.bbx and gb7714-2015.cbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
# from gb7714-2015.bbx
citexref#true,false
gbmedium#true,false
gbannote#true,false
gbfieldtype#true,false
gbfnperpage#true,false
gbfootbib#true,false
gbstyle#true,false
gbtype#true,false
gbcodegbk#true,false
gbstrict#true,false
gbtitlelink#true,false
gbctexset#true,false
gbnoauthor#true,false
gbfieldstd#true,false
gbpub#true,false
gbpunctin#true,false
gblanorder=#chineseahead,englishahead,%<string%>
gbcitelocal=#gb7714-2015,chinese,english
gbbiblocal=#gb7714-2015,chinese,english
gblocal=#gb7714-2015,chinese,english
gbbiblabel=#bracket,parens,plain,dot,box,circle
gbnamefmt=#uppercase,lowercase,givenahead,familyahead,pinyin,quanpin,reverseorder
gbalign=#right,left,center,gb7714-2015,gb7714-2015ay
# from gb7714-2015.cbx
gblabelref#true,false
gbcitecomp#true,false
gbcitelabel=#bracket,parens,plain,dot,box,circle
#endkeyvals
# from gb7714-2015.bbx
#include:xstring
\versionofgbtstyle#S
\versionofbiblatex#S
\defversion{arg1}{arg2}{arg3}#S
\switchversion{arg1}{arg2}#S
\testCJKfirst{field}#*
\multivolparser{arg}#*
\multinumberparser{arg}#*
\footbibmargin#*
\footbiblabelsep#*
\execgbfootbib#*
\thegbnamefmtcase#*
\mkgbnumlabel{arg}#*
\thegbalignlabel#*
\thegbcitelocalcase#*
\thegbbiblocalcase#*
\lancnorder#S
\lanjporder#S
\lankrorder#S
\lanenorder#S
\lanfrorder#S
\lanruorder#S
\execlanodeah#*
\thelanordernum#*
\execlanodudf{string}#*
\setlocalbibstring{string}{text}
\setlocalbiblstring{string}{text}
\dealsortlan#*
\bibitemindent#*
\biblabelextend#*
\setaligngbstyle#*
\lengthid#*
\lengthlw#*
\itemcmd#*
\setaligngbstyleay#*
\publocpunct#*
\bibtitlefont#*
\bibauthorfont#*
\bibpubfont#*
\execgbfdfmtstd#*
\aftertransdelim#*
\gbcaselocalset#*
\gbpinyinlocalset#*
\gbquanpinlocalset#*
\defdoublelangentry{match}{fieldvalue}
\entrykeya#S
\entrykeyb#S
\userfieldabcde#S
# from gb7714-2015.cbx
\mkbibleftborder#*
\mkbibrightborder#*
\mkbibsuperbracket{text}#*
\mkbibsuperscriptusp{text}#*
\upcite{bibid}#*C
\upcite[postnote]{bibid}#*C
\upcite[prenote][postnote]{bibid}#*C
\pagescite{bibid}#C
\pagescite[postnote]{bibid}#C
\pagescite[prenote][postnote]{bibid}#C
\yearpagescite{bibid}#C
\yearpagescite[postnote]{bibid}#C
\yearpagescite[prenote][postnote]{bibid}#C
\yearcite{bibid}#C
\yearcite[postnote]{bibid}#C
\yearcite[prenote][postnote]{bibid}#C
\authornumcite{bibid}#C
\authornumcite[postnote]{bibid}#C
\authornumcite[prenote][postnote]{bibid}#C
\citet{bibid}#*C
\citet[postnote]{bibid}#*C
\citet[prenote][postnote]{bibid}#*C
\citep{bibid}#*C
\citep[postnote]{bibid}#*C
\citep[prenote][postnote]{bibid}#*C
\citetns{bibid}#*C
\citetns[postnote]{bibid}#*C
\citetns[prenote][postnote]{bibid}#*C
\citepns{bibid}#*C
\citepns[postnote]{bibid}#*C
\citepns[prenote][postnote]{bibid}#*C
\inlinecite{bibid}#*C
\inlinecite[postnote]{bibid}#*C
\inlinecite[prenote][postnote]{bibid}#*C
\citec{bibid}#C
\citec[postnote]{bibid}#C
\citec[prenote][postnote]{bibid}#C
\citecs{bibid}{bibid}#C
\citecs(post){bibid}{bibid}#*C
\citecs(pre)(post){bibid}{bibid}#C
\citecs(pre)(post)[post]{bibid}[post]{bibid}#*C
\citecs[post]{bibid}[post]{bibid}#*C
\citecs[pre][post]{bibid}[pre][post]{bibid}#*C
\citecs(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\authornumcites{bibid}{bibid}#C
\authornumcites(post){bibid}{bibid}#*C
\authornumcites(pre)(post){bibid}{bibid}#C
\authornumcites(pre)(post)[post]{bibid}[post]{bibid}#*C
\authornumcites[post]{bibid}[post]{bibid}#*C
\authornumcites[pre][post]{bibid}[pre][post]{bibid}#*C
\authornumcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
#endif

### biblatex-trad v0.5 ###
#ifOption:style=trad-abbrv
# from trad-abbrv.bbx
# loads trad-standard.bbx
\volumenumberdelim#*
\newcommaunit#*
\newcommaunit*#*
\newcommaunitStar#S
\newcommaunitNoStar#S
#endif

#ifOption:style=trad-alpha
# from trad-alpha.bbx
# loads trad-standard.bbx
\volumenumberdelim#*
\newcommaunit#*
\newcommaunit*#*
\newcommaunitStar#S
\newcommaunitNoStar#S
#endif

#ifOption:style=trad-plain
# from trad-plain.bbx
# loads trad-standard.bbx
\volumenumberdelim#*
\newcommaunit#*
\newcommaunit*#*
\newcommaunitStar#S
\newcommaunitNoStar#S
#endif

#ifOption:style=trad-standard
# from trad-standard.bbx
\volumenumberdelim#*
\newcommaunit#*
\newcommaunit*#*
\newcommaunitStar#S
\newcommaunitNoStar#S
#endif

#ifOption:style=trad-unsrt
# from trad-unsrt.bbx
# loads trad-standard.bbx
\volumenumberdelim#*
\newcommaunit#*
\newcommaunit*#*
\newcommaunitStar#S
\newcommaunitNoStar#S
#endif

### biblatex-unified v1.00 ###
#ifOption:style=unified
# from unified.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
issueandeditor#true,false
compactdois#true,false
#endkeyvals
\mkbibdateunified{arg1}{arg2}{arg3}#*
# from unified.cbx
#include:xpatch
\iflinkparens{true}{false}#*
# deprecated
\pgcitep{bibid}{text}#SC
\pgcitealt{bibid}{text}#SC
\pgcitet{bibid}{text}#SC
\pgposscitet{bibid}{text}#SC
\seccitealt{bibid}{text}#SC
\seccitep{bibid}{text}#SC
\seccitet{bibid}{text}#SC
\secposscitet{bibid}{text}#SC
\posscitet{bibid}#SC
\posscitet[postnote]{bibid}#SC
\posscitet[prenote][postnote]{bibid}#SC
\posscitealt{bibid}#SC
\posscitealt[postnote]{bibid}#SC
\posscitealt[prenote][postnote]{bibid}#SC
\possciteauthor{bibid}#SC
\possciteauthor[postnote]{bibid}#SC
\possciteauthor[prenote][postnote]{bibid}#SC
#endif

### univie-ling v1.17 ###
#ifOption:style=univie-ling
# from univie-ling.bbx
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
issueeditor#true,false
#endkeyvals
\mkbibdateunified{arg1}{arg2}{arg3}#*
#endif

### windycity 2021-12-04 ###
#ifOption:style=windycity
#keyvals:\usepackage/biblatex-ms#c,\ExecuteBibliographyOptions#c
annotate#true,false
collsonly#true,false
ibid#true,false
issn#true,false
library#true,false
noetal#true,false
nolos#true,false
nopages#true,false
reflist#true,false
short#true,false
shortafter#true,false
shortfirst#true,false
shortlinks#true,false
swapvol#true,false
#endkeyvals
\idemcite{bibid}#C
\idemcite[postnote]{bibid}#C
\idemcite[prenote][postnote]{bibid}#C
\idemcites{bibid}{bibid}#C
\idemcites(post){bibid}{bibid}#*C
\idemcites(pre)(post){bibid}{bibid}#C
\idemcites(pre)(post)[post]{bibid}[post]{bibid}#*C
\idemcites[post]{bibid}[post]{bibid}#*C
\idemcites[pre][post]{bibid}[pre][post]{bibid}#*C
\idemcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\footidemcite{bibid}#C
\footidemcite[postnote]{bibid}#C
\footidemcite[prenote][postnote]{bibid}#C
\footidemcites{bibid}{bibid}#C
\footidemcites(post){bibid}{bibid}#*C
\footidemcites(pre)(post){bibid}{bibid}#C
\footidemcites(pre)(post)[post]{bibid}[post]{bibid}#*C
\footidemcites[post]{bibid}[post]{bibid}#*C
\footidemcites[pre][post]{bibid}[pre][post]{bibid}#*C
\footidemcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\parenauth{bibid}#C
\parenauth[postnote]{bibid}#C
\parenauth[prenote][postnote]{bibid}#C
\parenauths{bibid}{bibid}#C
\parenauths(post){bibid}{bibid}#*C
\parenauths(pre)(post){bibid}{bibid}#C
\parenauths(pre)(post)[post]{bibid}[post]{bibid}#*C
\parenauths[post]{bibid}[post]{bibid}#*C
\parenauths[pre][post]{bibid}[pre][post]{bibid}#*C
\parenauths(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\mkmonthrange{arg1}{arg2}#*
\mkmonthdayrange{arg1}{arg2}#*
\mkmonthdayyearrange{arg1}{arg2}#*
\anona#*
\anonb#*
\crossreflist#*
\pluga#*
\plugb#*
\xtitle#*
\xeditor#*
\yeditor#*
\edtypes#*
\transtypes#*
\AtBeginLists#*
\AtEveryItem#*
\authtypes#*
\iffieldstart{field}{sym}{true}{false}#*
#endif