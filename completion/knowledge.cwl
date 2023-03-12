# knowledge package
# Matthew Bertucci 2/19/2022 for v1.28

#include:l3keys2e
#include:etoolbox
#include:currfile

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
cleveref
cleveref=#active,inactive,compatibility,auto
imakeidx
imakeidx=#active,inactive,compatibility,auto
#endkeyvals

\knowledgeconfigure{directives%keyvals}

#keyvals:\knowledgeconfigure#c,\usepackage/knowledge#c
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

#keyvals:\knowledgenewvariant#c,\knowledgesetvariant#c
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
#keyvals:\knowledgeconfigure#c,\usepackage/knowledge#c
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
#keyvals:\knowledgeconfigure#c,\usepackage/knowledge#c
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
\rekl{text}
\rekl(scope){text}
\rekl[knowledge name]{text}
\rekl(scope)[knowledge name]{text}

\AP
\itemAP

#ifOption:xcolor
#include:xcolor
#keyvals:\knowledgeconfigure#c,\usepackage/knowledge#c
color=#%color
cyclic color={%<color1,color2,...%>}
colorbox=#%color
#endkeyvals
#endif
#ifOption:xcolor=active
#include:xcolor
#keyvals:\knowledgeconfigure#c,\usepackage/knowledge#c
color=#%color
cyclic color={%<color1,color2,...%>}
colorbox=#%color
#endkeyvals
#endif

#ifOption:makeidx
#include:makeidx
#keyvals:\knowledge#c,\knowledgestyle#c,\knowledgestyle*#c,\knowledgedirective#c,\knowledgedirective*#c
index=%<text%>
index key=%<index key text%>
index parent key=%<index key%>
index style=%<csname%>
no index
#endkeyvals
\knowledgeIntroIndexStyle#*
#endif
#ifOption:makeidx=active
#include:makeidx
#keyvals:\knowledge#c,\knowledgestyle#c,\knowledgestyle*#c,\knowledgedirective#c,\knowledgedirective*#c
index=%<text%>
index key=%<index key text%>
index parent key=%<index key%>
index style=%<csname%>
no index
#endkeyvals
\knowledgeIntroIndexStyle#*
#endif

#ifOption:imakeidx
#include:imakeidx
#keyvals:\knowledge#c,\knowledgestyle#c,\knowledgestyle*#c,\knowledgedirective#c,\knowledgedirective*#c
index=%<text%>
index key=%<index key text%>
index parent key=%<index key%>
index style=%<csname%>
index name=%<name%>
no index
#endkeyvals
\knowledgeIntroIndexStyle#*
#endif
#ifOption:imakeidx=active
#include:imakeidx
#keyvals:\knowledge#c,\knowledgestyle#c,\knowledgestyle*#c,\knowledgedirective#c,\knowledgedirective*#c
index=%<text%>
index key=%<index key text%>
index parent key=%<index key%>
index style=%<csname%>
index name=%<name%>
no index
#endkeyvals
\knowledgeIntroIndexStyle#*
#endif

\kref{key}#r
\kpageref{key}#r

#ifOption:cleveref
#include:cleveref
\kcref{labellist}#r
\kCref{labellist}#r
\kcpageref{labellist}#r
\kCpageref{labellist}#r
\knamecref{key}#r
\knameCref{key}#r
\knamerefs{key}#r
\knamecrefs{key}#r
\knameCrefs{key}#r
#endif
#ifOption:cleveref=active
#include:cleveref
\kcref{labellist}#r
\kCref{labellist}#r
\kcpageref{labellist}#r
\kCpageref{labellist}#r
\knamecref{key}#r
\knameCref{key}#r
\knamerefs{key}#r
\knamecrefs{key}#r
\knameCrefs{key}#r
#endif

