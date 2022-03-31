# limap package
# Matthew Bertucci 3/31/2022 for v2.2

#include:longtable
#include:etoolbox
#include:booktabs

#keyvals:\usepackage/limap#c
austrian
german
french
english
USenglish
nonstrict
nolines
#endkeyvals

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