# upmethodology-extension package
# Matthew Bertucci 2022/04/21 for release 2022/02/10

#include:upmethodology-p-common

\Ifdefined{arg}{code}
\Ifelsedefined{arg}{true code}{false code}
\Ifundefined{arg}{code}
\Ifelseundefined{arg}{true code}{false code}
\Get{variable}
\GetLang{variable}{language}
\Set{variable}{name}
\Set[language]{variable}{name}
\Append{variable}{text}
\Append[language]{variable}{text}
\Unset{variable}
\Unset[language]{variable}
\DeclareCopyright{extname}{year}{copyrighter}{text}
\DeclareCopyright[language]{extname}{year}{copyrighter}{text}
\Put(x,y){stuff}#/picture
\UseExtension{extname}