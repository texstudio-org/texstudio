# glossaries-extra package
# Matthew Bertucci 11/27/2021 for v1.48

#include:glossaries

### 1 Introduction ###
## 1.2 New or Modified Package Options
\glossariesextrasetup{options%keyvals}
#keyvals:\usepackage/glossaries-extra#c,\glossariesextrasetup#c
## options passed to glossaries.sty
nowarn
nolangwarn
noredefwarn
debug=#false,true,showtargets,showaccsupp,showwrgloss,all
savewrites#true,false
translate=#true,false,babel
notranslate
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
style=
nolong
nosuper
nolist
notree
nostyles
nonumberlist
seeautonumberlist
counter=%<counter%>
nopostdot#true,false
nogroupskip#true,false
seenoindex=#error,warn,ignore
esclocations#true,false
indexonlyfirst#true,false
sanitizesort#true,false
sort=#standard,def,use,none
order=#word,letter
makeindex
xindy
xindygloss
xindynoglsnumbers
automake=#false,true,immediate
disablemakegloss
restoremakegloss
nohypertypes={%<list%>}
nomain
symbols
numbers
index
noglossaryindex
acronym#true,false
acronyms
acronymlists={%<value%>}
shortcuts=#acronyms,acro,ac,abbreviations,abbr,other,all,true,none,false
compatible-2.07#true,false
compatible-3.07#true,false
kernelglossredefs={%<value%>}
## options unique to glossaries-extra
showtargets=#left,right,innerleft,innerright,annoteleft,annoteright
postdot
postpunc=#comma,dot,none
prefix
accsupp
stylemods
stylemods=#default,all,inline,list,tree,mcols,long,longragged,longbooktabs,super,superragged,bookindex,longextra,topic
undefaction=#warn,error
indexcrossrefs#true,false
autoseeindex#true,false
record=#off,only,nameref,hybrid
equations
floats
indexcounter
docdef=#false,true,restricted,atom
nomissingglstext#true,false
abbreviations
#endkeyvals

\GlsXtrInternalLocationHyperlink{counter}{prefix}{location}#*
\glsxtrwrglossmark#*
\glsxtrabbrvtype#*

\glsshowtarget{target name}
\glsshowtargetouter{label}
\glsshowtargetfont#*
\glsshowtargetinner{label}#*
\glsxtrshowtargetsymbolright#*
\glsxtrshowtargetsymbolleft#*
\glsxtrshowtargetinner{label}#*
\glsxtrshowtargetouter{label}#*

#ifOption:record
#include:glossaries-extra-bib2gls
#endif
#ifOption:record=only
#include:glossaries-extra-bib2gls
#endif
#ifOption:record=nameref
#include:glossaries-extra-bib2gls
#endif

#ifOption:accsupp
#include:glossaries-accsupp
#endif

#ifOption:prefix
#include:glossaries-prefix
#endif

#ifOption:stylemods
#include:glossaries-extra-stylemods
#endif
#ifOption:stylemods=default
#include:glossaries-extra-stylemods
#endif
#ifOption:stylemods=all
#include:glossaries-extra-stylemods
#include:glossary-inline
#include:glossary-mcols
#include:glossary-longragged
#include:glossary-longbooktabs
#include:glossary-superragged
#include:glossary-bookindex
#include:glossary-longextra
#include:glossary-topic
#endif
#ifOption:stylemods=inline
#include:glossaries-extra-stylemods
#include:glossary-inline
#endif
#ifOption:stylemods=list
#include:glossaries-extra-stylemods
# glossary-list already loaded by glossaries.cwl
#endif
#ifOption:stylemods=tree
#include:glossaries-extra-stylemods
# glossary-tree already loaded by glossaries.cwl
#endif
#ifOption:stylemods=mcols
#include:glossaries-extra-stylemods
#include:glossary-mcols
#endif
#ifOption:stylemods=long
#include:glossaries-extra-stylemods
# glossary-long already loaded by glossaries.cwl
#endif
#ifOption:stylemods=longragged
#include:glossaries-extra-stylemods
#include:glossary-longragged
#endif
#ifOption:stylemods=longbooktabs
#include:glossaries-extra-stylemods
#include:glossary-longbooktabs
#endif
#ifOption:stylemods=super
#include:glossaries-extra-stylemods
# glossary-super already loaded by glossaries.cwl
#endif
#ifOption:stylemods=superragged
#include:glossaries-extra-stylemods
#include:glossary-superragged
#endif
#ifOption:stylemods=bookindex
#include:glossaries-extra-stylemods
#include:glossary-bookindex
#endif
#ifOption:stylemods=longextra
#include:glossaries-extra-stylemods
#include:glossary-longextra
#endif
#ifOption:stylemods=topic
#include:glossaries-extra-stylemods
#include:glossary-topic
#endif

#ifOption:abbreviations
\printabbreviations
\printabbreviations[options%keyvals]
\printunsrtabbreviations#*
\printunsrtabbreviations[options%keyvals]#*
\abbreviationsname#*
#endif

#keyvals:\printabbreviations#c,\printunsrtabbreviations#c,\printunsrtsymbols#c,\printunsrtnumbers#c,\printunsrtacronyms#c,\printunsrtindex#c,\printunsrtglossary#c,\printunsrtglossary*#c,\begin{printunsrtglossarywrap}#c
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
#endkeyvals

# from options inherited from glossaries.sty
#ifOption:debug=showaccsupp
\glsshowaccsupp{options}{tag}{replacement text}
#endif
#ifOption:translate=babel
#include:glossaries-babel
#endif
#ifOption:symbols
\printsymbols
\printsymbols[options%keyvals]
\glsxtrnewsymbol{label}{symbol}#l
\glsxtrnewsymbol[options%keyvals]{label}{symbol}#l
\printunsrtsymbols#*
\printunsrtsymbols[options%keyvals]#*
#endif
#ifOption:numbers
\printnumbers
\printnumbers[options%keyvals]
\glsxtrnewnumber{label}{number}#l
\glsxtrnewnumber[options%keyvals]{label}{number}#l
\printunsrtnumbers#*
\printunsrtnumbers[options%keyvals]#*
#endif
#ifOption:index
\newterm{term}
\newterm[options%keyvals]{term}
\printindex
\printindex[options%keyvals]
\printunsrtindex#*
\printunsrtindex[options%keyvals]#*
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

#keyvals:\glsxtrnewsymbol#c,\glsxtrnewnumber#c,\newsym#c,\newnum#c
description=
parent=
descriptionplural=
text=
first=
plural=
firstplural=
symbol=
symbolplural=
user1=
user2=
user3=
user4=
user5=
user6=
nonumberlist#true,false
see=
#endkeyvals

#ifOption:compatible-2.07
#include:glossaries-compatible-207
#endif
#ifOption:compatible-2.07=true
#include:glossaries-compatible-207
#endif

## options shortcuts=acronyms,acro,ac,all,true provide these
\acs{label}#*r
\acs[options%keyvals]{label}#*r
\acs{label}[insert]#*r
\acs[options%keyvals]{label}[insert]#*r
\acs*{label}#Sr
\acs*[options]{label}#Sr
\acs*{label}[insert]#Sr
\acs*[options]{label}[insert]#Sr
\acs+{label}#Sr
\acs+[options]{label}#Sr
\acs+{label}[insert]#Sr
\acs+[options]{label}[insert]#Sr

\Acs{label}#*r
\Acs[options%keyvals]{label}#*r
\Acs{label}[insert]#*r
\Acs[options%keyvals]{label}[insert]#*r
\Acs*{label}#Sr
\Acs*[options]{label}#Sr
\Acs*{label}[insert]#Sr
\Acs*[options]{label}[insert]#Sr
\Acs+{label}#Sr
\Acs+[options]{label}#Sr
\Acs+{label}[insert]#Sr
\Acs+[options]{label}[insert]#Sr

\acsp{label}#*r
\acsp[options%keyvals]{label}#*r
\acsp{label}[insert]#*r
\acsp[options%keyvals]{label}[insert]#*r
\acsp*{label}#Sr
\acsp*[options]{label}#Sr
\acsp*{label}[insert]#Sr
\acsp*[options]{label}[insert]#Sr
\acsp+{label}#Sr
\acsp+[options]{label}#Sr
\acsp+{label}[insert]#Sr
\acsp+[options]{label}[insert]#Sr

\Acsp{label}#*r
\Acsp[options%keyvals]{label}#*r
\Acsp{label}[insert]#*r
\Acsp[options%keyvals]{label}[insert]#*r
\Acsp*{label}#Sr
\Acsp*[options]{label}#Sr
\Acsp*{label}[insert]#Sr
\Acsp*[options]{label}[insert]#Sr
\Acsp+{label}#Sr
\Acsp+[options]{label}#Sr
\Acsp+{label}[insert]#Sr
\Acsp+[options]{label}[insert]#Sr

\acl{label}#*r
\acl[options%keyvals]{label}#*r
\acl{label}[insert]#*r
\acl[options%keyvals]{label}[insert]#*r
\acl*{label}#Sr
\acl*[options]{label}#Sr
\acl*{label}[insert]#Sr
\acl*[options]{label}[insert]#Sr
\acl+{label}#Sr
\acl+[options]{label}#Sr
\acl+{label}[insert]#Sr
\acl+[options]{label}[insert]#Sr

\Acl{label}#*r
\Acl[options%keyvals]{label}#*r
\Acl{label}[insert]#*r
\Acl[options%keyvals]{label}[insert]#*r
\Acl*{label}#Sr
\Acl*[options]{label}#Sr
\Acl*{label}[insert]#Sr
\Acl*[options]{label}[insert]#Sr
\Acl+{label}#Sr
\Acl+[options]{label}#Sr
\Acl+{label}[insert]#Sr
\Acl+[options]{label}[insert]#Sr

\aclp{label}#*r
\aclp[options%keyvals]{label}#*r
\aclp{label}[insert]#*r
\aclp[options%keyvals]{label}[insert]#*r
\aclp*{label}#Sr
\aclp*[options]{label}#Sr
\aclp*{label}[insert]#Sr
\aclp*[options]{label}[insert]#Sr
\aclp+{label}#Sr
\aclp+[options]{label}#Sr
\aclp+{label}[insert]#Sr
\aclp+[options]{label}[insert]#Sr

