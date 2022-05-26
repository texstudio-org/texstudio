# ycbook class
# Matthew Bertucci 2022/05/25 for release 2018/01/03

#include:class-mwbk
#include:titletoc
#include:ifxetex
#include:inputenc
#include:hyperref
#include:graphicx
#include:booktabs
#include:adjustbox
#include:afterpage
#include:placeins
#include:changepage

#keyvals:\documentclass/ycbook#c
chapterrule
sectionrule
chaptercentered
chapterleft
chapterright
nochaptercentered
nochapterleft
nochapterright
sansserifnotes
nodots
nofootnoterule
traditionalfootnote
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

#keyvals:\pagestyle#c,\thispagestyle#c
headingsbeforeplain
myheadingsbeforeplain
uheadings
myuheadings
headingsnodot
uheadingsnodot
headingsbeforeplainnodot
#endkeyvals

\fancytoc
\traditionaltoc
\coloredheadline{color}
\coloredfootline{color}
\twopagepicture{placement}{l or p}{imagefile}{caption%text}#g
\twopagepicturen{placement}{l or p}{imagefile}{caption%text}#g
\mywidth#S
\oldfootnote{text}#S