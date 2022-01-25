# YAMLvars package
# Matthew Bertucci 12/18/2021

#include:luacode
#include:xspace
#include:etoolbox
#include:penlight

#keyvals:\usepackage/YAMLvars#c
useyv
parseCLI
allowundeclared
overwritedefs
debug
#endkeyvals

#ifOption:useyv
\yv{var}
#endif

\begin{declareYAMLvars}
\end{declareYAMLvars}
\begin{parseYAMLvars}
\end{parseYAMLvars}

\declareYAMLvarsFile{file}
\parseYAMLvarsFile{file}

\resetYAMLvarsspec
\AllowUndeclaredYV
