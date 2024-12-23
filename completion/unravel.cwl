# unravel package
# muzimuzhi/1 Nov 2019 for unravel v0.2g

#include:gtl

\unravel{code}
\unravel[keyvals]{code}
\unravelsetup{keyvals}

#keyvals:\unravel,\unravelsetup
explicit-prompt#true,false
internal-debug#true,false
machine
max-action=%<integer%>
max-output=%<integer%>
max-input=%<integer%>
mute
number-steps#true,false
online=%<integer%>
prompt-input={%<item1,item2,...%>}
trace-assigns#true,false
trace-expansion#true,false
trace-other#true,false
welcome-message#true,false
#endkeyvals

# expl3 interface
\unravel:nn {%<⟨keyvals⟩%>} {%<⟨code⟩%>}#/%expl3
\unravel_get:nnN {%<⟨keyvals⟩%>} {%<⟨code⟩%>} %<⟨tl var⟩%>#/%expl3
\unravel_setup:n {%<⟨keyvals⟩%>}#/%expl3