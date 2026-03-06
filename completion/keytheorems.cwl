# keytheorems package
# Matthew Bertucci 2026/02/20 for v0.3.5

#include:aliascnt
#include:amsthm
#include:refcount
#include:translations
#include:unique

#keyvals:\usepackage/keytheorems#c
overload
thmtools-compat
store-all
#endkeyvals

#ifOption:thmtools-compat
\declaretheorem{envname}#N
\declaretheorem[options%keyvals]{envname}#N
\declaretheoremstyle{style%specialDef}#s#%keytheoremstyle
\declaretheoremstyle[options%keyvals]{style%specialDef}#s#%keytheoremstyle
\begin{restatable}{envname}{tag}
\begin{restatable}[options%keyvals]{envname}{tag}
\end{restatable}
\begin{restatable*}{envname}{tag}
\begin{restatable*}[options%keyvals]{envname}{tag}
\end{restatable*}
#keyvals:\begin{restatable},\begin{restatable*}
note=%<text%>
short-note=%<text%>
label=##l
manual-num=%<text%>
continues=#%label
continues*=#%label
restate-keys={%<keyvals%>}
listhack=#true,false
seq=%<name%>
tcb-append={%<tcolorbox keys%>}
ignore=#true,false
#endkeyvals
\listoftheorems
\listoftheorems[options%keyvals]
\listtheoremname#*
\addtotheorempreheadhook{code}#*
\addtotheorempreheadhook[envname]{code}#*
\addtotheorempostheadhook{code}#*
\addtotheorempostheadhook[envname]{code}#*
\addtotheoremprefoothook{code}#*
\addtotheoremprefoothook[envname]{code}#*
\addtotheorempostfoothook{code}#*
\addtotheorempostfoothook[envname]{code}#*
#keyvals:\newkeytheorem#c,\declaretheorem#c,\newkeytheoremstyle#c,\renewkeytheoremstyle#c,\providekeytheoremstyle#c,\declarekeytheoremstyle#c,\declaretheoremstyle#c
thmbox
thmbox=#L,M,S
shaded
shaded={%<shade options%>}
#endkeyvals
#endif

\keytheoremset{options%keyvals}

#keyvals:\usepackage/keytheorems#c,\keytheoremset#c
overload
thmtools-compat
store-all
restate-counter
qed-symbol=%<symbol%>
auto-translate#true,false
store-sets-label
predefined
predefined={%<options%>}
#endkeyvals

#keyvals:\keytheoremset#c
continues-code=%<code%>
#endkeyvals

\newkeytheorem{envname}#N
\newkeytheorem{envname}[options%keyvals]#N
\renewkeytheorem{envname}
\renewkeytheorem{envname}[options%keyvals]
\providekeytheorem{envname}#N
\providekeytheorem{envname}[options%keyvals]#N
\declarekeytheorem{envname}#N
\declarekeytheorem{envname}[options%keyvals]#N

# keys that can't be used in styles
#keyvals:\newkeytheorem#c,\renewkeytheorem#c,\providekeytheorem#c,\declarekeytheorem#c,\declaretheorem#c
name=%<display name%>
refname=%<ref name%>
Refname=%<ref name%>
plural-refname=%<ref name%>
plural-Refname=%<ref name%>
#endkeyvals

# keys that can be used in styles
#keyvals:\newkeytheorem#c,\renewkeytheorem#c,\providekeytheorem#c,\declarekeytheorem#c,\declaretheorem#c,\newkeytheoremstyle#c,\renewkeytheoremstyle#c,\providekeytheoremstyle#c,\declarekeytheoremstyle#c,\declaretheoremstyle#c
numbered=#true,false,unless-unique
parent=%<counter%>
sibling=%<counter%>
preheadhook=%<code%>
postheadhook=%<code%>
prefoothook=%<code%>
postfoothook=%<code%>
qed
qed=%<symbol%>
tcolorbox
tcolorbox={%<tcolorbox options%>}
tcolorbox-no-titlebar
tcolorbox-no-titlebar={%<tcolorbox options%>}
leftmargin=##L
rightmargin=##L
margin=##L
counter-format=%<code%>
#endkeyvals

\newkeytheoremstyle{style%specialDef}{options%keyvals}#s#%keytheoremstyle
\renewkeytheoremstyle{style}{options%keyvals}
\providekeytheoremstyle{style%specialDef}{options%keyvals}#s#%keytheoremstyle
\declarekeytheoremstyle{style%specialDef}{options%keyvals}#s#%keytheoremstyle

#keyvals:\newkeytheoremstyle#c,\renewkeytheoremstyle#c,\providekeytheoremstyle#c,\declarekeytheoremstyle#c,\declaretheoremstyle#c
spaceabove=##L
spacebelow=##L
bodyfont=%<font commands%>
headindent=##L
headfont=%<font commands%>
headpunct=%<code%>
postheadspace=##L
break
notefont=%<font commands%>
notebraces={%<left brace%>}{%<right brace%>}
headformat=#margin,swapnumber,%<code%>
inherit-style=%<style name%>
noteseparator=%<separator%>
numberfont=%<font commands%>
#endkeyvals

#keyvals:\theoremstyle#c
%keytheoremstyle
#endkeyvals

\NAME#*
\NUMBER#*
\NOTE#*

\getkeytheorem{tag}
\getkeytheorem[property%keyvals]{tag}

#keyvals:\getkeytheorem#c
body
#endkeyvals

\IfRestatingTF{true code}{false code}#*
\IfRestatingT{true code}#*
\IfRestatingF{false code}#*

\externaltheorems{file}
\externaltheorems[prefix]{file}

\listofkeytheorems
\listofkeytheorems[options%keyvals]
\keytheoremlistset{options%keyvals}

#keyvals:\listofkeytheorems#c,\keytheoremlistset#c,\listoftheorems#c
numwidth=##L
indent=##L
ignore={%<env1,env2,...%>}
show={%<env1,env2,...%>}
onlynamed
onlynamed={%<env1,env2,...%>}
ignoreall
showall
title=%<text%>
swapnumber#true,false
onlynumbered
onlynumbered={%<env1,env2,...%>}
seq=%<name%>
title-code=%<code%>
no-title#true,false
note-code=%<code%>
print-body
no-continues#true,false
no-chapter-skip#true,false
chapter-skip-length=##L
no-toc#true,false
format-code=%<code%>
one-col#true,false
#endkeyvals

\addtheoremcontentsline{level}{text}#*
\addtotheoremcontents{code}#*

\addtotheoremhook{hook name}{code}
\addtotheoremhook[envname]{hook name}{code}

\Autoref{label}#r
\Autoref*{label}#r

# expl3 interface
\l_keythms_thmuse_envname_tl#/%expl3
\keythms_getthm_theorem:nnnnn {%<⟨name⟩%>} {%<⟨number⟩%>} {%<⟨restate counters⟩%>} {%<⟨keys⟩%>} {%<⟨body text⟩%>}#/%expl3
\keythms_getthm_body:nnn {%<⟨name⟩%>} {%<⟨restate counters⟩%>} {%<⟨body text⟩%>}#/%expl3
\keythms_listof_listcmd:nnnnnnn {%<⟨name⟩%>} {%<⟨number⟩%>} {%<⟨Href⟩%>} {%<⟨page⟩%>} {%<⟨restate counters⟩%>} {%<⟨keys⟩%>} {%<⟨body text⟩%>}#/%expl3
