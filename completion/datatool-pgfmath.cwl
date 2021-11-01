# datatool-pgfmath package
# Matthew Bertucci 10/31/2021 for v2.32

#include:xkeyval
#include:pgfrcs
#include:pgfkeys
#include:pgfmath
#include:datatool-base

\dtlifnumeq{num1}{num2}{true case}{false case}#*
\dtlifnumlt{num1}{num2}{true case}{false case}#*
\dtlifnumgt{num1}{num2}{true case}{false case}#*
\dtlifnumopenbetween{num}{min}{max}{true case}{false case}#*
\dtlifnumclosedbetween{num}{min}{max}{true case}{false case}#*
\dtladd{cmd}{num1}{num2}#*d
\dtlsub{cmd}{num1}{num2}#*d
\dtlmul{cmd}{num1}{num2}#*d
\dtldiv{cmd}{num1}{num2}#*d
\dtlroot{cmd}{num}#*d
\dtlround{cmd}{num}{digits}#*d
\dtltrunc{cmd}{num}{digits}#*d
\dtlclip{cmd}{num}#*d
\dtlmin{cmd}{num1}{num2}#*d
\dtlmax{cmd}{num1}{num2}#*d
\dtlabs{cmd}{num}#*d
\dtlneg{cmd}{num}#*d