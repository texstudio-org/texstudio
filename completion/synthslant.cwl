# synthslant package
# Matthew Bertucci 2024/05/11 for v0.1

#include:iftex
#include:xkeyval

#keyvals:\usepackage/synthslant#c
auto
disable
fontspec
l3draw
negslant=%<slant-expr%>
pdf
posslant=%<slant-expr%>
ps
slant=%<slant-expr%>
tikz
#endkeyvals

#ifOption:fontspec
#include:fontspec
#endif

#ifOption:l3draw
#include:l3draw
#endif

#ifOption:ps
#include:pst-3d
#endif
#ifOption:PS
#include:pst-3d
#endif

#ifOption:tikz
#include:tikz
#endif
#ifOption:TikZ
#include:tikz
#endif

\synthslant
\synthnegslant
\textsynthslant{text}
\textsynthuprightitalic{text}
\synthslantbox{slant}{text}
\begin{slantenvironment}
\end{slantenvironment}
\begin{negslantenvironment}
\end{negslantenvironment}

\slantcontext#*
\negslantcontext#*