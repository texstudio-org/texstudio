# vectorlogos package
# Matthew Bertucci 2024/03/30 for v0.1.3

#include:calc
#include:graphicx
#include:xstring

\simplevectorlogo{name%keyvals}
\simplevectorlogo[options]{name%keyvals}
\simplevectorlogo*{name%keyvals}
\simplevectorlogo*[options]{name%keyvals}
\vectorlogo{name%keyvals}
\vectorlogo[suffix]{name%keyvals}

#keyvals:\simplevectorlogo,\simplevectorlogo*,\vectorlogo
emacs
geogebra
scratch
texmaker
texstudio
miktex
ctanlion
latexproject
texworks
#endkeyvals

#keyvals:\simplevectorlogo,\simplevectorlogo*
emacs-alt
geogebra-icon
scratch-alt
scratch-cat
texmaker-alt
#endkeyvals

\logoscratch
\logoscratch[suffix]
\logogeogebra
\logogeogebra[suffix]
\logotexstudio
\logotexstudio[suffix]
\logoemacs
\logoemacs[suffix]
\logotexmaker
\logotexmaker[suffix]
\logomiktex
\logomiktex[suffix]
\logoctanlion
\logoctanlion[suffix]
\logolatexproject
\logolatexproject[suffix]
\logotexworks
\logotexworks[suffix]

# not documented
\GenMacroLogoVect{cmd}{name}#Sd
