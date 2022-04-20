# functional package
# Matthew Bertucci 4/17/2022 for v2022D

# Note on cwl: the package author Jianrui Lyu encourages use of spaces between
# args which along with the need to have proper "\newcommand" completion
# requires many commands to be listed twice; once with what the user sees,
# another with #S that tells the completer what to do. In some cases for reasons
# I don't understand, the order matters, e.g. with \TlMapVariable.

#include:expl3

## Overview of Features ##
# Evaluation from Inside to Outside
\IgnoreSpacesOn
\IgnoreSpacesOff

# Group Scoping of Functions
\Functional{options%keyvals}
#keyvals:\Functional
scoping#true,false
tracing#true,false
#endkeyvals

## Functional Programming (Prg) ##
# Defining Functions and Conditionals
\PrgNewFunction %<\function%> {%<arg spec%>} {%<code%>}
\PrgNewFunction{cmd}{xargs}{def}#Sd
\PrgNewConditional %<\function%> {%<arg spec%>} {%<code%>}
\PrgNewConditional{cmd}{xargs}{def}#Sd

# Collecting Returned Values
\Return{tokens}
\gResultTl

## Argument Using (Use) ##
# Expanding Tokens
\Name{csname}
\Value %<\variable%>
\Expand{tokens}
\UnExpand{tokens}
\OnlyName{tokens}
\OnlyValue{tokens}

# Using Tokens
\UseOne{arg}
\GobbleOne{arg}
\UseGobble{arg1}{arg2}
\GobbleUse{arg1}{arg2}

## Control Structures (Bool) ##
# Constant and Scratch Booleans
\cTrueBool
\cFalseBool
\lTmpaBool
\lTmpbBool
\lTmpcBool
\lTmpiBool
\lTmpjBool
\lTmpkBool
\gTmpaBool
\gTmpbBool
\gTmpcBool
\gTmpiBool
\gTmpjBool
\gTmpkBool

# Creating and Setting Booleans
\BoolNew %<\boolvar%>
\BoolNew{cmd}#Sd
\BoolConst %<\boolvar%> {%<bool expr%>}
\BoolConst{cmd}#Sd
\BoolSet %<\boolvar%> {%<bool expr%>}
\BoolSet{cmd}#Sd
\BoolSetTrue %<\boolvar%>
\BoolSetFalse %<\boolvar%>
\BoolSetEq %<\boolvar1 \boolvar2%>

# Viewing Booleans
\BoolLog {bool expr}
\BoolVarLog %<\boolvar%>
\BoolShow {bool expr}
\BoolVarShow %<\boolvar%>

# Booleans and Conditionals
\BoolIfExist %<\boolvar%>
\BoolIfExistTF %<\boolvar%> {%<true code%>} {%<false code%>}
\BoolVarIf %<\boolvar%>
\BoolVarIfTF %<\boolvar%> {%<true code%>} {%<false code%>}
\BoolVarNot %<\boolvar%>
\BoolVarNotTF %<\boolvar%> {%<true code%>} {%<false code%>}
\BoolVarAnd %<\boolvar1 \boolvar2%>
\BoolVarAndTF %<\boolvar1 \boolvar2%> {%<true code%>} {%<false code%>}
\BoolVarOr %<\boolvar1 \boolvar2%>
\BoolVarOrTF %<\boolvar1 \boolvar2%> {%<true code%>} {%<false code%>}
\BoolVarXor %<\boolvar1 \boolvar2%>
\BoolVarXorTF %<\boolvar1 \boolvar2%> {%<true code%>} {%<false code%>}

# Booleans and Logical Loops #
\BoolDoUntil %<\boolvar%> {%<code%>}
\BoolDoWhile %<\boolvar%> {%<code%>}
\BoolUntilDo %<\boolvar%> {%<code%>}
\BoolWhileDo %<\boolvar%> {%<code%>}

## Token Lists (Tl) ##
# Constant and Scratch Token Lists
\cSpaceTl
\cEmptyTl
\lTmpaTl
\lTmpbTl
\lTmpcTl
\lTmpiTl
\lTmpjTl
\lTmpkTl
\gTmpaTl
\gTmpbTl
\gTmpcTl
\gTmpiTl
\gTmpjTl
\gTmpkTl

# Creating and Using Token Lists
\TlNew %<\tlvar%>
\TlNew{cmd}#Sd
\TlConst %<\tlvar%> {%<tokens%>}
\TlConst{cmd}{def}#Sd
\TlUse %<\tlvar%>
\TlToStr {tokens}
\TlToStr{tokens%definition}#S
\TlVarToStr %<\tlvar%>

