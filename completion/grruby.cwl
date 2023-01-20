# grruby package
# ponte-vecchio 2023-01-17 for v0.7

#include:ragged2e
#include:relsize
#include:etoolbox
#include:xcolor

#keyvals:\usepackage/grruby#c
rubystyle=#default,gromob,XXruby,ruby,progress,rup,lw,rw,user
rubycolor=#%color
expos#true,false
pdflatex
#endkeyvals

\grfoo %<hangul%>(%<hanja%>)
\grfoo %<hangul%>(%<hanja%>){%<footnote%>}
\grrubystyle{%<options%>}
\grrubycolor{color}

#keyvals:\grrubystyle#c
default
gromob
XXruby
ruby
progress
rup
lw
rw
user
#endkeyvals

\begin{grruby}
\end{grruby}
\begin{grrubypars}
\end{grrubypars}

\grexpos
\grexpos[%<options%>]

#keyvals:\grexpos#c
true
false
#endkeyvals

\grrubyUserDefined{%<hangul%>}{%<hanja%>}
