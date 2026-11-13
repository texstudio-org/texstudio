# florilegium package
# Matthew Bertucci 2026/11/11 for v2.0.1

#include:luatex
#include:tikz
#include:eso-pic

#keyvals:\usepackage/florilegium#c
aging
authored
grown
intensity=%<factor%>
nomargin
novisitors
sections
theme=#geometric,math
#endkeyvals

\florilegiumage{factor}
\florilegiumbloom
\florilegiumbloom[type]
\florilegiumdraw{type}{number}
\florilegiumframe[opt]{k}{n}
\florilegiumframe{k}{n}
\florilegiuminitial[lines]{letter}
\florilegiuminitialfont{font file%file}
\florilegiuminitial{letter}
\florilegiumornament{type}
\florilegiumseed#*
\florilegiumtextend
\florilegiumtheme{theme}

ink#B
accent#B