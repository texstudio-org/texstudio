# lualinalg package
# Matthew Bertucci 2023/02/11 for v1.0

#include:xkeyval
#include:amsmath
#include:luamaths
#include:luacode

\vectorNew{name}{entries}
\vectorPrint{vector}
\vectorPrint[truncate=%<integer%>]{%<vector%>}
\vectorGetCoordinate{vector}{index}
\vectorSetCoordinate{vector}{index}{value}
\vectorCopy{name}{vector}
\vectorAdd{name}{vector1}{vector2}
\vectorSub{name}{vector1}{vector2}
\vectorMulNum{name}{vector}{number}
\vectorDot{vector1}{vector2}
\vectorCross{name}{vector1}{vector2}
\vectorSumNorm{vector}
\vectorEuclidNorm{vector}
\vectorpNorm{vector}{p}
\vectorSupNorm{vector}
\vectorCreateRandom{name}{dimension}{a}{b}
\vectorOp{name}{expression}
\vectorGetAngle{vector1}{vector2}
\vectorParse{vector}

\vectorGramSchmidt{list of vectors}
\vectorGramSchmidt[options%keyvals]{list of vectors}
\vectorGramSchmidtSteps{list of vectors}
\vectorGramSchmidtSteps[options%keyvals]{list of vectors}

#keyvals:\vectorGramSchmidt,\vectorGramSchmidtSteps
brckt=#round,square,curly
truncate=%<integer%>
#endkeyvals

\complexRound{a+bi}{num digits}

\matrixNew{name}{entries}

\matrixPrint{matrix}
\matrixPrint[options%keyvals]{matrix}

#keyvals:\matrixPrint
type=#pmatrix,bmatrix,vmatrix,Vmatrix
truncate=%<integer%>
#endkeyvals

\matrixNumRows{matrix}
\matrixNumCols{matrix}
\matrixGetElement{matrix}{i}{j}
\matrixAdd{name}{matrix1}{matrix2}
\matrixSub{name}{matrix1}{matrix2}
\matrixMulNum{name}{number}{matrix}
\matrixMul{name}{matrix1}{matrix2}
\matrixPow{name}{matrix}{power}
\matrixInvert{name}{matrix}
\matrixTrace{matrix}
\matrixConjugate{name}{matrix}
\matrixConjugateT{name}{matrix}
\matrixNormOne{matrix}
\matrixNormInfty{matrix}
\matrixNormMax{matrix}
\matrixNormF{matrix}
\matrixRank{matrix}
\matrixDet{matrix}
\matrixTranspose{name}{matrix}
\matrixSetElement{matrix}{i}{j}{value}
\matrixSubmatrix{name}{matrix}{i}{j}{k}{l}
\matrixConcatH{name}{matrix1}{matrix2}
\matrixConcatV{name}{matrix1}{matrix2}
\matrixOp{matrix}{expression}
\matrixCopy{name}{matrix}
\matrixCreateRandom{name}{i}{j}{k}{l}
\matrixSwapRows{name}{matrix}{row1}{row2}
\matrixMulRow{name}{matrix}{row}{number}
\matrixMulAddRow{name}{matrix}{row1}{number}{row2}
\matrixSwapCols{name}{matrix}{col1}{col2}
\matrixMulCol{name}{matrix}{col}{number}
\matrixMulAddCol{name}{matrix}{col1}{number}{col2}
\matrixRREF{name}{matrix}

\matrixRREFSteps{matrix}
\matrixRREFSteps[options%keyvals]{matrix}
\matrixGaussJordan{name}{matrix1}{matrix2}
\matrixGaussJordanSteps{matrix1}{matrix2}
\matrixGaussJordanSteps[options%keyvals]{matrix1}{matrix2}

#keyvals:\matrixRREFSteps,\matrixGaussJordanSteps
type=#pmatrix,bmatrix,vmatrix,Vmatrix
truncate=%<integer%>
#endkeyvals

# not documented
\matrixRREFERR{arg}#S
\matrixRREFE{arg}#S