# acro package (commands taken from the acro manual of V1.4C)
# The acro package was created by Clemens Niederberger
# This file was created by Bjoern Menke (2014-01-08). It contains most of the current commands of the acro package.
# updated by Matthew Bertucci, 2022-04-18 for v3.8

#include:l3keys2e
#include:translations
#include:etoolbox

#keyvals:\usepackage/acro#c
upgrade#true,false
#endkeyvals

\DeclareAcronym{id}{properties%keyvals}
\NewAcroPreset{set name}{properties%keyvals}
\RenewAcroPreset{set name}{properties%keyvals}
\DeclareAcroPreset{set name}{properties%keyvals}

\ac{id}
\ac[options%keyvals]{id}
\ac*{id}
\ac*[options%keyvals]{id}
\Ac{id}
\Ac[options%keyvals]{id}
\Ac*{id}
\Ac*[options%keyvals]{id}
\acp{id}
\acp[options%keyvals]{id}
\acp*{id}
\acp*[options%keyvals]{id}
\Acp{id}
\Acp[options%keyvals]{id}
\Acp*{id}
\Acp*[options%keyvals]{id}
\iac{id}
\iac[options%keyvals]{id}
\iac*{id}
\iac*[options%keyvals]{id}
\Iac{id}
\Iac[options%keyvals]{id}
\Iac*{id}
\Iac*[options%keyvals]{id}
\acs{id}
\acs[options%keyvals]{id}
\acs*{id}
\acs*[options%keyvals]{id}
\Acs{id}
\Acs[options%keyvals]{id}
\Acs*{id}
\Acs*[options%keyvals]{id}
\acsp{id}
\acsp[options%keyvals]{id}
\acsp*{id}
\acsp*[options%keyvals]{id}
\Acsp{id}
\Acsp[options%keyvals]{id}
\Acsp*{id}
\Acsp*[options%keyvals]{id}
\iacs{id}
\iacs[options%keyvals]{id}
\iacs*{id}
\iacs*[options%keyvals]{id}
\Iacs{id}
\Iacs[options%keyvals]{id}
\Iacs*{id}
\Iacs*[options%keyvals]{id}
\acl{id}
\acl[options%keyvals]{id}
\acl*{id}
\acl*[options%keyvals]{id}
\Acl{id}
\Acl[options%keyvals]{id}
\Acl*{id}
\Acl*[options%keyvals]{id}
\aclp{id}
\aclp[options%keyvals]{id}
\aclp*{id}
\aclp*[options%keyvals]{id}
\Aclp{id}
\Aclp[options%keyvals]{id}
\Aclp*{id}
\Aclp*[options%keyvals]{id}
\iacl{id}
\iacl[options%keyvals]{id}
\iacl*{id}
\iacl*[options%keyvals]{id}
\Iacl{id}
\Iacl[options%keyvals]{id}
\Iacl*{id}
\Iacl*[options%keyvals]{id}
\aca{id}
\aca[options%keyvals]{id}
\aca*{id}
\aca*[options%keyvals]{id}
\Aca{id}
\Aca[options%keyvals]{id}
\Aca*{id}
\Aca*[options%keyvals]{id}
\acap{id}
\acap[options%keyvals]{id}
\acap*{id}
\acap*[options%keyvals]{id}
\Acap{id}
\Acap[options%keyvals]{id}
\Acap*{id}
\Acap*[options%keyvals]{id}
\iaca{id}
\iaca[options%keyvals]{id}
\iaca*{id}
\iaca*[options%keyvals]{id}
\Iaca{id}
\Iaca[options%keyvals]{id}
\Iaca*{id}
\Iaca*[options%keyvals]{id}
\acf{id}
\acf[options%keyvals]{id}
\acf*{id}
\acf*[options%keyvals]{id}
\Acf{id}
\Acf[options%keyvals]{id}
\Acf*{id}
\Acf*[options%keyvals]{id}
\acfp{id}
\acfp[options%keyvals]{id}
\acfp*{id}
\acfp*[options%keyvals]{id}
\Acfp{id}
\Acfp[options%keyvals]{id}
\Acfp*{id}
\Acfp*[options%keyvals]{id}
\iacf{id}
\iacf[options%keyvals]{id}
\iacf*{id}
\iacf*[options%keyvals]{id}
\Iacf{id}
\Iacf[options%keyvals]{id}
\Iacf*{id}
\Iacf*[options%keyvals]{id}

