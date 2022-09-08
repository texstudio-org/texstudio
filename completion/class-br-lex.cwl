# br-lex class
# Matthew Bertucci 2022/09/07 for v2017/08/01

#include:class-mwbk
#include:ulem
#include:ifxetex
#include:fontspec
#include:polyglossia
#include:inputenc
#include:babel
# loads brazil option of babel
#include:textcase

#keyvals:\documentclass/br-lex#c
capitulo
paragrafoespaco
paragrafonormal
# options passed to mwbk class
a4paper
a5paper
a6paper
b4paper
b5paper
b6paper
letterpaper
legalpaper
executivepaper
landscape
wide
withmarginpar
withoutmarginpar
10pt
10dd
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
openright
openany
onecolumn
twocolumn
leqno
fleqn
openbib
rmheadings
sfheadings
floatssmall
floatsnormalsize
authortitle
titleauthor
indentfirst
noindentfirst
#endkeyvals

\titulo{Título%text}
\descricao{Descrição%text}
\cortado{texto%text}

\artigo
\paragrafo
\paragrafounico
\inciso
\alinea
\itens

\theartigo#*
\theparagrafo#*
\theinciso#*
\thealinea#*
\theitens#*

# from brazil option of babel
\captionsbrazil#*
\datebrazil#*
\extrasbrazil#*
\noextrasbrazil#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
\ord
\orda
\ro#*
\ra#*