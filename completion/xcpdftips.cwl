# xcpdftips package
# Matthew Bertucci 1/22/2022 for v1.1

#include:bibentry
#include:pdfcomment
#include:etoolbox

#ifOption:ocg
#include:pdfbase
#include:ocgbase
#include:calc
#include:linegoal
#include:xcolor
#endif

#ifOption:tcolorbox
#include:tcolorbox
#endif

#keyvals:\usepackage/xcpdftips#c
redefcite
ocg
tcolorbox
#endkeyvals

\xpdfcite{keylist}#c
\xpdfcite[postfix]{keylist}
\xpdfcite[prefix][postfix]{keylist}