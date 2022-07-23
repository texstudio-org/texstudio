# miscdoc package
# Matthew Bertucci 2022/07/20 for v1.2

#include:lmodern
#include:fontenc
# loads T1 option of fontenc
#include:booktabs

#keyvals:\usepackage/miscdoc#c
hyper
#endkeyvals

#ifOption:hyper
#include:hyperref
#include:bookmark
#endif

\cs{csname}
\csx{csname}#S
\bsbs
\cmdinvoke{%<csname%>}%<arguments%>
\cmdinvoke*{%<csname%>}%<arguments%>
\delcmdinvoke{%<csname%>}%<delimiter%>
\delcmdinvoke*{%<csname%>}%<delimiter%>
\newitem
\meta{arg}
\environment{envname}
\pkgoption{option}
\extension{ext}
\Package{package}
\option{option}
\option[option]
\FontName{font}

# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n