# lisp-on-tex package
# Matthew Bertucci 2026/08/04 for v2.2

#include:xkeyval

#keyvals:\usepackage/lisp-on-tex#c
noGC
markGC
GCopt={%<options%>}
#endkeyvals

\lispinterp{LISP code}

\addassoc{arg1}{arg2}{arg3}#S
\lispeval{arg1}{arg2}#S

# from lisp-arith.sty
\+
\*
\<
\>
\geq
\isZeroQ
\leq
\max
\min
\mod
\negativeQ
\positiveQ

# from lisp-string.sty
\concat
\expand
\fgets
\group
\immediatewrite#S
\intTOstring
\stringTOint
\ungroup

# from lisp-latexutil.sty
\message
\readLaTeXCounter

# from lisp-prim.sty
\apply
\begin
\booleanQ
\callOCC
\car
\cdr
\cons
\define
\define{cmd}#Sd
\defineM
\defineM{cmd}#Sd
\defmacro
\eval
\lambda
\lambda(cmd)#Sd
\length
\lispif
\list
\macroexpand
\pairQ
\print
\quote
\read
\setB
\stdprint
\texprint

# from lisp-util.sty
\and
\atomQ
\closureQ
\envfuncQ#S
\funcQ
\let
\letM
\letrec
\listQ
\macroQ
\map
\not
\nth
\or
\procedureQ

