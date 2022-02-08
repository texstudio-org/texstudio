# crumbs package
# Matthew Bertucci 2/7/2022 for v0.3.1

#include:xkeyval
#include:etoolbox
#include:catchfile

#keyvals:\usepackage/crumbs#c
dry
increment
#endkeyvals

\crumbs
\subcrumbs

\appendwrite#*
\appendtofile{file}{content}#*
\crumbection{title}#*L2
\crumbection[short title]{title}#*L2
\subcrumbection{title}#*L2
\subcrumbection[short title]{title}#*L2
\crumb{arg1}{arg2}#*
\subcrumb{arg1}{arg2}#*
\thecrumbi#*
\thesubcrumbi#*