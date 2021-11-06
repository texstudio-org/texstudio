# fp-basic package
# Matthew Bertucci 9/21/2021 for v2.1d

\FPset{variable%cmd}{value}#d
\FPprint{variable}
\FPadd{variable%cmd}{value1}{value2}#d
\FPdiv{variable%cmd}{value1}{value2}#d
\FPmul{variable%cmd}{value1}{value2}#d
\FPsub{variable%cmd}{value1}{value2}#d
\FPabs{variable%cmd}{value}#d
\FPneg{variable%cmd}{value}#d
\FPsgn{variable%cmd}{value}#d
\FPiflt{value1}{value2}
\FPifeq{value1}{value2}
\FPifgt{value1}{value2}
\FPifneg{value}
\FPifpos{value}
\FPifzero{value}
\FPifint{value}

\ifFPdebug#*
\FPdebugfalse#*
\FPdebugtrue#*
\ifFPmessages#*
\FPmessagesfalse#*
\FPmessagestrue#*
\ifFPtest#*