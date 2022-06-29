# emisa class
# Matthew Bertucci 2022/06/28 for v2.3.0

#include:inputenc
#include:fontenc
# loads T1 option of fontenc
#include:textcomp
#include:microtype
#include:babel
#include:float
#include:caption
#include:graphicx
#include:xcolor
# loads table option of xcolor
#include:etoolbox
#include:biblatex
# loads style=emisa option of biblatex

#include:afterpage
#include:amsmath
#include:amssymb

#include:booktabs
#include:calc
#include:environ
#include:eso-pic


#include:geometry

#include:listings
#include:newtxmath
#include:newtxtext
#include:placeins
#include:twoopt
#include:url
#include:xspace

#keyvals:\documentclass/emisa#c

#endkeyvals



















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

# from table option of xcolor
#include:colortbl
\rowcolors{row}{odd-row-color}{even-row-color}
\rowcolors[commands]{row}{odd-row-color}{even-row-color}
\rowcolors{row}{color}{color}#S
\rowcolors[commands]{row}{color}{color}#S
\rowcolors*{row}{odd-row-color}{even-row-color}
\rowcolors*[commands]{row}{odd-row-color}{even-row-color}
\rowcolors*{row}{color}{color}#S
\rowcolors*[commands]{row}{color}{color}#S
\showrowcolors
\hiderowcolors
\rownum

# from style=emisa option of biblatex