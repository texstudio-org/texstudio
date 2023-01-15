# pgfmath package
# muzimuzhi 7 Jul 2020, tikz-pgf 3.1.5b
# filetree updated 2023/01/15 for v3.1.10

#include:pgfrcs
#include:pgfkeys

# Dependency Tree:
# pgfmath.sty
# ├── pgfrcs.sty
# ├── pgfkeys.sty
# └── pgfmath.code.tex
#     ├── pgfkeys.code.tex (already loaded by pgfkeys.sty)
#     ├── pgfmathutil.code.tex
#     ├── pgfmathparser.code.tex
#     ├── pgfmathfunctions.code.tex
#     ├── pgfmathfunctions.basic.code.tex
#     ├── pgfmathfunctions.trigonometric.code.tex
#     ├── pgfmathfunctions.random.code.tex
#     ├── pgfmathfunctions.comparison.code.tex
#     ├── pgfmathfunctions.base.code.tex
#     ├── pgfmathfunctions.round.code.tex
#     ├── pgfmathfunctions.misc.code.tex
#     ├── pgfmathfunctions.integerarithmetics.code.tex
#     ├── pgfmathcalc.code.tex
#     └── pgfmathfloat.code.tex

\pgfmathloaded#S

# from pgfmathcalc.code.tex
\pgfmathsetlength{length register}{math expression}#*
\pgfmathaddtolength{length register}{math expression}#*
\pgfmathsetcount{count register}{math expression}#*
\pgfmathaddtocount{count register}{math expression}#*
\pgfmathsetcounter{counter}{math expression}#*
\pgfmathaddtocounter{counter}{math expression}#*
\pgfmathsetmacro{cmd}{math expression}#*d
\pgfmathsetlengthmacro{cmd}{math expression}#*d
\pgfmathtruncatemacro{cmd}{math expression}#*d

\pgfmathnewcounter{counter}#*
\pgfmathmakecounterglobal{counter}#*

\pgfmathanglebetweenpoints{point 1}{point 2}#*
\pgfmathanglebetweenlines{line 1 start}{line 1 end}{line 2 start}{line 2 end}#*
\pgfmathrotatepointaround{point}{rotate center}{degree}#*
\pgfmathreflectpointalongaxis{point}{point on axis}{axis angle}#*
\pgfmathpointintersectionoflineandarc{point 1}{point 2}{arc center}{start angle}{end angle}{radii}#*
\pgfmathangleonellipse{point on ellipse}{radii}#*

# from pgfmathutil.code.tex
\pgfmathincluded#*
\ifpgfmathcontinueloop#*
\pgfmathcontinuelooptrue#*
\pgfmathcontinueloopfalse#*
\pgfmathloop %<loop body%>\repeatpgfmathloop#*
\repeatpgfmathloop#*
\pgfmathbreakloop#*
\pgfmathreturn#*
\pgfmathcounter#*
\pgfmathsmuggle%<macro%>\endgroup#*

# from pgfmathparser.code.tex
\ifpgfmathfloat#*
\pgfmathfloattrue#*
\pgfmathfloatfalse#*
\ifpgfmathunitsdeclared#*
\pgfmathunitsdeclaredtrue#*
\pgfmathunitsdeclaredfalse#*
\ifpgfmathmathunitsdeclared#*
\pgfmathmathunitsdeclaredtrue#*
\pgfmathmathunitsdeclaredfalse#*
\ifpgfmathignoreunitscale#*
\pgfmathignoreunitscaletrue#*
\pgfmathignoreunitscalefalse#*
\pgfmathprint{real number}
\pgfmathparse{math expression}
\pgfmathqparse{math expression}#*
\pgfmathpostparse#*
\pgfmathscaleresult#*
\pgfmathsetresultunitscale{scale value}#*
\pgfmathresultunitscale#*
\pgfmathifexpression{math expression}{true}{false}#*
\pgfmathdeclareoperator{op}{op name}{arity}{type}{precedence}#*