#keyvals:\DeclareAcronym#c,\NewAcroPreset#c,\RenewAcroPreset#c,\DeclareAcroPreset#c
short={%<text%>}
long={%<text%>}
alt={%<text%>}
extra={%<text%>}
foreign={%<text%>}
long-post={%<text%>}
post={%<text%>}
sort={%<text%>}
tag={%<csv list%>}
before-citation={%<csv list%>}
index-sort={%<text%>}
short-plural={%<text%>}
short-plural-form={%<text%>}
long-plural={%<text%>}
long-plural-form={%<text%>}
alt-plural={%<text%>}
alt-plural-form={%<text%>}
foreign-plural={%<text%>}
foreign-plural-form={%<text%>}
plural={%<text%>}
plural-form={%<text%>}
short-indefinite={%<text%>}
long-indefinite={%<text%>}
alt-indefinite={%<text%>}
pdfstring=%<string%>
pdfcomment={%<text%>}
short-acc={%<text%>}
long-acc={%<text%>}
alt-acc={%<text%>}
foreign-acc={%<text%>}
foreign-acc-plural-form={%<text%>}
extra-acc={%<text%>}
single-acc={%<text%>}
list-acc={%<text%>}
list={%<text%>}
foreign-babel=%<language%>
foreign-locale=%<language%>
preset=%<set name%>
uselist={%<csv list of ids%>}
#endkeyvals

#keyvals:\DeclareAcronym#c,\NewAcroPreset#c,\RenewAcroPreset#c,\DeclareAcroPreset#c,\ac#c,\ac*#c,\Ac#c,\Ac*#c,\acp#c,\acp*#c,\Acp#c,\Acp*#c,\iac#c,\iac*#c,\Iac#c,\Iac*#c,\acs#c,\acs*#c,\Acs#c,\Acs*#c,\acsp#c,\acsp*#c,\Acsp#c,\Acsp*#c,\iacs#c,\iacs*#c,\Iacs#c,\Iacs*#c,\acl#c,\acl*#c,\Acl#c,\Acl*#c,\aclp#c,\aclp*#c,\Aclp#c,\Aclp*#c,\iacl#c,\iacl*#c,\Iacl#c,\Iacl*#c,\aca#c,\aca*#c,\Aca#c,\Aca*#c,\acap#c,\acap*#c,\Acap#c,\Acap*#c,\iaca#c,\iaca*#c,\Iaca#c,\Iaca*#c,\acf#c,\acf*#c,\Acf#c,\Acf*#c,\acfp#c,\acfp*#c,\Acfp#c,\Acfp*#c,\iacf#c,\iacf*#c,\Iacf#c,\Iacf*#c
case-sensitive#true,false
case-insensitive#true,false
first-style=#long-short,short-long,short,long,footnote
subsequent-style=#long-short,short-long,short,long,footnote
single-style=#long-short,short-long,short,long,footnote
single={%<text%>}
use-id-as-short#true,false
cite=[%<prenote%>][%<postnote%>]{%<citation keys%>}
index={%<text%>}
index-sort={%<text%>}
no-index#true,false
format={%<code%>}
short-format={%<code%>}
long-format={%<code%>}
first-long-format={%<code%>}
alt-format={%<code%>}
extra-format={%<code%>}
foreign-format={%<code%>}
single-format={%<code%>}
list-format={%<code%>}
%acroproperty
#endkeyvals

\printacronyms[options%keyvals]

