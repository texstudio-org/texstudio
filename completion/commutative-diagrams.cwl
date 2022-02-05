# commutative-diagrams package
# Matthew Bertucci 2/3/2022 for v1.0.1

#include:tikz

# Dependency Tree:
# commutative-diagrams.sty
# ├─ tikz.sty
# └─ tikzlibrarycommutative-diagrams.code.tex
#    ├─ tikzlibrarycommutative-diagrams.diorthono.code.tex
#    ├─ tikzlibrarycommutative-diagrams.ramma.code.tex
#    │  ├─ tikzlibrarycommutative-diagrams.bapto.code.tex
#    │  ├─ tikzlibrarycommutative-diagrams.ektropi.code.tex
#    │  │  └─ tikzlibrarycommutative-diagrams.koinos.code.tex
#    │  ├─ tikzlibrarycommutative-diagrams.katharizo.code.tex
#    │  ├─ tikzlibrarycommutative-diagrams.koinos.code.tex
#    │  ├─ tikzlibrarycommutative-diagrams.ozos.code.tex
#    │  │  └─ tikzlibrarycommutative-diagrams.koinos.code.tex
#    │  ├─ tikzlibrarycommutative-diagrams.mitra.code.tex
#    │  │  ├─ tikzlibrarymatrix.code.tex
#    │  │  └─ tikzlibrarycommutative-diagrams.koinos.code.tex
#    │  └─ tikzlibrarycommutative-diagrams.velos.code.tex
#    └─ tikzlibrarycommutative-diagrams.mandyas.code.tex
#       ├─ tikzlibrarycalc.code.tex
#       └─ tikzlibrarypositioning.code.tex

\begin{codi}#\math
\begin{codi}[options%keyvals]#\math
\end{codi}#\math

#keyvals:\begin{codi}#c
prompter
expand=#none,once,full
replace character=%<character1%> with %<character2%>
replace charcode=%<charcode%> with %<character%>
remove characters=%<characters%>
remove character=%<character%>
remove charcode=%<charcode%>
overwrite=#false,alias,true
every diagram/.append style={%<TikZ options%>}
every layout/.append style={%<TikZ options%>}
every object/.append style={%<TikZ options%>}
every arrow/.append style={%<TikZ options%>}
every label/.append style={%<TikZ options%>}
tetragonal
tetragonal=base %<<length>%> height %<<length>%>
hexagonal
hexagonal=%<<direction>%> side %<<length>%> angle %<<angle>%>
square=##L
golden=##L
arrows/crossing over
arrows/crossing over/clearance=##L
arrows/crossing over/color=#%color
arrows/slide=##L
arrows/shove=##L
# some common tikz options
%color
x=##L
y=##L
node distance=##L
#endkeyvals

\obj {%<object%>};
\obj [%<options%>] {%<object%>};
# following line allows keyval completer to work even with spaces in lines above
\obj[%<options%>]#S

#keyvals:\obj#c
expand=#none,once,full
tetragonal=base %<<length>%> height %<<length>%>
hexagonal=%<<direction>%> side %<<length>%> angle %<<angle>%>
square=##L
golden=##L
replace character=%<character1%> with %<character2%>
replace charcode=%<charcode%> with %<character%>
remove characters=%<characters%>
remove character=%<character%>
remove charcode=%<charcode%>
overwrite=#false,alias,true
# some common tikz options
%color
above=of %<node%>
below=of %<node%>
left=of %<node%>
right=of %<node%>
above left=of %<node%>
below left=of %<node%>
above right=of %<node%>
below right=of %<node%>
base left=of %<node%>
base right=of %<node%>
mid left=of %<node%>
mid right=of %<node%>
#endkeyvals

\mor %<morphism%>;
\mor [%<label options%>] %<morphism%>;
\mor [%<label options%>]:[%<arrow options%>] %<morphism%>;
# same as above for \obj
\mor[%<options%>]#S

#keyvals:\mor#c
mid
# some common tikz style options
%color
swap
at start
very near start
near start
midway
near end
very near end
at end
#endkeyvals

# from tikzlibrarycommutative-diagrams.diorthono.code.tex
\kDAct#*

