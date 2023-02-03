# latexalpha2 package
# Matthew Bertucci 2/2/2022 for v1.0

#include:graphicx
#include:amsmath
#include:etoolbox
#include:pdftexcmds
#include:morewrites

#keyvals:\usepackage/latexalpha2#c
local
cloud
cache
nocache
#endkeyvals

\wolfram{code%definition}
\wolfram[format%keyvals]{code%definition}

#keyvals:\wolfram
tex
wolfram
text
#endkeyvals

\wolframgraphics{code%definition}{file}
\wolframgraphics[format%keyvals]{code%definition}{file}

#keyvals:\wolframgraphics
pdf
png
jpg
#endkeyvals

\wolframalpha{query}
\wolframalpha[format%keyvals]{query}

#keyvals:\wolframalpha
tex
wolfram
wolfram2
text
#endkeyvals

\wolframsolve{equation%definition}{independent variable%definition}{dependent variable%definition}
\wolframsolve{equation%definition}{independent variable%definition}{dependent variable%definition}
\wolframdsolve{equation%definition}{independent variable%definition}{dependent variable%definition}
\wolframdsolve{equation%definition}{independent variable%definition}{dependent variable%definition}

\wolframtex{code%definition}
\wolframtex[format%keyvals]{code%definition}

#keyvals:\wolframtex
tex
wolfram
text
#endkeyvals

\wolframanimation{code%definition}{folder name%definition}

\backslash

# not documented
\instring{char}{string}#*
\wsreturncodefile#*
\wsreturncode#*
