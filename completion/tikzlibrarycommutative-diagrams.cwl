# commutative-diagrams tikzlibrary
# 2022/12/06 for v1.0.1

# tikzlibrarycommutative-diagrams.code.tex
# ├─ tikzlibrarycommutative-diagrams.diorthono.code.tex
# ├─ tikzlibrarycommutative-diagrams.ramma.code.tex
# │  ├─ tikzlibrarycommutative-diagrams.bapto.code.tex
# │  ├─ tikzlibrarycommutative-diagrams.ektropi.code.tex
# │  │  └─ tikzlibrarycommutative-diagrams.koinos.code.tex
# │  ├─ tikzlibrarycommutative-diagrams.katharizo.code.tex
# │  ├─ tikzlibrarycommutative-diagrams.koinos.code.tex
# │  ├─ tikzlibrarycommutative-diagrams.ozos.code.tex
# │  │  └─ tikzlibrarycommutative-diagrams.koinos.code.tex
# │  ├─ tikzlibrarycommutative-diagrams.mitra.code.tex
# │  │  ├─ tikzlibrarymatrix.code.tex
# │  │  └─ tikzlibrarycommutative-diagrams.koinos.code.tex
# │  └─ tikzlibrarycommutative-diagrams.velos.code.tex
# └─ tikzlibrarycommutative-diagrams.mandyas.code.tex
#    ├─ tikzlibrarycalc.code.tex
#    └─ tikzlibrarypositioning.code.tex

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

#keyvals:\begin{tikzpicture}#c,\tikz#c
codi
#endkeyvals

# from tikzlibrarycommutative-diagrams.diorthono.code.tex
\kDAct#S

# from tikzlibrarycommutative-diagrams.ramma.code.tex
\ifkDRammaObjIsMatrix#S
\kDRammaObjIsMatrixtrue#S
\kDRammaObjIsMatrixfalse#S
\kDRammaObjDecideWhetherIsMatrixThen{arg}#S
\kDRammaObjDWIM#S
\kDRammaObjDWIMSightThen{arg1}{arg2}#S
\kDRammaObjDWIMGobThen{arg1}{arg2}#S
\kDRammaObjOutput#S
\kDRammaObj#S
\kDRammaMor#S
\kDRamma#S
\kDRammaOpen#S
\kDRammaShut#S
\kDRammaOptTok#S
\kDRammaTmpTok#S
\kDRammaMaybeFetchOptionsThen{arg}#S
\kDRammaFetchOptionsThen{arg1}[arg2]#S
\kDRammaOutput#S

# from tikzlibrarycommutative-diagrams.bapto.code.tex
# no user commands

# from tikzlibrarycommutative-diagrams.ektropi.code.tex
\kDEktropiDefaultToksBackup#S
\kDEktropiRestore#S

# from tikzlibrarycommutative-diagrams.katharizo.code.tex
\kDKatharizoStringified#S
\kDKatharizoStringify{arg}#S
\kDKatharizoSanitized#S
\kDKatharizoSanitize{arg}#S
\kDKatharizoSSpace#S
\kDKatharizoSAppendSpace#S
\kDKatharizoSString{arg1}{arg2}#S
\kDKatharizoSWord{arg1}{arg2}#S
\kDKatharizoSCharacter{arg}#S
\kDFoo#S

# from tikzlibrarycommutative-diagrams.koinos.code.tex
\kDEscapecharCounter#S
\kDEscapecharDisable#S
\kDEscapecharEnable#S
\kDStoreCatcodeOf{arg}#S
\kDRestoreCatcodeOf{arg}#S
\kDGobbleHardTok#S
\kDGobbleSoftTok{arg}#S
\kDIfNextHardCh#S
\kDIfNextSoftCh{arg1}{arg2}{arg3}#S
\kDINCToken#S
\kDINCTrue#S
\kDINC#S
\kDAppend{arg1}{arg2}#S
\kDFetchOptAndGrpThen{arg}#S
\kDOptTok#S
\kDGrpTok#S
\kDFetchGrpThen{arg1}{arg2}#S
\kDExit#S
\kDLoop#S
\kDTmpTok#S
\kDFetchTilGrpThen{arg1}{arg2}#S
\kDTrimTrailingSpace{arg}#S
\kDRTS#S
\kDRTSAct#S
\kDDetectTrailingSpace{arg}#S
\ifkDDTSHasTrail#S
\kDDTSHasTrailtrue#S
\kDDTSHasTrailfalse#S
\kDDTSGob#S
\ifkDDTSPrevSpace#S
\kDDTSPrevSpacetrue#S
\kDDTSPrevSpacefalse#S
\kDTrimLeadingSpace{arg}#S
\kDGobbleSpaceThen{arg}#S
\kDGSGroupThen{arg1}{arg2}#S
\kDGSOtherThen{arg1}{arg2}#S
\ifConTeXt#S
\ConTeXttrue#S
\ConTeXtfalse#S
\ifkDDumping#S
\kDDumpingtrue#S
\kDDumpingfalse#S
\kDDumpFile#S
\kDDumpOpen#S
\kDDump{arg}#S
\kDDumpClose#S

