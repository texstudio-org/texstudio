# countriesofeurope package
# Matthew Bertucci 9/19/2021 for v0.23

#include:ifxetex
#include:ifluatex
#include:xkeyval
#include:graphicx
#include:xcolor
#include:fontenc
#include:textcomp

#keyvals:\usepackage/countriesofeurope#c
Scale=%<factor%>
Ligatures=
#endkeyvals

\countriesofeuropefamily#*
\CoEF#*
\EUCountry{name}
\EUCountry[options%keyvals]{name}
\setCoEkeys{options%keyvals}

#keyvals:\EUCountry,\setCoEkeys
Scale=%<factor%>
outline#true,false
fillcolor=#%color
linecolor=#%color
#endkeyvals

\Albania
\Andorra
\Austria
\Belarus
\Belgium
\Bosnia
\Bulgaria
\Croatia
\Czechia
\Denmark
\Estonia
\Finland
\France
\Germany
\GreatBritain
\Greece
\Hungary
\Iceland
\Ireland
\Italy
\Latvia
\Liechtenstein
\Lithuania
\Luxembourg
\Macedonia
\Malta
\Moldova
\Montenegro
\Netherlands
\Norway
\Poland
\Portugal
\Romania
\Serbia
\Slovakia
\Slovenia
\Spain
\Sweden
\Switzerland

\getPDFsyntax#S
\getPDFcolor#S

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
