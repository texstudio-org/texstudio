# datagidx package
# Matthew Bertucci 2025/03/06 for v3.0

#include:datatool
#include:mfirstuc
#include:multicol

#keyvals:\usepackage/datagidx#c
optimize=#off,low,high
draft
final
nowarn#true,false
compositor=%<symbol%>
counter=%<counter%>
columns=%<integer%>
child=#named,noname
namecase=#nochange,uc,lc,firstuc,capitalise
postname=%<text%>
postdesc=#dot,none
prelocation=#none,enspace,space,dotfill,hfill
location=#hide,list,first
see=#comma,brackets,dot,space,nosep,semicolon,location
symboldesc=#symbol,desc,(symbol) desc,desc (symbol),symbol desc,desc symbol
namefont=%<font cmd%>
# options passed to datatool
delimiter=%<char%>
separator=%<char%>
default-name=%<db name%>
new-value-expand#true,false
new-value-trim#true,false
store-datum#true,false
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

#ifOption:math=fp
#include:fp
#endif

#ifOption:math=pgfmath
#include:pgfrcs
#include:pgfkeys
#include:pgfmath
#endif

#keyvals:\DTLsetup
index={%<keyvals%>}
#endkeyvals

## Defining Index/Glossary Databases ##
\newgidx{db%specialDef}{title%text}#s#%db
\newgidx[options%keyvals]{db%specialDef}{title%text}#s#%db

## Loading Data Created by datatooltk ##
\loadgidx{file}{title%text}
\loadgidx[options%keyvals]{file}{title%text}

#keyvals:\loadgidx,\newgidx,\printterms
balance#true,false
heading=%<text%>
post-heading=%<text%>
postheading=%<text%>
show-groups#true,false
showgroups#true,false
sort={%<sort code%>}
style=#index,indexalign,align,gloss,dict
#endkeyvals

## Defining Terms ##
\newterm{name}
\newterm[options%keyvals]{name}

#keyvals:\newterm#c,\newacro#c
database=%<database name%>
label=%<label%>
parent=%<parent label%>
text=%<text%>
plural=%<plural form%>
symbol=%<symbol%>
description=%<text%>
see=%<label%>
seealso=%<label%>
sort=%<text%>
short=%<text%>
shortplural=%<text%>
long=%<text%>
longplural=%<text%>
#endkeyvals

\DTLgidxName{forename}{surname}
\DTLgidxNameNum{number}
\DTLgidxPlace{country/county}{city/town}
\DTLgidxSubject{subject}{text}
\DTLgidxOffice{office}{name}
\DTLgidxRank{title%plain}{forename/initials}
\DTLgidxParticle{particle}{surname}
\DTLgidxMac{text}
\DTLgidxSaint{text}
\DTLgidxParen{text}
\DTLgidxIgnore{text}
\DTLgidxStripBackslash{cmd}
\newtermlabelhook#*
\newtermsorthook#*

## Referencing Terms ##
\useentry{label%plain}{col key}
\Useentry{label%plain}{col key}
\USEentry{label%plain}{col key}
\useentrynl{label%plain}{col key}#*
\Useentrynl{label%plain}{col key}#*
\USEentrynl{label%plain}{col key}#*
\glslink{label%plain}{text}
\glsdispentry{label%plain}{col key}
\Glsdispentry{label%plain}{col key}
\DTLgidxFetchEntry{cmd}{label%plain}{col key}#d
\glsadd{label%plain}
\glsaddall{db%special}
\gls{label%plain}#*
\glspl{label%plain}#*
\glsnl{label%plain}#*
\glsplnl{label%plain}#*
\Gls{label%plain}#*
\Glspl{label%plain}#*
\Glsnl{label%plain}#*
\Glsplnl{label%plain}#*
\glssym{label%plain}#*
\Glssym{label%plain}#*

## Locations ##
\DTLgidxCounter#*
\DTLgidxSetCompositor{char}#*

## Adding Extra Fields ##
\newtermaddfield{col key}{new term key}{default value}#*
\newtermaddfield{col key}{new term key}[data type]{default value}#*
\newtermaddfield{col key}[placeholder cmd]{new term key}{default value}#*
\newtermaddfield{col key}[placeholder cmd]{new term key}[data type]{default value}#*
\newtermaddfield[db list]{col key}{new term key}{default value}#*
\newtermaddfield[db list]{col key}{new term key}[data type]{default value}#*
\newtermaddfield[db list]{col key}[placeholder cmd]{new term key}{default value}#*
\newtermaddfield[db list]{col key}[placeholder cmd]{new term key}[data type]{default value}#*
\field{key%plain}#*

## Abbreviations ##
\newacro{short}{long}
\newacro[options%keyvals]{short}{long}
\acronymfont{text}#*
\DTLgidxAcrStyle{long}{short}
\acr{label%plain}
\acrpl{label%plain}
\Acr{label%plain}
\Acrpl{label%plain}
\DTLgidxFormatAcr{label}{long}{short}#*
\DTLgidxFormatAcrUC{label}{long}{short}#*
\glsreset{label%plain}
\glsunset{label%plain}
\glsresetall{db%special}
\glsunsetall{db%special}

## 7.8 Displaying the Index or Glossary ##
\printterms
\printterms[options%keyvals]

