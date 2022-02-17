# datagidx package
# Matthew Bertucci 10/31/2021 for v2.32

#include:datatool
#include:etoolbox
#include:xkeyval
#include:mfirstuc
#include:xfor
#include:multicol
#include:textcase
#include:afterpage

#keyvals:\usepackage/datagidx#c
final
draft
#endkeyvals

## 7.1 Defining Index/Glossary Databases ##
\loadgidx{filename}{title%plain}
\loadgidx[options%keyvals]{filename}{title%plain}
\newgidx{db}{title%plain}#s#%db
\newgidx[options%keyvals]{db}{title%plain}#s#%db

#keyvals:\loadgidx,\newgidx
showgroups#true,false
style=#index,indexalign,align,gloss,dict
sort=
balance#true,false
heading=
postheading=
#endkeyvals

## 7.2 Locations ##
\DTLgidxCounter#*
\DTLgidxAddLocationType{cmd}
\DTLgidxSetCompositor

## 7.3 Defining Terms ##
\newterm{name}
\newterm[options%keyvals]{name}

#keyvals:\newterm#c
database=
label=
sort=
parent=
text=
description=
plural=
symbol=
short=
long=
shortplural=
longplural=
see=
seealso=
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

#keyvals:\newacro
database=
label=
parent=
symbol=
shortplural=
longplural=
see=
seealso=
#endkeyvals

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
database=
postdesc=#dot,none
prelocation=#none,enspace,space,dotfill,hfill
location=#hide,list,first
symboldesc=#symbol,desc,(symbol) desc,desc (symbol),symbol desc,desc symbol
columns=%<integer%>
namecase=#nochange,uc,lc,firstuc,capitalise
namefont=
postname=
see=#comma,brackets,dot,space,nosep,semicolon,location
child=#named,noname
showgroups#true,false
style=#index,indexalign,align,gloss,dict
symbolwidth=##L
locationwidth=##L
childsort#true,false
heading=
postheading=
sort=
balance#true,false
condition=
#endkeyvals

\DTLgidxChildSep#*
\DTLgidxPostChild#*
\DTLgidxCategoryNameFont#*
\DTLgidxCategorySep#*
\DTLgidxSubCategorySep#*
\DTLgidxDictPostItem#*
\datagidxdictindent#*

\DTLgidxCurrentdb
