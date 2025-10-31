# xpeekahead package
# Matthew Bertucci 2025/10/24 for v1.3

\xpeekahead_set:NnTF {%<⟨command⟩%>} {%<⟨regex⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\xpeekahead_set:NnT {%<⟨command⟩%>} {%<⟨regex⟩%>} {%<⟨true code⟩%>}#/%expl3
\xpeekahead_set:NnF {%<⟨command⟩%>} {%<⟨regex⟩%>} {%<⟨false code⟩%>}#/%expl3
\xpeekahead_gset:NnTF {%<⟨command⟩%>} {%<⟨regex⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\xpeekahead_gset:NnT {%<⟨command⟩%>} {%<⟨regex⟩%>} {%<⟨true code⟩%>}#/%expl3
\xpeekahead_gset:NnF {%<⟨command⟩%>} {%<⟨regex⟩%>} {%<⟨false code⟩%>}#/%expl3
\xpeekahead_set:NNTF {%<⟨command⟩%>} %<⟨regex var⟩%> {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\xpeekahead_set:NNT {%<⟨command⟩%>} %<⟨regex var⟩%> {%<⟨true code⟩%>}#/%expl3
\xpeekahead_set:NNF {%<⟨command⟩%>} %<⟨regex var⟩%> {%<⟨false code⟩%>}#/%expl3
\xpeekahead_gset:NNTF {%<⟨command⟩%>} %<⟨regex var⟩%> {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\xpeekahead_gset:NNT {%<⟨command⟩%>} %<⟨regex var⟩%> {%<⟨true code⟩%>}#/%expl3
\xpeekahead_gset:NNF {%<⟨command⟩%>} %<⟨regex var⟩%> {%<⟨false code⟩%>}#/%expl3
\xpeekahead_cmd_peek:N %<⟨command⟩%>#/%expl3
\xpeekahead_cmd_peek:nTF {%<⟨regex⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\xpeekahead_cmd_peek:nT {%<⟨regex⟩%>} {%<⟨true code⟩%>}#/%expl3
\xpeekahead_cmd_peek:nF {%<⟨regex⟩%>} {%<⟨false code⟩%>}#/%expl3
\xpeekahead_cmd_peek:NTF %<⟨regex var⟩%> {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\xpeekahead_cmd_peek:NT %<⟨regex var⟩%> {%<⟨true code⟩%>}#/%expl3
\xpeekahead_cmd_peek:NF %<⟨regex var⟩%> {%<⟨false code⟩%>}#/%expl3
\xpeekahead_env_set:nN {%<⟨envname⟩%>} {%<⟨command⟩%>}#/%expl3
\xpeekahead_env_set:nnTF {%<⟨envname⟩%>} {%<⟨regex⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\xpeekahead_env_set:nnT {%<⟨envname⟩%>} {%<⟨regex⟩%>} {%<⟨true code⟩%>}#/%expl3
\xpeekahead_env_set:nnF {%<⟨envname⟩%>} {%<⟨regex⟩%>} {%<⟨false code⟩%>}#/%expl3
\xpeekahead_env_set:nNTF {%<⟨envname⟩%>} %<⟨regex var⟩%> {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\xpeekahead_env_set:nNT {%<⟨envname⟩%>} %<⟨regex var⟩%> {%<⟨true code⟩%>}#/%expl3
\xpeekahead_env_set:nNF {%<⟨envname⟩%>} %<⟨regex var⟩%> {%<⟨false code⟩%>}#/%expl3

\xpeekSetCmd{command}{regex}{true code}{false code}#d
\xpeekSetCmdGlobal{command}{regex}{true code}{false code}#d
\xpeekTokCmd{command%plain}
\xpeekTok{regex}{true code}{false code}
\xpeekEnvCmd{envname}{command%plain}
\xpeekEnv{envname}{regex}{true code}{false code}