# spdef package
# Matthew Bertucci 2/7/2022 for v1.2

#keyvals:\usepackage/spdef#c,\RequirePackage/spdef#c
ph
pa
!ph
!pa
use=%<csname%>
!use=%<csname%>
#endkeyvals

\ifsmartphone#*
\smartphonetrue#*
\smartphonefalse#*

\ifsp{true}{false}

\expexe{arg}#*