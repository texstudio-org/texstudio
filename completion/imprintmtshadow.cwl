# imprintmtshadow package
# Matthew Bertucci 2/22/2022 for v1.0

#include:keyval

#keyvals:\usepackage/imprintmtshadow#c
scaled=%<factor%>
#endkeyvals

\imprintmtshadowfamily
\textimprintmtshadow{text}
\ProcessOptionsWithKV{family}#S