\knowledgenewrobustcmd{cmd}[args]{def}#*d
\knowledgenewcommand{cmd}[args]{def}#*d
\knowledgerenewcommand{cmd}[args]{def}#*
\KnowledgeNewDocumentCommand{cmd}{xargs}{def}#*d
\KnowledgeRenewDocumentCommand{cmd}{xargs}{def}#*
\KnowledgeProvideDocumentCommand{cmd}{xargs}{def}#*d
\KnowledgeDeclareDocumentCommand{cmd}{xargs}{def}#*d
\knowledgedeclarecommand{cmd}[args]{def}#*d
\knowledgenewmathcommand{cmd}[args]{def}#*d
\knowledgenewtextcommand{cmd}[args]{def}#*d
\knowledgerenewmathcommand{cmd}[args]{def}#*
\knowledgerenewtextcommand{cmd}[args]{def}#*
\knowledgedeclaremathcommand{cmd}[args]{def}#*d
\knowledgedeclaretextcommand{cmd}[args]{def}#*d
\KnowledgeNewDocumentMathCommand{cmd}{xargs}{def}#*d
\KnowledgeNewDocumentTextCommand{cmd}{xargs}{def}#*d
\KnowledgeRenewDocumentMathCommand{cmd}{xargs}{def}#*
\KnowledgeRenewDocumentTextCommand{cmd}{xargs}{def}#*
\KnowledgeProvideDocumentMathCommand{cmd}{xargs}{def}#*d
\KnowledgeProvideDocumentTextCommand{cmd}{xargs}{def}#*d
\KnowledgeDeclareDocumentMathCommand{cmd}{xargs}{def}#*d
\KnowledgeDeclareDocumentTextCommand{cmd}{xargs}{def}#*d
\knowledgenewcommandPIE{cmd}[args]{def}#*d
\knowledgerenewcommandPIE{cmd}[args]{def}#*
\knowledgedeclarecommandPIE{cmd}[args]{def}#*d
\knowledgenewmathcommandPIE{cmd}[args]{def}#*d
\knowledgerenewmathcommandPIE{cmd}[args]{def}#*
\knowledgedeclaremathcommandPIE{cmd}[args]{def}#*d
\KnowledgeNewDocumentCommandPIE{cmd}{xargs}{def}#*d
\KnowledgeRenewDocumentCommandPIE{cmd}{xargs}{def}#*
\KnowledgeDeclareDocumentCommandPIE{cmd}{xargs}{def}#*d
\KnowledgeProvideDocumentCommandPIE{cmd}{xargs}{def}#*d
\KnowledgeNewDocumentMathCommandPIE{cmd}{xargs}{def}#*d
\KnowledgeRenewDocumentMathCommandPIE{cmd}{xargs}{def}#*
\KnowledgeDeclareDocumentMathCommandPIE{cmd}{xargs}{def}#*d
\KnowledgeProvideDocumentMathCommandPIE{cmd}{xargs}{def}#*d

\withkl{cmd}{code}#*
\cmdkl{arg}#*

\knowledgepackagemode#*
\IfKnowledgePaperModeTF{true}{false}#*
\ifKnowledgePaperMode#*
\KnowledgePaperModetrue#*
\KnowledgePaperModefalse#*
\IfKnowledgeElectronicModeTF{true}{false}#*
\ifKnowledgeElectronicMode#*
\KnowledgeElectronicModetrue#*
\KnowledgeElectronicModefalse#*
\IfKnowledgeCompositionModeTF{true}{false}#*
\ifKnowledgeCompositionMode#*
\KnowledgeCompositionModetrue#*
\KnowledgeCompositionModefalse#*
  
\robustdisplay{arg}#*
\robustdisplaybracket{arg}#*
\knowledgeFixHyperrefTwocolumn#*

