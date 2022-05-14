# mkstmp_pro package
# Matthew Bertucci 2022/05/13 for v1.1

#include:aeb_pro
#include:xkeyval

\setStampPath{path%definition}
\makeStamps{{name=%<name1%>,page=%<page1%>}{name=%<name2%>,page=%<page2%>}%<...%>}

\definePath{cmd}{path%definition}#*d
\predocassemJS#*