# from pgfmathfunctions.code.tex
\pgfmathdeclarefunction{name}{num of args}{code}#*
\pgfmathdeclarefunction*{name}{num of args}{code}#*
\pgfmathredeclarefunction{name}{code}#*
\pgfmathnotifynewdeclarefunction{name}{num of args}{code}#*
\pgfmathdeclarepseudoconstant{name}{code}#*
\pgfmathredeclarepseudoconstant{name}{code}#*

# from pgfmathfunctions.basic.code.tex
\pgfmathadd{x}{y}#*
\pgfmathsubtract{x}{y}#*
\pgfmathneg{x}#*
\pgfmathmultiply{x}{y}#*
\pgfmathdivide{x}{y}#*
\pgfmathreciprocal{x}#*
\pgfmathdiv{x}#*
\pgfmathmod{x}{y}#*
\pgfmathMod{x}{y}#*
\pgfmathabs{x}#*
\pgfmathsign{x}#*
\pgfmathe#*
\pgfmathln{x}#*
\pgfmathlogten{x}#*
\pgfmathlogtwo{x}#*
\pgfmathexp{x}#*
\pgfmathsqrt{x}#*
\pgfmathpow{x}{power}#*
\pgfmathfactorial{x}#*

# from pgfmathfunctions.trigonometric.code.tex
\pgfmathpi#*
\pgfmathiftrigonometricusesdeg{true}{false}#*
\pgfmathradians{x in radians} # for compatibility with pgf 1.18 beta#*
\pgfmathdeg{x in radians}#*
\pgfmathrad{x in degrees}#*
\pgfmathsin{x in degrees}#*
\pgfmathcos{x in degrees}#*
\pgfmathsincos{num in degress}#*
\pgfmathtan{x in degrees}#*
\pgfmathcosec{x in degrees}#*
\pgfmathsec{x in degrees}#*
\pgfmathcot{x in degrees}#*
\pgfmathasin{x in degrees}#*
\pgfmathacos{x in degrees}#*
\pgfmathatan{x in degrees}#*
\pgfmathatantwo{y in degrees}{x in degrees}#*

# from pgfmathfunctions.random.code.tex
\pgfmathsetseed{integer}#*
\pgfmathgeneratepseudorandomnumber#*
\pgfmathrnd#*
\pgfmathrand#*
\pgfmathrandom{maximum int}#*
\pgfmathrandom{minimum int}{maximum int}#*
\pgfmathrandominteger{cmd}{minimum}{maximum}#*d
\pgfmathdeclarerandomlist{list name}{list of items}#*
\pgfmathrandomitem{cmd}{list name}#*d

# from pgfmathfunctions.comparison.code.tex
\pgfmathgreater{x}{y}#*
\pgfmathgreaterthan{x}{y}#*
\pgfmathless{x}{y}#*
\pgfmathlessthan{x}{y}#*
\pgfmathequal{x}{y}#*
\pgfmathequalto{x}{y}#*
\ifpgfmathcomparison#*
\pgfmathcomparisontrue#*
\pgfmathcomparisonfalse#*
\pgfmathapproxequalto{x}{y}#*
\pgfmathifthenelse{x}{true}{false}#*
\pgfmathnotequal{x}{y}#*
\pgfmathnotless{x}{y}#*
\pgfmathnotgreater{x}{y}#*
\pgfmathand{x}{y}#*
\pgfmathor{x}{y}#*
\pgfmathnot{x}#*
\pgfmathtrue#*
\pgfmathfalse#*

# from pgfmathfunctions.base.code.tex
\pgfmathbin{x in base 10}#*
\pgfmathhex{x in base 10}#*
\pgfmathHex{x in base 10}#*
\pgfmathoct{x in base 10}#*
\pgfmathbasetodec{cmd}{number}{base}#*d
\pgfmathdectobase{cmd}{number}{base}#*d
\pgfmathdectoBase{cmd}{number}{base}#*d
\pgfmathbasetobase{cmd}{number}{base1}{base2}#*d
\pgfmathbasetoBase{cmd}{number}{base1}{base2}#*d
\pgfmathsetbasenumberlength{integer}#*
\pgfmathtodigitlist{cmd}{number}#*d

