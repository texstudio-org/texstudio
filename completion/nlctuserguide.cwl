# nlctuserguide package
# Matthew Bertucci 2022/10/18 for v1.08

#include:iftex
#include:etoolbox
#include:fontspec
#include:fontawesome
#include:twemojis
#include:pifont
#include:amsfonts
#include:textcomp
#include:array
#include:upquote
#include:hologo
#include:varioref
#include:xcolor
#include:tcolorbox
# loads breakable, skins, and listings tcolorbox options
#include:hyperref
#include:mfirstuc
#include:glossaries-extra
# loads (among others) record=nameref, symbols, and stylemods={mcols,bookindex,topic,longextra} options of glossaries-extra
#include:attachfile

#keyvals:\usepackage/nlctuserguide#c
xr
vref
novref
atsymgroup
noatsymgroup
deephierarchy
# options passed to glossaries-extra (those already passed not listed)
debug=#false,true,showtargets,showaccsupp,showwrgloss,all
savewrites#true,false
hyperfirst#true,false
writeglslabels
writeglslabelnames
toc#true,false
numberline#true,false
section=%<section unit%>
ucmark#true,false
numberedsection=#false,nolabel,autolabel
savenumberlist#true,false
entrycounter#true,false
counterwithin=%<counter%>
subentrycounter#true,false
style=%<style-name%>
nonumberlist
seeautonumberlist
counter=%<counter%>
nopostdot#true,false
nogroupskip#true,false
seenoindex=#error,warn,ignore
esclocations#true,false
indexonlyfirst#true,false
sanitizesort#true,false
sort=#none,clear,def,use,standard
order=#word,letter
automake=#false,delayed,immediate,makegloss,lite
automakegloss
automakeglosslite
disablemakegloss
restoremakegloss
nohypertypes={%<list%>}
nomain
numbers
index
noglossaryindex
acronyms
acronymlists={%<value%>}
shortcuts=#acronyms,acro,ac,abbreviations,abbr,acother,abother,other,all,true,none,false
mfirstuc=#expanded,unexpanded
kernelglossredefs={%<value%>}
showtargets=#left,right,innerleft,innerright,annoteleft,annoteright
postdot
postpunc=#comma,dot,none
prefix
accsupp
undefaction=#warn,error
indexcrossrefs#true,false
autoseeindex#true,false
record=#off,only,nameref,hybrid
bibglsaux=%<basename%>
equations
docdef=#false,true,restricted,atom
nomissingglstext#true,false
abbreviations
nowarn
nolangwarn
noredefwarn
translate=#true,false,babel
notranslate
nolong
nolist
notree
nostyles
makeindex
xindy
xindygloss
xindynoglsnumbers
acronym#true,false
languages=%<language%>
#endkeyvals

#ifOption:xr
#include:xr-hyper
#endif

#ifOption:accsupp
#include:glossaries-accsupp
#keyvals:\newabbreviation#c,\newabbr#c
access=%<text%>
textaccess=%<text%>
pluralaccess=%<text%>
firstaccess=%<text%>
firstpluralaccess=%<text%>
shortaccess=%<text%>
shortpluralaccess=%<text%>
longaccess=%<text%>
longpluralaccess=%<text%>
#endkeyvals
#endif
#ifOption:prefix
#include:glossaries-prefix
#endif
#ifOption:abbreviations
\printabbreviations
\printabbreviations[options%keyvals]
\printunsrtabbreviations#*
\printunsrtabbreviations[options%keyvals]#*
\abbreviationsname#*
#endif
#ifOption:debug=showaccsupp
\glsshowaccsupp{options}{tag}{replacement text}
#endif
#ifOption:translate=babel
#include:glossaries-babel
#endif
#ifOption:numbers
\printnumbers
\printnumbers[options%keyvals]
\glsxtrnewnumber{label}{number}#l
\glsxtrnewnumber[options%keyvals]{label}{number}#l
\printunsrtnumbers#*
\printunsrtnumbers[options%keyvals]#*
\glsxtrpostdescnumber#*
#endif
#ifOption:index
\newterm{term}
\newterm[options%keyvals]{term}
\printindex
\printindex[options%keyvals]
\printunsrtindex#*
\printunsrtindex[options%keyvals]#*
\glsxtrpostdescindex#*
#endif
#ifOption:acronym
\printacronyms
\printacronyms[options%keyvals]
\printunsrtacronyms#*
\printunsrtacronyms[options%keyvals]#*
#endif
#ifOption:acronym=true
\printacronyms
\printacronyms[options%keyvals]
\printunsrtacronyms#*
\printunsrtacronyms[options%keyvals]#*
#endif
#ifOption:acronyms
\printacronyms
\printacronyms[options%keyvals]
\printunsrtacronyms#*
\printunsrtacronyms[options%keyvals]#*
#endif
#ifOption:shortcuts=other
\newentry{label}{keyvals}#l
\newsym{label}{symbol}#l
\newsym[options%keyvals]{label}{symbol}#l
\newnum{label}{number}#l
\newnum[options%keyvals]{label}{number}#l
#endif
#ifOption:shortcuts=acother
\newentry{label}{keyvals}#l
\newsym{label}{symbol}#l
\newsym[options%keyvals]{label}{symbol}#l
\newnum{label}{number}#l
\newnum[options%keyvals]{label}{number}#l
#endif
#ifOption:shortcuts=abother
\newentry{label}{keyvals}#l
\newsym{label}{symbol}#l
\newsym[options%keyvals]{label}{symbol}#l
\newnum{label}{number}#l
\newnum[options%keyvals]{label}{number}#l
#endif
#ifOption:shortcuts=all
\newentry{label}{keyvals}#l
\newsym{label}{symbol}#l
\newsym[options%keyvals]{label}{symbol}#l
\newnum{label}{number}#l
\newnum[options%keyvals]{label}{number}#l
\newabbr{label}{short}{long}#l
\newabbr[options%keyvals]{label}{short}{long}#l
#endif
#ifOption:shortcuts=true
\newentry{label}{keyvals}#l
\newsym{label}{symbol}#l
\newsym[options%keyvals]{label}{symbol}#l
\newnum{label}{number}#l
\newnum[options%keyvals]{label}{number}#l
\newabbr{label}{short}{long}#l
\newabbr[options%keyvals]{label}{short}{long}#l
#endif
#ifOption:shortcuts=abbreviations
\newabbr{label}{short}{long}#l
\newabbr[options%keyvals]{label}{short}{long}#l
#endif
#ifOption:shortcuts=abbr
\newabbr{label}{short}{long}#l
\newabbr[options%keyvals]{label}{short}{long}#l
#endif
#ifOption:xindy
\GlsSetXdyLanguage{language}
\GlsSetXdyLanguage[glossary type]{language}
\GlsSetXdyCodePage{code}
\GlsAddXdyCounters{counter list}
\GlsAddXdyAttribute{name}
\GlsAddXdyLocation{name}{definition}
\GlsAddXdyLocation[prefix-location]{name}{definition}
\GlsSetXdyLocationClassOrder{location names}
\GlsSetXdyMinRangeLength{integer}
\GlsSetXdyFirstLetterAfterDigits{letter}
\GlsSetXdyNumberGroupOrder{relative location}
\GlsAddLetterGroup{arg1}{arg2}
\GlsAddSortRule{arg1}{arg2}
\GlsAddXdyAlphabet{name}{definition}
\GlsAddXdyStyle{xindy style}
\GlsSetXdyStyles{xindy styles}
#endif

