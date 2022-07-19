# asternote package
# Matthew Bertucci 2022/07/17 for v1.1

#keyvals:\usepackage/asternote#c
japanese
luajapanese
#endkeyvals

#ifOption:luajapanese
#include:luatex
#endif

\setasternotenoindent
\setasternoteindent
\setasternotetext
\setasternotesuperscript
\setasterreftext
\setasterrefsuperscript
\setasternumbertext
\asternumbersetsuperscript
\asternotereset
\asternote{label}#l
\asternotetext{label}#l
\asternotesuperscript{label}#l
\asterref{label}#r
\asterreftext{label}#r
\asterrefsuperscript{label}#r
\asternumber{text%plain}
\asternumbertext{text%plain}
\asternumbersuperscript{text%plain}

# not documented
\theasternotecounter#*