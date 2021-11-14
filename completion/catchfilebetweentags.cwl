# catchfilebetweentags package
# Matthew Bertucci 11/13/2021 for v1.1

#include:etex
#include:etoolbox
#include:ltxcmds
#include:catchfile

\CatchFileBetweenTags{csname}{file}{tag}
\CatchFileBetweenTags*{csname}{file}{tag}

\ExecuteMetaData{tag}
\ExecuteMetaData[file]{tag}
\ExecuteMetaData*{tag}
\ExecuteMetaData*[file]{tag}

\CatchFileBetweenDelims{csname}{file}{start delim}{stop delim}
\CatchFileBetweenDelims{csname}{file}{start delim}{stop delim}[setup]