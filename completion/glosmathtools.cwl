# glosmathtools package
# Matthew Bertucci 11/11/2021 for v1.0.0

#include:amsmath
#include:amsfonts
#include:etoolbox
#include:glossaries

#ifOption:qtmarkupright
\qtmark
#endif

\sbu{arg}#*

\newglosentrymath{label}{math sym%formula}{keyvals}#l

#keyvals:\newglosentrymath#c
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
descseclang=
#endkeyvals

#keyvals:\newglossaryentry#c,\longnewglossaryentry#c,\provideglossaryentry#c,\longprovideglossaryentry#c,\newacronym#c,\newterm#c
descseclang=
#endkeyvals

\glscatnamefmt{text}#*

\glsac{label}#r
\glsac[accent-type%keyvals]{label}#r

\glsub{label}{sub-label}#r
\glsub[accent-type%keyvals]{label}{sub-label}#r

\glsubs{label}{sub-label1}{sub-label2}#r
\glsubs[accent type1%keyvals]{label}{sub-label1}{sub-label2}#r
\glsubs[accent type1%keyvals][accent-type2]{label}{sub-label1}{sub-label2}#r

\glsvi{label1%ref}{label2%ref}
\glsvi[accent-type1%keyvals]{label1%ref}{label2%ref}
\glsvi[accent-type1%keyvals][accent-type2]{label1%ref}{label2%ref}

\glsvisub{label1%ref}{label2%ref}
\glsvisub[accent type%keyvals]{label1%ref}{label2%ref}

#keyvals:\glsac#c,\glsub#c,\glsubs#c,\glsvi#c,
dot
ddot
bar
hat
vec
tilde
#endkeyvals

\glslang{label}#r
\glslang[language%keyvals]{label}#r

\setacronymlang{language%keyvals}

\begin{acronymlang}{language%keyvals}
\end{acronymlang}

#keyvals:\glslang#c,\setacronymlang#c,\begin{acronymlang}#c
L1
L2
L1L2
L2L1
#endkeyvals

\glsentrydescsec#*
\Glsentrydescsec#*
\glsdescsec#*
\Glsdescsec#*
\GLSdescsec#*
\glosstyledesc{arg}#*
\glsentrydot#*
\glsentryddot#*
\glsentrybar#*
\glsentryhat#*
\glsentryvec#*
\glsentrytilde#*

#keyvals:\setglossarystyle#c
nomencl
nomencl-L1
nomencl-L2
nomencl-L1L2
nomencl-L2L1
#endkeyvals

## glosmathtools passes options to glossaries package
#ifOption:debug=showtargets
\glsshowtarget{target name}
\glsshowtargetouter{label}
\glsshowtargetfont#*
#endif
#ifOption:debug=showaccsupp
\glsshowaccsupp{options}{tag}{replacement text}
#endif
#ifOption:translate=babel
#include:glossaries-babel
#endif
#ifOption:symbols
\printsymbols
\printsymbols[options%keyvals]
#endif
#ifOption:numbers
\printnumbers
\printnumbers[options%keyvals]
#endif
#ifOption:index
\newterm{term{
\newterm[options%keyvals]{term}
\printindex
\printindex[options%keyvals]
#endif
#ifOption:acronym
\printacronyms
\printacronyms[options%keyvals]
#endif
#ifOption:acronym=true
\printacronyms
\printacronyms[options%keyvals]
#endif
#ifOption:acronyms
\printacronyms
\printacronyms[options%keyvals]
#endif
#ifOption:compatible-2.07
#include:glossaries-compatible-207
#endif
#ifOption:compatible-2.07=true
#include:glossaries-compatible-207
#endif
#ifOption:shortcuts
\acs{label}#r
\acs[options%keyvals]{label}#r
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

\Acs{label}#r
\Acs[options%keyvals]{label}#r
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

\acl{label}#r
\acl[options%keyvals]{label}#r
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

\Acl{label}#r
\Acl[options%keyvals]{label}#r
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

\acf{label}#r
\acf[options%keyvals]{label}#r
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

\Acf{label}#r
\Acf[options%keyvals]{label}#r
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

\ac{label}#r
\ac[options%keyvals]{label}#r
\ac{label}[insert]#*r
\ac[options%keyvals]{label}[insert]#*r
\Ac{label}#r
\Ac[options%keyvals]{label}#r
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

\acp{label}#r
\acp[options%keyvals]{label}#r
\acp{label}[insert]#*r
\acp[options%keyvals]{label}[insert]#*r
\Acp{label}#r
\Acp[options%keyvals]{label}#r
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