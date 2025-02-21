# pegmatch package
# Matthew Bertucci 2025/02/16 for v2025B

\gTmpaSpeg
\gTmpbSpeg
\IfSpegExtractF{speg var}{string}{speg seq var}{false code}
\IfSpegExtractT{speg var}{string}{speg seq var}{true code}
\IfSpegExtractTF{speg var}{string}{speg seq var}{true code}{false code}
\IfSpegMatchF{speg var}{string}{false code}
\IfSpegMatchT{speg var}{string}{true code}
\IfSpegMatchTF{speg var}{string}{true code}{false code}
\lSpegTmpaSeq
\lSpegTmpbSeq
\lTmpaSpeg
\lTmpbSpeg
\MapSpegSeqInline{speg seq var}{code}
\NewSpeg{speg var%cmd}#d
\SetSpeg{speg var}{speg expr}
\SpegC{pattern}
\SpegCp
\SpegP{string}
\SpegQ{integer}
\SpegR{%<<X><Y><x><y>%>}
\SpegS{string}

# not documented
\ExtractSpeg{speg var}{string}{speg seq var}#*
\LogSpeg{speg var}#*
\MatchSpeg{speg var}{string}#*
\SetSpegTracing{keyvals}#*
\SpegAnd{pattern}{string}#*
\SpegChoice{pattern}{string}#*
\SpegConcat{pattern}{string}#*
\SpegNot{pattern}{string}#*
\SpegRepeat{pattern}{integer}{string}#*

#keyvals:\SetSpegTracing
+set
-set
+match
-match
all
none
#endkeyvals