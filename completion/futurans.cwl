# futurans package
# Matthew Bertucci 2/27/2022 for v1.0a

#include:fontenc
#include:textcomp
#include:keyval

#keyvals:\usepackage/futurans#c
scaled=%<factor%>
#endkeyvals

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