\Aclp{label}#*r
\Aclp[options%keyvals]{label}#*r
\Aclp{label}[insert]#*r
\Aclp[options%keyvals]{label}[insert]#*r
\Aclp*{label}#Sr
\Aclp*[options]{label}#Sr
\Aclp*{label}[insert]#Sr
\Aclp*[options]{label}[insert]#Sr
\Aclp+{label}#Sr
\Aclp+[options]{label}#Sr
\Aclp+{label}[insert]#Sr
\Aclp+[options]{label}[insert]#Sr

\acf{label}#*r
\acf[options%keyvals]{label}#*r
\acf{label}[insert]#*r
\acf[options%keyvals]{label}[insert]#*r
\acf*{label}#Sr
\acf*[options]{label}#Sr
\acf*{label}[insert]#Sr
\acf*[options]{label}[insert]#Sr
\acf+{label}#Sr
\acf+[options]{label}#Sr
\acf+{label}[insert]#Sr
\acf+[options]{label}[insert]#Sr

\Acf{label}#*r
\Acf[options%keyvals]{label}#*r
\Acf{label}[insert]#*r
\Acf[options%keyvals]{label}[insert]#*r
\Acf*{label}#Sr
\Acf*[options]{label}#Sr
\Acf*{label}[insert]#Sr
\Acf*[options]{label}[insert]#Sr
\Acf+{label}#Sr
\Acf+[options]{label}#Sr
\Acf+{label}[insert]#Sr
\Acf+[options]{label}[insert]#Sr

\acfp{label}#*r
\acfp[options%keyvals]{label}#*r
\acfp{label}[insert]#*r
\acfp[options%keyvals]{label}[insert]#*r
\acfp*{label}#Sr
\acfp*[options]{label}#Sr
\acfp*{label}[insert]#Sr
\acfp*[options]{label}[insert]#Sr
\acfp+{label}#Sr
\acfp+[options]{label}#Sr
\acfp+{label}[insert]#Sr
\acfp+[options]{label}[insert]#Sr

\Acfp{label}#*r
\Acfp[options%keyvals]{label}#*r
\Acfp{label}[insert]#*r
\Acfp[options%keyvals]{label}[insert]#*r
\Acfp*{label}#Sr
\Acfp*[options]{label}#Sr
\Acfp*{label}[insert]#Sr
\Acfp*[options]{label}[insert]#Sr
\Acfp+{label}#Sr
\Acfp+[options]{label}#Sr
\Acfp+{label}[insert]#Sr
\Acfp+[options]{label}[insert]#Sr

\ac{label}#*r
\ac[options%keyvals]{label}#*r
\ac{label}[insert]#*r
\ac[options%keyvals]{label}[insert]#*r
\Ac{label}#*r
\Ac[options%keyvals]{label}#*r
\Ac{label}[insert]#*r
\Ac[options%keyvals]{label}[insert]#*r
\ac*{label}#Sr
\ac*[options]{label}#Sr
\ac*{label}[insert]#Sr
\ac*[options]{label}[insert]#Sr
\Ac*{label}#Sr
\Ac*[options]{label}#Sr
\Ac*{label}[insert]#Sr
\Ac*[options]{label}[insert]#Sr
\ac+{label}#Sr
\ac+[options]{label}#Sr
\ac+{label}[insert]#Sr
\ac+[options]{label}[insert]#Sr
\Ac+{label}#Sr
\Ac+[options]{label}#Sr
\Ac+{label}[insert]#Sr
\Ac+[options]{label}[insert]#Sr

\acp{label}#*r
\acp[options%keyvals]{label}#*r
\acp{label}[insert]#*r
\acp[options%keyvals]{label}[insert]#*r
\Acp{label}#*r
\Acp[options%keyvals]{label}#*r
\Acp{label}[insert]#*r
\Acp[options%keyvals]{label}[insert]#*r
\acp*{label}#Sr
\acp*[options]{label}#Sr
\acp*{label}[insert]#Sr
\acp*[options]{label}[insert]#Sr
\Acp*{label}#Sr
\Acp*[options]{label}#Sr
\Acp*{label}[insert]#Sr
\Acp*[options]{label}[insert]#Sr
\acp+{label}#Sr
\acp+[options]{label}#Sr
\acp+{label}[insert]#Sr
\acp+[options]{label}[insert]#Sr
\Acp+{label}#Sr
\Acp+[options]{label}#Sr
\Acp+{label}[insert]#Sr
\Acp+[options]{label}[insert]#Sr

\AC{label}#*r
\AC[options]{label}#*r
\AC{label}[insert]#*r
\AC[options]{label}[insert]#*r
\ACP{label}#*r
\ACP[options]{label}#*r
\ACP{label}[insert]#*r
\ACP[options]{label}[insert]#*r
\ACS{label}#*r
\ACS[options]{label}#*r
\ACS{label}[insert]#*r
\ACS[options]{label}[insert]#*r
\ACSP{label}#*r
\ACSP[options]{label}#*r
\ACSP{label}[insert]#*r
\ACSP[options]{label}[insert]#*r
\ACL{label}#*r
\ACL[options]{label}#*r
\ACL{label}[insert]#*r
\ACL[options]{label}[insert]#*r
\ACLP{label}#*r
\ACLP[options]{label}#*r
\ACLP{label}[insert]#*r
\ACLP[options]{label}[insert]#*r
\ACF{label}#*r
\ACF[options]{label}#*r
\ACF{label}[insert]#*r
\ACF[options]{label}[insert]#*r
\ACFP{label}#*r
\ACFP[options]{label}#*r
\ACFP{label}[insert]#*r
\ACFP[options]{label}[insert]#*r

#ifOption:shortcuts=other
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

### 2 Modifications to Existing Commands and Styles ###
## 2.1 Define Entries ##
\glsxtrnopostpunc#*
\glsxtrrestorepostpunc#*

\longnewglossaryentry*{label}{keyvals}{long description}#l

#keyvals:\newentry#c,\longnewglossaryentry*#c
name=
description=
parent=
descriptionplural=
text=
first=
plural=
firstplural=
symbol=
symbolplural=
sort=
type=
user1=
user2=
user3=
user4=
user5=
user6=
nonumberlist#true,false
see=
#endkeyvals

\glsxtrpostlongdescription#*

\makeglossaries[list]

## 2.2 Entry Indexing ##
\glsaddeach{label list}#l
\glsaddeach[options%keyvals]{label list}#l
\GlsXtrAutoAddOnFormat{format list}{glsadd options%keyvals}
\GlsXtrAutoAddOnFormat[label]{format list}{glsadd options%keyvals}
#keyvals:\glsaddeach#c,\GlsXtrAutoAddOnFormat#c
format=%<csname%>
counter=%<counter%>
local#true,false
#endkeyvals

\glsxtrassignfieldfont{text}#*
\GlsXtrSetDefaultGlsOpts{options%keyvals}
\GlsXtrSetDefaultNumberFormat{format csname}
\GlsXtrSetAltModifier{char}{options%keyvals}

#keyvals:\gls#c,\Gls#c,\GLS#c,\glspl#c,\Glspl#c,\GLSpl#c,\glsdisp#c,\glslink#c,\glstext#c,\Glstext#c,\GLStext#c,\glsfirst#c,\Glsfirst#c,\GLSfirst#c,\glsplural#c,\Glsplural#c,\GLSplural#c,\glsfirstplural#c,\Glsfirstplural#c,\GLSfirstplural#c,\glsname#c,\Glsname#c,\GLSname#c,\glssymbol#c,\Glssymbol#c,\GLSsymbol#c,\glssymbolplural#c,\Glssymbolplural#c,\GLSsymbolplural#c,\glsdesc#c,\Glsdesc#c,\GLSdesc#c,\glsdescplural#c,\Glsdescplural#c,\GLSdescplural#c,\glsuseri#c,\Glsuseri#c,\GLSuseri#c,\glsuserii#c,\Glsuserii#c,\GLSuserii#c,\glsuseriii#c,\Glsuseriii#c,\GLSuseriii#c,\glsuseriv#c,\Glsuseriv#c,\GLSuseriv#c,\glsuserv#c,\Glsuserv#c,\GLSuserv#c,\glsuservi#c,\Glsuservi#c,\GLSuservi#c,\cgls#c,\cGls#c,\cglspl#c,\cGlspl#c,\GlsXtrSetDefaultGlsOpts#c,\GlsXtrSetAltModifier#c,\glsxtrsetpopts#c,\glsxtrfmt#c,\glsxtrfmt*#c
noindex#true,false
wrgloss=#before,after
hyperoutside#true,false
textformat=%<csname%>
prefix=%<prefix%>
thevalue=%<location%>
theHvalue=%<<prefix><location>%>
#endkeyvals

#keyvals:\GlsXtrSetDefaultGlsOpts#c,\GlsXtrSetAltModifier#c,\glsxtrsetpopts#c
hyper#true,false
format=%<csname%>
counter=%<counter%>
local#true,false
#endkeyvals

\glsxtrinitwrgloss#*
\ifglsxtrinitwrgloss
\glsxtrinitwrglosstrue#*
\glsxtrinitwrglossfalse#*
\glsxtrdowrglossaryhook{label}#*r
\glslinkpresetkeys#*
\glsaddpresetkeys#*
\glsaddpostsetkeys#*
\glsxtrinithyperoutside#*

#keyvals:\glsadd#c,\glsaddall#c
thevalue=%<location%>
theHvalue=%<<prefix><location>%>
#endkeyvals

