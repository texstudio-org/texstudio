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
\flJSStr*{cmd}{JS string%definition}#d
\defineJSStr{cmd}{JS string%definition}#*d
\fieldJSStr{cmd}{JS string%definition}#*d
\dlJSStr{cmd}{JS string%definition}#d
\dlJSStr*{cmd}{JS string%definition}#d
\cs{csname}
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
\DLspecialDefs#S
\GoTo#S
\GoToD#S
\GoToR#S
\LB#S
\Launch{arg}#S
\NL#S
\Thread{arg}#S
\URI{arg}#S
\Uni#S
\W#S
\addActionObj#S
\addImportAnFDF{arg}#S
\addToDocOpen{arg}#S
\aebpFA#S
\aebpopentoks#S
\applydljs{arg}#S
\begindljs#S
\beginseg#S
\begin{didPrint}#S
\begin{didSave}#S
\begin{localJS}#S
\begin{willClose}#S
\begin{willPrint}#S
\begin{willSave}#S
\ckivspace{arg1}#S
\db{arg}#S
\defineJSArg#S
\definebraces#S
\defjsLB#S
\detectdljs#S
\dfnJSCRDef#S
\dfnJSCR{arg}#S
\dlPkgInfoDate#S
\dlPkgInfoDesc#S
\dlPkgInfoPkg#S
\dlPkgInfoVer#S
\dlSetPkgInfo#S
\dlTC{arg}#S
\dlcombine#S
\dlcomment#S
\dlcontig#S
\dlgobToFi{arg}#S
\dljs#S
\dljspdftextmp#S
\dljspresent#S
\dljstfor#S
\dljstmp#S
\dlparsePkgInfo{arg1}{arg2}{arg3}#S
\dlpkgInfo#S
\dlpkgInfoExpd#S
\efdlspecials#S
\enddlcomment#S
\enddljs#S
\endinsDLJS#S
\endjsexpverbatimwrite#S
\endnewsegment#S
\endseg#S
\end{didPrint}#S
\end{didSave}#S
\end{localJS}#S
\end{willClose}#S
\end{willPrint}#S
\end{willSave}#S
\eqdospecials#S
\escIs{arg}#S
\execJSOff#S
\execJSOn#S
\expVerb#S
\fdfAfterheader{arg}#S
\fdfbeginstreamobj#S
\fdfendstreamobj#S
\fdfheader#S
\fdftrailer#S
\firstFDFline#S
\firstdljs#S
\fitpage#S
\fitvisible#S
\fitwidth#S
\genericLB#S
\genericNL#S
\gobiv#S
\holdtokstmp#S
\importAnFDF#S
\importAnFDFTemplate#S
\importAnFDFtmp#S
\importdljs#S
\inputAltAdbFncs#S
\insPath{arg}#S
\insdljsloadVar#S
\isOpenAction#S
\isStar#S
\iwvo{arg}#S
\jsFrstLne#S
\jsN#S
\jsR#S
\jsT#S
\jscsDLJS#S
\jscsDflt#S
\jsexpverbatimwrite#S
\lastFDFline#S
\makeJSspecials#S
\makecmt#S
\makespecialJS#S
\multisegments#S
\newsegment#S
\opentoks#S
\pdfLBr#S
\pdfRBr#S
\pdfSPDef#S
\pdfSpacesOff#S
\pdfSpacesOn#S
\pdfmarkLB#S
\pdftexOAction#S
\previewMiKTeX#S
\protectJSCtrls#S
\reqpkg#S
\restoreDLspecialDefs#S
\theFirstAction#S
\thedljssegs#S
\thisPageActionpdftex#S
\usedAdbFuncs#S

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