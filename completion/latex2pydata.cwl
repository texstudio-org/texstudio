# latex2pydata package
# Matthew Bertucci 2024/05/20 for v0.2.0

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

# not documented
\pydatawritemlvaluestart#S
\pydatawritemlvalueline#S
\pydatawritemlvalueend#S
\pydatabuffermlvaluestart#S
\pydatabuffermlvalueline{arg}#S
\pydatabuffermlvalueend#S
