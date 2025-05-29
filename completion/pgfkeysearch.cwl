# pgfkeysearch package
# Matthew Bertucci 2025/05/29 for v1.4

\pgfkeysearchsettings{keyvals}#*

#keyvals:\usepackage/pgfkeysearch#c,\pgfkeysearchsettings
root search#true,false
#endkeyvals

\pgfkeysearch{path-list}{key%plain}{macro%cmd}#*d
\pgfkeysearchvalueof{path-list}{key%plain}{macro%cmd}#*d
\pgfkeysearchTF{path-list}{key%plain}{macro%cmd}{if-found}{if-not}#*d
\pgfkeysearchvalueofTF{path-list}{key%plain}{macro%cmd}{if-found}{if-not}#*d