# Viewing Token Lists
\TlLog {tokens}
\TlLog{tokens%definition}#S
\TlVarLog %<\tlvar%>
\TlShow {tokens}
\TlShow{tokens%definition}#S
\TlVarShow %<\tlvar%>

# Setting Token List Variables
\TlSet %<\tlvar%> {%<tokens%>}
\TlSet{cmd}{def}#Sd
\TlSetEq %<\tlvar1 \tlvar2%>
\TlSetEq{cmd}#Sd
\TlClear %<\tlvar%>
\TlClearNew %<\tlvar%>
\TlClearNew{cmd}#Sd
\TlConcat %<\tlvar1 \tlvar2 \tlvar3%>
\TlConcat{cmd}#Sd
\TlPutLeft %<\tlvar%> {%<tokens%>}
\TlPutRight %<\tlvar%> {%<tokens%>}

# Replacing Tokens
\TlVarReplaceOnce %<\tlvar%> {%<old tokens%>} {%<new tokens%>}
\TlVarReplaceAll %<\tlvar%> {%<old tokens%>} {%<new tokens%>}
\TlVarRemoveOnce %<\tlvar%> {%<tokens%>}
\TlVarRemoveAll %<\tlvar%> {%<tokens%>}
\TlTrimSpaces {tokens}
\TlVarTrimSpaces %<\tlvar%>

# Working with the Content of Token Lists
\TlCount {tokens}
\TlCount{tokens%definition}#S
\TlVarCount %<\tlvar%>
\TlHead {tokens}
\TlVarHead %<\tlvar%>
\TlTail {tokens}
\TlVarTail %<\tlvar%>
\TlItem {tokens} {int expr}
\TlVarItem %<\tlvar%> {%<int expr%>}
\TlRandItem {tokens}
\TlVarRandItem %<\tlvar%>

# Mapping over Token Lists
\TlMapInline {tokens} {inline function}
\TlVarMapInline %<\tlvar%> {%<inline function%>}
\TlMapVariable{tokens}{cmd}{def}#Sd
\TlMapVariable {%<tokens%>} %<\variable%> {%<code%>}
\TlVarMapVariable{tlvar}{cmd}{def}#Sd
\TlVarMapVariable %<\tlvar \variable%> {%<code%>}

# Token List Conditionals
\TlIfExist %<\tlvar%>
\TlIfExistTF %<\tlvar%> {%<true code%>} {%<false code%>}
\TlIfEmpty {tokens}
\TlIfEmptyTF {tokens} {true code} {false code}
\TlVarIfEmpty %<\tlvar%>
\TlVarIfEmptyTF %<\tlvar%> {%<true code%>} {%<false code%>}
\TlIfBlank {tokens}
\TlIfBlankTF {tokens} {true code} {false code}
\TlIfEq {tokens1} {tokens2}
\TlIfEqTF {tokens1} {tokens2} {true code} {false code}
\TlVarIfEq %<\tlvar1 \tlvar2%>
\TlVarIfEqTF %<\tlvar1 \tlvar2%> {%<true code%>} {%<false code%>}
\TlIfIn {tokens1} {tokens2}
\TlIfInTF {tokens1} {tokens2} {true code} {false code}
\TlVarIfIn %<\tlvar%> {%<tokens%>}
\TlVarIfInTF %<\tlvar%> {%<tokens%>} {%<true code%>} {%<false code%>}
\TlIfSingle {tokens}
\TlIfSingleTF {tokens} {true code} {false code}
\TlVarIfSingle %<\tlvar%>
\TlVarIfSingleTF %<\tlvar%> {%<true code%>} {%<false code%>}

# Token List Case Functions
\TlVarCase %<\tlvar%> {%<\tlvar1 {code1} \tlvar2 {code2} ...%>}
\TlVarCaseT %<\tlvar%> {%<\tlvar1 {code1} \tlvar2 {code2} ...%>} {%<true code%>}
\TlVarCaseF %<\tlvar%> {%<\tlvar1 {code1} \tlvar2 {code2} ...%>} {%<false code%>}
\TlVarCaseTF %<\tlvar%> {%<\tlvar1 {code1} \tlvar2 {code2} ...%>} {%<true code%>} {%<false code%>}

## Strings (Str) ##
#  Constant and Scratch Strings
\cAmpersandStr
\cAtsignStr
\cBackslashStr
\cLeftBraceStr
\cRightBraceStr
\cCircumflexStr
\cColonStr
\cDollarStr
\cHashStr
\cPercentStr
\cTildeStr
\cUnderscoreStr
\cZeroStr
\lTmpaStr
\lTmpbStr
\lTmpcStr
\lTmpiStr
\lTmpjStr
\lTmpkStr
\gTmpaStr
\gTmpbStr
\gTmpcStr
\gTmpiStr
\gTmpjStr
\gTmpkStr

