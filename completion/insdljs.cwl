# insdljs package
# Matthew Bertucci 2/7/2022 for v0.4.0

#include:xkeyval
#include:ifpdf
#include:ifxetex
#include:ifluatex
#include:hyperref
#include:verbatim
#include:conv-xkv
#include:everyshi

#keyvals:\usepackage/insdljs#c
dvipsone
dvips
textures
pdftex
luatex
dvipdfm
dvipdfmx
xetex
nodljs
debug
execJS
nopro
reqjs
!reqjs
usealtadobe
#endkeyvals

\flJSStr{cmd}{JS string%definition}#d
\flJSStr[options%keyvals]{cmd}{JS string%definition}#d
\flJSStr*{cmd}{JS string%definition}#d
\flJSStr*[options%keyvals]{cmd}{JS string%definition}#d
\defineJSStr{cmd}{JS string%definition}#*d
\fieldJSStr{cmd}{JS string%definition}#*d
\dlJSStr{cmd}{JS string%definition}#d
\dlJSStr[options%keyvals]{cmd}{JS string%definition}#d
\dlJSStr*{cmd}{JS string%definition}#d
\dlJSStr*[options%keyvals]{cmd}{JS string%definition}#d

#keyvals:\flJSStr#c,\flJSStr*#c,\dlJSStr#c,\dlJSStr*#c
quotes
noquotes
parens
noparens
#endkeyvals

\cs{csname}
\eqbs#*
\jslit

\begin{insDLJS}{base name}{script name}
\begin{insDLJS}[JS var]{base name}{script name}
\end{insDLJS}
\begin{insDLJS*}{base name}
\begin{insDLJS*}[JS var]{base name}
\end{insDLJS*}
\begin{newsegment}{script name}
\end{newsegment}

\OpenAction{action code}
\thisPageAction{open script}{close script}
\JS{string}
\Named{string}

\begin{execJS}{name}
\end{execJS}
\begin{defineJS}{cmd}#d
\begin{defineJS}[chngCats]{cmd}#d
\end{defineJS}
\begin{defineJS*}{cmd}#d
\begin{defineJS*}[chngCats]{cmd}#d
\end{defineJS*}

\bParams{%<token1%>}%<...{tokenN}%>\eParams
\eParams#S

\makeJSspecials#*

# not documented
\actualsize#S
\addActionObj#S
\addImportAnFDF{arg}#S
\addToDocOpen{arg}#S
\aebpFA#S
\aebpopentoks#S
\applydljs{arg}#S
\begin{didPrint}#S
\begin{didSave}#S
\begin{dlcomment}#S
\begin{dljs}#S
\begin{jsexpverbatimwrite}#S
\begin{localJS}#S
\begin{willClose}#S
\begin{willPrint}#S
\begin{willSave}#S
\begindljs#S
\beginseg#S
\ckivspace{arg1}#S
\db{arg}#S
\definebraces#S
\defineJSArg#S
\defjsLB#S
\detectdljs#S
\dfnJSCR{arg}#S
\dfnJSCRDef#S
\dfnJSR#S
\dlcombine#S
\dlcontig#S
\dlgobToFi{arg}#S
\dljsBase#S
\dljsobjtoks#S
\dljspdftextmp#S
\dljspresent#S
\dljstfor#S
\dljstmp#S
\dlparsePkgInfo{arg1}{arg2}{arg3}#S
\dlpkgInfo#S
\dlPkgInfoDate#S
\dlPkgInfoDesc#S
\dlpkgInfoExpd#S
\dlPkgInfoPkg#S
\dlPkgInfoVer#S
\dlSetPkgInfo#S
\DLspecialDefs#S
\dlTC{arg}#S
\efdlspecials#S
\end{didPrint}#S
\end{didSave}#S
\end{dlcomment}#S
\end{dljs}#S
\end{jsexpverbatimwrite}#S
\end{localJS}#S
\end{willClose}#S
\end{willPrint}#S
\end{willSave}#S
\endseg#S
\eqdospecials#S
\eqesc#S
\Eschr#S
\escIs{arg}#S
\execJSOff#S
\execJSOn#S
\expVerb#S
\fdfAfterheader{arg}#S
\fdfbeginstreamobj#S
\fdfendstreamobj#S
\fdfheader#S
\fdftrailer#S
\firstdljs#S
\firstFDFline#S
\fitheight#S
\fitpage#S
\fitvisible#S
\fitwidth#S
\genericLB#S
\genericNL#S
\gobiv#S
\GoTo#S
\GoToD#S
\GoToR#S
\holdtokstmp#S
\importAnFDF#S
\importAnFDFTemplate#S
\importAnFDFtmp#S
\importdljs#S
\importfdftoks#S
\inheritzoom#S
\inputAltAdbFncs#S
\insdljsloadVar#S
\insPath{arg}#S
\isOpenAction#S
\isStar#S
\iwvo{arg}#S
\jscsDflt#S
\jscsDLJS#S
\jsFrstLne#S
\jsN#S
\jsR#S
\jsT#S
\JStoks#S
\lastFDFline#S
\Launch{arg}#S
\LB#S
\makecmt#S
\makeesc#S
\makespecialJS#S
\multisegments#S
\NL#S
\objNames#S
\opentoks#S
\Page#S
\pdfLBr#S
\pdfmarkLB#S
\pdfRBr#S
\pdfSP#S
\pdfSpacesOff#S
\pdfSpacesOn#S
\pdfSPDef#S
\pdftexOAction#S
\previewMiKTeX#S
\protectJSCtrls#S
\reqpkg#S
\restoreDLspecialDefs#S
\thedljssegs#S
\theFirstAction#S
\thisPageActionpdftex#S
\Thread{arg}#S
\typeset#S
\Uni#S
\URI{arg}#S
\usedAdbFuncs#S
\W#S

\ifpdfmarkup#*
\pdfmarkuptrue#*
\pdfmarkupfalse#*
\ifthereisdjs#*
\thereisdjstrue#*
\thereisdjsfalse#*
\ifpdfspaces#*
\pdfspacestrue#*
\pdfspacesfalse#*
\ifisdljs#*
\isdljstrue#*
\isdljsfalse#*
\ifdlfortypeset#*
\dlfortypesettrue#*
\dlfortypesetfalse#*
