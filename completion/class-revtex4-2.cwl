# revtex4-2 class
# Matthew Bertucci 2022/05/06 for v4.2e

#include:textcase
#include:url
#include:natbib
#include:revsymb4-2

#keyvals:\documentclass/revtex4-2#c
checkin
preprint
reprint
showpacs
noshowpacs
showkeys
noshowkeys
balancelastpage
nobalancelastpage
nopreprintnumbers
preprintnumbers
10pt
11pt
12pt
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
bibnotes
nobibnotes
footinbib
nofootinbib
altaffilletter
altaffilsymbol
superbib
citeautoscript
longbibliography
nolongbibliography
eprint
noeprint
twoside
oneside
onecolumn
twocolumn
author
numerical
galley
raggedbottom
flushbottom
tightenlines
lengthcheck
draft
final
eqsecnum
secnumarabic
fleqn
floats
endfloats
endfloats
titlepage
notitlepage
osa
osameet
opex
tops
josa
amsfonts
amssymb
noamssymb
amsmath
noamsmath
byrevtex
floatfix
nofloatfix
ltxgridinfo
outputdebug
raggedfooter
noraggedfooter
frontmatterverbose
linenumbers
nomerge
hypertext
frontmatterverbose
inactive
groupedaddress
unsortedaddress
runinaddress
superscriptaddress
# societies; loads aps by default
aapm
aip
aps
aps10pt
aps11pt
aps12pt
apsrmp
sor
# journals; loads pra by default
pra
prb
prc
prd
pre
prl
prab
prper
rmp
prx
prapplied
prmaterials
prfluids
physrev
#endkeyvals

#ifOption:amsfonts
#include:amsfonts
#endif

#ifOption:amssymb
#include:amssymb
#endif

#ifOption:amsmath
#include:amsmath
#endif

#ifOption:linenumbers
#include:lineno
#endif

\absbox#*
\accepted[optional text%text]{date}
\accepted{date}
\acknowledgmentsname#*
\addstuff{penalty}{glue}#*
\affiliation{affiliation%text}
\altaffiliation[optional text%text]{affiliation%text}
\altaffiliation{affiliation%text}
\andname#*
\appdef{command}{code}#*d
\appendixesname#*
\blankaffiliation#*
\botrule#t
\checkindate#*
\collaboration{collaboration%text}
\colrule#t
\copyrightname#*
\doauthor{arg1}{arg2}{arg3}#*
\doi{DOI}
\doibase#*
\eid{eid}#*
\email[optional text%text]{email address%URL}#U
\email{email address%URL}#U
\endpage{endpage}
\eprint{text}#*
\eqncolsep#*
\figuresname#*
\firstname{firstname}#*
\flushing
\footsofar#*
\frstrut#*
\fullinterlineskip#*
\gappdef{command}{code}#*d
\homepage[optional text%text]{URL}#U
\homepage{URL}#U
\href{URL}{text%plain}#U
\intertabularlinepenalty#*
\issuenumber{number}
\journalname#*
\keywords{word1; word2; ...%text}
\linefoot{label}#*
\lineloop{number}#*
\listofvideos
\lofname#*
\loopuntil{arg}#*
\loopwhile{arg}#*
\lotname#*
\lovname#*
\lrstrut#*
\mit#*
\noaffiliation
\numbername#*
\oneapage#*
\onecolumngrid#*
\onlinecite[postfix]{keylist}
\onlinecite{keylist}#c
\other#*
\pacs{PACS codes}#*
\pagesofar#*
\phantomsection#*
\ppname#*
\prepdef{command}{code}#*d
\preprint{text%plain}
\printfigures
\printindex
\printtables
\printvideos
\published[optional text%text]{date}
\published{date}
\received[optional text%text]{date}
\received{date}
\removephantombox#*
\removestuff#*
\replacestuff{penalty}{glue}#*
\restorecolumngrid#*
\revised[optional text%text]{date}
\revised{date}
\say{cmd}#*
\saythe{count}#*
\setfloatlink{URL}#U
\squeezetable
\startpage{startpage}
\surname{surname}
\tableftsep#*
\tablesname#*
\tabmidsep#*
\tabrightsep#*
\text{text}
\textcite[postfix]{keylist}
\textcite{keylist}#c
\theaffil#*
\thecollab#*
\theHvideo#*
\thelinecount#*
\thepagegrid#*
\thevideo#*
\title[short title%text]{text}
\tocname#*
\toprule#t
\traceoutput#*
\tracingplain#*
\triggerpar#*
\twocolumngrid#*
\volumename#*
\volumenumber{number}
\volumeyear{year}

\begin{acknowledgments}
\end{acknowledgments}
\begin{acknowledgements}#*
\end{acknowledgements}#*
\begin{ruledtabular}
\end{ruledtabular}
\begin{turnpage}
\end{turnpage}
\begin{video}
\begin{video}[placement]
\end{video}
\begin{video*}
\begin{video*}[placement]
\end{video*}
\begin{widetext}
\end{widetext}

# only available if longtable loaded
\begin{longtable*}{preamble}#S\tabular
\end{longtable*}#S
\endfirstfoot#S/longtable,longtable*
\endlastfoot#S/longtable,longtable*
\endfirsthead#S/longtable,longtable*
\endfoot#S/longtable,longtable*
\endhead#S/longtable,longtable*

## Societies
# aps (default)
\adv#*
\ao#*
\ap#*
\apl#*
\apm#*
\apj#*
\bell#*
\bmf#*
\cha#*
\jqe#*
\assp#*
\aprop#*
\mtt#*
\iovs#*
\jcp#*
\jap#*
\jmp#*
\jmo#*
\josa#*
\josaa#*
\josab#*
\jpp#*
\jpr#*
\ltp#*
\nat#*
\oc#*
\ol#*
\pl#*
\pop#*
\pof#*
\pra#*
\prb#*
\prc#*
\prd#*
\pre#*
\prl#*
\rmp#*
\rsi#*
\rse#*
\pspie#*
\sjqe#*
\vr#*
\sd#*
\jor#*
\cp#*
\byrevtex#*

# aapm
#ifOption:aapm
#keyvals:\documentclass/revtex4-2#c
mph
#endkeyvals
\aapmreprint#*
\aapmpreprint#*
#endif

# aip
#ifOption:aip
#keyvals:\documentclass/revtex4-2#c
jcp
pop
rsi
jap
apl
apm
cha
pof
bmf
rse
jmp
adv
sd
jor
cp
author-numerical
article-title
#endkeyvals
\aipreprint#*
\aippreprint#*
#endif

# sor
#ifOption:sor
#keyvals:\documentclass/revtex4-2#c
jor
author-numerical
article-title
#endkeyvals
#endif

# deprecated
\address{text}#S
\altaddress{text}#S
\begin{quasitable}#S
\end{quasitable}#S
\case{arg1}{arg2}#Sm
\draft#S
\slantfrac{arg1}{arg2}#Sm
\tablenote{text}#S
\tablenotemark#S
\tablenotetext{text}#S
