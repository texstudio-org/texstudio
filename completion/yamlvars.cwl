# yamlvars package
# Matthew Bertucci 2023/11/27

#include:luacode
#include:etoolbox
#include:luakeys
#include:penlightplus

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

# not documented
\TextualYV#S
\setYAMLvars{arg}#S
\setYAMLvars*{arg}#S
\setdefYAMLvars{arg}#S
\yamlvarsdebugon#S
\yamlvarsdebugoff#S
