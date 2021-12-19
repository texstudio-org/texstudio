# euscript package
# Matthew Bertucci 12/13/2021 for v3.00

#keyvals:\usepackage/euscript#c
mathcal
mathscr
#endkeyvals

\EuScript{letters}#m
\CMcal{letters}#*m

#ifOption:mathscr
\mathscr{letters}#m
#endif