# from tikzlibrarycommutative-diagrams.ramma.code.tex
\ifkDRammaObjIsMatrix#*
\kDRammaObjIsMatrixtrue#*
\kDRammaObjIsMatrixfalse#*
\kDRammaObjDecideWhetherIsMatrixThen{arg}#*
\kDRammaObjDWIM#*
\kDRammaObjDWIMSightThen{arg1}{arg2}#*
\kDRammaObjDWIMGobThen{arg1}{arg2}#*
\kDRammaObjOutput#*
\kDRammaObj#*
\kDRammaMor#*
\kDRamma#*
\kDRammaOpen#*
\kDRammaShut#*
\kDRammaOptTok#*
\kDRammaTmpTok#*
\kDRammaMaybeFetchOptionsThen{arg}#*
\kDRammaFetchOptionsThen{arg1}[arg2]#*
\kDRammaOutput#*

# from tikzlibrarycommutative-diagrams.bapto.code.tex
# no user commands

# from tikzlibrarycommutative-diagrams.ektropi.code.tex
\kDEktropiDefaultToksBackup#*
\kDEktropiRestore#*

# from tikzlibrarycommutative-diagrams.katharizo.code.tex
\kDKatharizoStringified#*
\kDKatharizoStringify{arg}#*
\kDKatharizoSanitized#*
\kDKatharizoSanitize{arg}#*
\kDKatharizoSSpace#*
\kDKatharizoSAppendSpace#*
\kDKatharizoSString{arg1}{arg2}#*
\kDKatharizoSWord{arg1}{arg2}#*
\kDKatharizoSCharacter{arg}#*
\kDFoo#*

# from tikzlibrarycommutative-diagrams.koinos.code.tex
\kDEscapecharCounter#*
\kDEscapecharDisable#*
\kDEscapecharEnable#*
\kDStoreCatcodeOf{arg}#*
\kDRestoreCatcodeOf{arg}#*
\kDGobbleHardTok#*
\kDGobbleSoftTok{arg}#*
\kDIfNextHardCh#*
\kDIfNextSoftCh{arg1}{arg2}{arg3}#*
\kDINCToken#*
\kDINCTrue#*
\kDINC#*
\kDAppend{arg1}{arg2}#*
\kDFetchOptAndGrpThen{arg}#*
\kDOptTok#*
\kDGrpTok#*
\kDFetchGrpThen{arg1}{arg2}#*
\kDExit#*
\kDLoop#*
\kDTmpTok#*
\kDFetchTilGrpThen{arg1}{arg2}#*
\kDTrimTrailingSpace{arg}#*
\kDRTS#*
\kDRTSAct#*
\kDDetectTrailingSpace{arg}#*
\ifkDDTSHasTrail#*
\kDDTSHasTrailtrue#*
\kDDTSHasTrailfalse#*
\kDDTSGob#*
\ifkDDTSPrevSpace#*
\kDDTSPrevSpacetrue#*
\kDDTSPrevSpacefalse#*
\kDTrimLeadingSpace{arg}#*
\kDGobbleSpaceThen{arg}#*
\kDGSGroupThen{arg1}{arg2}#*
\kDGSOtherThen{arg1}{arg2}#*
\ifConTeXt#*
\ConTeXttrue#*
\ConTeXtfalse#*
\ifkDDumping#*
\kDDumpingtrue#*
\kDDumpingfalse#*
\kDDumpFile#*
\kDDumpOpen#*
\kDDump{arg}#*
\kDDumpClose#*

# from tikzlibrarycommutative-diagrams.ozos.code.tex
\kDOzos#*
\kDOzosFetchThen#*
\kDOzosMaybeDumpThen{arg}#*
\kDOzosOutput#*

