# CWL for the chemmacros.sty package 
# Matthew Bertucci updated 1/18/2022 for v6.0; 2/14/2022 for v6.1; 3/7/2022 for v6.2

# note: by default, all modules are loaded

#include:l3keys2e
#include:amstext
#include:chemformula
#include:chemgreek
#include:elements
#include:mathtools
#include:chemnum
#include:siunitx
#include:relsize
#include:bm
#include:etoolbox
#include:translations
#include:tikz
#include:tikzlibrarycalc
#include:tikzlibrarydecorations.pathmorphing
#include:xfrac

#keyvals:\usepackage/chemmacros#c
minimal#true,false
modules={%<list of modules%>}
#endkeyvals

## basic setup
\chemsetup{options%keyvals}
\chemsetup[module]{options%keyvals}

## acid-base module
\pH
\pOH
\Ka
\Kb
\Kw
\pKa
\pKa[number]
\pKb
\pKb[number]
\p{anything}

\NewChemEqConstant{cmd}{name}{subscript}#*d
\RenewChemEqConstant{cmd}{name}{default appearance}#*
\DeclareChemEqConstant{cmd}{name}{default appearance}#*d
\ProvideChemEqConstant{cmd}{name}{default appearance}#*d

#keyvals:\chemsetup#c
p-style=#italics,slanted,upright
K-acid={%<text%>}
K-base={%<text%>}
K-water={%<text%>}
eq-constant={%<text%>}
#endkeyvals

## charges-module
# loads formula module
\fplus
\fminus
\scrp
\scrm
\fscrp
\fscrm
\fsscrp
\fsscrm
\pch#*
\pch[number]#*
\mch#*
\mch[number]#*
\fpch#*
\fpch[number]#*
\fmch#*
\fmch[number]#*
\delp
\delm
\fdelp
\fdelm

\NewChemCharge{cmd}{charge symbol}#*d
\RenewChemCharge{cmd}{charge symbol}#*
\DeclareChemCharge{cmd}{charge symbol}#*d
\ProvideChemCharge{cmd}{charge symbol}#*d
\NewChemPartialCharge{cmd}{charge symbol}#*d
\RenewChemPartialCharge{cmd}{charge symbol}#*
\DeclareChemPartialCharge{cmd}{charge symbol}#*d
\ProvideChemPartialCharge{cmd}{charge symbol}#*d

#keyvals:\chemsetup#c
circled=#formal,all,none
circletype=#chem,math
partial-format={%<LaTeX code%>}
#endkeyvals

## nomenclature-module
# loads tikz module
\iupac{IUPAC name}
\chemprime#*
\nonbreakinghyphen#*
\hydrogen
\H
\oxygen
\O
\nitrogen
\N
\sulfur
\Sf
\phosphorus
\P
\cip{conformation}
\rectus
\R
\sinister
\S
\dexter
\D
\laevus
\L
\cis
\trans
\fac
\mer
\sin
\ter
\zusammen
\Z
\entgegen
\E
\syn
\anti
\tert
\ortho
\meta
\para
\Rconf
\Rconf[letter]
\Sconf
\Sconf[letter]
\bridge{number}
\hapto{number}
\dento{number}
\latin{phrase}
\latin[options%keyvals]{phrase}
#keyvals:\latin#c
format={%<format%>}
#endkeyvals
\insitu
\invacuo
\abinitio

\NewChemIUPAC{cmd}{declaration}#*d
\ProvideChemIUPAC{cmd}{declaration}#*d
\RenewChemIUPAC{cmd}{declaration}#*
\DeclareChemIUPAC{cmd}{declaration}#*d
\LetChemIUPAC{cmd1%cmd}{cmd2}#*d
\NewChemIUPACShorthand{shorthand token}{cs}#*
\RenewChemIUPACShorthand{shorthand token}{cs}#*
\DeclareChemIUPACShorthand{shorthand token}{cs}#*
\ProvideChemIUPACShorthand{shorthand token}{cs}#*
\RemoveChemIUPACShorthand{shorthand token}{cs}#*
\NewChemLatin{cmd}{phrase}#*d
\DeclareChemLatin{cmd}{phrase}#*d
\RenewChemLatin{cmd}{phrase}#*
\ProvideChemLatin{cmd}{phrase}#*d

