# pgfkeysearch package
# Matthew Bertucci 2025/11/12 for v1.5

\pgfkeysearchsettings{keyvals}#*

#keyvals:\usepackage/pgfkeysearch#c,\pgfkeysearchsettings
root search#true,false
key=#value,macro
settings=#old,new
#endkeyvals

\pgfkeygetvalueof{path}{key%plain}{macro%cmd}#*d
\pgfkeyget{path}{key%plain}{macro%cmd}#*d
\pgfkeygetvalueofTF{path}{key%plain}{macro%cmd}{if-found}{if-not}#*d
\pgfkeygetTF{path}{key%plain}{macro%cmd}{if-found}{if-not}#*d

\pgfkeysearch{path-list}{key%plain}{macro%cmd}#*d
\pgfkeysearchvalueof{path-list}{key%plain}{macro%cmd}#*d
\pgfkeysearchTF{path-list}{key%plain}{macro%cmd}{if-found}{if-not}#*d
\pgfkeysearchvalueofTF{path-list}{key%plain}{macro%cmd}{if-found}{if-not}#*d
