# mol2chemfig package
# Matthew Bertucci 2022/08/11 for v1.5

#include:xcolor
#include:chemfig
#include:twoopt
#include:ifmtarg
#include:calc
#include:xstring
#include:tikzlibrarydecorations

\mcfinput{file}#i
\mcfpush{anchor1}{angle1:dist1}{anchor2}{angle2:dist2}
\mcfpush[length]{anchor1}{angle1:dist1}{anchor2}{angle2:dist2}
\mcfpush[length1][length2]{anchor1}{angle1:dist1}{anchor2}{angle2:dist2}

\mcfabove{arg1}{arg2}#*
\mcfaboveright{arg1}{arg2}{arg3}#*
\mcfatomno{number}#*
\mcfbelow{arg1}{arg2}#*
\mcfbelowright{arg1}{arg2}{arg3}#*
\mcfcringle{arg}#*
\mcfelmove[opt]{arg1}{arg2}{arg3}{arg4}#*
\mcfelmove{arg1}{arg2}{arg3}{arg4}#*
\mcfleft{arg1}{arg2}#*
\mcfminus#*
\mcfplus#*
\mcfright{arg1}{arg2}#*
\mcfvspace#*

mcfbgcolor#B
mcfpusharrowcolor#B
mcfatomnocolor#B