\actext{acronym}
\app{application}
\app{application}[suffix]#*
\appdef{application}
\appfmt{application}
\apptext{application}
\araracont
\araraline{arara code}
\banned
\BibTeX
\blog{URL-path%URL}{link text%text}
\booktitle{text}
\cbeg{envname}
\cend{envname}
\cls{class}
\cls{class}[suffix]#*
\clsfmt{class%plain}
\clsoptfmt{class-option}
\clstext{class}
\cmd{csname}
\cmddef*[options%keyvals]{csname}#*
\cmddef*{csname}
\cmddef[options%keyvals]{csname}#*
\cmddef{csname}
\cmddefsyntax{keyvals}{csname}
\cmdmod{arg}
\cmdmod{arg}[suffix]#*
\code{code}
\codebackslash
\codepar
\comment{text}
\common
\conditionsyntax
\conno
\conyes
\csfmt{csname}
\csmetafmt{cmd-prefix}{meta-text}{cmd-suffix}
\csmetametafmt{cmd-prefix}{meta-text1}{separator}{meta-text2}{cmd-suffix}
\csoptfmt{cmd-option}
\ctanmirror{URL-path%URL}{link text%text}
\ctanmirrordocnofn{URL-path%URL}{link text%text}
\ctanmirrornofn{URL-path%URL}{link text%text}
\ctanpkg{package}
\CTANpkg{package}
\ctanpkgmirror{package}{link text%text}
\ctanref{URL-path%URL}{link text%text}
\ctansupportmirror{URL-path%URL}{link text%text}
\ctr{counter}
\ctr{counter}[suffix]#*
\ctrdef*{counter}
\ctrdef{counter}
\ctrfmt{counter}
\ctrtext{counter}
\dash
\dcolon
\dcomma
\defsemanticcmd[color]{cmd}{font-cmd}{prefix}#d
\defsemanticcmd{cmd}{font-cmd}{prefix}#d
\defval{value}
\deprecated
\dequals
\desc{description%text}
\dfullstop
\dhyphen
\dickimawhref{URL-path%URL}{link text%text}
\dickimawhrefnofn{URL-path%URL}{link text%text}
\docref{link text%text}{PDF-file}
\dsb
\dunderscore#*
\env{envname}
\env{envname}[suffix]#*
\envdef*[options%keyvals]{envname}#*
\envdef*{envname}
\envdef[options%keyvals]{envname}#*
\envdef{envname}
\envfmt{envname}
\envtext{envname}
\eTeX
\exampleref*{label}#r
\Exampleref*{label}#r
\exampleref{label}#r
\Exampleref{label}#r
\examplesref*{labellist}#r
\Examplesref*{labellist}#r
\examplesref{labellist}#r
\Examplesref{labellist}#r
\ext{extension}
\ext{extension}[suffix]#*
\exttext{extension}
\faqitem{item}{link text%text}
\faqpage{category}{link text%text}
\faqspkg{package}
\field{field}{entries}
\figureref*{label}#r
\Figureref*{label}#r
\figureref{label}#r
\Figureref{label}#r
\figuresref*{labellist}#r
\Figuresref*{labellist}#r
\figuresref{labellist}#r
\Figuresref{labellist}#r
\file{file}
\filedef{file}
\filefmt{file}
\fnsym{num}
\fnsymtext{num}{text}
\gabbr{abbrev-name}{short}{long}{desc-cmds}
\gacr{acronym}{short}{long}{desc-cmds}
\gallery{link text%text}
\gallerypage{page-name%URL}{link text%text}
\galleryref{URL-path%URL}{link text%text}
\gallerytopic{package}
\galleryurl{URL-path%URL}
\gapp{application-name}{desc-cmds}
\gcls{class-name}{desc-cmds}
\gclsboolopt{class-option-name}{desc-cmds}
\gclsopt{class-option-name}{desc-cmds}
\gcmd{cmd-name}{desc-cmds}
\gcmdmeta{cmd-prefix}{meta-text}{cmd-suffix}{desc-cmds}
\gcmdmetameta{cmd-prefix}{meta-text1}{separator}{meta-text2}{cmd-suffix}{desc-cmds}
\gcmds{cmd-name}{desc-cmds}
\gcmdsp{cmd-name}{desc-cmds}
\gcond{cmd-name}{desc-cmds}
\gcsboolopt{cmd-option-name}{desc-cmds}
\gcsopt{cmd-option-name}{desc-cmds}
\gctr{counter-name}{desc-cmds}
\genv{env-name}{desc-cmds}
\gext{extension-name}{desc-cmds}
\gfile{file-name}{desc-cmds}
\gfilemeta{file-prefix}{meta-text}{file-suffix}{desc-cmds}
\gfilemetameta{file-prefix}{meta-text1}{separator}{meta-text2}{file-suffix}{desc-cmds}
\gidx{name}{desc-cmds}
\gidxpl{name}{desc-cmds}
\glongswitch{switch-name}{desc-cmds}
\glsbibwriteentry{entry}{entry-label}{desc-cmds}
\gmod{modifier-name}{desc-cmds}
\gopt{option-name}{desc-cmds}
\goptval{option}{value}{desc-cmds}
\gpkg{package-name}{desc-cmds}
\gpunc{punc-name}{desc-cmds}
\gpunccmd{punc-name}{symbol}{desc-cmds}
\gshortswitch{switch-name}{desc-cmds}
\gstyboolopt{package-option-name}{desc-cmds}
\gstyopt{package-option-name}{desc-cmds}
\gterm{term-name}{desc-cmds}
\gtermabbr{term-name}{short}{long}{desc-cmds}
\gtermacr{acronym}{short}{long}{desc-cmds}
\htmlavailable
\idx[options%keyvals]{label}#r
\Idx[options%keyvals]{label}#r
\idx[options%keyvals]{label}[insert]#r
\Idx[options%keyvals]{label}[insert]#r
\idx{label}#r
\Idx{label}#r
\idx{label}[insert]#r
\Idx{label}[insert]#r
\idxc[options%keyvals]{label}#r
\idxc[options%keyvals]{label}[insert]#r
\idxc{label}#r
\idxc{label}[insert]#r
\idxf[options%keyvals]{label}
\idxf{label}
\idxn[options%keyvals]{label}
\idxn{label}
\idxpl[options%keyvals]{label}#r
\Idxpl[options%keyvals]{label}#r
\idxpl[options%keyvals]{label}[insert]#r
\Idxpl[options%keyvals]{label}[insert]#r
\idxpl{label}#r
\Idxpl{label}#r
\idxpl{label}[insert]#r
\Idxpl{label}[insert]#r
\ifnlctdownloadlinks#*
\inapp{application}
\inclass{class}
\initval{value}
\initvalempty
\initvalvaries
\inlineglsdef[type]{label}#r
\inlineglsdef{label}#r
\inlineidxdef{entry}
\Inlineidxdef{entry}
\inlineidxfdef{entry}
\inlineidxpdef{entry}
\inlineswitchdef{switch}
\inpackage{package}
\itemtitle{text}
\keyval
\keyvallist
\listofexamples
\longargfmt{arg}
\longswitch
\LuaLaTeX
\LuaTeX
\marg{arg}
\margm{arg}
\menu{item1,item2,...%text}
\meta{arg}
\metafilefmt{file-prefix}{meta-text}{file-suffix}
\MikTeX
\mirrorsamplefile{file}
\name{name}
\nlctcloseparen
\nlctclosesqbracket
\nlctdownloadlinksfalse
\nlctdownloadlinkstrue
\nlctopenparen
\nlctopensqbracket
\no
\note{text}
\oarg{arg}
\oargm{arg}
\opt{option}
\opt{option}[suffix]#*
\optdefsyntax{keyvals}{option}
\opteqvalref{option}{value}
\optfmt{option}
\option{option}
\optiondef*{option}
\optiondef{option}
\options{opt1,opt2}
\optionsor{opt1,opt2}
\optionsto{opt1}{opt2}
\optionvaldef*{option}{value}
\optionvaldef{option}{value}
\opttext{option}
\optval{option}{value}
\optvalm{option}{value}
\optvalref{option}{value}
\parent{parent}
\pdfLaTeX
\pdfTeX
\pkgdef*[options%keyvals]{package}#*
\pkgdef*{package}
\pkgdef[options%keyvals]{package}#*
\pkgdef{package}
\plabel[text]{label}#l
\plabel{label}#l
\printicons
\printsummary
\prono
\providedby{file}
\proyes
\qt{text}
\qtdocref{link text%text}{PDF-file}
\qtt{text}
\sectionref*{label}#r
\Sectionref*{label}#r
\sectionref{label}#r
\Sectionref{label}#r
\sectionsref*{label}#r
\Sectionsref*{label}#r
\sectionsref{label}#r
\Sectionsref{label}#r
\settabcolsep{length}
\shortargfmt{arg}
\starredcs{csname}
\sty{package}
\sty{package}[suffix]#*
\styfmt{package%plain}
\styoptfmt{package-option}
\stytext{package}
\switch{switch}
\switch{switch}[suffix]#*
\switchdef{switch}
\switchtext{switch}
\sym{symname}
\syntax{arg}
\tablefnmark{mark}
\tablefns{text}
\tablefntext{mark}{text}
\tableref*{label}#r
\Tableref*{label}#r
\tableref{label}#r
\Tableref{label}#r
\tablesref*{labellist}#r
\Tablesref*{labellist}#r
\tablesref{labellist}#r
\Tablesref{labellist}#r
\texdocref{URL-path%URL}
\texfaq{URL-path%URL}{link text%text}
\TeXLive
\texseref{URL-path%URL}{link text%text}
\tugboat{title%text}{year}{volume}{number}{pdf}
\unlimited
\urlfootref{URL}{link text%text}#U
\XeLaTeX
\XeTeX
\yes

