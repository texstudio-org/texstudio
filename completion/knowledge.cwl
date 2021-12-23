# knowledge package
# Matthew Bertucci 12/23/2021 for v1.26

#include:l3keys2e
#include:etoolbox
#include:xparse
#keyvals:\usepackage/knowledge#c
paper
electronic
composition
hyperref
hyperref=#active,inactive,compatibility,auto
xcolor
xcolor=#active,inactive,compatibility,auto
makeidx
makeidx=#active,inactive,compatibility,auto
#endkeyvals

\knowledgeconfigure{directives%keyvals}

#keyvals:\knowledgeconfigure,\usepackage/knowledge#c
diagnose bar#true,false
diagnose help#true,false
diagnose line#true,false
fix hyperref twocolumn
label scope#true,false
notion
protect quotation={%<env1,env2,...%>}
protect link
unprotect link
quotation
silent
strict
visible anchor points#true,false
no patch
#endkeyvals

\knowledge{knowledge name}{directives%keyvals}
\knowledge{knowledge name}[synonym1|synonym2|...]{directives%keyvals}
\knowledgestyle{style name}{keyvals}
\knowledgestyle*{style name}{keyvals}
\knowledgedirective{name}[optional parameter]{keyvals}
\knowledgedirective*{name}[optional parameter]{keyvals}
\knowledgedefault{keyvals}
\knowledgedefault*{keyvals}

#keyvals:\knowledge#c,\knowledgestyle#c,\knowledgestyle*#c,\knowledgedirective#c,\knowledgedirective*#c
also now
autoref
autoref link
autoref target
autorefhere
boldface
detokenize
emphasize
ensuretext
ensuremath
export=%<file%>
invisible
italic
fbox
md
notion
index=
index key=
index style=
index parent key=
intro style=%<knowledge style%>
invisible
italic
link=%<knowledge%>
link scope=%<label%>
lowercase
mathord
mathop
mathbin
mathrel
mathopen
mathclose
mathpunct
namespace=
now
remove space
scope=%<name%>
smallcaps
style=%<knowledge style%>
synonym
text=%<text%>
remove space
typewriter
underline
up
uppercase
wrap=%<macro%>
#endkeyvals

\kl{text}
\kl(scope){text}
\kl[knowledge name]{text}
\kl(scope)[knowledge name]{text}

\knowledgenewvariant{command}{directives%keyvals}#d
\knowledgesetvariant{command}{directives%keyvals}#d

#keyvals:\knowledgenewvariant,\knowledgesetvariant
namespace=%<string%>
default style={%<style list%>}
unknown style={%<style list%>}
unknown style cont={%<style list%>}
style directive={%<directive list%>}
auto knowledge={%<directives%>}
unknown warning#true,false
unknown diagnose#true,false
suggestion={%<directives%>}
PDF string={%<code%>}
display code={%<code%>}
#endkeyvals

\knowledgevariantmodifier{variant1*variant2*...}{command}

\begin{scope}
\end{scope}
\knowledgescope{scope name}
\knowledgeimport{scope1,scope2,...}
\knowledgeconfigureenvironment{env1,env2,...}{keyvals}

#keyvals:\knowledgeconfigureenvironment#c
scope#true,false
label=#none,accepts
environment#true,false
autoclose#true,false
parents={%<area1,area2,...%>}
push code={%<code%>}
pop code={%<code%>}
occurrences=#once,multiple,recursive
forces=%<area%>
knowledge=%<knowledge%>
#endkeyvals

#ifOption:hyperref
#include:hyperref
#keyvals:\knowledgeconfigure,\usepackage/knowledge#c
ref=%<label%>
protect link
url=%<URL%>
anchor point color=#%color
AP color=#%color
anchor point shape=%<shape%>
AP shape=%<shape%>
anchor point shift={%<x,y%>}
AP shift={%<x,y%>}
#endkeyvals
#endif
#ifOption:hyperref=active
#include:hyperref
#keyvals:\knowledgeconfigure,\usepackage/knowledge#c
ref=%<label%>
protect link
url=%<URL%>
anchor point color=#%color
AP color=#%color
anchor point shape=%<shape%>
AP shape=%<shape%>
anchor point shift={%<x,y%>}
AP shift={%<x,y%>}
#endkeyvals
#endif

\intro{knowledge}
\intro[knowledge name]{knowledge}
\intro*{knowledge}
\intro*[knowledge name]{knowledge}
\phantomintro{knowledge}
\phantomintro(label){knowledge}
\nointro{knowledge}
\reintro{knowledge}
\reintro[knowledge name]{knowledge}
\reintro*{knowledge}
\reintro*[knowledge name]{knowledge}

\AP
\itemAP

#ifOption:xcolor
#include:xcolor
#keyvals:\knowledgeconfigure,\usepackage/knowledge#c
color=#%color
cyclic color={%<color1,color2,...%>}
colorbox=#%color
#endkeyvals
#endif
#ifOption:xcolor=active
#include:xcolor
#keyvals:\knowledgeconfigure,\usepackage/knowledge#c
color=#%color
cyclic color={%<color1,color2,...%>}
colorbox=#%color
#endkeyvals
#endif

#ifOption:makeidx
#include:makeidx
#endif
#ifOption:makeidx=active
#include:makeidx
#endif

\knowledgepackagemode#*
\IfKnowledgePaperModeTF{true}{false}#*
\ifKnowledgePaperMode#*
\IfKnowledgeElectronicModeTF{true}{false}#*
\ifKnowledgeElectronicMode#*
\IfKnowledgeCompositionModeTF{true}{false}#*
\ifKnowledgeCompositionMode#*
