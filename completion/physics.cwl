# The physics package was created by Sergio C. de la Barrera physics.tex@gmail.com
# This file was created by Carlos Eduardo Valencia Urbina (2014-04-04). It contains most of the current commands of the physics package.
#include:amsmath

#keyvals:\usepackage/physics#c
trig
notrig
uprightdiff
italicdiff
bolddel
arrowdel
#endkeyvals

# physics package (commands taken from the physics manual of v1.3)
\Bqty{expression}#m
\Im{expression}#m 
\PV{expression}#m
\Pmqty{matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4}#m
\Pr(expression)#m
\Probability#*m
\Res[expression]#m
\Re{expression}#m
\Residue#*m
\Tr#m
\Trace#*m
\abs*{expression}#*m
\abs{expression}#m
\absolutevalue{expression}#*m
\acomm*{expression1}{expression2}#*m
\acomm{expression1}{expression2}#m
\acommutator{expression1}{expression2}#*m
\acos(expression)#m
\acos[power](expression)#m
\acosecant#*m
\acosine#*m
\acot(expression)#m
\acot[power](expression)#m 
\acotangent#*m
\acsc(expression)#m
\acsc[power](expression)#m
\admat{matrix element 1,matrix element 2,...}#*m
\anticommutator{expression1}{expression2}#*m
\antidiagonalmatrix{matrix element 1,matrix element 2,...}#*m
\arccos(expression)#m 
\arccos[power](expression)#m 
\arccosecant#*m 
\arccosine#*m
\arccot(expression)#m 
\arccot[power](expression)#m 
\arccotangent#*m 
\arccsc(expression)#m
\arccsc[power](expression)#m
\arcsec(expression)#m 
\arcsec[power](expression)#m
\arcsecant#*m 
\arcsin(expression)#m 
\arcsin[power](expression)#m  
\arcsine#*m 
\arctan(expression)#m
\arctan[power](expression)#m
\arctangent#*m 
\argclose
\argclose*
\argopen
\argopen*
\asec(expression)#m
\asec[power](expression)#m
\asecant#*m
\asin(expression)#m
\asin[power](expression)#m 
\asine#*m
\atan(expression)#m
\atan[power](expression)#m
\atangent#*m
\bmqty{matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4}#m
\bqty{expression}#m
\bra*{expression}#*m
\bra*{expression1}\ket*{expression2}#*m
\bra*{expression1}\ket{expression2}#*m
\bra{expression}#m
\bra{expression1}\ket*{expression2}#*m
\bra{expression1}\ket{expression2}#*m
\braces{ldelim}{rdelim}{expression}#*m
\braket*{expression1}{expression2}#*m
\braket{expression1}#*m
\braket{expression1}{expression2}#m
\colcount#*
\comm*{expression1}{expression2}#*m
\comm{expression1}{expression2}#m
\commutator{expression1}{expression2}#*m
\cos(expression)#m
\cos[power](expression)#m 
\cosecant#*m 
\cosh(expression)#m 
\cosh[power](expression)#m 
\cosine#*m 
\cot(expression)#m
\cot[power](expression)#m 
\cotangent#*m 
\coth(expression)#m 
\coth[power](expression)#m 
\cp#*m
\cross#m
\crossproduct#*m
\csc(expression)#m
\csc[power](expression)#m
\csch(expression)#m
\csch[power](expression)#m
\curl#*m
\curl(expression)#m
\curl*(expression)#*m
\curl*[expression]#*m
\curl[expression]#m
\curl{expression}#m
\dd#*m
\dd(expression)#m
\dd[power]{expression}#m
\dd{expression}#m
\derivative{function}{expression}#m 
\det(expression)#m
\determinant#*m
\diagonalmatrix{matrix element 1,matrix element 2,...}#*m
\differential#*m
\div#*m
\div(expression)#m
\div*(expression)#*m
\div*[expression]#*m
\div[expression]#m
\div{expression}#m
\divergence#*m
\divergence{expression}#*m
\divisionsymbol#m
\dmat{matrix element 1,matrix element 2,...}#*m
\dotproduct#*m
\dv*{function}{expression}#m
\dv[power]{function}{expression}#m
\dv{expression}#m
\dv{expression1}(expression2)#m
\dv{function}{expression}#m
\dyad*{expression1}{expression2}#*m
\dyad{expression}#*m
\dyad{expression1}{expression2}#m
\erf(expression)#m
\ev**{expression1}{expression2}#m
\ev*{expression1}{expression2}#m
\ev{expression}#m
\ev{expression1}{expression2}#m
\eval(expression|_{limit1}^{limit2}#m
\eval*(expression|_{limit1}^{limit2}#*m
\eval*[expression|_{limit1}^{limit2}#*m
\eval*{expression}_{limit1}^{limit2}#*m
\eval[expression|_{limit1}^{limit2}#m
\eval{expression}_{limit1}^{limit2}#m
\evaluated{expression}_{limit1}^{limit2}#*m
\exp(expression)#m
\expectationvalue{expression1}{expression2}#*m
\exponential#*m
\expval*{expression1}{expression2}#*m
\expval{expression}#m
\expval{expression1}{expression2}#*m
\fbraces{ldelim}{rdelim}{symbol}{expression}#*m
\fderivative{function}{expression}#*m
\fdv*{function}{expression}#m
\fdv{expression}#m
\fdv{expression}(function)#m
\fdv{function}{expression}#m
\flatfrac{expression1}(expression2)#m
\functionalderivative{function}{expression}#*m
\grad#*m
\grad(expression)#m
\grad*(expression)#*m
\grad*[expression]#*m
\grad[expression]#m
\grad{expression}#m
\gradient#*m
\gradient{expression}#*m
\homework#*
\hypcosecant#*m
\hypcosine#*m 
\hypcotangent#*m 
\hypsecant#*m 
\hypsine#*m 
\hyptangent#*m 
\identitymatrix{n}#*m
\imaginary#m
\imat{n}#*m
\innerproduct{expression1}{expression2}#*m
\ip*{expression1}{expression2}#m
\ip{expression1}{expression2}#m
\ket*{expression}#*m
\ket{expression}#m
\ketbra*{expression1}{expression2}#*m
\ketbra{expression1}{expression2}#*m
\laplacian#*m
\laplacian(expression)#m
\laplacian*(expression)#*m
\laplacian*[expression]#*m
\laplacian[expression]#m
\laplacian{expression}#m
\ln(expression)#m
\log(expression)#m
\logarithm#*m
\lparen#*
\matrixdeterminant{matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element}#*m
\matrixel*{expression1}{expression2}{expression3}#*m
\matrixel{expression1}{expression2}{expression3}#*m
\matrixelement*{expression1}{expression2}{expression3}#*m
\matrixelement{expression1}{expression2}{expression3}#*m
\matrixquantity(matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4)#*m
\matrixquantity{matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4}#*m
\matrixtoks#*
\mdet{matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element}#m
\mel**{expression1}{expression2}{expression3}#m
\mel*{expression1}{expression2}{expression3}#m
\mel{expression1}{expression2}{expression3}#m
\mqty(\admat{matrix element 1,matrix element 2,matrix element 3,...})#m
\mqty(\antidiagonalmatrix{matrix element 1,matrix element 2,matrix element 3,...})#*m
\mqty(\diagonalmatrix{matrix element 1,matrix element 2,matrix element 3,...})#*m
\mqty(\dmat[matrix element]{matrix element 1,matrix element 2,matrix element 3,...})#m
\mqty(\dmat{matrix element 1,matrix element 2,matrix element 3,...})#m
\mqty(\identitymatrix{number})#*m
\mqty(\imat{number})#m
\mqty(\paulimatrix{n})#*m
\mqty(\pmat{n})#m
\mqty(\xmat*{matrix element star for element indices }{n}{m})#m
\mqty(\xmat{matrix element}{n}{m})#m
\mqty(\xmatrix{matrix element}{n}{m})#*m
\mqty(\zeromatrix{n}{m})#*m
\mqty(\zmat{n}{m})#m
\mqty(matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4)#*m
\mqty*(matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4)#*m
\mqty[matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4]#*m
\mqty{matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4}#*m
\mqty|matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4|#*m
\naturallogarithm#*m
\norm*{expression}#*m
\norm{expression}#m
\op*{expression1}{expression2}#*m
\op{expression1}{expression2}#*m
\opbraces{operator}(expression)#*m
\order*{expression}#*m
\order{expression}#m
\ordersymbol#*m
\outerproduct{expression1}{expression2}#*m
\partialderivative{function}{expression}#*m
\paulimatrix{n}#*m
\paulixmatrix#*
\pauliymatrix#*
\paulizmatrix#*
\pb*{expression1}{expression2}#*m
\pb{expression1}{expression2}#*m
\pderivative{expression}#*m
\pdv*{f}{x}#m
\pdv[power]{function}{expression}#m
\pdv{expression}#m
\pdv{f}{x}{y}#m
\pdv{function}{expression}#m
\pmat{n}#*m
\pmqty{matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4}#m
\poissonbracket{expression1}{expression2}#*m
\pqty{expression}#m
\principalvalue#*m
\principalvalue{expression}#*m
\pv{expression}#m
\qall#m
\qall*#m
\qand#m
\qand*#m
\qas#m
\qas*#m
\qassume#m
\qassume*#m
\qc{word or phrase}#m
\qcc#m
\qcc*#m
\qcomma{word or phrase}#*m
\qelse#m
\qelse*#m
\qeven#m
\qeven*#m
\qfor#m
\qfor*#m
\qgiven#m
\qgiven*#m
\qif#m
\qif*#m
\qin#m
\qin*#m
\qinteger#m
\qinteger*#m
\qlet#m
\qlet*#m
\qodd#m
\qodd*#m
\qor#m
\qor*#m
\qotherwise#m
\qotherwise*#m
\qq*{word or phrase}#m
\qq{word or phrase}#m
\qqtext*{text}#*
\qqtext{text}#*
\qsince#m
\qsince*#m
\qthen#m
\qthen*#m
\qty(expression)#*m
\qty[expression]#*m
\qty{expression}#*m
\qty|expression|#*m
\quantity#*m
\qunless#m
\qunless*#m
\qusing#m
\qusing*#m
\rank#m
\real#m
\rowcount#*
\rparen#*
\sbmqty{matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4}#m
\sec(expression)#m 
\sec[power](expression)#m 
\secant#*m 
\sech(expression)#m 
\sech[power](expression)#m 
\sin(expression)#m
\sin[power](expression)#m 
\sine#*m 
\sinh(expression)#m
\sinh[power](expression)#m  
\smallmatrixdeterminant{matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4}#*m
\smallmatrixquantity{matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4}#*m
\smdet{matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element}#m
\smqty({matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4})#*m
\smqty*({matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4})#*m
\smqty[{matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4}]#*m
\smqty{matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4}#*m
\smqty|{matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4}|#*m
\sPmqty{matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4}#m
\spmqty{matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4}#m
\svmqty{matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4}#m
\tan(expression)#m 
\tan[power](expression)#m 
\tangent#*m 
\tanh(expression)#m 
\tanh[power](expression)#m   
\tr#m 
\tr(expression)#m
\trace#*m
\trigbraces{operator}(expression)#*m
\trigopt#*
\va*{expression}#m
\va{expression}#m
\var(expression)#m
\var{expression}#m
\varE#*m
\variation{expression}#*m
\vb*{expression}#m
\vb{expression}#m
\vdot#m
\vectorarrow{expression}#*m
\vectorbold{expression}#*m
\vectorunit{expression}#*m
\vev{expression}#*m
\vmqty{matrix element 1 & matrix element 2  \\ matrix element 3 & matrix element 4}#m
\vnabla#*m
\vqty{expression}#m
\vu*{expression}#m
\vu{expression}#m
\xmat{matrix element}{n}{m}#*m
\xmatrix{matrix element}{n}{m}#*m
\zeromatrix{n}{m}#*m
\zmat{n}{m}#*m