#keyvals:\chemsetup#c
hyphen-pre-space
hyphen-post-space
break-space
iupac=#auto,restricted,strict
iupac-format={%<definition%>}
cip-kern=##L
cip-outer-format={%<format%>}
cip-inner-format={%<format%>}
cip-number-format={%<format%>}
bridge-number=#sub,super
coord-use-hyphen#true,false
latin-format={%<definition%>}
#endkeyvals

## particles-module
# loads charges and formula modules
\el
\prt
\ntr
\Hyd
\Oxo
\water
\El
\Nuc
\ba

\NewChemParticle{cmd}{formula%plain}#*d
\RenewChemParticle{cmd}{formula%plain}#*
\DeclareChemParticle{cmd}{formula%plain}#*d
\ProvideChemParticle{cmd}{formula%plain}#*d
\NewChemNucleophile{cmd}{formula%plain}#*d
\RenewChemNucleophile{cmd}{formula%plain}#*
\DeclareChemNucleophile{cmd}{formula%plain}#*d
\ProvideChemNucleophile{cmd}{formula%plain}#*d

#keyvals:\chemsetup#c
elpair=#dots,dash,false
space=##L
#endkeyvals

## phases-module
# loads formula module
\sld
\lqd
\gas
\aq
\phase{phase}

\NewChemPhase{cmd}{symbol}#*d
\DeclareChemPhase{cmd}{symbol}#*d
\RenewChemPhase{cmd}{symbol}#*
\ProvideChemPhase{cmd}{symbol}#*d

#keyvals:\chemsetup#c
pos=#side,sub
#endkeyvals

## symbols-module
# loads amstext package
\transitionstatesymbol
\standardstatesymbol
\changestate

## formula-module
# loads amstext package and charges module
# loads chemformula, mhchem, chemist, or chemfig depending on user; chemformula is default
#keyvals:\chemsetup#c
formula=#chemformula,mhchem,chemist,chemfig
format={%<format%>}
#endkeyvals

## greek-module
# loads chemgreek package

#keyvals:\chemsetup#c
greek={%<mapping%>}
#endkeyvals

## isotopes-module
# loads elements package
\isotope{isotope}
\isotope*{isotope}

#keyvals:\chemsetup#c
side-connect={%<input%>}
#endkeyvals

## mechanisms-module
# loads amstext package
\mech
\mech[type%keyvals]
#keyvals:\mech
1
2
se
1e
2e
ar
e
e1
e2
cb
#endkeyvals

## newman-module
# loads tikz module
\newman{part-list}
\newman[options%keyvals]{part-list}
\newman[options%keyvals](angle){part-list}

#keyvals:\newman#c,\chemsetup#c
angle=%<degrees%>
scale=%<factor%>
ring={%<TikZ options%>}
atoms={%<TikZ options%>}
back-atoms={%<TikZ options%>}
#endkeyvals

## orbital-module
# loads tikz module
\orbital{type}
\orbital[options%keyvals]{type}

#keyvals:\orbital#c
scale=%<factor%>
angle=%<degrees%>
#endkeyvals

#keyvals:\orbital#c,\chemsetup#c
phase=#+,-
color=#%color
half#true,false
overlay#true,false
opacity=%<number%>
#endkeyvals

## polymers-module
# loads nomenclature and tikz modules
\copolymer
\statistical
\random
\alternating
\periodic
\block
\graft
\blend
\comb
\complex
\cyclic
\branch
\network
\ipnetwork
\sipnetwork
\star

\makepolymerdelims{height}{opening node}{closing node}#*
\makepolymerdelims[options%keyvals]{height}{opening node}[depth]{closing node}#*