## 2.3 Cross-References (“see” and “see also”) ##
\glsxtraddallcrossrefs#*
\glsxtrusesee{label}#r
\glsxtruseseeformat{tag}{xr list}#*
\glsxtrhiername{label}#*r
\glsxtrhiernamesep
\Glsxtrhiername{label}#*r
\GlsXtrhiername{label}#*r
\GLSxtrhiername{label}#*r
\GLSXTRhiername{label}#*r
\glsxtruseseealso{label}#r
\glsxtruseseealsoformat{xr list}#*
\glsxtrusealias{label}#*r
\glsxtrseealsolabels{label}#*r
\glsxtrseelist{xr list}#*
\glsseefirstitem{label}#*r
\glsseelastoxfordsep
\glsxtrindexseealso{label}{xr list}#*
\seealsoname#*

## 2.4 Entry Display Style Modifications ##
\glsxtrregularfont{text}#*
\glsxtrabbreviationfont{text}#*
\glsxtrgenabbrvfmt#*
\glssetabbrvfmt{category}#*
\glsxtrpostlinkhook#*
\glsxtrpostlink#*
\glsxtrpostlinkendsentence#*
\glsxtrifcustomdiscardperiod{true}{false}#*
\glsdefpostlink{category}{definition}#*
\glsxtrpostlinkAddDescOnFirstUse#*
\glsxtrpostlinkAddSymbolOnFirstUse#*
\glsxtrpostlinkAddSymbolDescOnFirstUse#*
\glsxtrifwasfirstuse{true}{false}#*

## 2.6 First Use Flag ##
\GlsXtrIfUnusedOrUndefined{label}{true}{false}#*
\glslocalreseteach{labellist}#*r
\glslocalunseteach{labellist}#*r
\GlsXtrStartUnsetBuffering#*
\GlsXtrStopUnsetBuffering#*
\GlsXtrForUnsetBufferedList{csname}#*
\GlsXtrDiscardUnsetBuffering#*
\GlsXtrExpandedFmt{csname}{text}#*

## 2.7 Plurals ##
\glsxtrabbrvpluralsuffix#*

## 2.8 Nested Links ##
\glsxtrp{field}{label}#*r
\glsps{label}#*r
\glspt{label}#*r
\glsxtrsetpopts{options%keyvals}#*
\glossxtrsetpopts#*
\Glsxtrp{field}{label}#*r
\GLSxtrp{field}{label}#*r

## 2.9 Acronym Style Modifications ##
\RestoreAcronyms#*
\glsacspacemax#*

## 2.10 Glossaries ##
\newignoredglossary*{name}#*
\provideignoredglossary{name}#*

#keyvals:\printnoidxglossary#c,\printglossary#c,\printunsrtglossary#c,\printsymbols#c,\printnumbers#c,\printindex#c,\printacronyms#c,\printabbreviations#c,\printunsrtabbreviations#c,\printunsrtsymbols#c,\printunsrtnumbers#c,\printunsrtacronyms#c,\printunsrtindex#c,\printunsrtglossary#c,\printunsrtglossary*#c,\begin{printunsrtglossarywrap}#c
target#true,false
targetnameprefix=%<prefix%>
prefix=%<prefix%>
label=##l
groups#true,false
leveloffset=%<n or ++n%>
#endkeyvals

\glsxtrsetglossarylabel{label}#*l

## 2.11 Glossary Style Modifications ##
\glsxtrsetgrouptitle{label}{title%text}#*
\glsxtrgetgrouptitle{group}{cmd}#*d
\glsxtrlocalsetgrouptitle{label}{title%text}#*
\glsentrypdfsymbol{label}#*r
\glossentrynameother{label}{field}#*r
\glsxtrpostnamehook{label}#*r
\glsxtrdoautoindexname{label}{indexname}#*r
\glsdefpostname{category}{definition}#*
\glsextrapostnamehook{label}#*r
\glsxtrpostdescription#*
\glsdefpostdesc{category}{definition}#*
\GlsXtrFormatLocationList{number list}#*
\GlsXtrEnablePreLocationTag{page}{pages}#*
\glsxtrdisplaysingleloc{format}{location}#*
\glsxtrdisplaystartloc{format}{location}#*
\glsxtrdisplayendloc{format}{location}#*
\glsxtrlocrangefmt#*
\glsxtrdisplayendlochook{format}{location}#*
\glsxtrlocationhyperlink{counter}{prefix}{location}#*

### 4 Abbreviations ###
\newabbreviation{label}{short}{long}#l
\newabbreviation[options%keyvals]{label}{short}{long}#l

#keyvals:\newabbreviation#c,\newabbr#c
name=
description=
parent=
descriptionplural=
text=
first=
plural=
firstplural=
symbol=
symbolplural=
sort=
type=
user1=
user2=
user3=
user4=
user5=
user6=
nonumberlist#true,false
see=
long=
longplural=
short=
shortplural=
category=
#endkeyvals

\glsuseabbrvfont{text}{category}#*
\glsuselongfont{text}{category}#*
\forallabbreviationlists{cmd}{body}#*
\ExtraCustomAbbreviationFields#*
\MakeAcronymsAbbreviations#*

## 4.1 Tagging Initials ##
\GlsXtrEnableInitialTagging{categories}{cmd}#*d
\glsxtrtagfont{text}#*

## 4.2 Abbreviation Styles ##
\setabbreviationstyle{style name}
\setabbreviationstyle[category]{style name}
\letabbreviationstyle{style1}{style2}#*

\glsxtrshort{label}#r
\glsxtrshort[options%keyvals]{label}#r
\glsxtrshort{label}[insert]#*r
\glsxtrshort[options%keyvals]{label}[insert]#*r
\glsxtrlong{label}#r
\glsxtrlong[options%keyvals]{label}#r
\glsxtrlong{label}[insert]#*r
\glsxtrlong[options%keyvals]{label}[insert]#*r
\glsxtrfull{label}#r
\glsxtrfull[options%keyvals]{label}#r
\glsxtrfull{label}[insert]#*r
\glsxtrfull[options%keyvals]{label}[insert]#*r

\Glsxtrshort{label}#r
\Glsxtrshort[options%keyvals]{label}#r
\Glsxtrshort{label}[insert]#*r
\Glsxtrshort[options%keyvals]{label}[insert]#*r
\Glsxtrlong{label}#r
\Glsxtrlong[options%keyvals]{label}#r
\Glsxtrlong{label}[insert]#*r
\Glsxtrlong[options%keyvals]{label}[insert]#*r
\Glsxtrfull{label}#r
\Glsxtrfull[options%keyvals]{label}#r
\Glsxtrfull{label}[insert]#*r
\Glsxtrfull[options%keyvals]{label}[insert]#*r

\GLSxtrshort{label}#r
\GLSxtrshort[options%keyvals]{label}#r
\GLSxtrshort{label}[insert]#*r
\GLSxtrshort[options%keyvals]{label}[insert]#*r
\GLSxtrlong{label}#r
\GLSxtrlong[options%keyvals]{label}#r
\GLSxtrlong{label}[insert]#*r
\GLSxtrlong[options%keyvals]{label}[insert]#*r
\GLSxtrfull{label}#r
\GLSxtrfull[options%keyvals]{label}#r
\GLSxtrfull{label}[insert]#*r
\GLSxtrfull[options%keyvals]{label}[insert]#*r

\glsxtrshortpl{label}#*r
\glsxtrshortpl[options%keyvals]{label}#*r
\glsxtrshortpl{label}[insert]#*r
\glsxtrshortpl[options%keyvals]{label}[insert]#*r
\glsxtrlongpl{label}#*r
\glsxtrlongpl[options%keyvals]{label}#*r
\glsxtrlongpl{label}[insert]#*r
\glsxtrlongpl[options%keyvals]{label}[insert]#*r
\glsxtrfullpl{label}#*r
\glsxtrfullpl[options%keyvals]{label}#*r
\glsxtrfullpl{label}[insert]#*r
\glsxtrfullpl[options%keyvals]{label}[insert]#*r

\Glsxtrshortpl{label}#*r
\Glsxtrshortpl[options%keyvals]{label}#*r
\Glsxtrshortpl{label}[insert]#*r
\Glsxtrshortpl[options%keyvals]{label}[insert]#*r
\Glsxtrlongpl{label}#*r
\Glsxtrlongpl[options%keyvals]{label}#*r
\Glsxtrlongpl{label}[insert]#*r
\Glsxtrlongpl[options%keyvals]{label}[insert]#*r
\Glsxtrfullpl{label}#*r
\Glsxtrfullpl[options%keyvals]{label}#*r
\Glsxtrfullpl{label}[insert]#*r
\Glsxtrfullpl[options%keyvals]{label}[insert]#*r

\GLSxtrshortpl{label}#*r
\GLSxtrshortpl[options%keyvals]{label}#*r
\GLSxtrshortpl{label}[insert]#*r
\GLSxtrshortpl[options%keyvals]{label}[insert]#*r
\GLSxtrlongpl{label}#*r
\GLSxtrlongpl[options%keyvals]{label}#*r
\GLSxtrlongpl{label}[insert]#*r
\GLSxtrlongpl[options%keyvals]{label}[insert]#*r
\GLSxtrfullpl{label}#*r
\GLSxtrfullpl[options%keyvals]{label}#*r
\GLSxtrfullpl{label}[insert]#*r
\GLSxtrfullpl[options%keyvals]{label}[insert]#*r

\cGLS{label}#*r
\cGLS[options%keyvals]{label}#*r
\cGLS{label}[insert]#*r
\cGLS[options%keyvals]{label}[insert]#*r
\cGLSpl{label}#*r
\cGLSpl[options%keyvals]{label}#*r
\cGLSpl{label}[insert]#*r
\cGLSpl[options%keyvals]{label}[insert]#*r

#ifOption:shortcuts=abbreviations
\newabbr{label}{short}{long}#l
\newabbr[options%keyvals]{label}{short}{long}#l
#endif
#ifOption:shortcuts=abbr
\newabbr{label}{short}{long}#l
\newabbr[options%keyvals]{label}{short}{long}#l
#endif

## options shortcuts=abbreviations,abbr,all,true provide these
\AC{label}#*r
\AC[options]{label}#*r
\AC{label}[insert]#*r
\AC[options]{label}[insert]#*r

