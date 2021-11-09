# CWL for the chemmacros.sty package 
# Matthew Bertucci 11/7/2021 for v5.11a

#include:l3keys2e
#include:siunitx
#include:chemformula
#include:chemnum
#include:tikz
#include:xfrac
#include:mathtools
#include:relsize
#include:amstext
#include:elements
#include:scrlfile
#include:chemgreek
#include:translations

# basic setup
\usechemmodule{module%keyvals}
#keyvals:\usechemmodule#c
all
isotope
mechanisms
newman
orbital
polymers
reactions
redox
scheme
spectroscopy
thermodynamics
units
tikz
xfrac
#endkeyvals

\chemsetup{options%keyvals}
\chemsetup[module]{options%keyvals}
#keyvals:\chemsetup#c
modules={%<list of modules%>}
greek={%<mapping%>}
#endkeyvals

\IfChemCompatibilityTF{comp}{version}{true}{false}#*
\IfChemCompatibilityT{comp}{version}{true}#*
\IfChemCompatibilityF{comp}{version}{false}#*
\ChemCompatibility{version}#*
\ChemCompatibilityFrom{version}#*
\ChemCompatibilityTo{version}#*
\ChemCompatibilityBetween{version1}{version2}#*
\EndChemCompatibility#*


# acid-base module
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
\RenewChemEqConstant{cmd}{name}{default appearance}#*d
\DeclareChemEqConstant{cmd}{name}{default appearance}#*d
\ProvideChemEqConstant{cmd}{name}{default appearance}#*d

#keyvals:\chemsetup#c
p-style=#italics,slanted,upright
K-acid={%<text%>}
K-base={%<text%>}
K-water={%<text%>}
eq-constant={%<text%>}
#endkeyvals

# charges-module
\fplus
\fminus
\scrp
\scrm
\fscrp
\fscrm
\fsscrp
\fsscrm
\pch
\pch[number]
\mch
\mch[number]
\fpch
\fpch[number]
\fmch
\fmch[number]
\delp
\delm
\fdelp
\fdelm

\NewChemCharge{cmd}{charge symbol}#*d
\RenewChemCharge{cmd}{charge symbol}#*d
\DeclareChemCharge{cmd}{charge symbol}#*d
\ProvideChemCharge{cmd}{charge symbol}#*d
\NewChemPartialCharge{cmd}{charge symbol}#*d
\RenewChemPartialCharge{cmd}{charge symbol}#*d
\DeclareChemPartialCharge{cmd}{charge symbol}#*d
\ProvideChemPartialCharge{cmd}{charge symbol}#*d

#keyvals:\chemsetup#c
circled=#formal,all,none
circletype=#chem,math
partial-format={%<LaTeX code%>}
#endkeyvals


# nomenclature-module
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
\RenewChemIUPAC{cmd}{declaration}#*d
\DeclareChemIUPAC{cmd}{declaration}#*d
\LetChemIUPAC{cmd1%cmd}{cmd2}#*d
\NewChemIUPACShorthand{shorthand token}{cs}#*
\RenewChemIUPACShorthand{shorthand token}{cs}#*
\DeclareChemIUPACShorthand{shorthand token}{cs}#*
\ProvideChemIUPACShorthand{shorthand token}{cs}#*
\RemoveChemIUPACShorthand{shorthand token}{cs}#*
\NewChemLatin{cmd}{phrase}#*d
\DeclareChemLatin{cmd}{phrase}#*d
\RenewChemLatin{cmd}{phrase}#*d
\ProvideChemLatin{cmd}{phrase}#*d

#keyvals:\chemsetup#c
hyphen-pre-space
hyphen-post-space
break-space
iupac=#auto,restricted,strict
cip-kern=##L
cip-outer-format={%<format%>}
cip-inner-format={%<format%>}
cip-number-format={%<format%>}
bridge-number=#sub,super
coord-use-hyphen#true,false
#endkeyvals


# particles-module
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
\RenewChemParticle{cmd}{formula%plain}#*d
\DeclareChemParticle{cmd}{formula%plain}#*d
\ProvideChemParticle{cmd}{formula%plain}#*d
\NewChemNucleophile{cmd}{formula%plain}#*d
\RenewChemNucleophile{cmd}{formula%plain}#*d
\DeclareChemNucleophile{cmd}{formula%plain}#*d
\ProvideChemNucleophile{cmd}{formula%plain}#*d