\createexample{preamble code%text}{document code%text}
\createexample[options%keyvals]{preamble code%text}{document code%text}
\createexample*{preamble code%text}{document code%text}
\createexample*[options%keyvals]{preamble code%text}{document code%text}

#keyvals:\createexample,\createexample*
fontsize=#8,9,10,11,12,14,17,20
class=%<class%>
pagestyle=%<pagestyle%>
graphicsopts={%<graphics options%>}
pages=%<pages%>
pagesep=##L
tex={%<tex cmds%>}
arara={%<arara cmds%>}
description={%<text%>}
title={%<text%>}
label=##l
#endkeyvals

\nlctuserguidegls{commands}
\nlctuserguidegls[bib2gls options%keyvals]{commands}

#keyvals:\nlctuserguidegls
charset=%<encoding name%>
interpret-preamble#true,false
write-preamble#true,false
set-widest#true,false
entry-type-aliases={%<keyvals%>}
unknown-entry-alias=%<value%>
action=#define,copy,define or copy
src={%<list%>}
selection=#recorded and deps,recorded and deps and see,recorded and deps and see not also,recorded no deps,recorded and ancestors,deps but not recorded,ancestors but not recorded,selected before,all
match={%<keyvals%>}
match-op=#and,or
not-match={%<keyvals%>}
match-action=#filter,add
limit=%<number%>
save-child-count#true,false
save-sibling-count#true,false
save-root-ancestor#true,false
flatten#true,false
flatten-lonely=#false,presort,postsort
flatten-lonely-rule=#only unrecorded parents,discard unrecorded,no discard
strip-missing-parents#true,false
missing-parents=#strip,warn,create
missing-parent-category=#same as child,same as base,no value,false,%<label%>
group-level=#{%<n%>},{>%<n%>},{>=%<n%>},{<%<n%>},{<=%<n%>},all
merge-small-groups
merge-small-groups=%<n%>
master=%<name%>
master-resources={%<list%>}
interpret-label-fields#true,false
labelify={%<list%>}
labelify-replace={%<list%>}
label-prefix=%<prefix%>
duplicate-label-suffix=%<suffix%>
record-label-prefix=%<tag%>
cs-label-prefix=%<tag%>
ext-prefixes={%<list%>}
prefix-only-existing#true,false
save-original-id=#false,true,%<field%>
save-original-id-action=#always,no override,changed override,changes,diff
save-definition-index#true,false
save-use-index#true,false
dependency-fields={%<list%>}
group=%<label%>
category=#false,same as entry,same as original entry,same as base,same as type,%<label%>
type=#false,same as entry,same as original entry,same as base,same as category,same as parent,%<label%>
trigger-type=%<type%>
progenitor-type=%<type%>
progeny-type=%<type%>
adopted-parent-field=%<field%>
abbreviation-name-fallback=%<field%>
ignore-fields={%<list%>}
field-aliases={%<keyvals%>}
replicate-fields={%<keyvals%>}
replicate-override#true,false
replicate-missing-field-action=#skip,fallback,empty
counter=%<value%>
copy-action-group-field=%<value%>
copy-alias-to-see#true,false
save-from-see=%<value%>
save-from-seealso=%<value%>
save-from-alias=%<value%>
save-crossref-tail=%<value%>
save-original-entrytype=%<value%>
save-original-entrytype-action=#always,no override,changed override,changed,diff,changed no override
post-description-dot=#none,all,check
strip-trailing-nopost=#true,false
check-end-punctuation={%<list%>}
sort-label-list={%<list%>}
prune-xr#true,false
prune-see-match={%<keyvals%>}
prune-see-op=#and,or
prune-seealso-match={%<keyvals%>}
prune-seealso-op=#and,or
prune-iterations=%<number%>
bibtex-contributor-fields={%<list%>}
contributor-order=#surname,von,forenames
encapsulate-fields={%<keyvals%>}
encapsulate-fields*={%<keyvals%>}
format-integer-fields={%<keyvals%>}
format-decimal-fields={%<keyvals%>}
interpret-fields={%<list%>}
interpret-fields-action=#replace,replace non empty
hex-unicode-fields={%<list%>}
date-time-fields={%<list%>}
date-fields={%<list%>}
time-fields={%<list%>}
date-time-field-format=%<value%>
date-field-format=%<value%>
time-field-format=%<value%>
date-time-field-locale=%<value%>
date-field-locale=%<value%>
time-field-locale=%<value%>
prefix-fields={%<list%>}
append-prefix-field=#none,space,space or nbsp
append-prefix-field-cs=%<cs%>
append-prefix-field-exceptions=%<sequence%>
append-prefix-field-cs-exceptions=%<sequence%>
append-prefix-field-nbsp-match=%<pattern%>
no-case-change-cs={%<list%>}
word-boundaries={%<list%>}
short-case-change=#white space,cs space,dash,nbsp
long-case-change=#white space,cs space,dash,nbsp
name-case-change=#white space,cs space,dash,nbsp
description-case-change=#white space,cs space,dash,nbsp
field-case-change={%<keyvals%>}
short-plural-suffix=%<suffix%>
dual-short-plural-suffix=%<suffix%>
save-locations=#false,true,see,see not also,alias only
save-loclist#true,false
save-primary-locations=#false,retain,default format,start,remove
save-principal-locations=#false,retain,default format,start,remove
primary-location-formats={%<list%>}
principal-location-formats={%<list%>}
primary-loc-counters=#combine,match,split
principal-loc-counters=#combine,match,split
min-loc-range=%<value%>
max-loc-diff=%<integer%>
suffixF=%<value%>
suffixFF=%<value%>
compact-ranges=%<value%>
see=#omit,before,after
seealso=#omit,before,after
alias=#omit,before,after
alias-loc=#keep,transfer,omit
loc-prefix=%<value%>
loc-prefix-def=#global,local,individual
loc-suffix=%<value%>
loc-suffix-def=#global,local,individual
loc-counters={%<list%>}
save-index-counter=%<value%>
supplemental-locations=%<basename%>
supplemental-selection=%<value%>
supplemental-category=%<value%>
sort=%<value%>
shuffle=%<seed%>
sort-field=%<field%>
missing-sort-fallback=%<field%>
custom-sort-fallbacks={%<keyvals%>}
entry-sort-fallback=%<field%>
abbreviation-sort-fallback=%<field%>
symbol-sort-fallback=%<field%>
bibtexentry-sort-fallback=%<field%>
field-concat-sep=%<separator%>
trim-sort#true,false
sort-replace={%<list%>}
sort-rule=%<value%>
break-at=#word,character,sentence,upper-notlower,upper-upper,upper-notlower-word,upper-upper-word,none
break-marker=%<marker%>
break-at-match={%<keyvals%>}
break-at-match-op=#and,or
break-at-not-match={%<keyvals%>}
sort-number-pad=%<number%>
sort-pad-plus=%<marker%>
sort-pad-minus=%<marker%>
identical-sort-action=#none,def,use,id,original id,%<field%>
sort-suffix=#none,non-unique,%<field%>
sort-suffix-marker=%<marker%>
encapsulate-sort=%<csname%>
strength=#primary,secondary,tertiary,identical
decomposition=#canonical,full,none
letter-number-rule=#before letter,after letter,between,first,last
letter-number-punc-rule=#punc-space-first,punc-space-last,space-punc-first,space-punc-last,space-first-punc-last,punc-first-space-last,punc-first-space-zero,punc-last-space-zero,punc-first-space-zero-match-next,punc-last-space-zero-match-next
numeric-sort-pattern=%<value%>
numeric-locale=#locale,doc,%<lang-tag%>
date-sort-locale=#locale,doc,%<lang-tag%>
date-sort-format=#default,short,medium,long,full,%<pattern%>
group-formation=#default,codepoint,unicode category,unicode script,unicode category and script
secondary=%<value%>
secondary-match={%<keyvals%>}
secondary-not-match={%<keyvals%>}
secondary-match-op=#and,or
secondary-match-action=#filter,add
secondary-missing-sort-fallback=%<field%>
secondary-trim-sort#true,false
secondary-sort-replace={%<list%>}
secondary-sort-rule=%<value%>
secondary-break-at=#word,character,sentence,upper-notlower,upper-upper,upper-notlower-word,upper-upper-word,none
secondary-break-marker=%<marker%>
secondary-break-at-match={%<keyvals%>}
secondary-break-at-match-op=#and,or
secondary-break-at-not-match={%<keyvals%>}
secondary-sort-number-pad=%<number%>
secondary-sort-pad-plus=%<marker%>
secondary-sort-pad-minus=%<marker%>
secondary-identical-sort-action=#none,def,use,id,original id,%<field%>
secondary-sort-suffix=#none,non-unique,%<field%>
secondary-sort-suffix-marker=%<marker%>
secondary-strength=#primary,secondary,tertiary,identical
secondary-decomposition=#canonical,full,none
secondary-letter-number-rule=#before letter,after letter,between,first,last
secondary-letter-number-punc-rule=#punc-space-first,punc-space-last,space-punc-first,space-punc-last,space-first-punc-last,punc-first-space-last,punc-first-space-zero,punc-last-space-zero,punc-first-space-zero-match-next,punc-last-space-zero-match-next
secondary-numeric-sort-pattern=%<value%>
secondary-numeric-locale=#locale,doc,%<lang-tag%>
secondary-date-sort-locale=#locale,doc,%<lang-tag%>
secondary-date-sort-format=#default,short,medium,long,full,%<pattern%>
secondary-group-formation=#default,codepoint,unicode category,unicode script,unicode category and script
dual-prefix=%<prefix%>
primary-dual-dependency#true,false
combine-dual-locations=#false,both,dual,primary,dual retain principal,primary retain principal
dual-type=#false,same as entry,same as original entry,same as base,same as primary,same as parent,same as category,%<label%>
dual-category=#false,same as entry,same as original entry,same as base,same as primary,same as type,%<label%>
dual-counter=%<value%>
dual-short-case-change=#white space,cs space,dash,nbsp
dual-long-case-change=#white space,cs space,dash,nbsp
dual-field=%<value%>
dual-date-time-field-format=%<value%>
dual-date-field-format=%<value%>
dual-time-field-format=%<value%>
dual-date-time-field-locale=%<value%>
dual-date-field-locale=%<value%>
date-time-field-locale=%<value%>
dual-sort=%<value%>
dual-sort-field=%<value%>
dual-missing-sort-fallback=%<field%>
dual-trim-sort#true,false
dual-sort-replace={%<list%>}
dual-sort-rule=%<value%>
dual-break-at=#word,character,sentence,upper-notlower,upper-upper,upper-notlower-word,upper-upper-word,none
dual-break-marker=%<marker%>
dual-break-at-match={%<keyvals%>}
dual-break-at-match-op=#and,or
dual-break-at-not-match={%<keyvals%>}
dual-sort-number-pad=%<number%>
dual-sort-pad-plus=%<marker%>
dual-sort-pad-minus=%<marker%>
dual-identical-sort-action=#none,def,use,id,original id,%<field%>
dual-sort-suffix=#none,non-unique,%<field%>
dual-sort-suffix-marker=%<marker%>
dual-strength=#primary,secondary,tertiary,identical
dual-decomposition=#canonical,full,none
dual-letter-number-rule=#before letter,after letter,between,first,last
dual-letter-number-punc-rule=#punc-space-first,punc-space-last,space-punc-first,space-punc-last,space-first-punc-last,punc-first-space-last,punc-first-space-zero,punc-last-space-zero,punc-first-space-zero-match-next,punc-last-space-zero-match-next
dual-numeric-sort-pattern=%<value%>
dual-numeric-locale=#locale,doc,%<lang-tag%>
dual-date-sort-locale=#locale,doc,%<lang-tag%>
dual-date-sort-format=#default,short,medium,long,full,%<pattern%>
dual-group-formation=#default,codepoint,unicode category,unicode script,unicode category and script
dual-entry-map={{%<list1%>},{%<list2%>}}
dual-abbrv-map={{%<list1%>},{%<list2%>}}
dual-abbrventry-map={{%<list1%>},{%<list2%>}}
dual-symbol-map={{%<list1%>},{%<list2%>}}
dual-indexentry-map={{%<list1%>},{%<list2%>}}
dual-indexsymbol-map={{%<list1%>},{%<list2%>}}
dual-indexabbrv-map={{%<list1%>},{%<list2%>}}
dual-entry-backlink#true,false
dual-abbrv-backlink#true,false
dual-symbol-backlink#true,false
dual-abbrventry-backlink#true,false
dual-entryabbrv-backlink#true,false
dual-indexentry-backlink#true,false
dual-indexsymbol-backlink#true,false
dual-indexabbrv-backlink#true,false
dual-backlink#true,false
tertiary-prefix=%<prefix%>
tertiary-type=%<value%>
tertiary-category=%<value%>
compound-options-global#true,false
compound-dependent#true,false
compound-add-hierarchy#true,false
compound-has-records#true,false
compound-adjust-name=#false,unique,once
compound-main-type=#same as entry,same as original entry,same as base,same as category,same as parent,%<label%>
compound-other-type=#same as main,same as entry,same as original entry,same as base,same as category,same as parent,%<label%>
compound-type-override#true,false
compound-write-def=#none,all,ref
#endkeyvals