\ab{label}#*r
\ab[options]{label}#*r
\ab{label}[insert]#*r
\ab[options]{label}[insert]#*r
\abp{label}#*r
\abp[options]{label}#*r
\abp{label}[insert]#*r
\abp[options]{label}[insert]#*r
\as{label}#*r
\as[options]{label}#*r
\as{label}[insert]#*r
\as[options]{label}[insert]#*r
\asp{label}#*r
\asp[options]{label}#*r
\asp{label}[insert]#*r
\asp[options]{label}[insert]#*r
\al{label}#*r
\al[options]{label}#*r
\al{label}[insert]#*r
\al[options]{label}[insert]#*r
\alp{label}#*r
\alp[options]{label}#*r
\alp{label}[insert]#*r
\alp[options]{label}[insert]#*r
\af{label}#*r
\af[options]{label}#*r
\af{label}[insert]#*r
\af[options]{label}[insert]#*r
\afp{label}#*r
\afp[options]{label}#*r
\afp{label}[insert]#*r
\afp[options]{label}[insert]#*r
\Ab{label}#*r
\Ab[options]{label}#*r
\Ab{label}[insert]#*r
\Ab[options]{label}[insert]#*r
\Abp{label}#*r
\Abp[options]{label}#*r
\Abp{label}[insert]#*r
\Abp[options]{label}[insert]#*r
\As{label}#*r
\As[options]{label}#*r
\As{label}[insert]#*r
\As[options]{label}[insert]#*r
\Asp{label}#*r
\Asp[options]{label}#*r
\Asp{label}[insert]#*r
\Asp[options]{label}[insert]#*r
\Al{label}#*r
\Al[options]{label}#*r
\Al{label}[insert]#*r
\Al[options]{label}[insert]#*r
\Alp{label}#*r
\Alp[options]{label}#*r
\Alp{label}[insert]#*r
\Alp[options]{label}[insert]#*r
\Af{label}#*r
\Af[options]{label}#*r
\Af{label}[insert]#*r
\Af[options]{label}[insert]#*r
\Afp{label}#*r
\Afp[options]{label}#*r
\Afp{label}[insert]#*r
\Afp[options]{label}[insert]#*r
\AB{label}#*r
\AB[options]{label}#*r
\AB{label}[insert]#*r
\AB[options]{label}[insert]#*r
\ABP{label}#*r
\ABP[options]{label}#*r
\ABP{label}[insert]#*r
\ABP[options]{label}[insert]#*r
\AS{label}#*r
\AS[options]{label}#*r
\AS{label}[insert]#*r
\AS[options]{label}[insert]#*r
\ASP{label}#*r
\ASP[options]{label}#*r
\ASP{label}[insert]#*r
\ASP[options]{label}[insert]#*r
\AL{label}#*r
\AL[options]{label}#*r
\AL{label}[insert]#*r
\AL[options]{label}[insert]#*r
\ALP{label}#*r
\ALP[options]{label}#*r
\ALP{label}[insert]#*r
\ALP[options]{label}[insert]#*r
\AF{label}#*r
\AF[options]{label}#*r
\AF{label}[insert]#*r
\AF[options]{label}[insert]#*r
\AFP{label}#*r
\AFP[options]{label}#*r
\AFP{label}[insert]#*r
\AFP[options]{label}[insert]#*r

## 4.4 Predefined Abbreviation Styles ##
\glsxtrparen{text}#*
\glsabbrvdefaultfont{text}#*
\glsfirstabbrvdefaultfont{text}#*
\glslongdefaultfont{text}#*
\glsfirstlongdefaultfont{text}#*
\glsxtrabbrvpluralsuffix#*
\glsabbrvscfont{text}#*
\glsxtrfirstscfont{text}#*
\glsfirstabbrvscfont{text}#*
\glsxtrscsuffix#*
\glsabbrvsmfont{text}#*
\glsfirstabbrvsmfont{text}#*
\glsxtrfirstsmfont{text}#*
\glsxtrsmsuffix#*
\glsabbrvemfont{text}#*
\glsfirstabbrvemfont{text}#*
\glsxtremsuffix#*
\glsfirstlongemfont{long-form}#*
\glslongemfont{long-form}#*
\glsabbrvuserfont{text}#*
\glsfirstabbrvuserfont{text}#*
\glslonguserfont{text}#*
\glsfirstlonguserfont{text}#*
\glsxtrusersuffix#*
\glsabbrvhyphenfont{text}#*
\glsfirstabbrvhyphenfont{text}#*
\glslonghyphenfont{text}#*
\glsfirstlonghyphenfont{text}#*
\glsxtrhyphensuffix#*
\glsabbrvonlyfont{text}#*
\glsfirstabbrvonlyfont{text}#*
\glslongonlyfont{text}#*
\glsfirstlongonlyfont{text}#*
\glsxtronlysuffix#*
\glsabbrvsconlyfont{text}#*
\glsfirstabbrvsconlyfont{text}#*
\glsxtrsconlysuffix#*
\glsabbrvscuserfont{text}#*
\glsfirstabbrvscuserfont{text}#*
\glsxtrscusersuffix#*
\glsxtrinsertinsidetrue#*
\glsxtrfullsep{label}#*r
\GlsXtrWarnDeprecatedAbbrStyle{old name}{new name}#*
\glsxtrshortnolongname#*
\glsxtrshortdescname#*
\glsxtrlongnoshortdescname#*
\glsxtrlongnoshortname#*
\glsxtrlongshortname#*
\glsxtronlyname#*
\glsxtrsconlyname#*
\glsxtronlydescname#*
\glsxtronlydescsort#*
\glsxtrsconlydescname#*
\glsxtrsconlydescsort#*
\glsxtruserfield#*
\glsxtruserparen{text}{label}#*r
\glsuserdescription{long}{label}#*r
\glsxtrlongshortdescsort#*
\glsxtrlongshortdescname#*
\glsxtrlongshortuserdescname#*
\glsxtrshortlongname#*
\glsxtrshortlongdescname#*
\glsxtrshortlonguserdescname#*
\glsxtrshortlongdescsort#*
\glsxtrfootnotename#*
\glsfirstlongfootnotefont{text}#*
\glslongfootnotefont{text}#*
\glsxtrabbrvfootnote{label}{string}#*r
\glsxtrfootnotedescname#*
\glsxtrfootnotedescsort#*
\glsxtrifnextpunc{true}{false}#*
\glsxtrlonghyphenshort{label}{long}{short}{insert}#*r
\glsxtrposthyphenshort{label}{insert}#*r
\glsxtrlonghyphen{long}{label}{insert}#*r
\glsxtrshorthyphen{long}{label}{insert}#*r
\glsxtrshorthyphenlong{long}{short}{label}{insert}#*r
\glsxtrposthyphenlong{label}{insert}#*r
\glsxtrifhyphenstart{string}{true}{false}#*
\ifglsxtrinsertinside#*
\glsxtrinsertinsidetrue#*
\glsxtrinsertinsidefalse#*
\glsxtrlonghyphennoshort{label}{long}{insert}#*r
\glsxtrlongshortscuserdescname#*
\glsxtrlongshortscusername#*
\glsxtrposthyphensubsequent{label}{insert}#*r
\glsxtrpostlocalreset{label}#*r
\glsxtrpostlocalunset{label}#*r
\glsxtrpostreset{label}#*r
\glsxtrpostunset{label}#*r


## 4.5 Defining New Abbreviation Styles ##
\newabbreviationstyle{name}{setup}{fmts}
\renewabbreviationstyle{name}{setup}{fmts}#*
\CustomAbbreviationFields#*
\newabbreviationhook#*
\GlsXtrPostNewAbbreviation#*
\glsxtrnewabbrevpresetkeyhook{arg1}{arg2}{arg3}#*
\glsshortpltok#*
\glslongpltok#*
\glsxtrorgshort#*
\glsxtrorglong#*
\glscategorylabel#*
\GlsXtrUseAbbrStyleSetup{name}#*
\abbrvpluralsuffix#*
\glsfirstabbrvfont{text}#*
\glsabbrvfont{text}#*
\glsfirstlongfont{text}#*
\glslongfont{text}#*
\glsxtrfullformat{label}{insert}#*r
\Glsxtrfullformat{label}{insert}#*r
\glsxtrfullplformat{label}{insert}#*r
\Glsxtrfullplformat{label}{insert}#*r
\glsxtrinlinefullformat{label}{insert}#*r
\Glsxtrinlinefullformat{label}{insert}#*r
\glsxtrinlinefullplformat{label}{insert}#*r
\Glsxtrinlinefullplformat{label}{insert}#*r
\glsxtrsubsequentfmt{label}{insert}#*r
\Glsxtrsubsequentfmt{label}{insert}#*r
\glsxtrsubsequentplfmt{label}{insert}#*r
\Glsxtrsubsequentplfmt{label}{insert}#*r
\GlsXtrUseAbbrStyleFmts{name}#*
\Glsxtrdefaultsubsequentfmt{label}{insert}#*r
\glsxtrdefaultsubsequentfmt{label}{insert}#*r
\Glsxtrdefaultsubsequentplfmt{label}{insert}#*r
\glsxtrdefaultsubsequentplfmt{label}{insert}#*r

### 5 Entries in Sectioning Titles, Headers, Captions and Contents ###
## 5.1 Simplistic Approach ##
\glsxtrRevertMarks
\glsxtrRevertTocMarks

