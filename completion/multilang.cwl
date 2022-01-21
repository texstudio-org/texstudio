# multilang package
# Matthew Bertucci 1/20/2022 for v0.9b

#include:environ
#include:etoolbox
#include:pgfkeys
#include:pgfopts

#keyvals:\usepackage/multilang#c
languages={%<lang1,lang2,...%>}
#endkeyvals

\NewMultilangCmd{command}{options%keyvals}#d

#keyvals:\NewMultilangCmd#c
command=%<command%>
margs={%<arg1,arg2,...%>}
oargs={%<arg1,arg2,...%>}
starred#true,false
disablable#true,false
defaults={%<arg1=val1,arg2=val2,...%>}
alias/%<name%>={%<arg1,arg2,...%>}
#endkeyvals

\NewMultilangEnv{envname}{options%keyvals}#N

#keyvals:\NewMultilangEnv#c
environment=%<environment%>
margs={%<arg1,arg2,...%>}
oargs={%<arg1,arg2,...%>}
disablable#true,false
defaults={%<arg1=val1,arg2=val2,...%>}
alias/%<name%>={%<arg1,arg2,...%>}
#endkeyvals

\NewMultilangType{type name}{format%definition}
\NewMultilangType[arg count]{type name}{format%definition}