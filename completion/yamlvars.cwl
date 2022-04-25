# yamlvars package
# Matthew Bertucci 4/24/2022 for release 2022-04-16

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
\lowercasevarYVon
\lowercasevarYVoff

\begin{parseYAMLpdfdata}
\end{parseYAMLpdfdata}