## 5.2 New Commands Designed for Chapter/Section Headings ##
\glsfmtshort{label}#*r
\glsfmtshortpl{label}#*r
\Glsfmtshort{label}#*r
\Glsfmtshortpl{label}#*r
\GLSfmtshort{label}#*r
\Glsfmtshortpl{label}#*r
\glsfmtlong{label}#*r
\glsfmtlongpl{label}#*r
\Glsfmtlong{label}#*r
\Glsfmtlongpl{label}#*r
\GLSfmtlong{label}#*r
\GLSfmtlongpl{label}#*r
\glspdffmtfull{label}#*r
\glspdffmtfullpl{label}#*r
\glsfmtfull{label}#*r
\glsfmtfullpl{label}#*r
\Glsfmtfull{label}#*r
\Glsfmtfullpl{label}#*r
\GLSfmtfull{label}#*r
\GLSfmtfullpl{label}#*r
\glsfmttext{label}#*r
\Glsfmttext{label}#*r
\GLSfmttext{label}#*r
\glsfmtplural{label}#*r
\Glsfmtplural{label}#*r
\GLSfmtplural{label}#*r
\glsfmtname{label}#*r
\Glsfmtname{label}#*r
\GLSfmtname{label}#*r
\glsfmtfirst{label}#*r
\Glsfmtfirst{label}#*r
\GLSfmtfirst{label}#*r
\glsfmtfirstpl{label}#*r
\Glsfmtfirstpl{label}#*r
\GLSfmtfirstpl{label}#*r

### 6 Multi (or Compound) Entries ###
\multiglossaryentry{multi-label}{labellist}
\multiglossaryentry{multi-label}[main label]{labellist}#*
\multiglossaryentry[options%keyvals]{multi-label}{labellist}
\multiglossaryentry[options%keyvals]{multi-label}[main label]{labellist}#*
\mgls{multi-label}
\mgls[options%keyvals]{multi-label}
\mgls{multi-label}[insert]#*
\mgls[options%keyvals]{multi-label}[insert]#*
\providemultiglossaryentry{multi-label}{labellist}
\providemultiglossaryentry{multi-label}[main label]{labellist}#*
\providemultiglossaryentry[options%keyvals]{multi-label}{labellist}
\providemultiglossaryentry[options%keyvals]{multi-label}[main label]{labellist}#*
\ifmultiglossaryentryglobal#*
\multiglossaryentryglobaltrue
\multiglossaryentryglobalfalse
\mglsSetOptions{multi-label}{options%keyvals}
\mglsAddOptions{multi-label}{options%keyvals}
\GlsXtrMglsOrGls{mgls cmd}{gls cmd}{label}#*
\GlsXtrMglsOrGls{mgls cmd}{gls cmd}[options%keyvals]{label}#*
\GlsXtrMglsOrGls{mgls cmd}{gls cmd}[options%keyvals]{label}[insert]#*
\mglsWriteSeparateRefsFalse#*
\mglsWriteSeparateRefsTrue#*

## 6.2 Main and Other Elements ##
\mglsSetMain{multi-label}{new-main-label}

## 6.3 Prefixes and Suffixes ##
\mglsprefix#*
\mglssuffix#*
\mglsdefcategoryprefix{category}{definition}#*
\mglsdefcategorysuffix{category}{definition}#*
\mglshascategoryprefix{category}{true}{false}#*
\mglshascategorysuffix{category}{true}{false}#*
\mglsusecategoryprefix{category}#*
\mglsusecategorysuffix{category}#*

## 6.4 Separators ##
\glscombinedsep{prev label%ref}{next label%ref}#*r
\glscombinedfirstsep{prev label%ref}{next label%ref}#*r
\glscombinedsepfirst{prev label%ref}{next label%ref}#*r
\glscombinedfirstsepfirst{prev label%ref}{next label%ref}#*r
\glssetcombinedsepabbrvnbsp#*
\glssetcombinedsepabbrvnone#*
\glssetcombinedsepnarrow{width}{narrow sep%l}#*

## 6.5 \mgls Element Hooks ##
\mglselementprehook#*
\mglselementposthook#*
\mglscurrentmultilabel#*
\mglscurrentmainlabel#*
\mglscurrentlist#*
\mglscurrentoptions#*
\mglscurrentcategory#*
\glsxtrcurrentmglscsname#*
\mglsisfirstuse{true}{false}#*
\mglscurrentlabel#*
\mglselementindex#*
\mglscurrentprefix#*
\mglscurrentsuffix#*
\mglsiflast{true}{false}#*

## 6.6 Post-Link Hook ##
\mglscustompostlinkhook#*
\mglslastelementpostlinkhook#*
\mglslastmainpostlinkhook#*
\mglslastmultilabel#*
\mglslastcategory#*
\mglswasfirstuse{true}{false}#*
\mglslastelementlabel#*
\mglsiflastelementskipped{true}{false}#*
\mglsiflastelementwasfirstuse{true}{false}#*
\mglsiflastelementwasplural{true}{false}#*
\mglsiflastelementcapscase{no-change}{firstuc}{all caps}#*
\mglslastmainlabel#*
\mglsiflastmainskipped{true}{false}#*
\mglsiflastmainwasfirstuse{true}{false}#*
\mglsiflastmainwasplural{true}{false}#*
\mglsiflastmaincapscase{no-change}{firstuc}{all caps}#*

## 6.7 Multi-Entry First Use ##
\ifmglsused{multi-label}{true}{false}#*
\mglsunset{multi-label}#*
\mglsreset{multi-label}#*
\mglslocalunset{multi-label}#*
\mglslocalreset{multi-label}#*
\mglsunsetall#*
\mglsresetall#*

## 6.9 Multi-Entry Settings ##
\multiglossaryentrysetup{options%keyvals}

#keyvals:\multiglossaryentry#c,\multiglossaryentrysetup#c
indexmain=#false,true,first
indexothers=#false,true,first
encapmain=%<format%>
encapothers=%<format%>
postlinks=#none,all,notlast,mainnotlast,mainonly,othernotlast,otheronly
mpostlink=#false,true,firstonly,usedonly
mpostlinkelement=#last,main,custom
firstprefix=%<prefix%>
usedprefix=%<prefix%>
firstsuffix=%<suffix%>
usedsuffix=%<suffix%>
firstskipmain#true,false
firstskipothers#true,false
usedskipmain#true,false
usedskipothers#true,false
hyper=#none,allmain,mainonly,individual,otheronly,notmainfirst,nototherfirst,notfirst
textformat=%<csname%>
category=%<category%>
mglsopts={%<mgls options%>}
#endkeyvals

\glsxtrmglsWarnAllSkipped{message%text}{insert}{cmd}#*

## 6.10 \mgls Options ##

#keyvals:\mgls#c,\Mgls#c,\MGls#c,\MGLS#c,\mglspl#c,\Mglspl#c,\MGlspl#c,\MGLSpl#c,\mglsname#c,\Mglsname#c,\MGlsname#c,\MGLSname#c,\mglsmainpl#c,\Mglsmainpl#c,\MGlsmainpl#c,\MGLSmainpl#c,\mglsshort#c,\Mglsshort#c,\MGlsshort#c,\MGLSshort#c,\mglslong#c,\Mglslong#c,\MGlslong#c,\MGLSlong#c,\mglsfull#c,\Mglsfull#c,\MGlsfull#c,\MGLSfull#c,\mglssymbol#c,\Mglssymbol#c,\MGlssymbol#c,\MGLSsymbol#c,\mglsusefield#c,\Mglsusefield#c,\MGlsusefield#c,\MGLSusefield#c,\mglsSetOptions#c,\mglsAddOptions#c
setup={%<options%>}
all={%<gls options%>}
main={%<gls options%>}
others={%<gls options%>}
hyper#true,false
multiunset=#global,local,none
presetlocal#true,false
resetall#true,false
resetmain#true,false
resetothers#true,false
unsetall#true,false
unsetmain#true,false
unsetothers#true,false
#endkeyvals

\mglselementreset{label}#*r
\mglselementunset{label}#*r
\mglsunsetothers{multi-label}
\mglslocalunsetothers{multi-label}

