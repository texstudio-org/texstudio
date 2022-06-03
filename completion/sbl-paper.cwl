# sbl-paper package
# Matthew Bertucci 2022/05/30 for release 2020/11/04

#include:geometry
#include:textcase
#include:setspace
#include:titlesec
#include:titletoc
#include:fancyhdr
#include:footmisc
#include:bibleref-parse
#include:biblatex
# loads style=sbl option of biblatex
#include:imakeidx
#include:hyperref

#keyvals:\usepackage/sbl-paper#c
jblstyle
#endkeyvals

\firstsection{title}#L2
\firstsection[short title]{title}#L2
\institution{institution%text}
\professor{name}
\course{course%text}

\Pbibleverse{passage}
\Pbibleverse[options%keyvals]{passage}
\Pibibleverse{passage}
\Pibibleverse[options%keyvals]{passage}

#keyvals:\Pbibleverse,\Pibibleverse
comma=#list,chvsep,likeBR,preferchvsep,preferlikeBR
#endkeyvals

# from style=sbl option of biblatex
#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c
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