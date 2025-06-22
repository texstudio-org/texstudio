# package chemformula v4.17
# typeset chemical compounds and reactions
# Clemens Niederberger 01/07/2016
# URL: http://www.ctan.org/pkg/chemformula
# URL: http://www.mychemistry.eu/forums/forum/chemformula/
# Contact: contact@mychemistry.eu
# File written on 02/23/2016

#include:tikz
#include:amsmath
#include:xfrac
#include:nicefrac
#
#
# Chapter 3. Setup
#
#
\setchemformula{options%keyvals}
#
#
# Chapter 4. The Basic Principle
#
#
\ch{formula}
\ch[options%keyvals]{formula}
#
#
# Chapter 5. Stoichiometric Factors
#
#
#keyvals:\ch,\setchemformula,\chcpd
decimal-marker={%<marker%>}
frac-style=#math,xfrac,nicefrac
frac-math-cmd={%<command sequence%>}
stoich-space={%<skip%>}
stoich-paren-parse=#true,false
stoich-format={%<code%>}
#endkeyvals
#
#
# Chapter 6. Compounds
#
#
# Section 6.4. Charges and Other Superscripts
#
#keyvals:\ch,\setchemformula,\chcpd
circled=#formal,all,none
circletype=#chem,math
charge-hshift=##L
#endkeyvals
#
# Section 6.5. Bonds
#
\bond{bond name}
\NewChemBond{name}{code}
\DeclareChemBond{name}{code}#*
\RenewChemBond{name}{code}#*
\ProvideChemBond{name}{code}#*
\NewChemBondAlias{new name}{old name}
\DeclareChemBondAlias{new name}{old name}#*
\ShowChemBond{name}#*
#
# Section 6.6. Customization
#
#keyvals:\ch,\setchemformula,\chcpd
subscript-vshift=##L
subscript-style=#text,math
charge-hshift=##L
charge-vshift=##L
charge-style=#text,math
math-scripts#true,false
adduct-space=##L
adduct-penalty={%<num%>}
bond-length=##L
bond-offset=##L
bond-style={%<TikZ%>}
bond-penalty={%<num%>}
radical-style={%<TikZ%>}
radical-radius=##L
radical-hshift=##L
radical-vshift=##L
radical-space=##L
#endkeyvals
#
# Section 6.7. Standalone Formulae
#
\chcpd{compound}
\chcpd[options%keyvals]{compound}
#
# Section 6.8. Extend Compound Properties
#
\NewChemCompoundProperty{token}{replacement}
\ProvideChemCompoundProperty{token}{replacement}#*
\RenewChemCompoundProperty{token}{replacement}#*
\DeclareChemCompoundProperty{token}{replacement}#*
\RemoveChemCompoundProperty{token}#*
#
#
# Chapter 7. Special Input Types
#
#
\NewChemAdditionSymbol{name}{input}{output}
\ProvideChemAdditionSymbol{name}{input}{output}#*
\RenewChemAdditionSymbol{name}{input}{output}#*
\DeclareChemAdditionSymbol{name}{input}{output}#*
#keyvals:\ch,\setchemformula,\chcpd
plus-space={%<skip%>}
plus-penalty={%<num%>}
plus-output-symbol={%<code%>}
minus-space={%<skip%>}
minus-penalty={%<num%>}
minus-output-symbol={%<code%>}
#endkeyvals
\NewChemSymbol{input}{output}
\ProvideChemSymbol{input}{output}#*
\RenewChemSymbol{input}{output}#*
\DeclareChemSymbol{input}{output}#*
#
#
# Chapter 8. Escaped Input
#
#
# Section 8.2. Math
#
#keyvals:\ch,\setchemformula,\chcpd
math-space={%<skip%>}
#endkeyvals
#
#
# Chapter 9. Arrows
#
#
# Section 9.3. Customization
#
#keyvals:\ch,\setchemformula,\chcpd
arrow-offset=##L
arrow-min-length=##L
arrow-yshift=##L
arrow-ratio={%<factor%>}
compound-sep=##L
label-offset=##L
label-style={%<font command%>}
arrow-penalty={%<num%>}
arrow-style={%<TikZ%>}
#endkeyvals
#
# Section 9.4. Modify Arrow Types
#
\NewChemArrow{type}{TikZ}
\ProvideChemArrow{type}{TikZ}#*
\DeclareChemArrow{type}{TikZ}#*
\RenewChemArrow{type}{TikZ}#*
\ShowChemArrow{type}#*
#
# Section 9.5. Standalone Arrows
#
\charrow{type}
\charrow{type}[above]
\charrow{type}[above][below]
#
#
# Chapter 10. Names
#
#
# Section 10.2. Customization
#
#keyvals:\ch,\setchemformula,\chcpd
name-format={%<commands%>}
name-width=##L,auto
#endkeyvals
#
# Section 10.3. Standalone Names
#
\chname(text 1)(text 2)
#
#
# Chapter 11. Format and Font
#
#
#keyvals:\ch,\setchemformula,\chcpd
format={%<code%>}
atom-format={%<code%>}
font-family={%<family%>}
font-series={%<series%>}
font-shape={%<shape%>}
font-spec={%<font%>}
font-spec={[%<options%>]%<font%>}
#endkeyvals
#
#
# Chapter 13. Usage with TikZ or pgfplots and externalization
#
#
#keyvals:\setchemformula
tikz-external-disable=#true,false
#endkeyvals
#
#
# Chapter 14. Lewis Formulae
#
#
\chlewis{electron spec}{atom}
\chlewis[options%keyvals]{electron spec}{atom}
#keyvals:\chlewis,\setchemformula
lewis-default=#.,:,|,o,single,pair,{pair (dotted)},{pair (line)},empty#c
lewis-distance=##L
lewis-line-length=##L
lewis-line-width=##L
lewis-offset=##L
# other useful keys
radical-radius=##L
#endkeyvals
#
#
# Chapter 15. Kröger-Vink Notation
#
#
#keyvals:\ch,\setchemformula
kroeger-vink=#true,false
kv-positive-style={%<TikZ%>}
kv-positive-radius=##L
kv-positive-hshift=##L
kv-positive-vshift=##L
kv-positive-offset=##L
kv-positive-symbol={%<TeX code%>}
#endkeyvals
#
#
# Other commands inside the package
#
#
\chstoich{arg1}#S
\DeprecatedFormulaCommand{deprecated macro}{replacement macro}{code}#S
