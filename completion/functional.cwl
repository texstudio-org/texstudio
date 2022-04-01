# functional package
# Matthew Bertucci 3/30/2022 for v2022B

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
\Result{tokens}
\gResultTl#*

## Argument Using (Use) ##
# Expanding Tokens
\Name{csname}
\Value %<\variable%>
\Expand{tokens}
\ExpNot{tokens}
\ExpValue %<\variable%>

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
\BoolNew %<\boolean%>
\BoolNew{cmd}#Sd
\BoolConst %<\boolean%> {%<bool expr%>}
\BoolConst{cmd}#Sd
\BoolSet %<\boolean%> {%<bool expr%>}
\BoolSet{cmd}#Sd
\BoolSetTrue %<\boolean%>
\BoolSetFalse %<\boolean%>
\BoolSetEq %<\boolean1 \boolean2%>

# Viewing Booleans
\BoolLog{bool expr}
\BoolVarLog %<\boolean%>
\BoolShow{bool expr}
\BoolVarShow %<\boolean%>

# Booleans and Conditionals
\BoolIfExist %<\boolean%>
\BoolIfExistTF %<\boolean%> {%<true code%>} {%<false code%>}
\BoolVarIf %<\boolean%>
\BoolVarIfTF %<\boolean%> {%<true code%>} {%<false code%>}
\BoolVarNot %<\boolean%>
\BoolVarNotTF %<\boolean%> {%<true code%>} {%<false code%>}
\BoolVarAnd %<\boolean1 \boolean2%>
\BoolVarAndTF %<\boolean1 \boolean2%> {%<true code%>} {%<false code%>}
\BoolVarOr %<\boolean1 \boolean2%>
\BoolVarOrTF %<\boolean1 \boolean2%> {%<true code%>} {%<false code%>}
\BoolVarXor %<\boolean1 \boolean2%>
\BoolVarXorTF %<\boolean1 \boolean2%> {%<true code%>} {%<false code%>}

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
\TlConst %<\tlvar%> {%<token list%>}
\TlConst{cmd}#Sd
\TlUse %<\tlvar%>
\TlToStr{token list}
\TlVarToStr %<\tlvar%>

# Viewing Token Lists
\TlLog{token list}
\TlVarLog %<\tlvar%>
\TlShow{token list}
\TlVarShow %<\tlvar%>

# Setting Token List Variables
\TlSet %<\tlvar%> {%<tokens%>}
\TlSet{cmd}#Sd
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
\TlReplaceOnce %<\tlvar%> {%<old tokens%>} {%<new tokens%>}
\TlReplaceAll %<\tlvar%> {%<old tokens%>} {%<new tokens%>}
\TlRemoveOnce %<\tlvar%> {%<tokens%>}
\TlRemoveAll %<\tlvar%> {%<tokens%>}
\TlTrimSpaces{token list}
\TlVarTrimSpaces %<\tlvar%>

# Working with the Content of Token Lists
\TlCount{tokens}
\TlVarCount %<\tlvar%>
\TlHead{token list}
\TlVarHead %<\tlvar%>
\TlTail{token list}
\TlVarTail %<\tlvar%>
\TlItem{token list}{int expr}
\TlVarItem %<\tlvar%> {%<int expr%>}
\TlRandItem{token list}
\TlVarRandItem %<\tlvar%>

# Mapping over Token Lists
\TlMapInline{token list}{inline function}
\TlVarMapInline %<\tlvar%> {%<inline function%>}
\TlMapVariable{token list}{cmd}{def}#Sd
\TlMapVariable{%<token list%>} %<\variable%> {%<code%>}
\TlVarMapVariable{tlvar}{cmd}{def}#Sd
\TlVarMapVariable %<\tlvar \variable%> {%<code%>}