\printabbrs
\printabbrs[options%keyvals]
\printcommonoptions{label}
\printcommonoptions[options%keyvals]{label}
\printterms
\printterms[options%keyvals]
\printuserguideindex
\printuserguideindex[options%keyvals]

#keyvals:\printabbrs,\printcommonoptions,\printterms,\printuserguideindex
title=
toctitle=
style=
numberedsection=#false,nolabel,autolabel
nonumberlist#true,false
nogroupskip#true,false
nopostdot#true,false
entrycounter#true,false
subentrycounter#true,false
sort=#word,letter,standard,use,def,nocase,case
# options added by glossaries-extra
target#true,false
targetnameprefix=%<prefix%>
prefix=%<prefix%>
label=##l
groups#true,false
leveloffset=%<<n> or ++<n>%>
#endkeyvals

\begin{itemdesc}
\end{itemdesc}
\begin{deflist}
\end{deflist}
\begin{warning}
\begin{warning}[options%keyvals]
\end{warning}
\begin{important}
\begin{important}[options%keyvals]
\end{important}
\begin{information}
\begin{information}[options%keyvals]
\end{information}
\begin{pinnedbox}
\begin{pinnedbox}[options%keyvals]
\end{pinnedbox}
\begin{defnbox}
\begin{defnbox}[options%keyvals]
\end{defnbox}
\begin{settingsbox}
\begin{settingsbox}[options%keyvals]
\end{settingsbox}
\begin{terminal}
\end{terminal}
\begin{transcript}
\end{transcript}
\begin{codebox}
\begin{codebox}[options%keyvals]
\end{codebox}
\begin{codebox*}
\begin{codebox*}[options%keyvals]
\end{codebox*}
\begin{badcodebox}
\end{badcodebox}
\begin{unicodebox}
\end{unicodebox}
\begin{compactcodebox}
\begin{compactcodebox}[options%keyvals]
\end{compactcodebox}
\begin{compactcodebox*}
\begin{compactcodebox*}[options%keyvals]
\end{compactcodebox*}
\begin{resultbox}
\begin{resultbox}[options%keyvals]
\end{resultbox}
\begin{coderesult}
\begin{coderesult}[options%keyvals]
\end{coderesult}
\begin{coderesult*}
\begin{coderesult*}[options%keyvals]
\end{coderesult*}
\begin{unicoderesult}
\end{unicoderesult}
\begin{unicoderesult*}
\end{unicoderesult*}
\begin{example}{title%text}{label}#l
\end{example}

