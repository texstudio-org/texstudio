# garamondx package
# Matthew Bertucci 2022/05/06 for v1.12

#include:graphicx
#include:keyval
#include:fontenc
# loads T1 option of fontenc
#include:fontaxes
#include:textcomp
#include:etoolbox

#keyvals:\usepackage/garamondx#c
babel#true,false
sups#true,false
swashQ#true,false
scaled
scaled=%<factor%>
osf#true,false
osfI#true,false
#endkeyvals

\sustyle
\swashQ
\textlf{text}
\textosf{text}
\textosfI{text}
\textsu{text}
\useosf#*
\useosfI#*

\ProcessOptionsWithKV{family}#S
\fileversion#S
\filedate#S

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