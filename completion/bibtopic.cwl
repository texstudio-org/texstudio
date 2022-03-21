# bibtopic package
# Matthew Bertucci 3/21/2022 for v1.1a

#include:ifthen

#keyvals:\usepackage/bibtopic#c
breakcites
defaultbib
dot
normalwarnings
overridenumbers
dontoverridenumbers
printheadings
sectcntreset
slow
unitcntnoreset
verbose
#endkeyvals

\begin{btSect}{bib file}
\begin{btSect}[style]{bib file}
\end{btSect}
\btPrintCited
\btPrintNotCited
\btPrintAll
\begin{btUnit}
\end{btUnit}
\thebtauxfile#*

# not documented
\btBegThbCmd#*
\btCiteSect{key%plain}#*
\btGetVal{key%plain}#*
\btRef{key%plain}{type}#*
\btretval#*