# Creating and Using Strings
\StrNew %<\strvar%>
\StrNew{cmd}#Sd
\StrConst %<\strvar%> {%<tokens%>}
\StrConst{cmd}{def}#Sd
\StrUse %<\strvar%>

# Viewing Strings
\StrLog {tokens}
\StrLog{tokens%definition}#S
\StrVarLog %<\strvar%>
\StrShow {tokens}
\StrShow{tokens%definition}#S
\StrVarShow %<\strvar%>

# Setting String Variables
\StrSet %<\strvar%> {%<tokens%>}
\StrSet{cmd}{def}#Sd
\StrSetEq %<\strvar1 \strvar2%>
\StrClear %<\strvar%>
\StrClearNew %<\strvar%>
\StrClearNew{cmd}#Sd
\StrConcat %<\strvar1 \strvar2 \strvar3%>
\StrConcat{cmd}#Sd
\StrPutLeft %<\strvar%> {%<tokens%>}
\StrPutRight %<\strvar%> {%<tokens%>}

# Modifying String Variables
\StrVarReplaceOnce %<\tlvar%> {%<old tokens%>} {%<new tokens%>}
\StrVarReplaceAll %<\tlvar%> {%<old tokens%>} {%<new tokens%>}
\StrVarRemoveOnce %<\strvar%> {%<tokens%>}
\StrVarRemoveAll %<\strvar%> {%<tokens%>}

# Working with the Content of Strings
\StrCount {tokens}
\StrCount{tokens%definition}#S
\StrSize {tokens}#*
\StrSize{tokens%definition}#S
\StrVarCount %<\tlvar%>
\StrHead {tokens}
\StrVarHead %<\tlvar%>
\StrTail {tokens}
\StrVarTail %<\tlvar%>
\StrItem {tokens} {int expr}
\StrVarItem %<\tlvar%> {%<int expr%>}

# Mapping over Strings
\StrMapInline {tokens} {inline function}
\StrVarMapInline %<\tlvar%> {%<inline function%>}
\StrMapVariable{tokens}{cmd}{def}#Sd
\StrMapVariable {%<tokens%>} %<\variable%> {%<code%>}
\StrVarMapVariable{strvar}{cmd}{def}#Sd
\StrVarMapVariable %<\strvar \variable%> {%<code%>}

# String Conditionals
\StrIfExist %<\strvar%>
\StrIfExistTF %<\strvar%> {%<true code%>} {%<false code%>}
\StrVarIfEmpty %<\strvar%>
\StrVarIfEmptyTF %<\strvar%> {%<true code%>} {%<false code%>}
\StrIfEq {tokens1} {tokens2}
\StrIfEqTF {tokens1} {tokens2} {true code} {false code}
\StrVarIfEq %<\strvar1 \strvar2%>
\StrVarIfEqTF %<\strvar1 \strvar2%> {%<true code%>} {%<false code%>}
\StrIfIn {tokens1} {tokens2}
\StrIfInTF {tokens1} {tokens2} {true code} {false code}
\StrVarIfIn %<\strvar%> {%<tokens%>}
\StrVarIfInTF %<\strvar%> {%<tokens%>} {%<true code%>} {%<false code%>}
\StrCompare {%<tokens1%>} %<<relation>%> {%<tokens2%>}
\StrCompareTF {%<tokens1%>} %<<relation>%> {%<tokens2%>} {%<true code%>} {%<false code%>}
\StrIfCompare {%<tokens1%>} %<<relation>%> {%<tokens2%>}#*
\StrIfCompareTF {%<tokens1%>} %<<relation>%> {%<tokens2%>} {%<true code%>} {%<false code%>}#*

# String Case Functions
\StrCase {%<test string%>} {%<{string1} {code1} {string2} {code2} ...%>}
\StrCaseT {%<test string%>} {%<{string1} {code1} {string2} {code2} ...%>} {%<true code%>}
\StrCaseF {%<test string%>} {%<{string1} {code1} {string2} {code2} ...%>} {%<false code%>}
\StrCaseTF {%<test string%>} {%<{string1} {code1} {string2} {code2} ...%>} {%<true code%>} {%<false code%>}

## Integers (Int) ##
# Constant and Scratch ints
\cZeroInt
\cOneInt
\cMaxInt
\cMaxRegisterInt
\cMaxCharInt
\lTmpaInt
\lTmpbInt
\lTmpcInt
\lTmpiInt
\lTmpjInt
\lTmpkInt
\gTmpaInt
\gTmpbInt
\gTmpcInt
\gTmpiInt
\gTmpjInt
\gTmpkInt

