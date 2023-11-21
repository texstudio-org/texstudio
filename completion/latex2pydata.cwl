# latex2pydata package
# Matthew Bertucci 2023/11/21 for v0.1

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
\pydatawritekeyvalue{key%plain}{value}#*
\begin{pydatawritemlvalue}#*
\end{pydatawritemlvalue}#*
\pydatasetbuffername{buffername}#*
\pydataclearbuffername{buffername}#*
\pydatabuffermdfivesum#*
\pydatawritebuffer#*
\pydatabufferkey{key%plain}#*
\pydatabuffervalue{value}#*
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