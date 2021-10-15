# xlop package
# Matthew Bertucci 10/5/2021 for v0.28

\opset{options%keyvals}
\opadd{num1}{num2}
\opadd[options%keyvals]{num1}{num2}
\opmanyadd{%<num1%>}{%<num2%>}%<...{numN}%>
\opmanyadd[%<options%>]{%<num1%>}{%<num2%>}%<...{numN}%>
\opsub{num1}{num2}
\opsub[options%keyvals]{num1}{num2}
\opmul{num1}{num2}
\opmul[options%keyvals]{num1}{num2}
\opdiv{num1}{num2}
\opdiv[options%keyvals]{num1}{num2}
\opidiv{num1}{num2}
\opidiv[options%keyvals]{num1}{num2}

#keyvals:\opset#c,\opadd#c,\opmanyadd#c,\opsub#c,\opmul#c,\opdiv#c,\opidiv#c,\opgfsqrt#c
afterperiodsymbol=
equalsymbol=
approxsymbol=
decimalsepsymbol=
addsymbol=
subsymbol=
mulsymbol=
divsymbol=
voperation=#top,center,bottom
voperator=#top,center,bottom
deletezero#true,false
style=#display,text
parenthesisnegative=#none,all,last
lineheight=##L
columnwidth=##L
decimalsepwidth=##L
hrulewidth=##L
vrulewidth=##L
decimalsepoffset=##L
operandstyle=%<style cmds%>
operandstyle.%<num%>=%<style cmds%>
resultstyle=%<style cmds%>
resultstyle.%<num%>=%<style cmds%>
remainderstyle=%<style cmds%>
remainderstyle.%<num%>=%<style cmds%>
intermediarystyle=%<style cmds%>
intermediarystyle.%<num%>=%<style cmds%>
carrystyle=%<style cmds%>
carrystyle.%<num%>=%<style cmds%>
#endkeyvals

\opcolumnwidth#*
\oplineheight#*

#keyvals:\opadd#c
carryadd#true,false
lastcarry#true,false
#endkeyvals

#keyvals:\opmanyadd#c
vmanyoperator=#top,center,bottom,Top,Center,Bottom
#endkeyvals

#keyvals:\opsub#c
carrysub#true,false
lastcarry#true,false
offsetcarry=
behaviorsub=#silent,warning,error
#endkeyvals

#keyvals:\opmul#c
displayshiftintermediary=#shift,all,none
shiftintermediarysymbol=
displayintermediary=#none,all,nonzero,None
hfactor=#right,decimal
#endkeyvals

#keyvals:\opdiv#c,\opidiv#c
maxdivstep=%<integer%>
safedivstep=%<integer%>
period#true,false
vruleperiod=
displayintermediary=#none,all,nonzero,None
dividendbridge#true,false
shiftdecimalsep=#both,divisor,none
strikedecimalsepsymbol=
#endkeyvals

\opadd*{num1}{num2}{variable}
\opsub*{num1}{num2}{variable}
\opmul*{num1}{num2}{variable}
\opdiv*{num1}{num2}{quotient var}{remainder var}
\opdiv*[options%keyvals]{num1}{num2}{quotient var}{remainder var}
\opidiv*{num1}{num2}{quotient var}{remainder var}

#keyvals:\opdiv*#c,\opexpr#c
maxdivstep=%<integer%>
safedivstep=%<integer%>
period#true,false
#endkeyvals

\opcopy{number}{variable}
\opprint{arg}
\opdisplay{style%keyvals}{number}
\opdisplay[specs]{style}{number}
\oplput(x,y){text}
\oprput(x,y){text}
\ophline(x,y){length}
\opvline(x,y){length}
\opexport{number}{cmd}#d
\opwidth{number}{variable}
\opintegerwidth{number}{variable}
\opdecimalwidth{number}{variable}
\opunzero{number}
\opinteger{number}{variable}
\opdecimal{number}{variable}
\opgetdigit{number}{index}{variable}
\opsetdigit{number}{index}{variable}
\opgetintegerdigit{number}{index}{variable}
\opsetintegerdigit{number}{index}{variable}
\opgetdecimaldigit{number}{index}{variable}
\opsetdecimaldigit{number}{index}{variable}
\opcmp{num1}{num2}
\ifopgt
\ifopge
\ifople
\ifoplt
\ifopeq
\ifopneq

\opgcd{num1}{num2}{variable}
\opdivperiod{num1}{num2}{variable}
\opcastingoutnines{number}{variable}
\opcastingoutelevens{number}{variable}
\oppower{number}{power}{variable}
\opfloor{number}{approx rank}{variable}
\opceil{number}{approx rank}{variable}
\opround{number}{approx rank}{variable}

\opsqrt{number}{variable}
\opsqrt[options%keyvals]{number}{variable}
\opgfsqrt{number}
\opgfsqrt[options%keyvals]{number}

#keyvals:\opsqrt#c,\opgfsqrt#c
maxdivstep=%<integer%>
#endkeyvals

\opexpr{expression}{variable}
\opexpr[options%keyvals]{expression}{variable}
\opabs{number}{variable}
\opneg{number}{variable}