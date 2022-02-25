# euscript package
# Matthew Bertucci 12/13/2021 for v3.00

#keyvals:\usepackage/euscript#c
mathcal
mathscr
#endkeyvals

\EuScript{text%plain}#m
\CMcal{text%plain}#*m

#ifOption:mathscr
\mathscr{text%plain}#m
#endif