# Integer Expressions
\IntEval {int expr}
\IntMathAdd {int expr1} {int expr2}
\IntMathSub {int expr1} {int expr2}
\IntMathMult {int expr1} {int expr2}
\IntMathDiv {int expr1} {int expr2}
\IntMathDivTruncate {int expr1} {int expr2}
\IntMathSign {int expr}
\IntMathAbs {int expr}
\IntMathMax {int expr1} {int expr2}
\IntMathMin {int expr1} {int expr2}
\IntMathMod {int expr1} {int expr2}
\IntMathRand {int expr1} {int expr2}

# Creating and Using Integers
\IntNew %<\intvar%>
\IntNew{cmd}#Sd
\IntConst %<\intvar%> {%<int expr%>}
\IntConst{cmd}#Sd
\IntUse %<\intvar%>

# Viewing Integers
\IntLog {int expr}
\IntVarLog %<\intvar%>
\IntShow {int expr}
\IntVarShow %<\intvar%>

# Setting Integer Variables
\IntSet %<\intvar%> {%<int expr%>}
\IntSet{cmd}#Sd
\IntSetEq %<\intvar1 \intvar2%>
\IntSetEq{cmd}#Sd
\IntZero %<\intvar%>
\IntZeroNew %<\intvar%>
\IntZeroNew{cmd}#Sd
\IntIncr %<\intvar%>
\IntDecr %<\intvar%>
\IntAdd %<\intvar%> {%<int expr%>}
\IntSub %<\intvar%> {%<int expr%>}

# Integer Step Functions
\IntStepInline {init value} {step} {final value} {code}
\IntStepVariable{init value}{step}{final value}{cmd}{code%definition}#Sd
\IntStepVariable {%<init value%>} {%<step%>} {%<final value%>} %<\tlvar%> {%<code%>}

# Integer Conditionals
\IntIfExist %<\intvar%>
\IntIfExistTF %<\intvar%> {%<true code%>} {%<false code%>}
\IntIfOdd {int expr}
\IntIfOddTF {int expr} {true code} {false code}
\IntIfEven {int expr}
\IntIfEvenTF {int expr} {true code} {false code}
\IntCompare {%<int expr1%>} %<<relation>%> {%<int expr2%>}
\IntCompareTF {%<int expr1%>} %<<relation>%> {%<int expr2%>} {%<true code%>} {%<false code%>}

# Integer Case Functions
\IntCase {%<test int expr%>} {%<{int expr1} {code1} {int expr2} {code2} ...%>}
\IntCaseT {%<test int expr%>} {%<{int expr1} {code1} {int expr2} {code2} ...%>} {%<true code%>}
\IntCaseF {%<test int expr%>} {%<{int expr1} {code1} {int expr2} {code2} ...%>} {%<false code%>}
\IntCaseTF {%<test int expr%>} {%<{int expr1} {code1} {int expr2} {code2} ...%>} {%<true code%>} {%<false code%>}

## Floating Point Numbers (Fp) ##
# Constant and Scratch Floating Points
\cZeroFp
\cMinusZeroFp
\cOneFp
\cInfFp
\cMinusInfFp
\cEFp
\cPiFp
\cOneDegreeFp
\lTmpaFp
\lTmpbFp
\lTmpcFp
\lTmpiFp
\lTmpjFp
\lTmpkFp
\gTmpaFp
\gTmpbFp
\gTmpcFp
\gTmpiFp
\gTmpjFp
\gTmpkFp

# Floating Point Expressions
\FpEval {fp expr}
\FpMathAdd {fp expr1} {fp expr2}
\FpMathSub {fp expr1} {fp expr2}
\FpMathMult {fp expr1} {fp expr2}
\FpMathDiv {fp expr1} {fp expr2}
\FpMathSign {fp expr}
\FpMathAbs {fp expr}
\FpMathMax {fp expr1} {fp expr2}
\FpMathMin {fp expr1} {fp expr2}

# Creating and Using Floating Points
\FpNew %<\fpvar%>
\FpNew{cmd}#Sd
\FpConst %<\fpvar%> {%<fp expr%>}
\FpConst{cmd}#Sd
\FpUse %<\fpvar%>

# Viewing Floating Points
\FpLog {fp expr}
\FpVarLog %<\fpvar%>
\FpShow {fp expr}
\FpVarShow %<\fpvar%>

