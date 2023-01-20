# ksjosaref package
# ponte-vecchio 2023-01-17 for v0.3

#include:amsmath
#include:refcount

#keyvals:\usepackage/ksjosaref#c
refcmd
#endkeyvals

\josaref{label}#r
\josaref[type]{label}#r
\josaref[type][delim%keyvals]{label}#r

#keyvals:\josaref#c
paren
bracket
left=%<delim%>
right=%<delim%>
#endkeyvals

#ifOption:refcmd
\ref[type]{label}#r
\ref[type][delim]{label}#r
#endif

\josarefcmds
\nojosarefcmds

# deprecated
\josapageref{label}#Sr
\josaeqref{label}#Sr
