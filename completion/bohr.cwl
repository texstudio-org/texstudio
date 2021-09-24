# bohr package
# Matthew Bertucci 9/19/2021 for v1.0

#include:tikz
#include:pgfopts
#include:elements

\bohr{num of electrons}{atom name}
\bohr[num of shells]{num of electrons}{atom name}

\setbohr{options%keyvals}

#keyvals:\setbohr
insert-symbol#true,false
insert-number#true,false
insert-missing#true,false
atom-style={%<code%>}
name-options-set={%<tikz-options%>}
name-options-add={%<tikz-options%>}
nucleus-options-set={%<tikz-options%>}
nucleus-options-add={%<tikz-options%>}
nucleus-radius=##L
electron-options-set={%<tikz-options%>}
electron-options-add={%<tikz-options%>}
electron-radius=##L
shell-options-set={%<tikz-options%>}
shell-options-add={%<tikz-options%>}
shell-dist=##L
distribution-method=#periodic,quantum
#endkeyvals