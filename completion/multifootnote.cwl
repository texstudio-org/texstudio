# multifootnote package
# Matthew Bertucci 2024/03/25

#include:refcount

#keyvals:\usepackage/multifootnote#c
backref
left align
left indent
left indent=##L
manual
#endkeyvals

#ifOption:backref
#include:hyperref
#endif
#ifOption:backref=true
#include:hyperref
#endif

\multifootnotemark[label]
\footnotenumber[label]
\multifootnotemarkmanual[label]#*
\footnotenumbermanual[label]#*
\multifootnotetext[list of labels]{text}
\multifootnote[list of labels]{text}
\multifootnotetextmanual[list of labels]{text}#*
\multifootnotemanual[list of labels]{text}#*

\multifootnotetag{list of tags%specialDef}#s#%multifootnotetag
\footnotetag{list of tags%specialDef}#s#%multifootnotetag
\multifootnotetagmanual{list of tags%specialDef}#*s#%multifootnotetag
\footnotetagmanual{list of tags%specialDef}#*s#%multifootnotetag
\multifootnotetagtext[tag%keyvals]{text}
\multifootnotetagtextmanual[tag%keyvals]{text}#*

#keyvals:\multifootnotetagtext#c,\multifootnotetagtextmanual#c
%multifootnotetag
#endkeyvals
