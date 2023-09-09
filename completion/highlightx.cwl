# highlightx package
# Matthew Bertucci 2023/09/02 for v0.1.1

#include:soul
#include:tikz
#include:xstring
#include:simplekv
#include:tikzlibrarytikzmark
#include:tikzlibrarycalc
#include:tikzlibrarydecorations.pathmorphing

hlcolback#B

\SurlignerFormule{formula}
\SurlignerFormule{formula}<options TikZ>
\SurlignerFormule[clés%keyvals]{formula}
\SurlignerFormule[clés%keyvals]{formula}<options TikZ>
\SurlignerFormule*{formula}
\SurlignerFormule*{formula}<options TikZ>
\SurlignerFormule*[clés%keyvals]{formula}
\SurlignerFormule*[clés%keyvals]{formula}<options TikZ>

#keyvals:\SurlignerFormule,\SurlignerFormule*
Fond=#%color
Bord=#%color
Texte=#%color
Offset=##L
#endkeyvals

\HighlightFormula{formula}
\HighlightFormula{formula}<TikZ options>
\HighlightFormula[keyvals]{formula}
\HighlightFormula[keyvals]{formula}<TikZ options>
\HighlightFormula*{formula}
\HighlightFormula*{formula}<TikZ options>
\HighlightFormula*[keyvals]{formula}
\HighlightFormula*[keyvals]{formula}<TikZ options>

#keyvals:\HighlightFormula,\HighlightFormula*
bg=#%color
border=#%color
text=#%color
offset=##L
#endkeyvals

\genhighlightpar{text}
\genhighlightpar[color]{text}