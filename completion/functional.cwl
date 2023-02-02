# functional package
# Matthew Bertucci 2023/01/07 for v2023A

# Note on cwl: the package author Jianrui Lyu encourages use of spaces between
# args which along with the need to have proper "\newcommand" completion
# requires many commands to be listed twice; once with what the user sees,
# another with #S that tells the completer what to do. In some cases for reasons
# I don't understand, the order matters, e.g. with \TlMapVariable.

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
# Evaluating Functions
\evalWhole{tokens}
\evalNone{tokens}

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
\fileGet{file name%file}{setup}{cmd}#Sd
\fileGetT {%<file name%>} {%<setup%>} %<\tlvar%> {%<true code%>}
\fileGetT{file name%file}{setup}{cmd}{true code}#Sd
\fileGetF {%<file name%>} {%<setup%>} %<\tlvar%> {%<false code%>}
\fileGetF{file name%file}{setup}{cmd}{false code}#Sd
\fileGetTF {%<file name%>} {%<setup%>} %<\tlvar%> {%<true code%>} {%<false code%>}
\fileGetTF{file name%file}{setup}{cmd}{true code}{false code}#Sd
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
\PrgNewConditional %<\function%> {%<arg spec%>} {%<code%>}#S
\PrgNewConditional{cmd}{xargs}{def}#Sd