## 6.11 Variants of \mgls ##
\mglspl{multi-label}#
\mglspl[options%keyvals]{multi-label}#
\mglspl{multi-label}[insert]#*
\mglspl[options%keyvals]{multi-label}[insert]#*
\mglsmainpl{multi-label}#
\mglsmainpl[options%keyvals]{multi-label}#
\mglsmainpl{multi-label}[insert]#*
\mglsmainpl[options%keyvals]{multi-label}[insert]#*
\Mgls{multi-label}#
\Mgls[options%keyvals]{multi-label}#
\Mgls{multi-label}[insert]#*
\Mgls[options%keyvals]{label}[insert]#*
\MGls{multi-label}#
\MGls[options%keyvals]{multi-label}#
\MGls{multi-label}[insert]#*
\MGls[options%keyvals]{multi-label}[insert]#*
\Mglspl{multi-label}#
\Mglspl[options%keyvals]{multi-label}#
\Mglspl{multi-label}[insert]#*
\Mglspl[options%keyvals]{multi-label}[insert]#*
\Mglsmainpl{multi-label}#
\Mglsmainpl[options%keyvals]{multi-label}#
\Mglsmainpl{multi-label}[insert]#*
\Mglsmainpl[options%keyvals]{multi-label}[insert]#*
\MGlspl{multi-label}#
\MGlspl[options%keyvals]{multi-label}#
\MGlspl{multi-label}[insert]#*
\MGlspl[options%keyvals]{multi-label}[insert]#*
\MGlsmainpl{multi-label}#
\MGlsmainpl[options%keyvals]{multi-label}#
\MGlsmainpl{multi-label}[insert]#*
\MGlsmainpl[options%keyvals]{multi-label}[insert]#*
\MGLS{multi-label}#
\MGLS[options%keyvals]{multi-label}#
\MGLS{multi-label}[insert]#*
\MGLS[options%keyvals]{multi-label}[insert]#*
\MGLSpl{multi-label}#
\MGLSpl[options%keyvals]{multi-label}#
\MGLSpl{multi-label}[insert]#*
\MGLSpl[options%keyvals]{multi-label}[insert]#*
\MGLSmainpl{multi-label}#
\MGLSmainpl[options%keyvals]{multi-label}#
\MGLSmainpl{multi-label}[insert]#*
\MGLSmainpl[options%keyvals]{multi-label}[insert]#*
\mglsshort{multi-label}#
\mglsshort[options%keyvals]{multi-label}#
\mglsshort{multi-label}[insert]#*
\mglsshort[options%keyvals]{multi-label}[insert]#*
\mglslong{multi-label}#
\mglslong[options%keyvals]{multi-label}#
\mglslong{multi-label}[insert]#*
\mglslong[options%keyvals]{multi-label}[insert]#*
\mglsfull{multi-label}#
\mglsfull[options%keyvals]{multi-label}#
\mglsfull{multi-label}[insert]#*
\mglsfull[options%keyvals]{multi-label}[insert]#*
\Mglsshort{multi-label}#
\Mglsshort[options%keyvals]{multi-label}#
\Mglsshort{multi-label}[insert]#*
\Mglsshort[options%keyvals]{multi-label}[insert]#*
\Mglslong{multi-label}#
\Mglslong[options%keyvals]{multi-label}#
\Mglslong{multi-label}[insert]#*
\Mglslong[options%keyvals]{multi-label}[insert]#*
\Mglsfull{multi-label}#
\Mglsfull[options%keyvals]{multi-label}#
\Mglsfull{multi-label}[insert]#*
\Mglsfull[options%keyvals]{multi-label}[insert]#*
\mglsname{multi-label}#*
\mglsname[options%keyvals]{multi-label}#*
\mglsname{multi-label}[insert]#*
\mglsname[options%keyvals]{multi-label}[insert]#*
\mglssymbol{multi-label}#*
\mglssymbol[options%keyvals]{multi-label}#*
\mglssymbol{multi-label}[insert]#*
\mglssymbol[options%keyvals]{multi-label}[insert]#*
\mglsusefield{multi-label}#*
\mglsusefield[options%keyvals]{multi-label}#*
\mglsusefield{multi-label}[insert]#*
\mglsusefield[options%keyvals]{multi-label}[insert]#*
\Mglsname{multi-label}#*
\Mglsname[options%keyvals]{multi-label}#*
\Mglsname{multi-label}[insert]#*
\Mglsname[options%keyvals]{multi-label}[insert]#*
\Mglssymbol{multi-label}#*
\Mglssymbol[options%keyvals]{multi-label}#*
\Mglssymbol{multi-label}[insert]#*
\Mglssymbol[options%keyvals]{multi-label}[insert]#*
\Mglsusefield{multi-label}#*
\Mglsusefield[options%keyvals]{multi-label}#*
\Mglsusefield{multi-label}[insert]#*
\Mglsusefield[options%keyvals]{multi-label}[insert]#*
\MGlsname{multi-label}#*
\MGlsname[options%keyvals]{multi-label}#*
\MGlsname{multi-label}[insert]#*
\MGlsname[options%keyvals]{multi-label}[insert]#*
\MGlssymbol{multi-label}#*
\MGlssymbol[options%keyvals]{multi-label}#*
\MGlssymbol{multi-label}[insert]#*
\MGlssymbol[options%keyvals]{multi-label}[insert]#*
\MGlsusefield{multi-label}#*
\MGlsusefield[options%keyvals]{multi-label}#*
\MGlsusefield{multi-label}[insert]#*
\MGlsusefield[options%keyvals]{multi-label}[insert]#*
\mglsfield#*
\mpglsWarning#*
\mpgls{multi-label}#*
\mpgls[options%keyvals]{multi-label}#*
\mpgls{multi-label}[insert]#*
\mpgls[options%keyvals]{multi-label}[insert]#*
\mpglspl{multi-label}#*
\mpglspl[options%keyvals]{multi-label}#*
\mpglspl{multi-label}[insert]#*
\mpglspl[options%keyvals]{multi-label}[insert]#*
\mpglsmainpl{multi-label}#*
\mpglsmainpl[options%keyvals]{multi-label}#*
\mpglsmainpl{multi-label}[insert]#*
\mpglsmainpl[options%keyvals]{multi-label}[insert]#*
\Mpgls{multi-label}#*
\Mpgls[options%keyvals]{multi-label}#*
\Mpgls{multi-label}[insert]#*
\Mpgls[options%keyvals]{multi-label}[insert]#*
\Mpglspl{multi-label}#*
\Mpglspl[options%keyvals]{multi-label}#*
\Mpglspl{multi-label}[insert]#*
\Mpglspl[options%keyvals]{multi-label}[insert]#*
\Mpglsmainpl{multi-label}#*
\Mpglsmainpl[options%keyvals]{multi-label}#*
\Mpglsmainpl{multi-label}[insert]#*
\Mpglsmainpl[options%keyvals]{multi-label}[insert]#*
\MPGls{multi-label}#*
\MPGls[options%keyvals]{multi-label}#*
\MPGls{multi-label}[insert]#*
\MPGls[options%keyvals]{multi-label}[insert]#*
\MPGlspl{multi-label}#*
\MPGlspl[options%keyvals]{multi-label}#*
\MPGlspl{multi-label}[insert]#*
\MPGlspl[options%keyvals]{multi-label}[insert]#*
\MPGlsmainpl{multi-label}#*
\MPGlsmainpl[options%keyvals]{multi-label}#*
\MPGlsmainpl{multi-label}[insert]#*
\MPGlsmainpl[options%keyvals]{multi-label}[insert]#*
\MPGLS{multi-label}#*
\MPGLS[options%keyvals]{multi-label}#*
\MPGLS{multi-label}[insert]#*
\MPGLS[options%keyvals]{multi-label}[insert]#*
\MPGLSpl{multi-label}#*
\MPGLSpl[options%keyvals]{multi-label}#*
\MPGLSpl{multi-label}[insert]#*
\MPGLSpl[options%keyvals]{multi-label}[insert]#*
\MPGLSmainpl{multi-label}#*
\MPGLSmainpl[options%keyvals]{multi-label}#*
\MPGLSmainpl{multi-label}[insert]#*
\MPGLSmainpl[options%keyvals]{multi-label}[insert]#*

## 6.12 Cross-References ##
\mglsseefirstitem{label}#*r
\mglsseeitem{label}#*r
\glsxtrifmulti{label}{true}{false}#*
\glsxtrmultimain{multi-label}#*
\glsxtrmultilist{multi-label}#*
\mglsforelements{multi-label}{cmd}{body}#*
\mglsforotherelements{multi-label}{cmd}{body}#*
\glsxtrmultitotalelements{multi-label}#*
\glsxtrmultimainindex{multi-label}#*
\glsxtrmultilastotherindex{multi-label}#*
\writemultiglossentry{options}{multi-label}{main-label}{list}#*

## 6.14 bib2gls ##
# see glossaries-extra-bib2gls.cwl

### 7 Categories ###
\glscategory{label}#r
\glsifcategory{entry-label}{category-label}{true}{false}#*
\glsxtrchecknohyperfirst{label}#*r
\glsxtrwordsep#*
\glsxtrword{word}#*
\glsxtrfieldtitlecasecs{phrase cmd}#*
\glsdefaultshortaccess{short}{long}#*
\glsxtrassignactualsetup#*
\glssetcategoryattribute{category}{attribute}{value}
\glssetcategoriesattribute{category list}{attribute list}{value}
\glssetcategoriesattributes{category list}{attribute list}{value}
\glssetregularcategory{category}
\glssetattribute{entry}{attribute}{value}
\glsunsetcategoryattribute{category}{attribute}
\glsgetcategoryattribute{category}{attribute}
\glsgetattribute{entry}{attribute}
\glshascategoryattribute{category}{attribute}{true}{false}#*
\glshasattribute{entry}{attribute}{value}{true}{false}#*
\glsifcategoryattribute{category}{attribute}{value}{true}{false}#*
\glsifattribute{entry}{attribute}{value}{true}{false}#*
\glsifregularcategory{category}{true}{false}#*
\glsifregular{entry}{true}{false}#*
\glsifnotregularcategory{category}{true}{false}#*
\glsifnotregular{entry}{true}{false}#*
\glsforeachincategory{category}{glossary cmd}{label cmd}{body}#*
\glsforeachincategory[glossaries]{category}{glossary cmd}{label cmd}{body}#*
\glsforeachwithattribute{attribute}{value}{glossary cmd}{label cmd}{body}#*
\glsforeachwithattribute[glossaries]{attribute}{value}{glossary cmd}{label cmd}{body}#*
\glsxtrsetcategory{entry list}{category list}#*
\glsxtrsetcategoryforall{glossaries}{category}#*
\glsxtrfieldtitlecase{label}{field}#*

### 8 Counting References ###
## 8.1 Entry Counting (First Use Flag) ##
\cGLS{label}#*r
\cGLS[options%keyvals]{label}#*r
\cGLS{label}[insert]#*r
\cGLS[options%keyvals]{label}[insert]#*r
\cGLSpl{label}#*r
\cGLSpl[options%keyvals]{label}#*r
\cGLSpl{label}[insert]#*r
\cGLSpl[options%keyvals]{label}[insert]#*r
\cGLSformat{label}{insert}#*r
\cGLSplformat{label}{insert}#*r
\glsxtrifcounttrigger{label}{trigger code}{normal code}#*
\GlsXtrEnableEntryCounting{categories}{value}#*
\GlsXtrEnableEntryUnitCounting{categories}{value}{counter}#*
\glsentryprevtotalcount{label}#*r
\glsentryprevmaxcount{label}#*r
\glsenableentryunitcount#*

## 8.2 Link Counting ##
\GlsXtrEnableLinkCounting{categories}#*
\GlsXtrEnableLinkCounting[master counter]{categories}#*
\glsxtrinclinkcounter{counter}#*
\GlsXtrLinkCounterValue{label}#*r
\GlsXtrTheLinkCounter{counter}#*
\GlsXtrIfLinkCounterDef{label}{true}{false}#*r
\GlsXtrLinkCounterName{label}#*r

### 9 Auto-Indexing ###
\glsxtrdoautoindexname{label}{attribute}#*r
\glsxtrautoindexentry{label}#*r
\glsxtrautoindexassignsort{cmd}{label}#*r
\glsxtrautoindexesc#*
\glsxtrautoindex{text}#*
\GlsXtrEnableIndexFormatOverride#*
\GlsXtrSetActualChar{char}#*
\GlsXtrSetLevelChar{char}#*
\GlsXtrSetEscChar{char}#*
\GlsXtrSetEncapChar{char}#*

