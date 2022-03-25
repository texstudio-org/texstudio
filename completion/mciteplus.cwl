# mciteplus package
# Matthew Bertucci 3/19/2022 for v1.2

#keyvals:\usepackage/mciteplus#c
chapterbibrootbib
debug
nohooks
#endkeyvals

\ifmciteErrorOnUnknown#*
\mciteErrorOnUnknowntrue
\mciteErrorOnUnknownfalse
\mcitedefaultmidpunct#*
\mcitedefaultendpunct#*
\mcitedefaultseppunct#*
\mciteSetBstMidEndSepPunct{middle punct}{end punct}{sep punct}
\mciteSetMidEndSepPunct{middle punct}{end punct}{sep punct}
\mcitebstendpunct#*
\mciteendpunct#*
\mcitebstmidpunct#*
\mcitemidpunct#*
\mcitebstseppunct#*
\mciteseppunct#*
\themcitebibitemcount#*
\themcitesubitemcount#*
\ifmciteResetBibitemCount#*
\mciteResetBibitemCountfalse
\mciteResetBibitemCounttrue
\mciteSetBstSublistMode{mode%keyvals}
\mciteSetSublistMode{mode%keyvals}
#keyvals:\mciteSetBstSublistMode,\mciteSetSublistMode
d
n
s
b
f
h
#endkeyvals
\mcitedefaultsublistlabel#*
\mcitedefaultsublistbegin#*
\mcitedefaultsublistend#*
\mciteSetBstSublistLabelBeginEnd{label}{begdef}{enddef}
\mciteSetSublistLabelBeginEnd{label}{begdef}{enddef}
\mcitebstsublistbegin#*
\mcitebstsublistend#*
\mcitesublistbegin#*
\mcitesublistend#*
\mcitebstsublistlabel#*
\mcitesublistlabel#*
\mciteSubRef{bibid}#C
\mciteSubRef[track ID]{bibid}#C
\mciteSubPageRef{bibid}#C
\mciteSubPageRef[track ID]{bibid}#C
\mcitesubrefform#*
\mciteBibitemArgI#*
\mciteBibitemOptArgI#*
\ifmciteBibitemOptArgI#*
\mciteBibitemOptArgItrue#*
\mciteBibitemOptArgIfalse#*
\mciteCurheadBibitemArgI#*
\mciteCurheadBibitemOptArgI#*
\ifmciteCurheadBibitemOp#*
\mciteCurheadBibitemOptrue#*
\mciteCurheadBibitemOpfalse#*
\mciteorgbibsamplelabel#*
\mcitebibsamplelabel#*
\mcitedefaultmaxwidthbibitemform#*
\mcitedefaultmaxwidthsubitemform#*
\mcitedefaultmaxwidthbibitemforminit#*
\mcitedefaultmaxwidthsubitemforminit#*
\mciteSetBstMaxWidthForm{type%keyvals}{form}
\mciteSetBstMaxWidthForm[init]{type%keyvals}{form}
\mciteSetMaxWidthForm{type%keyvals}{form}
\mciteSetMaxWidthForm[init]{type%keyvals}{form}
#keyvals:\mciteSetBstMaxWidthForm,\mciteSetMaxWidthForm
bibitem
subitem
#endkeyvals
\mcitebstmaxwidthbibitemform#*
\mcitebstmaxwidthsubitemform#*
\mcitebstmaxwidthbibitemforminit#*
\mcitebstmaxwidthsubitemforminit#*
\mcitemaxwidthbibitem#*
\mcitemaxwidthsubitem#*
\mcitemaxwidthbibitemform#*
\mcitemaxwidthsubitemform#*
\mcitemaxcountbibitem#*
\mcitemaxcountsubitem#*
\EndOfBibitem#*
\mciteOrgcite{bibid}#*C
\mciteOrgcite[add. text]{bibid}#*C
\mciteOrgnocite{bibid}#*C
\mciteOrgnocite[add. text]{bibid}#*C
\begin{mcitethebibliography}
\end{mcitethebibliography}
\mciteOrgbibitem{citekey}#*
\mciteOrgbibitem[label]{citekey}#*
\mcitetrackID#*
\mcitebibtrackID#*
\mciteauxout#*
\mcitebibauxout#*
\mciteCiteA{aux out}{track ID}{prehandler}{posthandler}{fwd}{cite list}#*
\mciteCiteA{aux out}{track ID}{prehandler}{posthandler}{fwd}[opt1]{cite list}#*
\mciteCiteA{aux out}{track ID}{prehandler}{posthandler}{fwd}[opt1][opt2]{cite list}#*
\mciteCiteA*{aux out}{track ID}{prehandler}{posthandler}{fwd}{cite list}#*
\mciteCiteA*{aux out}{track ID}{prehandler}{posthandler}{fwd}[opt1]{cite list}#*
\mciteCiteA*{aux out}{track ID}{prehandler}{posthandler}{fwd}[opt1][opt2]{cite list}#*
\mciteCiteB{aux out}{track ID}{prehandler}{posthandler}{fwd}{sec ID}{cite list}#*
\mciteCiteB{aux out}{track ID}{prehandler}{posthandler}{fwd}[opt1]{sec ID}{cite list}#*
\mciteCiteB{aux out}{track ID}{prehandler}{posthandler}{fwd}[opt1][opt2]{sec ID}{cite list}#*
\mciteCiteB*{aux out}{track ID}{prehandler}{posthandler}{fwd}{sec ID}{cite list}#*
\mciteCiteB*{aux out}{track ID}{prehandler}{posthandler}{fwd}[opt1]{sec ID}{cite list}#*
\mciteCiteB*{aux out}{track ID}{prehandler}{posthandler}{fwd}[opt1][opt2]{sec ID}{cite list}#*
\mciteCitePrehandlerArg#*
\mciteCitePosthandlerArg#*
\mciteCiteSecIDArg#*
\mciteCiteFwdArg#*
\mciteCiteOptArgI#*
\mciteCiteOptArgII#*
\mciteDoList{aux out}{track ID}{cite list}#*
\mciteExtraDoLists#*
\mciteCiteAuxArg#*
\mciteCiteTrackArg#*
\mciteCiteListArg#*
\mciteheadlist#*
\mciteFwdCiteListArg#*
\mciteBIBdecl#*
\mciteBIBenddecl#*
\mcitefwdBIBdecl#*

