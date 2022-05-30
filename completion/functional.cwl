# functional package
# Matthew Bertucci 2022/05/23 for v2022G

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
\prgNewFunction %<\function%> {%<arg spec%>} {%<code%>}
\prgNewFunction{cmd}{xargs}{def}#Sd
\prgSetEqFunction %<\function1 \function2%>
\prgSetEqFunction{cmd}#Sd
\prgNewConditional %<\function%> {%<arg spec%>} {%<code%>}
\prgNewConditional{cmd}{xargs}{def}#Sd

# Collecting Returned Values
\prgReturn{tokens}
\prgPrint{tokens}
\gResultTl

# Running Code with Anonymous Functions
\prgDo{code}
\prgRunOneArgCode{arg1}{code}
\prgRunTwoArgCode{arg1}{arg2}{code}
\prgRunThreeArgCode{arg1}{arg2}{arg3}{code}
\prgRunFourArgCode{arg1}{arg2}{arg3}{arg4}{code}

## Argument Using (Use) ##
# Expanding Tokens
\expName{csname}
\expValue %<\variable%>
\expWhole{tokens}
\unExpand{tokens}
\onlyName{tokens}
\onlyValue{tokens}

# Using Tokens
\useOne{arg}
\gobbleOne{arg}
\useGobble{arg1}{arg2}
\gobbleUse{arg1}{arg2}

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
\boolNew %<\boolvar%>
\boolNew{cmd}#Sd
\boolConst %<\boolvar%> {%<bool expr%>}
\boolConst{cmd}#Sd
\boolSet %<\boolvar%> {%<bool expr%>}
\boolSet{cmd}#Sd
\boolSetTrue %<\boolvar%>
\boolSetFalse %<\boolvar%>
\boolSetEq %<\boolvar1 \boolvar2%>

# Viewing Booleans
\boolLog {bool expr}
\boolVarLog %<\boolvar%>
\boolShow {bool expr}
\boolVarShow %<\boolvar%>

# Booleans and Conditionals
\boolIfExist %<\boolvar%>
\boolIfExistT %<\boolvar%> {%<true code%>}
\boolIfExistF %<\boolvar%> {%<false code%>}
\boolIfExistTF %<\boolvar%> {%<true code%>} {%<false code%>}
\boolVarIf %<\boolvar%>
\boolVarIfT %<\boolvar%> {%<true code%>}
\boolVarIfF %<\boolvar%> {%<false code%>}
\boolVarIfTF %<\boolvar%> {%<true code%>} {%<false code%>}
\boolVarNot %<\boolvar%>
\boolVarNotT %<\boolvar%> {%<true code%>}
\boolVarNotF %<\boolvar%> {%<false code%>}
\boolVarNotTF %<\boolvar%> {%<true code%>} {%<false code%>}
\boolVarAnd %<\boolvar1 \boolvar2%>
\boolVarAndT %<\boolvar1 \boolvar2%> {%<true code%>}
\boolVarAndF %<\boolvar1 \boolvar2%> {%<false code%>}
\boolVarAndTF %<\boolvar1 \boolvar2%> {%<true code%>} {%<false code%>}
\boolVarOr %<\boolvar1 \boolvar2%>
\boolVarOrT %<\boolvar1 \boolvar2%> {%<true code%>}
\boolVarOrF %<\boolvar1 \boolvar2%> {%<false code%>}
\boolVarOrTF %<\boolvar1 \boolvar2%> {%<true code%>} {%<false code%>}
\boolVarXor %<\boolvar1 \boolvar2%>
\boolVarXorT %<\boolvar1 \boolvar2%> {%<true code%>}
\boolVarXorF %<\boolvar1 \boolvar2%> {%<false code%>}
\boolVarXorTF %<\boolvar1 \boolvar2%> {%<true code%>} {%<false code%>}

# Booleans and Logical Loops #
\boolVarDoUntil %<\boolvar%> {%<code%>}
\boolVarDoWhile %<\boolvar%> {%<code%>}
\boolVarUntilDo %<\boolvar%> {%<code%>}
\boolVarWhileDo %<\boolvar%> {%<code%>}

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
\tlNew %<\tlvar%>
\tlNew{cmd}#Sd
\tlConst %<\tlvar%> {%<tokens%>}
\tlConst{cmd}{def}#Sd
\tlUse %<\tlvar%>
\tlToStr {tokens}
\tlToStr{tokens%definition}#S
\tlVarToStr %<\tlvar%>

# Viewing Token Lists
\tlLog {tokens}
\tlLog{tokens%definition}#S
\tlVarLog %<\tlvar%>
\tlShow {tokens}
\tlShow{tokens%definition}#S
\tlVarShow %<\tlvar%>

# Setting Token List Variables
\tlSet %<\tlvar%> {%<tokens%>}
\tlSet{cmd}{def}#Sd
\tlSetEq %<\tlvar1 \tlvar2%>
\tlSetEq{cmd}#Sd
\tlClear %<\tlvar%>
\tlClearNew %<\tlvar%>
\tlClearNew{cmd}#Sd
\tlConcat %<\tlvar1 \tlvar2 \tlvar3%>
\tlConcat{cmd}#Sd
\tlPutLeft %<\tlvar%> {%<tokens%>}
\tlPutRight %<\tlvar%> {%<tokens%>}

# Replacing Tokens
\tlVarReplaceOnce %<\tlvar%> {%<old tokens%>} {%<new tokens%>}
\tlVarReplaceAll %<\tlvar%> {%<old tokens%>} {%<new tokens%>}
\tlVarRemoveOnce %<\tlvar%> {%<tokens%>}
\tlVarRemoveAll %<\tlvar%> {%<tokens%>}
\tlTrimSpaces {tokens}
\tlVarTrimSpaces %<\tlvar%>

# Working with the Content of Token Lists
\tlCount {tokens}
\tlCount{tokens%definition}#S
\tlVarCount %<\tlvar%>
\tlHead {tokens}
\tlVarHead %<\tlvar%>
\tlTail {tokens}
\tlVarTail %<\tlvar%>
\tlItem {tokens} {int expr}
\tlVarItem %<\tlvar%> {%<int expr%>}
\tlRandItem {tokens}
\tlVarRandItem %<\tlvar%>

# Mapping over Token Lists
\tlMapInline {tokens} {inline function}
\tlVarMapInline %<\tlvar%> {%<inline function%>}
\tlMapVariable{tokens}{cmd}{def}#Sd
\tlMapVariable {%<tokens%>} %<\variable%> {%<code%>}
\tlVarMapVariable{tlvar}{cmd}{def}#Sd
\tlVarMapVariable %<\tlvar \variable%> {%<code%>}

# Token List Conditionals
\tlIfExist %<\tlvar%>
\tlIfExistT %<\tlvar%> {%<true code%>}
\tlIfExistF %<\tlvar%> {%<false code%>}
\tlIfExistTF %<\tlvar%> {%<true code%>} {%<false code%>}
\tlIfEmpty {tokens}
\tlIfEmptyT {tokens} {true code}
\tlIfEmptyF {tokens} {false code}
\tlIfEmptyTF {tokens} {true code} {false code}
\tlVarIfEmpty %<\tlvar%>
\tlVarIfEmptyT %<\tlvar%> {%<true code%>}
\tlVarIfEmptyF %<\tlvar%> {%<false code%>}
\tlVarIfEmptyTF %<\tlvar%> {%<true code%>} {%<false code%>}
\tlIfBlank {tokens}
\tlIfBlankT {tokens} {true code}
\tlIfBlankF {tokens} {false code}
\tlIfBlankTF {tokens} {true code} {false code}
\tlIfEq {tokens1} {tokens2}
\tlIfEqT {tokens1} {tokens2} {true code}
\tlIfEqF {tokens1} {tokens2} {false code}
\tlIfEqTF {tokens1} {tokens2} {true code} {false code}
\tlVarIfEq %<\tlvar1 \tlvar2%>
\tlVarIfEqT %<\tlvar1 \tlvar2%> {%<true code%>}
\tlVarIfEqF %<\tlvar1 \tlvar2%> {%<false code%>}
\tlVarIfEqTF %<\tlvar1 \tlvar2%> {%<true code%>} {%<false code%>}
\tlIfIn {tokens1} {tokens2}
\tlIfInT {tokens1} {tokens2} {true code}
\tlIfInF {tokens1} {tokens2} {false code}
\tlIfInTF {tokens1} {tokens2} {true code} {false code}
\tlVarIfIn %<\tlvar%> {%<tokens%>}
\tlVarIfInT %<\tlvar%> {%<tokens%>} {%<true code%>}
\tlVarIfInF %<\tlvar%> {%<tokens%>} {%<false code%>}
\tlVarIfInTF %<\tlvar%> {%<tokens%>} {%<true code%>} {%<false code%>}
\tlIfSingle {tokens}
\tlIfSingleT {tokens} {true code}
\tlIfSingleF {tokens} {false code}
\tlIfSingleTF {tokens} {true code} {false code}
\tlVarIfSingle %<\tlvar%>
\tlVarIfSingleT %<\tlvar%> {%<true code%>}
\tlVarIfSingleF %<\tlvar%> {%<false code%>}
\tlVarIfSingleTF %<\tlvar%> {%<true code%>} {%<false code%>}

# Token List Case Functions
\tlVarCase %<\tlvar%> {%<\tlvar1 {code1} \tlvar2 {code2} ...%>}
\tlVarCaseT %<\tlvar%> {%<\tlvar1 {code1} \tlvar2 {code2} ...%>} {%<true code%>}
\tlVarCaseF %<\tlvar%> {%<\tlvar1 {code1} \tlvar2 {code2} ...%>} {%<false code%>}
\tlVarCaseTF %<\tlvar%> {%<\tlvar1 {code1} \tlvar2 {code2} ...%>} {%<true code%>} {%<false code%>}

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
\strNew %<\strvar%>
\strNew{cmd}#Sd
\strConst %<\strvar%> {%<tokens%>}
\strConst{cmd}{def}#Sd
\strUse %<\strvar%>

# Viewing Strings
\strLog {tokens}
\strLog{tokens%definition}#S
\strVarLog %<\strvar%>
\strShow {tokens}
\strShow{tokens%definition}#S
\strVarShow %<\strvar%>

# Setting String Variables
\strSet %<\strvar%> {%<tokens%>}
\strSet{cmd}{def}#Sd
\strSetEq %<\strvar1 \strvar2%>
\strClear %<\strvar%>
\strClearNew %<\strvar%>
\strClearNew{cmd}#Sd
\strConcat %<\strvar1 \strvar2 \strvar3%>
\strConcat{cmd}#Sd
\strPutLeft %<\strvar%> {%<tokens%>}
\strPutRight %<\strvar%> {%<tokens%>}

# Modifying String Variables
\strVarReplaceOnce %<\tlvar%> {%<old tokens%>} {%<new tokens%>}
\strVarReplaceAll %<\tlvar%> {%<old tokens%>} {%<new tokens%>}
\strVarRemoveOnce %<\strvar%> {%<tokens%>}
\strVarRemoveAll %<\strvar%> {%<tokens%>}

# Working with the Content of Strings
\strCount {tokens}
\strCount{tokens%definition}#S
\strSize {tokens}#*
\strSize{tokens%definition}#S
\strVarCount %<\tlvar%>
\strHead {tokens}
\strVarHead %<\tlvar%>
\strTail {tokens}
\strVarTail %<\tlvar%>
\strItem {tokens} {int expr}
\strVarItem %<\tlvar%> {%<int expr%>}

# Mapping over Strings
\strMapInline {tokens} {inline function}
\strVarMapInline %<\tlvar%> {%<inline function%>}
\strMapVariable{tokens}{cmd}{def}#Sd
\strMapVariable {%<tokens%>} %<\variable%> {%<code%>}
\strVarMapVariable{strvar}{cmd}{def}#Sd
\strVarMapVariable %<\strvar \variable%> {%<code%>}

