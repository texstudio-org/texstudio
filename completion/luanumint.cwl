# luanumint package
# Matthew Bertucci 2023/07/25 for v1.0

#include:luacode
#include:breqn
#include:xkeyval

# doesn't make much sense to use without options, hence the #*'s
\luaMidpt{function}#*m
\luaMidpt[options%keyvals]{function}#m
\luaMidptSteps{function}#*m
\luaMidptSteps[options%keyvals]{function}#m
\luaTrapz{function}#*m
\luaTrapz[options%keyvals]{function}#m
\luaTrapzSteps{function}#*m
\luaTrapzSteps[options%keyvals]{function}#m
\luaSimpsonOneThird{function}#*m
\luaSimpsonOneThird[options%keyvals]{function}#m
\luaSimpsonOneThirdSteps{function}#*m
\luaSimpsonOneThirdSteps[options%keyvals]{function}#m
\luaSimpsonThreeEighth{function}#*m
\luaSimpsonThreeEighth[options%keyvals]{function}#m
\luaSimpsonThreeEighthSteps{function}#*m
\luaSimpsonThreeEighthSteps[options%keyvals]{function}#m

#keyvals:\luaMidpt,\luaMidptSteps,\luaTrapz,\luaTrapzSteps,\luaSimpsonOneThird,\luaSimpsonOneThirdSteps,\luaSimpsonThreeEighth,\luaSimpsonThreeEighthSteps
a=%<number%>
b=%<number%>
n=%<integer%>
func=%<label%>
trun=%<integer%>
#endkeyvals