#keyvals:\begin{warning},\begin{important},\begin{information},\begin{pinnedbox},\begin{defnbox},\begin{settingsbox},\begin{codebox},\begin{codebox*},\begin{compactcodebox},\begin{compactcodebox*},\begin{resultbox},\begin{coderesult},\begin{coderesult*}
### << always available keys >> ###
title=%<text%>
notitle
adjusted title=%<text%>
adjust text=%<text%>
squeezed title=%<text%>
squeezed title*=%<text%>
titlebox=#visible,invisible
detach title
attach title
attach title to upper=%<text%>
subtitle style={%<options%>}
upperbox=#visible,invisible
visible
invisible
saveto=%<file name%>
lowerbox=#visible,invisible,ignore
savelowerto=%<file name%>
lower separated#true,false
savedelimiter=%<name%>
colframe=#%color
colback=#%color
title filled#true,false
colbacktitle=#%color
colupper=#%color
collower=#%color
coltext=#%color
coltitle=#%color
fontupper=%<text%>
fontlower=%<text%>
fonttitle=%<text%>
halign=#justify,left,flush left,right,flush right,center,flush center
halign upper=#justify,left,flush left,right,flush right,center,flush center
halign lower=#justify,left,flush left,right,flush right,center,flush center
halign title=#justify,left,flush left,right,flush right,center,flush center
flushleft upper
center upper
flushright upper
flushleft lower
center lower
flushright lower
flushleft title
center title
flushright title
valign=#top,center,bottom,scale,scale*
valign upper=#top,center,bottom,scale,scale*
valign lower=#top,center,bottom,scale,scale*
valign scale limit=%<number%>
width=##L
text width=##L
add to width=##L
toprule=##L
bottomrule=##L
leftrule=##L
rightrule=##L
titlerule=##L
boxrule=##L
arc=##L
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=##L
auto outer arc
boxsep=##L
left=##L
left*=##L
lefttitle=##L
leftupper=##L
leftlower=##L
right=##L
right*=##L
righttitle=##L
rightupper=##L
rightlower=##L
top=##L
toptitle=##L
bottom=##L
bottomtitle=##L
middle=##L
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=##L
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=%<fraction%>
opacityback=%<fraction%>
opacitybacktitle=%<fraction%>
opacityfill=%<fraction%>
opacityupper=%<fraction%>
opacitylower=%<fraction%>
opacitytext=%<fraction%>
opacitytitle=%<fraction%>
natural height
height=##L
height plus=##L
height from=%<min%> to %<max%>
text height=##L
add to height=##L
add to natural height=##L
height fill
height fill=#true,false,maximum
inherit height
inherit height=%<fraction%>
square
space=%<fraction%>
space to upper
space to lower
space to both
space to=%<macro%>
split=%<fraction%>
equal height group=%<id%>
minimum for equal height group=%<id:length%>
minimum for current equal height group=##L
use height from group
use height from group=%<id%>
before title={%<code%>}
after title={%<code%>}
before upper={%<code%>}
before upper*={%<code%>}
after upper={%<code%>}
after upper*={%<code%>}
before lower={%<code%>}
before lower*={%<code%>}
after lower={%<code%>}
after lower*={%<code%>}
text fill=
tabulars={%<preamble%>}
tabulars*={%<code%>}{%<preamble%>}
tabularx={%<preamble%>}
tabularx*={%<code%>}{%<preamble%>}
tikz upper
tikz upper={%<TikZ options%>}
tikz lower
tikz lower={%<TikZ options%>}
tikznode upper
tikznode upper={%<TikZ options%>}
tikznode lower
tikznode lower={%<TikZ options%>}
tikznode
tikznode={%<TikZ options%>}
varwidth upper
varwidth upper=##L
overlay={%<code%>}
no overlay
overlay broken={%<code%>}
overlay unbroken={%<code%>}
overlay first={%<code%>}
overlay middle={%<code%>}
overlay last={%<code%>}
overlay unbroken and first={%<code%>}
overlay middle and last={%<code%>}
overlay unbroken and last={%<code%>}
overlay first and middle={%<code%>}
floatplacement=%<values%>
float
float=%<values%>
float*
float*=%<values%>
nofloat
every float={%<code%>}
before float={%<code%>}
after float={%<code%>}
before={%<code%>}
after={%<code%>}
nobeforeafter
force nobeforeafter
before skip balanced=%<glue%>
after skip balanced=%<glue%>
beforeafter skip balanced=%<glue%>
before skip=##L
after skip=##L
beforeafter skip=##L
left skip=##L
right skip=##L
leftright skip=##L
parskip
noparskip
autoparskip
baseline=##L
box align=#bottom,top,center,base
ignore nobreak#true,false
before nobreak={%<code%>}
parfillskip restore#true,false
enlarge top initially by=##L
enlarge bottom finally by=##L
enlarge top at break by=##L
enlarge bottom at break by=##L
enlarge top by=##L
enlarge bottom by=##L
enlarge left by=##L
enlarge right by=##L
enlarge by=##L
grow to left by=##L
grow to right by=##L
grow sidewards by=##L
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=##L
spread outwards
spread outwards=##L
move upwards
move upwards=##L
move upwards*
move upwards*=##L
fill downwards
fill downwards=##L
spread upwards
spread upwards=##L
spread upwards*
spread upwards*=##L
spread sidewards
spread sidewards=##L
spread
spread=##L
spread downwards
spread downwards=##L
shrink tight
extrude left by=##L
extrude right by=##L
extrude top by=##L
extrude bottom by=##L
extrude by=##L
every box/.style={%<options%>}
every box on layer 1/.style={%<options%>}
every box on layer 2/.style={%<options%>}
every box on layer 3/.style={%<options%>}
every box on layer 4/.style={%<options%>}
capture=#minipage,hbox,fitbox
hbox
minipage
parbox#true,false
hyphenationfix#true,false
tempfile=%<file name%>
phantom={%<code%>}
nophantom
label=##l
phantomlabel=##l
label type=%<type%>
no label type
step=%<counter%>
step and label={%<counter%>}{%<marker%>}
list entry=%<text%>
list text=%<text%>
add to list={%<list%>}{%<type%>}
nameref=%<text%>
hypertarget=%<marker%>
bookmark=%<text%>
bookmark*={%<options%>}{%<text%>}
index=%<entry%>
index*={%<name%>}{%<entry%>}
check odd page#true,false
if odd page={%<odd options%>}{%<even options%>}
if odd page or oneside={%<odd options%>}{%<even options%>}
if odd page*={%<odd options%>}{%<even options%>}
if odd page or oneside*={%<odd options%>}{%<even options%>}
shield externalize#true,false
external=%<file name%>
remake
remake#true,false
reset
code={%<code%>}
IfBlankTF={%<token list%>}{%<true%>}{%<false%>}
IfBlankT={%<token list%>}{%<true%>}
IfBlankF={%<token list%>}{%<false%>}
IfEmptyTF={%<token list%>}{%<true%>}{%<false%>}
IfEmptyT={%<token list%>}{%<true%>}
IfEmptyF={%<token list%>}{%<false%>}
IfNoValueTF={%<arg%>}{%<true%>}{%<false%>}
IfNoValueT={%<arg%>}{%<true%>}
IfNoValueF={%<arg%>}{%<false%>}
IfValueTF={%<arg%>}{%<true%>}{%<false%>}
IfValueT={%<arg%>}{%<true%>}
IfValueF={%<arg%>}{%<false%>}
IfBooleanTF={%<arg%>}{%<true%>}{%<false%>}
IfBooleanT={%<arg%>}{%<true%>}
IfBooleanF={%<arg%>}{%<false%>}
void
nirvana
blend before title=#colon,dash,colon hang,dash hang
blend before title code={%<code%>}
sidebyside#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=##L
lefthand width=##L
righthand width=##L
lefthand ratio=%<fraction%>
righthand ratio=%<fraction%>
sidebyside adapt=#none,left,right,both
sidebyside switch#true,false
verbatim ignore percent#true,false
record=%<content%>
no recording
skin=%<name%>
skin first=%<name%>
skin middle=%<name%>
skin last=%<name%>
graphical environment=%<envname%>
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes#true,false
frame code={%<code%>}
frame empty
interior titled code={%<code%>}
interior titled empty
interior code={%<code%>}
interior empty
segmentation code={%<code%>}
segmentation empty
title code={%<code%>}
title empty
skin first is subskin of={%<base skin%>}{%<options%>}
skin middle is subskin of={%<base skin%>}{%<options%>}
skin last is subskin of={%<base skin%>}{%<options%>}

