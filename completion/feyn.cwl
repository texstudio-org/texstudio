# feyn package
# Matthew Bertucci 2022/07/26 for v0.4.3

#keyvals:\usepackage/feyn#c
globalbang
noglobalbang
#endkeyvals

\feyn{chars}#m
\Feyn{chars}#m
\FEYN{chars}#m

\momentum{chars}{text}
\momentum[pos%keyvals]{chars}{text}
#keyvals:\momentum
top
urt
lrt
bot
llft
ulft
#endkeyvals

\belowl{chars}#m
\belowr{chars}#m

\Diagram{array}#m
\Diagram[alignment%keyvals]{array}#m
\DIAGRAM{array}#m
\DIAGRAM[alignment%keyvals]{array}#m
#keyvals:\Diagram,\DIAGRAM
bottom
centre
#endkeyvals

\maxis{arg}#m
\vertexlabel#m
\feynstrut{height}{depth}#m
\annotate{x}{y}{text}#m
\tannotate{x}{y}{text}#m

\FeynSpaceChar#*m
\FeynxSpaceChar#*m

\wfermion#m
\hfermion#m
\shfermion#m
\whfermion#m
\gvcropped#m
\bigbosonloop#m
\smallbosonloop#m
\bigbosonloopA#m
\smallbosonloopA#m
\bigbosonloopV#m
\smallbosonloopV#m
