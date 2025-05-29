# PixelArtTikz package
# Matthew Bertucci 2025/05/05 for v0.1.8

#keyvals:\usepackage/PixelArtTikz#c
csvii
#endkeyvals

#include:tikz
#include:simplekv
#include:xintexpr
#include:xinttools
#include:xstring
#include:multicol
#include:listofitems
#include:ifthen
#include:csvsimple-l3
#include:datatool

# French commands
\PixelArtTikz{file}
\PixelArtTikz<TikZ options>{file}
\PixelArtTikz[clés%keyvals]{file}
\PixelArtTikz[clés%keyvals]<TikZ options>{file}
\PixelArtTikz*{file}
\PixelArtTikz*[clés%keyvals]{file}

\begin{EnvPixelArtTikz}{file}#\pictureHighlight
\begin{EnvPixelArtTikz}<TikZ options>{file}
\begin{EnvPixelArtTikz}[clés%keyvals]{file}
\begin{EnvPixelArtTikz}[clés%keyvals]<TikZ options>{file}
\end{EnvPixelArtTikz}

\PixelArtTikzBloc{file}{découpage}{num bloc}
\PixelArtTikzBloc<TikZ options>{file}{découpage}{num bloc}
\PixelArtTikzBloc[clés%keyvals]{file}{découpage}{num bloc}
\PixelArtTikzBloc[clés%keyvals]<TikZ options>{file}{découpage}{num bloc}

\DecoupPixelArtTikz{file}{découpage}
\DecoupPixelArtTikz<TikZ options>{file}{découpage}
\DecoupPixelArtTikz[clés%keyvals]{file}{découpage}
\DecoupPixelArtTikz[clés%keyvals]<TikZ options>{file}{découpage}
\DecoupPixelArtTikz*{file}{découpage}
\DecoupPixelArtTikz*<TikZ options>{file}{découpage}
\DecoupPixelArtTikz*[clés%keyvals]{file}{découpage}
\DecoupPixelArtTikz*[clés%keyvals]<TikZ options>{file}{découpage}

\AideGrillePixelArtTikz{file}{découpage}
\AideGrillePixelArtTikz[clés%keyvals]{file}{découpage}
\AideGrillePixelArtTikz*{file}{découpage}
\AideGrillePixelArtTikz*[clés%keyvals]{file}{découpage}

#keyvals:\PixelArtTikz,\PixelArtTikz*,\begin{EnvPixelArtTikz},\PixelArtTikzBloc,\DecoupPixelArtTikz,\DecoupPixelArtTikz*,\AideGrillePixelArtTikz,\AideGrillePixelArtTikz*
Codes=%<chaîne%>
Couleurs={%<couleur1,couleur2,...%>}
Symboles={%<symbol1,symbol2,...%>}
Correction#true,false
Symb#true,false
BordCases#true,false
Decoupage=
Style=%<font commands%>
Unite=%<nombre%>
#endkeyvals

\PixelArtTikzCylindre{file}
\PixelArtTikzCylindre[clés%keyvals]{file}

\MiniPixelArt{liste des couleurs}
\MiniPixelArt{liste des couleurs}<TikZ options>
\MiniPixelArt[clés%keyvals]{liste des couleurs}
\MiniPixelArt[clés%keyvals]{liste des couleurs}<TikZ options>

#keyvals:\MiniPixelArt
Unite=##L
Bord#true,false
#endkeyvals

\TablCouleursPixelArt{données1,données2,...}
\TablCouleursPixelArt[clés%keyvals]{données1,données2,...}
\TablCouleursPixelArt*{données1,données2,...}
\TablCouleursPixelArt*[clés%keyvals]{données1,données2,...}

\cctblr{couleur fond}{case}
\cctblr[couleur police]{couleur fond}{case}

\readdtcsv{file}{nomlecture}
\dtpixlarttikz{nomlecture}
\dtpixlarttikz[clés%keyvals]{nomlecture}
\dtpixlarttikzblock{nomlecture}{LxC ou L+C}{numbloc}
\dtpixlarttikzblock[clés%keyvals]{nomlecture}{LxC ou L+C}{numbloc}

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

\PixelArtTikzBloc{file}{découpage}{num bloc}
\PixelArtTikzBloc<TikZ options>{file}{découpage}{num bloc}
\PixelArtTikzBloc[clés%keyvals]{file}{découpage}{num bloc}
\PixelArtTikzBloc[clés%keyvals]<TikZ options>{file}{découpage}{num bloc}

\CutPixlArtTikz{file}{cutting}
\CutPixlArtTikz<TikZ options>{file}{cutting}
\CutPixlArtTikz[keyvals]{file}{cutting}
\CutPixlArtTikz[keyvals]<TikZ options>{file}{cutting}
\CutPixlArtTikz*{file}{cutting}
\CutPixlArtTikz*<TikZ options>{file}{cutting}
\CutPixlArtTikz*[keyvals]{file}{cutting}
\CutPixlArtTikz*[keyvals]<TikZ options>{file}{cutting}

\HelpGridPixelArtTikz{file}{découpage}
\HelpGridPixelArtTikz[clés%keyvals]{file}{découpage}
\HelpGridPixelArtTikz*{file}{découpage}
\HelpGridPixelArtTikz*[clés%keyvals]{file}{découpage}

#keyvals:\PixlArtTikz,\PixlArtTikz*,\begin{EnvPixlArtTikz},\CutPixlArtTikz,\CutPixlArtTikz*,\HelpGridPixelArtTikz,\HelpGridPixelArtTikz*
Codes=%<string%>
Colors={%<color1,color2,...%>}
Symbols={%<symbol1,symbol2,...%>}
Correction#true,false
Symb#true,false
Border#true,false
Style=%<font commands%>
Unit=%<number%>
#endkeyvals

\PixlArtTikzCylindric{file}
\PixlArtTikzCylindric[keyvals]{file}

\MiniPixlArt{list of colors}
\MiniPixlArt{list of colors}<TikZ options>
\MiniPixlArt[options%keyvals]{list of colors}
\MiniPixlArt[options%keyvals]{list of colors}<TikZ options>

#keyvals:\MiniPixlArt
Unit=##L
Border#true,false
#endkeyvals