### << skins library keys >> ###
frame style={%<TikZ options%>}
frame style image=%<file name%>
frame style tile={%<graphics options%>}{%<file%>}
frame hidden
interior style={%<TikZ options%>}
interior style image=%<file name%>
interior style tile={%<graphics options%>}{%<file%>}
interior hidden
segmentation style={%<TikZ options%>}
segmentation hidden
title style={%<TikZ options%>}
title style image=%<file name%>
title style tile={%<graphics options%>}{%<file%>}
title hidden
titlerule style={%<TikZ options%>}
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left={%<boxtitle options%>}
attach boxed title to top text left
attach boxed title to top text left={%<boxtitle options%>}
attach boxed title to top center
attach boxed title to top center={%<boxtitle options%>}
attach boxed title to top right
attach boxed title to top right={%<boxtitle options%>}
attach boxed title to top text right
attach boxed title to top text right={%<boxtitle options%>}
attach boxed title to bottom left
attach boxed title to bottom left={%<boxtitle options%>}
attach boxed title to bottom text left
attach boxed title to bottom text left={%<boxtitle options%>}
attach boxed title to bottom center
attach boxed title to bottom center={%<boxtitle options%>}
attach boxed title to bottom right
attach boxed title to bottom right={%<boxtitle options%>}
attach boxed title to bottom text right
attach boxed title to bottom text right={%<boxtitle options%>}
attach boxed title to top
attach boxed title to top={%<boxtitle options%>}
attach boxed title to top*
attach boxed title to top*={%<boxtitle options%>}
attach boxed title to bottom
attach boxed title to bottom={%<boxtitle options%>}
attach boxed title to bottom*
attach boxed title to bottom*={%<boxtitle options%>}
flip title
flip title={%<boxtitle options%>}
boxed title size=#title,standard,copy
boxed title style={%<options%>}
no boxed title style
hbox boxed title
minipage boxed title
minipage boxed title=##L
minipage boxed title*
minipage boxed title*=##L
tikznode boxed title={%<TikZ options%>}
varwidth boxed title
varwidth boxed title=##L
varwidth boxed title*
varwidth boxed title*=##L
watermark text=%<text%>
watermark text on=%<part%> is %<text%>
watermark graphics=%<file name%>
watermark graphics on=%<part%> is %<file%>
watermark tikz={%<code%>}
watermark tikz on=%<part%> is %<code%>
no watermark
watermark opacity=%<fraction%>
watermark zoom=%<fraction%>
watermark shrink=%<fraction%>
watermark overzoom=%<fraction%>
watermark stretch=%<fraction%>
watermark color=#%color
clip watermark#true,false
clip title#true,false
clip upper#true,false
clip lower#true,false
borderline={%<width%>}{%<offset%>}{%<TikZ options%>}
no borderline
show bounding box
show bounding box=#%color
borderline north={%<width%>}{%<offset%>}{%<TikZ options%>}
borderline south={%<width%>}{%<offset%>}{%<TikZ options%>}
borderline east={%<width%>}{%<offset%>}{%<TikZ options%>}
borderline west={%<width%>}{%<offset%>}{%<TikZ options%>}
borderline horizontal={%<width%>}{%<offset%>}{%<TikZ options%>}
borderline vertical={%<width%>}{%<offset%>}{%<TikZ options%>}
no shadow
drop shadow
drop shadow=#%color
drop fuzzy shadow
drop fuzzy shadow=#%color
drop midday shadow
drop midday shadow=#%color
drop fuzzy midday shadow
drop fuzzy midday shadow=#%color
halo
halo=%<size%> with %<color%>
fuzzy halo
fuzzy halo=%<size%> with %<color%>
drop shadow southeast
drop shadow southeast=#%color
drop shadow south
drop shadow south=#%color
drop shadow southwest
drop shadow southwest=#%color
drop shadow west
drop shadow west=#%color
drop shadow northwest
drop shadow northwest=#%color
drop shadow north
drop shadow north=#%color
drop shadow northeast
drop shadow northeast=#%color
drop shadow east
drop shadow east=#%color
drop fuzzy shadow southeast
drop fuzzy shadow southeast=#%color
drop fuzzy shadow south
drop fuzzy shadow south=#%color
drop fuzzy shadow southwest
drop fuzzy shadow southwest=#%color
drop fuzzy shadow west
drop fuzzy shadow west=#%color
drop fuzzy shadow northwest
drop fuzzy shadow northwest=#%color
drop fuzzy shadow north
drop fuzzy shadow north=#%color
drop fuzzy shadow northeast
drop fuzzy shadow northeast=#%color
drop fuzzy shadow east
drop fuzzy shadow east=#%color
drop lifted shadow
drop lifted shadow=#%color
drop small lifted shadow
drop small lifted shadow=#%color
drop large lifted shadow
drop large lifted shadow=#%color
shadow={%<xshift%>}{%<yshift%>}{%<offset%>}{%<TikZ options%>}
fuzzy shadow={%<xshift%>}{%<yshift%>}{%<offset%>}{%<step%>}{%<TikZ options%>}
smart shadow arc#true,false
lifted shadow={%<xshift%>}{%<yshift%>}{%<bend%>}{%<step%>}{%<TikZ options%>}
tikz={%<TikZ options%>}
tikz reset
at begin tikz={%<TikZ code%>}
at begin tikz reset
at end tikz={%<TikZ code%>}
at end tikz reset
rotate=%<angle%>
scale=%<fraction%>
remember
remember as=%<name%>
underlay={%<code%>}
no underlay
underlay broken={%<code%>}
underlay unbroken={%<code%>}
no underlay unbroken
underlay first={%<code%>}
no underlay first
underlay middle={%<code%>}
no underlay middle
underlay last={%<code%>}
no underlay last
underlay boxed title={%<code%>}
no underlay boxed title
underlay unbroken and first={%<code%>}
underlay middle and last={%<code%>}
underlay unbroken and last={%<code%>}
underlay first and middle={%<code%>}
finish={%<code%>}
no finish
finish broken={%<code%>}
finish unbroken={%<code%>}
no finish unbroken
finish first={%<code%>}
no finish first
finish middle={%<code%>}
no finish middle
finish last={%<code%>}
no finish last
finish unbroken and first={%<code%>}
finish middle and last={%<code%>}
finish unbroken and last={%<code%>}
finish first and middle={%<code%>}
hyperref=%<marker%>
hyperref interior=%<marker%>
hyperref title=%<marker%>
hyperref node={%<marker%>}{%<node%>}
hyperlink=%<marker%>
hyperlink interior=%<marker%>
hyperlink title=%<marker%>
hyperlink node={%<marker%>}{%<node%>}
hyperurl=%<URL%>
hyperurl interior=%<URL%>
hyperurl title=%<URL%>
hyperurl node={%<URL%>}{%<node%>}
hyperurl*={%<hyperref options%>}{%<URL%>}
hyperurl* interior={%<hyperref options%>}{%<URL%>}
hyperurl* title={%<hyperref options%>}{%<URL%>}
hyperurl* node={%<hyperref options%>}{%<URL%>}{%<node%>}
draftmode#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower=#%color
opacitybacklower=%<fraction%>
overlaplower=##L
bicolor jigsaw
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance={%<options%>}
extend freelancefirst={%<options%>}
extend freelancemiddle={%<options%>}
extend freelancelast={%<options%>}
only=<%<overlay spec%>>{%<options%>}
hide=<%<overlay spec%>>
beamer hidden/.style={%<options%>}
alert=<%<overlay spec%>>
beamer alerted/.style={%<options%>}