# Setting Floating Point Variables
\FpSet %<\fpvar%> {%<fp expr%>}
\FpSet{cmd}#Sd
\FpSetEq %<\fpvar1 \fpvar2%>
\FpSetEq{cmd}#Sd
\FpZero %<\fpvar%>
\FpZeroNew %<\fpvar%>
\FpZeroNew{cmd}#Sd
\FpAdd %<\fpvar%> {%<fp expr%>}
\FpSub %<\fpvar%> {%<fp expr%>}

# Floating Point Step Functions
\FpStepInline {init value} {step} {final value} {code}
\FpStepVariable{init value}{step}{final value}{cmd}{code%definition}#Sd
\FpStepVariable {%<init value%>} {%<step%>} {%<final value%>} %<\tlvar%> {%<code%>}

# Float Point Conditionals
\FpIfExist %<\fpvar%>
\FpIfExistTF %<\fpvar%> {%<true code%>} {%<false code%>}
\FpCompare {%<fp expr1%>} %<<relation>%> {%<fp expr2%>}
\FpCompareTF {%<fp expr1%>} %<<relation>%> {%<fp expr2%>} {%<true code%>} {%<false code%>}

## Dimensions (Dim) ##
# Constant and Scratch Dimensions
\cMaxDim
\cZeroDim
\lTmpaDim
\lTmpbDim
\lTmpcDim
\lTmpiDim
\lTmpjDim
\lTmpkDim
\gTmpaDim
\gTmpbDim
\gTmpcDim
\gTmpiDim
\gTmpjDim
\gTmpkDim

# Dimension Expressions
\DimEval {dim expr}
\DimMathAdd {dim expr1} {dim expr2}
\DimMathSub {dim expr1} {dim expr2}
\DimMathRatio {dim expr1} {dim expr2}
\DimMathSign {dim expr}
\DimMathAbs {dim expr}
\DimMathMax {dim expr1} {dim expr2}
\DimMathMin {dim expr1} {dim expr2}

# Creating and Using Dimensions
\DimNew %<\dimen%>
\DimNew{cmd}#Sd
\DimConst %<\dimen%> {%<dim expr%>}
\DimConst{cmd}#Sd
\DimUse %<\dimen%>

# Viewing Dimensions
\DimLog {dim expr}
\DimVarLog %<\dimen%>
\DimShow {dim expr}
\DimVarShow %<\dimen%>

# Setting Dimension Variables
\DimSet %<\dimen%> {%<dim expr%>}
\DimSet{cmd}#Sd
\DimSetEq %<\dimen1 \dimen2%>
\DimSetEq{cmd}#Sd
\DimZero %<\dimen%>
\DimZeroNew %<\dimen%>
\DimZeroNew{cmd}#Sd
\DimAdd %<\dimen%> {%<dim expr%>}
\DimSub %<\dimen%> {%<dim expr%>}

# Dimension Step Functions
\DimStepInline {init value} {step} {final value} {code}
\DimStepVariable{init value}{step}{final value}{cmd}{code%definition}#Sd
\DimStepVariable {%<init value%>} {%<step%>} {%<final value%>} %<\tlvar%> {%<code%>}

# Dimension Conditionals
\DimIfExist %<\dimen%>
\DimIfExistTF %<\dimen%> {%<true code%>} {%<false code%>}
\DimCompare {%<dim expr1%>} %<<relation>%> {%<dim expr2%>}
\DimCompareTF {%<dim expr1%>} %<<relation>%> {%<dim expr2%>} {%<true code%>} {%<false code%>}

# Dimension Case Functions
\DimCase {%<test dim expr%>} {%<{dim expr1} {code1} {dim expr2} {code2} ...%>}
\DimCaseT {%<test dim expr%>} {%<{dim expr1} {code1} {dim expr2} {code2} ...%>}{%<true code%>}
\DimCaseF {%<test dim expr%>} {%<{dim expr1} {code1} {dim expr2} {code2} ...%>}{%<false code%>}
\DimCaseTF {%<test dim expr%>} {%<{dim expr1} {code1} {dim expr2} {code2} ...%>}{%<true code%>}{%<false code%>}

## Comma Separated Lists (Clist) ##
# Constant and Scratch Comma Lists
\cEmptyClist
\lTmpaClist
\lTmpbClist
\lTmpcClist
\lTmpiClist
\lTmpjClist
\lTmpkClist
\gTmpaClist
\gTmpbClist
\gTmpcClist
\gTmpiClist
\gTmpjClist
\gTmpkClist

# Creating and Using Comma Lists
\ClistNew %<\clistvar%>
\ClistNew{cmd}#Sd
\ClistConst %<\clistvar%> {%<comma list%>}
\ClistConst{cmd}#Sd
\ClistVarJoin %<\clistvar%> {%<separator%>}
\ClistVarJoinExtended %<\clistvar%> {%<sep for 2%>} {%<sep for >2%>} {%<sep for final 2%>}
\ClistJoin {comma list} {separator}
\ClistJoinExtended {comma list} {sep for 2} {sep for >2} {sep for final 2}

