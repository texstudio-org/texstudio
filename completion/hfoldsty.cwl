# hfoldsty package
# Matthew Bertucci 2022/07/21 for v1.15

#include:fontenc
# loads T1 option of fontenc
#include:ifthen

#keyvals:\usepackage/hfoldsty#c
oldstylett
newstylett
origtt
fix-cm
#endkeyvals

#ifOption:fix-cm
#include:fix-cm
#endif

\oldstylenums{text}
\newstylenums{text}