### << breakable library keys >> ###
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=%<text%>
notitle after break
adjusted title after break=%<text%>
lines before break=%<number%>
break at=%<length1/length2/...%>
enlargepage=%<length1/length2/...%>
enlargepage flexible=##L
compress page
compress page=#all,baselineskip,none
shrink break goal=##L
use color stack#true,false
toprule at break=##L
bottomrule at break=##L
topsep at break=##L
bottomsep at break=##L
pad before break=##L
pad before break*=##L
pad after break=##L
pad at break=##L
pad at break*=##L
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first#true,false
segmentation at break#true,false
extras={%<options%>}
no extras
extras broken={%<options%>}
extras unbroken={%<options%>}
no extras unbroken
extras first={%<options%>}
no extras first
extras middle={%<options%>}
no extras middle
extras last={%<options%>}
no extras last
extras unbroken and first={%<options%>}
extras middle and last={%<options%>}
extras unbroken and last={%<options%>}
extras first and middle={%<options%>}
extras title after break={%<options%>}
no extras title after break
#endkeyvals

banned#B
defbackground#B
optiondefbackground#B
optionvaluedefbackground#B
codebackground#B
summaryloc#B
cs#B
styopt#B
csopt#B
comment#B
style1#B
style2#B
style3#B
style4#B
style5#B
style6#B

