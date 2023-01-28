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
\PixelArtTikz{file}#i
\PixelArtTikz[options%keyvals]{file}#i
\PixelArtTikz[options%keyvals]<TikZ options>{file}#i
\PixelArtTikz*{file}#i
\PixelArtTikz*[options%keyvals]{file}#i

\begin{EnvPixelArtTikz}{file}#i\pictureHighlight
\begin{EnvPixelArtTikz}[options%keyvals]{file}#i
\begin{EnvPixelArtTikz}[options%keyvals]<TikZ options>{file}#i
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
\PixlArtTikz{file}#*i
\PixlArtTikz[options%keyvals]{file}#*i
\PixlArtTikz[options%keyvals]<TikZ options>{file}#*i
\PixlArtTikz*{file}#*i
\PixlArtTikz*[options%keyvals]{file}#*i

\begin{EnvPixlArtTikz}{file}#*i\pictureHighlight
\begin{EnvPixlArtTikz}[options%keyvals]{file}#*i
\begin{EnvPixlArtTikz}[options%keyvals]<TikZ options>{file}#*i
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