# histrings package
# Matthew Bertucci 2026/09/10 for v1.1.0

#include:etoolbox

\cardinaltext{number}#*
\sepdolistcsloop{sep}{mid}{last}{listcs}#*
\sepdolistloop{sep}{mid}{last}{listcs}#*
\sepforlistcsloop{handler}{sep}{mid}{last}{list}#*
\sepforlistloop{handler}{sep}{mid}{last}{list}#*

# not documented
\spcappto{arg1}{arg2}#S