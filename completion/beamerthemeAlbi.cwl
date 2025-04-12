# Albi beamertheme
# Matthew Bertucci 2025/04/09 for v1.5

#include:pgfopts
#include:etoolbox
#include:tikz

\Albikeys{keyvals}

#keyvals:\usetheme/Albi#c,\Albikeys
compactfootline#true,false
compacttitle#true,false
partpage#true,false
sectionpage#true,false
compress#true,false
#endkeyvals

#keyvals:\Albikeys
all logos={%<graphics code%>}
footline logo={%<graphics code%>}
logo={%<graphics code%>}
part logo={%<graphics code%>}
section logo={%<graphics code%>}
other logos list={%<file1,file2,...%>}
#endkeyvals

albi blue#B
albi dark #B
albi black#B
albi gray#B
albi silver#B
albi orange#B
albi red#B
albi yellow#B
albi cyan#B
albi green#B

\Albisetlogofilename{imagefile}#g
\Albiotherlogoslist{file1,file2,...}

# not documented
\insertslidenumberifuseful#S
\insertpartnameandnumber#S