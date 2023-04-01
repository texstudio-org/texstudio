# qcircuit package
# Matthew Bertucci 2023/03/31 for v2.6.0

#include:xy
#include:ifpdf

#keyvals:\usepackage/qcircuit#c
braket
qm
#endkeyvals

#ifOption:braket
\bra{arg%formula}
\ket{arg%formula}
#endif

#ifOption:qm
\ip{arg1%formula}{arg2%formula}
\melem{arg1%formula}{arg2%formula}{arg3%formula}
\expval{arg%formula}
\op{arg1%formula}{arg2%formula}
#endif

\Qcircuit {%<matrix%>}
\Qcircuit %<⟨spacing-spec⟩%> {%<matrix%>}
\Qcircuit{formula}#S

\barrier[length]{integer}
\barrier{integer}
\cctrl{integer}
\cctrlo{integer}
\cds{integer}{label}
\cghost{arg}
\control
\controlo
\ctrl{integer}
\ctrlo{integer}
\cw
\cw[integer]
\cwa
\cwa[integer]
\cwx
\cwx[integer]
\dstick{label}
\gate{label}
\gategroup{row1}{col1}{row2}{col2}{length}{hl-type}
\ghost{arg}
\inputgroup{row1}{row2}{length}{label}
\inputgrouph{row1}{row2}{length1}{label}{length2}
\inputgroupv{row1}{row2}{length1}{length2}{label}
\link{integer1}{integer2}
\lstick{label}
\measure{label}
\measureD{label}
\measuretab{label}
\meter
\meterB{label}
\metersymb
\multigate{integer}{label}
\multimeasure{integer}{label}
\multimeasureD{integer}{label}
\nghost{arg}
\pureghost{arg}
\push{label}
\qswap
\qw
\qw[integer]
\qwa
\qwa[integer]
\qwx
\qwx[integer]
\rstick{label}
\sgate{label}{integer}
\smeterB{label}{integer}
\targ
\ustick{label}