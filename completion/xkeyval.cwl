# xkeyval package
# Matthew Bertucci 10/14/2021 for v2.8

\setkeys{families}{keyvals}#*
\setkeys[prefix]{families}[ignored keys]{keyvals}#*
\setkeys*{families}{keyvals}#*
\setkeys*[prefix]{families}[ignored keys]{keyvals}#*
\setrmkeys{families}#*
\setrmkeys[prefix]{families}[ignored keys]#*
\setrmkeys*{families}#*
\setrmkeys*[prefix]{families}[ignored keys]#*
\setkeys+{families}{keyvals}#*
\setkeys+[prefix]{families}[ignored keys]{keyvals}#*
\setkeys*+{families}{keyvals}#*
\setkeys*+[prefix]{families}[ignored keys]{keyvals}#*
\setrmkeys+{families}#*
\setrmkeys+[prefix]{families}[ignored keys]#*
\setrmkeys*+{families}#*
\setrmkeys*+[prefix]{families}[ignored keys]#*

\savevalue{key%plain}#*
\gsavevalue{key%plain}#*

\savekeys{family}{keyvals}#*
\savekeys[prefix]{family}{keyvals}#*
\gsavekeys{family}{keyvals}#*
\gsavekeys[prefix]{family}{keyvals}#*
\delsavekeys{family}{keyvals}#*
\delsavekeys[prefix]{family}{keyvals}#*
\gdelsavekeys{family}{keyvals}#*
\gdelsavekeys[prefix]{family}{keyvals}#*
\unsavekeys{family}#*
\unsavekeys[prefix]{family}#*
\gunsavekeys{family}#*
\gunsavekeys[prefix]{family}#*

\global{key%plain}#*
\usevalue{key%plain}#*

\presetkeys{family}{head keys}{tail keys}#*
\presetkeys[prefix]{family}{head keys}{tail keys}#*
\gpresetkeys{family}{head keys}{tail keys}#*
\gpresetkeys[prefix]{family}{head keys}{tail keys}#*
\delpresetkeys{family}{head keys}{tail keys}#*
\delpresetkeys[prefix]{family}{head keys}{tail keys}#*
\gdelpresetkeys{family}{head keys}{tail keys}#*
\gdelpresetkeys[prefix]{family}{head keys}{tail keys}#*
\unpresetkeys{family}#*
\unpresetkeys[prefix]{family}#*
\gunpresetkeys{family}#*
\gunpresetkeys[prefix]{family}#*

\DeclareOptionX{key%plain}{function}#*
\DeclareOptionX[prefix]<family>{key%plain}[default]{function}#*
\DeclareOptionX*{function}#*
\ExecuteOptionsX{keyvals}#*
\ExecuteOptionsX[prefix]<families>[ignored keys]{keyvals}#*
\ProcessOptionsX#*
\ProcessOptionsX[prefix]<families>[ignored keys]#*
\ProcessOptionsX*#*
\ProcessOptionsX*[prefix]<families>[ignored keys]#*