# from pgfmathfunctions.round.code.tex
\pgfmathround{x}#*
\pgfmathfloor{x}#*
\pgfmathceil{x}#*
\pgfmathint{x}#*
\pgfmathfrac{x}#*
\pgfmathreal{x}#*

# from pgfmathfunctions.misc.code.tex
\pgfmathveclen{x coordinate}{y coordinate}#*
\pgfmathcosh{x in degree}#*
\pgfmathsinh{x in degree}#*
\pgfmathtanh{x in degree}#*
\pgfmathscientific{mantissa}{exponent}#*
\pgfmathwidth{"text"}#*
\pgfmathheight{"text"}#*
\pgfmathdepth{"text"}#*
\pgfmatharray{array}{index}#*
\pgfmathdim{array}#*
\pgfmathmax{num list}{num list}#*
\pgfmathmin{num list}{num list}#*
\pgfmathscalar{value}#*

# from pgfmathfunctions.integerarithmetics.code.tex
\pgfmathgcd{x}{y}#*
\pgfmathisprime{x}#*
\pgfmathisodd{x}#*
\pgfmathiseven{x}#*

# from pgfmathfloat.code.tex
\ifpgfmathfloatcomparison#*
\pgfmathfloatcomparisontrue#*
\pgfmathfloatcomparisonfalse#*
\ifpgfmathfloatroundhasperiod#*
\pgfmathfloatroundhasperiodtrue#*
\pgfmathfloatroundhasperiodfalse#*
\ifpgfmathprintnumberskipzeroperiod#*
\pgfmathprintnumberskipzeroperiodtrue#*
\pgfmathprintnumberskipzeroperiodfalse#*
\ifpgfmathfloatroundmayneedrenormalize#*
\pgfmathfloatroundmayneedrenormalizetrue#*
\pgfmathfloatroundmayneedrenormalizefalse#*

\pgfmathfloatparsenumber{number}#*
\pgfmathfloatqparsenumber{number}#*
\pgfmathfloattomacro{number}{flags macro%cmd}{mantissa macro%cmd}{exponent macro%cmd}#*d
\pgfmathfloattoregisters{number}{flags count}{mantissa dimen}{exponent count}#*
\pgfmathfloattoregisterstok{number}{flags count}{mantissa toks}{exponent count}#*
\pgfmathfloatgetflags{number}{flags count}#*
\pgfmathfloatgetflagstomacro{number}{flags macro%cmd}#*d
\pgfmathfloatgetmantissa{number}{mantissa dimen}#*
\pgfmathfloatgetmantisse{number}{mantissa dimen}#*
\pgfmathfloatgetmantissatok{number}{mantissa toks}#*
\pgfmathfloatgetmantissetok{number}{mantissa toks}#*
\pgfmathfloatgetexponent{number}{exponent count}#*

\pgfmathfloatcreate{flags}{mantissa}{exponent}#*
\pgfmathfloattofixed{float}#*
\pgfmathfloattoint{float}#*
\pgfmathfloattosci{float}#*
\pgfmathfloatvalueof{float}#*

\pgfmathroundto{fixed point number}#*
\pgfmathroundtozerofill{fixed point number}#*
\pgfmathfloatround{float}#*
\pgfmathfloatroundzerofill{float}#*

\pgfmathfloatrounddisplaystyle{flags}{mantissa}{exponent}#*

\pgfmathfloatgetfrac{number}#*
\pgfmathgreatestcommondivisor{int 1}{int 2}#*
\pgfmathifisint{number constant}{true}{false}#*
\pgfmathprintnumber{number}#*
\pgfmathprintnumberto{number}{cmd}#*d
\ifpgfmathfloatparsenumberpendingperiod#*
\pgfmathfloatparsenumberpendingperiodtrue#*
\pgfmathfloatparsenumberpendingperiodfalse#*

# variables
\pgfretval#*
\pgfmathresult
\pgfmathresulty#*
\pgfmathresultx#*
\pgfmathresultdenom#S
\pgfmathresultfractional#S
\pgfmathresultnumerator#S
\pgfmathresultX#S
