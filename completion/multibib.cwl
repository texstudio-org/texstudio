# multibib package
# Matthew Bertucci 3/9/2022 for v1.4

#keyvals:\usepackage/multibib#c
labeled
resetlabels
#endkeyvals

\newcites{suffix1,suffix2,...}{title1,title2,...%text}
\setbiblabelwidth{number}

#keyvals:\bibliographystyle#c
mbplain
#endkeyvals

\ifcontinuouslabels#S
\continuouslabelstrue#S
\continuouslabelsfalse#S
\iflabeled#S
\labeledtrue#S
\labeledfalse#S
\mylop{arg}#S
\to{arg}#S
\mylopoff{arg}#S
\newusecounter{counter}#S
\argdef#S
\argedef#S
\plugh#S
\testchar#S