# Token List Conditionals
\TlIfExist %<\tlvar%>
\TlIfExistTF %<\tlvar%> {%<true code%>} {%<false code%>}
\TlIfEmpty{token list}
\TlIfEmptyTF{token list}{true code}{false code}
\TlVarIfEmpty %<\tlvar%>
\TlVarIfEmptyTF %<\tlvar%> {%<true code%>} {%<false code%>}
\TlIfBlank{token list}
\TlIfBlankTF{token list}{true code}{false code}
\TlIfEq{token list1}{token list2}
\TlIfEqTF{token list1}{token list2}{true code}{false code}
\TlVarIfEq %<\tlvar1 \tlvar2%>
\TlVarIfEqTF %<\tlvar1 \tlvar2%> {%<true code%>} {%<false code%>}
\TlIfIn{token list1}{token list2}
\TlIfInTF{token list1}{token list2}{true code}{false code}
\TlVarIfIn %<\tlvar%> {%<token list%>}
\TlVarIfInTF %<\tlvar%> {%<token list%>} {%<true code%>} {%<false code%>}
\TlIfSingle{token list}
\TlIfSingleTF{token list}{true code}{false code}
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
\StrConst %<\strvar%> {%<token list%>}
\StrConst{cmd}#Sd
\StrUse %<\strvar%>

# Viewing Strings
\StrLog{token list}
\StrVarLog %<\strvar%>
\StrShow{token list}
\StrVarShow %<\strvar%>

# Setting String Variables
\StrSet %<\strvar%> {%<token list%>}
\StrSet{cmd}#Sd
\StrSetEq %<\strvar1 \strvar2%>
\StrClear %<\strvar%>
\StrClearNew %<\strvar%>
\StrClearNew{cmd}#Sd
\StrConcat %<\strvar1 \strvar2 \strvar3%>
\StrConcat{cmd}#Sd
\StrPutLeft %<\strvar%> {%<token list%>}
\StrPutRight %<\strvar%> {%<token list%>}

# Modifying String Variables
\StrReplaceOnce %<\tlvar%> {%<old tokens%>} {%<new tokens%>}
\StrReplaceAll %<\tlvar%> {%<old tokens%>} {%<new tokens%>}
\StrRemoveOnce %<\strvar%> {%<token list%>}
\StrRemoveAll %<\strvar%> {%<token list%>}

# Working with the Content of Strings
\StrCount{token list}
\StrSize{token list}#*
\StrVarCount %<\tlvar%>
\StrHead{token list}
\StrVarHead %<\tlvar%>
\StrTail{token list}
\StrVarTail %<\tlvar%>
\StrItem{token list}{int expr}
\StrVarItem %<\tlvar%> {%<int expr%>}

# Mapping over Strings
\StrMapInline{token list}{inline function}
\StrVarMapInline %<\tlvar%> {%<inline function%>}
\StrMapVariable{token list}{cmd}{def}#Sd
\StrMapVariable{%<token list%>} %<\variable%> {%<code%>}
\StrVarMapVariable{strvar}{cmd}{def}#Sd
\StrVarMapVariable %<\strvar \variable%> {%<code%>}

# String Conditionals
\StrIfExist %<\strvar%>
\StrIfExistTF %<\strvar%> {%<true code%>} {%<false code%>}
\StrVarIfEmpty %<\strvar%>
\StrVarIfEmptyTF %<\strvar%> {%<true code%>} {%<false code%>}
\StrIfEq{token list1}{token list2}
\StrIfEqTF{token list1}{token list2}{true code}{false code}
\StrVarIfEq %<\strvar1 \strvar2%>
\StrVarIfEqTF %<\strvar1 \strvar2%> {%<true code%>} {%<false code%>}
\StrIfIn{token list1}{token list2}
\StrIfInTF{token list1}{token list2}{true code}{false code}
\StrVarIfIn %<\strvar%> {%<token list%>}
\StrVarIfInTF %<\strvar%> {%<token list%>} {%<true code%>} {%<false code%>}
\StrCompare{%<token list1%>} %<<relation>%> {%<token list2%>}
\StrCompareTF{%<token list1%>} %<<relation>%> {%<token list2%>} {%<true code%>} {%<false code%>}
\StrIfCompare{%<token list1%>} %<<relation>%> {%<token list2%>}#*
\StrIfCompareTF{%<token list1%>} %<<relation>%> {%<token list2%>} {%<true code%>} {%<false code%>}#*

# String Case Functions
\StrCase{%<test string%>}{%<{string1} {code1} {string2} {code2} ...%>}
\StrCaseT{%<test string%>}{%<{string1} {code1} {string2} {code2} ...%>}{%<true code%>}
\StrCaseF{%<test string%>}{%<{string1} {code1} {string2} {code2} ...%>}{%<false code%>}
\StrCaseTF{%<test string%>}{%<{string1} {code1} {string2} {code2} ...%>}{%<true code%>}{%<false code%>}

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
\IntEval{int expr}
\IntMathAdd{int expr1}{int expr2}
\IntMathSub{int expr1}{int expr2}
\IntMathMult{int expr1}{int expr2}
\IntMathDiv{int expr1}{int expr2}
\IntMathDivTruncate{int expr1}{int expr2}
\IntMathSign{int expr}
\IntMathAbs{int expr}
\IntMathMax{int expr1}{int expr2}
\IntMathMin{int expr1}{int expr2}
\IntMathMod{int expr1}{int expr2}
\IntMathRand{int expr1}{int expr2}

