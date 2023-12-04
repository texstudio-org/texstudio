# vectorlogos package
# Matthew Bertucci 2023/12/01 for v0.1.2

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

# not documented
\GenMacroLogoVect{cmd}{name}#Sd