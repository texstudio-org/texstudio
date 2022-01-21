# libertineRoman package
# Matthew Bertucci 12/26/2021 for v5.3.0

#include:ifxetex
#include:ifluatex
#include:xkeyval
#include:textcomp
#include:mweights
#include:fontenc
#include:fontaxes

#keyvals:\usepackage/libertineRoman#c
type1#true,false
nofontspec#true,false
lining#true,false
nf#true,false
lf#true,false
oldstyle#true,false
osf#true,false
tabular#true,false
t#true,false
proportional#true,false
p#true,false
semibold#true,false
sb#true,false
bold#true,false
defaultfeatures={%<fontspec features%>}
#endkeyvals

\libertine#n
\libertineSB#n
\libertineOsF#n
\libertineLF#n
\libertineDisplay#n
\libertineInitial#n
\sufigures#n
\textsu{text}#n
\textsuperior{text}#*n
\oldstylenums{text}#n
\liningnums{text}#n
\oldstylenumsf{text}#n
\liningnumsf{text}#n
\tabularnums{text}#n
\proportionalnums{text}#n
\DeclareTextGlyphY{type}{name}{number}#*
\libertineGlyph{glyph name}#n
\libertineInitialGlyph{glyph name}#n
