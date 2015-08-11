# diagxy package - Michael Barr's commutative-diagram package
# freyj 04/04/2007
# version 2: freyj 7/10/2007
#-----------------
# delimiters
\bfig
\efig
# in-line macros
\to/{sh}/^{L}_{L}
\mon^{L}_{L}
\epi^{L}_{L}
\toleft^{L}_{L}
\monleft^{L}_{L}
\epileft^{L}_{L}
# diagram macros
\place({x},{y})[{item}]
\twoar({dx},{dy})
\morphism({x},{y})|{p}|/{sh}/<{dx},{dy}>[{N}`{N};{L}]
\square({x},{y})|{p}{p}{p}{p}|/{sh}`{sh}`{sh}`{sh}/<{dx},{dy}>[{N}`{N}`{N}`{N};{L}`{L}`{L}`{L}]
\hsquares({x},{y})|{p}{p}{p}{p}{p}{p}{p}|/{sh}`{sh}`{sh}`{sh}`{sh}`{sh}`{sh}/<{dx},{dx},{dy}>[{N}`{N}`{N}`{N}`{N}`{N};{L}`{L}`{L}`{L}`{L}`{L}`{L}]
\vsquares({x},{y})|{p}{p}{p}{p}{p}{p}{p}|/{sh}`{sh}`{sh}`{sh}`{sh}`{sh}`{sh}/<{dx},{dy},{dy}>[{N}`{N}`{N}`{N}`{N}`{N};{L}`{L}`{L}`{L}`{L}`{L}`{L}]
\ptriangle({x},{y})|{p}{p}{p}|/{sh}`{sh}`{sh}/<{dx},{dy}>[{N}`{N}`{N};{L}`{L}`{L}]
\qtriangle({x},{y})|{p}{p}{p}|/{sh}`{sh}`{sh}/<{dx},{dy}>[{N}`{N}`{N};{L}`{L}`{L}]
\dtriangle({x},{y})|{p}{p}{p}|/{sh}`{sh}`{sh}/<{dx},{dy}>[{N}`{N}`{N};{L}`{L}`{L}]
\btriangle({x},{y})|{p}{p}{p}|/{sh}`{sh}`{sh}/<{dx},{dy}>[{N}`{N}`{N};{L}`{L}`{L}]
\Atriangle({x},{y})|{p}{p}{p}|/{sh}`{sh}`{sh}/<{dx},{dy}>[{N}`{N}`{N};{L}`{L}`{L}]
\Vtriangle({x},{y})|{p}{p}{p}|/{sh}`{sh}`{sh}/<{dx},{dy}>[{N}`{N}`{N};{L}`{L}`{L}]
\Ctriangle({x},{y})|{p}{p}{p}|/{sh}`{sh}`{sh}/<{dx},{dy}>[{N}`{N}`{N};{L}`{L}`{L}]
\Dtriangle({x},{y})|{p}{p}{p}|/{sh}`{sh}`{sh}/<{dx},{dy}>[{N}`{N}`{N};{L}`{L}`{L}]
\Atrianglepair({x},{y})|{p}{p}{p}{p}{p}|/{sh}`{sh}`{sh}`{sh}`{sh}/<{dx},{dy}>[{N}`{N}`{N}`{N};{L}`{L}`{L}`{L}`{L}]
\Vtrianglepair({x},{y})|{p}{p}{p}{p}{p}|/{sh}`{sh}`{sh}`{sh}`{sh}/<{dx},{dy}>[{N}`{N}`{N}`{N};{L}`{L}`{L}`{L}`{L}]
\Ctrianglepair({x},{y})|{p}{p}{p}{p}{p}|/{sh}`{sh}`{sh}`{sh}`{sh}/<{dx},{dy}>[{N}`{N}`{N}`{N};{L}`{L}`{L}`{L}`{L}]
\Dtrianglepair({x},{y})|{p}{p}{p}{p}{p}|/{sh}`{sh}`{sh}`{sh}`{sh}/<{dx},{dy}>[{N}`{N}`{N}`{N};{L}`{L}`{L}`{L}`{L}]
\pullback({x},{y})|{p}{p}{p}{p}|/{sh}`{sh}`{sh}`{sh}/<{dx}`{dy}>[{N}`{N}`{N}`{N};{L}`{L}`{L}`{L}]|{p}{p}{p}|/{sh}`{sh}`{sh}/<{dx},{dy}>[{N};{L}`{L}`{L}]
\Square({x},{y})|{p}{p}{p}{p}|/{sh}`{sh}`{sh}`{sh}/<{dy}>[{N}`{N}`{N}`{N};{L}`{L}`{L}`{L}] # width automatically determined
\hSquares({x},{y})|{p}{p}{p}{p}{p}{p}{p}|/{sh}`{sh}`{sh}`{sh}`{sh}`{sh}`{sh}/<{dy}>[{N}`{N}`{N}`{N}`{N}`{N};{L}`{L}`{L}`{L}`{L}`{L}`{L}] # width automatically determined
\vSquares({x},{y})|{p}{p}{p}{p}{p}{p}{p}|/{sh}`{sh}`{sh}`{sh}`{sh}`{sh}`{sh}/<{dy},{dy}>[{N}`{N}`{N}`{N}`{N}`{N};{L}`{L}`{L}`{L}`{L}`{L}`{L}] # width automatically determined
\cube({x},{y})|{p}{p}{p}{p}|/{sh}`{sh}`{sh}`{sh}/<{dx},{dy}>[{N}`{N}`{N}`{N};{L}`{L}`{L}`{L}]({x},{y})|{p}{p}{p}{p}|/{sh}`{sh}`{sh}`{sh}/<{dx},{dy}>[{N}`{N}`{N}`{N};{L}`{L}`{L}`{L}]|{p}{p}{p}{p}|/{sh}`{sh}`{sh}`{sh}/[{L}`{L}`{L}`{L}]
\node {id}({x},{y})[{N}]
\arrow|{p}|/{sh}/[{id}`{id};{L}]
\Loop({x},{y}){N}({dirstart},{dirend})_{L}
\iiixiii({x},{y})|{p}{p}{p}{p}{p}{p}{p}{p}{p}{p}{p}{p}|/{sh}`{sh}`{sh}`{sh}`{sh}`{sh}`{sh}`{sh}`{sh}`{sh}`{sh}`{sh}/<{dx},{dy}>{zeroes}<{dx},{dy}>[{N}`{N}`{N}`{N}`{N}`{N}`{N}`{N}`{N};{L}`{L}`{L}`{L}`{L}`{L}`{L}`{L}`{L}`{L}`{L}`{L}]
\iiixii({x},{y})|{p}{p}{p}{p}{p}{p}{p}|/{sh}`{sh}`{sh}`{sh}`{sh}`{sh}`{sh}/<{dx},{dy}>{zeroes}<{dx},{dy}>[{N}`{N}`{N}`{N}`{N}`{N};{L}`{L}`{L}`{L}`{L}`{L}`{L}]
