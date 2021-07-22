# knowledge package
# Matthew Bertucci 7/22/2021

\knowledgeconfigure{keyvals}

#keyvals:\knowledgeconfigure
diagnose bar#true,false
diagnose help#true,false
diagnose line#true,false
fix hyperref twocolumn
label scope#true,false
notion
protect quotation=%<{env1,env2,...}%>
protect link
unprotect link
quotation
silent
strict
visible anchor points#true,false
no patch
#endkeyvals

\knowledge{knowledge name}[synonym1|synonym2|...]{keyvals}
\knowledgestyle{style name}{keyvals}
\knowledgestyle*{style name}{keyvals}
\knowledgedirective{name}[optional parameter]{keyvals}
\knowledgedirective*{name}[optional parameter]{keyvals}
\knowledgedefault{keyvals}
\knowledgedefault*{keyvals}

#keyvals:\knowledge#c,\knowledgestyle#c,\knowledgestyle*#c,\knowledgedirective#c,\knowledgedirective*#c
autoref
autoref link
autoref target
autorefhere
boldface
color=
colorbox=
cyclic color
detokenize
emphasize
ensuretext
ensuremath
export=
invisible
italic=
fbox
md
notion
index=
index key=
index style=
index parent key=
intro style=
italic
link=
link scope=
lowercase
mathord
mathop
mathbin
mathrel
mathopen
mathclose
mathpunct
protect link
ref=
scope=
smallcaps
style=
synonym
text=
remove space
typewriter
underline
up
uppercase
url=
wrap=
#endkeyvals

\kl(optional scope)[optional knowledge name]{text}

\knowledgenewvariant{command}{keyvals}
\knowledgesetvariant{command}{keyvals}

#keyvals:\knowledgenewvariant,\knowledgesetvariant
namespace=
default style=
unknown style=
unknown style cont=
style directive=
auto knowledge=
unknown warning#true,false
unknown diagnose#true,false
suggestion=
PDF string=
#endkeyvals

\knowledgevariantmodifier{variant1*variant2*...}{command}

\begin{scope}
\end{scope}
\knowledgescope{scope name}
\knowledgeimport{label}
\knowledgeconfigureenvironment{env1,env2,...}{keyvals}

#keyvals:\knowledgeconfigureenvironment#c
scope#true,false
label=#none,accepts
environment#true,false
autoclose#true,false
parents=
push code=
pop code=
occurrences=
forces=
#endkeyvals

#ifOption:hyperref
#include:hyperref
#endif
#ifOption:hyperref=active
#include:hyperref
#endif

\intro(optional scope)[optional knowledge name]{command}
\intro*(optional scope)[optional knowledge name]{command}
\phantomintro(optional label){command}
\nointro{command}
\reintro[optional knowledge name]{command}
\reintro*[optional knowledge name]{command}

\AP
\itemAP

#ifOption:xcolor
#include:xcolor
#endif
#ifOption:xcolor=active
#include:xcolor
#endif

#ifOption:makeidx
#include:makeidx
#endif
#ifOption:makeidx=active
#include:makeidx
#endif

\knowledgepackagemode#*
\IfKnowledgePaperModeTF#*
\ifKnowledgePaperMode#*
\IfKnowledgeElectronicModeTF#*
\ifKnowledgeElectronicMode#*
\IfKnowledgeCompositionModeTF#*
\ifKnowledgeCompositionMode#*