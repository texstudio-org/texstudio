# phonrule package
# Matthew Bertucci 11/18/2021 for v1.3.2

\phon{input}{output}
\phonc{input}{output}{context}
\phonl{input}{output}{context}
\phonr{input}{output}{context}
\phonb{input}{output}{context}
\oneof{contexts}
\oneof[alignment%keyvals]{contexts}
\phonfeat{features}
\phonfeat[alignment%keyvals]{features}
#keyvals:\oneof,\phonfeat
c
l
r
#endkeyvals
\phold
\env{output}{env}
\envl{output}{env}
\envr{output}{env}
\envb{output}{env}
\env*{output}{env}
\envl*{output}{env}
\envr*{output}{env}
\envb*{output}{env}