# selinput package
# Matthew Bertucci 1/4/2022 for v1.6

#include:inputenc
#include:kvsetkeys
#include:stringenc
#include:kvoptions

#keyvals:\usepackage/selinput#c
warning
ucs
utf8=%<file name%>
#endkeyvals

\SelectInputEncodingList{encoding list}
\SelectInputMappings{mapping pairs}

\SelectInputDefineMapping{arg}#*