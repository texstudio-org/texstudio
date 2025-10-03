# xpeekahead package
# Matthew Bertucci 2025/09/17 for v1.0

\xpeekahead_set:Nnnn {%<⟨command⟩%>} {%<⟨regex⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\xpeekahead_gset:Nnnn {%<⟨command⟩%>} {%<⟨regex⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\xpeekahead_cmd_peek:N {%<⟨command⟩%>}#/%expl3
\xpeekahead_cmd_peek:nnn {%<⟨regex⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\xpeekahead_env_set:nN {%<⟨envname⟩%>} {%<⟨command⟩%>}#/%expl3
\xpeekahead_env_set:nnnn {%<⟨envname⟩%>} {%<⟨regex⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3

\xpeekSetCmd{command}{regex}{true code}{false code}#d
\xpeekSetCmdGlobal{command}{regex}{true code}{false code}#d
\xpeekTokCmd{command%plain}
\xpeekTok{regex}{true code}{false code}
\xpeekEnvCmd{envname}{command%plain}
\xpeekEnv{envname}{regex}{true code}{false code}