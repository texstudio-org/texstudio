# llncsconf package
# Matthew Bertucci 3/27/2022 for v1.1.0

#include:hyperref
#include:ifthen

#keyvals:\usepackage/llncsconf#c
crop
rcsinfo
svninfo
accepted
submitted
intended
llncs
proceedings
#endkeyvals

#ifOption:rcsinfo
#include:rcsinfo
#endif

#ifOption:svninfo
#include:eso-pic
#include:svninfo
#endif

\conference{conference name%text}
\llncs{text}{page number}
\llncsdoi{DOI}