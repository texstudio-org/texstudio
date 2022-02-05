# mla class
# Matthew Bertucci 2/3/2022 for v1.0

#include:enumitem
#include:fancyhdr
#include:fullpage
#include:ragged2e
#include:newtxtext
#include:titlesec
#include:xstring
#include:babel
# babel loaded with american option
#include:csquotes
#include:hanging
#include:biblatex
# default is biblatex loaded with style=mla-new option
#include:caption
#include:float
#include:graphicx
#include:enotez
#include:hyperref

#keyvals:\documentclass/mla#c
mla7
mla8
mla8alt
nofigures
nonotes
microtype
nopaperheader
nopageheader
noheaders
plainheadings
fullpage
#endkeyvals

#ifOption:microtype
#include:microtype
#endif

\mladate
\begin{noindent}#*
\end{noindent}#*
\professor{professor}
\course{course%text}
\makemlaheader#*
\begin{blockquote}
\end{blockquote}
\begin{paper}
\end{paper}
\begin{notes}
\end{notes}
\begin{mlanotes}
\end{mlanotes}
\begin{workscited}
\end{workscited}

# from style=mla-new option of biblatex
#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c
# from mla-strict.bbx
annotation#true,false
showlocation#true,false
longdash#true,false
noremoteinfo#true,false
isan#true,false
ismn#true,false
isrn#true,false
issn#true,false
# from mla.cbx
firstlonghand#true,false
nofullfootnote#true,false
mancitepar#true,false
footnoterulestrict#true,false
mladraft
#endkeyvals
# from mla-strict.bbx
\openrangeformat{arg}#*
\openrangemark#*
\mlanamedash#*
# from mla.cbx
\splitfootnoterule#S
\pagefootnoterule#S
\mlasymbolfootnote#S
\themladraftnote#S
\headlesscite[prenote][postnote]{bibid}#C
\headlesscite[postnote]{bibid}#C
\headlesscite{bibid}#C
\headlessfullcite[prenote][postnote]{bibid}#C
\headlessfullcite[postnote]{bibid}#C
\headlessfullcite{bibid}#C
\titleandsubtitle[prenote][postnote]{bibid}#*C
\titleandsubtitle[postnote]{bibid}#*C
\titleandsubtitle{bibid}#*C