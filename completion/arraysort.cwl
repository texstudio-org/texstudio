# arraysort package
# Matthew Bertucci 1/18/2021 for v1.0

#include:arrayjobx
#include:calc
#include:ifthen
#include:etoolbox
#include:xargs
#include:macroswap

#keyvals:\usepackage/arraysort#c
comparestr
comparenum
randompart
#endkeyvals

\sortArray{integer}{array}
\sortArray[comparator%keyvals]{integer}{array}
\sortArray[comparator%keyvals][start]{integer}{array}

#ifOption:comparestr
#include:pdftexcmds
#keyvals:\sortArray#c
arraysortcomparestr
#endkeyvals
\arraysortcomparestr{arg1}{arg2}#*
#endif

#ifOption:comparenum
#keyvals:\sortArray#c
arraysortcomparenum
#endkeyvals
\arraysortcomparenum{arg1}{arg2}#*
#endif

#ifOption:randompart
#include:lcg
\sortArrayPartitionRand{comparator}{start}{end}{array}#*
#endif

\sortArrayPartitionMed{comparator}{start}{end}{array}#*
\sortArrayPartitionMid{comparator}{start}{end}{array}#*
\sortArrayPartitionFirst{comparator}{start}{end}{array}#*