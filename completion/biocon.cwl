# biocon package
# Matthew Bertucci 2022/10/11 for v0.9

#include:keyval
#include:ifthen

\plantlike{parameters%keyvals}
\plantlike[how]{parameters%keyvals}
\funguslike{parameters%keyvals}
\funguslike[how]{parameters%keyvals}
\animallike{parameters%keyvals}
\animallike[how]{parameters%keyvals}
\bactlike{parameters%keyvals}
\bactlike[how]{parameters%keyvals}

\newplant{identifier}{parameters%keyvals}
\newfungus{identifier}{parameters%keyvals}
\newanimal{identifier}{parameters%keyvals}
\newbact{identifier}{parameters%keyvals}

#keyvals:\plantlike,\funguslike,\animallike,\bactlike,\newplant,\newfungus,\newanimal,\newbact
genus=%<genus%>
oldgenus=%<genus%>
epithet=%<epithet%>
author=%<author%>
oldauthor=%<author%>
year=%<year%>
oldyear=%<year%>
%biocontaxon
#endkeyvals

\plant{identifier}
\plant[how%keyvals]{identifier}
\fungus{identifier}
\fungus[how%keyvals]{identifier}
\animal{identifier}
\animal[how%keyvals]{identifier}
\bact{identifier}
\bact[how%keyvals]{identifier}

\defaultplante{style-name%keyvals}
\defaultfunguse{style-name%keyvals}
\defaultanimale{style-name%keyvals}
\defaultbacte{style-name%keyvals}
\defaultfull{style-name%keyvals}
\defaultabbr{style-name%keyvals}

#keyvals:\plant,\fungus,\animal,\bact,\defaultplante,\defaultfunguse,\defaultanimale,\defaultbacte,\defaultfull,\defaultabbr
e
f
a
g
%biocontaxastyle
#endkeyvals

#keyvals:\defaultplante,\defaultfunguse,\defaultanimale,\defaultbacte,\defaultfull,\defaultabbr
ePlant
eAnimal
#endkeyvals

\newtaxon{name%specialDef}#s#%biocontaxon
\newtaxastyle{name%specialDef}{style}#s#%biocontaxastyle

\taxon{pre!name!post}
\taxonfirst{pre!name!post}
\taxit{text}

\taxitalics#*