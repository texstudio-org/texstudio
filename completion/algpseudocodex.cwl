# algpseudocodex package
# Matthew Bertucci 2023/02/17 for v1.1.0

#include:kvoptions
#include:algorithmicx
#include:etoolbox
#include:fifo-stack
#include:varwidth
#include:tabto
#include:totcount
#include:tikz
#include:tikzlibrarycalc
#include:tikzlibraryfit
#include:tikzlibrarytikzmark

#keyvals:\usepackage/algpseudocodex#c
noEnd#true,false
indLines#true,false
spaceRequire#true,false
italicComments#true,false
rightComments#true,false
commentColor=#%color
beginComment=%<text%>
endComment=%<text%>
beginLComment=%<text%>
endLComment=%<text%>
#endkeyvals

\Call{name}{args}#/algorithmic
\Output#/algorithmic
\Return#/algorithmic

\While{condition}#/algorithmic
\EndWhile#/algorithmic

\For{condition}#/algorithmic
\ForAll{condition}#/algorithmic
\EndFor#/algorithmic

\Loop#/algorithmic
\EndLoop#/algorithmic

\Repeat#/algorithmic
\Until{condition}#/algorithmic

\If{condition}#/algorithmic
\ElsIf{condition}#/algorithmic
\Else#/algorithmic
\EndIf#/algorithmic

\Procedure{name}{parameters}#/algorithmic
\EndProcedure#/algorithmic

\Function{name}{parameters}#/algorithmic
\EndFunction#/algorithmic

\Require#/algorithmic
\Ensure#/algorithmic

\LComment{text}#/algorithmic

\BeginBox#/algorithmic
\BeginBox[TikZ options]#/algorithmic
\EndBox#/algorithmic
\BoxedString{text}#/algorithmic
\BoxedString[TikZ options]{text}#/algorithmic

\algorithmicend#*
\algorithmicdo#*
\algorithmicwhile#*
\algorithmicfor#*
\algorithmicforall#*
\algorithmicloop#*
\algorithmicrepeat#*
\algorithmicuntil#*
\algorithmicprocedure#*
\algorithmicfunction#*
\algorithmicif#*
\algorithmicthen#*
\algorithmicelse#*
\algorithmicrequire#*
\algorithmicensure#*
\algorithmicreturn#*
\algorithmicoutput#*
