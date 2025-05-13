# switch package
# Matthew Bertucci 2025/05/13 for v1.0

\newswitch{switch%cmd}{default code}#d
\addcase{switch}{case}{case code}

\switch_new:Nn %<⟨switch⟩%> {%<⟨default code⟩%>}#/%expl3
\switch_addcase:Nnn %<⟨switch⟩%> {%<⟨case⟩%>} {%<⟨case code⟩%>}#/%expl3