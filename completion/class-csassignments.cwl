# csassignments class
# Matthew Bertucci 2022/06/09 for v1.0.0

#include:geometry
#include:inputenc
#include:babel
# loads english option of babel
#include:titlesec
#include:enumitem
#include:graphicx
#include:tocloft
#include:float
#include:ifthen
#include:translations
#include:csquotes
#include:fancyhdr
#include:microtype
#include:stmaryrd
#include:pdfpages
#include:hyperref
#include:tikz
#include:microtype
#include:amsmath
#include:amsthm
#include:amssymb
#include:mathtools
#include:totcount
#include:changepage
#include:etoolbox
#include:environ
#include:multicol
#include:tgpagella
#include:suffix
#include:tikzlibrarycalc

# passes all options to article class
#keyvals:\documentclass/csassignments#c
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

\gradingtable
\exercise{title%text}
\exercise[points]{title%text}
\exercise*{title%text}
\exercise*[points]{title%text}
\subexercise
\subexercise[title%text]
\exerciseRules
\subexerciseRules
\noPoints
\course{course%text}
\sheet{number}
\group{name}
\due{date}
\member{name}
\member[student id]{name}
\PrefixId{prefix text%text}
\PrefixAuthor{prefix text%text}
\PrefixDate{prefix text%text}
\N
\Z
\R
\Q
\C
\F
\primefield
\modring{ring}{modulus}
\derivative{variable%formula}
\matadd{mat1%formula}{mat2%formula}{mat3%formula}
\matmul{mat1%formula}{mat2%formula}
\matswap{mat1%formula}{mat2%formula}
\forall
\exists
\floor{arg%formula}
\ceil{arg%formula}
\abs{arg%formula}
\rfrac{numerator}{denominator}#m
\rel{symbol%formula}
\QED

\theexercisenumber#*
\thesubexercisenumber#*
\thetotalpoints#*
\gradingTableExerciseLabel#*
\gradingTableExercisePoints#*
\PTableA#*
\PTableB#*
\PTHead#*
\points#*
\Vhrulefill#*
\pdfmembers#*
\pdfmember{name}#*
\pdfmember[student id]{name}#*

#keyvals:\theoremstyle#c
it
#endkeyvals

# from english option of babel
\captionsenglish#*
\dateenglish#*
\extrasenglish#*
\noextrasenglish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
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
