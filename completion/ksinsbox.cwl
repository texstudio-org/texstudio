# ksinsbox package
# Matthew Bertucci 2023/01/20 for v0.1

# loads insbox.tex

\ksinsbox{content%text}
\ksinsbox[pos%keyvals]{content%text}
\ksinsbox[pos%keyvals][number]{content%text}

#keyvals:\ksinsbox
l
c
r
#endkeyvals

# from insbox.tex
\InsertBoxL{lines}{content%text}
\InsertBoxL{lines}{content%text}[correction]
\InsertBoxR{lines}{content%text}
\InsertBoxR{lines}{content%text}[correction]
\InsertBoxC{lines}{content%text}
\InsertBoxC{lines}{content%text}[correction]
\MoveBelowBox
\ParShape#S