# Creating and Using Integers
\IntNew %<\intvar%>
\IntNew{cmd}#Sd
\IntConst %<\intvar%> {%<int expr%>}
\IntConst{cmd}#Sd
\IntUse %<\intvar%>

# Viewing Integers
\IntLog{int expr}
\IntVarLog %<\intvar%>
\IntShow{int expr}
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
\IntStepInline{init value}{step}{final value}{code%definition}
\IntStepVariable{init value}{step}{final value}{cmd}{code%definition}#Sd
\IntStepVariable{%<init value%>} {%<step%>} {%<final value%>} %<\tlvar%> {%<code%>}

# Integer Conditionals
\IntIfExist %<\intvar%>
\IntIfExistTF %<\intvar%> {%<true code%>} {%<false code%>}
\IntIfOdd{int expr}
\IntIfOddTF{int expr}{true code}{false code}
\IntIfEven{int expr}
\IntIfEvenTF{int expr}{true code}{false code}
\IntCompare{%<int expr1%>} %<<relation>%> {%<int expr2%>}
\IntCompareTF{%<int expr1%>} %<<relation>%> {%<int expr2%>} {%<true code%>} {%<false code%>}

# Integer Case Functions
\IntCase{%<test int expr%>}{%<{int expr1} {code1} {int expr2} {code2} ...%>}
\IntCaseT{%<test int expr%>}{%<{int expr1} {code1} {int expr2} {code2} ...%>}{%<true code%>}
\IntCaseF{%<test int expr%>}{%<{int expr1} {code1} {int expr2} {code2} ...%>}{%<false code%>}
\IntCaseTF{%<test int expr%>}{%<{int expr1} {code1} {int expr2} {code2} ...%>}{%<true code%>}{%<false code%>}

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
\FpEval{fp expr}
\FpMathAdd{fp expr1}{fp expr2}
\FpMathSub{fp expr1}{fp expr2}
\FpMathMult{fp expr1}{fp expr2}
\FpMathDiv{fp expr1}{fp expr2}
\FpMathSign{fp expr}
\FpMathAbs{fp expr}
\FpMathMax{fp expr1}{fp expr2}
\FpMathMin{fp expr1}{fp expr2}

# Creating and Using Floating Points
\FpNew %<\fpvar%>
\FpNew{cmd}#Sd
\FpConst %<\fpvar%> {%<fp expr%>}
\FpConst{cmd}#Sd
\FpUse %<\fpvar%>

# Viewing Floating Points
\FpLog{fp expr}
\FpVarLog %<\fpvar%>
\FpShow{fp expr}
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
\FpStepInline{init value}{step}{final value}{code%definition}
\FpStepVariable{init value}{step}{final value}{cmd}{code%definition}#Sd
\FpStepVariable{%<init value%>} {%<step%>} {%<final value%>} %<\tlvar%> {%<code%>}

# Float Point Conditionals
\FpIfExist %<\fpvar%>
\FpIfExistTF %<\fpvar%> {%<true code%>} {%<false code%>}
\FpCompare{%<fp expr1%>} %<<relation>%> {%<fp expr2%>}
\FpCompareTF{%<fp expr1%>} %<<relation>%> {%<fp expr2%>} {%<true code%>} {%<false code%>}

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
\DimEval{dim expr}
\DimMathAdd{dim expr1}{dim expr2}
\DimMathSub{dim expr1}{dim expr2}
\DimMathRatio{dim expr1}{dim expr2}
\DimMathSign{dim expr}
\DimMathAbs{dim expr}
\DimMathMax{dim expr1}{dim expr2}
\DimMathMin{dim expr1}{dim expr2}

# Creating and Using Dimensions
\DimNew %<\dimen%>
\DimNew{cmd}#Sd
\DimConst %<\dimen%> {%<dim expr%>}
\DimConst{cmd}#Sd
\DimUse %<\dimen%>