#keyvals:\makepolymerdelims#c,\chemsetup#c
delimiters={%<<left><right>%>}
subscript=
superscript=
#endkeyvals

## reactions-module
# loads formula module and mathtools package
\begin{reaction}
\end{reaction}
\begin{reaction*}
\end{reaction*}
\begin{reactions}#\tabular
\end{reactions}
\begin{reactions*}#\tabular
\end{reactions*}
\AddRxnDesc{description}
\listofreactions

\NewChemReaction{envname}{math envname}#*N
\NewChemReaction{envname}[args]{math envname}#*N
\RenewChemReaction{envname}{math envname}#*
\RenewChemReaction{envname}[args]{math envname}#*
\DeclareChemReaction{envname}{math envname}#*N
\DeclareChemReaction{envname}[args]{math envname}#*N
\ProvideChemReaction{envname}{math envname}#*N
\ProvideChemReaction{envname}[args]{math envname}#*N
\reactionlistname#*

#keyvals:\chemsetup#c
tag-open={%<left delim%>}
tag-close={%<right delim%>}
before-tag={%<format%>}
own-counter#true,false
autoref-name={%<name%>}
list-name=
list-entry={%<prefix%>}
list-heading-cmd={%<code%>}
#endkeyvals

## reactants module
# loads chemnum and siunitx packages
\DeclareChemReactant{ID}{properties%keyvals}
#keyvals:\DeclareChemReactant
name=%<name%>
short=%<abbreviation%>
bookmark=%<text%>
upper-name=%<uppercase name%>
upper-bookmark=%<uppercase text%>
#endkeyvals

\reactant{ID}
\reactant[data and units%keyvals]{ID}
\reactant+{ID}#*
\reactant+[data and units%keyvals]{ID}#*
\reactantplain{ID}#*
\submainreactantplain{main ID}{sub ID}#*
\Reactant{ID}
\Reactant[data and units%keyvals]{ID}
\Reactantplain{ID}#*
\Submainreactantplain{main ID}{sub ID}#*
\solvent{ID}
\solvent[data and units%keyvals]{ID}
\solventplain{ID}#*
\Solventplain{ID}#*
\Solvent{ID}
\Solvent[data and units%keyvals]{ID}

#keyvals:\reactant,\reactant+,\Reactant,\solvent,\Solvent
mass=%<number%>
volume=%<number%>
fraction=%<number%>
amount=%<number%>
equiv=%<number%>
purity=%<number%>
concentration=%<number%>
solvent=%<number%>
#endkeyvals

#keyvals:\chemsetup#c,\reactant,\Reactant,\solvent,\Solvent
mass-unit=%<unit%>
volume-unit=%<unit%>
fraction-unit=%<unit%>
amount-unit=%<unit%>
equiv-unit=%<unit%>
concentration-unit=%<unit%>
purity-unit=%<unit%>
#endkeyvals

\printreactants
\printreactants*

\reactants{ID}#*
\reactantl{ID}#*
\solvents{ID}#*
\solventl{ID}#*

#keyvals:\chemsetup#c
initiate#true,false
switch#true,false
reactant-output-style=#name-main-other,main-name-other,main-other-name
solvent-output-style=#main-name,name-main
main=#default,amount,equiv
equivalents#true,false
acronym-support=#acro,glossaries,none
printreactants-style=#xltabular,longtable,none
#endkeyvals

## redox-module
# loads tikz and xfrac modules and mathtools and relsize packages
\ox{%<number%>,%<atom%>}
\ox[%<options%>]{%<number%>,%<atom%>}
\ox*{%<number%>,%<atom%>}
\ox*[%<options%>]{%<number%>,%<atom%>}
\OX{%<name%>,%<atom%>}
\redox(%<name1%>,%<name2%>){%<text%>}
\redox(%<name1%>,%<name2%>)[%<TikZ-options%>]{%<text%>}
\redox(%<name1%>,%<name2%>)[%<TikZ-options%>][%<vertical-factor%>]{%<text%>}

