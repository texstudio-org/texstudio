# asyfig package
# Matthew Bertucci 1/29/2022 for v0.1c

#include:asyalign
#include:color
#include:ifmtarg
#include:ifpdf
#include:ifplatform
#include:import
#include:graphicx
#include:pdftexcmds
#include:suffix
#include:xkeyval
#include:asyprocess

#keyvals:\usepackage/asyfig#c
process=#all,none,auto
#endkeyvals

\asyfig{file}
\asyfig*{file}
\asypath{path%URL}