# String Conditionals
\strIfExist %<\strvar%>
\strIfExistT %<\strvar%> {%<true code%>}
\strIfExistF %<\strvar%> {%<false code%>}
\strIfExistTF %<\strvar%> {%<true code%>} {%<false code%>}
\strVarIfEmpty %<\strvar%>
\strVarIfEmptyT %<\strvar%> {%<true code%>}
\strVarIfEmptyF %<\strvar%> {%<false code%>}
\strVarIfEmptyTF %<\strvar%> {%<true code%>} {%<false code%>}
\strIfEq {tokens1} {tokens2}
\strIfEqT {tokens1} {tokens2} {true code}
\strIfEqF {tokens1} {tokens2} {false code}
\strIfEqTF {tokens1} {tokens2} {true code} {false code}
\strVarIfEq %<\strvar1 \strvar2%>
\strVarIfEqT %<\strvar1 \strvar2%> {%<true code%>}
\strVarIfEqF %<\strvar1 \strvar2%> {%<false code%>}
\strVarIfEqTF %<\strvar1 \strvar2%> {%<true code%>} {%<false code%>}
\strIfIn {tokens1} {tokens2}
\strIfInT {tokens1} {tokens2} {true code}
\strIfInF {tokens1} {tokens2} {false code}
\strIfInTF {tokens1} {tokens2} {true code} {false code}
\strVarIfIn %<\strvar%> {%<tokens%>}
\strVarIfInT %<\strvar%> {%<tokens%>} {%<true code%>}
\strVarIfInF %<\strvar%> {%<tokens%>} {%<false code%>}
\strVarIfInTF %<\strvar%> {%<tokens%>} {%<true code%>} {%<false code%>}
\strCompare {%<tokens1%>} %<<relation>%> {%<tokens2%>}
\strCompareT {%<tokens1%>} %<<relation>%> {%<tokens2%>} {%<true code%>}
\strCompareF {%<tokens1%>} %<<relation>%> {%<tokens2%>} {%<false code%>}
\strCompareTF {%<tokens1%>} %<<relation>%> {%<tokens2%>} {%<true code%>} {%<false code%>}
\strIfCompare {%<tokens1%>} %<<relation>%> {%<tokens2%>}#*
\strIfCompareT {%<tokens1%>} %<<relation>%> {%<tokens2%>} {%<true code%>}#*
\strIfCompareF {%<tokens1%>} %<<relation>%> {%<tokens2%>} {%<false code%>}#*
\strIfCompareTF {%<tokens1%>} %<<relation>%> {%<tokens2%>} {%<true code%>} {%<false code%>}#*

# String Case Functions
\strCase {%<test string%>} {%<{string1} {code1} {string2} {code2} ...%>}
\strCaseT {%<test string%>} {%<{string1} {code1} {string2} {code2} ...%>} {%<true code%>}
\strCaseF {%<test string%>} {%<{string1} {code1} {string2} {code2} ...%>} {%<false code%>}
\strCaseTF {%<test string%>} {%<{string1} {code1} {string2} {code2} ...%>} {%<true code%>} {%<false code%>}

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
\intEval {int expr}
\intMathAdd {int expr1} {int expr2}
\intMathSub {int expr1} {int expr2}
\intMathMult {int expr1} {int expr2}
\intMathDiv {int expr1} {int expr2}
\intMathDivTruncate {int expr1} {int expr2}
\intMathSign {int expr}
\intMathAbs {int expr}
\intMathMax {int expr1} {int expr2}
\intMathMin {int expr1} {int expr2}
\intMathMod {int expr1} {int expr2}
\intMathRand {int expr1} {int expr2}

# Creating and Using Integers
\intNew %<\intvar%>
\intNew{cmd}#Sd
\intConst %<\intvar%> {%<int expr%>}
\intConst{cmd}#Sd
\intUse %<\intvar%>

# Viewing Integers
\intLog {int expr}
\intVarLog %<\intvar%>
\intShow {int expr}
\intVarShow %<\intvar%>

# Setting Integer Variables
\intSet %<\intvar%> {%<int expr%>}
\intSet{cmd}#Sd
\intSetEq %<\intvar1 \intvar2%>
\intSetEq{cmd}#Sd
\intZero %<\intvar%>
\intZeroNew %<\intvar%>
\intZeroNew{cmd}#Sd
\intIncr %<\intvar%>
\intDecr %<\intvar%>
\intAdd %<\intvar%> {%<int expr%>}
\intSub %<\intvar%> {%<int expr%>}

# Integer Step Functions
\intReplicate {int expr} {tokens}
\intStepInline {init value} {step} {final value} {code}
\intStepOneInline {init value} {final value} {code}
\intStepVariable{init value}{step}{final value}{cmd}{code%definition}#Sd
\intStepVariable {%<init value%>} {%<step%>} {%<final value%>} %<\tlvar%> {%<code%>}
\intStepOneVariable{init value}{final value}{cmd}{code%definition}#Sd
\intStepOneVariable {%<init value%>} {%<final value%>} %<\tlvar%> {%<code%>}

# Integer Conditionals
\intIfExist %<\intvar%>
\intIfExistT %<\intvar%> {%<true code%>}
\intIfExistF %<\intvar%> {%<false code%>}
\intIfExistTF %<\intvar%> {%<true code%>} {%<false code%>}
\intIfOdd {int expr}
\intIfOddT {int expr} {true code}
\intIfOddF {int expr} {false code}
\intIfOddTF {int expr} {true code} {false code}
\intIfEven {int expr}
\intIfEvenT {int expr} {true code}
\intIfEvenF {int expr} {false code}
\intIfEvenTF {int expr} {true code} {false code}
\intCompare {%<int expr1%>} %<<relation>%> {%<int expr2%>}
\intCompareT {%<int expr1%>} %<<relation>%> {%<int expr2%>} {%<true code%>}
\intCompareF {%<int expr1%>} %<<relation>%> {%<int expr2%>} {%<false code%>}
\intCompareTF {%<int expr1%>} %<<relation>%> {%<int expr2%>} {%<true code%>} {%<false code%>}

# Integer Case Functions
\intCase {%<test int expr%>} {%<{int expr1} {code1} {int expr2} {code2} ...%>}
\intCaseT {%<test int expr%>} {%<{int expr1} {code1} {int expr2} {code2} ...%>} {%<true code%>}
\intCaseF {%<test int expr%>} {%<{int expr1} {code1} {int expr2} {code2} ...%>} {%<false code%>}
\intCaseTF {%<test int expr%>} {%<{int expr1} {code1} {int expr2} {code2} ...%>} {%<true code%>} {%<false code%>}

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
\fpEval {fp expr}
\fpMathAdd {fp expr1} {fp expr2}
\fpMathSub {fp expr1} {fp expr2}
\fpMathMult {fp expr1} {fp expr2}
\fpMathDiv {fp expr1} {fp expr2}
\fpMathSign {fp expr}
\fpMathAbs {fp expr}
\fpMathMax {fp expr1} {fp expr2}
\fpMathMin {fp expr1} {fp expr2}

# Creating and Using Floating Points
\fpNew %<\fpvar%>
\fpNew{cmd}#Sd
\fpConst %<\fpvar%> {%<fp expr%>}
\fpConst{cmd}#Sd
\fpUse %<\fpvar%>

# Viewing Floating Points
\fpLog {fp expr}
\fpVarLog %<\fpvar%>
\fpShow {fp expr}
\fpVarShow %<\fpvar%>

# Setting Floating Point Variables
\fpSet %<\fpvar%> {%<fp expr%>}
\fpSet{cmd}#Sd
\fpSetEq %<\fpvar1 \fpvar2%>
\fpSetEq{cmd}#Sd
\fpZero %<\fpvar%>
\fpZeroNew %<\fpvar%>
\fpZeroNew{cmd}#Sd
\fpAdd %<\fpvar%> {%<fp expr%>}
\fpSub %<\fpvar%> {%<fp expr%>}

# Floating Point Step Functions
\fpStepInline {init value} {step} {final value} {code}
\fpStepVariable{init value}{step}{final value}{cmd}{code%definition}#Sd
\fpStepVariable {%<init value%>} {%<step%>} {%<final value%>} %<\tlvar%> {%<code%>}

# Float Point Conditionals
\fpIfExist %<\fpvar%>
\fpIfExistT %<\fpvar%> {%<true code%>}
\fpIfExistF %<\fpvar%> {%<false code%>}
\fpIfExistTF %<\fpvar%> {%<true code%>} {%<false code%>}
\fpCompare {%<fp expr1%>} %<<relation>%> {%<fp expr2%>}
\fpCompareT {%<fp expr1%>} %<<relation>%> {%<fp expr2%>} {%<true code%>}
\fpCompareF {%<fp expr1%>} %<<relation>%> {%<fp expr2%>} {%<false code%>}
\fpCompareTF {%<fp expr1%>} %<<relation>%> {%<fp expr2%>} {%<true code%>} {%<false code%>}

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
\dimEval {dim expr}
\dimMathAdd {dim expr1} {dim expr2}
\dimMathSub {dim expr1} {dim expr2}
\dimMathRatio {dim expr1} {dim expr2}
\dimMathSign {dim expr}
\dimMathAbs {dim expr}
\dimMathMax {dim expr1} {dim expr2}
\dimMathMin {dim expr1} {dim expr2}

# Creating and Using Dimensions
\dimNew %<\dimen%>
\dimNew{cmd}#Sd
\dimConst %<\dimen%> {%<dim expr%>}
\dimConst{cmd}#Sd
\dimUse %<\dimen%>

# Viewing Dimensions
\dimLog {dim expr}
\dimVarLog %<\dimen%>
\dimShow {dim expr}
\dimVarShow %<\dimen%>

# Setting Dimension Variables
\dimSet %<\dimen%> {%<dim expr%>}
\dimSet{cmd}#Sd
\dimSetEq %<\dimen1 \dimen2%>
\dimSetEq{cmd}#Sd
\dimZero %<\dimen%>
\dimZeroNew %<\dimen%>
\dimZeroNew{cmd}#Sd
\dimAdd %<\dimen%> {%<dim expr%>}
\dimSub %<\dimen%> {%<dim expr%>}

# Dimension Step Functions
\dimStepInline {init value} {step} {final value} {code}
\dimStepVariable{init value}{step}{final value}{cmd}{code%definition}#Sd
\dimStepVariable {%<init value%>} {%<step%>} {%<final value%>} %<\tlvar%> {%<code%>}

# Dimension Conditionals
\dimIfExist %<\dimen%>
\dimIfExistT %<\dimen%> {%<true code%>}
\dimIfExistF %<\dimen%> {%<false code%>}
\dimIfExistTF %<\dimen%> {%<true code%>} {%<false code%>}
\dimCompare {%<dim expr1%>} %<<relation>%> {%<dim expr2%>}
\dimCompareT {%<dim expr1%>} %<<relation>%> {%<dim expr2%>} {%<true code%>}
\dimCompareF {%<dim expr1%>} %<<relation>%> {%<dim expr2%>} {%<false code%>}
\dimCompareTF {%<dim expr1%>} %<<relation>%> {%<dim expr2%>} {%<true code%>} {%<false code%>}

# Dimension Case Functions
\dimCase {%<test dim expr%>} {%<{dim expr1} {code1} {dim expr2} {code2} ...%>}
\dimCaseT {%<test dim expr%>} {%<{dim expr1} {code1} {dim expr2} {code2} ...%>}{%<true code%>}
\dimCaseF {%<test dim expr%>} {%<{dim expr1} {code1} {dim expr2} {code2} ...%>}{%<false code%>}
\dimCaseTF {%<test dim expr%>} {%<{dim expr1} {code1} {dim expr2} {code2} ...%>}{%<true code%>}{%<false code%>}

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
\clistNew %<\clistvar%>
\clistNew{cmd}#Sd
\clistConst %<\clistvar%> {%<comma list%>}
\clistConst{cmd}#Sd
\clistVarJoin %<\clistvar%> {%<separator%>}
\clistVarJoinExtended %<\clistvar%> {%<sep for 2%>} {%<sep for >2%>} {%<sep for final 2%>}
\clistJoin {comma list} {separator}
\clistJoinExtended {comma list} {sep for 2} {sep for >2} {sep for final 2}

# Viewing Comma Lists
\clistLog {comma list}
\clistVarLog %<\clistvar%>
\clistShow {comma list}
\clistVarShow %<\clistvar%>

# Setting Comma Lists
\clistSet %<\clistvar%> {%<comma list%>}
\clistSet{cmd}#Sd
\clistSetEq %<\clistvar1 \clistvar2%>
\clistSetEq{cmd}#Sd
\clistSetFromSeq %<\clistvar \seqvar%>
\clistSetFromSeq{cmd}{arg}#Sd
\clistClear %<\clistvar%>
\clistClearNew %<\clistvar%>
\clistClearNew{cmd}#Sd
\clistConcat %<\clistvar1 \clistvar2 \clistvar3%>
\clistPutLeft %<\clistvar%> {%<comma list%>}
\clistPutRight %<\clistvar%> {%<comma list%>}

# Modifying Comma Lists
\clistVarRemoveDuplicates %<\clistvar%>
\clistVarRemoveAll %<\clistvar%> {%<item%>}
\clistVarReverse %<\clistvar%>

