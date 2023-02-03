# datagidx package
# Matthew Bertucci 2022/06/07 for v2.32

#include:datatool
#include:etoolbox
#include:xkeyval
#include:mfirstuc
#include:xfor
#include:multicol
#include:textcase
#include:afterpage

#keyvals:\usepackage/datagidx#c
utf8#true,false
optimize=#off,low,high
columns=%<integer%>
child=#named,noname
namecase=#nochange,uc,lc,firstuc,capitalise
namefont=%<font cmd%>
postname=%<text%>
postdesc=#dot,none
prelocation=#none,enspace,space,dotfill,hfill
location=#hide,list,first
see=#comma,brackets,dot,space,nosep,semicolon,location
symboldesc=#symbol,desc,(symbol) desc,desc (symbol),symbol desc,desc symbol
compositor=%<symbol%>
draft
final
verbose#true,false
nowarn#true,false
#endkeyvals

## 7.1 Defining Index/Glossary Databases ##
\loadgidx{file}{title%text}
\loadgidx[options%keyvals]{file}{title%text}
\newgidx{db%specialDef}{title%text}#s#%db
\newgidx[options%keyvals]{db%specialDef}{title%text}#s#%db

#keyvals:\loadgidx,\newgidx
showgroups#true,false
style=#index,indexalign,align,gloss,dict
sort={%<sort cmd%>}
balance#true,false
heading=%<text%>
postheading=%<text%>
#endkeyvals

## 7.2 Locations ##
\DTLgidxCounter#*
\DTLgidxAddLocationType{cmd}
\DTLgidxSetCompositor{symbol}

## 7.3 Defining Terms ##
\newterm{name}
\newterm[options%keyvals]{name}

#keyvals:\newterm#c,\newacro#c
database=%<database name%>
label=%<label%>
sort=%<sort key%>
parent=%<parent entry%>
text=%<text%>
description=%<text%>
plural=%<plural form%>
symbol=%<symbol%>
short=%<short form%>
long=%<long form%>
shortplural=%<short plural form%>
longplural=%<long plural form%>
see=%<label%>
seealso=%<label%>
#endkeyvals

\DTLgidxSetDefaultDB{label%plain}
\DTLgidxParen{text}
\DTLgidxPlace{country/county}{city/town}
\DTLgidxSubject{subject}{text}
\DTLgidxName{forename}{surname}
\DTLgidxRank{title%plain}{forename/initials}
\DTLgidxNameNum{number}
\DTLgidxMac{text}
\DTLgidxSaint{text}
\DTLgidxParticle{text}
\DTLgidxOffice{office}{name}
\newtermlabelhook#*
\DTLgidxNoFormat{text}
\DTLgidxGobble{text}
\DTLgidxIgnore
\DTLgidxStripBackslash{cmd}

## 7.4 Referencing Terms ##
\useentry{label%plain}{field}
\Useentry{label%plain}{field}
\USEentry{label%plain}{field}
\useentrynl{label%plain}{field}#*
\Useentrynl{label%plain}{field}#*
\USEentrynl{label%plain}{field}#*
\glslink{label%plain}{text}
\glsdispentry{label%plain}{field}
\Glsdispentry{label%plain}{field}
\DTLgidxFetchEntry{cmd}{label%plain}{field}#d
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

## 7.5 Adding Extra Fields ##
\newtermaddfield{field name}{key name}{default value}#*
\newtermaddfield[db list]{field name}{key name}{default value}#*
\field{key%plain}#*

## 7.6 Acronyms ##
\newacro{short}{long}
\newacro[options%keyvals]{short}{long}
\acronymfont#*
\DTLgidxAcrStyle{long}{short}

\acr{label%plain}
\acrpl{label%plain}
\Acr{label%plain}#*
\Acrpl{label%plain}#*
\glsreset{label%plain}
\glsunset{label%plain}
\glsresetall{db%special}
\glsunsetall{db%special}

## 7.7 Conditionals ##
\iftermexists{label%plain}{true case}{false case}#*
\ifentryused{label%plain}{true case}{false case}#*

## 7.8 Displaying the Index or Glossary ##
\printterms
\printterms[options%keyvals]

