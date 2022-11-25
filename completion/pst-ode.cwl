# pst-ode package
# Matthew Bertucci 2022/11/24 for v0.18

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
rk4
#endkeyvals

\pstODEsaveState{state}
\pstODErestoreState{state}

\PSTODELoaded#S
