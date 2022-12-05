# guitarchordschemes package
# Matthew Bertucci 2/15/2022 for v0.7

#include:tikz
#include:tikzlibraryshapes.misc
#include:tikzlibrarycalc
#include:cnltx-base

\chordscheme
\chordscheme[options%keyvals]

#keyvals:\chordscheme
fret-number=%<number%>
name=%<chord symbol%>
position=%<position%>
finger=%<fret%>/%<string%>:%<label%>
root=%<fret%>/%<string%>:%<label%>
show-root=%<fret%>/%<string%>
barre=%<fret%>/%<string range%>:%<label%>
ring={%<strings%>}
mute={%<strings%>}
#endkeyvals

\scales
\scales[options%keyvals]

#keyvals:\scales#c
fret-number=%<number%>
name=%<title%>
position=%<position%>
finger=%<fret%>/%<string%>:%<label%>
root=%<fret%>/%<string%>:%<label%>
fingering=#type 1,type 1A,type 2,type 3,type 4
fingering*=#type 1,type 1A,type 2,type 3,type 4
fingering?=#type 1,type 1A,type 2,type 3,type 4
#endkeyvals

\setfingering{name}{fingers}{roots}

\setchordscheme{options%keyvals}

#keyvals:\setchordscheme,\usepackage/guitarchordschemes#c
x-unit=##L
y-unit=##L
rotate=%<angle%>
finger-format={%<TeX code%>}
finger-format+={%<TeX code%>}
position-format={%<TeX code%>}
position-format+={%<TeX code%>}
name-format={%<TeX code%>}
name-format+={%<TeX code%>}
name-below#true,false
name-distance=##L
chord-name-cs=%<cs%>
scales-name-cs=%<cs%>
string-name-format={%<TeX code%>}
string-name-format+={%<TeX code%>}
strings=%<number%>
chord-frets=%<number%>
scales-frets=%<number%>
line-width=##L
finger-radius=%<number%>
finger-x-offset=%<number%>
finger-y-offset=%<number%>
finger-style={%<TikZ style%>}
root-style={%<TikZ style%>}
show-root-style={%<TikZ style%>}
ringing-style={%<TikZ style%>}
muted-style={%<TikZ style%>}
tuning={%<strings%>}
restrict-bounding-box#true,false
#endkeyvals

\rootsymbol#*
\showrootsymbol#*
\ringingstring#*
\mutedstring#*