\abbrpostnamehook#*
\acrpostnamehook#*
\addtoexamplepreamble{arg1}#*
\addtolistofexamples{arg1}#*
\advantagefmt{text}#*
\altdocref{text}{PDF-file}{html}#*
\appnotefmt{arg1}#*
\asteriskmarker#*
\badcodedesc#*
\badcodesym#*
\badcodetext#*
\banned#*
\banneddesc#*
\bannedsym#*
\bannedtext#*
\bibglslocationgroup{arg1}{arg2}{arg3}#*
\bibglslocationgroupsep#*
\bibglsothergroup#*
\bibglsothergroup{arg1}{arg2}{arg3}#*
\bibglsothergrouptitle{arg1}{arg2}{arg3}#*
\boxtitleshift#*
\childoptval{arg1}{arg2}{arg3}#*
\childsummarypar#*
\clsdef[opt]{arg}#*
\clsdef{arg}#*
\clsdefbookmarklevel#*
\clsdefcounter#*
\clsentryname{arg1}#*
\clstitle#*
\cmddefbookmarklevel#*
\cmddefbookmarkleveloffset#*
\cmddefcounter#*
\cmddefmodifierhandler{arg1}#*
\cmdfont#*
\cmdnotefmt{arg1}#*
\cmdtitle#*
\codedesc#*
\codefont#*
\codesym#*
\codetext#*
\counterdesc#*
\countersym#*
\countertext#*
\createexamplefirstline#*
\createtarget{arg1}{arg2}#*
\csfmtcolourfont{arg1}#*
\csfmtfont{arg1}#*
\ctrdefbookmarklevel#*
\currentcounter#*
\currentcounterlevel#*
\currentsyntax#*
\daggermarker#*
\defaultoptdefbookmarklevel#*
\definitiondesc#*
\definitionsym#*
\definitiontext#*
\deprecatedbanned#*
\deprecateddesc#*
\deprecatedorbannedfmt{text}#*
\deprecatedsym#*
\deprecatedtext#*
\disadvantagefmt{text}#*
\doubledaggermarker#*
\entrycountprehook{arg1}#*
\entrydefsection#*
\entrynamebox#S
\entrysec[opt]{arg1}#*
\entrysec{arg1}#*
\entryskip#*
\enventryname{arg1}#*
\envtitle#*
\exampleattachpdficon#*
\exampleattachtexicon#*
\exampledownloadpdficon#*
\exampledownloadtexicon#*
\Examplename#*
\examplename#*
\Examplerefprefix#*
\examplerefprefix#*
\examplesdir#*
\Examplesrefprefix#*
\examplesrefprefix#*
\extfmt#*
\Figurerefprefix#*
\figurerefprefix#*
\Figuresrefprefix#*
\figuresrefprefix#*
\filedownloadlink{arg1}#*
\filedownloadsubpath#*
\filetag{arg1}#*
\filteremptylocation{arg1}#*
\florettemarker#*
\fmtorcode#*
\fmtorcode{arg1}{arg2}#*
\fnsymmark{arg1}#*
\fnsymmarker{arg1}#*
\gathermodifiers{arg1}#*
\genericsummaryentryoption{arg1}{arg2}#*
\getinitordefval{arg1}#*
\glsaddterm{arg1}#*
\glsbibwritefield{arg1}{arg2}#*
\glsxtrchapterlocfmt#*
\glsxtrfigurelocfmt#*
\glsxtrparagraphlocfmt#*
\glsxtrsectionlocfmt#*
\glsxtrsubparagraphlocfmt#*
\glsxtrsubsectionlocfmt#*
\glsxtrsubsubsectionlocfmt#*
\glsxtrtablelocfmt#*
\goptmetaval#*
\hashmarker#*
\ifnlctattachpdf#*
\ifnotdefaultstatus{arg1}{arg2}{arg3}#*
\ifshowsummarysubgroupheaders#*
\ifshowsummarytopgroupheaders#*
\importantdesc#*
\importantsym#*
\importanttext#*
\informationdesc#*
\informationsym#*
\informationtext#*
\initcodeenv#*
\initordefval#*
\initvalnotefmt{text}#*
\inlineoptionvaldef{arg1}{arg2}#*
\keyeqvalue{arg1}{arg2}#*
\keyeqvaluem{arg1}{arg2}#*
\linkedentryname{arg1}#*
\listofexampleslabel#*
\listofexamplesname#*
\locationgroupencapchapter{arg1}#*
\locationgroupencapparagraph#*
\locationgroupencapsection#*
\locationgroupencapsubparagraph#*
\locationgroupencapsubsection#*
\locationgroupencapsubsubsection#*
\locationgroupmarkerchapter#*
\locationgroupmarkerfigure#*
\locationgroupmarkerpage#*
\locationgroupmarkerpages#*
\locationgroupmarkerparagraph#*
\locationgroupmarkersection#*
\locationgroupmarkersubparagraph#*
\locationgroupmarkersubsection#*
\locationgroupmarkersubsubsection#*
\locationgroupmarkertable#*
\lozengemarker#*
\maindef[opt]{arg}#*
\maindef{arg}#*
\mainfmt{arg1}#*
\mainglsadd{arg1}{arg2}{arg3}#*
\mainglsaddcounter#*
\mainmatteronly#*
\menufmt{arg1}#*
\menusep#*
\metaboolean#*
\metametafilefmt{arg1}{arg2}{arg3}{arg4}{arg5}#*
\nlctattachpdffalse#*
\nlctattachpdftrue#*
\nlctdefaultafter#*
\nlctdocatnum{arg1}#*
\nlctdocsymbolgrouplabel{arg1}{arg2}{arg3}#*
\nlctdocsymbolgrouptitle{arg1}{arg2}{arg3}#*
\nlctdownloadlink{arg1}#*
\nlctexampledisablecmds#*
\nlctexampleenvtitlefont#*
\nlctexamplefilebasename#*
\nlctexampleimagelist#*
\nlctexamplelets#*
\nlctexampletag#*
\nlctexampletagattachfont#*
\nlctexampletitlebox[opt]{arg1}#*
\nlctexampletitlebox{arg1}#*
\nlctexampletitlefmt{arg1}#*
\nlctexampletitlefont#*
\nlctguideindexinitpostnamehooks#*
\nlctmodifierglslist#*
\nlctmodifierlist#*
\nlctmodifiertag#*
\nlctnovref#*
\nlctuserguidebib#S
\nlctuserguidecustomentryaliases#*
\nlctuserguideextrarules#*
\nlctuserguideignoredpuncrules#*
\nlctuserguideletterrules#*
\nlctuserguideloadgls{arg1}#*
\nlctuserguidepreletterrules#*
\nlctuserguidepuncrules#*
\nlctusevref#*
\novaluesettingdesc#*
\novaluesettingsym#*
\novaluesettingtext#*
\optdefbookmarklevel#*
\optionlistitemformat{arg1}#*
\optionlistprefix#*
\optionlisttag#*
\optionlisttags#*
\optiontag#*
\optionvaluedesc#*
\optionvaluesym#*
\optionvaluetext#*
\optnotefmt{arg1}#*
\optvaldefbookmarklevel#*
\optvaldefcounter#*
\optvalrefeq{arg1}{arg2}{arg3}#*
\pdflongswitch#*
\pilcrowmarker#*
\pkgdefbookmarklevel#*
\pkgdefcounter#*
\pkgentryname{arg1}#*
\pkgnotefmt{arg1}#*
\pkgtitle#*
\postnote#S
\printcommandoptions{arg1}{arg2}#*
\printcommandoptionsprocesshook{arg1}{arg2}#*
\printcommonoptionsprocesshook{arg1}{arg2}#*
\providedbyfmt{arg1}#*
\referencemarker#*
\refslistlastsep#*
\refslistsep#*
\resultdesc#*
\resultsym#*
\resulttext#*
\rootsummarypar#*
\seclocfmt{arg1}{arg2}#*
\sectionmarker#*
\Sectionrefprefix#*
\sectionrefprefix#*
\Sectionsrefprefix#*
\sectionsrefprefix#*
\setcounterlevels{arg1}{arg2}#*
\setexamplefontsize{arg1}#*
\setexamplepreamble{arg}#*
\settermshook{arg1}#*
\settingstitle#*
\setupcodeenvfmts#*
\setwidestnamehook{arg1}#*
\showsummarysubgroupheadersfalse#*
\showsummarysubgroupheaderstrue#*
\showsummarytopgroupheadersfalse#*
\showsummarytopgroupheaderstrue#*
\sidenote{arg1}#*
\starmarker#*
\statusbannedsym#*
\statusbannedtext#*
\statusdefaultsym#*
\statusdefaulttext#*
\statusdeprecatedbannedsym#*
\statusdeprecatedbannedtext#*
\statusdeprecatedsym#*
\statusdeprecatedtext#*
\statushook{arg1}#*
\statussym#*
\statustext#*
\summaryentryclass{arg1}#*
\summaryentryclassbookmark{arg1}{arg2}#*
\summaryentryclassoption#*
\summaryentrycommand{arg1}#*
\summaryentrycommandoption#*
\summaryentryenvironment{arg1}#*
\summaryentryenvironmentoption#*
\summaryentryoption{arg1}#*
\summaryentryoptionvalue{arg1}#*
\summaryentrypackage{arg1}#*
\summaryentrypackagebookmark{arg1}{arg2}#*
\summaryentrypackageoption#*
\summaryentryskip#*
\summaryhook{arg1}#*
\summaryhookdoskip#*
\summaryloc{arg1}#*
\summarylocfmt{arg1}#*
\summarylocfont#*
\summarylocwidth#*
\summarynotefmt{arg1}#*
\summarypar#*
\summarypredesc#*
\summarysec#*
\summarysecnumdepth#*
\summarysubitemindent#*
\summarysubsec#*
\summarysubsecnumdepth#*
\summarytagfmt{text}#*
\symboldefinitions#*
\symbolentry{arg1}#*
\tablefnfmt{arg1}#*
\Tablerefprefix#*
\tablerefprefix#*
\Tablesrefprefix#*
\tablesrefprefix#*
\tagsep#*
\targetorhyperlink{arg1}{arg2}#*
\terminaldesc#*
\terminalsym#*
\terminaltext#*
\termslocfmt{arg1}#*
\texmeta{arg}#*
\theexample#*
\thispackage#*
\thispackagename#*
\tick#*
\toggleoffsettingdesc#*
\toggleoffsettingsym#*
\toggleoffsettingtext#*
\toggleonsettingdesc#*
\toggleonsettingsym#*
\toggleonsettingtext#*
\totalclsopts#S
\totalcmds#S
\totalenvs#S
\totalindexitems#S
\totalpkgopts#S
\totalterms#S
\transcriptdesc#*
\transcriptsym#*
\transcripttext#*
\unicodedesc#*
\unicodesym#*
\unicodetext#*
\valuesettingdesc#*
\valuesettingsym#*
\valuesettingtext#*
\vdoubleasteriskmarker#*
\warningdesc#*
\warningsym#*
\warningtext#*
\xrsectionref{arg1}{arg2}{arg3}#*

# from breakable option of tcolorbox
#include:pdfcol

# from skins option of tcolorbox
#include:tikz

# from listings option of tcolorbox
#include:listings
#include:pdftexcmds
#include:shellesc

# from record=nameref option of glossaries-extra
#include:glossaries-extra-bib2gls

# from symbols option of glossaries-extra
\printsymbols
\printsymbols[options%keyvals]
\glsxtrnewsymbol{label}{symbol}#l
\glsxtrnewsymbol[options%keyvals]{label}{symbol}#l
\printunsrtsymbols#*
\printunsrtsymbols[options%keyvals]#*
\glsxtrpostdescsymbol#*

# from stylemods={...} option of glossaries-extra
#include:glossaries-extra-stylemods
#include:glossary-mcols
#include:glossary-bookindex
#include:glossary-topic
#include:glossary-longextra
