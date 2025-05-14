# switch package
# Matthew Bertucci 2025/05/13 for v1.0

\newswitch{switch%cmd}{default code}#d
\addcase{switch}{case}{case code}

\switch_new:Nn %<⟨switch⟩%> {%<⟨default code⟩%>}#/%expl3
\switch_addcase:Nnn %<⟨switch⟩%> {%<⟨case⟩%>} {%<⟨case code⟩%>}#/%expl3
\switch_if_exist:NT %<⟨switch⟩%> {%<⟨true code⟩%>}#/%expl3
\switch_if_exist:NF %<⟨switch⟩%> {%<⟨false code⟩%>}#/%expl3
\switch_if_exist:NTF %<⟨switch⟩%> {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\switch_if_case_exist:NnT %<⟨switch⟩%> {%<⟨case⟩%>} {%<⟨true code⟩%>}#/%expl3
\switch_if_case_exist:NnF %<⟨switch⟩%> {%<⟨case⟩%>} {%<⟨false code⟩%>}#/%expl3
\switch_if_case_exist:NnTF %<⟨switch⟩%> {%<⟨case⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\switch_undefine:N %<⟨switch⟩%>#/%expl3
\switch_case_undefine:Nn %<⟨switch⟩%> {%<⟨case⟩%>}#/%expl3