#keyvals:\printterms
child=#named,noname
child-sort#true,false
childsort#true,false
columns=%<integer%>
condition={%<condition%>}
database=#%db
include-if=%<definition%>
include-if-fn=%<cmd%>
location=#hide,list,first
location-width=##L
locationwidth=##L
name-case=#nochange,uc,lc,firstuc,capitalise
namecase=#nochange,uc,lc,firstuc,capitalise
name-font=%<font cmd%>
namefont=%<font cmd%>
post-name=%<text%>
postname=%<text%>
post-desc=#dot,none
postdesc=#dot,none
pre-location=#none,enspace,space,dotfill,hfill
prelocation=#none,enspace,space,dotfill,hfill
see=#comma,brackets,dot,space,nosep,semicolon,location
symbol-desc=#symbol,desc,(symbol) desc,desc (symbol),symbol desc,desc symbol
symboldesc=#symbol,desc,(symbol) desc,desc (symbol),symbol desc,desc symbol
symbol-width=##L
symbolwidth=##L
#endkeyvals

\DTLgidxCurrentdb#*
\DTLgidxGroupHeaderTitle{text}#*
\printtermsrestoreonecolumn#*
\DTLgidxSetColumns{integer}#*
\DTLgidxNameCase{text}#*
\DTLgidxNameFont{text}#*
\DTLgidxPostName#*
\DTLgidxPostChildName#*
\DTLgidxChildStyle{text}#*
\DTLgidxChildCountLabel#*
\DTLgidxSymDescSep#*
\DTLgidxFormatDesc{text}#*
\DTLgidxPostDescription#*
\DTLgidxEndItem#*
\DTLgidxPreLocation#*
\DTLgidxPostLocation#*
\DTLgidxFormatSee{tag}{label list}#*
\DTLgidxFormatSeeAlso{tag}{label list}#*
\DTLgidxSeeTagFont{text}#*
\DTLidxFormatSeeItem{label}#*
\DTLidxSeeLastSep#*
\DTLidxSeeSep#*
\seename#*
\seealsoname#*
\datagidxsymbolwidth#*L
\datagidxlocationwidth#*L
\datagidxsymalign#*
\datagidxlocalign#*
\DTLgidxChildSep#*
\DTLgidxPostChild#*
\DTLgidxDictPostItem#*
\datagidxdictindent#*
\DTLgidxDictHead#*
\DTLgidxCategoryNameFont#*
\DTLgidxCategorySep#*
\DTLgidxSubCategorySep#*

## Supplementary Commands ##
\DTLgidxEnableHyper#*
\DTLgidxDisableHyper#*
\iftermexists{label%plain}{true code}{false code}#*
\ifentryused{label%plain}{true code}{false code}#*
\datagidxprevgroup#*
\DTLgidxAssignList#*
\datagidxmapdata{body}#*
\postnewtermhook#*
\datagidxlastlabel#*
\DTLgidxNoFormat{text}#*
\DTLgidxGobble{text}#*
\datagidxconvertchars#*
\datagidxnewstyle{name}{definitions}#*
\datagidxtarget{target name}{text}#*
\datagidxlink{target name}{text}#*
\theDTLgidxChildCount#*
\theHDTLgidxChildCount#S

# misc
\DTLgidxForeachEntry{body}#*
\DTLgidxLocation#*
\DTLgidxSetDefaultDB{db%special}#*
\datagidxcurrentgroup#*
\datagidxend#*
\datagidxitem#*
\datagidxsetstyle{style name}#*
\datagidxstart#*
\datagidxwordifygreek#*

# not in main documentation
\DTLgidxChildren#S
\DTLgidxChildrenSeeAlso#S
\DTLgidxDoSeeOrLocation#S
\DTLgidxLocationFF{loc1}{loc2}#S
\DTLgidxLocationF{loc1}{loc2}#S
\DTLgidxLocationSep#S
\DTLgidxNoHeading#S
\DTLgidxSee#S
\DTLgidxSeeAlso#S
\DTLgidxSeeList{label list}#S
\DTLgidxSymbolDescLeft#S
\DTLgidxSymbolDescRight#S
\DTLgidxSymbolDescription#S
\datagidxbalancefalse#S
\datagidxbalancetrue#S
\datagidxchildend#S
\datagidxchilditem#S
\datagidxchildstart#S
\datagidxdb{entry}#S
\datagidxdescwidth#S
\datagidxdictparshape#S
\datagidxdoseealso{arg}#S
\datagidxextendedtoascii#S
\datagidxgroupheader#S
\datagidxgroupsep#S
\datagidxhighoptfilename{filename%file}#S
\datagidxindent#S
\datagidxnamewidth#S
\datagidxseealsoend#S
\datagidxseealsostart#S
\datagidxshowgroupsfalse#S
\datagidxshowgroupstrue#S
\datagidxshowifdraft{arg}#S
\datagidxstripaccents#S
\datagidxtermkeys#S
\dtldofirstlocation#S
\dtldolocationlist#S
\ifdatagidxbalance#S
\ifdatagidxshowgroups#S
\ifnewtermfield{name}{true}{false}#S
\newtermfield{name}#S
\printtermsstartpar#S

# deprecated
\DTLgidxAddLocationType{cmd}#S