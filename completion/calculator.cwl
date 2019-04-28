# calculator package
# https://ctan.org/pkg/calculator
#
# Created by @ppizarror
# https://github.com/ppizarror/calculator-cwl
# date: Sun 28 Apr

# --------------------------------------------
# 1. Predefined numbers
# --------------------------------------------
\numberPI#n
\numberTHREEHALFPI#n
\numberQUARTERPI#n
\numberSIXTHPI#n
\numberE#n
\numberETWO#n
\numberLOGTEN#n
\numberGOLD#n
\numberSQRTTWO#n
\numberSQRTFIVE#n
\numberCOSXXX#n
\numberHALFPI#n
\numberTHIRDPI#n
\numberFIFTHPI#n
\numberTWOPI#n
\numberINVE#n
\numberINVETWO#n
\numberINVGOLD#n
\numberSQRTTHREE#n
\numberCOSXLV#n

# --------------------------------------------
# 2. Operations with numbers
# --------------------------------------------

# Assignments and comparisons
\COPY{num}{cmd}#d
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

\TRUNCATE[n]{num}{cmd}#d
\ROUND[n]{num}{cmd}#d

# Integers
\INTEGERDIVISION{num1}{num2}{cmd1}{cmd2}#d
\INTEGERQUOTIENT{num1}{num2}{cmd}#d
\MODULO{num1}{num2}{cmd}#d

\GCD{num1}{num2}{cmd}#d
\LCM{num1}{num2}{cmd}#d

\FRACTIONSIMPLIFY{num1}{num2}{cmd1}{cmd2}#d

# Elementary functions
\SQUAREROOT{num}{cmd}#d

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
\VECTORCOPY(x,y,z)(cmd1,cmd2,cmd3)#d
\VECTORADD(x1,y1,z1)(x2,y2,z2)(cmd1,cmd2,cmd3)#d
\VECTORSUB(x1,y1,z1)(x2,y2,z2)(cmd1,cmd2,cmd3)#d
\SCALARVECTORPRODUCT{num}(x,y,z)(cmd1,cmd2,cmd3)#d
\SCALARPRODUCT(x1,y1,z1)(x2,y2,z2){cmd1,cmd2,cmd3}#d
\DOTPRODUCT(x1,y1,z1)(x2,y2,z2){cmd1,cmd2,cmd3}#d
\VECTORNORM(x,y,z){cmd}#d
\VECTORPRODUCT(x1,y1,z1)(x2,y2,z2)(cmd1,cmd2,cmd3)#d
\CROSSPRODUCT(x1,y1,z1)(x2,y2,z2)(cmd1,cmd2,cmd3)#d
\UNITVECTOR(x,y,z)(cmd1,cmd2,cmd3)#d
\VECTORABSVALUE(x,y,z)(cmd1,cmd2,cmd3)#d
\TWOVECTORSANGLE(x1,y1,z1)(x2,y2,z2){cmd}#d

# Matrix Operations
\MATRIXCOPY(a11...a33)(cmd11...cmd33)#d
\TRANSPOSEMATRIX(a11...a33)(cmd11...cmd33)#d
\MATRIXADD(a11...a33)(b11...b33)(cmd11...cmd33)#d
\MATRIXSUB(a11...a33)(b11...b33)(cmd11...cmd33)#d
\SCALARMATRIXPRODUCT{num}(a11...a33)(cmd11...cmd33)#d
\MATRIXVECTORPRODUCT(a11...a33)(x,y,z)(cmd1,cmd2,cmd3)#d
\MATRIXPRODUCT(a11...a33)(b11...b33)(cmd11...cmd33)#d
\DETERMINANT{a11...a33){cmd}#d
\INVERSEMATRIX(a11...a33)(cmd11...cmd33)#d
\MATRIXABSVALUE(a11...a33)(cmd11...cmd33)#d
\SOLVELINEARSYSTEM(a11...a33)(b1,b2,b3)(cmd1,cmd2,cmd3)#d