# not documented
\ifmciteBstWouldAddEndPunct#*
\ifmciteCiteStarFwdArg#*
\ifmciteCurheadBibitemOptArgI#*
\ifmciteMacroOptArgI#*
\ifmciteMacroOptArgII#*
\ifmciteMacroStarForm#*
\mcitebibitem[label]{citekey}#*
\mcitebibitem{citekey}#*
\mciteBstWouldAddEndPunctfalse#*
\mciteBstWouldAddEndPuncttrue#*
\mciteCiteStarFwdArgfalse#*
\mciteCiteStarFwdArgtrue#*
\mciteCurheadBibitemOptArgIfalse#*
\mciteCurheadBibitemOptArgItrue#*
\mciteEndOfBibGroupPostsubcloseHook#*
\mciteEndOfBibGroupPresubcloseHook#*
\mciteGetMaxCount{track ID}{type}{out macro}#*
\mciteGetMaxWidth{track ID}{type}{out macro}#*
\mciteMacroOptArgIfalse#*
\mciteMacroOptArgIIfalse#*
\mciteMacroOptArgIItrue#*
\mciteMacroOptArgItrue#*
\mciteMacroStarFormfalse#*
\mciteMacroStarFormtrue#*
\mciteOrgbibliography{bib file}#*
\mciteSetMaxCount{track ID}{type}{count}#*
\mciteSetMaxWidth{track ID}{type}{width}#*
\mcitethebibliographyHook#*

\mciteBACKREFform#S
\mciteCITEREFform#S
\mciteOrgBIBUNITSbibunit#S