# Working with the Contents of Comma Lists
\clistCount {comma list}
\clistVarCount %<\clistvar%>
\clistItem {comma list} {int expr}
\clistVarItem %<\clistvar%> {%<int expr%>}
\clistRandItem {comma list}
\clistVarRandItem %<\clistvar%>

# Comma Lists as Stacks
\clistGet %<\clistvar \tlvar%>
\clistGet{clistvar}{cmd}#Sd
\clistGetT %<\clistvar \tlvar%> {%<true code%>}
\clistGetT{clistvar}{cmd}#Sd
\clistGetF %<\clistvar \tlvar%> {%<false code%>}
\clistGetF{clistvar}{cmd}#Sd
\clistGetTF %<\clistvar \tlvar%> {%<true code%>} {%<false code%>}
\clistGetTF{clistvar}{cmd}#Sd
\clistPop %<\clistvar \tlvar%>
\clistPop{clistvar}{cmd}#Sd
\clistPopT %<\clistvar \tlvar%> {%<true code%>}
\clistPopT{clistvar}{cmd}#Sd
\clistPopF %<\clistvar \tlvar%> {%<false code%>}
\clistPopF{clistvar}{cmd}#Sd
\clistPopTF %<\clistvar \tlvar%> {%<true code%>} {%<false code%>}
\clistPopTF{clistvar}{cmd}#Sd
\clistPush %<\clistvar%> {%<items%>}

# Mapping over Comma Lists
\clistMapInline {comma list} {inline function}
\clistVarMapInline %<\clistvar%> {%<inline function%>}
\clistMapVariable{comma list}{cmd}{def}#Sd
\clistMapVariable {%<comma list%>} %<\variable%> {%<code%>}
\clistVarMapVariable{clistvar}{cmd}{def}#Sd
\clistVarMapVariable %<\clistvar \variable%> {%<code%>}

# Comma List Conditionals
\clistIfExist %<\clistvar%>
\clistIfExistT %<\clistvar%> {%<true code%>}
\clistIfExistF %<\clistvar%> {%<false code%>}
\clistIfExistTF %<\clistvar%> {%<true code%>} {%<false code%>}
\clistIfEmpty {comma list}
\clistIfEmptyT {comma list} {true code}
\clistIfEmptyF {comma list} {false code}
\clistIfEmptyTF {comma list} {true code} {false code}
\clistVarIfEmpty %<\clistvar%>
\clistVarIfEmptyT %<\clistvar%> {%<true code%>}
\clistVarIfEmptyF %<\clistvar%> {%<false code%>}
\clistVarIfEmptyTF %<\clistvar%> {%<true code%>} {%<false code%>}
\clistIfIn {comma list} {item}
\clistIfInT {comma list} {item} {true code}
\clistIfInF {comma list} {item} {false code}
\clistIfInTF {comma list} {item} {true code} {false code}
\clistVarIfIn %<\clistvar%> {%<item%>}
\clistVarIfInT %<\clistvar%> {%<item%>} {%<true code%>}
\clistVarIfInF %<\clistvar%> {%<item%>} {%<false code%>}
\clistVarIfInTF %<\clistvar%> {%<item%>} {%<true code%>} {%<false code%>}

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
\seqNew %<\seqvar%>
\seqNew{cmd}#Sd
\seqConstFromClist %<\seqvar%> {%<comma list%>}
\seqConstFromClist{cmd}#Sd
\seqVarJoin %<\seqvar%> {%<separator%>}
\seqVarJoinExtended %<\seqvar%> {%<sep for 2%>} {%<sep for >2%>} {%<sep for final 2%>}

# Viewing Sequences
\seqVarLog %<\seqvar%>
\seqVarShow %<\seqvar%>

# Setting Sequences
\seqSetFromClist %<\seqvar%> {%<comma list%>}
\seqSetFromClist{cmd}#Sd
\seqSetSplit %<\seqvar%> {%<delimiter%>} {%<tokens%>}
\seqSetSplit{cmd}#Sd
\seqSetEq %<\seqvar1 \seqvar2%>
\seqSetEq{cmd}#Sd
\seqClear %<\seqvar%>
\seqClearNew %<\seqvar%>
\seqClearNew{cmd}#Sd
\seqConcat %<\seqvar1 \seqvar2 \seqvar3%>
\seqPutLeft %<\seqvar%> {%<item%>}
\seqPutRight %<\seqvar%> {%<item%>}

# Modifying Sequences
\seqVarRemoveDuplicates %<\seqvar%>
\seqVarRemoveAll %<\seqvar%> {%<item%>}
\seqVarReverse %<\seqvar%>

# Working with the Contents of Sequences
\seqVarCount %<\seqvar%>
\seqVarItem %<\seqvar%> {%<int expr%>}
\seqVarRandItem %<\seqvar%>

# Sequences as Stacks
\seqGet %<\seqvar \tlvar%>
\seqGetT %<\seqvar \tlvar%> {%<true code%>}
\seqGetF %<\seqvar \tlvar%> {%<false code%>}
\seqGetTF %<\seqvar \tlvar%> {%<true code%>} {%<false code%>}
\seqPop %<\seqvar \tlvar%>
\seqPopT %<\seqvar \tlvar%> {%<true code%>}
\seqPopF %<\seqvar \tlvar%> {%<false code%>}
\seqPopTF %<\seqvar \tlvar%> {%<true code%>} {%<false code%>}
\seqPush %<\seqvar%> {%<item%>}

# Recovering Items from Sequences
\seqGetLeft %<\seqvar \tlvar%>
\seqGetLeftT %<\seqvar \tlvar%> {%<true code%>}
\seqGetLeftF %<\seqvar \tlvar%> {%<false code%>}
\seqGetLeftTF %<\seqvar \tlvar%> {%<true code%>} {%<false code%>}
\seqGetRight %<\seqvar \tlvar%>
\seqGetRightT %<\seqvar \tlvar%> {%<true code%>}
\seqGetRightF %<\seqvar \tlvar%> {%<false code%>}
\seqGetRightTF %<\seqvar \tlvar%> {%<true code%>} {%<false code%>}
\seqPopLeft %<\seqvar \tlvar%>
\seqPopLeftT %<\seqvar \tlvar%> {%<true code%>}
\seqPopLeftF %<\seqvar \tlvar%> {%<false code%>}
\seqPopLeftTF %<\seqvar \tlvar%> {%<true code%>} {%<false code%>}
\seqPopRight %<\seqvar \tlvar%>
\seqPopRightT %<\seqvar \tlvar%> {%<true code%>}
\seqPopRightF %<\seqvar \tlvar%> {%<false code%>}
\seqPopRightTF %<\seqvar \tlvar%> {%<true code%>} {%<false code%>}

# Mapping over Sequences
\seqVarMapInline %<\seqvar%> {%<inline function%>}
\seqVarMapVariable{seqvar}{cmd}{def}#Sd
\seqVarMapVariable %<\seqvar \variable%> {%<code%>}

# Sequence Conditionals
\seqIfExist %<\seqvar%>
\seqIfExistT %<\seqvar%> {%<true code%>}
\seqIfExistF %<\seqvar%> {%<false code%>}
\seqIfExistTF %<\seqvar%> {%<true code%>} {%<false code%>}
\seqVarIfEmpty %<\seqvar%>
\seqVarIfEmptyT %<\seqvar%> {%<true code%>}
\seqVarIfEmptyF %<\seqvar%> {%<false code%>}
\seqVarIfEmptyTF %<\seqvar%> {%<true code%>} {%<false code%>}
\seqVarIfIn %<\seqvar%> {%<item%>}
\seqVarIfInT %<\seqvar%> {%<item%>} {%<true code%>}
\seqVarIfInF %<\seqvar%> {%<item%>} {%<false code%>}
\seqVarIfInTF %<\seqvar%> {%<item%>} {%<true code%>} {%<false code%>}

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
\propNew %<\propvar%>
\propNew{cmd}#Sd
\propConstFromKeyval %<\propvar%> {%<key1=value2, key2=value2, ...%>}
\propConstFromKeyval{cmd}#Sd
\propToKeyval %<\propvar%>

# Viewing Property Lists
\propVarLog %<\propvar%>
\propVarShow %<\propvar%>

# Setting Property Lists
\propSetFromKeyval %<\propvar%> {%<key1=value2, key2=value2, ...%>}
\propSetFromKeyval{cmd}#Sd
\propSetEq %<\propvar1 \propvar2%>
\propSetEq{cmd}#Sd
\propClear %<\propvar%>
\propClearNew %<\propvar%>
\propClearNew{cmd}#Sd
\propConcat %<\propvar1 \propvar2 \propvar3%>
\propPut %<\propvar%> {%<key%>} {%<value%>}
\propPutIfNew %<\propvar%> {%<key%>} {%<value%>}
\propPutFromKeyval %<\propvar%> {%<key1=value2, key2=value2, ...%>}
\propVarRemove %<\propvar%> {%<key%>}

# Recovering Values from Property Lists
\propVarCount %<\propvar%>
\propVarItem %<\propvar%> {%<key%>}
\propGet %<\propvar%> {%<key%>} %<\tlvar%>
\propGet{propvar}{key%plain}{cmd}#Sd
\propGetT %<\propvar%> {%<key%>} %<\tlvar%> {%<true code%>}
\propGetT{propvar}{key%plain}{cmd}#Sd
\propGetF %<\propvar%> {%<key%>} %<\tlvar%> {%<false code%>}
\propGetF{propvar}{key%plain}{cmd}#Sd
\propGetTF %<\propvar%> {%<key%>} %<\tlvar%> {%<true code%>} {%<false code%>}
\propGetTF{propvar}{key%plain}{cmd}#Sd
\propPop %<\propvar%> {%<key%>} %<\tlvar%>
\propPop{propvar}{key%plain}{cmd}#Sd
\propPopT %<\propvar%> {%<key%>} %<\tlvar%> {%<true code%>}
\propPopT{propvar}{key%plain}{cmd}#Sd
\propPopF %<\propvar%> {%<key%>} %<\tlvar%> {%<false code%>}
\propPopF{propvar}{key%plain}{cmd}#Sd
\propPopTF %<\propvar%> {%<key%>} %<\tlvar%> {%<true code%>} {%<false code%>}
\propPopTF{propvar}{key%plain}{cmd}#Sd

# Mapping over property lists
\propVarMapInline %<\propvar%> {%<inline function%>}

# Property List Conditionals
\propIfExist %<\propvar%>
\propIfExistT %<\propvar%> {%<true code%>}
\propIfExistF %<\propvar%> {%<false code%>}
\propIfExistTF %<\propvar%> {%<true code%>} {%<false code%>}
\propVarIfEmpty %<\propvar%>
\propVarIfEmptyT %<\propvar%> {%<true code%>}
\propVarIfEmptyF %<\propvar%> {%<false code%>}
\propVarIfEmptyTF %<\propvar%> {%<true code%>} {%<false code%>}
\propVarIfIn %<\propvar%> {%<key%>}
\propVarIfInT %<\propvar%> {%<key%>} {%<true code%>}
\propVarIfInF %<\propvar%> {%<key%>} {%<false code%>}
\propVarIfInTF %<\propvar%> {%<key%>} {%<true code%>} {%<false code%>}

## Regular Expressions (Regex) ##
# Regular Expression Variables
\lTmpaRegex
\lTmpbRegex
\lTmpcRegex
\lTmpiRegex
\lTmpjRegex
\lTmpkRegex
\gTmpaRegex
\gTmpbRegex
\gTmpcRegex
\gTmpiRegex
\gTmpjRegex
\gTmpkRegex

\regexNew %<\regexvar%>
\regex{cmd}#Sd
\regexSet %<\regexvar%> {%<regex%>}
\regexSet{cmd}{def}#Sd
\regexConst %<\regexvar%> {%<regex%>}
\regexConst{cmd}{def}#Sd
\regexLog {%<regex%>}
\regexVarLog %<\regexvar%>
\regexShow {%<regex%>}
\regexVarShow %<\regexvar%>

# Regular Expression Matching
\regexMatch {%<regex%>} {%<tokens%>}
\regexMatchT {%<regex%>} {%<tokens%>} {%<true code%>}
\regexMatchF {%<regex%>} {%<tokens%>} {%<false code%>}
\regexMatchTF {%<regex%>} {%<tokens%>} {%<true code%>} {%<false code%>}
\regexVarMatch %<\regexvar%> {%<tokens%>}
\regexVarMatchT %<\regexvar%> {%<tokens%>} {%<true code%>}
\regexVarMatchF %<\regexvar%> {%<tokens%>} {%<false code%>}
\regexVarMatchTF %<\regexvar%> {%<tokens%>} {%<true code%>} {%<false code%>}
\regexCount {%<regex%>} {%<tokens%>} %<\intvar%>
\regexVarCount  %<\regexvar%> {%<tokens%>} %<\intvar%>
\regexMatchCase {%<{regex1} {code1} {regex2} {code2} ...%>} {%<tokens%>}
\regexMatchCaseT {%<{regex1} {code1} {regex2} {code2} ...%>} {%<tokens%>} {%<true code%>}
\regexMatchCaseF {%<{regex1} {code1} {regex2} {code2} ...%>} {%<tokens%>} {%<false code%>}
\regexMatchCaseTF {%<{regex1} {code1} {regex2} {code2} ...%>} {%<tokens%>} {%<true code%>} {%<false code%>}

