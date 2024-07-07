# sepfootnotes package
# Matthew Bertucci 2024/07/07 for v0.3d

#keyvals:\usepackage/sepfootnotes#c
quiet
warn
error
global
after
#endkeyvals

\sepfootnotecontent{key%specialDef}{content%text}#s#%sepfootnotekey
\sepfootnote{key%keyvals}
\sepfootnotemark{key%keyvals}
\sepfootnotetext{key%keyvals}
\printsepfootnote{key%keyvals}
\sepfootquicknote{content%text}

#keyvals:\sepfootnote#c,\sepfootnotemark#c,\sepfootnotetext#c,\printsepfootnote#c
%sepfootnotekey
#endkeyvals

\newfootnotes{prefix}
\newfootnotes*{prefix}
\newsymbolfootnotes{prefix}
\newsymbolfootnotes[counter]{prefix}
\newendnotes{prefix}
\newcommentnotes{prefix}
\newsymbolcommentnotes{prefix}
\newsymbolcommentnotes[counter]{prefix}