# from tikzlibrarycommutative-diagrams.mitra.code.tex
\kDMitra#*
\kDMitraTmpTok#*
\kDMitraFetchMatrixThen{arg}#*
\kDMitraMatOutTok#*
\kDMitraParseMatrixTableThen{arg}#*
\kDMitraParseTable#*
\kDMitraParseAllRowsThen{arg}#*
\kDExit#*
\kDMitraParseOneRowThen{arg}#*
\kDMitraMarkRowEndBefore{arg1}{arg2}#*
\kDMitraParseAllColsThen{arg}#*
\kDMitraParseRowEndThen{arg}#*
\kDMitraFetchRowEndThen{arg}#*
\kDMitraRowOptTok#*
\kDMitraPrintRowEndThen{arg}#*
\kDMitraMaybeFetchRowOptionsThen{arg}#*
\kDMitraFetchRowOptionsThen{arg1}[arg2]#*
\kDMitraParseOneColThen{arg}#*
\kDMitraParseColEndThen{arg}#*
\kDMitraColOptTok#*
\kDMitraMaybeFetchColOptionsThen{arg}#*
\kDMitraFetchColOptionsThen{arg1}[arg2]#*
\kDMitraMaybePrintColEndThen{arg}#*
\kDMitraParseCellThen{arg}#*
\kDMitraCelOptTok#*
\kDMitraMaybeFetchCellOptionsThen{arg}#*
\kDMitraFetchCellOptionsThen{%<arg1%>}|%<arg2%>|#*
\kDMitraCelCntTok#*
\kDMitraFetchCellContentThen{arg1}{arg1}#*
\kDMitraMaybeDoCellThen{arg}#*
\kDMitraPrintCellThen{arg}#*
\kDMitraMaybeDumpCell#*
\kDMitraOutput#*

# from tikzlibrarycommutative-diagrams.velos.code.tex
\kDVelosQuoteHandler{arg}#*
\kDVelosUnquote"%<arg%>"#*
\kDVelosTemp#*
\kDVelosGlobalLabelOptions#*
\kDVelosGlobalEdgeOptions#*
\ifkDVelosGOAfterColon#*
\kDVelosGOAfterColontrue#*
\kDVelosGOAfterColonfalse#*
\kDVelosFetchGlobalOptionsThen{arg}#*
\kDVelosGOMaybeFetchThen{arg}#*
\kDVelosGOFetchThen{arg1}[arg2]#*
\kDVelosGOThinkThen{arg}#*
\kDVelosDoFirstEdgeThen{arg}#*
\kDVelosSource#*
\kDVelosCurFstSrc#*
\kDVelosPrvFstSrc#*
\kDVelosFetchFirstSourceThen{arg}#*
\kDVelosFFSBracketsThen{arg1}(arg2)#*
\kDVelosFFSTillOverThen{arg1}{arg2}#*
\kDVelosFetchFirstEdgeThen{arg}#*
\kDVelosEdge#*
\kDVelosFetchEdgeThen{arg}#*
\kDVelosFEThen{arg}#*
\ifkDVelosTempIsKeysList#*
\kDVelosTempIsKeysListtrue#*
\kDVelosTempIsKeysListfalse#*
\kDVelosFEEnquotedThen{%<arg1%>}"%<arg2%>"#*
\kDVelosFEKeysListThen{arg1}[arg2]#*
\kDVelosFETillOverThen{arg}#*
\kDVelosFETOThen{arg}#*
\kDVelosFEAppendThen{arg}{arg}#*
\kDVelosFEEdgePrepend{arg}#*
\kDVelosFEEdgePrependNode{arg}#*
\kDVelosFEThinkThen{arg}#*
\kDVelosFELoop#*
\kDVelosFEBreak#*
\kDVelosTarget#*
\kDVelosCurLstTar#*
\kDVelosPrvLstTar#*
\kDVelosFetchTargetThen#*
\kDVelosFTBracketsThen{arg1}(arg2)#*
\kDVelosFTTillOverThen{arg}#*
\kDVelosFTTOThen{arg}#*
\kDVelosFTTOLoop#*
\kDVelosFTTOExit#*
\kDVelosFTAppendThen{arg}{arg}#*
\kDVelosAlias#*
\kDVelosSaila#*
\kDVelosDerefSrc#*
\kDVelosDerefTar#*
\kDVelosDrawFetchedEdgeThen{arg}#*
\kDVelos#*
\kDVelosMaybeChainEdge#*