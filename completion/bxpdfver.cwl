# bxpdfver package
# Matthew Bertucci 2026/05/21 for v0.8b

#include:ifthen

#keyvals:\usepackage/bxpdfver#c
1.4
1.5
1.6
1.7
2.0
nocompress
compress
noobjcompress
objcompress
native
dvipdfmx
dvips
dvisvgm
dviout
xdvi
disabled
nodvidriver
new-dvipdfmx
lenient
#endkeyvals

\setpdfversion{version}
\suppresspdfcompression
\suppresspdfobjcompression
\setpdfdecimaldigits{precision}
\preservepdfdestinations

# not documented
\bxDebug{text}#S
\bxpdfverDecimalDigits#*
\bxpdfverMajorVersion#*
\bxpdfverMinorVersion#*
\bxpdfverPkResolution#*
\setpdfpkresolution{number}#*