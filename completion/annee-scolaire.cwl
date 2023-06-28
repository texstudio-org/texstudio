# annee-scolaire package
# Matthew Bertucci 9/16/2021 for v1.6

#include:l3keys2e

#keyvals:\usepackage/annee-scolaire#c
premiermois=%<integer%>
premierjour=%<integer%>
decalage=%<integer%>
separateur=%<tokens%>
#endkeyvals

\anneescolaire
\anneescolaire[shift]
\debutanneescolaire
\debutanneescolaire[shift]
\finanneescolaire
\finanneescolaire[shift]
\AnneeScolairePresentation{year}
\AnneeScolairePresentation[number]{year}