# from tikzlibrarycommutative-diagrams.ozos.code.tex
\kDOzos#S
\kDOzosFetchThen#S
\kDOzosMaybeDumpThen{arg}#S
\kDOzosOutput#S

# from tikzlibrarycommutative-diagrams.mitra.code.tex
#include:tikzlibrarymatrix
\kDMitra#S
\kDMitraTmpTok#S
\kDMitraFetchMatrixThen{arg}#S
\kDMitraMatOutTok#S
\kDMitraParseMatrixTableThen{arg}#S
\kDMitraParseTable#S
\kDMitraParseAllRowsThen{arg}#S
\kDExit#S
\kDMitraParseOneRowThen{arg}#S
\kDMitraMarkRowEndBefore{arg1}{arg2}#S
\kDMitraParseAllColsThen{arg}#S
\kDMitraParseRowEndThen{arg}#S
\kDMitraFetchRowEndThen{arg}#S
\kDMitraRowOptTok#S
\kDMitraPrintRowEndThen{arg}#S
\kDMitraMaybeFetchRowOptionsThen{arg}#S
\kDMitraFetchRowOptionsThen{arg1}[arg2]#S
\kDMitraParseOneColThen{arg}#S
\kDMitraParseColEndThen{arg}#S
\kDMitraColOptTok#S
\kDMitraMaybeFetchColOptionsThen{arg}#S
\kDMitraFetchColOptionsThen{arg1}[arg2]#S
\kDMitraMaybePrintColEndThen{arg}#S
\kDMitraParseCellThen{arg}#S
\kDMitraCelOptTok#S
\kDMitraMaybeFetchCellOptionsThen{arg}#S
\kDMitraFetchCellOptionsThen{%<arg1%>}|%<arg2%>|#S
\kDMitraCelCntTok#S
\kDMitraFetchCellContentThen{arg1}{arg1}#S
\kDMitraMaybeDoCellThen{arg}#S
\kDMitraPrintCellThen{arg}#S
\kDMitraMaybeDumpCell#S
\kDMitraOutput#S

# from tikzlibrarycommutative-diagrams.velos.code.tex
\kDVelosQuoteHandler{arg}#S
\kDVelosUnquote"%<arg%>"#S
\kDVelosTemp#S
\kDVelosGlobalLabelOptions#S
\kDVelosGlobalEdgeOptions#S
\ifkDVelosGOAfterColon#S
\kDVelosGOAfterColontrue#S
\kDVelosGOAfterColonfalse#S
\kDVelosFetchGlobalOptionsThen{arg}#S
\kDVelosGOMaybeFetchThen{arg}#S
\kDVelosGOFetchThen{arg1}[arg2]#S
\kDVelosGOThinkThen{arg}#S
\kDVelosDoFirstEdgeThen{arg}#S
\kDVelosSource#S
\kDVelosCurFstSrc#S
\kDVelosPrvFstSrc#S
\kDVelosFetchFirstSourceThen{arg}#S
\kDVelosFFSBracketsThen{arg1}(arg2)#S
\kDVelosFFSTillOverThen{arg1}{arg2}#S
\kDVelosFetchFirstEdgeThen{arg}#S
\kDVelosEdge#S
\kDVelosFetchEdgeThen{arg}#S
\kDVelosFEThen{arg}#S
\ifkDVelosTempIsKeysList#S
\kDVelosTempIsKeysListtrue#S
\kDVelosTempIsKeysListfalse#S
\kDVelosFEEnquotedThen{%<arg1%>}"%<arg2%>"#S
\kDVelosFEKeysListThen{arg1}[arg2]#S
\kDVelosFETillOverThen{arg}#S
\kDVelosFETOThen{arg}#S
\kDVelosFEAppendThen{arg}{arg}#S
\kDVelosFEEdgePrepend{arg}#S
\kDVelosFEEdgePrependNode{arg}#S
\kDVelosFEThinkThen{arg}#S
\kDVelosFELoop#S
\kDVelosFEBreak#S
\kDVelosTarget#S
\kDVelosCurLstTar#S
\kDVelosPrvLstTar#S
\kDVelosFetchTargetThen#S
\kDVelosFTBracketsThen{arg1}(arg2)#S
\kDVelosFTTillOverThen{arg}#S
\kDVelosFTTOThen{arg}#S
\kDVelosFTTOLoop#S
\kDVelosFTTOExit#S
\kDVelosFTAppendThen{arg}{arg}#S
\kDVelosAlias#S
\kDVelosSaila#S
\kDVelosDerefSrc#S
\kDVelosDerefTar#S
\kDVelosDrawFetchedEdgeThen{arg}#S
\kDVelos#S
\kDVelosMaybeChainEdge#S

# from tikzlibrarycommutative-diagrams.ektropi.code.tex
#include:tikzlibrarycalc
#include:tikzlibrarypositioning