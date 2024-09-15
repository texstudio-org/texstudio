# gitinfo-lua package
# Matthew Bertucci 2024/09/14 for v1.2.0

#include:luacode
#include:pgfopts

#keyvals:\usepackage/gitinfo-lua#c
contrib
alpha
authors
titlepage
rootdir
#endkeyvals

\gitdirectory{path%definition}
\gitunsetdirectory
\gitversion
\ifgitdirty{true code}{false code}
\gitdate
\gitauthor
\gitemail
\dogitauthors
\dogitauthors[conjunction]
\forgitauthors{csname}
\forgitauthors[conjunction]{csname}
\gitcommit{csname}{revision}
\gitcommit[format]{csname}{revision}
\forgitcommit{csname}{rev-spec}
\forgitcommit[format]{csname}{rev-spec}
\forgittag{csname}
\forgittag[format]{csname}
\forgittagseq{csname}
\gittag{csname}{tag}
\gittag[format]{csname}{tag}
