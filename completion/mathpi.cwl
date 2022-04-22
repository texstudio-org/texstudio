# mathpi package
# Matthew Bertucci 4/21/2022 for v1.1

#keyvals:\usepackage/mathpi#c
mathfrak
mathcal
mathscr
mathbb
#endkeyvals

#ifOption:mathfrak
\mathfrak{text%plain}#m
#endif

#ifOption:mathscr
\mathscr{text%plain}#m
#endif

#ifOption:mathbb
\mathbb{text%plain}#m
#endif