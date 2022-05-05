# kotexutf package
# Matthew Bertucci 2022/05/04 for v2.1.1

#include:inputenc
#include:kolabels-utf

#keyvals:\usepackage/kotexutf#c
nonfrench
hangul
hanja
nojosa
finemath
strictcharcheck
#endkeyvals

#ifOption:hangul
#include:kosections-utf
#endif

#ifOption:finemath
\finemath#S
#endif

#ifOption:strictcharcheck
\strictcharcheck#S
#endif

\dotemph{text}
\jong
\jung
\rieul
\SetAdhocFonts{hangul font}{hanja font}
\SetHangulFonts{serif font}{sans font}{mono font}
\SetHanjaFonts{serif font}{sans font}{mono font}
\setInterHangulSkip{skip%l}
\SetSansFonts{hangul font}{hanja font}
\SetSerifFonts{hangul font}{hanja font}
\usehangulfontspec{font}

# not documented
\asciiexclamationafterhangul{arg}#*
\asciifullstopafterhangul{arg}#*
\asciiquestionafterhangul{arg}#*
\breakafterasciichar#*
\breakafterinlinemath#*
\breakbeforeasciichar#*
\breakbetweenhangul#*
\breakbetweenhanja#*
\cjksymbolextraspace#*
\cjksymbolskip#*
\cjksymbolunskip#*
\declarehangulspacefactor#*
\declarehanjaspacefactor#*
\declarenobreakspacefactor#*
\disablehangulfontspec#*
\disablehangullinebreak#*
\josatoks{arg}#*
\kernbeforeasciichar#*
\kernbeforelatinquoteclose#*
\makejosa{jung}{jong}#*
\nobreakafterasciichar#*
\nobreakafterinlinemath#*
\nobreakbetweenhangul#*
\nobreakbetweenhanja#*
\pdfstringdefPreHook#S
\postcjksymbol#*
\postcjksymnobreak#*
\postcjksymskip#*
\unihangulchar{arg}#*