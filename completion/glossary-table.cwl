# glossary-table package
# Matthew Bertucci 2022/10/22 for v1.49

#include:glossary-longbooktabs

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
block-style=#name-desc,desc-name,name-symbol,symbol-name,name-symbol-desc,name-desc-symbol,name,name-other,other-name,symbol-other,other-symbol
#endkeyvals

\glstableiffilter{label}{true}{false}#*
\glstablenameheader#*
\glstabledescheader#*
\glstablesymbolheader#*
\glstableotherheader#*

# not documented
\begin{glstablesubentries}#S
\end{glstablesubentries}#S
\glstableblockalign#S
\glstableblockentry{arg1}#S
\glstableblockheader#S
\glstableblockperrowcount#S
\glstableblocksubentry{arg1}#S
\glstableblocksubentrysep#S
\glstableblockwidth#S
\glstablecaption{arg1}{arg2}{arg3}#S
\glstablecenteralign{arg1}#S
\glstableChildEntries{arg1}#S
\glstablecolsperblock#S
\glstablecurrentblockindex#S
\glstableDesc{arg1}#S
\glstabledesccolalign#S
\glstableDescFmt{arg1}#S
\glstabledescwidth#S
\glstablefinishlengthupdates#S
\glstablefinishrow#S
\glstablefirsthead{arg1}#S
\glstablefoot{arg1}#S
\glstableGroupHeaderFmt#S
\glstablegroupheading{arg1}#S
\glstablehead{arg1}#S
\glstableHeaderFmt{arg1}#S
\glstableifmeasuring#S
\glstableifmeasuring{arg1}{arg2}#S
\glstableifpar{arg1}#S
\glstableinitlengthupdates#S
\glstablelastfoot{arg1}#S
\glstableleftalign{arg1}#S
\glstablelengthupdate{arg1}#S
\glstablemeasureandupdate{arg1}{arg2}#S
\glstablenamecolalign#S
\glstableNameFmt{arg1}#S
\glstableNameNoDesc{arg1}#S
\glstableNameSingleFmt{arg1}#S
\glstableNameSinglePostName#S
\glstableNameSinglePostSubName#S
\glstableNameSingleSubSuppl{arg1}#S
\glstableNameSingleSuppl{arg1}#S
\glstableNameSingleSymSep#S
\glstableNameTarget{arg1}#S
\glstablenamewidth#S
\glstablenewstyle{arg1}{arg2}#S
\glstablenextcaption{arg1}{arg2}#S
\glstableOther{arg1}#S
\glstableotherfield#S
\glstableOtherNoDesc{arg1}#S
\glstableOtherSep#S
\glstablepostnextcaption#S
\glstablePreChildren#S
\glstablerightalign{arg1}#S
\glstablerowspan{arg1}#S
\glstablesetstyle{arg1}#S
\glstableSubDesc{arg1}#S
\glstableSubDescFmt{arg1}#S
\glstableSubNameFmt{arg1}#S
\glstableSubNameNoDesc{arg1}#S
\glstableSubNameSingleFmt{arg1}#S
\glstableSubNameTarget{arg1}#S
\glstableSubOtherNoDesc{arg1}#S
\glstableSubSymbolFmt{arg1}#S
\glstableSubSymbolNameFmt{arg1}#S
\glstableSubSymbolNameTarget{arg1}#S
\glstablesymbolcolalign#S
\glstableSymbolFmt{arg1}#S
\glstableSymbolNameFmt{arg1}#S
\glstableSymbolNameTarget{arg1}#S
\glstablesymbolwidth#S
\glstabletotalcols#S