# Regular Expression Submatch Extraction
\regexExtractOnce {%<regex%>} {%<tokens%>} %<\seqvar%>
\regexExtractOnce{regex}{tokens}{cmd}#Sd
\regexExtractOnceT {%<regex%>} {%<tokens%>} %<\seqvar%> {%<true code%>}
\regexExtractOnceT{regex}{tokens}{cmd}#Sd
\regexExtractOnceF {%<regex%>} {%<tokens%>} %<\seqvar%> {%<false code%>}
\regexExtractOnceF{regex}{tokens}{cmd}#Sd
\regexExtractOnceTF {%<regex%>} {%<tokens%>} %<\seqvar%> {%<true code%>} {%<false code%>}
\regexExtractOnceTF{regex}{tokens}{cmd}#Sd
\regexVarExtractOnce %<\regexvar%> {%<tokens%>} %<\seqvar%>
\regexVarExtractOnce{regexvar}{tokens}{cmd}#Sd
\regexVarExtractOnceT %<\regexvar%> {%<tokens%>} %<\seqvar%> {%<true code%>}
\regexVarExtractOnceT{regexvar}{tokens}{cmd}#Sd
\regexVarExtractOnceF %<\regexvar%> {%<tokens%>} %<\seqvar%> {%<false code%>}
\regexVarExtractOnceF{regexvar}{tokens}{cmd}#Sd
\regexVarExtractOnceTF %<\regexvar%> {%<tokens%>} %<\seqvar%> {%<true code%>} {%<false code%>}
\regexVarExtractOnceTF{regexvar}{tokens}{cmd}#Sd
\regexExtractAll {%<regex%>} {%<tokens%>} %<\seqvar%>
\regexExtractAll{regex}{tokens}{cmd}#Sd
\regexExtractAllT {%<regex%>} {%<tokens%>} %<\seqvar%> {%<true code%>}
\regexExtractAllT{regex}{tokens}{cmd}#Sd
\regexExtractAllF {%<regex%>} {%<tokens%>} %<\seqvar%> {%<false code%>}
\regexExtractAllF{regex}{tokens}{cmd}#Sd
\regexExtractAllTF {%<regex%>} {%<tokens%>} %<\seqvar%> {%<true code%>} {%<false code%>}
\regexExtractAllTF{regex}{tokens}{cmd}#Sd
\regexVarExtractAll %<\regexvar%> {%<tokens%>} %<\seqvar%>
\regexVarExtractAll{regexvar}{tokens}{cmd}#Sd
\regexVarExtractAllT %<\regexvar%> {%<tokens%>} %<\seqvar%> {%<true code%>}
\regexVarExtractAllT{regexvar}{tokens}{cmd}#Sd
\regexVarExtractAllF %<\regexvar%> {%<tokens%>} %<\seqvar%> {%<false code%>}
\regexVarExtractAllF{regexvar}{tokens}{cmd}#Sd
\regexVarExtractAllTF %<\regexvar%> {%<tokens%>} %<\seqvar%> {%<true code%>} {%<false code%>}
\regexVarExtractAllTF{regexvar}{tokens}{cmd}#Sd
\regexSplit {%<regex%>} {%<tokens%>} %<\seqvar%>
\regexSplit{regex}{tokens}{cmd}#Sd
\regexSplitT {%<regex%>} {%<tokens%>} %<\seqvar%> {%<true code%>}
\regexSplitT{regex}{tokens}{cmd}#Sd
\regexSplitF {%<regex%>} {%<tokens%>} %<\seqvar%> {%<false code%>}
\regexSplitF{regex}{tokens}{cmd}#Sd
\regexSplitTF {%<regex%>} {%<tokens%>} %<\seqvar%> {%<true code%>} {%<false code%>}
\regexSplitTF{regex}{tokens}{cmd}#Sd
\regexVarSplit %<\regexvar%> {%<tokens%>} %<\seqvar%>
\regexVarSplit{regexvar}{tokens}{cmd}#Sd
\regexVarSplitT %<\regexvar%> {%<tokens%>} %<\seqvar%> {%<true code%>}
\regexVarSplitT{regexvar}{tokens}{cmd}#Sd
\regexVarSplitF %<\regexvar%> {%<tokens%>} %<\seqvar%> {%<false code%>}
\regexVarSplitF{regexvar}{tokens}{cmd}#Sd
\regexVarSplitTF %<\regexvar%> {%<tokens%>} %<\seqvar%> {%<true code%>} {%<false code%>}
\regexVarSplitTF{regexvar}{tokens}{cmd}#Sd

# Regular Expression Replacement
\regexReplaceOnce {%<regex%>} {%<replacement%>} %<\tlvar%>
\regexReplaceOnceT {%<regex%>} {%<replacement%>} %<\tlvar%> {%<true code%>}
\regexReplaceOnceF {%<regex%>} {%<replacement%>} %<\tlvar%> {%<false code%>}
\regexReplaceOnceTF {%<regex%>} {%<replacement%>} %<\tlvar%> {%<true code%>} {%<false code%>}
\regexVarReplaceOnce %<\regexvar%> {%<replacement%>} %<\tlvar%>
\regexVarReplaceOnceT %<\regexvar%> {%<replacement%>} %<\tlvar%> {%<true code%>}
\regexVarReplaceOnceF %<\regexvar%> {%<replacement%>} %<\tlvar%> {%<false code%>}
\regexVarReplaceOnceTF %<\regexvar%> {%<replacement%>} %<\tlvar%> {%<true code%>} {%<false code%>}
\regexReplaceAll {%<regex%>} {%<replacement%>} %<\tlvar%>
\regexReplaceAllT {%<regex%>} {%<replacement%>} %<\tlvar%> {%<true code%>}
\regexReplaceAllF {%<regex%>} {%<replacement%>} %<\tlvar%> {%<false code%>}
\regexReplaceAllTF {%<regex%>} {%<replacement%>} %<\tlvar%> {%<true code%>} {%<false code%>}
\regexVarReplaceAll %<\regexvar%> {%<replacement%>} %<\tlvar%>
\regexVarReplaceAllT %<\regexvar%> {%<replacement%>} %<\tlvar%> {%<true code%>}
\regexVarReplaceAllF %<\regexvar%> {%<replacement%>} %<\tlvar%> {%<false code%>}
\regexVarReplaceAllTF %<\regexvar%> {%<replacement%>} %<\tlvar%> {%<true code%>} {%<false code%>}
\regexReplaceCaseOnce {%<{regex1} {replacement1} {regex2} {replacement2} ...%>} %<\tlvar%>
\regexReplaceCaseOnceT {%<{regex1} {replacement1} {regex2} {replacement2} ...%>} %<\tlvar%> {%<true code%>}
\regexReplaceCaseOnceF {%<{regex1} {replacement1} {regex2} {replacement2} ...%>} %<\tlvar%> {%<false code%>}
\regexReplaceCaseOnceTF {%<{regex1} {replacement1} {regex2} {replacement2} ...%>} %<\tlvar%> {%<true code%>} {%<false code%>}
\regexReplaceCaseAll {%<{regex1} {replacement1} {regex2} {replacement2} ...%>} %<\tlvar%>
\regexReplaceCaseAllT {%<{regex1} {replacement1} {regex2} {replacement2} ...%>} %<\tlvar%> {%<true code%>}
\regexReplaceCaseAllF {%<{regex1} {replacement1} {regex2} {replacement2} ...%>} %<\tlvar%> {%<false code%>}
\regexReplaceCaseAllTF {%<{regex1} {replacement1} {regex2} {replacement2} ...%>} %<\tlvar%> {%<true code%>} {%<false code%>}

# Characters in Regular Expressions
\x{hh}#*
\a#*
\e#*
\f#*
\n#*
\r#*
\t#*

# Characters Classes
\d#*
\h#*
\s#*
\v#*
\w#*
\D#*
\H#*
\N#*
\S#*
\V#*
\W#*
\K#*

# Matching Exact Tokens
\c{regex}#*
\cC#*
\cB#*
\cE#*
\cM#*
\cT#*
\cP#*
\cU#*
\cD#*
\cS#*
\cL#*
\cO#*
\cA#*
\u{var name}#*
\ur{var name}#*

# Miscellaneous
\b#*
\B#*
\A#*
\Z#*
\z#*
\G#*

## Token Manipulation (Token) ##
\charLowercase %<char%>
\charUppercase %<char%>
\charTitlecase %<char%>
\charFoldcase %<char%>
\charStrLowercase %<char%>
\charStrUppercase %<char%>
\charStrTitlecase %<char%>
\charStrFoldcase %<char%>
\charSetLccode {int expr1} {int expr2}
\charSetUccode {int expr1} {int expr2}
\charValueLccode {int expr}
\charValueUccode {int expr}

## Text Processing (Text) ##
# Case Changing
\textExpand {text}
\textLowercase {text}
\textUppercase {text}
\textTitlecase {text}
\textTitlecaseFirst {text}
\textLangLowercase {language} {text}
\textLangUppercase {language} {text}
\textLangTitlecase {language} {text}
\textLangTitlecaseFirst {language} {text}

## Files (File) ##
# File Operation Functions
\fileInput {file name}
\fileInput{file}#Si
\fileIfExistInput {file name}
\fileIfExistInput{file}#Si
\fileIfExistInputF {file name} {false code}
\fileIfExistInputF{file}{false code}#Si
\fileGet {%<file name%>} {%<setup%>} %<\tlvar%>
\fileGet{file name}{setup}{cmd}#Sd
\fileGetT {%<file name%>} {%<setup%>} %<\tlvar%> {%<true code%>}
\fileGetT{file name}{setup}{cmd}{true code}#Sd
\fileGetF {%<file name%>} {%<setup%>} %<\tlvar%> {%<false code%>}
\fileGetF{file name}{setup}{cmd}{false code}#Sd
\fileGetTF {%<file name%>} {%<setup%>} %<\tlvar%> {%<true code%>} {%<false code%>}
\fileGetTF{file name}{setup}{cmd}{true code}{false code}#Sd
\fileIfExist {%<file name%>}
\fileIfExistT {%<file name%>} {%<true code%>}
\fileIfExistF {%<file name%>} {%<false code%>}
\fileIfExistTF {%<file name%>} {%<true code%>} {%<false code%>}

## Quarks (Quark) ##
# Constant Quarks
\qNoValue

# Quark Conditionals
\quarkVarIfNoValue %<\tlvar%>
\quarkVarIfNoValueT %<\tlvar%> {%<true code%>}
\quarkVarIfNoValueF %<\tlvar%> {%<false code%>}
\quarkVarIfNoValueTF %<\tlvar%> {%<true code%>} {%<false code%>}

## Legacy Concepts (Legacy) ##
\legacyIf {%<name%>}
\legacyIfT {%<name%>} {%<true code%>}
\legacyIfF {%<name%>} {%<false code%>}
\legacyIfTF {%<name%>} {%<true code%>} {%<false code%>}
\legacyIfSetTrue {%<name%>}
\legacyIfSetFalse {%<name%>}
\legacyIfSet {%<name%>} {%<bool expr%>}

# not documented
\clistMapBreak#*
\clistVarSort{arg1}{arg2}#*
\cNoValueTl#*
\expOnce{arg}#*
\expPartial{arg}#*
\fileInputStop#*
\prgLocal#*
\noExpand{tokens}#*
\onlyOnce{tokens}#*
\onlyPartial{tokens}#*
\prgBreak#*
\prgBreakDo#*
\propMapBreak#*
\seqJoin{arg1}{arg2}#*
\seqJoinExtended{arg1}{arg2}{arg3}{arg4}#*
\seqMapBreak#*
\seqVarSort{arg1}{arg2}#*
\sortReturnSame#*
\sortReturnSwapped#*

