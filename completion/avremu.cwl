# avremu package
# Matthew Bertucci 1/29/2022 for v0.1

#include:etoolbox
#include:tabularx
#include:kvoptions

#keyvals:\usepackage/avremu#c
debug#true,false
#endkeyvals

\useavremulibrary{list of libraries}

## automatically loads avr.numbers, avr.binary, avr.bitops, avr.memory, avr.instr, avr.io, and avr.testsuite
## from avr.numbers
# no new user commands

## from avr.binary
\avrloadc{file}
\avrloadc[compiler options]{file}
\avrcompile{file}#*
\avrcompile[compiler options]{file}#*
\avrloadihex{file}

## from avr.bitops
# no new user commands

## from avr.memory
# no new user commands

## from avr.instr
\ifavrbreak#*
\avrbreaktrue#*
\avrbreakfalse#*
\avrstep
\avrstep[number]
\avrrun
\avrsinglestep
\avrinstrcount

## from avr.io
\avrUDR
\avrUDRclear

## from avr.testsuite
# no new user commands

## from avr.draw (not automatically loaded)
\avrdrawiter{arg}#*
\avrdrawSize{arg1}{arg2}#*
\avrdrawppm{file}
