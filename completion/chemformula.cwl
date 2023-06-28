# package chemformula v4.17
# typeset chemical compounds and reactions
# Clemens Niederberger 01/07/2016
# URL: http://www.ctan.org/pkg/chemformula
# URL: http://www.mychemistry.eu/forums/forum/chemformula/
# Contact: contact@mychemistry.eu
# File written on 02/23/2016

#include:l3keys2e
#include:tikz
#include:amsmath
#include:xfrac
#include:nicefrac
#
#
# Chapter 3. Setup
#
#
\setchemformula{%<options%>}
#
#
# Chapter 4. The Basic Principle
#
#
\ch{formula}
\ch[%<options%>]{formula}
#
#
# Chapter 5. Stoichiometric Factors
#
#
#keyvals:\ch
decimal-marker={%<marker%>}
frac-style=#math,xfrac,nicefrac
frac-math-cmd={%<command sequence%>}
stoich-space={%<skip%>}
stoich-paren-parse=#true,false
stoich-format={%<code%>}
#endkeyvals
#keyvals:\setchemformula
decimal-marker={%<marker%>}
frac-style=#math,xfrac,nicefrac
frac-math-cmd={%<command sequence%>}
stoich-space={%<skip%>}
stoich-paren-parse=#true,false
stoich-format={%<code%>}
#endkeyvals
#keyvals:\chcpd
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
#keyvals:\ch
circled=#formal,all,none
circletype=#chem,math
charge-hshift={%<dim%>}
#endkeyvals
#keyvals:\setchemformula
circled=#formal,all,none
circletype=#chem,math
#endkeyvals
#keyvals:\chcpd
circled=#formal,all,none
circletype=#chem,math
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
#keyvals:\ch
subscript-vshift={%<dim%>}
subscript-style=#text,math
charge-hshift={%<dim%>}
charge-vshift={%<dim%>}
charge-style=#text,math
math-scripts#true,false
adduct-space={%<dim%>}
adduct-penalty={%<num%>}
bond-length={%<dim%>}
bond-offset={%<dim%>}
bond-style={%<TikZ%>}
bond-penalty={%<num%>}
radical-style={%<TikZ%>}
radical-radius={%<dim%>}
radical-hshift={%<dim%>}
radical-vshift={%<dim%>}
radical-space={%<dim%>}
#endkeyvals
#keyvals:\setchemformula
subscript-vshift={%<dim%>}
subscript-style=#text,math
charge-hshift={%<dim%>}
charge-vshift={%<dim%>}
charge-style=#text,math
math-scripts#true,false
adduct-space={%<dim%>}
adduct-penalty={%<num%>}
bond-length={%<dim%>}
bond-offset={%<dim%>}
bond-style={%<TikZ%>}
bond-penalty={%<num%>}
radical-style={%<TikZ%>}
radical-radius={%<dim%>}
radical-hshift={%<dim%>}
radical-vshift={%<dim%>}
radical-space={%<dim%>}
#endkeyvals
#keyvals:\chcpd
subscript-vshift={%<dim%>}
subscript-style=#text,math
charge-hshift={%<dim%>}
charge-vshift={%<dim%>}
charge-style=#text,math
math-scripts#true,false
adduct-space={%<dim%>}
adduct-penalty={%<num%>}
bond-length={%<dim%>}
bond-offset={%<dim%>}
bond-style={%<TikZ%>}
bond-penalty={%<num%>}
radical-style={%<TikZ%>}
radical-radius={%<dim%>}
radical-hshift={%<dim%>}
radical-vshift={%<dim%>}
radical-space={%<dim%>}
#endkeyvals
#
# Section 6.7. Standalone Formulae
#
\chcpd{compound}
\chcpd[%<options%>]{compound}
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
#keyvals:\ch
plus-space={%<skip%>}
plus-penalty={%<num%>}
plus-output-symbol={%<code%>}
minus-space={%<skip%>}
minus-penalty={%<num%>}
minus-output-symbol={%<code%>}
#endkeyvals
#keyvals:\setchemformula
plus-space={%<skip%>}
plus-penalty={%<num%>}
plus-output-symbol={%<code%>}
minus-space={%<skip%>}
minus-penalty={%<num%>}
minus-output-symbol={%<code%>}
#endkeyvals
#keyvals:\chcpd
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
#keyvals:\ch
math-space={%<skip%>}
#endkeyvals
#keyvals:\setchemformula
math-space={%<skip%>}
#endkeyvals
#keyvals:\chcpd
math-space={%<skip%>}
#endkeyvals
#
#
# Chapter 9. Arrows
#
#
# Section 9.3. Customization
#
#keyvals:\ch
arrow-offset={%<dim%>}
arrow-min-length={%<dim%>}
arrow-yshift={%<dim%>}
arrow-ratio={%<factor%>}
compound-sep={%<dim%>}
label-offset={%<dim%>}
label-style={%<font command%>}
arrow-penalty={%<num%>}
arrow-style={%<TikZ%>}
#endkeyvals
#keyvals:\setchemformula
arrow-offset={%<dim%>}
arrow-min-length={%<dim%>}
arrow-yshift={%<dim%>}
arrow-ratio={%<factor%>}
compound-sep={%<dim%>}
label-offset={%<dim%>}
label-style={%<font command%>}
arrow-penalty={%<num%>}
arrow-style={%<TikZ%>}
#endkeyvals
#keyvals:\chcpd
arrow-offset={%<dim%>}
arrow-min-length={%<dim%>}
arrow-yshift={%<dim%>}
arrow-ratio={%<factor%>}
compound-sep={%<dim%>}
label-offset={%<dim%>}
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
#keyvals:\ch
name-format={%<comands%>}
name-width=#{%<dim%>},auto
#endkeyvals
#keyvals:\setchemformula
name-format={%<comands%>}
name-width=#{%<dim%>},auto
#endkeyvals
#keyvals:\chcpd
name-format={%<comands%>}
name-width=#{%<dim%>},auto
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
#keyvals:\ch
format={%<code%>}
atom-format={%<code%>}
font-family={%<family%>}
font-series={%<series%>}
font-shape={%<shape%>}
font-spec={%<font%>}
font-spec={[%<options%>]%<font%>}
#endkeyvals
#keyvals:\setchemformula
format={%<code%>}
atom-format={%<code%>}
font-family={%<family%>}
font-series={%<series%>}
font-shape={%<shape%>}
font-spec={%<font%>}
font-spec={[%<options%>]%<font%>}
#endkeyvals
#keyvals:\chcpd
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
\chlewis{electron spec}{atom}#
\chlewis[%<options%>]{electron spec}{atom}#
#keyvals:\chlewis
lewis-default=#.,:,|,o,single,pair,{pair (dotted)},{pair (line)},empty
lewis-distance={%<dim%>}
lewis-line-length={%<dim%>}
lewis-line-width={%<dim%>}
lewis-offset={%<dim%>}5ex
#endkeyvals
#keyvals:\setchemformula
lewis-default=#.,:,|,o,single,pair,{pair (dotted)},{pair (line)},empty
lewis-distance={%<dim%>}
lewis-line-length={%<dim%>}
lewis-line-width={%<dim%>}
lewis-offset={%<dim%>}
#endkeyvals
#
#
# Chapter 15. Kröger-Vink Notation
#
#
#keyvals:\ch
kroeger-vink=#true,false
kv-positive-style={%<TikZ%>}
kv-positive-radius={%<dim%>}
kv-positive-hshift={%<dim%>}
kv-positive-vshift={%<dim%>}
kv-positive-offset={%<dim%>}
kv-positive-symbol={%<TeX code%>}
#endkeyvals
#keyvals:\setchemformula
kroeger-vink=#true,false
kv-positive-style={%<TikZ%>}
kv-positive-radius={%<dim%>}
kv-positive-hshift={%<dim%>}
kv-positive-vshift={%<dim%>}
kv-positive-offset={%<dim%>}
kv-positive-symbol={%<TeX code%>}
#endkeyvals
#
#
# Other commands inside the package
#
#
\chstoich{arg1}#S
\DeprecatedFormulaCommand{deprecated macro}{replacement macro}{code}#S
\chemformula@version#S
\chemformula@date#S
