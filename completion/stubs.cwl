# stubs package
# Matthew Bertucci 4/18/2022 for v0.1.1

#include:textpos
#include:graphicx

#keyvals:\usepackage/stubs#c
addmargin
#endkeyvals

\stubs{width}{text front%text}
\stubs{width}[text back%text]{text front%text}
\stubs[number]{width}{text front%text}
\stubs[number]{width}[text back%text]{text front%text}

\stublmargin#*
\stubrmargin#*
\stubbmargin#*