# pst-ob3d package
# Matthew Bertucci 2/23/2022 for v0.15

#include:pstricks

\pstODEsolve{result}{output format}{t0}{t1}{N}{X_0}{function%definition}
\pstODEsolve[options%keyvals]{result}{output format}{t0}{t1}{N}{X_0}{function%definition}

#keyvals:\pstODEsolve#c
dt0=%<number%>
append
saveData
algebraicOutputFormat
algebraicT
algebraicN
algebraicIC
algebraic
algebraicAll
silent
varsteptol=%<number%>
#endkeyvals

\pstODEsaveState{state}
\pstODErestoreState{state}

\PSTODELoaded#S