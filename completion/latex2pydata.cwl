# latex2pydata package
# Matthew Bertucci 2025/03/04 for v0.5.0

#include:etoolbox
#include:fvextra
#include:pdftexcmds

\pydatasetfilehandle{filehandle}#*
\pydatareleasefilehandle{filehandle}#*
\pydatasetfilename{file}#*
\pydataclosefilename{file}#*
\pydatasetschemamissing{missing behavior}#*
\pydatasetschemakeytype{key%plain}{value type}#*
\pydataclearschema#*
\pydatawritemeta#*
\pydataclearmeta#*
\pydatawritedictopen#*
\pydatawritedictclose#*
\pydatawritelistopen#*
\pydatawritelistclose#*
\pydatawritekey{key%plain}#*
\pydatawritevalue{value}#*
\pydatawritekeyedefvalue{key%plain}{value}#*
\pydatawritekeyvalue{key%plain}{value}#*
\begin{pydatawritemlvalue}#*
\end{pydatawritemlvalue}#*
\pydatawritemlvalueopen#*
\pydatawritemlvalueline{line}#*
\pydatawritemlvalueclose#*
\pydatasetbuffername{buffername}#*
\pydataclearbuffername{buffername}#*
\pydatabuffermdfivesum#*
\pydatawritebuffer#*
\pydatabufferkey{key%plain}#*
\pydatabuffervalue{value}#*
\pydatabufferkeyedefvalue{key%plain}{value}#*
\pydatabufferkeyvalue{key%plain}{value}#*
\begin{pydatabuffermlvalue}#*
\end{pydatabuffermlvalue}#*
\pydatabuffermlvalueopen#*
\pydatabuffermlvalueline{line}#*
\pydatabuffermlvalueclose#*

# deprecated
\pydatawritemlvaluestart#S
\pydatawritemlvalueend#S
\pydatabuffermlvaluestart#S
\pydatabuffermlvalueend#S
