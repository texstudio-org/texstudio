# glossary-table package
# Matthew Bertucci 2022/11/09 for v1.50

#include:longtable
#include:array
#include:booktabs

\printunsrttable
\printunsrttable[options%keyvals]

#keyvals:\printunsrttable
# same options as \printunsrtglossary except nogroupskip, nonumberlist, and style
title=%<text%>
toctitle=%<text%>
numberedsection=#false,nolabel,autolabel
nopostdot#true,false
entrycounter#true,false
subentrycounter#true,false
sort=#word,letter,standard,use,def,nocase,case
target#true,false
targetnameprefix=%<prefix%>
prefix=%<prefix%>
label=##l
groups#true,false
leveloffset=%<<n> or ++<n>%>
preamble=%<text%>
postamble=%<text%>
flatten#true,false
# additional options
blocks=%<n%>
header#true,false
rules#true,false
blocksep=%<alignment spec%>
par=#false,justified,ragged
other=%<field-label%>
init={%<code%>}
block-style=#name,name-desc,desc-name,name-symbol,symbol-name,name-other,other-name,symbol-other,other-symbol,name-symbol-desc,name-desc-symbol,name-other-desc,desc-other-name,name-symbol-other-desc,name-other-symbol-desc,desc-symbol-other-name,desc-other-symbol-name
#endkeyvals

\glstableiffilter{label}{true}{false}#*
\glstableChildEntries{label}#*
\glstableiffilterchild{label}{true}{false}#*
\glstablePreChildren#*
\begin{glstablesubentries}#*\tabular
\end{glstablesubentries}#*
\glstablesubentryalign#*
\glstableblocksubentrysep#*
\glstablecaption{lot title%text}{title%text}{label code}#*
\glstablenextcaption{lot title%text}{title%text}#*
\glstablepostnextcaption#*
\glstablenameheader#*
\glstabledescheader#*
\glstablesymbolheader#*
\glstableotherheader#*

\glstablesetstyle{style%keyvals}

#keyvals:\glstablesetstyle
name
name-desc
desc-name
name-symbol
symbol-name
name-other
other-name
symbol-other
other-symbol
name-symbol-desc
name-desc-symbol
name-other-desc
desc-other-name
name-symbol-other-desc
name-other-symbol-desc
desc-symbol-other-name
desc-other-symbol-name
#endkeyvals

\glstablenewline#*
\glstableleftalign{width}#*
\glstablerightalign{width}#*
\glstablecenteralign{width}#*
\glstablenamecolalign#*
\glstabledesccolalign#*
\glstablesymbolcolalign#*
\glstableothercolalign#*
\glstablenamewidth#*
\glstabledescwidth#*
\glstablesymbolwidth#*
\glstableotherwidth#*
\glstableblockwidth#*
\glstablepostpreambleskip#*
\glstableprepostambleskip#*
\glstableNameFmt{text}#*
\glstableSubNameFmt{text}#*
\glstableSymbolFmt{text}#*
\glstableSubSymbolFmt{text}#*
\glstableDescFmt{text}#*
\glstableSubDescFmt{text}#*
\glstableotherfield#*
\glstableOtherFmt{text}#*
\glstableOther{label}#*
\glstableSubOtherNoDesc{label}#*
\glstableifhasotherfield{label}{true}{false}#*
\glstableHeaderFmt{text}#*

# not documented
\glstableblockalign#S
\glstableblockentry{arg1}#S
\glstableblockheader#S
\glstableblockperrowcount#S
\glstableblocksubentry{arg1}#S
\glstablecolsperblock#S
\glstablecurrentblockindex#S
\glstableDesc{arg1}#S
\glstableDescWithOther{arg}#S
\glstablefinishlengthupdates#S
\glstablefinishrow#S
\glstablefirsthead{arg1}#S
\glstablefoot{arg1}#S
\glstablefootstrut#S
\glstableGroupHeaderFmt#S
\glstablegroupheading{arg1}#S
\glstablehead{arg1}#S
\glstableifmeasuring#S
\glstableifmeasuring{arg1}{arg2}#S
\glstableifpar{arg1}#S
\glstableinitlengthupdates#S
\glstablelastfoot{arg1}#S
\glstablelengthupdate{arg1}#S
\glstablemeasureandupdate{arg1}{arg2}#S
\glstableName{arg}#S
\glstableNameNoDesc{arg1}#S
\glstableNameSingleFmt{text}#S
\glstableNameSinglePostName#S
\glstableNameSinglePostSubName#S
\glstableNameSingleSubSuppl{arg1}#S
\glstableNameSingleSuppl{arg1}#S
\glstableNameSingleSymSep#S
\glstableNameTarget{arg1}#S
\glstablenewstyle{arg1}{arg2}#S
\glstableOtherNoDesc{arg1}#S
\glstableOtherSep#S
\glstableOtherWithSep{arg1}{arg2}{arg3}#S
\glstablePostGroupNewLine#S
\glstablerowspan{arg1}#S
\glstablesetstyle{arg1}#S
\glstablespanwidth#S
\glstableSubDesc{arg1}#S
\glstableSubDescSymbolOther{arg}#S
\glstablesubentryalign#S
\glstablesubentrywidth#S
\glstableSubName{arg}#S
\glstableSubNameNoDesc{arg1}#S
\glstableSubNameSep#S
\glstableSubNameSingleFmt{text}#S
\glstableSubNameSymbolNoDesc{arg}#S
\glstableSubNameTarget{arg1}#S
\glstableSubOtherSep#S
\glstableSubOtherWithSep{arg1}{arg2}{arg3}#S
\glstableSubOtherWithSep{arg1}{arg2}{arg3}#S
\glstableSubSep#S
\glstableSubSymbol{arg}#S
\glstableSubSymbolName{arg}#S
\glstableSubSymbolNameFmt{text}#S
\glstableSubSymbolNameTarget{arg1}#S
\glstableSubSymbolWithSep{arg1}{arg2}{arg3}#S
\glstableSymbol{arg}#S
\glstableSymbolName{arg}#S
\glstableSymbolNameFmt{text}#S
\glstableSymbolNameTarget{arg1}#S
\glstabletotalcols#S
