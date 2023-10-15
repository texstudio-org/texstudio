# PixelArtTikz package
# Matthew Bertucci 2023/10/15 for v0.1.2

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
\PixelArtTikz[clés%keyvals]{file}
\PixelArtTikz[clés%keyvals]<TikZ options>{file}
\PixelArtTikz*{file}
\PixelArtTikz*[clés%keyvals]{file}

\begin{EnvPixelArtTikz}{file}#\pictureHighlight
\begin{EnvPixelArtTikz}[clés%keyvals]{file}
\begin{EnvPixelArtTikz}[clés%keyvals]<TikZ options>{file}
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

\MiniPixelArt{liste des couleurs}
\MiniPixelArt{liste des couleurs}<TikZ options>
\MiniPixelArt[clés%keyvals]{liste des couleurs}
\MiniPixelArt[clés%keyvals]{liste des couleurs}<TikZ options>

#keyvals:\MiniPixelArt
Unite=##L
Bord#true,false
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

\MiniPixlArt{list of colors}
\MiniPixlArt{list of colors}<TikZ options>
\MiniPixlArt[options%keyvals]{list of colors}
\MiniPixlArt[options%keyvals]{list of colors}<TikZ options>

#keyvals:\MiniPixlArt
Unit=##L
Border#true,false
#endkeyvals

# not documented
\DessineCarrePA{arg1}{arg2}{arg3}#S
\DrawSquarePA{arg1}{arg2}{arg3}#S
\minipaunit#S
\PATchiffres#S
\PATcouleurs#S
\PATlettres#S
\PATtaille#S
\PATunit#S
\pixchf#S
\pixcnt#S
\pixcol#S
\pixpos#S
