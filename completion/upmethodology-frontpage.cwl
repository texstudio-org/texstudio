# upmethodology-frontpage package
# Matthew Bertucci 2022/04/21 for release 2022/02/10

#include:upmethodology-p-common
#include:upmethodology-extension
#include:upmethodology-document

#keyvals:\usepackage/upmethodology-frontpage#c
french
francais
english
#endkeyvals

\setfrontcover{layout name%keyvals}
#keyvals:\setfrontcover#c
classic
modern
#endkeyvals

\makefrontcover
\setfrontillustration{imagefile}#g
\setfrontillustration[scale]{imagefile}#g
\clearfrontillustration