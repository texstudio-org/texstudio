# listofsymbols package
# Matthew Bertucci 11/18/2021 for v0.2

#include:ifthen
#include:calc
#include:xspace

#ifOption:nomencl
#include:nomencl
#endif

\opensymdef
\closeymdef
\newsym{name}{output%formula}
\newsym[description]{name}{output%formula}
\newsub{name}{output%formula}
\newsub[description]{name}{output%formula}
\subsep[separator]
\listofsymbols
\symwidth#*
\symindent#*
\sympagenowidth#*
\listofsubscripts
\listofboth
\symheadingname#*
\subheadingname#*
\bothheadingname#*
\markasused{name}
\markasunused{name}
\dontmarkasused{name}
\losstring
\printsymline{sortkey}{symbol}{name}{description}{pageno}#*
\addsymline{sortkey}{symbol}{name}{description}{filehandle}#*
\symheading#*
\subheading#*