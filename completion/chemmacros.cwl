# CWL for the chemmacros.sty package 

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


# basic setup
\chemsetup{options}


# acid-base module
\pH
\POH
\Ka
\Kb
\Kw
\pKa[number]
\pKb[number]
\p{anything}

\NewChemEqConstant{cs}{name}{subscript}#*
\RenewChemEqConstant{cs}{name}{default appearance}#*
\DeclareChemEqConstant{cs}{name}{default appearance}#*
\ProvideChemEqConstant{cs}{name}{default appearance}#*


# charges-module
\fplus
\fminus
\scrp
\scrm
\fscrp
\fscrm
\fsscrp
\fsscrm
\pch[number]
\mch[number]
\fpch[number]
\fmch[number]
\delp
\delm
\fdelp
\fdelm

\NewChemCharge{cs}{charge symbol}#*
\RenewChemCharge{cs}{charge symbol}#*
\DeclareChemCharge{cs}{charge symbol}#*
\ProvideChemCharge{cs}{charge symbol}#*
\NewChemPartialCharge{cs}{charge symbol}#*
\RenewChemPartialCharge{cs}{charge symbol}#*
\DeclareChemPartialCharge{cs}{charge symbol}#*
\ProvideChemPartialCharge{cs}{charge symbol}#*


# nomenclature-module
\iupac
\chemprime
\hydrogen#*
\oxygen#*
\nitrogen#*
\sulfur#*
\phosphorus#*
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
\sinister
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
\Rconf[letter]
\Sconf[letter]
\bridge{number}
\hapto{number}
\dento{number}
\latin[options]{phrase}
\insitu
\invacuo
\abinitio

\NewChemIUPAC{cs}{declaration}#*
\ProvideChemIUPAC{cs}{declaration}#*
\RenewChemIUPAC{cs}{declaration}#*
\DeclareChemIUPAC{cs}{declaration}#*
\LetChemIUPAC{cs1}{cs2}#*
\NewChemIUPACShorthand{shorthand token}{cs}#*
\RenewChemIUPACShorthand{shorthand token}{cs}#*
\DeclareChemIUPACShorthand{shorthand token}{cs}#*
\ProvideChemIUPACShorthand{shorthand token}{cs}#*
\RemoveChemIUPACShorthand{shorthand token}{cs}#*
\NewChemLatin{cs}{phrase}#*
\DeclareChemLatin{cs}{phrase}#*
\RenewChemLatin{cs}{phrase}#*
\ProvideChemLatin{cs}{phrase}#*


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

\NewChemParticle{cs}{formula}#*
\RenewChemParticle{cs}{formula}#*
\DeclareChemParticle{cs}{formula}#*
\ProvideChemParticle{cs}{formula}#*
\NewChemNucleophile{cs}{formula}#*
\RenewChemNucleophile{cs}{formula}#*
\DeclareChemNucleophile{cs}{formula}#*
\ProvideChemNucleophile{cs}{formula}#*


# phases-module
\sld
\lqd
\gas
\aq
\phase{phase}

\NewChemPhase{cs}{symbol}#*
\DeclareChemPhase{cs}{symbol}#*
\RenewChemPhase{cs}{symbol}#*
\ProvideChemPhase{cs}{symbol}#*
\DeclareTranslation{language}{name}{translation}#*


# symbols-module
\transitionstatesymbol
\standardstatesymbol
\changestate


# isotopes-module
\isotope{isotope}
\isotope*{isotope}


# mechanisms-module
\mech[type]


# newman-module
\newman[options][angle]{part-list}


# orbital-module
\orbital[options]{type}


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

\makepolymerdelims[options]{height}{opening node}{closing node}#*


# reactions-module
\begin{reaction}[name]
\end{reaction}
\begin{reaction*}[name]
\end{reaction*}
\begin{reactions}
\end{reactions}
\begin{reactions*}
\end{reactions*}
\AddRxnDesc#\reactions,\reactions*
\listofreactions

\renewtagform{tagname}[format]{left delimiter}{right delimiter}#*
\NewChemReaction{name}[argument count]{math name}#*
\RenewChemReaction{name}[argument count]{math name}#*
\DeclareChemReaction{name}[argument count]{math name}#*
\ProvideChemReaction{name}[argument count]{math name}#*


# redox-module
\ox[%<options%>]{%<number%>,%<atom%>}
\ox*[%<options%>]{%<number%>,%<atom%>}
\OX{%<name%>,%<atom%>}
\redox(%<name1%>,%<name2%>)[%<tikz-options%>][%<vertical-factor%>]{%<text%>}


# scheme-module
\begin{scheme}
\end{scheme}
\listschemename
\schemename
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
\data{type}[specification]#\experimental
\data*{type}[specification]#\experimental
\NMR{%<isotope%>,%<element%>[%<coupling cores%>]}(%<frequency%>,%<freq. unit%>)[%<solvent%>]#\experimental
\J(%<bonds%>;%<nuclei%>)[%<unit%>]{%<num-list%>}#\experimental
\J(%<bonds%>;%<nuclei%>){%<num-list%>}#\experimental
\J[%<unit%>]{%<num-list%>}#\experimental
\J{%<num-list%>}#\experimental
\#{number of nuclei}#\experimental
\pos{number}#\experimental
\val{number}#\experimental
\val{%<num1%>--%<num2%>}#\experimental


\NewChemNMR{%<cs%>}{%<isotope%>,%<atom%>}#*
\DeclareChemNMR{%<cs%>}{%<isotope%>,%<atom%>}#*
\RenewChemNMR{%<cs%>}{%<isotope%>,%<atom%>}#*
\ProvideChemNMR{%<cs%>}{%<isotope%>,%<atom%>}#*


# thermodynamics-module
\state[options]{symbol}
\enthalpy[options](subscript){value}
\enthalpy[options]{value}
\enthalpy(subscript){value}
\enthalpy{value}
\enthalpy*[options](subscript){value}
\enthalpy*[options]{value}
\enthalpy*(subscript){value}
\enthalpy*{value}
\entropy[options](subscript){value}
\entropy[options]{value}
\entropy(subscript){value}
\entropy{value}
\entropy*[options](subscript){value}
\entropy*[options]{value}
\entropy*(subscript){value}
\entropy*{value}
\gibbs[options](subscript){value}
\gibbs[options]{value}
\gibbs(subscript){value}
\gibbs{value}
\gibbs*[options](subscript){value}
\gibbs*[options]{value}
\gibbs*(subscript){value}
\gibbs*{value}

\NewChemState{cs}{options}#*
\RenewChemState{cs}{options}#*
\DeclareChemState{cs}{options}#*
\ProvideChemState{cs}{options}#*


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
