# limap class
# Matthew Bertucci 3/31/2022 for v2.2

#include:longtable
#include:etoolbox
#include:booktabs
#include:fancyhdr
#include:class-report

#keyvals:\documentclass/limap#c
austrian
german
french
english
USenglish
nonstrict
nolines
book
report
article
letter
koma
base
# options passed to report, the default underlying class
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
openright
openany
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

#ifOption:book
#include:class-book
#endif

#ifOption:letter
#include:class-letter
#endif

#ifOption:koma
#include:class-scrreprt
#endif

\Block{title}
\MapBlockLabelFont#*
\MapParskip#*
\MapTitleFraction#*
\MapTextFraction#*
\MapRuleWidth#*
\MapRuleStart#*
\WideBlock{content%text}

\begin{Map}{title}
\end{Map}
\MapFont#*
\MapTitleFont#*
\MapContinued#*
\MapContinuing#*
\MapTitleContinuedFont#*
\MapNewpage#*
\MapTOC{text}#*

\MapTableOfContents
\MapTableOfContentsStyle#*
\MapBlockStartHook{code}#*
\MapBlockTOC{text}#*

\begin{MapTabular}{preamble}#\tabular
\end{MapTabular}
\MapTabularFraction#*

\MapTOCname#*
\MapTOCpage#*

# not in main documentation
\filename#S
\fileversion#S
\filedate#S
\docversion#S
\docdate#S
\defineLimapLanguage{name}{continued}{continuing}{TOCname}{TOCpage}#*
\MapContinuingFormat{text}#*
\MapContinuedFormat{text}#*
\MapTOCheadfont#*
\MakeTitle#S
\begin{Abstract}#S
\end{Abstract}#S