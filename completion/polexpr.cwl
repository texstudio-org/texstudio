# polexpr package
# Matthew Bertucci 12/18/2021 for v0.8.5

#include:xintexpr

## Non-expandable macros ##
\poldef %<polname(letter)%> := %<pol expr%>;
\PolDef{polname}{pol expr}
\PolDef[letter]{polname}{pol expr}
\PolGenFloatVariant{polname}
\PolTypeset{polname}
\PolTypeset[letter]{polname}
\PolTypeset*{polname}
\PolTypeset*[letter]{polname}
\PolTypesetCmd{raw coeff}#*
\PolIfCoeffIsPlusOrMinusOne{true}{false}#*
\PolTypesetOne{raw coeff}#*
\PolTypesetMonomialCmd#*
\PolTypesetCmdPrefix{raw coeff}#*
\PolIndex#*
\PolVar#*

## Non-expandable macros related to the root localization routines ##
\PolToSturm{polname}{sturmname}
\PolToSturm*{polname}{sturmname}
\PolSturmIsolateZeros{sturmname}
\PolSturmIsolateZeros*{sturmname}
\PolSturmIsolateZeros**{sturmname}
\PolSturmIsolateZerosAndGetMultiplicities{sturmname}#*
\PolSturmIsolateZerosGetMultiplicitiesAndRationalRoots{sturmname}#*
\PolSturmIsolateZerosAndFindRationalRoots{sturmname}
\PolRefineInterval*{sturmname}{index}
\PolRefineInterval{sturmname}{index}
\PolRefineInterval[N]{sturmname}{index}
\PolEnsureIntervalLength{sturmname}{index}{exponent}
\PolEnsureIntervalLengths{sturmname}{exponent}
\PolPrintIntervals{sturmname}
\PolPrintIntervals[varname]{sturmname}
\PolPrintIntervals*{sturmname}
\PolPrintIntervals*[varname]{sturmname}
\PolPrintIntervalsNoRealRoots#*
\PolPrintIntervalsBeginEnv#*
\PolPrintIntervalsEndEnv#*
\PolPrintIntervalsKnownRoot#*
\PolPrintIntervalsUnknownRoot#*
\PolPrintIntervalsPrintExactZero#*
\PolPrintIntervalsPrintLeftEndPoint#*
\PolPrintIntervalsPrintRightEndPoint#*
\PolPrintIntervalsPrintMultiplicity#*
\PolSetToSturmChainSignChangesAt{macro%cmd}{sturmname}{value}#d
\PolSetToNbOfZerosWithin{macro%cmd}{sturmname}{value left}{value right}#d
\PolLet{polname1}={polname2}
\PolGlobalLet{polname1}={polname2}
\PolAssign{%<polname%>}\toarray%<\macro%>
\toarray{cmd}#Sd
\PolGet{polname}\fromarray%<\macro%>
\fromarray#S
\PolFromCSV{polname}{csv}
\PolMapCoeffs{macro}{polname}
\PolReduceCoeffs{polname}
\PolReduceCoeffs*{polname}
\PolMakeMonic{polname}
\PolMakePrimitive{polname}
\PolDiff{polname1}{polname2}
\PolDiff[N]{polname1}{polname2}
\PolAntiDiff{polname1}{polname2}
\PolAntiDiff[N]{polname1}{polname2}
\PolDivide{polname1}{polname2}{polnameQ}{polnameR}
\PolQuo{polname1}{polname2}{polnameQ}
\PolRem{polname1}{polname2}{polnameR}
\PolGCD{polname1}{polname2}{polnameGCD}

## Expandable macros ##
\PolToExpr{pol expr}
\PolToExpr*{pol expr}
\PolToExprVar#*
\PolToExprInVar#*
\PolToExprTimes#*
\PolToExprCaret#*
\PolToExprCmd{raw coeff}#*
\PolToExprOneTerm{raw coeff}{exponent}#*
\PolToExprOneTermStyleA{raw coeff}{exponent}#*
\PolToExprOneTermStyleB{raw coeff}{exponent}#*
\PolToExprTermPrefix{raw coeff}#*
\PolToFloatExpr{pol expr}
\PolToFloatExpr*{pol expr}
\PolToFloatExprOneTerm{raw coeff}{exponent}#*
\PolToFloatExprCmd{raw coeff}#*
\PolNthCoeff{polname}{index}
\PolLeadingCoeff{polname}
\PolDegree{polname}
\PolIContent{polname}
\PolToList{polname}
\PolToCSV{polname}
\PolEval{polname}\AtExpr{num expr}
\AtExpr#S
\PolEval{polname}\At{value}
\At#S
\PolEvalReduced{polname}\AtExpr{num expr}
\PolEvalReduced{polname}\At{value}
\PolFloatEval{polname}\AtExpr{num expr}
\PolFloatEval{polname}\At{value}