# Viewing Dimensions
\DimLog{dim expr}
\DimVarLog %<\dimen%>
\DimShow{dim expr}
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
\DimStepInline{init value}{step}{final value}{code%definition}
\DimStepVariable{init value}{step}{final value}{cmd}{code%definition}#Sd
\DimStepVariable{%<init value%>} {%<step%>} {%<final value%>} %<\tlvar%> {%<code%>}

# Dimension Conditionals
\DimIfExist %<\dimen%>
\DimIfExistTF %<\dimen%> {%<true code%>} {%<false code%>}
\DimCompare{%<dim expr1%>} %<<relation>%> {%<dim expr2%>}
\DimCompareTF{%<dim expr1%>} %<<relation>%> {%<dim expr2%>} {%<true code%>} {%<false code%>}

# Dimension Case Functions
\DimCase{%<test dim expr%>}{%<{dim expr1} {code1} {dim expr2} {code2} ...%>}
\DimCaseT{%<test dim expr%>}{%<{dim expr1} {code1} {dim expr2} {code2} ...%>}{%<true code%>}
\DimCaseF{%<test dim expr%>}{%<{dim expr1} {code1} {dim expr2} {code2} ...%>}{%<false code%>}
\DimCaseTF{%<test dim expr%>}{%<{dim expr1} {code1} {dim expr2} {code2} ...%>}{%<true code%>}{%<false code%>}

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
\ClistJoin{comma list}{separator}
\ClistJoinExtended{comma list}{sep for 2}{sep for >2}{sep for final 2}

# Viewing Comma Lists
\ClistLog{comma list}
\ClistVarLog %<\clistvar%>
\ClistShow{comma list}
\ClistVarShow %<\clistvar%>

# Setting Comma Lists
\ClistSet %<\clistvar%> {%<comma list%>}
\ClistSet{cmd}#Sd
\ClistSetEq %<\clistvar1 \clistvar2%>
\ClistSetEq{cmd}#Sd
\ClistClear %<\clistvar%>
\ClistClearNew %<\clistvar%>
\ClistClearNew{cmd}#Sd
\ClistConcat %<\clistvar1 \clistvar2 \clistvar3%>
\ClistPutLeft %<\clistvar%> {%<comma list%>}
\ClistPutRight %<\clistvar%> {%<comma list%>}

# Modifying Comma Lists
\ClistRemoveDuplicates %<\clistvar%>
\ClistRemoveAll %<\clistvar%> {%<item%>}
\ClistReverse %<\clistvar%>

# Working with the Contents of Comma Lists
\ClistCount{comma list}
\ClistVarCount %<\clistvar%>
\ClistItem{comma list}{int expr}
\ClistVarItem %<\clistvar%> {%<int expr%>}
\ClistRandItem{comma list}
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
\ClistMapInline{comma list}{inline function}
\ClistVarMapInline %<\clistvar%> {%<inline function%>}
\ClistMapVariable{comma list}{cmd}{def}#Sd
\ClistMapVariable{%<comma list%>} %<\variable%> {%<code%>}
\ClistVarMapVariable{clistvar}{cmd}{def}#Sd
\ClistVarMapVariable %<\clistvar \variable%> {%<code%>}

# Comma List Conditionals
\ClistIfExist %<\clistvar%>
\ClistIfExistTF %<\clistvar%> {%<true code%>} {%<false code%>}
\ClistIfEmpty{comma list}
\ClistIfEmptyTF{comma list}{true code}{false code}
\ClistVarIfEmpty %<\clistvar%>
\ClistVarIfEmptyTF %<\clistvar%> {%<true code%>} {%<false code%>}
\ClistIfIn{comma list}{item}
\ClistIfInTF{comma list}{item}{true code}{false code}
\ClistVarIfIn %<\clistvar%> {%<item%>}
\ClistVarIfInTF %<\clistvar%> {%<item%>} {%<true code%>} {%<false code%>}

## not documented ##
\Break#S
\PrgBreak#S
\BreakDo#S
\PrgBreakDo#S
\UseName{tokens}#S
\UseValue#S
\UseExpand{tokens}#S
\cNoValueTl#S
\SortReturnSame#S
\SortReturnSwapped#S
\ClistSetFromSeq{cmd}{arg}#Sd
\ClistSort{arg1}{arg2}#S
\ClistMapBreak#S