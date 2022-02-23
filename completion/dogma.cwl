# dogma package
# Matthew Bertucci 2/22/2022 for v1.3

#include:fontenc
#include:textcomp
#include:keyval

#keyvals:\usepackage/dogma#c
scaled=%<factor%>
#endkeyvals

\dogmabold{text}
\dogmablack{text}
\dogmaoutline{text}
\dogmascript{text}
\ProcessOptionsWithKV{family}#S

# from T1 option of fontenc
\DH#n
\NG#n
\dj#n
\ng#n
\k{arg}#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\quotedblbase#n
\quotesinglbase#n
\textquotedbl#n
\DJ#n
\th#n
\TH#n
\dh#n
\Hwithstroke#*n
\hwithstroke#*n
\textogonekcentered{arg}#*n
\guillemetleft#n
\guillemetright#n