# crumbs package
# Matthew Bertucci 2026/10/16 for v0.4.2

#include:etoolbox

#keyvals:\usepackage/crumbs#c
dry
increment
#endkeyvals

\crumbs
\subcrumbs

\crumbection{title}#*L2
\crumbection[short title]{title}#*L2
\subcrumbection{title}#*L2
\subcrumbection[short title]{title}#*L2
\crumb{arg1}{arg2}#*
\subcrumb{arg1}{arg2}#*
\thecrumbi#S
\thesubcrumbi#S