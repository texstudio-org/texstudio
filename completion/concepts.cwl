# concepts package
# Matthew Bertucci 10/6/2021 for v0.0.6

#include:etextools
#include:nth
#include:xspace
#include:ltxkeys
#include:xstring

\NewConcept{concept key}{options%keyvals}

#keyvals:\NewConcept
name=
Name=
plural=
Plural=
namecmd=
symbols={%<list of symbols%>}
symbolcmd=
#endkeyvals

\ConceptOption{concept key}{option%keyvals}

#keyvals:\ConceptOption
name
Name
plural
Plural
namecmd
symbols
symbolcmd
#endkeyvals

\ConceptName{concept key}
\ConceptName^{concept key}
\ConceptName*{concept key}
\ConceptName^*{concept key}

\ConceptSymbol{concept key}
\ConceptSymbol{concept key}[symbol index]

\ConceptSymbols{concept key}{symbol indices}
\ConceptSymbols{concept key}[separator]{symbol indices}
\ConceptSymbols{concept key}[separator][last separator]{symbol indices}

\ConceptNameAndSymbols{concept key}{symbol indices}
\ConceptNameAndSymbols{concept key}[separator]{symbol indices}
\ConceptNameAndSymbols{concept key}[separator][last separator]{symbol indices}