### 10 bib2gls: Managing Reference Databases ###
\glsxtrresourcefile{file}
\glsxtrresourcefile[options]{file}
\GlsXtrLoadResources
\GlsXtrLoadResources[options]
\glsxtrresourcecount

## 10.3 The glossaries-extra-bib2gls package ##
# see glossaries-extra-bib2gls.cwl

## 10.4 Supplementary Commands ##
\glsxtrresourceinit#*
\GlsXtrDefaultResourceOptions#*
\glsxtrnewgls{prefix}{cmd}#*d
\glsxtrnewgls[default options]{prefix}{cmd}#*d
\glsxtrnewglslike{prefix}{gls cmd%cmd}{glspl cmd%cmd}{Gls cmd%cmd}{Glspl cmd%cmd}#*d
\glsxtrnewglslike[default options]{prefix}{gls cmd%cmd}{glspl cmd%cmd}{Gls cmd%cmd}{Glspl cmd%cmd}#*d
\glsxtrnewGLSlike{prefix}{GLS cmd%cmd}{GLSpl cmd%cmd}#*d
\glsxtrnewGLSlike[default options]{prefix}{GLS cmd%cmd}{GLSpl cmd%cmd}#*d
\glsxtrnewrgls{prefix}{cmd}#*d
\glsxtrnewrgls[default options]{prefix}{cmd}#*d
\glsxtrnewrglslike{prefix}{rgls cmd%cmd}{rglspl cmd%cmd}{rGls cmd%cmd}{rGlspl cmd%cmd}#*d
\glsxtrnewrglslike[default options]{prefix}{rgls cmd%cmd}{rglspl cmd%cmd}{rGls cmd%cmd}{rGlspl cmd%cmd}#*d
\glsxtrnewrGLSlike{prefix}{rGLS cmd%cmd}{rGLSpl cmd%cmd}#*d
\glsxtrnewrGLSlike[default options]{prefix}{rGLS cmd%cmd}{rGLSpl cmd%cmd}#*d
\glsxtridentifyglslike{prefix}{cmd}#*
\glsxtraddlabelprefix{prefix}#*
\glsxtrprependlabelprefix{prefix}#*
\glsxtrclearlabelprefixes#*
\glsxtrifinlabelprefixlist{prefix}{true}{false}#*
\dgls{label}#*r
\dgls[options%keyvals]{label}#*r
\dgls{label}[insert]#*r
\dgls[options%keyvals]{label}[insert]#*r
\dGls{label}#*r
\dGls[options%keyvals]{label}#*r
\dGls{label}[insert]#*r
\dGls[options%keyvals]{label}[insert]#*r
\dGLS{label}#*r
\dGLS[options%keyvals]{label}#*r
\dGLS{label}[insert]#*r
\dGLS[options%keyvals]{label}[insert]#*r
\dglspl{label}#*r
\dglspl[options%keyvals]{label}#*r
\dglspl{label}[insert]#*r
\dglspl[options%keyvals]{label}[insert]#*r
\dGlspl{label}#*r
\dGlspl[options%keyvals]{label}#*r
\dGlspl{label}[insert]#*r
\dGlspl[options%keyvals]{label}[insert]#*r
\dGLSpl{label}#*r
\dGLSpl[options%keyvals]{label}#*r
\dGLSpl{label}[insert]#*r
\dGLSpl[options%keyvals]{label}[insert]#*r
\dglslink{label}#*r
\dglslink[options%keyvals]{label}#*r
\dglslink{label}[insert]#*r
\dglslink[options%keyvals]{label}[insert]#*r
\dglsdisp{label}#*r
\dglsdisp[options%keyvals]{label}#*r
\dglsdisp{label}[insert]#*r
\dglsdisp[options%keyvals]{label}[insert]#*r

## 10.5 Record Counting ##
\glsxtrdetoklocation{location}#*
\GlsXtrTotalRecordCount{label}#*r
\GlsXtrRecordCount{label}{counter}#*r
\GlsXtrLocationRecordCount{label}{counter}{location}#*r
\rgls{label}#*r
\rgls[options%keyvals]{label}#*r
\rgls{label}[insert]#*r
\rgls[options%keyvals]{label}[insert]#*r
\rGls{label}#*r
\rGls[options%keyvals]{label}#*r
\rGls{label}[insert]#*r
\rGls[options%keyvals]{label}[insert]#*r
\rGLS{label}#*r
\rGLS[options%keyvals]{label}#*r
\rGLS{label}[insert]#*r
\rGLS[options%keyvals]{label}[insert]#*r
\rglspl{label}#*r
\rglspl[options%keyvals]{label}#*r
\rglspl{label}[insert]#*r
\rglspl[options%keyvals]{label}[insert]#*r
\rGlspl{label}#*r
\rGlspl[options%keyvals]{label}#*r
\rGlspl{label}[insert]#*r
\rGlspl[options%keyvals]{label}[insert]#*r
\rGLSpl{label}#*r
\rGLSpl[options%keyvals]{label}#*r
\rGLSpl{label}[insert]#*r
\rGLSpl[options%keyvals]{label}[insert]#*r
\GlsXtrSetRecordCountAttribute{category list}{n}#*
\glsxtrifrecordtrigger{label}{trigger code}{normal}#*r
\glsxtrrecordtriggervalue{label}#*r
\rglsformat{label}{insert}#*r
\rglsplformat{label}{insert}#*r
\rGlsformat{label}{insert}#*r
\rGlsplformat{label}{insert}#*r
\rGLSformat{label}{insert}#*r
\rGLSplformat{label}{insert}#*r
\glsxtrenablerecordcount#*

### 11 Miscellaneous New Commands ###
\glsxtrpageref{label}#r
\glsxtrcopytoglossary{entry-label}{glossary-type}
\apptoglossarypreamble{code}#*
\apptoglossarypreamble[type]{code}#*
\preglossarypreamble{code}#*
\preglossarypreamble[type]{code}#*

## 11.1 Entry Fields ##
\GlsXtrFmtField#*r
\glsxtrfmt{label}{text}#*r
\glsxtrfmt[options%keyvals]{label}{text}#*r
\glsxtrfmt*{label}{text}#*r
\glsxtrfmt*{label}{text}[insert]#*r
\glsxtrfmt*[options%keyvals]{label}{text}#*r
\glsxtrfmt*[options%keyvals]{label}{text}[insert]#*r
\GlsXtrFmtDefaultOptions#*
\glsxtrfmtdisplay{csname}{text}{insert}#*
\glsxtrentryfmt{label}{text}#*r
\glsxtrpdfentryfmt{label}{text}#*r
\glsxtrprovidestoragekey{key%plain}{default}{cmd}#*d
\glsxtrifemptyglossary{type}{true}{false}#*
\glsxtrifkeydefined{key%plain}{true}{false}#*
\GlsXtrSetField{label}{field}{value}#*r
\GlstrLetField{label}{field}{value}#*r
\glsxtrsetfieldifexists{label}{field}{code}#*
\glsxtrdeffield{label}{field}{replacement text}#*r
\glsxtredeffield{label}{field}{replacement text}#*r
\glsxtrapptocsvfield{label}{field}{value}#*r
\gGlsXtrSetField{label}{field}{value}#*r
\eGlsXtrSetField{label}{field}{value}#*r
\xGlsXtrSetField{label}{field}{value}#*r
\GlsXtrLetField{label}{field}{cmd}#*d
\csGlsXtrLetField{label}{field}{csname}#*r
\GlsXtrLetFieldToField{label1%ref}{field1}{label2%ref}{field2}#*r
\glsxtrifhasfield{field}{label}{true}{false}#*r
\glsxtrifhasfield*{field}{label}{true}{false}#*r
\GlsXtrIfFieldUndef{field}{label}{true}{false}#*r
\GlsXtrIfFieldEqStr{field}{label}{text}{true}{false}#*r
\GlsXtrIfFieldEqXpStr{field}{label}{text}{true}{false}#*r
\GlsXtrIfXpFieldEqXpStr{field}{label}{text}{true}{false}#*r
\GlsXtrIfFieldValueInCsvList{label}{field}{list}{true}{false}#*r
\GlsXtrIfValueInFieldCsvList{label}{field}{value}{true}{false}#*r
\xGlsXtrIfValueInFieldCsvList{label}{field}{value}{true}{false}#*r
\GlsXtrIfFieldNonZero{field}{label}{true}{false}#*r
\GlsXtrIfFieldEqNum{field}{label}{integer}{true}{false}#*r
\GlsXtrIfFieldCmpNum{field}{label}{comparison}{integer}{true}{false}#*r
\glsxtrusefield{entry}{field}#*
\Glsxtrusefield{entry}{field}#*
\GLSxtrusefield{entry}{field}#*
\glsxtrfieldlistadd{label}{field}{item}#*r
\glsxtrfieldlistgadd{label}{field}{item}#*r
\glsxtrfieldlisteadd{label}{field}{item}#*r
\glsxtrfieldlistxadd{label}{field}{item}#*r
\glsxtrfielddolistloop{label}{field}#*r
\glsxtrfieldforlistloop{label}{field}{handler}#*r
\glsxtrfieldformatlist{label}{field}#*r
\glsxtrfieldifinlist{label}{field}{item}{true}{false}#*r
\glsxtrfieldxifinlist{label}{field}{item}{true}{false}#*r
\glsxtrforcsvfield{label}{field}{handler}#*r
\glsxtrendfor#*
\glsxtrfieldformatcsvlist{label}{field}#*r
\GlsXtrForeignTextField#*
\GlsXtrForeignText{entry}{text}#*
\GlsXtrRecordCounter{counter}#*
\GlsXtrUnknownDialectWarning{locale}{lang}#*

## 11.2 Display All Entries Without Sorting or Indexing ##
\printunsrtglossary
\printunsrtglossary[options%keyvals]
\printunsrtglossary*{code}
\printunsrtglossary*[options%keyvals]{code}
\glsxtrgroupfield#*
\printunsrtglossaries#*
\printunsrtglossaryentryprocesshook{label}#*r
\printunsrtglossaryskipentry#*
\printunsrtglossarypredoglossary#*
\printunsrtglossaryhandler{label}#*r
\glsxtrunsrtdo{label}#*r
\GlsXtrLocationField#*
\glsxtriflabelinlist{label}{label list}{true}{false}#*r
\printunsrtglossaryunit{counter}#*
\printunsrtglossaryunit[options]{counter}#*
\printunsrtglossaryunitsetup{counter}#*