#keyvals:\printterms
database=%<database name%>
postdesc=#dot,none
prelocation=#none,enspace,space,dotfill,hfill
location=#hide,list,first
symboldesc=#symbol,desc,(symbol) desc,desc (symbol),symbol desc,desc symbol
columns=%<integer%>
namecase=#nochange,uc,lc,firstuc,capitalise
namefont=%<font cmd%>
postname=%<text%>
see=#comma,brackets,dot,space,nosep,semicolon,location
child=#named,noname
showgroups#true,false
style=#index,indexalign,align,gloss,dict
symbolwidth=##L
locationwidth=##L
childsort#true,false
heading=%<text%>
postheading=%<text%>
sort={%<sort cmd%>}
balance#true,false
condition={%<condition%>}
#endkeyvals

\DTLgidxChildSep#*
\DTLgidxPostChild#*
\DTLgidxCategoryNameFont#*
\DTLgidxCategorySep#*
\DTLgidxSubCategorySep#*
\DTLgidxDictPostItem#*
\datagidxdictindent#*

\DTLgidxCurrentdb

# not in main documentation
\datagidxbalancefalse#*
\datagidxbalancetrue#*
\datagidxchildend#*
\datagidxchilditem#*
\datagidxchildstart#*
\datagidxconvertchars#*
\datagidxcurrentgroup#*
\datagidxdb{entry}#*
\datagidxdescwidth#*
\datagidxdictparshape#*
\datagidxdoseealso{arg}#*
\datagidxend#*
\datagidxextendedtoascii#*
\datagidxgroupheader#*
\datagidxgroupsep#*
\datagidxhighoptfilename{filename%file}#*
\datagidxindent#*
\datagidxitem#*
\datagidxlastlabel#*
\datagidxlink{arg1}{arg2}#*
\datagidxlocalign#*
\datagidxlocationwidth#*
\datagidxnamewidth#*
\datagidxprevgroup#*
\datagidxseealsoend#*
\datagidxseealsostart#*
\datagidxsetstyle{style}#*
\datagidxshowgroupsfalse#*
\datagidxshowgroupstrue#*
\datagidxshowifdraft{arg}#*
\datagidxstart#*
\datagidxstripaccents#*
\datagidxsymalign#*
\datagidxsymbolwidth#*
\datagidxtarget{arg}#*
\datagidxtermkeys#*
\datagidxwordifygreek#*
\dtldofirstlocation#*
\dtldolocationlist#*
\DTLgidxChildCountLabel#*
\DTLgidxChildren#*
\DTLgidxChildrenSeeAlso#*
\DTLgidxChildStyle{text}#*
\DTLgidxDictHead#*
\DTLgidxDisableHyper#*
\DTLgidxDoSeeOrLocation#*
\DTLgidxEnableHyper#*
\DTLgidxForeachEntry{body}#*
\DTLgidxFormatAcr{label}{long}{short}#*
\DTLgidxFormatAcrUC{label}{long}{short}#*
\DTLgidxFormatDesc{text}#*
\DTLgidxFormatSee{tag}{label list}#*
\DTLgidxFormatSeeAlso{tag}{label list}#*
\DTLgidxGroupHeaderTitle{text}#*
\DTLgidxLocation#*
\DTLgidxLocationF{loc1}{loc2}#*
\DTLgidxLocationFF{loc1}{loc2}#*
\DTLgidxLocationSep#*
\DTLgidxNameCase{text}#*
\DTLgidxNameFont{text}#*
\DTLgidxNoHeading#*
\DTLgidxPostChildName#*
\DTLgidxPostDescription#*
\DTLgidxPostName#*
\DTLgidxPreLocation#*
\DTLgidxSee#*
\DTLgidxSeeAlso#*
\DTLgidxSeeList{label list}#*
\DTLgidxSeeTagFont{text}#*
\DTLgidxSetColumns{integer}#*
\DTLgidxSymbolDescLeft#*
\DTLgidxSymbolDescRight#*
\DTLgidxSymbolDescription#*
\DTLgidxSymDescSep#*
\DTLidxFormatSeeItem{label}#*
\DTLidxSeeLastSep#*
\DTLidxSeeSep#*
\ifdatagidxbalance#*
\ifdatagidxshowgroups#*
\ifnewtermfield{name}{true}{false}#*
\newtermfield{name}#*
\postnewtermhook#*
\printtermsrestoreonecolumn#*
\printtermsstartpar#*
\seealsoname#*
\seename#*
\theDTLgidxChildCount#*
\theHDTLgidxChildCount#*
