# sansmath package
# Matthew Bertucci 11/11/2021 for v1.1

#keyvals:\usepackage/sansmath#c
T1
EULERGREEK
eulergreek
#endkeyvals

\sansmath
\unsansmath
\begin{sansmath}
\end{sansmath}
\mathsfsl{text%plain}#m
\sfsl#S
\mathsfbf{text%plain}#m
\sfbf#S

#ifOption:eulergreek
\matheug{arg}
#endif

#ifOption:EULERGREEK
\matheug{arg}
#endif

\sansmathencoding#*
\EulGreek#*
\EuUCGreek#*
\NonEulGreek#*
\EulGreekList#*
\NonEulGreek#*
\sfMathSwitch#*