#keyvals:\chemsetup#c
elpair=#dots,dash,false
space=##L
#endkeyvals


# phases-module
\sld
\lqd
\gas
\aq
\phase{phase}

\NewChemPhase{cmd}{symbol}#*d
\DeclareChemPhase{cmd}{symbol}#*d
\RenewChemPhase{cmd}{symbol}#*d
\ProvideChemPhase{cmd}{symbol}#*d

#keyvals:\chemsetup#c
pos=#side,sub
#endkeyvals


# symbols-module
\transitionstatesymbol
\standardstatesymbol
\changestate


# base-module
\NewChemMacroset{name}{arg spec}{internal command call}#*
\NewChemMacroset*{name}{arg spec}{internal command call}#*
\ChemCleverefSupport{counter}{singular}{plural}#*
\ChemCleverefSupport{counter}{singular}[uppercase singular]{plural}[uppercase plural]#*
\ChemFancyrefSupport{prefix}{name}#*
\ChemFancyrefSupport{prefix}{name}[uppercase name]#*


# chemformula-module
#keyvals:\chemsetup#c
formula=#chemformula,mhchem,chemist,chemfig
format={%<format%>}
#endkeyvals


# lang-module
\DeclareChemTranslation{key%plain}{language}{translation}#*
\DeclareChemTranslations{key%plain}{language=translation,...}#*
\ChemTranslate{translation key}#*

#keyvals:\chemsetup#c
language=
#endkeyvals


# isotopes-module
\isotope{isotope}
\isotope*{isotope}

#keyvals:\chemsetup#c
side-connect={%<input%>}
#endkeyvals


# mechanisms-module
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


# newman-module
\newman{part-list}
\newman[options%keyvals]{part-list}
\newman[options%keyvals][angle]{part-list}

#keyvals:\newman#c,\chemsetup#c
angle=%<degrees%>
scale=%<factor%>
ring={%<TikZ%>}
atoms={%<TikZ%>}
back-atoms={%<TikZ%>}
#endkeyvals


# orbital-module
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


# polymers-module
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


# reactions-module
\begin{reaction}
\end{reaction}
\begin{reaction*}
\end{reaction*}
\begin{reactions}
\end{reactions}
\begin{reactions*}
\end{reactions*}
\AddRxnDesc{description}
\listofreactions

\renewtagform{tagname}{left delimiter}{right delimiter}#*
\renewtagform{tagname}[format]{left delimiter}{right delimiter}#*
\NewChemReaction{envname}{math envname}#*N
\NewChemReaction{envname}[args]{math envname}#*N
\RenewChemReaction{envname}{math envname}#*N
\RenewChemReaction{envname}[args]{math envname}#*N
\DeclareChemReaction{envname}{math envname}#*N
\DeclareChemReaction{envname}[args]{math envname}#*N
\ProvideChemReaction{envname}{math envname}#*N
\ProvideChemReaction{envname}[args]{math envname}#*N
\reactionlistname#*

#keyvals:\chemsetup#c
tag-open={%<left delim%>}
tag-close={%<right delim%>}
before-tag={%<format%>}
list-name=
list-entry={%<prefix%>}
list-heading-cmd={%<code%>}
tocbasic#true,false
#endkeyvals


# redox-module
\ox{%<number%>,%<atom%>}
\ox[%<options%>]{%<number%>,%<atom%>}
\ox*{%<number%>,%<atom%>}
\ox*[%<options%>]{%<number%>,%<atom%>}
\OX{%<name%>,%<atom%>}
\redox(%<name1%>,%<name2%>){%<text%>}
\redox(%<name1%>,%<name2%>)[%<tikz-options%>]{%<text%>}
\redox(%<name1%>,%<name2%>)[%<tikz-options%>][%<vertical-factor%>]{%<text%>}

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


# scheme-module
\begin{scheme}
\end{scheme}
\listschemename#*
\schemename#*
\listofschemes


# spectroscopy-module
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
\RenewChemNMR{cmd}{isotope,atom}#*d
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


# thermodynamics-module
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
\RenewChemState{cmd}{options%keyvals}#*d
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


# units-module
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


# xfrac-module
\chemfrac{numerator}{denominator}
\chemfrac[type%keyvals]{numerator}{denominator}
#keyvals:\chemfrac
text
superscript
#endkeyvals