# Viewing Comma Lists
\ClistLog {comma list}
\ClistVarLog %<\clistvar%>
\ClistShow {comma list}
\ClistVarShow %<\clistvar%>

# Setting Comma Lists
\ClistSet %<\clistvar%> {%<comma list%>}
\ClistSet{cmd}#Sd
\ClistSetEq %<\clistvar1 \clistvar2%>
\ClistSetEq{cmd}#Sd
\ClistSetFromSeq %<\clistvar \seqvar%>
\ClistSetFromSeq{cmd}{arg}#Sd
\ClistClear %<\clistvar%>
\ClistClearNew %<\clistvar%>
\ClistClearNew{cmd}#Sd
\ClistConcat %<\clistvar1 \clistvar2 \clistvar3%>
\ClistPutLeft %<\clistvar%> {%<comma list%>}
\ClistPutRight %<\clistvar%> {%<comma list%>}

# Modifying Comma Lists
\ClistVarRemoveDuplicates %<\clistvar%>
\ClistVarRemoveAll %<\clistvar%> {%<item%>}
\ClistVarReverse %<\clistvar%>

# Working with the Contents of Comma Lists
\ClistCount {comma list}
\ClistVarCount %<\clistvar%>
\ClistItem {comma list} {int expr}
\ClistVarItem %<\clistvar%> {%<int expr%>}
\ClistRandItem {comma list}
\ClistVarRandItem %<\clistvar%>

# Comma Lists as Stacks
\ClistGet %<\clistvar \tlvar%>
\ClistGet{clistvar}{cmd}#Sd
\ClistGetT %<\clistvar \tlvar%> {%<true code%>}
\ClistGetT{clistvar}{cmd}#Sd
\ClistGetF %<\clistvar \tlvar%> {%<false code%>}
\ClistGetF{clistvar}{cmd}#Sd
\ClistGetTF %<\clistvar \tlvar%> {%<true code%>} {%<false code%>}
\ClistGetTF{clistvar}{cmd}#Sd
\ClistPop %<\clistvar \tlvar%>
\ClistPop{clistvar}{cmd}#Sd
\ClistPopT %<\clistvar \tlvar%> {%<true code%>}
\ClistPopT{clistvar}{cmd}#Sd
\ClistPopF %<\clistvar \tlvar%> {%<false code%>}
\ClistPopF{clistvar}{cmd}#Sd
\ClistPopTF %<\clistvar \tlvar%> {%<true code%>} {%<false code%>}
\ClistPopTF{clistvar}{cmd}#Sd
\ClistPush %<\clistvar%> {%<items%>}

# Mapping over Comma Lists
\ClistMapInline {comma list} {inline function}
\ClistVarMapInline %<\clistvar%> {%<inline function%>}
\ClistMapVariable{comma list}{cmd}{def}#Sd
\ClistMapVariable {%<comma list%>} %<\variable%> {%<code%>}
\ClistVarMapVariable{clistvar}{cmd}{def}#Sd
\ClistVarMapVariable %<\clistvar \variable%> {%<code%>}

# Comma List Conditionals
\ClistIfExist %<\clistvar%>
\ClistIfExistTF %<\clistvar%> {%<true code%>} {%<false code%>}
\ClistIfEmpty {comma list}
\ClistIfEmptyTF {comma list} {true code} {false code}
\ClistVarIfEmpty %<\clistvar%>
\ClistVarIfEmptyTF %<\clistvar%> {%<true code%>} {%<false code%>}
\ClistIfIn {comma list} {item}
\ClistIfInTF {comma list} {item} {true code} {false code}
\ClistVarIfIn %<\clistvar%> {%<item%>}
\ClistVarIfInTF %<\clistvar%> {%<item%>} {%<true code%>} {%<false code%>}

## Sequences and Stacks (Seq) ##
# Constant and Scratch Sequences
\cEmptySeq
\lTmpaSeq
\lTmpbSeq
\lTmpcSeq
\lTmpiSeq
\lTmpjSeq
\lTmpkSeq
\gTmpaSeq
\gTmpbSeq
\gTmpcSeq
\gTmpiSeq
\gTmpjSeq
\gTmpkSeq