## Expandable macros related to the root localization routines ##
\PolSturmChainLength{sturmname}
\PolSturmIfZeroExactlyKnown{sturmname}{index}{true}{false}
\PolSturmIsolatedZeroLeft{sturmname}{index}
\PolSturmIsolatedZeroRight{sturmname}{index}
\PolSturmIsolatedZeroMultiplicity{sturmname}{index}
\PolSturmNbOfIsolatedZeros{sturmname}
\PolSturmNbOfRootsOf{sturmname}\LessThanOrEqualTo{value}
\PolSturmNbOfRootsOf{sturmname}\LessThanOrEqualToExpr{num expr}
\PolSturmNbWithMultOfRootsOf{sturmname}\LessThanOrEqualTo{value}
\PolSturmNbWithMultOfRootsOf{sturmname}\LessThanOrEqualToExpr{num expr}
\PolSturmNbOfRationalRoots{sturmname}
\PolSturmNbOfRationalRootsWithMultiplicities{sturmname}
\PolSturmRationalRoot{sturmname}{k}
\PolSturmRationalRootIndex{sturmname}{k}
\PolSturmRationalRootMultiplicity{sturmname}{k}
\PolIntervalWidth{sturmname}{index}

## Expandable macros for use within execution of \PolPrintIntervals ##
\PolPrintIntervalsTheVar
\PolPrintIntervalsTheIndex
\PolPrintIntervalsTheSturmName
\PolPrintIntervalsTheLeftEndPoint
\PolPrintIntervalsTheRightEndPoint
\PolPrintIntervalsTheMultiplicity

## Booleans ##
\ifpolnewpolverbose#*
\polnewpolverbosetrue#*
\polnewpolverbosefalse
\ifpoltypesetall#*
\poltypesetalltrue#*
\poltypesetallfalse
\ifpoltoexprall#*
\poltoexpralltrue#*
\poltoexprallfalse

## Utilities ##
\PolDecToString{decimal number}
\polexprsetup{options%keyvals}

#keyvals:\polexprsetup
norr=%<sturmname postfix%>
sqfnorr=%<sturmname postfix%>
#endkeyvals

## not documented ##
\ifxintveryverbose#*
\xintveryverbosetrue#*
\xintveryverbosefalse#*
\next#S
\PolNbOfRootsLessThanOrEqualToExpr{arg1}{arg2}#S
\PolNbOfRootsLessThanOrEqualTo{arg1}#S
\PolNbWithMultOfRootsLessThanOrEqualToExpr{arg1}{arg2}#S
\PolNbWithMultOfRootsLessThanOrEqualTo{arg1}#S
\PolPrintIntervalsArrayStretch#S
\PolSturmIntervalIndexAtExpr{arg1}{arg2}#S
\PolSturmIntervalIndexAt{arg1}{arg2}#S
\PolSturmIntervalIndex{arg1}{arg2}{arg3}#S
\PolToExprAscending{arg1}{arg2}#S
\PolToExprDescending{arg1}#S
\PolToFloatExprAscending{arg1}{arg2}#S
\PolToFloatExprDescending{arg1}#S
\xintPolAdd{arg1}#S
\xintPolAntiOne{arg1}#S
\xintPolCoeffs{arg1}#S
\xintPolCoeff{arg1}{arg2}#S
\xintPolCont{arg1}#S
\xintPolDeg{arg1}#S
\xintPolDiffN{arg1}{arg2}#S
\xintPolDiffOne{arg1}#S
\xintPolDiffTwo{arg1}#S
\xintPolDivModQ{arg1}#S
\xintPolDivModR{arg1}#S
\xintPolDivMod{arg1}#S
\xintPolEvalAt{arg1}{arg2}#S
\xintPolGCDof{arg1}#S
\xintPolIntFrom{arg1}#S
\xintPolIntegral{arg1}{arg2}#S
\xintPolLCoeffs{arg1}#S
\xintPolLC{arg1}#S
\xintPolLPol{arg1}#S
\xintPolMonicPart{arg1}#S
\xintPolMul{arg1}#S
\xintPolOpp{arg1}#S
\xintPolPRem{arg1}#S
\xintPolPol{arg1}#S
\xintPolPow{arg1}#S
\xintPolPrimPart{arg1}#S
\xintPolQuoRem{arg1}#S
\xintPolQuo{arg1}#S
\xintPolRedCoeffs{arg1}#S
\xintPolRem{arg1}#S
\xintPolSRedCoeffs{arg1}#S
\xintPolSqr{arg1}#S
\xintPolSub{arg1}#S
\xintiiifNeg#S
\xintiiifneg#S

## deprecated ##
\PolEvalAtExpr{arg1}{arg2}#S
\PolEvalAt{arg1}{arg2}#S
\PolEvalReducedAtExpr{arg1}{arg2}#S
\PolEvalReducedAt{arg1}{arg2}#S
\PolFloatEvalAtExpr{arg1}{arg2}#S
\PolFloatEvalAt{arg1}{arg2}#S

# the following slightly improves the appearance of expl3 code
\POL#S