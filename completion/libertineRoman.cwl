# libertineRoman package
# Matthew Bertucci 2023/11/27 for v5.3.0

#include:ifxetex
#include:ifluatex
#include:xkeyval
#include:mweights
#include:fontenc
#include:fontaxes

#keyvals:\usepackage/libertineRoman#c
type1#true,false
nofontspec#true,false
lining#true,false
oldstyle#true,false
tabular#true,false
proportional#true,false
semibold#true,false
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
\textsu{text}#*n
\textsup{text}#n
\textsuperior{text}#*n
\liningnums{text}#n
\oldstylenumsf{text}#n
\liningnumsf{text}#n
\tabularnums{text}#n
\proportionalnums{text}#n
\DeclareTextGlyphY{type}{name}{number}#*
\libertineGlyph{glyph name}#n
\libertineInitialGlyph{glyph name}#n
