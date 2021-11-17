# tagging package
# Matthew Bertucci 11/16/2021 for v1.1.0.1

#include:etoolbox
#include:verbatim

\tagged{tag list}{source text}
\untagged{tag list}{alt text}
\iftagged{tag list}{source text}{alt text}

\begin{taggedblock}{tag list}
\end{taggedblock}
\begin{untaggedblock}{tag list}
\end{untaggedblock}

\usetag{tag list}

\droptag{tag list}

\taggedy#*
\taggedn#*