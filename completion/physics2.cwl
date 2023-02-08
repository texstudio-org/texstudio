# physics2 package
# Matthew Bertucci 2023/02/07 for v0.1.1

#include:keyval

\usephysicsmodule{modules%keyvals}
\usephysicsmodule[options]{modules%keyvals}

#keyvals:\usephysicsmodule
ab.braket
ab.legacy
ab
bm-um.legacy
braket
diagmat
doubleprod
nabla.legacy
op.legacy
qtext.legacy
xmat
#endkeyvals

## no good way to conditionally load module commands so all just listed here

## from phy-common.sty (automatically loaded)
\delopen%<⟨delim⟩%>#m
\delclose%<⟨delim⟩%>#m
\biggg%<⟨delim⟩%>#m
\Biggg%<⟨delim⟩%>#m
\bigggl%<⟨delim⟩%>#m
\bigggm%<⟨delim⟩%>#m
\bigggr%<⟨delim⟩%>#m
\Bigggl%<⟨delim⟩%>#m
\Bigggm%<⟨delim⟩%>#m
\Bigggr%<⟨delim⟩%>#m

## from phy-ab.sty ('ab' module)
\ab%<⟨ldelim⟩ arg ⟨rdelim⟩%>#m
\ab*%<⟨ldelim⟩ arg ⟨rdelim⟩%>#m
\pab{arg}#m
\pab*{arg}#m
\bab{arg}#m
\bab*{arg}#m
\Bab{arg}#m
\Bab*{arg}#m
\vab{arg}#m
\vab*{arg}#m
\aab{arg}#m
\aab*{arg}#m
\Vab{arg}#m
\Vab*{arg}#m

## from phy-ab.braket.sty ('ab.braket' module)
# loads ab module
\bra<%<subformula%>|#m
\bra*<%<subformula%>|#m
\ket|%<subformula%>>#m
\ket*|%<subformula%>>#m
\braket<%<subformula%>|#m
\braket*<%<subformula%>|#m
\ketbra|%<subformula1%>>%<optional%><%<subformula2%>|#m
\ketbra*|%<subformula1%>>%<optional%><%<subformula2%>|#m

## from phy-braket.sty ('braket' module)
# loads ab module
##### note: conflicts with phy-ab.braket so excluded until cwl module localization works
## \bra{subformula}
## \bra*{subformula}
## \bra[size%keyvals]{subformula}
## \ket{subformula}
## \ket*{subformula}
## \ket[size%keyvals]{subformula}
## \braket{subformula1}{subformula2}
## \braket[size%keyvals]{subformula1}{subformula2}
## \braket[1%<,size%>%keyvals]{%<subformula%>}
## \braket[3%<,size%>%keyvals]{%<subformula1%>}{%<subformula2%>}{%<subformula3%>}
## \braket*{subformula1}{subformula2}
## \braket*[1]{%<subformula%>}
## \braket*[3]{%<subformula1%>}{%<subformula2%>}{%<subformula3%>}
## \ketbra{subformula1}{subformula2}
## \ketbra{subformula1}[optional]{subformula2}
## \ketbra*{subformula1}{subformula2}
## \ketbra*{subformula1}[optional]{subformula2}
## \ketbra[size%keyvals]{subformula1}{subformula2}
## \ketbra[size%keyvals]{subformula1}[optional]{subformula2}
##
## #keyvals:\bra,\ket,\braket,\ketbra
## big
## Big
## bigg
## Bigg
## biggg
## Biggg
## #endkeyvals
## 
## #keyvals:\braket
## 1
## 3
## #endkeyvals

## from phy-diagmat.sty ('diagmat' module)
# loads amsmath package
#include:amsmath
\diagmat{entry1,entry2,...}#m
\diagmat[empty=%<entry%>]{%<entry1,entry2,...%>}#m
\pdiagmat{entry1,entry2,...}#m
\pdiagmat[empty=%<entry%>]{%<entry1,entry2,...%>}#m
\bdiagmat{entry1,entry2,...}#m
\bdiagmat[empty=%<entry%>]{%<entry1,entry2,...%>}#m
\Bdiagmat{entry1,entry2,...}#m
\Bdiagmat[empty=%<entry%>]{%<entry1,entry2,...%>}#m
\vdiagmat{entry1,entry2,...}#m
\vdiagmat[empty=%<entry%>]{%<entry1,entry2,...%>}#m
\Vdiagmat{entry1,entry2,...}#m
\Vdiagmat[empty=%<entry%>]{%<entry1,entry2,...%>}#m

## from phy-doubleprod.sty ('doubleprod' module)
\doublecross#m
\doubledot#m

## from phy-xmat.sty ('xmat' module)
# loads amsmath package
\xmat{entry}{rows shown}{cols shown}
\xmat[options%keyvals]{entry}{rows shown}{cols shown}
\pxmat{entry}{rows shown}{cols shown}
\pxmat[options%keyvals]{entry}{rows shown}{cols shown}
\bxmat{entry}{rows shown}{cols shown}
\bxmat[options%keyvals]{entry}{rows shown}{cols shown}
\Bxmat{entry}{rows shown}{cols shown}
\Bxmat[options%keyvals]{entry}{rows shown}{cols shown}
\vxmat{entry}{rows shown}{cols shown}
\vxmat[options%keyvals]{entry}{rows shown}{cols shown}
\Vxmat{entry}{rows shown}{cols shown}
\Vxmat[options%keyvals]{entry}{rows shown}{cols shown}

#keyvals:\xmat,\pxmat,\bxmat,\Bxmat,\vxmat,\Vxmat
showtop=%<rows%>
showleft=%<columns%>
format=%<format code%>
#endkeyvals

### legacy modules (not recommended by package author, hence #*'s)

## from phy-ab.legacy.sty ('ab.legacy' module)
# loads ab module
\abs{arg}#*m
\abs*{arg}#*m
\abs[size]{arg}#*m
\norm{arg}#*m
\norm*{arg}#*m
\norm[size]{arg}#*m
\order{arg}#*m
\order*{arg}#*m
\order[size]{arg}#*m
\eval{arg}#*m
\eval[ldelim]{arg}#*m

## from phy-bm-um.legacy.sty ('bm-um.legacy' module)
\bm{letter}#*m

## from phy-nabla.legacy.sty ('nabla.legacy' module)
# loads ab module
# loads fixdif package
\grad#*m
\div#*m
\curl#*m
\laplacian#*m

## from phy-op.legacy.sty ('op.legacy' module)
\asin#*m
\acos#*m
\atan#*m
\acsc#*m
\asec#*m
\acot#*m
\Tr#*m
\tr#*m
\rank#*m
\erf#*m
\Res#*m
\res#*m
\PV#*m
\pv#*m
\Resymbol#S
\Imsymbol#S

## from phy-qtext.legacy.sty ('qtext.legacy' module)
# loads amstext package
\qqtext{text}#Sm
\qqtext*{text}#Sm
\qq{text}#*m
\qq*{text}#*m
\qcomma#Sm
\qc#*m
\qcc#*m
\qcc*#*m
\qif#*m
\qthen#*m
\qelse#*m
\qotherwise#*m
\qunless#*m
\qgive#*m
\qusing#*m
\qunless#*m
\qassume#*m
\qsince#*m
\qlet#*m
\qfor#*m
\qall#*m
\qeven#*m
\qodd#*m
\qinteger#*m
\qand#*m
\qor#*m
\qas#*m
\qin#*m