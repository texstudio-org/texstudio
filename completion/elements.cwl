# elements package
# Matthew Bertucci 9/19/2021 for v0.3

#include:translations

\elementname{%<atomic number|element symbol%>}
\setatomname{atomic number}{element name}
\setatomname[alt name]{atomic number}{element name}
\DeclareAtomName{atomic number}{element name}#*
\DeclareAtomName[alt name]{atomic number}{element name}#*
\saveelementname{cmd}{%<atomic number|element symbol|element name%>}#*d

\elementsymbol{%<atomic number|element name%>}
\setatomsymbol{atomic number}{element symbol}
\DeclareAtomSymbol{atomic number}{element symbol}#*
\saveelementsymbol{cmd}{%<atomic number|element symbol|element name%>}#*d

\atomicnumber{%<element symbol|element name%>}
\Z{%<element symbol|element name%>}#*
\saveatomicnumber{cmd}{%<atomic number|element symbol|element name%>}#*d

\elconf{%<atomic number|element symbol|element name%>}
\writeelconf{electron distribution}
\setelectrondistribution{atomic number}{element distribution}
\DeclareElectronDistribution{atomic number}{element distribution}#*
\printangularmomentum{value}#*

\setatomisotopes{atomic number}{isotope list}
\DeclareAtomIsotopes{atomic number}{isotope list}#*
\saveelementisotopes{cmd}{%<atomic number|element symbol|element name%>}#*d
\savemainelementisotope{cmd}{%<atomic number|element symbol|element name%>}#*d
\mainelementisotope{%<atomic number|element symbol|element name%>}