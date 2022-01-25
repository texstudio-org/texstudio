# menu package
# Matthew Bertucci 1/23/2022 for v0.994

#include:xspace

#keyvals:\usepackage/menu#c
hand
framed
grey
#endkeyvals

#ifOption:hand
#include:bbding
#endif

#ifOption:framed
#include:fancybox
#endif

#ifOption:grey
#include:fancybox
#include:color
menugrey#B
#endif

\menu{entry1!entry2!!...%text}
\begin{menufolder}{title%text}
\begin{menufolder}[length]{title%text}
\end{menufolder}
\menuitem{item%text}
\menuitem[length]{item%text}
\menuitemactive{item%text}
\menuitemactive[length]{item%text}
\menuseparator
\menuseparator[length]
\menutext{text}#*
\menumathsymbols{symbol1%formula}{symbol2%formula}
\menumathsymbols[start%formula]{symbol1%formula}{symbol2%formula}
\menusymbols{symbol1}{symbol2}
\menusymbols[start]{symbol1}{symbol2}
\menusymbols{symbol1}{symbol2}[end]#*
\menusymbols[start]{symbol1}{symbol2}[end]
\menufolderentry{title%text}#*
\menufolderentry[length]{title%text}#*
\menuitemactivesymbol#*
\menuitemlength#*
\menusep#*
\ifmenuoptionhand#*
\menuoptionhandtrue#*
\menuoptionhandfalse#*
\ifmenuoptionframed#*
\menuoptionframedtrue#*
\menuoptionframedfalse#*
\ifmenuoptiongrey#*
\menuoptiongreytrue#*
\menuoptiongreyfalse#*
\gt#S
\filedate#S
\fileversion#S