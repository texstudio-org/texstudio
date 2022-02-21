# mode: multido.sty
# dani/2006-02-22; updated by Matthew Bertucci 9/27/2021 for v1.42

\multido{variables%cmd}{repetitions}{actions}#d
\MultidoCheckNames#*
\mmultido{variables%cmd}{repetitions}{actions}#*d
\Multido{variables%cmd}{repetitions}{actions}#*d
\MMultido{variables%cmd}{repetitions}{actions}#*d
\multidocount#*
\multidostop#*
\fpAdd{num1}{num2}{cmd}#d
\fpSub{num1}{num2}{cmd}#d
\MultidoLoaded#S
\TheAtCode#S
\fileversion#S
\filedate#S

# if undefined, multido defines \FPadd and \FPsub as \fpAdd and \fpSub, resp.
\FPadd{num1}{num2}{cmd}#Sd
\FPsub{num1}{num2}{cmd}#Sd