# deprecated
\Result{tokens}#S
\PrgNewFunction %<\function%> {%<arg spec%>} {%<code%>}#S
\PrgNewFunction{cmd}{xargs}{def}#Sd
\PrgSetEqFunction %<\function1 \function2%>#S
\PrgSetEqFunction{cmd}#Sd
\PrgNewConditional %<\function%> {%<arg spec%>} {%<code%>}#S
\PrgNewConditional{cmd}{xargs}{def}#Sd
\Return{tokens}#S
\Print{tokens}#S
\Do{code}#S
\PrgRunOneArgCode{arg1}{code}#S
\PrgRunTwoArgCode{arg1}{arg2}{code}#S
\PrgRunThreeArgCode{arg1}{arg2}{arg3}{code}#S
\PrgRunFourArgCode{arg1}{arg2}{arg3}{arg4}{code}#S
\Local#S
\Name{csname}#S
\Value %<\variable%>#S
\Expand{tokens}#S
\UnExpand{tokens}#S
\OnlyName{tokens}#S
\OnlyValue{tokens}#S
\NoExpand{tokens}#S
\OnlyOnce{tokens}#S
\OnlyPartial{tokens}#S
\PrgPrint{tokens}#S
\UseOne{arg}#S
\GobbleOne{arg}#S
\UseGobble{arg1}{arg2}#S
\GobbleUse{arg1}{arg2}#S
\BoolNew %<\boolvar%>#S
\BoolNew{cmd}#Sd
\BoolConst %<\boolvar%> {%<bool expr%>}#S
\BoolConst{cmd}#Sd
\BoolSet %<\boolvar%> {%<bool expr%>}#S
\BoolSet{cmd}#Sd
\BoolSetTrue %<\boolvar%>#S
\BoolSetFalse %<\boolvar%>#S
\BoolSetEq %<\boolvar1 \boolvar2%>#S
\BoolLog {bool expr}#S
\BoolVarLog %<\boolvar%>#S
\BoolShow {bool expr}#S
\BoolVarShow %<\boolvar%>#S
\BoolIfExist %<\boolvar%>#S
\BoolIfExistT %<\boolvar%> {%<true code%>}#S
\BoolIfExistF %<\boolvar%> {%<false code%>}#S
\BoolIfExistTF %<\boolvar%> {%<true code%>} {%<false code%>}#S
\BoolVarIf %<\boolvar%>#S
\BoolVarIfT %<\boolvar%> {%<true code%>}#S
\BoolVarIfF %<\boolvar%> {%<false code%>}#S
\BoolVarIfTF %<\boolvar%> {%<true code%>} {%<false code%>}#S
\BoolVarNot %<\boolvar%>#S
\BoolVarNotT %<\boolvar%> {%<true code%>}#S
\BoolVarNotF %<\boolvar%> {%<false code%>}#S
\BoolVarNotTF %<\boolvar%> {%<true code%>} {%<false code%>}#S
\BoolVarAnd %<\boolvar1 \boolvar2%>#S
\BoolVarAndT %<\boolvar1 \boolvar2%> {%<true code%>}#S
\BoolVarAndF %<\boolvar1 \boolvar2%> {%<false code%>}#S
\BoolVarAndTF %<\boolvar1 \boolvar2%> {%<true code%>} {%<false code%>}#S
\BoolVarOr %<\boolvar1 \boolvar2%>#S
\BoolVarOrT %<\boolvar1 \boolvar2%> {%<true code%>}#S
\BoolVarOrF %<\boolvar1 \boolvar2%> {%<false code%>}#S
\BoolVarOrTF %<\boolvar1 \boolvar2%> {%<true code%>} {%<false code%>}#S
\BoolVarXor %<\boolvar1 \boolvar2%>#S
\BoolVarXorT %<\boolvar1 \boolvar2%> {%<true code%>}#S
\BoolVarXorF %<\boolvar1 \boolvar2%> {%<false code%>}#S
\BoolVarXorTF %<\boolvar1 \boolvar2%> {%<true code%>} {%<false code%>}#S
\BoolVarDoUntil %<\boolvar%> {%<code%>}#S
\BoolVarDoWhile %<\boolvar%> {%<code%>}#S
\BoolVarUntilDo %<\boolvar%> {%<code%>}#S
\BoolVarWhileDo %<\boolvar%> {%<code%>}#S
\TlNew %<\tlvar%>#S
\TlNew{cmd}#Sd
\TlConst %<\tlvar%> {%<tokens%>}#S
\TlConst{cmd}{def}#Sd
\TlUse %<\tlvar%>#S
\TlToStr {tokens}#S
\TlToStr{tokens%definition}#S
\TlVarToStr %<\tlvar%>#S
\TlLog {tokens}#S
\TlLog{tokens%definition}#S
\TlVarLog %<\tlvar%>#S
\TlShow {tokens}#S
\TlShow{tokens%definition}#S
\TlVarShow %<\tlvar%>#S
\TlSet %<\tlvar%> {%<tokens%>}#S
\TlSet{cmd}{def}#Sd
\TlSetEq %<\tlvar1 \tlvar2%>#S
\TlSetEq{cmd}#Sd
\TlClear %<\tlvar%>#S
\TlClearNew %<\tlvar%>#S
\TlClearNew{cmd}#Sd
\TlConcat %<\tlvar1 \tlvar2 \tlvar3%>#S
\TlConcat{cmd}#Sd
\TlPutLeft %<\tlvar%> {%<tokens%>}#S
\TlPutRight %<\tlvar%> {%<tokens%>}#S
\TlVarReplaceOnce %<\tlvar%> {%<old tokens%>} {%<new tokens%>}#S
\TlVarReplaceAll %<\tlvar%> {%<old tokens%>} {%<new tokens%>}#S
\TlVarRemoveOnce %<\tlvar%> {%<tokens%>}#S
\TlVarRemoveAll %<\tlvar%> {%<tokens%>}#S
\TlTrimSpaces {tokens}#S
\TlVarTrimSpaces %<\tlvar%>#S
\TlCount {tokens}#S
\TlCount{tokens%definition}#S
\TlVarCount %<\tlvar%>#S
\TlHead {tokens}#S
\TlVarHead %<\tlvar%>#S
\TlTail {tokens}#S
\TlVarTail %<\tlvar%>#S
\TlItem {tokens} {int expr}#S
\TlVarItem %<\tlvar%> {%<int expr%>}#S
\TlRandItem {tokens}#S
\TlVarRandItem %<\tlvar%>#S
\TlMapInline {tokens} {inline function}#S
\TlVarMapInline %<\tlvar%> {%<inline function%>}#S
\TlMapVariable{tokens}{cmd}{def}#Sd
\TlMapVariable {%<tokens%>} %<\variable%> {%<code%>}#S
\TlVarMapVariable{tlvar}{cmd}{def}#Sd
\TlVarMapVariable %<\tlvar \variable%> {%<code%>}#S
\TlIfExist %<\tlvar%>#S
\TlIfExistT %<\tlvar%> {%<true code%>}#S
\TlIfExistF %<\tlvar%> {%<false code%>}#S
\TlIfExistTF %<\tlvar%> {%<true code%>} {%<false code%>}#S
\TlIfEmpty {tokens}#S
\TlIfEmptyT {tokens} {true code}#S
\TlIfEmptyF {tokens} {false code}#S
\TlIfEmptyTF {tokens} {true code} {false code}#S
\TlVarIfEmpty %<\tlvar%>#S
\TlVarIfEmptyT %<\tlvar%> {%<true code%>}#S
\TlVarIfEmptyF %<\tlvar%> {%<false code%>}#S
\TlVarIfEmptyTF %<\tlvar%> {%<true code%>} {%<false code%>}#S
\TlIfBlank {tokens}#S
\TlIfBlankT {tokens} {true code}#S
\TlIfBlankF {tokens} {false code}#S
\TlIfBlankTF {tokens} {true code} {false code}#S
\TlIfEq {tokens1} {tokens2}#S
\TlIfEqT {tokens1} {tokens2} {true code}#S
\TlIfEqF {tokens1} {tokens2} {false code}#S
\TlIfEqTF {tokens1} {tokens2} {true code} {false code}#S
\TlVarIfEq %<\tlvar1 \tlvar2%>#S
\TlVarIfEqT %<\tlvar1 \tlvar2%> {%<true code%>}#S
\TlVarIfEqF %<\tlvar1 \tlvar2%> {%<false code%>}#S
\TlVarIfEqTF %<\tlvar1 \tlvar2%> {%<true code%>} {%<false code%>}#S
\TlIfIn {tokens1} {tokens2}#S
\TlIfInT {tokens1} {tokens2} {true code}#S
\TlIfInF {tokens1} {tokens2} {false code}#S
\TlIfInTF {tokens1} {tokens2} {true code} {false code}#S
\TlVarIfIn %<\tlvar%> {%<tokens%>}#S
\TlVarIfInT %<\tlvar%> {%<tokens%>} {%<true code%>}#S
\TlVarIfInF %<\tlvar%> {%<tokens%>} {%<false code%>}#S
\TlVarIfInTF %<\tlvar%> {%<tokens%>} {%<true code%>} {%<false code%>}#S
\TlIfSingle {tokens}#S
\TlIfSingleT {tokens} {true code}#S
\TlIfSingleF {tokens} {false code}#S
\TlIfSingleTF {tokens} {true code} {false code}#S
\TlVarIfSingle %<\tlvar%>#S
\TlVarIfSingleT %<\tlvar%> {%<true code%>}#S
\TlVarIfSingleF %<\tlvar%> {%<false code%>}#S
\TlVarIfSingleTF %<\tlvar%> {%<true code%>} {%<false code%>}#S
\TlVarCase %<\tlvar%> {%<\tlvar1 {code1} \tlvar2 {code2} ...%>}#S
\TlVarCaseT %<\tlvar%> {%<\tlvar1 {code1} \tlvar2 {code2} ...%>} {%<true code%>}#S
\TlVarCaseF %<\tlvar%> {%<\tlvar1 {code1} \tlvar2 {code2} ...%>} {%<false code%>}#S
\TlVarCaseTF %<\tlvar%> {%<\tlvar1 {code1} \tlvar2 {code2} ...%>} {%<true code%>} {%<false code%>}#S
\StrNew %<\strvar%>#S
\StrNew{cmd}#Sd
\StrConst %<\strvar%> {%<tokens%>}#S
\StrConst{cmd}{def}#Sd
\StrUse %<\strvar%>#S
\StrLog {tokens}#S
\StrLog{tokens%definition}#S
\StrVarLog %<\strvar%>#S
\StrShow {tokens}#S
\StrShow{tokens%definition}#S
\StrVarShow %<\strvar%>#S
\StrSet %<\strvar%> {%<tokens%>}#S
\StrSet{cmd}{def}#Sd
\StrSetEq %<\strvar1 \strvar2%>#S
\StrClear %<\strvar%>#S
\StrClearNew %<\strvar%>#S
\StrClearNew{cmd}#Sd
\StrConcat %<\strvar1 \strvar2 \strvar3%>#S
\StrConcat{cmd}#Sd
\StrPutLeft %<\strvar%> {%<tokens%>}#S
\StrPutRight %<\strvar%> {%<tokens%>}#S
\StrVarReplaceOnce %<\tlvar%> {%<old tokens%>} {%<new tokens%>}#S
\StrVarReplaceAll %<\tlvar%> {%<old tokens%>} {%<new tokens%>}#S
\StrVarRemoveOnce %<\strvar%> {%<tokens%>}#S
\StrVarRemoveAll %<\strvar%> {%<tokens%>}#S
\StrCount {tokens}#S
\StrCount{tokens%definition}#S
\StrSize {tokens}#S
\StrSize{tokens%definition}#S
\StrVarCount %<\tlvar%>#S
\StrHead {tokens}#S
\StrVarHead %<\tlvar%>#S
\StrTail {tokens}#S
\StrVarTail %<\tlvar%>#S
\StrItem {tokens} {int expr}#S
\StrVarItem %<\tlvar%> {%<int expr%>}#S
\StrMapInline {tokens} {inline function}#S
\StrVarMapInline %<\tlvar%> {%<inline function%>}#S
\StrMapVariable{tokens}{cmd}{def}#Sd
\StrMapVariable {%<tokens%>} %<\variable%> {%<code%>}#S
\StrVarMapVariable{strvar}{cmd}{def}#Sd
\StrVarMapVariable %<\strvar \variable%> {%<code%>}#S
\StrIfExist %<\strvar%>#S
\StrIfExistT %<\strvar%> {%<true code%>}#S
\StrIfExistF %<\strvar%> {%<false code%>}#S
\StrIfExistTF %<\strvar%> {%<true code%>} {%<false code%>}#S
\StrVarIfEmpty %<\strvar%>#S
\StrVarIfEmptyT %<\strvar%> {%<true code%>}#S
\StrVarIfEmptyF %<\strvar%> {%<false code%>}#S
\StrVarIfEmptyTF %<\strvar%> {%<true code%>} {%<false code%>}#S
\StrIfEq {tokens1} {tokens2}#S
\StrIfEqT {tokens1} {tokens2} {true code}#S
\StrIfEqF {tokens1} {tokens2} {false code}#S
\StrIfEqTF {tokens1} {tokens2} {true code} {false code}#S
\StrVarIfEq %<\strvar1 \strvar2%>#S
\StrVarIfEqT %<\strvar1 \strvar2%> {%<true code%>}#S
\StrVarIfEqF %<\strvar1 \strvar2%> {%<false code%>}#S
\StrVarIfEqTF %<\strvar1 \strvar2%> {%<true code%>} {%<false code%>}#S
\StrIfIn {tokens1} {tokens2}#S
\StrIfInT {tokens1} {tokens2} {true code}#S
\StrIfInF {tokens1} {tokens2} {false code}#S
\StrIfInTF {tokens1} {tokens2} {true code} {false code}#S
\StrVarIfIn %<\strvar%> {%<tokens%>}#S
\StrVarIfInT %<\strvar%> {%<tokens%>} {%<true code%>}#S
\StrVarIfInF %<\strvar%> {%<tokens%>} {%<false code%>}#S
\StrVarIfInTF %<\strvar%> {%<tokens%>} {%<true code%>} {%<false code%>}#S
\StrCompare {%<tokens1%>} %<<relation>%> {%<tokens2%>}#S
\StrCompareT {%<tokens1%>} %<<relation>%> {%<tokens2%>} {%<true code%>}#S
\StrCompareF {%<tokens1%>} %<<relation>%> {%<tokens2%>} {%<false code%>}#S
\StrCompareTF {%<tokens1%>} %<<relation>%> {%<tokens2%>} {%<true code%>} {%<false code%>}#S
\StrIfCompare {%<tokens1%>} %<<relation>%> {%<tokens2%>}#*#S
\StrIfCompareT {%<tokens1%>} %<<relation>%> {%<tokens2%>} {%<true code%>}#*#S
\StrIfCompareF {%<tokens1%>} %<<relation>%> {%<tokens2%>} {%<false code%>}#*#S
\StrIfCompareTF {%<tokens1%>} %<<relation>%> {%<tokens2%>} {%<true code%>} {%<false code%>}#*#S
\StrCase {%<test string%>} {%<{string1} {code1} {string2} {code2} ...%>}#S
\StrCaseT {%<test string%>} {%<{string1} {code1} {string2} {code2} ...%>} {%<true code%>}#S
\StrCaseF {%<test string%>} {%<{string1} {code1} {string2} {code2} ...%>} {%<false code%>}#S
\StrCaseTF {%<test string%>} {%<{string1} {code1} {string2} {code2} ...%>} {%<true code%>} {%<false code%>}#S
\IntEval {int expr}#S
\IntMathAdd {int expr1} {int expr2}#S
\IntMathSub {int expr1} {int expr2}#S
\IntMathMult {int expr1} {int expr2}#S
\IntMathDiv {int expr1} {int expr2}#S
\IntMathDivTruncate {int expr1} {int expr2}#S
\IntMathSign {int expr}#S
\IntMathAbs {int expr}#S
\IntMathMax {int expr1} {int expr2}#S
\IntMathMin {int expr1} {int expr2}#S
\IntMathMod {int expr1} {int expr2}#S
\IntMathRand {int expr1} {int expr2}#S
\IntNew %<\intvar%>#S
\IntNew{cmd}#Sd
\IntConst %<\intvar%> {%<int expr%>}#S
\IntConst{cmd}#Sd
\IntUse %<\intvar%>#S
\IntLog {int expr}#S
\IntVarLog %<\intvar%>#S
\IntShow {int expr}#S
\IntVarShow %<\intvar%>#S
\IntSet %<\intvar%> {%<int expr%>}#S
\IntSet{cmd}#Sd
\IntSetEq %<\intvar1 \intvar2%>#S
\IntSetEq{cmd}#Sd
\IntZero %<\intvar%>#S
\IntZeroNew %<\intvar%>#S
\IntZeroNew{cmd}#Sd
\IntIncr %<\intvar%>#S
\IntDecr %<\intvar%>#S
\IntAdd %<\intvar%> {%<int expr%>}#S
\IntSub %<\intvar%> {%<int expr%>}#S
\IntReplicate {int expr} {tokens}#S
\IntStepInline {init value} {step} {final value} {code}#S
\IntStepOneInline {init value} {final value} {code}#S
\IntStepVariable{init value}{step}{final value}{cmd}{code%definition}#Sd
\IntStepVariable {%<init value%>} {%<step%>} {%<final value%>} %<\tlvar%> {%<code%>}#S
\IntStepOneVariable{init value}{final value}{cmd}{code%definition}#Sd
\IntStepOneVariable {%<init value%>} {%<final value%>} %<\tlvar%> {%<code%>}#S
\IntIfExist %<\intvar%>#S
\IntIfExistT %<\intvar%> {%<true code%>}#S
\IntIfExistF %<\intvar%> {%<false code%>}#S
\IntIfExistTF %<\intvar%> {%<true code%>} {%<false code%>}#S
\IntIfOdd {int expr}#S
\IntIfOddT {int expr} {true code}#S
\IntIfOddF {int expr} {false code}#S
\IntIfOddTF {int expr} {true code} {false code}#S
\IntIfEven {int expr}#S
\IntIfEvenT {int expr} {true code}#S
\IntIfEvenF {int expr} {false code}#S
\IntIfEvenTF {int expr} {true code} {false code}#S
\IntCompare {%<int expr1%>} %<<relation>%> {%<int expr2%>}#S
\IntCompareT {%<int expr1%>} %<<relation>%> {%<int expr2%>} {%<true code%>}#S
\IntCompareF {%<int expr1%>} %<<relation>%> {%<int expr2%>} {%<false code%>}#S
\IntCompareTF {%<int expr1%>} %<<relation>%> {%<int expr2%>} {%<true code%>} {%<false code%>}#S
\IntCase {%<test int expr%>} {%<{int expr1} {code1} {int expr2} {code2} ...%>}#S
\IntCaseT {%<test int expr%>} {%<{int expr1} {code1} {int expr2} {code2} ...%>} {%<true code%>}#S
\IntCaseF {%<test int expr%>} {%<{int expr1} {code1} {int expr2} {code2} ...%>} {%<false code%>}#S
\IntCaseTF {%<test int expr%>} {%<{int expr1} {code1} {int expr2} {code2} ...%>} {%<true code%>} {%<false code%>}#S
\FpEval {fp expr}#S
\FpMathAdd {fp expr1} {fp expr2}#S
\FpMathSub {fp expr1} {fp expr2}#S
\FpMathMult {fp expr1} {fp expr2}#S
\FpMathDiv {fp expr1} {fp expr2}#S
\FpMathSign {fp expr}#S
\FpMathAbs {fp expr}#S
\FpMathMax {fp expr1} {fp expr2}#S
\FpMathMin {fp expr1} {fp expr2}#S
\FpNew %<\fpvar%>#S
\FpNew{cmd}#Sd
\FpConst %<\fpvar%> {%<fp expr%>}#S
\FpConst{cmd}#Sd
\FpUse %<\fpvar%>#S
\FpLog {fp expr}#S
\FpVarLog %<\fpvar%>#S
\FpShow {fp expr}#S
\FpVarShow %<\fpvar%>#S
\FpSet %<\fpvar%> {%<fp expr%>}#S
\FpSet{cmd}#Sd
\FpSetEq %<\fpvar1 \fpvar2%>#S
\FpSetEq{cmd}#Sd
\FpZero %<\fpvar%>#S
\FpZeroNew %<\fpvar%>#S
\FpZeroNew{cmd}#Sd
\FpAdd %<\fpvar%> {%<fp expr%>}#S
\FpSub %<\fpvar%> {%<fp expr%>}#S
\FpStepInline {init value} {step} {final value} {code}#S
\FpStepVariable{init value}{step}{final value}{cmd}{code%definition}#Sd
\FpStepVariable {%<init value%>} {%<step%>} {%<final value%>} %<\tlvar%> {%<code%>}#S
\FpIfExist %<\fpvar%>#S
\FpIfExistT %<\fpvar%> {%<true code%>}#S
\FpIfExistF %<\fpvar%> {%<false code%>}#S
\FpIfExistTF %<\fpvar%> {%<true code%>} {%<false code%>}#S
\FpCompare {%<fp expr1%>} %<<relation>%> {%<fp expr2%>}#S
\FpCompareT {%<fp expr1%>} %<<relation>%> {%<fp expr2%>} {%<true code%>}#S
\FpCompareF {%<fp expr1%>} %<<relation>%> {%<fp expr2%>} {%<false code%>}#S
\FpCompareTF {%<fp expr1%>} %<<relation>%> {%<fp expr2%>} {%<true code%>} {%<false code%>}#S
\DimEval {dim expr}#S
\DimMathAdd {dim expr1} {dim expr2}#S
\DimMathSub {dim expr1} {dim expr2}#S
\DimMathRatio {dim expr1} {dim expr2}#S
\DimMathSign {dim expr}#S
\DimMathAbs {dim expr}#S
\DimMathMax {dim expr1} {dim expr2}#S
\DimMathMin {dim expr1} {dim expr2}#S
\DimNew %<\dimen%>#S
\DimNew{cmd}#Sd
\DimConst %<\dimen%> {%<dim expr%>}#S
\DimConst{cmd}#Sd
\DimUse %<\dimen%>#S
\DimLog {dim expr}#S
\DimVarLog %<\dimen%>#S
\DimShow {dim expr}#S
\DimVarShow %<\dimen%>#S
\DimSet %<\dimen%> {%<dim expr%>}#S
\DimSet{cmd}#Sd
\DimSetEq %<\dimen1 \dimen2%>#S
\DimSetEq{cmd}#Sd
\DimZero %<\dimen%>#S
\DimZeroNew %<\dimen%>#S
\DimZeroNew{cmd}#Sd
\DimAdd %<\dimen%> {%<dim expr%>}#S
\DimSub %<\dimen%> {%<dim expr%>}#S
\DimStepInline {init value} {step} {final value} {code}#S
\DimStepVariable{init value}{step}{final value}{cmd}{code%definition}#Sd
\DimStepVariable {%<init value%>} {%<step%>} {%<final value%>} %<\tlvar%> {%<code%>}#S
\DimIfExist %<\dimen%>#S
\DimIfExistT %<\dimen%> {%<true code%>}#S
\DimIfExistF %<\dimen%> {%<false code%>}#S
\DimIfExistTF %<\dimen%> {%<true code%>} {%<false code%>}#S
\DimCompare {%<dim expr1%>} %<<relation>%> {%<dim expr2%>}#S
\DimCompareT {%<dim expr1%>} %<<relation>%> {%<dim expr2%>} {%<true code%>}#S
\DimCompareF {%<dim expr1%>} %<<relation>%> {%<dim expr2%>} {%<false code%>}#S
\DimCompareTF {%<dim expr1%>} %<<relation>%> {%<dim expr2%>} {%<true code%>} {%<false code%>}#S
\DimCase {%<test dim expr%>} {%<{dim expr1} {code1} {dim expr2} {code2} ...%>}#S
\DimCaseT {%<test dim expr%>} {%<{dim expr1} {code1} {dim expr2} {code2} ...%>}{%<true code%>}#S
\DimCaseF {%<test dim expr%>} {%<{dim expr1} {code1} {dim expr2} {code2} ...%>}{%<false code%>}#S
\DimCaseTF {%<test dim expr%>} {%<{dim expr1} {code1} {dim expr2} {code2} ...%>}{%<true code%>}{%<false code%>}#S
\ClistNew %<\clistvar%>#S
\ClistNew{cmd}#Sd
\ClistConst %<\clistvar%> {%<comma list%>}#S
\ClistConst{cmd}#Sd
\ClistVarJoin %<\clistvar%> {%<separator%>}#S
\ClistVarJoinExtended %<\clistvar%> {%<sep for 2%>} {%<sep for >2%>} {%<sep for final 2%>}#S
\ClistJoin {comma list} {separator}#S
\ClistJoinExtended {comma list} {sep for 2} {sep for >2} {sep for final 2}#S
\ClistLog {comma list}#S
\ClistVarLog %<\clistvar%>#S
\ClistShow {comma list}#S
\ClistVarShow %<\clistvar%>#S
\ClistSet %<\clistvar%> {%<comma list%>}#S
\ClistSet{cmd}#Sd
\ClistSetEq %<\clistvar1 \clistvar2%>#S
\ClistSetEq{cmd}#Sd
\ClistSetFromSeq %<\clistvar \seqvar%>#S
\ClistSetFromSeq{cmd}{arg}#Sd
\ClistClear %<\clistvar%>#S
\ClistClearNew %<\clistvar%>#S
\ClistClearNew{cmd}#Sd
\ClistConcat %<\clistvar1 \clistvar2 \clistvar3%>#S
\ClistPutLeft %<\clistvar%> {%<comma list%>}#S
\ClistPutRight %<\clistvar%> {%<comma list%>}#S
\ClistVarRemoveDuplicates %<\clistvar%>#S
\ClistVarRemoveAll %<\clistvar%> {%<item%>}#S
\ClistVarReverse %<\clistvar%>#S
\ClistCount {comma list}#S
\ClistVarCount %<\clistvar%>#S
\ClistItem {comma list} {int expr}#S
\ClistVarItem %<\clistvar%> {%<int expr%>}#S
\ClistRandItem {comma list}#S
\ClistVarRandItem %<\clistvar%>#S
\ClistGet %<\clistvar \tlvar%>#S
\ClistGet{clistvar}{cmd}#Sd
\ClistGetT %<\clistvar \tlvar%> {%<true code%>}#S
\ClistGetT{clistvar}{cmd}#Sd
\ClistGetF %<\clistvar \tlvar%> {%<false code%>}#S
\ClistGetF{clistvar}{cmd}#Sd
\ClistGetTF %<\clistvar \tlvar%> {%<true code%>} {%<false code%>}#S
\ClistGetTF{clistvar}{cmd}#Sd
\ClistPop %<\clistvar \tlvar%>#S
\ClistPop{clistvar}{cmd}#Sd
\ClistPopT %<\clistvar \tlvar%> {%<true code%>}#S
\ClistPopT{clistvar}{cmd}#Sd
\ClistPopF %<\clistvar \tlvar%> {%<false code%>}#S
\ClistPopF{clistvar}{cmd}#Sd
\ClistPopTF %<\clistvar \tlvar%> {%<true code%>} {%<false code%>}#S
\ClistPopTF{clistvar}{cmd}#Sd
\ClistPush %<\clistvar%> {%<items%>}#S
\ClistMapInline {comma list} {inline function}#S
\ClistVarMapInline %<\clistvar%> {%<inline function%>}#S
\ClistMapVariable{comma list}{cmd}{def}#Sd
\ClistMapVariable {%<comma list%>} %<\variable%> {%<code%>}#S
\ClistVarMapVariable{clistvar}{cmd}{def}#Sd
\ClistVarMapVariable %<\clistvar \variable%> {%<code%>}#S
\ClistIfExist %<\clistvar%>#S
\ClistIfExistT %<\clistvar%> {%<true code%>}#S
\ClistIfExistF %<\clistvar%> {%<false code%>}#S
\ClistIfExistTF %<\clistvar%> {%<true code%>} {%<false code%>}#S
\ClistIfEmpty {comma list}#S
\ClistIfEmptyT {comma list} {true code}#S
\ClistIfEmptyF {comma list} {false code}#S
\ClistIfEmptyTF {comma list} {true code} {false code}#S
\ClistVarIfEmpty %<\clistvar%>#S
\ClistVarIfEmptyT %<\clistvar%> {%<true code%>}#S
\ClistVarIfEmptyF %<\clistvar%> {%<false code%>}#S
\ClistVarIfEmptyTF %<\clistvar%> {%<true code%>} {%<false code%>}#S
\ClistIfIn {comma list} {item}#S
\ClistIfInT {comma list} {item} {true code}#S
\ClistIfInF {comma list} {item} {false code}#S
\ClistIfInTF {comma list} {item} {true code} {false code}#S
\ClistVarIfIn %<\clistvar%> {%<item%>}#S
\ClistVarIfInT %<\clistvar%> {%<item%>} {%<true code%>}#S
\ClistVarIfInF %<\clistvar%> {%<item%>} {%<false code%>}#S
\ClistVarIfInTF %<\clistvar%> {%<item%>} {%<true code%>} {%<false code%>}#S
\SeqNew %<\seqvar%>#S
\SeqNew{cmd}#Sd
\SeqConstFromClist %<\seqvar%> {%<comma list%>}#S
\SeqConstFromClist{cmd}#Sd
\SeqVarJoin %<\seqvar%> {%<separator%>}#S
\SeqVarJoinExtended %<\seqvar%> {%<sep for 2%>} {%<sep for >2%>} {%<sep for final 2%>}#S
\SeqVarLog %<\seqvar%>#S
\SeqVarShow %<\seqvar%>#S
\SeqSetFromClist %<\seqvar%> {%<comma list%>}#S
\SeqSetFromClist{cmd}#Sd
\SeqSetSplit %<\seqvar%> {%<delimiter%>} {%<tokens%>}#S
\SeqSetSplit{cmd}#Sd
\SeqSetEq %<\seqvar1 \seqvar2%>#S
\SeqSetEq{cmd}#Sd
\SeqClear %<\seqvar%>#S
\SeqClearNew %<\seqvar%>#S
\SeqClearNew{cmd}#Sd
\SeqConcat %<\seqvar1 \seqvar2 \seqvar3%>#S
\SeqPutLeft %<\seqvar%> {%<item%>}#S
\SeqPutRight %<\seqvar%> {%<item%>}#S
\SeqVarRemoveDuplicates %<\seqvar%>#S
\SeqVarRemoveAll %<\seqvar%> {%<item%>}#S
\SeqVarReverse %<\seqvar%>#S
\SeqVarCount %<\seqvar%>#S
\SeqVarItem %<\seqvar%> {%<int expr%>}#S
\SeqVarRandItem %<\seqvar%>#S
\SeqGet %<\seqvar \tlvar%>#S
\SeqGetT %<\seqvar \tlvar%> {%<true code%>}#S
\SeqGetF %<\seqvar \tlvar%> {%<false code%>}#S
\SeqGetTF %<\seqvar \tlvar%> {%<true code%>} {%<false code%>}#S
\SeqPop %<\seqvar \tlvar%>#S
\SeqPopT %<\seqvar \tlvar%> {%<true code%>}#S
\SeqPopF %<\seqvar \tlvar%> {%<false code%>}#S
\SeqPopTF %<\seqvar \tlvar%> {%<true code%>} {%<false code%>}#S
\SeqPush %<\seqvar%> {%<item%>}#S
\SeqGetLeft %<\seqvar \tlvar%>#S
\SeqGetLeftT %<\seqvar \tlvar%> {%<true code%>}#S
\SeqGetLeftF %<\seqvar \tlvar%> {%<false code%>}#S
\SeqGetLeftTF %<\seqvar \tlvar%> {%<true code%>} {%<false code%>}#S
\SeqGetRight %<\seqvar \tlvar%>#S
\SeqGetRightT %<\seqvar \tlvar%> {%<true code%>}#S
\SeqGetRightF %<\seqvar \tlvar%> {%<false code%>}#S
\SeqGetRightTF %<\seqvar \tlvar%> {%<true code%>} {%<false code%>}#S
\SeqPopLeft %<\seqvar \tlvar%>#S
\SeqPopLeftT %<\seqvar \tlvar%> {%<true code%>}#S
\SeqPopLeftF %<\seqvar \tlvar%> {%<false code%>}#S
\SeqPopLeftTF %<\seqvar \tlvar%> {%<true code%>} {%<false code%>}#S
\SeqPopRight %<\seqvar \tlvar%>#S
\SeqPopRightT %<\seqvar \tlvar%> {%<true code%>}#S
\SeqPopRightF %<\seqvar \tlvar%> {%<false code%>}#S
\SeqPopRightTF %<\seqvar \tlvar%> {%<true code%>} {%<false code%>}#S
\SeqVarMapInline %<\seqvar%> {%<inline function%>}#S
\SeqVarMapVariable{seqvar}{cmd}{def}#Sd
\SeqVarMapVariable %<\seqvar \variable%> {%<code%>}#S
\SeqIfExist %<\seqvar%>#S
\SeqIfExistT %<\seqvar%> {%<true code%>}#S
\SeqIfExistF %<\seqvar%> {%<false code%>}#S
\SeqIfExistTF %<\seqvar%> {%<true code%>} {%<false code%>}#S
\SeqVarIfEmpty %<\seqvar%>#S
\SeqVarIfEmptyT %<\seqvar%> {%<true code%>}#S
\SeqVarIfEmptyF %<\seqvar%> {%<false code%>}#S
\SeqVarIfEmptyTF %<\seqvar%> {%<true code%>} {%<false code%>}#S
\SeqVarIfIn %<\seqvar%> {%<item%>}#S
\SeqVarIfInT %<\seqvar%> {%<item%>} {%<true code%>}#S
\SeqVarIfInF %<\seqvar%> {%<item%>} {%<false code%>}#S
\SeqVarIfInTF %<\seqvar%> {%<item%>} {%<true code%>} {%<false code%>}#S
\PropNew %<\propvar%>#S
\PropNew{cmd}#Sd
\PropConstFromKeyval %<\propvar%> {%<key1=value2, key2=value2, ...%>}#S
\PropConstFromKeyval{cmd}#Sd
\PropToKeyval %<\propvar%>#S
\PropVarLog %<\propvar%>#S
\PropVarShow %<\propvar%>#S
\PropSetFromKeyval %<\propvar%> {%<key1=value2, key2=value2, ...%>}#S
\PropSetFromKeyval{cmd}#Sd
\PropSetEq %<\propvar1 \propvar2%>#S
\PropSetEq{cmd}#Sd
\PropClear %<\propvar%>#S
\PropClearNew %<\propvar%>#S
\PropClearNew{cmd}#Sd
\PropConcat %<\propvar1 \propvar2 \propvar3%>#S
\PropPut %<\propvar%> {%<key%>} {%<value%>}#S
\PropPutIfNew %<\propvar%> {%<key%>} {%<value%>}#S
\PropPutFromKeyval %<\propvar%> {%<key1=value2, key2=value2, ...%>}#S
\PropVarRemove %<\propvar%> {%<key%>}#S
\PropVarCount %<\propvar%>#S
\PropVarItem %<\propvar%> {%<key%>}#S
\PropGet %<\propvar%> {%<key%>} %<\tlvar%>#S
\PropGet{propvar}{key%plain}{cmd}#Sd
\PropGetT %<\propvar%> {%<key%>} %<\tlvar%> {%<true code%>}#S
\PropGetT{propvar}{key%plain}{cmd}#Sd
\PropGetF %<\propvar%> {%<key%>} %<\tlvar%> {%<false code%>}#S
\PropGetF{propvar}{key%plain}{cmd}#Sd
\PropGetTF %<\propvar%> {%<key%>} %<\tlvar%> {%<true code%>} {%<false code%>}#S
\PropGetTF{propvar}{key%plain}{cmd}#Sd
\PropPop %<\propvar%> {%<key%>} %<\tlvar%>#S
\PropPop{propvar}{key%plain}{cmd}#Sd
\PropPopT %<\propvar%> {%<key%>} %<\tlvar%> {%<true code%>}#S
\PropPopT{propvar}{key%plain}{cmd}#Sd
\PropPopF %<\propvar%> {%<key%>} %<\tlvar%> {%<false code%>}#S
\PropPopF{propvar}{key%plain}{cmd}#Sd
\PropPopTF %<\propvar%> {%<key%>} %<\tlvar%> {%<true code%>} {%<false code%>}#S
\PropPopTF{propvar}{key%plain}{cmd}#Sd
\PropVarMapInline %<\propvar%> {%<inline function%>}#S
\PropIfExist %<\propvar%>#S
\PropIfExistT %<\propvar%> {%<true code%>}#S
\PropIfExistF %<\propvar%> {%<false code%>}#S
\PropIfExistTF %<\propvar%> {%<true code%>} {%<false code%>}#S
\PropVarIfEmpty %<\propvar%>#S
\PropVarIfEmptyT %<\propvar%> {%<true code%>}#S
\PropVarIfEmptyF %<\propvar%> {%<false code%>}#S
\PropVarIfEmptyTF %<\propvar%> {%<true code%>} {%<false code%>}#S
\PropVarIfIn %<\propvar%> {%<key%>}#S
\PropVarIfInT %<\propvar%> {%<key%>} {%<true code%>}#S
\PropVarIfInF %<\propvar%> {%<key%>} {%<false code%>}#S
\PropVarIfInTF %<\propvar%> {%<key%>} {%<true code%>} {%<false code%>}#S
\RegexNew %<\regexvar%>#S
\Regex{cmd}#Sd
\RegexSet %<\regexvar%> {%<regex%>}#S
\RegexSet{cmd}{def}#Sd
\RegexConst %<\regexvar%> {%<regex%>}#S
\RegexConst{cmd}{def}#Sd
\RegexLog {%<regex%>}#S
\RegexVarLog %<\regexvar%>#S
\RegexShow {%<regex%>}#S
\RegexVarShow %<\regexvar%>#S
\RegexMatch {%<regex%>} {%<tokens%>}#S
\RegexMatchT {%<regex%>} {%<tokens%>} {%<true code%>}#S
\RegexMatchF {%<regex%>} {%<tokens%>} {%<false code%>}#S
\RegexMatchTF {%<regex%>} {%<tokens%>} {%<true code%>} {%<false code%>}#S
\RegexVarMatch %<\regexvar%> {%<tokens%>}#S
\RegexVarMatchT %<\regexvar%> {%<tokens%>} {%<true code%>}#S
\RegexVarMatchF %<\regexvar%> {%<tokens%>} {%<false code%>}#S
\RegexVarMatchTF %<\regexvar%> {%<tokens%>} {%<true code%>} {%<false code%>}#S
\RegexCount {%<regex%>} {%<tokens%>} %<\intvar%>#S
\RegexVarCount  %<\regexvar%> {%<tokens%>} %<\intvar%>#S
\RegexMatchCase {%<{regex1} {code1} {regex2} {code2} ...%>} {%<tokens%>}#S
\RegexMatchCaseT {%<{regex1} {code1} {regex2} {code2} ...%>} {%<tokens%>} {%<true code%>}#S
\RegexMatchCaseF {%<{regex1} {code1} {regex2} {code2} ...%>} {%<tokens%>} {%<false code%>}#S
\RegexMatchCaseTF {%<{regex1} {code1} {regex2} {code2} ...%>} {%<tokens%>} {%<true code%>} {%<false code%>}#S
\RegexExtractOnce {%<regex%>} {%<tokens%>} %<\seqvar%>#S
\RegexExtractOnce{regex}{tokens}{cmd}#Sd
\RegexExtractOnceT {%<regex%>} {%<tokens%>} %<\seqvar%> {%<true code%>}#S
\RegexExtractOnceT{regex}{tokens}{cmd}#Sd
\RegexExtractOnceF {%<regex%>} {%<tokens%>} %<\seqvar%> {%<false code%>}#S
\RegexExtractOnceF{regex}{tokens}{cmd}#Sd
\RegexExtractOnceTF {%<regex%>} {%<tokens%>} %<\seqvar%> {%<true code%>} {%<false code%>}#S
\RegexExtractOnceTF{regex}{tokens}{cmd}#Sd
\RegexVarExtractOnce %<\regexvar%> {%<tokens%>} %<\seqvar%>#S
\RegexVarExtractOnce{regexvar}{tokens}{cmd}#Sd
\RegexVarExtractOnceT %<\regexvar%> {%<tokens%>} %<\seqvar%> {%<true code%>}#S
\RegexVarExtractOnceT{regexvar}{tokens}{cmd}#Sd
\RegexVarExtractOnceF %<\regexvar%> {%<tokens%>} %<\seqvar%> {%<false code%>}#S
\RegexVarExtractOnceF{regexvar}{tokens}{cmd}#Sd
\RegexVarExtractOnceTF %<\regexvar%> {%<tokens%>} %<\seqvar%> {%<true code%>} {%<false code%>}#S
\RegexVarExtractOnceTF{regexvar}{tokens}{cmd}#Sd
\RegexExtractAll {%<regex%>} {%<tokens%>} %<\seqvar%>#S
\RegexExtractAll{regex}{tokens}{cmd}#Sd
\RegexExtractAllT {%<regex%>} {%<tokens%>} %<\seqvar%> {%<true code%>}#S
\RegexExtractAllT{regex}{tokens}{cmd}#Sd
\RegexExtractAllF {%<regex%>} {%<tokens%>} %<\seqvar%> {%<false code%>}#S
\RegexExtractAllF{regex}{tokens}{cmd}#Sd
\RegexExtractAllTF {%<regex%>} {%<tokens%>} %<\seqvar%> {%<true code%>} {%<false code%>}#S
\RegexExtractAllTF{regex}{tokens}{cmd}#Sd
\RegexVarExtractAll %<\regexvar%> {%<tokens%>} %<\seqvar%>#S
\RegexVarExtractAll{regexvar}{tokens}{cmd}#Sd
\RegexVarExtractAllT %<\regexvar%> {%<tokens%>} %<\seqvar%> {%<true code%>}#S
\RegexVarExtractAllT{regexvar}{tokens}{cmd}#Sd
\RegexVarExtractAllF %<\regexvar%> {%<tokens%>} %<\seqvar%> {%<false code%>}#S
\RegexVarExtractAllF{regexvar}{tokens}{cmd}#Sd
\RegexVarExtractAllTF %<\regexvar%> {%<tokens%>} %<\seqvar%> {%<true code%>} {%<false code%>}#S
\RegexVarExtractAllTF{regexvar}{tokens}{cmd}#Sd
\RegexSplit {%<regex%>} {%<tokens%>} %<\seqvar%>#S
\RegexSplit{regex}{tokens}{cmd}#Sd
\RegexSplitT {%<regex%>} {%<tokens%>} %<\seqvar%> {%<true code%>}#S
\RegexSplitT{regex}{tokens}{cmd}#Sd
\RegexSplitF {%<regex%>} {%<tokens%>} %<\seqvar%> {%<false code%>}#S
\RegexSplitF{regex}{tokens}{cmd}#Sd
\RegexSplitTF {%<regex%>} {%<tokens%>} %<\seqvar%> {%<true code%>} {%<false code%>}#S
\RegexSplitTF{regex}{tokens}{cmd}#Sd
\RegexVarSplit %<\regexvar%> {%<tokens%>} %<\seqvar%>#S
\RegexVarSplit{regexvar}{tokens}{cmd}#Sd
\RegexVarSplitT %<\regexvar%> {%<tokens%>} %<\seqvar%> {%<true code%>}#S
\RegexVarSplitT{regexvar}{tokens}{cmd}#Sd
\RegexVarSplitF %<\regexvar%> {%<tokens%>} %<\seqvar%> {%<false code%>}#S
\RegexVarSplitF{regexvar}{tokens}{cmd}#Sd
\RegexVarSplitTF %<\regexvar%> {%<tokens%>} %<\seqvar%> {%<true code%>} {%<false code%>}#S
\RegexVarSplitTF{regexvar}{tokens}{cmd}#Sd
\RegexReplaceOnce {%<regex%>} {%<replacement%>} %<\tlvar%>#S
\RegexReplaceOnceT {%<regex%>} {%<replacement%>} %<\tlvar%> {%<true code%>}#S
\RegexReplaceOnceF {%<regex%>} {%<replacement%>} %<\tlvar%> {%<false code%>}#S
\RegexReplaceOnceTF {%<regex%>} {%<replacement%>} %<\tlvar%> {%<true code%>} {%<false code%>}#S
\RegexVarReplaceOnce %<\regexvar%> {%<replacement%>} %<\tlvar%>#S
\RegexVarReplaceOnceT %<\regexvar%> {%<replacement%>} %<\tlvar%> {%<true code%>}#S
\RegexVarReplaceOnceF %<\regexvar%> {%<replacement%>} %<\tlvar%> {%<false code%>}#S
\RegexVarReplaceOnceTF %<\regexvar%> {%<replacement%>} %<\tlvar%> {%<true code%>} {%<false code%>}#S
\RegexReplaceAll {%<regex%>} {%<replacement%>} %<\tlvar%>#S
\RegexReplaceAllT {%<regex%>} {%<replacement%>} %<\tlvar%> {%<true code%>}#S
\RegexReplaceAllF {%<regex%>} {%<replacement%>} %<\tlvar%> {%<false code%>}#S
\RegexReplaceAllTF {%<regex%>} {%<replacement%>} %<\tlvar%> {%<true code%>} {%<false code%>}#S
\RegexVarReplaceAll %<\regexvar%> {%<replacement%>} %<\tlvar%>#S
\RegexVarReplaceAllT %<\regexvar%> {%<replacement%>} %<\tlvar%> {%<true code%>}#S
\RegexVarReplaceAllF %<\regexvar%> {%<replacement%>} %<\tlvar%> {%<false code%>}#S
\RegexVarReplaceAllTF %<\regexvar%> {%<replacement%>} %<\tlvar%> {%<true code%>} {%<false code%>}#S
\RegexReplaceCaseOnce {%<{regex1} {replacement1} {regex2} {replacement2} ...%>} %<\tlvar%>#S
\RegexReplaceCaseOnceT {%<{regex1} {replacement1} {regex2} {replacement2} ...%>} %<\tlvar%> {%<true code%>}#S
\RegexReplaceCaseOnceF {%<{regex1} {replacement1} {regex2} {replacement2} ...%>} %<\tlvar%> {%<false code%>}#S
\RegexReplaceCaseOnceTF {%<{regex1} {replacement1} {regex2} {replacement2} ...%>} %<\tlvar%> {%<true code%>} {%<false code%>}#S
\RegexReplaceCaseAll {%<{regex1} {replacement1} {regex2} {replacement2} ...%>} %<\tlvar%>#S
\RegexReplaceCaseAllT {%<{regex1} {replacement1} {regex2} {replacement2} ...%>} %<\tlvar%> {%<true code%>}#S
\RegexReplaceCaseAllF {%<{regex1} {replacement1} {regex2} {replacement2} ...%>} %<\tlvar%> {%<false code%>}#S
\RegexReplaceCaseAllTF {%<{regex1} {replacement1} {regex2} {replacement2} ...%>} %<\tlvar%> {%<true code%>} {%<false code%>}#S
\CharLowercase %<char%>#S
\CharUppercase %<char%>#S
\CharTitlecase %<char%>#S
\CharFoldcase %<char%>#S
\CharStrLowercase %<char%>#S
\CharStrUppercase %<char%>#S
\CharStrTitlecase %<char%>#S
\CharStrFoldcase %<char%>#S
\CharSetLccode {int expr1} {int expr2}#S
\CharSetUccode {int expr1} {int expr2}#S
\CharValueLccode {int expr}#S
\CharValueUccode {int expr}#S
\TextExpand {text}#S
\TextLowercase {text}#S
\TextUppercase {text}#S
\TextTitlecase {text}#S
\TextTitlecaseFirst {text}#S
\TextLangLowercase {language} {text}#S
\TextLangUppercase {language} {text}#S
\TextLangTitlecase {language} {text}#S
\TextLangTitlecaseFirst {language} {text}#S
\FileInput {file name}#S
\FileInput{file}#Si
\FileIfExistInput {file name}#S
\FileIfExistInput{file}#Si
\FileIfExistInputF {file name} {false code}#S
\FileIfExistInputF{file}{false code}#Si
\FileGet {%<file name%>} {%<setup%>} %<\tlvar%>#S
\FileGet{file name}{setup}{cmd}#Sd
\FileGetT {%<file name%>} {%<setup%>} %<\tlvar%> {%<true code%>}#S
\FileGetT{file name}{setup}{cmd}{true code}#Sd
\FileGetF {%<file name%>} {%<setup%>} %<\tlvar%> {%<false code%>}#S
\FileGetF{file name}{setup}{cmd}{false code}#Sd
\FileGetTF {%<file name%>} {%<setup%>} %<\tlvar%> {%<true code%>} {%<false code%>}#S
\FileGetTF{file name}{setup}{cmd}{true code}{false code}#Sd
\FileIfExist {%<file name%>}#S
\FileIfExistT {%<file name%>} {%<true code%>}#S
\FileIfExistF {%<file name%>} {%<false code%>}#S
\FileIfExistTF {%<file name%>} {%<true code%>} {%<false code%>}#S
\QuarkVarIfNoValue %<\tlvar%>#S
\QuarkVarIfNoValueT %<\tlvar%> {%<true code%>}#S
\QuarkVarIfNoValueF %<\tlvar%> {%<false code%>}#S
\QuarkVarIfNoValueTF %<\tlvar%> {%<true code%>} {%<false code%>}#S
\LegacyIf {%<name%>}#S
\LegacyIfT {%<name%>} {%<true code%>}#S
\LegacyIfF {%<name%>} {%<false code%>}#S
\LegacyIfTF {%<name%>} {%<true code%>} {%<false code%>}#S
\LegacyIfSetTrue {%<name%>}#S
\LegacyIfSetFalse {%<name%>}#S
\LegacyIfSet {%<name%>} {%<bool expr%>}#S
\ClistVarSort{arg1}{arg2}#S
\SeqJoin{arg1}{arg2}#S
\SeqJoinExtended{arg1}{arg2}{arg3}{arg4}#S
\SeqVarSort{arg1}{arg2}#S
