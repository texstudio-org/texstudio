# bitpattern package
# Matthew Bertucci 1/28/2022

#include:keyval
#include:calc
#include:multido

#keyvals:\usepackage/bitpattern#c
littleEndian
bigEndian
numberBitsAbove
numberBitsBelow
noBitNumbers
numberFieldsOnce
numberFieldsTwice
numberAllBits
#endkeyvals

\bitpattern{%<name1%>}[%<size1%>]%<{name2}[size2]...%>/
\bitpattern[%<options%>]{%<name1%>}[%<size1%>]%<{name2}[size2]...%>/

#keyvals:\bitpattern
littleEndian
bigEndian
numberBitsAbove
numberBitsBelow
noBitNumbers
numberFieldsOnce
numberFieldsTwice
numberAllBits
startBit=%<number%>
bitWidth=##L
tickHeight=##L
#endkeyvals

\bpLittleEndian#*
\bpBigEndian#*
\bpNumberBitsAbove#*
\bpNumberBitsBelow#*
\bpNoBitNumbers#*
\bpNumberFieldsOnce#*
\bpNumberFieldsTwice#*
\bpNumberAllBits#*
\bpStartAtBit{number}#*
\bpSetBitWidth{width}#*
\bpSetTickHeight{height}#*
\bpFormatField{text%plain}#*
\bpFormatBitNumber{number}#*
