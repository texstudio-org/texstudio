# bxpdfver package
# Matthew Bertucci 2022/04/29 for v0.5a

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