#keyvals:\ox#c,\ox*#c
format={%<code%>}
pos=#top,super,side
side-connect={%<code%>}
#endkeyvals

#keyvals:\ox#c,\ox*#c,\chemsetup#c
parse#true,false
roman#true,false
explicit-sign#true,false
decimal-marker=#comma,point
align=#center,right
text-frac=%<cmd%>
super-frac=%<cmd%>
#endkeyvals

#keyvals:\chemsetup#c
dist=##L
sep=##L
#endkeyvals

## scheme-module
# loads chemnum package
\begin{scheme}
\end{scheme}
\listschemename#*
\schemename#*
\listofschemes

#keyvals:\chemsetup#c
float-method=#KOMA,memoir,tocbasic,newfloat,floatrow,float,traditional
#endkeyvals

## spectroscopy-module
# loads formula module and siunitx package
\NMR{%<isotope%>,%<element%>}(%<frequency%>,%<freq. unit%>)[%<solvent%>]
\NMR{%<isotope%>,%<element%>}(%<frequency%>)[%<solvent%>]
\NMR{%<isotope%>,%<element%>}(%<frequency%>,%<freq. unit%>)
\NMR{%<isotope%>,%<element%>}(%<frequency%>)
\NMR{%<isotope%>,%<element%>}
\NMR{%<isotope%>,%<element%>}[%<solvent%>]
\NMR(%<frequency%>,%<freq. unit%>)[%<solvent%>]
\NMR(%<frequency%>)[%<solvent%>]
\NMR(%<frequency%>,%<freq. unit%>)
\NMR(%<frequency%>)
\NMR
\NMR*{%<isotope%>,%<element%>}(%<frequency%>,%<freq. unit%>)[%<solvent%>]
\NMR*{%<isotope%>,%<element%>}(%<frequency%>)[%<solvent%>]
\NMR*{%<isotope%>,%<element%>}(%<frequency%>,%<freq. unit%>)
\NMR*{%<isotope%>,%<element%>}(%<frequency%>)
\NMR*{%<isotope%>,%<element%>}
\NMR*{%<isotope%>,%<element%>}[%<solvent%>]
\NMR*(%<frequency%>,%<freq. unit%>)[%<solvent%>]
\NMR*(%<frequency%>)[%<solvent%>]
\NMR*(%<frequency%>,%<freq. unit%>)
\NMR*(%<frequency%>)
\NMR*
\begin{experimental}
\end{experimental}
\data{type}#/experimental
\data{type}[specification]#/experimental
\data*{type}#/experimental
\data*{type}[specification]#/experimental
\NMR{%<isotope%>,%<element%>[%<coupling cores%>]}(%<frequency%>,%<freq. unit%>)[%<solvent%>]
\J(%<bonds%>;%<nuclei%>)[%<unit%>]{%<num-list%>}#/experimental
\J(%<bonds%>;%<nuclei%>){%<num-list%>}#/experimental
\J[%<unit%>]{%<num-list%>}#/experimental
\J{%<num-list%>}#/experimental
\#{number of nuclei}#/experimental
\pos{number}#/experimental
\val{number}#/experimental
\val{%<num1%>--%<num2%>}#/experimental

\NewChemNMR{cmd}{isotope,atom}#*d
\DeclareChemNMR{cmd}{isotope,atom}#*d
\RenewChemNMR{cmd}{isotope,atom}#*
\ProvideChemNMR{cmd}{isotope,atom}#*d

#keyvals:\chemsetup#c
unit=%<unit%>
nucleus={%<num%>,%<atom%>}
connector={%<code%>}
method={%<code%>}
nmr-base-format={%<commands%>}
pos-number=#side,sub,super
coupling-symbol={%<code%>}
coupling-unit=%<unit%>
coupling-pos=#side,sub
coupling-nuclei-pre={%<code%>}
coupling-nuclei-post={%<code%>}
coupling-bonds-pre={%<code%>}
coupling-bonds-post={%<code%>}
coupling-pos-cs={%<cmd%>}
atom-number-cs={%<cmd%>}
atom-number-space=##L
delta={%<tokens%>}
list#true,false
list-setup={%<setup%>}
use-equal#true,false
#endkeyvals

