# bidituftesidenote package
# Matthew Bertucci 2022/06/03 for v0.4

#include:xifthen
#include:ragged2e
#include:setspace
#include:biditools
#include:natbib
#include:bibentry
#include:optparams

\bidituftesidenotemarginpar{text}#*
\footnotelayout#*
\gsetlength{length cmd}{length}#*
\LTRbidituftesidenotemarginpar{text}#*
\LTRcite{keylist}#c
\LTRmarginnote[offset%l]{text}
\LTRmarginnote{text}
\LTRsidenote[number][offset%l]{text}
\LTRsidenote[number]{text}
\LTRsidenote{text}
\marginnote[offset%l]{text}
\marginnote{text}
\multfootsep#*
\multiplefootnotemarker#*
\RTLbidituftesidenotemarginpar{text}#*
\RTLcite{keylist}#c
\RTLmarginnote[offset%l]{text}
\RTLmarginnote{text}
\RTLsidenote[number][offset%l]{text}
\RTLsidenote[number]{text}
\RTLsidenote{text}
\setcitationfont{font commands}
\setLTRcitationfont{font commands}
\setLTRmarginnotefont{font commands}
\setLTRsidenotefont{font commands}
\setmarginnotefont{font commands}
\setRTLcitationfont{font commands}
\setRTLmarginnotefont{font commands}
\setRTLsidenotefont{font commands}
\setsidenotefont{font commands}
\sidenote[number][offset%l]{text}
\sidenote[number]{text}
\sidenote{text}