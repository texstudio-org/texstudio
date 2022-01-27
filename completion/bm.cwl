# bm, ctan
# tbraun 6/11/2008
# jdshor 4/15/2017

#keyvals:\usepackage/bm#c
nopmb
warn
info
silent
#endkeyvals

\bm{math expression}#m
\hm{math expression}#m

\bmdefine{cmd}{def}#d
\hmdefine{cmd}{def}#d

\boldsymbol{math expression}#*m
\heavysymbol{math expression}#*m

\DeclareBoldMathCommand[math version%keyvals]{cmd}{def}#d
\DeclareBoldMathCommand{cmd}{def}#d

#keyvals:\DeclareBoldMathCommand#c
bold
heavy
#endkeyvals

\bmmax
\hmmax
