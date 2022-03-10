# YAMLvars package
# Matthew Bertucci 3/8/2022 for release 2022-03-03

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
\ForbidUndeclaredYV
