# berenis package
# Matthew Bertucci 2024/09/30 for v2.1

#include:svn-prov
#include:fontenc
#include:nfssext-cfr

#keyvals:\usepackage/berenis#c
lig#true,false
osf
lf
prop
tab
lm
enc=#t1,ly1
scale=%<factor%>
#endkeyvals

\sishape
\textsi{text}
\swashstyle
\textswash{text}
\lstyle
\textl{text}
\zeroslash
\ostyle
\texto{text}
\tstyle
\textt{text}
\pstyle
\textp{text}
\tlstyle
\texttl{text}
\tostyle
\textto{text}
\plstyle
\textpl{text}
\postyle
\textpo{text}
\infstyle
\textinf{text}
\sustyle
\textsu{text}

# deprecated
\instyle#S
\textin{text}#S

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
