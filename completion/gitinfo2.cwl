# gitinfo2 package
# Matthew Bertucci 12/12/2021 for v2.0.7

#include:etoolbox
#include:xstring
#include:kvoptions
#include:eso-pic

#keyvals:\usepackage/gitinfo2#c
local
grumpy
missing=%<text%>
notags=%<text%>
dirty=%<text%>
maxdepth=%<integer%>
mark
markifdraft
markifdirty
marknotags
raisemark=##L
pcount
#endkeyvals

\gitReferences
\gitBranch
\gitDirty
\gitAbbrevHash
\gitHash
\gitAuthorName
\gitAuthorEmail
\gitAuthorDate
\gitAuthorIsoDate
\gitAuthorUnixDate
\gitCommitterName
\gitCommitterEmail
\gitCommitterDate
\gitCommitterIsoDate
\gitCommitterUnixDate
\gitVtag
\gitVtags
\gitVtagn
\gitFirstTagDescribe
\gitRel
\gitRels
\gitReln
\gitRoff
\gitTags
\gitDescribe

\gitMark#*
\gitMarkFormat#*
\gitMarkPref#*
\gitWrapEmail{email}#*