# Creating and Using Sequences
\SeqNew %<\seqvar%>
\SeqNew{cmd}#Sd
\SeqConstFromClist %<\seqvar%> {%<comma list%>}
\SeqConstFromClist{cmd}#Sd
\SeqVarJoin %<\seqvar%> {%<separator%>}
\SeqVarJoinExtended %<\seqvar%> {%<sep for 2%>} {%<sep for >2%>} {%<sep for final 2%>}

# Viewing Sequences
\SeqVarLog %<\seqvar%>
\SeqVarShow %<\seqvar%>

# Setting Sequences
\SeqSetFromClist %<\seqvar%> {%<comma list%>}
\SeqSetFromClist{cmd}#Sd
\SeqSetSplit %<\seqvar%> {%<delimiter%>} {%<tokens%>}
\SeqSetSplit{cmd}#Sd
\SeqSetEq %<\seqvar1 \seqvar2%>
\SeqSetEq{cmd}#Sd
\SeqClear %<\seqvar%>
\SeqClearNew %<\seqvar%>
\SeqClearNew{cmd}#Sd
\SeqConcat %<\seqvar1 \seqvar2 \seqvar3%>
\SeqPutLeft %<\seqvar%> {%<item%>}
\SeqPutRight %<\seqvar%> {%<item%>}

# Modifying Sequences
\SeqVarRemoveDuplicates %<\seqvar%>
\SeqVarRemoveAll %<\seqvar%> {%<item%>}
\SeqVarReverse %<\seqvar%>

# Working with the Contents of Sequences
\SeqVarCount %<\seqvar%>
\SeqVarItem %<\seqvar%> {%<int expr%>}
\SeqVarRandItem %<\seqvar%>

# Sequences as Stacks
\SeqGet %<\seqvar \tlvar%>
\SeqGetT %<\seqvar \tlvar%> {%<true code%>}
\SeqGetF %<\seqvar \tlvar%> {%<false code%>}
\SeqGetTF %<\seqvar \tlvar%> {%<true code%>} {%<false code%>}
\SeqPop %<\seqvar \tlvar%>
\SeqPopT %<\seqvar \tlvar%> {%<true code%>}
\SeqPopF %<\seqvar \tlvar%> {%<false code%>}
\SeqPopTF %<\seqvar \tlvar%> {%<true code%>} {%<false code%>}
\SeqPush %<\seqvar%> {%<item%>}

# Recovering Items from Sequences
\SeqGetLeft %<\seqvar \tlvar%>
\SeqGetLeftT %<\seqvar \tlvar%> {%<true code%>}
\SeqGetLeftF %<\seqvar \tlvar%> {%<false code%>}
\SeqGetLeftTF %<\seqvar \tlvar%> {%<true code%>} {%<false code%>}
\SeqGetRight %<\seqvar \tlvar%>
\SeqGetRightT %<\seqvar \tlvar%> {%<true code%>}
\SeqGetRightF %<\seqvar \tlvar%> {%<false code%>}
\SeqGetRightTF %<\seqvar \tlvar%> {%<true code%>} {%<false code%>}
\SeqPopLeft %<\seqvar \tlvar%>
\SeqPopLeftT %<\seqvar \tlvar%> {%<true code%>}
\SeqPopLeftF %<\seqvar \tlvar%> {%<false code%>}
\SeqPopLeftTF %<\seqvar \tlvar%> {%<true code%>} {%<false code%>}
\SeqPopRight %<\seqvar \tlvar%>
\SeqPopRightT %<\seqvar \tlvar%> {%<true code%>}
\SeqPopRightF %<\seqvar \tlvar%> {%<false code%>}
\SeqPopRightTF %<\seqvar \tlvar%> {%<true code%>} {%<false code%>}

# Mapping over Sequences
\SeqVarMapInline %<\seqvar%> {%<inline function%>}
\SeqVarMapVariable{seqvar}{cmd}{def}#Sd
\SeqVarMapVariable %<\seqvar \variable%> {%<code%>}

# Sequence Conditionals
\SeqIfExist %<\seqvar%>
\SeqIfExistTF %<\seqvar%> {%<true code%>} {%<false code%>}
\SeqVarIfEmpty %<\seqvar%>
\SeqVarIfEmptyTF %<\seqvar%> {%<true code%>} {%<false code%>}
\SeqVarIfIn %<\seqvar%> {%<item%>}
\SeqVarIfInTF %<\seqvar%> {%<item%>} {%<true code%>} {%<false code%>}

## Property Lists (Prop) ##
# Constant and Scratch Properties
\cEmptyProp
\lTmpaProp
\lTmpbProp
\lTmpcProp
\lTmpiProp
\lTmpjProp
\lTmpkProp
\gTmpaProp
\gTmpbProp
\gTmpcProp
\gTmpiProp
\gTmpjProp
\gTmpkProp

