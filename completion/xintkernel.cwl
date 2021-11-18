# xintkernel package
# Matthew Bertucci 11/16/2021 for v1.4j

\XINTrestorecatcodes#*
\XINTrestorecatcodesendinput#*
\XINTsetcatcodes#*
\XINTsetupcatcodes#*

\xintdothis#*
\xintorthat#*

\xintodef#*
\xintodef{cmd}#Sd
\xintoodef#*
\xintoodef{cmd}#Sd
\xintfdef#*
\xintfdef{cmd}#Sd

\odef
\odef{cmd}#Sd
\oodef
\oodef{cmd}#Sd
\fdef
\fdef{cmd}#Sd

\xintReverseOrder{list}
\xintreverseorder{list}#S
\xintLength{list}
\xintlength{list}#S
\xintFirstItem{list}
\xintfirstitem{list}#S
\xintLastItem{list}
\xintlastitem{list}#S
\xintFirstOne{list}
\xintfirstone{list}#S
\xintLastOne{list}
\xintlastone{list}#S
\xintLengthUpTo{integer}{list}
\xintlengthupto{integer}{list}#S
\xintReplicate{integer}{content}
\xintreplicate{integer}#*
\xintGobble{integer}
\xintgobble{integer}
\xintUniformDeviate{integer}#*

\xintMessage{package}{label%plain}{message%text}#*
\ifxintverbose#*
\xintverbosetrue#*
\xintverbosefalse#*
\ifxintglobaldefs#*
\xintglobaldefstrue#*
\xintglobaldefsfalse#*

# the following slightly improve the appearance of expl3 code
\xint#S
\XINT#S