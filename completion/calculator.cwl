# calculator package
# https://ctan.org/pkg/calculator
#
# Created by @ppizarror
# https://github.com/ppizarror/calculator-cwl
# date: Sun 28 Apr

# Matthew Bertucci updated 3/31/2022 for v2.0

# --------------------------------------------
# 1. Predefined numbers
# --------------------------------------------
\numberPI
\numberTHREEHALFPI
\numberQUARTERPI
\numberSIXTHPI
\numberE
\numberETWO
\numberLOGTEN
\numberGOLD
\numberSQRTTWO
\numberSQRTFIVE
\numberCOSXXX
\numberHALFPI
\numberTHIRDPI
\numberFIFTHPI
\numberTWOPI
\numberINVE
\numberINVETWO
\numberINVGOLD
\numberSQRTTHREE
\numberCOSXLV

# --------------------------------------------
# 2. Operations with numbers
# --------------------------------------------

# Assignments and comparisons
\COPY{num}{cmd}#d
\GLOBALCOPY{num}{cmd}#*d
\MAX{num1}{num2}{cmd}#d
\MIN{num1}{num2}{cmd}#d

# Real arithmetic
\ADD{num1}{num2}{cmd}#d
\SUBTRACT{num1}{num2}{cmd}#d
\MULTIPLY{num1}{num2}{cmd}#d
\DIVIDE{num1}{num2}{cmd}#d

\SQUARE{num}{cmd}#d
\CUBE{num}{cmd}#d
\POWER{num}{exp}{cmd}#d

\ABSVALUE{num}{cmd}#d
\INTEGERPART{num}{cmd}#d
\FLOOR{num}{cmd}#d
\FRACTIONALPART{num}{cmd}#d

\TRUNCATE{num}{cmd}#d
\TRUNCATE[n]{num}{cmd}#d
\ROUND{num}{cmd}#d
\ROUND[n]{num}{cmd}#d

# Integers
\INTEGERDIVISION{num1}{num2}{cmd1%cmd}{cmd2%cmd}#d
\INTEGERQUOTIENT{num1}{num2}{cmd}#d
\MODULO{num1}{num2}{cmd}#d

\GCD{num1}{num2}{cmd}#d
\LCM{num1}{num2}{cmd}#d

\FRACTIONSIMPLIFY{num1}{num2}{cmd1%cmd}{cmd2%cmd}#d

# Elementary functions
\SQUAREROOT{num}{cmd}#d
\SQRT{num}{cmd}#*d

\EXP{num}{cmd}#d
\EXP[num1]{num2}{cmd}#d
\LOG{num}{cmd}#d
\LOG[num1]{num2}{cmd}#d

\SIN{num}{cmd}#d
\COS{num}{cmd}#d
\TAN{num}{cmd}#d
\COT{num}{cmd}#d
\DEGREESSIN{num}{cmd}#d
\DEGREESCOS{num}{cmd}#d
\DEGREESTAN{num}{cmd}#d
\DEGREESCOT{num}{cmd}#d
\DEGREESSIN[degrees]{num}{cmd}#d
\DEGREESCOS[degrees]{num}{cmd}#d
\DEGREESTAN[degrees]{num}{cmd}#d
\DEGREESCOT[degrees]{num}{cmd}#d
\DEGtoRAD{num}{cmd}#d
\RADtoDEG{num}{cmd}#d
\REDUCERADIANSANGLE{num}{cmd}#d
\REDUCEDEGREESANGLE{num}{cmd}#d

\SINH{num}{cmd}#d
\COSH{num}{cmd}#d
\TANH{num}{cmd}#d
\COTH{num}{cmd}#d

\ARCSIN{num}{cmd}#d
\ARCCOS{num}{cmd}#d
\ARCTAN{num}{cmd}#d
\ARCCOT{num}{cmd}#d

\ARSINH{num}{cmd}#d
\ARCOSH{num}{cmd}#d
\ARTANH{num}{cmd}#d
\ARCOTH{num}{cmd}#d

# --------------------------------------------
# 3. Operations with lengths
# --------------------------------------------
\LENGTHDIVIDE{length1}{length2}{cmd}#d
\LENGTHADD{length1}{length2}{cmd}#d
\LENGTHSUBTRACT{length1}{length2}{cmd}#d

# --------------------------------------------
# 4. Matrix arithmetic
# --------------------------------------------

# Vector Operations
\VECTORSIZE(x,y,z){cmd}#*d
\VECTORCOPY(x,y,z)(cmd1,cmd2,cmd3%cmd)#d
\VECTORGLOBALCOPY(x,y,z)(cmd1,cmd2,cmd3%cmd)#*d
\VECTORADD(x1,y1,z1)(x2,y2,z2)(cmd1,cmd2,cmd3%cmd)#d
\VECTORSUB(x1,y1,z1)(x2,y2,z2)(cmd1,cmd2,cmd3%cmd)#d
\SCALARVECTORPRODUCT{num}(x,y,z)(cmd1,cmd2,cmd3%cmd)#d
\SCALARPRODUCT(x1,y1,z1)(x2,y2,z2){cmd}#d
\DOTPRODUCT(x1,y1,z1)(x2,y2,z2){cmd}#d
\VECTORNORM(x,y,z){cmd}#d
\VECTORPRODUCT(x1,y1,z1)(x2,y2,z2)(cmd1,cmd2,cmd3%cmd)#d
\CROSSPRODUCT(x1,y1,z1)(x2,y2,z2)(cmd1,cmd2,cmd3%cmd)#d
\UNITVECTOR(x,y,z)(cmd1,cmd2,cmd3%cmd)#d
\VECTORABSVALUE(x,y,z)(cmd1,cmd2,cmd3%cmd)#d
\TWOVECTORSANGLE(x1,y1,z1)(x2,y2,z2){cmd}#d

# Matrix Operations
\MATRIXSIZE(a11...a33){cmd}#*d
\MATRIXCOPY(a11...a33)(cmd11...cmd33%cmd)#d
\MATRIXGLOBALCOPY(a11...a33)(cmd11...cmd33%cmd)#*d
\TRANSPOSEMATRIX(a11...a33)(cmd11...cmd33%cmd)#d
\MATRIXADD(a11...a33)(b11...b33)(cmd11...cmd33%cmd)#d
\MATRIXSUB(a11...a33)(b11...b33)(cmd11...cmd33%cmd)#d
\SCALARMATRIXPRODUCT{num}(a11...a33)(cmd11...cmd33%cmd)#d
\MATRIXVECTORPRODUCT(a11...a33)(x,y,z)(cmd1,cmd2,cmd3%cmd)#d
\VECTORMATRIXPRODUCT(x,y,z)(a11...a33)(cmd1,cmd2,cmd3%cmd)#*d
\MATRIXPRODUCT(a11...a33)(b11...b33)(cmd11...cmd33%cmd)#d
\DETERMINANT{a11...a33){cmd}#d
\INVERSEMATRIX(a11...a33)(cmd11...cmd33%cmd)#d
\MATRIXABSVALUE(a11...a33)(cmd11...cmd33%cmd)#d
\SOLVELINEARSYSTEM(a11...a33)(b1,b2,b3)(cmd1,cmd2,cmd3%cmd)#d