# Creating and Using Property Lists
\PropNew %<\propvar%>
\PropNew{cmd}#Sd
\PropConstFromKeyval %<\propvar%> {%<key1=value2, key2=value2, ...%>}
\PropConstFromKeyval{cmd}#Sd
\PropToKeyval %<\propvar%>

# Viewing Property Lists
\PropVarLog %<\propvar%>
\PropVarShow %<\propvar%>

# Setting Property Lists
\PropSetFromKeyval %<\propvar%> {%<key1=value2, key2=value2, ...%>}
\PropSetFromKeyval{cmd}#Sd
\PropSetEq %<\propvar1 \propvar2%>
\PropSetEq{cmd}#Sd
\PropClear %<\propvar%>
\PropClearNew %<\propvar%>
\PropClearNew{cmd}#Sd
\PropConcat %<\propvar1 \propvar2 \propvar3%>
\PropPut %<\propvar%> {%<key%>} {%<value%>}
\PropPutIfNew %<\propvar%> {%<key%>} {%<value%>}
\PropPutFromKeyval %<\propvar%> {%<key1=value2, key2=value2, ...%>}
\PropVarRemove %<\propvar%> {%<key%>}

# Recovering Values from Property Lists
\PropVarCount %<\propvar%>
\PropVarItem %<\propvar%> {%<key%>}
\PropGet %<\propvar%> {%<key%>} %<\tlvar%>
\PropGet{propvar}{key%plain}{cmd}#Sd
\PropGetT %<\propvar%> {%<key%>} %<\tlvar%> {%<true code%>}
\PropGetT{propvar}{key%plain}{cmd}#Sd
\PropGetF %<\propvar%> {%<key%>} %<\tlvar%> {%<false code%>}
\PropGetF{propvar}{key%plain}{cmd}#Sd
\PropGetTF %<\propvar%> {%<key%>} %<\tlvar%> {%<true code%>} {%<false code%>}
\PropGetTF{propvar}{key%plain}{cmd}#Sd
\PropPop %<\propvar%> {%<key%>} %<\tlvar%>
\PropPop{propvar}{key%plain}{cmd}#Sd
\PropPopT %<\propvar%> {%<key%>} %<\tlvar%> {%<true code%>}
\PropPopT{propvar}{key%plain}{cmd}#Sd
\PropPopF %<\propvar%> {%<key%>} %<\tlvar%> {%<false code%>}
\PropPopF{propvar}{key%plain}{cmd}#Sd
\PropPopTF %<\propvar%> {%<key%>} %<\tlvar%> {%<true code%>} {%<false code%>}
\PropPopTF{propvar}{key%plain}{cmd}#Sd

# Mapping over property lists
\PropVarMapInline %<\propvar%> {%<inline function%>}

# Property List Conditionals
\PropIfExist %<\propvar%>
\PropIfExistTF %<\propvar%> {%<true code%>} {%<false code%>}
\PropVarIfEmpty %<\propvar%>
\PropVarIfEmptyTF %<\propvar%> {%<true code%>} {%<false code%>}
\PropVarIfIn %<\propvar%> {%<key%>}
\PropVarIfInTF %<\propvar%> {%<key%>} {%<true code%>} {%<false code%>}

## Quarks (Quark) ##
# Constant Quarks
\qNoValue

# Quark Conditionals
\QuarkVarIfNoValue %<\tlvar%>
\QuarkVarIfNoValueTF %<\tlvar%> {%<true code%>} {%<false code%>}

## Legacy Concepts (Legacy) ##
\LegacyIf {%<name%>}
\LegacyIfT {%<name%>} {%<true code%>}
\LegacyIfF {%<name%>} {%<false code%>}
\LegacyIfTF {%<name%>} {%<true code%>} {%<false code%>}
\LegacyIfSetTrue {%<name%>}
\LegacyIfSetFalse {%<name%>}
\LegacyIfSet {%<name%>} {%<bool expr%>}

## not documented ##
\Break#*
\BreakDo#*
\ClistMapBreak#*
\ClistVarSort{arg1}{arg2}#*
\cNoValueTl#*
\Local#*
\NoExpand{tokens}#*
\OnlyExpandF{tokens}#*
\OnlyExpandO{tokens}#*
\PrgBreak#*
\PrgBreakDo#*
\PropMapBreak#*
\SeqJoin{arg1}{arg2}#*
\SeqJoinExtended{arg1}{arg2}{arg3}{arg4}#*
\SeqMapBreak#*
\SeqVarSort{arg1}{arg2}#*
\SortReturnSame#*
\SortReturnSwapped#*

# deprecated
\Result{tokens}#S