## 11.3 Partial Glossaries ##
\begin{printunsrtglossarywrap}#*
\begin{printunsrtglossarywrap}[options%keyvals]#*
\end{printunsrtglossarywrap}#*
\printunsrtinnerglossary{pre-code}{post-code}#*
\printunsrtinnerglossary[options%keyvals]{pre-code}{post-code}#*
#keyvals:\printunsrtinnerglossary
nonumberlist#true,false
nogroupskip#true,false
nopostdot#true,false
entrycounter#true,false
subentrycounter#true,false
sort=#word,letter,standard,use,def,nocase,case
target#true,false
targetnameprefix=%<prefix%>
prefix=%<prefix%>
groups#true,false
leveloffset=%<n or ++n%>
#endkeyvals

## 11.4 Standalone Entry Items ##
\glsxtrglossentry{label}#r
\GlsXtrStandaloneGlossaryType#*
\GlsXtrStandaloneSubEntryItem{label}#*r
\GlsXtrStandaloneEntryName{label}#*r
\glsxtractivatenopost#*
\glsxtrglossentryother{header}{label}{field}#*r
\GlsXtrStandaloneEntryOther{label}{field}#*r

## 11.5 Entry Aliases ##
\glsxtrsetaliasnoindex#*
\glsxtrindexaliased#*
\glsxtralias{label}#*r
\glsxtrifindexing{true}{false}#*

### 12 On-the-Fly Document Definitions ###
\GlsXtrEnableOnTheFly
\glsxtr{label}#l
\glsxtr[gls options%keyvals]{label}#l
\glsxtr[gls options%keyvals][dfn options]{label}#l
\GlsXtrWarning{defn options}{label}#*
\glsxtrpl{label}#l
\glsxtrpl[gls options%keyvals]{label}#l
\glsxtrpl[gls options%keyvals][dfn options]{label}#l
\Glsxtr{label}#l
\Glsxtr[gls options%keyvals]{label}#l
\Glsxtr[gls options%keyvals][dfn options]{label}#l
\Glsxtrpl{label}#l
\Glsxtrpl[gls options%keyvals]{label}#l
\Glsxtrpl[gls options%keyvals][dfn options]{label}#l
\glsxtrcat#*

### 13 Supplemental Packages ###
## 13.2 Accessibility Support ##
\glsaccessname{label}#*r
\Glsaccessname{label}#*r
\GLSaccessname{label}#*r
\glsaccesstext{label}#*r
\Glsaccesstext{label}#*r
\GLSaccesstext{label}#*r
\GLSaccessplural{label}#*r
\glsaccessplural{label}#*r
\Glsaccessplural{label}#*r
\glsaccessfirst{label}#*r
\Glsaccessfirst{label}#*r
\GLSaccessfirst{label}#*r
\glsaccessfirstplural{label}#*r
\Glsaccessfirstplural{label}#*r
\GLSaccessfirstplural{label}#*r
\glsaccesssymbol{label}#*r
\Glsaccesssymbol{label}#*r
\GLSaccesssymbol{label}#*r
\glsaccesssymbolplural{label}#*r
\Glsaccesssymbolplural{label}#*r
\GLSaccesssymbolplural{label}#*r
\glsaccessdesc{label}#*r
\Glsaccessdesc{label}#*r
\GLSaccessdesc{label}#*r
\glsaccessdescplural{label}#*r
\Glsaccessdescplural{label}#*r
\GLSaccessdescplural{label#*r
\glsaccessshort{label}#*r
\Glsaccessshort{label}#*r
\glsaccessshortpl{label}#*r
\Glsaccessshortpl{label}#*r
\glsaccesslong{label}#*r
\Glsaccesslong{label}#*r
\glsaccesslongpl{label}#*r
\Glsaccesslongpl{label}#*r

### 15 Multi-Lingual Support ###
\GlsXtrNoGlsWarningHead{label}{file}#*r
\GlsXtrNoGlsWarningEmptyStart#*
\GlsXtrNoGlsWarningEmptyMain#*
\GlsXtrNoGlsWarningEmptyNotMain{label}#*r
\GlsXtrNoGlsWarningCheckFile{file}#*
\GlsXtrNoGlsWarningMisMatch#*
\GlsXtrNoGlsWarningNoOut{file}#*
\GlsXtrNoGlsWarningTail#*
\GlsXtrNoGlsWarningBuildInfo#*
\GlsXtrNoGlsWarningAutoMake{label}#*r
\GlsXtrRecordWarning{type}#*

#keyvals:\glsxtrfmt#c,\glsxtrfmt*#c,\cGLS#c,\cGLSpl#c,\dgls#c,\dGls#c,\dGLS#c,\dglspl#c,\dGlspl#c,\dGLSpl#c,\dglslink#c,\dglsdisp#c,\rgls#c,\rGls#c,\rGLS#c,\rglspl#c,\rGlspl#c,\rGLSpl#c,\glsxtr#c,\glsxtrpl#c,\Glsxtr#c,\Glsxtrpl#c
hyper#true,false
format=%<csname%>
counter=%<counter%>
local#true,false
noindex#true,false
wrgloss=#before,after
hyperoutside#true,false
textformat=%<csname%>
prefix=%<prefix%>
thevalue=%<location%>
theHvalue=%<<prefix><location>%>
#endkeyvals

\GlossariesExtraWarning{warning%text}#*
\GlossariesExtraWarningNoLine{warning%text}#*
\glsxtrprovideaccsuppcmd{category}{field}#*
\glsxtrAccSuppAbbrSetFirstLongAttrs{category}#*
\glsxtrAccSuppAbbrSetNameLongAttrs{category}#*
\glsxtrAccSuppAbbrSetNameShortAttrs{category}#*
\glsxtrAccSuppAbbrSetNoLongAttrs{category}#*
\glsxtrAccSuppAbbrSetTextShortAttrs{category}#*
\GlsXtrDefineAbbreviationShortcuts#*
\GlsXtrDefineAcShortcuts#*
\GlsXtrDefineAbbreviationShortcuts#*
\GlsXtrDefineOtherShortcuts#*
\Glsxtrheadfirst{label}#*r
\glsxtrheadfirst{label}#*r
\Glsxtrheadfirstplural{label}#*r
\glsxtrheadfirstplural{label}#*r
\Glsxtrheadfull{label}#*r
\glsxtrheadfull{label}#*r
\Glsxtrheadfullpl{label}#*r
\glsxtrheadfullpl{label}#*r
\Glsxtrheadlong{label}#*r
\glsxtrheadlong{label}#*r
\Glsxtrheadlongpl{label}#*r
\glsxtrheadlongpl{label}#*r
\Glsxtrheadname{label}#*r
\glsxtrheadname{label}#*r
\Glsxtrheadplural{label}#*r
\glsxtrheadplural{label}#*r
\Glsxtrheadshort{label}#*r
\glsxtrheadshort{label}#*r
\Glsxtrheadshortpl{label}#*r
\glsxtrheadshortpl{label}#*r
\Glsxtrheadtext{label}#*r
\glsxtrheadtext{label}#*r
\GLSxtrtitlefirst{label}#*r
\Glsxtrtitlefirst{label}#*r
\glsxtrtitlefirst{label}#*r
\GLSxtrtitlefirstplural{label}#*r
\Glsxtrtitlefirstplural{label}#*r
\glsxtrtitlefirstplural{label}#*r
\GLSxtrtitlefull{label}#*r
\Glsxtrtitlefull{label}#*r
\glsxtrtitlefull{label}#*r
\GLSxtrtitlefullpl{label}#*r
\Glsxtrtitlefullpl{label}#*r
\glsxtrtitlefullpl{label}#*r
\GLSxtrtitlelong{label}#*r
\Glsxtrtitlelong{label}#*r
\glsxtrtitlelong{label}#*r
\GLSxtrtitlelongpl{label}#*r
\Glsxtrtitlelongpl{label}#*r
\glsxtrtitlelongpl{label}#*r
\GLSxtrtitlename{label}#*r
\Glsxtrtitlename{label}#*r
\glsxtrtitlename{label}#*r
\glsxtrtitleorpdforheading{label}#*r
\GLSxtrtitleplural{label}#*r
\Glsxtrtitleplural{label}#*r
\glsxtrtitleplural{label}#*r
\Glsxtrtitleshort{label}#*r
\glsxtrtitleshort{label}#*r
\Glsxtrtitleshortpl{label}#*r
\glsxtrtitleshortpl{label}#*r
\GLSxtrtitletext{label}#*r
\Glsxtrtitletext{label}#*r
\glsxtrtitletext{label}#*r
\ifglsxtrinitwrglossbefore#*
\glsxtrinitwrglossbeforefalse#*
\glsxtrinitwrglossbeforetrue#*
\glsxtrifinmark#*
\glsxtrmarkhook#*
\glsxtrrestoremarkhook#*
\glsxtrmglswrite{arg}#*
\glsxtrNoGlossaryWarning#*
\glsxtrsetupfulldefs#*

\glsdoshowtarget#S
\glslinkwrcontent#S
\glsxtrcounterprefix#S
\glsxtrcurrentgrptitle#S
\glsxtrdiscardperiod#S
\glsxtrifperiod#S
\glsxtrdohyperlink#S
\glsxtrdopostpunc#S
\glsxtrhyperlink#S
\glsxtrprotectlinks#S
\glsxtrscfont#S
\glsxtrsmfont#S
\glsxtrsupplocationurl#S
\glsxtrundefaction#S
\glsxtrundeftag#S
\mglscurrentmainlist#S
\mglscurrentmainoptions#S
\RequireGlossariesExtraLang#S
\ProvidesGlossariesExtraLang#S
\thewrglossary#S