#keyvals:\printacronyms#c
template=#description,lof,longtable,supertabular,tabularray,tabular,toc,xltabular
sort#true,false
display=#all,used
exclude={%<csv list of tags%>}
include={%<csv list of tags%>}
add#true,false
heading=#none,section,section*,chapter,chapter*
name={%<text%>}
preamble={%<text%>}
locale/display#true,false
local#true,false
pages={%<keyvals%>}
#endkeyvals

\acsetup{options%keyvals}

#keyvals:\acsetup#c
case-sensitive#true,false
case-insensitive#true,false
use-id-as-short#true,false
first-style=#long-short,short-long,short,long,footnote
subsequent-style=#long-short,short-long,short,long,footnote
single#true,false
single-style=#long-short,short-long,short,long,footnote
list/template=#description,tabular,longtable,supertabular,lof,toc
list/sort#true,false
list/display=#all,used
list/exclude={%<csv list of tags%>}
list/include={%<csv list of tags%>}
list/add#true,false
list/heading=#none,section,section*,chapter,chapter*
list/name={%<text%>}
list/preamble={%<text%>}
list/locale/display#true,false
list/local#true,false
list/foreign/display#true,false
pages/display=#first,all,none
pages/seq/use=#true,false
pages/seq/pre={%<code%>}
pages/seq/threshold=%<number%>
pages/fill={%<code%>}
pages/name#true,false
format={%<code%>}
format/short={%<code%>}
format/long={%<code%>}
format/first-long={%<code%>}
format/alt={%<code%>}
format/extra={%<code%>}
format/foreign={%<code%>}
format/list={%<code%>}
format/replace#true,false
short-plural-ending={%<text%>}
long-plural-ending={%<text%>}
foreign/display#true,false
locale/display#true,false
locale/format={%<code%>}
uppercase/first
uppercase/title
uppercase/all
uppercase/none
uppercase/cmd={%<commands%>}
uppercase/short#true,false
cite/cmd={%<citation command%>}
cite/group#true,false
cite/display=#first,all,none
cite/pre={%<text%>}
cite/group/cmd={%<citation command%>}
cite/group/pre={%<text%>}
index/use=#true,false,indexed
index/cmd={%<index command%>}
index/disable={%<code%>}
index/clear
barriers/use#true,false
barriers/reset#true,false
barriers/single#true,false
trailing/define=%<token%>{%<name%>}
trailing/activate={%<list of token names%>}
trailing/deactivate={%<list of token names%>}
make-links#true,false
link-only-first#true,false
pdfcomments/use#true,false
pdfcomments/cmd={%<code%>}
accsupp/use#true,false
accsupp/options={%<accsupp options%>}
accsupp/method={%<method%>}
language=
patch/floats#true,false
patch/list#true,false
patch/tabularx#true,false
patch/ltxtable#true,false
patch/tabu#true,false
patch/caption#true,false
patch/maketitle#true,false
load-style=%<name%>
templates/colspec={%<value%>}
#endkeyvals

\acrodotfill#*
\acbarrier#*
\acdot#*
\acspace#*
\abbrdot#*
\aciftrailing{list of token names}{true}{false}#*

\acuse{list of ids}#*
\acuseall#*
\acreset{list of ids}#*
\acresetall#*
\acrotranslate{key%plain}#*
\acswitchoff#*
\acswitchon#*

