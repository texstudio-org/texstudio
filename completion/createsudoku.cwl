# createsudoku package
# Matthew Bertucci 2022/12/01 for v1.0

#include:solvesudoku

\generategrid
\generategrid[file]
\genfile
\prevfile
\currfile
\setsudrandom{number}
\initialelimination
\elimseventeen
\elimnum{number}
\elimcross
\elimex
\elimcrossandnines
\elimcrossandex
\elimcrossandexandnines

# not in main documentation
\acluenotdeletedfalse#S
\acluenotdeletedtrue#S
\deleteaclue#*
\elimclues#*
\elimcluesonebyone#*
\gencommentary{text}#*
\ifacluenotdeleted#S
\oldcommentary{text}#S
\printsudresults#*
\swapcolpair{colstartcell1}{colstartcell2}
\swaprowpair{rowstartcell1}{rowstartcell2}
\swaps#*
\toomanyloops#S
\trysolution#*
\writestartgrid#*
\writestate{file}#*

# from random.tex
\randomi#*
\nextrandom#*
\setrannum{count register}{min}{max}#*
\setrandim{dimen register}{min}{max}#*
\pointless#*
\PoinTless#S
\ranval#*
