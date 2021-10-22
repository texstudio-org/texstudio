# bitset package
# Matthew Bertucci 10/20/2021 for v1.0

#include:infwarerr
#include:intcalc
#include:bigintcalc

\bitsetReset{BitSet}
\bitsetLet{BitSet1}{BitSet2}

\bitsetSetBin{BitSet}{BinaryNumber}
\bitsetSetOct{BitSet}{OctalNumber}
\bitsetSetHex{BitSet}{HexadecimalNumber}
\bitsetSetDec{BitSet}{DecimalNumber}

\bitsetGetBin{BitSet}{MinSize}
\bitsetGetOct{BitSet}{MinSize}
\bitsetGetHex{BitSet}{MinSize}
\bitsetGetDec{BitSet}

\bitsetAnd{BitSet1}{BitSet2}
\bitsetAndNot{BitSet1}{BitSet2}
\bitsetOr{BitSet1}{BitSet2}
\bitsetXor{BitSet1}{BitSet2}

\bitsetShiftLeft{BitSet}{ShiftAmount}
\bitsetShiftRight{BitSet}{ShiftAmount}

\bitsetClear{BitSet}{Index}
\bitsetSet{BitSet}{Index}
\bitsetFlip{BitSet}{Index}
\bitsetSetValue{BitSet}{Index}{Bit}

\bitsetGet{BitSet}{Index}
\bitsetNextClearBit{BitSet}{Index}
\bitsetNextSetBit{BitSet}{Index}
\bitsetGetSetBitList{BitSet}

\bitsetSize{BitSet}
\bitsetCardinality{BitSet}

\bitsetIsDefined{BitSet}{Then}{Else}
\bitsetIsEmpty{BitSet}{Then}{Else}
\bitsetEquals{BitSet1}{BitSet2}{Then}{Else}
\bitsetIntersects{BitSet1}{BitSet2}{Then}{Else}
\bitsetQuery{BitSet}{Index}{Then}{Else}