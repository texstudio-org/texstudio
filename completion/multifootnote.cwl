# multifootnote package
# Matthew Bertucci 2022/06/02 for release 2022/05/31

#include:l3keys2e

#keyvals:\usepackage/multifootnote#c
left align
left indent
left indent=##L
#endkeyvals

\multifootnotemark[label]#l
\footnotenumber[label]#l
\multifootnotetext[labellist]{text}#r
\multifootnote[labellist]{text}#r

\multifootnotetag{list of tags%specialDef}#s#%multifootnotetag
\footnotetag{list of tags%specialDef}#s#%multifootnotetag
\multifootnotetagtext[tag%keyvals]{text}#r

#keyvals:\multifootnotetagtext#c
%multifootnotetag
#endkeyvals