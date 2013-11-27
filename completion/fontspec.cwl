#  fontspec 1.14 package
#  nja 17 July 2007
#  url: http://www.ctan.org/tex-archive/help/Catalogue/entries/fontspec.html

\usepackage[cm-default/lm-default/math/no-math/config/no-config/quiet]{fontspec}

\fontspec{fontname}
\fontspec[fontfeature=option]{fontname}
\fontspec[fontfeature=option,fontfeature=option]{fontname}

\setmainfont{fontname}
\setmainfont[fontfeature=option]{fontname}
\setmainfont[fontfeature=option,fontfeature=option]{fontname}

\setsansfont{fontname}
\setsansfont[fontfeature=option]{fontname}
\setsansfont[fontfeature=option,fontfeature=option]{fontname}

\setmonofont{fontname}
\setmonofont[fontfeature=option]{fontname}
\setmonofont[fontfeature=option,fontfeature=option]{fontname}

\newfontfamily<fontinstance>{fontname}

\newfontface<fontface>{fontname}
\newfontface<fontface>[fontfeature=option]{fontname}
\newfontface<fontface>[fontfeature=option,fontfeature=option]{fontname}

\setmathrm
\setboldmathrm
\setmathsf
\setmathtt


\defaultfontfeatures{fontfeature=option}
\defaultfontfeatures{fontfeature=option,fontfeature=option}
\addfontfeatures{fontfeatures}
\addfontfeatures{fontfeature=option,fontfeature=option}

\newfontscript{fontspecname}{OpenTypedefinition}
\newfontlanguage{fontspecname}{OpenTypedefinition}

\newAATfeature{feature}{option}{featurecode}{selectorcode}
\newfeaturecode{feature}{option}{featurecode}{selectorcode}
\newICUfeature{feature}{option}{featuretag}
\newfontfeature{name}{inputstring}
\aliasfontfeature{existingname}{newname}
\aliasfontfeatureoption{fontfeature}{existingname}{newname}

