# pxjahyper package
# Matthew Bertucci 2022/07/22 for v1.2

#include:platex
#include:keyval
#include:ltxcmds
#include:etoolbox
#include:bxjatoucs

#keyvals:\usepackage/pxjahyper#c
dvipdfmx
dvipdfm
dvips
nodvidriver
resetdvidriver
autodvidriver
tounicode
notounicode
out2uni
noout2uni
convbkmk
noconvbkmk
papersize
nopapersize
charcmds
nocharcmds
bigcode
nobigcode
jacommentline
nojacommentline
disablecmds
nodisablecmds
otfutf
nootfutf
otfcid
nootfcid
otfmacros
nootfmacros
force-unicode
#endkeyvals

#ifOption:tounicode
#include:pxjahyper-enc
#endif

#ifOption:bigcode
#include:uplatex
#endif

\pxjahypersetup{options%keyvals}

#keyvals:\pxjahypersetup#c,\usepackage/pxjahyper#c
fallback=#geta,delete
extjis#true,false
ajhankaku-chars#true,false
#endkeyvals

\Ux{Unicode 符号値 16 進}
\pxDeclarePdfTextCommand{cmd}{jis}{ucs}#d
\pxDeclarePdfTextComposite{cmd}{arg}{jis}{ucs}#d
\pxHyperrefUnicodePatched#S