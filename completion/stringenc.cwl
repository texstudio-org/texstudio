# stringenc package
# Matthew Bertucci 11/30/2021 for v1.12

#include:infwarerr
#include:ltxcmds
#include:pdfescape
#include:pdftexcmds

\StringEncodingConvert{cmd}{string}{from}{to}#*d
\StringEncodingSuccessFailure{success}{failure}#*
\StringEncodingConvertTest{cmd}{string}{from}{to}{success}{failure}#*d
\StringEncodingList#*
\StringEncodingLoad{enc file}#*