\NewAcroTemplate{name}{code}#*
\NewAcroTemplate[type]{name}{code}#*
\RenewAcroTemplate{name}{code}#*
\RenewAcroTemplate[type]{name}{code}#*
\SetupAcroTemplate{name}{code}#*
\SetupAcroTemplate[type]{name}{code}#*
\SetupNextAcroTemplate{name}{code}#*
\SetupNextAcroTemplate[type]{name}{code}#*
\AcroTemplateType#*
\AcroTemplateName#*
\acrolistname#*
\acrowrite{property}#*
\acroformat{type}{text}#*
\acroshow{property}#*
\acroifTF{property}{true}{false}#*
\acroifT{property}{true}{false}#*
\acroifF{property}{true}{false}#*
\acroifbooleanTF{property}{true}{false}#*
\acroifbooleanT{property}{true}{false}#*
\acroifbooleanF{property}{true}{false}#*
\acroifallTF{properties}{true}{false}#*
\acroifallT{properties}{true}{false}#*
\acroifallF{properties}{true}{false}#*
\acroifanyTF{properties}{true}{false}#*
\acroifanyT{properties}{true}{false}#*
\acroifanyF{properties}{true}{false}#*
\acroiftagTF{tag}{true}{false}#*
\acroiftagT{tag}{true}{false}#*
\acroiftagF{tag}{true}{false}#*
\acroifstarredTF{true}{false}#*
\acroifstarredT{true}{false}#*
\acroifstarredF{true}{false}#*
\AcroPropertiesMap{code}#*
\AcroAcronymsMap{code}#*
\AcronymID#*
\AcroMapBreak#*
\AcroPropertiesSet{id}{list of properties}#*
\acroifusedTF{true}{false}#*
\acroifusedT{true}{false}#*
\acroifusedF{true}{false}#*
\acroiffirstTF{true}{false}#*
\acroiffirstT{true}{false}#*
\acroiffirstF{true}{false}#*
\acroifsingleTF{true}{false}#*
\acroifsingleT{true}{false}#*
\acroifsingleF{true}{false}#*
\acrogroupcite#*
\acroifchapterTF{true}{false}#*
\acroifchapterT{true}{false}#*
\acroifchapterF{true}{false}#*
\acroifpagesTF{true}{false}#*
\acroifpagesT{true}{false}#*
\acroifpagesF{true}{false}#*
\acropages{first}{range}#*
\acronopagerange#*
\acroneedpages#*
\acropagefill#*
\acronymsmap{code}#*
\acronymsmapTF{code}{true}{false}#*
\acronymsmapT{code}{true}{false}#*
\acronymsmapF{code}{true}{false}#*
\AcronymTable#*
\AcroAddRow{code}#*
\AcroNeedPackage{package}#*
\AcroRerun#*
\DeclareAcroEnding{name}{short default}{long default}#*
\DeclareAcroArticle{name}{default}#*
\DeclareAcroTranslation{key%plain}{language-translation list}#*
\AddAcroTranslations{key%plain}{language-translation list}#*
\DeclareAcroProperty{name%specialDef}#*s#%acroproperty
\DeclareAcroProperty*{name%specialDef}#*s#%acroproperty
\DeclareAcroPropertyAlias{name1%specialDef}{name2}#*s#%acroproperty
\MakeAcroPropertyAlias{name1}{name2}#*
\NewAcroCommand{cmd}{xargs}{definition}#*d
\RenewAcroCommand{cmd}{xargs}{definition}#*
\DeclareAcroCommand{cmd}{xargs}{definition}#*d
\ProvideAcroCommand{cmd}{xargs}{definition}#*d
\UseAcroTemplate{name}#*
\UseAcroTemplate[type]{name}[argument number]#*
\acrocite#*
\acrodonotuse#*
\acroplural#*
\acroindefinite#*
\acroupper#*
\acrofull#*

# not documented
\nospace#*
\AcroModule{name}{description%text}#*
\AcroModuleEnd#*
\AcroStyle{name}#*
\AcroMap{arg1}{arg2}#*
\acroloadstyle{style}#*
\acsimple{arg1}{arg2}#*
\acfootnote{arg}#*
\acgobbletrail#*
\acroheading#*
\acropreamble#*
\acropostamble#*
\acrofield{arg1}{arg2}#*
\acroprintfield{arg1}{arg2}#*
\acroiffieldTF{arg1}{arg2}{true}{false}#*
\acroifanyfieldTF{arg1}{arg2}{true}{false}#*
\acroifallfieldsTF{arg1}{arg2}{true}{false}#*
\acroifpagefieldTF{arg}#*
\acroifpropertyTF{arg}#*
\acroifpropertyT{arg}#*
\acroifpropertyF{arg}#*
\acshow{id}#*
\acshow[options]{id}#*
\acroendfootnote#*