## thermodynamics-module
# loads siunitx package
\state{symbol}
\state[options%keyvals]{symbol}
\enthalpy[options%keyvals](subscript){value}
\enthalpy[options%keyvals]{value}
\enthalpy(subscript){value}
\enthalpy{value}
\enthalpy*[options%keyvals](subscript){value}
\enthalpy*[options%keyvals]{value}
\enthalpy*(subscript){value}
\enthalpy*{value}
\entropy[options%keyvals](subscript){value}
\entropy[options%keyvals]{value}
\entropy(subscript){value}
\entropy{value}
\entropy*[options%keyvals](subscript){value}
\entropy*[options%keyvals]{value}
\entropy*(subscript){value}
\entropy*{value}
\gibbs[options%keyvals](subscript){value}
\gibbs[options%keyvals]{value}
\gibbs(subscript){value}
\gibbs{value}
\gibbs*[options%keyvals](subscript){value}
\gibbs*[options%keyvals]{value}
\gibbs*(subscript){value}
\gibbs*{value}

\NewChemState{cmd}{options%keyvals}#*d
\RenewChemState{cmd}{options%keyvals}#*
\DeclareChemState{cmd}{options%keyvals}#*d
\ProvideChemState{cmd}{options%keyvals}#*d

#keyvals:\state,\enthalpy,\enthalpy*,\entropy,\entropy*,\gibbs,\gibbs*,\NewChemState,\RenewChemState,\DeclareChemState,\ProvideChemState
pre={%<text%>}
post={%<text%>}
superscript-left={%<text%>}
superscript-right={%<text%>}
superscript={%<text%>}
subscript-left={%<text%>}
subscript-right={%<text%>}
subscript={%<text%>}
#endkeyvals

#keyvals:\enthalpy,\enthalpy*,\entropy,\entropy*,\gibbs,\gibbs*,\NewChemState,\RenewChemState,\DeclareChemState,\ProvideChemState
subscript-pos=#left,right
symbol=
unit=
#endkeyvals

## units-module
# loads siunitx package
\atmosphere
\atm
\calory
\cal
\cmc
\molar
\moLar
\Molar
\MolMass
\normal
\torr
\angstrom
\atomicmassunit
\bar
\elementarycharge
\mmHg

## base-module
# loads bm, amstext, and etoolbox packages
\NewChemMacroset{name}{arg spec}{internal command call}#*
\NewChemMacroset*{name}{arg spec}{internal command call}#*
\ChemCleverefSupport{counter}{singular}{plural}#*
\ChemCleverefSupport{counter}{singular}[uppercase singular]{plural}[uppercase plural]#*
\ChemFancyrefSupport{prefix}{name}#*
\ChemFancyrefSupport{prefix}{name}[uppercase name]#*

## errorcheck module
# no new user commands

## lang-module
# loads translations package
\DeclareChemTranslation{key%plain}{language}{translation}#*
\DeclareChemTranslations{key%plain}{language=translation,...}#*
\AddChemTranslation{language}{key%plain}{translation}#*
\AddChemTranslations{language}{key=translation,...}#*
\ChemTranslate{translation key}#*

#keyvals:\chemsetup#c
language=#auto,%<language%>
#endkeyvals

# tikz-module
# loads tikz package and calc and decorations.pathmorphing tikzlibraries

## xfrac-module
# loads xfrac package
\chemfrac{numerator}{denominator}
\chemfrac[type%keyvals]{numerator}{denominator}
#keyvals:\chemfrac
text
superscript
#endkeyvals

## Appendix
\ChemStyle{name}#*
\ChemStyle{name}[version description%text]#*
\ChemStyle*{name}#*
\ChemStyle*{name}[version description%text]#*
\usechemstyle{list of styles}
