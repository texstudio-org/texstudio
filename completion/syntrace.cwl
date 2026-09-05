# syntrace package
# Matthew Bertucci 2026/09/04 for v1.1

#include:ifthen
#include:synttree

#keyvals:\usepackage/syntrace#c
synttree
qtree
i-start
#endkeyvals

#ifOption:qtree
#include:qtree
#endif

\traceLabel{label%specialDef}#s#%syntrace-label
\traceReference{syntrace-label%special}
\syntraceaddresetmacro{csname}
\syntraceremoveresetmacro{csname}#*


