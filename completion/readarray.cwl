# readarray package
# Matthew Bertucci 11/22/2021 for v3.1

#include:forloop
#include:listofitems

\readdef{file}{data-macro%cmd}#d
\readrecordarray{file}{array-identifier%cmd}#d
\readarray{data-macro}{array-identifier%cmd}[-,columns]#d
\readarray{data-macro}{array-identifier%cmd}[-,rows,columns]#d
\readarray*{data-macro}{array-identifier%cmd}[-,columns]#d
\readarray*{data-macro}{array-identifier%cmd}[-,rows,columns]#d
\initarray{array-identifier%cmd}[rows,columns]#d
\initarray{array-identifier%cmd}[planes,rows,columns]#d
\mergearray{from-array-id}{to-array-id}[row,column]
\mergearray{from-array-id}{to-array-id}[plane,row,column]
\typesetarray{array-identifier}
\arraytomacro{array-identifier}[row,column]{macro%cmd}#d
\arraytomacro{array-identifier}[plane,row,column]{macro%cmd}#d
\setvalue{array-identifier}[row,column]{value}
\setvalue{array-identifier}[plane,row,column]{value}
\readarraysepchar{parsing-separator-char}
\readarrayendlinechar=%<<end-of-line-catcode>%>
\readarrayinitvalue#*
\typesetcell{arg}#*
\typesetplanesepchar#*
\typesetrowsepchar#*
\typesetcolsepchar#*
\nocheckbounds
\checkbounds
\hypercheckbounds
\ifignoreblankreadarrayrecords#*
\ignoreblankreadarrayrecordstrue#*
\ignoreblankreadarrayrecordsfalse#*
\nrows
\ncols
\nrecords
\ArrayRecord
\ArrayRecord[record]
\readarraybackslash#*
\readarrayPackageVersion#S
\readarrayPackageDate#S

# deprecated
\arraydump#S
\scalardump#S