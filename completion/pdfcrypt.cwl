# pdfcrypt package
# Matthew Bertucci 1/8/2021 for v1.1

#include:infwarerr
#include:keyval

\pdfcryptsetup{options%keyvals}

#keyvals:\usepackage/pdfcrypt#c,\pdfcryptsetup
owner=%<owner password%>
user=%<user password%>
print#true,false
copy#true,false
edit#true,false
annotate#true,false
all
none
debug#true,false
set#true,false
pdftex
vtex
#endkeyvals

\nopdfcrypt
\pdfcrypt#*