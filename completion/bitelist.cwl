# bitelist package
# Matthew Bertucci 2022/05/31 for v0.1

\BiteMake{def-cmd}{cmd}{find}#*d
\BiteFindByIn{find}{cmd}{list}#*
\BiteSep#*
\BiteStop#*
\BiteCrit#*
\BiteMakeIfOnly{def-cmd}{cmd}{find}#*d
\BiteIfCrit{suffix}{yes}{no}#*
\BiteMakeIf{def-cmd}{cmd}{find}#*d
\BiteFindByInIn{find}{cmd}{list}{yes}{no}#*
\BiteIfSpace#*
\BiteGetNextWord{list}{yes}{no}#*
\BiteFindByInBraces{find}{cmd}{list}{yes}{no}#*
\BiteMakeIfBraces{def-cmd}{cmd}{find}#*d
\BiteTidyI{prefix}{suffix}#*
\BiteTidyII#*
\BiteTidied#*
\fileinfo#S
\filename#S
\filedate#S
\fileversion#S