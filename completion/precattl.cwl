# precattl package
# Matthew Bertucci 2025/05/09 for v0.0.0

\precattlExec{token list}
\precattlSet %<\tlvar%> {%<token list%>}
\precattlSet{cmd}{token list}#Sd

# expl3 interface
\precattl_exec:n {%<⟨token list⟩%>}#/%expl3
\precattl_set:Nn %<⟨tl var⟩%> {%<⟨token list⟩%>}#/%expl3

# not documented
\execinside{arg}#S
\execinsideSet{cmd}{arg}#Sd
\execinsideGset{cmd}{arg}#Sd
