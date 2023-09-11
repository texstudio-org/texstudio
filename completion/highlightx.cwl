# highlightx package
# Matthew Bertucci 2023/09/04 for v0.1.2

#include:soul
#include:tikz
#include:xstring
#include:simplekv
#include:tikzlibrarytikzmark
#include:tikzlibrarycalc
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibrarybabel

#keyvals:\usepackage/highlightx#c
nobabel
#endkeyvals

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

\SurlignerTexte{text}
\SurlignerTexte{text}<options TikZ>
\SurlignerTexte[clés%keyvals]{text}
\SurlignerTexte[clés%keyvals]{text}<options TikZ>
\SurlignerTexte*{text}
\SurlignerTexte*{text}<options TikZ>
\SurlignerTexte*[clés%keyvals]{text}
\SurlignerTexte*[clés%keyvals]{text}<options TikZ>

#keyvals:\SurlignerTexte,\SurlignerTexte*
Fond=#%color
Bord=#%color
Opacite=%<factor%>
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

\HighlightText{text}
\HighlightText{text}<TikZ options>
\HighlightText[keyvals]{text}
\HighlightText[keyvals]{text}<TikZ options>
\HighlightText*{text}
\HighlightText*{text}<TikZ options>
\HighlightText*[keyvals]{text}
\HighlightText*[keyvals]{text}<TikZ options>

#keyvals:\HighlightText,\HighlightText*
bg=#%color
border=#%color
opacity=%<factor%>
offset=##L
#endkeyvals

\genhighlightpar{text}
\genhighlightpar[color]{text}
\genhighlightpar*{text}
\genhighlightpar*[color]{text}

\surlignparbg#S
\surlignparopac#S
