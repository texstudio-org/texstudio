# nl-interval package
# Matthew Bertucci 9/19/2021 for v1.0

#include:tkz-fct

\nlAxisX{min}{max}#/tikzpicture
\nlinfnum{number}{o or c}#/tikzpicture
\nlinfnum[options%keyvals]{number}[sub]{o or c}[height]#/tikzpicture
\nlnuminf{number}{o or c}#/tikzpicture
\nlnuminf[options%keyvals]{number}[sub]{o or c}[height]#/tikzpicture
\nlnumnum{number1}{o or c}{number2}{o or c}#/tikzpicture#/tikzpicture
\nlnumnum[options%keyvals]{number1}[sub1]{o or c}{number2}[sub2]{o or c}[height]#/tikzpicture

#keyvals:\nlinfnum#c,\nlnuminf#c,\nlnumnum#c
pattern=
color=#%color
#endkeyvals