# miscellaneous undocumented commands
\KAuxActivate#*
\KAuxOpen#*
\KAuxClose#*
\IfKAuxReadyTF{true}{false}#*
\KAuxBefore{code}#*
\KAuxAfter{code}#*
\KAuxInit{code}#*
\NewKAuxCommand{cmd}{xargs}{def}#*d
\KAuxEOF{arg}#*
\KAuxCommand{cmd}{xargs}{def}#*d
\ActivateKAuxPhase{arg}#*
\DeclareKAuxPhaseCommand{cmd}{xargs}{def}#*d
\KAuxWriteLocation*
\KAuxWriteX{arg}*
\KAuxWriteX*{arg}*
\KAuxWrite{arg}*
\KAuxWrite*{arg}*
\KAuxFileAt{file}{line}*
\kauxCurrentFile*
\kauxCurrentLine*
\KAuxProcess{phase}*
\NewGBool{arg1}{arg2}*
\NewGBool{arg1}{arg2}[opt]*
\NewGBoolComplete{arg1}{arg2}{arg3}*
\NewGCs{arg1}{arg2}*
\NewGCs{arg1}{arg2}[opt]*
\NewGCsComplete{arg1}{arg2}{arg3}*
\OverloadCommand{cmd}{xargs}{def}#*d
\OverloadCommand{cmd}{xargs}[opt]{def}#*d
\ChooseCommand{arg1}{arg2}#*
\XparseArgs{arg1}{arg2}#*
\ExpXparseArgs{arg1}{arg2}#*
\KnowledgeConfigureBooleanOption{option}#*
\KnowledgeConfigureBooleanOption[default]{option}#*
\KnowledgeConfigureBooleanOptionTF{option}{true}{false}#*
\KnowledgeConfigureBooleanOptionTF[default]{option}{true}{false}#*
\KnowledgeConfigureTrigger{trigger}{def}#*
\KnowledgeConfigureTrigger[opt]{trigger}{def}#*
\KnowledgePackageTrigger{trigger}{def}#*
\KnowledgePackageBooleanOption{arg}#*
\KnowledgePackageBooleanOption[opt]{arg}#*
\ScopeConfigure{envname}{options}#*
\KAuxUndeclaredScopeTag{arg}#*
\KAuxDeclaredScopeTag{arg}#*
\KAuxNewLinkScopetagInstance{arg1}{arg2}#*
\KAuxScopeNewInstance{arg1}{arg2}{arg3}#*
\KAuxScopeTag{arg1}{arg2}#*
\KnowledgeConfigureEnvironment{env1,env2,...}{keyvals}#*
\ScopeHackEnvironments#*
\ScopeActivate#*
\KnowledgeDiagnoseOutput#*
\NewKnowledgeParamBool{param}{bool}#*
\NewKnowledgeParamBool*{param}{bool}#*
\KnowledgeTransferBool{arg}#*
\NewKnowledgeParamTl{param}#*
\NewKnowledgeParamTl[opt]{param}#*
\NewKnowledgeParamTl*{param}#*
\NewKnowledgeParamTl*[opt]{param}#*
\KnowledgeTransferTl{arg}#*
\NewKnowledgeParamCode{arg1}{arg2}#*
\NewKnowledgeParamPackageError{arg1}{arg2}#*
\KAuxKnowledge{arg1}{arg2}{arg3}{arg4}#*
\knowledgeusestyle{arg1}{arg2}#*
\KAuxErrorKnowledgeRecursive{arg1}{arg2}{arg3}{arg4}#*
\KAuxErrorKnowledgeUnknown{arg1}{arg2}{arg3}{arg4}#*
\KAuxErrorLabelUnknown{arg}#*
\KAuxAutoref{arg1}{arg2}{arg3}#*
\KAuxAutorefTarget{arg1}{arg2}{arg3}#*
\KAuxUseKnowledge{arg1}{arg2}{arg3}#*
\ensuretext{arg}#*
\knowledgedisplayref{arg}#*
\makequotationactive#*
\makequotationletter#*
\quotesymbol#*
\klactivequotationmark#*
\klactivedoublequotationmark#*
\klactivatequotation#*
\kldeactivatequotation#*
\KnowledgifyNewcommand{command}#*
\KnowledgifyNewDocumentCommand{command}#*
\IfXcolorTF{true}{false}#*
\ifXcolor#*
\Xcolortrue#*
\Xcolorfalse#*
\KnowledgeConfigureNotion{arg}#*
\KnowledgeConfigureNotion[opt]{arg}#*
