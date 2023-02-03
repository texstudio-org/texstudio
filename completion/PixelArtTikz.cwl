# PixelArtTikz package
# Matthew Bertucci 2023/01/26 for v0.1.0

#keyvals:\usepackage/PixelArtTikz#c
csvii
#endkeyvals

#include:tikz
#include:simplekv
#include:xintexpr
#include:xinttools
#include:xstring
#include:listofitems
#include:csvsimple-l3

# French commands
\PixelArtTikz{file}
\PixelArtTikz[options%keyvals]{file}
\PixelArtTikz[options%keyvals]<TikZ options>{file}
\PixelArtTikz*{file}
\PixelArtTikz*[options%keyvals]{file}

\begin{EnvPixelArtTikz}{file}#\pictureHighlight
\begin{EnvPixelArtTikz}[options%keyvals]{file}
\begin{EnvPixelArtTikz}[options%keyvals]<TikZ options>{file}
\end{EnvPixelArtTikz}

#keyvals:\PixelArtTikz,\PixelArtTikz*,\begin{EnvPixelArtTikz}
Codes=%<chaîne%>
Couleurs={%<couleur1,couleur2,...%>}
Symboles={%<symbol1,symbol2,...%>}
Correction#true,false
Symb#true,false
BordCases#true,false
Style=%<font commands%>
Unite=%<nombre%>
#endkeyvals

# English commands
\PixlArtTikz{file}#*
\PixlArtTikz[options%keyvals]{file}#*
\PixlArtTikz[options%keyvals]<TikZ options>{file}#*
\PixlArtTikz*{file}#*
\PixlArtTikz*[options%keyvals]{file}#*

\begin{EnvPixlArtTikz}{file}#*\pictureHighlight
\begin{EnvPixlArtTikz}[options%keyvals]{file}#*
\begin{EnvPixlArtTikz}[options%keyvals]<TikZ options>{file}#*
\end{EnvPixlArtTikz}#*

#keyvals:\PixlArtTikz,\PixlArtTikz*,\begin{EnvPixlArtTikz}
Codes=%<string%>
Colors={%<color1,color2,...%>}
Symbols={%<symbol1,symbol2,...%>}
Correction#true,false
Symb#true,false
Border#true,false
Style=%<font commands%>
Unit=%<number%>
#endkeyvals

# not documented
\PATchiffres#S
\PATcouleurs#S
\PATlettres#S
\PATtaille#S
\PATunit#S
\pixchf#S
\pixcnt#S
\pixcol#S
\pixpos#S
