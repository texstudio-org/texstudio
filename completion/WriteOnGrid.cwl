# WriteOnGrid package
# Matthew Bertucci 2023/01/16 for v0.1.0

#include:tikz
#include:simplekv
#include:xstring
#include:tikzlibrarycalc
#include:tikzlibrarypositioning

\begin{EnvGrid}[keyvals]
\begin{EnvGrid}[keyvals]<color>
\end{EnvGrid}

#keyvals:\begin{EnvGrid}
NumSquares=%<<cols>x<rows>%>
Unit=%<number%>
Margin=%<number%>
Enlarge=%<L/R%>
Border#true,false
Seyes#true,false
#endkeyvals

\WriteLine{text}
\WriteLine<alignment>{text}
\WriteLine[keyvals]{text}
\WriteLine[keyvals]<alignment>{text}

#keyvals:\WriteLine
OffsetH=%<num squares%>
OffsetV=##L
Scale=%<factor%>
#endkeyvals

\PassLine

# French versions of commands
\begin{EnvQuadrillage}[clés%keyvals]
\begin{EnvQuadrillage}[clés%keyvals]<color>
\end{EnvQuadrillage}

#keyvals:\begin{EnvQuadrillage}
NbCarreaux=%<<nbCol>x<nbLig>%>
Unite=%<nombre%>
Marge=%<nombre%>
Elargir=%<L/R%>
Cadre#true,false
Seyes#true,false
#endkeyvals

\EcrireLigne{text}
\EcrireLigne<alignement>{text}
\EcrireLigne[clés%keyvals]{text}
\EcrireLigne[clés%keyvals]<alignement>{text}

#keyvals:\EcrireLigne
DecalH=%<nombre carreaux%>
DecalV=##L
Echelle=%<factor%>
#endkeyvals

\PasseLigne

# not documented
\QuadEchelle#S
\QuadElar#S
\QuadElarD#S
\QuadElarG#S
\QuadNbCar#S
\QuadNbLig#S
\thelgquadri#S
\ValeurCarreau#S