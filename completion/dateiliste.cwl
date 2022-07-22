# dateiliste package
# Matthew Bertucci 2022/07/20 for v0.6

#include:rcsinfo
#include:ltxtable

#keyvals:\usepackage/dateiliste#c
addmain
noaddmain
cat12
nocat12
showpages
noshowpages
svn
subversion
cvs
rcs
#endkeyvals

#ifOption:svn
#include:svninfo
#endif
#ifOption:subversion
#include:svninfo
#endif

\ProvideFileInfos{id-string}{description%text}
\mainFileToList
\printFileList
\printFileList[section command]

\fileListName#*
\fileListPreamble#*
\fileNameName#*
\dateName#*
\verName#*
\descriptionName#*
\pageName#*

\afterfi{cmd}#S