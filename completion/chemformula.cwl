# package chemformula v4.14a
# typeset chemical compounds and reactions
# Clemens Niederberger 01/07/2016
# URL: http://www.ctan.org/pkg/chemformula
# URL: http://www.mychemistry.eu/forums/forum/chemformula/
# Contact: contact@mychemistry.eu
# File written on 02/23/2016

#include:expl3
#include:xparse
#include:l3keys2e
#include:tikz
#include:amstext
#include:xfrac
#include:nicefrac
#include:scrlfile
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
\ch{input}
\ch[%<options%>]{input}
#
#
# Chapter 5. Stoichiometric Factors
#
#
#keyvals:\ch
decimal-marker={%<marker%>} # default: .
frac-style=#math,xfrac,nicefrac, # default: math
frac-math-cmd={%<command sequence%>} # default: \frac
stoich-space={%<skip%>} # default: .1667em plus .0333em minus .0117em
stoich-paren-parse=#true,false, # default: false
stoich-print={%<cs%>} # default: \chstoich
#endkeyvals
#keyvals:\setchemformula
decimal-marker={%<marker%>} # default: .
frac-style=#math,xfrac,nicefrac, # default: math
frac-math-cmd={%<command sequence%>} # default: \frac
stoich-space={%<skip%>} # default: .1667em plus .0333em minus .0117em
stoich-paren-parse=#true,false, # default: false
stoich-print={%<cs%>} # default: \chstoich
#endkeyvals
#keyvals:\chcpd
decimal-marker={%<marker%>} # default: .
frac-style=#math,xfrac,nicefrac, # default: math
frac-math-cmd={%<command sequence%>} # default: \frac
stoich-space={%<skip%>} # default: .1667em plus .0333em minus .0117em
stoich-paren-parse=#true,false, # default: false
stoich-print={%<cs%>} # default: \chstoich
#endkeyvals
#
#
# Chapter 6. Compounds
#
#
# Section 6.4. Charges and Other Superscripts
#
#keyvals:\ch
circled=#formal,all,none, # default: formal
circletype=#chem,math, # default: chem
charge-hshift={%<dim%>}
#endkeyvals
#keyvals:\setchemformula
circled=#formal,all,none, # default: formal
circletype=#chem,math, # default: chem
#endkeyvals
#keyvals:\chcpd
circled=#formal,all,none, # default: formal
circletype=#chem,math, # default: chem
#endkeyvals
#
# Section 6.5. Bonds
#
\bond{bond name}
\NewChemBond{name}{code}#d
\DeclareChemBond{name}{code}#*d
\RenewChemBond{name}{code}#*d
\ProvideChemBond{name}{code}#*d
\NewChemBondAlias{new name}{old name}#d
\DeclareChemBondAlias{new name}{old name}#*d
\ShowChemBond{name}#*
#
# Section 6.6. Customization
#
#keyvals:\ch
subscript-vshift={%<dim%>} # default: 0pt
subscript-style=#text,math, # default: text
charge-hshift={%<dim%>} # default: .25em
charge-vshift={%<dim%>} # default: 0pt
charge-style=#text,math, # default: text
adduct-space={%<dim%>} # default: .1333em
adduct-penalty={%<num%>} # default: 300
bond-length={%<dim%>} # default: .5833em
bond-offset={%<dim%>} # default: .07em
bond-style={%<TikZ%>} # default: empty
bond-penalty={%<num%>} # default: 10000
radical-style={%<TikZ%>} # default: empty
radical-radius={%<dim%>} # default: .2ex
radical-hshift={%<dim%>} # default: .15em
radical-vshift={%<dim%>} # default: .5ex
radical-space={%<dim%>} # default: .15em
#endkeyvals
#keyvals:\setchemformula
subscript-vshift={%<dim%>} # default: 0pt
subscript-style=#text,math, # default: text
charge-hshift={%<dim%>} # default: .25em
charge-vshift={%<dim%>} # default: 0pt
charge-style=#text,math, # default: text
adduct-space={%<dim%>} # default: .1333em
adduct-penalty={%<num%>} # default: 300
bond-length={%<dim%>} # default: .5833em
bond-offset={%<dim%>} # default: .07em
bond-style={%<TikZ%>} # default: empty
bond-penalty={%<num%>} # default: 10000
radical-style={%<TikZ%>} # default: empty
radical-radius={%<dim%>} # default: .2ex
radical-hshift={%<dim%>} # default: .15em
radical-vshift={%<dim%>} # default: .5ex
radical-space={%<dim%>} # default: .15em
#endkeyvals
#keyvals:\chcpd
subscript-vshift={%<dim%>} # default: 0pt
subscript-style=#text,math, # default: text
charge-hshift={%<dim%>} # default: .25em
charge-vshift={%<dim%>} # default: 0pt
charge-style=#text,math, # default: text
adduct-space={%<dim%>} # default: .1333em
adduct-penalty={%<num%>} # default: 300
bond-length={%<dim%>} # default: .5833em
bond-offset={%<dim%>} # default: .07em
bond-style={%<TikZ%>} # default: empty
bond-penalty={%<num%>} # default: 10000
radical-style={%<TikZ%>} # default: empty
radical-radius={%<dim%>} # default: .2ex
radical-hshift={%<dim%>} # default: .15em
radical-vshift={%<dim%>} # default: .5ex
radical-space={%<dim%>} # default: .15em
#endkeyvals
#
# Section 6.7. Standalone Formulae
#
\chcpd{compound}
\chcpd[%<options%>]{compound}
#
# Section 6.8. Extend Compound Properties
#
\NewChemCompoundProperty{token}{replacement}#d
\ProvideChemCompoundProperty{token}{replacement}#*d
\RenewChemCompoundProperty{token}{replacement}#*d
\DeclareChemCompoundProperty{token}{replacement}#*d
\RemoveChemCompoundProperty{token}#*
#
#
# Chapter 7. Special Input Types
#
#
\NewChemAdditionSymbol{name}{input}{output}#d
\ProvideChemAdditionSymbol{name}{input}{output}#*d
\RenewChemAdditionSymbol{name}{input}{output}#*d
\DeclareChemAdditionSymbol{name}{input}{output}#*d
#keyvals:\ch
plus-space={%<skip%>} # default: .3em plus .1em minus .1em
plus-penalty={%<num%>} # default: 700
plus-output-symbol={%<code%>} # default: +
minus-space={%<skip%>} # default: .3em plus .1em minus .1em
minus-penalty={%<num%>} # default: 700
minus-output-symbol={%<code%>} # default: $-$
#endkeyvals
#keyvals:\setchemformula
plus-space={%<skip%>} # default: .3em plus .1em minus .1em
plus-penalty={%<num%>} # default: 700
plus-output-symbol={%<code%>} # default: +
minus-space={%<skip%>} # default: .3em plus .1em minus .1em
minus-penalty={%<num%>} # default: 700
minus-output-symbol={%<code%>} # default: $-$
#endkeyvals
#keyvals:\chcpd
plus-space={%<skip%>} # default: .3em plus .1em minus .1em
plus-penalty={%<num%>} # default: 700
plus-output-symbol={%<code%>} # default: +
minus-space={%<skip%>} # default: .3em plus .1em minus .1em
minus-penalty={%<num%>} # default: 700
minus-output-symbol={%<code%>} # default: $-$
#endkeyvals
\NewChemSymbol{input}{output}#d
\ProvideChemSymbol{input}{output}#*d
\RenewChemSymbol{input}{output}#*d
\DeclareChemSymbol{input}{output}#*d
#
#
# Chapter 8. Escaped Input
#
#
# Section 8.2. Math
#
#keyvals:\ch
math-space={%<skip%>} # default: .1667em plus .0333em minus .0117em
#endkeyvals
#keyvals:\setchemformula
math-space={%<skip%>} # default: .1667em plus .0333em minus .0117em
#endkeyvals
#keyvals:\chcpd
math-space={%<skip%>} # default: .1667em plus .0333em minus .0117em
#endkeyvals
#
#
# Chapter 9. Arrows
#
#
# Section 9.3. Customization
#
#keyvals:\ch
arrow-offset={%<dim%>} # default: .75em
arrow-min-length={%<dim%>} # default: 0pt
arrow-yshift={%<dim%>} # default: 0pt
arrow-ratio={%<factor%>} # default: .6
compound-sep={%<dim%>} # default: .5em
label-offset={%<dim%>} # default: 2pt
label-style={%<font command%>} # default: \footnotesize
arrow-penalty={%<num%>} # default: 0
arrow-style={%<TikZ%>} # default: empty
#endkeyvals
#keyvals:\setchemformula
arrow-offset={%<dim%>} # default: .75em
arrow-min-length={%<dim%>} # default: 0pt
arrow-yshift={%<dim%>} # default: 0pt
arrow-ratio={%<factor%>} # default: .6
compound-sep={%<dim%>} # default: .5em
label-offset={%<dim%>} # default: 2pt
label-style={%<font command%>} # default: \footnotesize
arrow-penalty={%<num%>} # default: 0
arrow-style={%<TikZ%>} # default: empty
#endkeyvals
#keyvals:\chcpd
arrow-offset={%<dim%>} # default: .75em
arrow-min-length={%<dim%>} # default: 0pt
arrow-yshift={%<dim%>} # default: 0pt
arrow-ratio={%<factor%>} # default: .6
compound-sep={%<dim%>} # default: .5em
label-offset={%<dim%>} # default: 2pt
label-style={%<font command%>} # default: \footnotesize
arrow-penalty={%<num%>} # default: 0
arrow-style={%<TikZ%>} # default: empty
#endkeyvals
#
# Section 9.4. Modify Arrow Types
#
\NewChemArrow{type}{TikZ}#d
\ProvideChemArrow{type}{TikZ}#*d
\DeclareChemArrow{type}{TikZ}#*d
\RenewChemArrow{type}{TikZ}#*d
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
name-format={%<comands%>} # default: \scriptsize\centering
name-width=#{%<dim%>},auto, # default: auto
#endkeyvals
#keyvals:\setchemformula
name-format={%<comands%>} # default: \scriptsize\centering
name-width=#{%<dim%>},auto, # default: auto
#endkeyvals
#keyvals:\chcpd
name-format={%<comands%>} # default: \scriptsize\centering
name-width=#{%<dim%>},auto, # default: auto
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
format={%<code%>} # default: empty
atom-format={%<code%>} # default: empty
font-family={%<family%>} # default: empty
font-series={%<series%>} # default: empty
font-shape={%<shape%>} # default: empty
font-spec={%<font%>} # default: empty
font-spec={[%<options%>]%<font%>} # default: empty
#endkeyvals
#keyvals:\setchemformula
format={%<code%>} # default: empty
atom-format={%<code%>} # default: empty
font-family={%<family%>} # default: empty
font-series={%<series%>} # default: empty
font-shape={%<shape%>} # default: empty
font-spec={%<font%>} # default: empty
font-spec={[%<options%>]%<font%>} # default: empty
#endkeyvals
#keyvals:\chcpd
format={%<code%>} # default: empty
atom-format={%<code%>} # default: empty
font-family={%<family%>} # default: empty
font-series={%<series%>} # default: empty
font-shape={%<shape%>} # default: empty
font-spec={%<font%>} # default: empty
font-spec={[%<options%>]%<font%>} # default: empty
#endkeyvals
#
#
# Chapter 13. Usage with TikZ or pgfplots and externalization
#
#
#keyvals:\setchemformula
tikz-external-disable=#true,false, # default: true
#endkeyvals
#
#
# Chapter 14. Lewis Formulae
#
#
\chlewis{electron spec}{atom}#
\chlewis[%<options%>]{electron spec}{atom}#
#keyvals:\chlewis
lewis-default=#.,:,|,o,single,pair,{pair (dotted)},{pair (line)},empty, # default: pair
lewis-distance={%<dim%>} # default: 1ex
lewis-line-length={%<dim%>} # default: 1.5ex
lewis-line-width={%<dim%>} # default: 1pt
lewis-offset={%<dim%>} # default: .5ex
#endkeyvals
#keyvals:\setchemformula
lewis-default=#.,:,|,o,single,pair,{pair (dotted)},{pair (line)},empty, # default: pair
lewis-distance={%<dim%>} # default: 1ex
lewis-line-length={%<dim%>} # default: 1.5ex
lewis-line-width={%<dim%>} # default: 1pt
lewis-offset={%<dim%>} # default: .5ex
#endkeyvals
#
#
# Chapter 15. Kröger-Vink Notation
#
#
#keyvals:\ch
kroeger-vink=#true,false, # default: false
kv-positive-style={%<TikZ%>} # default: empty
kv-positive-radius={%<dim%>} # default: .3ex
kv-positive-hshift={%<dim%>} # default: .15ex
kv-positive-vshift={%<dim%>} # default: .5ex
kv-positive-offset={%<dim%>} # default: .4em
kv-positive-symbol={%<TeX code%>} # default: $\time$
#endkeyvals
#keyvals:\setchemformula
kroeger-vink=#true,false, # default: false
kv-positive-style={%<TikZ%>} # default: empty
kv-positive-radius={%<dim%>} # default: .3ex
kv-positive-hshift={%<dim%>} # default: .15ex
kv-positive-vshift={%<dim%>} # default: .5ex
kv-positive-offset={%<dim%>} # default: .4em
kv-positive-symbol={%<TeX code%>} # default: $\time$
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