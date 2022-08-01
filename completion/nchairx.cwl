# nchairx package
# Matthew Bertucci 2022/08/01 for v1.0.0

#include:xkeyval
#include:amsmath
#include:amssymb
#include:suffix
#include:mathtools
#include:ntheorem
# loads thmmarks option of ntheorem
#include:graphicx
#include:enumitem
#include:tensor
#include:aliascnt

#keyvals:\usepackage/nchairx#c
noMath
#endkeyvals

\mathscr{text%plain}#m

\begin{claim}
\begin{claim}[heading%text]
\end{claim}
\begin{nnclaim}
\begin{nnclaim}[heading%text]
\end{nnclaim}
\begin{corollary}
\begin{corollary}[heading%text]
\end{corollary}
\begin{nncorollary}
\begin{nncorollary}[heading%text]
\end{nncorollary}
\begin{definition}
\begin{definition}[heading%text]
\end{definition}
\begin{nndefinition}
\begin{nndefinition}[heading%text]
\end{nndefinition}
\begin{lemma}
\begin{lemma}[heading%text]
\end{lemma}
\begin{nnlemma}
\begin{nnlemma}[heading%text]
\end{nnlemma}
\begin{proposition}
\begin{proposition}[heading%text]
\end{proposition}
\begin{nnproposition}
\begin{nnproposition}[heading%text]
\end{nnproposition}
\begin{theorem}
\begin{theorem}[heading%text]
\end{theorem}
\begin{nntheorem}
\begin{nntheorem}[heading%text]
\end{nntheorem}
\begin{conjecture}
\begin{conjecture}[heading%text]
\end{conjecture}
\begin{nnconjecture}
\begin{nnconjecture}[heading%text]
\end{nnconjecture}
\begin{convention}
\begin{convention}[heading%text]
\end{convention}
\begin{nnconvention}
\begin{nnconvention}[heading%text]
\end{nnconvention}
\begin{example}
\begin{example}[heading%text]
\end{example}
\begin{nnexample}
\begin{nnexample}[heading%text]
\end{nnexample}
\begin{notation}
\begin{notation}[heading%text]
\end{notation}
\begin{nnnotation}
\begin{nnnotation}[heading%text]
\end{nnnotation}
\begin{question}
\begin{question}[heading%text]
\end{question}
\begin{nnquestion}
\begin{nnquestion}[heading%text]
\end{nnquestion}
\begin{remark}
\begin{remark}[heading%text]
\end{remark}
\begin{nnremark}
\begin{nnremark}[heading%text]
\end{nnremark}
\begin{exercise}
\begin{exercise}[heading%text]
\end{exercise}
\begin{nnexercise}
\begin{nnexercise}[heading%text]
\end{nnexercise}
\begin{maintheorem}
\begin{maintheorem}[heading%text]
\end{maintheorem}
\begin{nnmaintheorem}
\begin{nnmaintheorem}[heading%text]
\end{nnmaintheorem}

\begin{proof}
\begin{proof}[heading%text]
\end{proof}
\begin{subproof}
\begin{subproof}[heading%text]
\end{subproof}

\begin{hint}
\end{hint}

\begin{claimlist}
\begin{claimlist}[options%keyvals]
\end{claimlist}
\begin{conjecturelist}
\begin{conjecturelist}[options%keyvals]
\end{conjecturelist}
\begin{conventionlist}
\begin{conventionlist}[options%keyvals]
\end{conventionlist}
\begin{corollarylist}
\begin{corollarylist}[options%keyvals]
\end{corollarylist}
\begin{definitionlist}
\begin{definitionlist}[options%keyvals]
\end{definitionlist}
\begin{examplelist}
\begin{examplelist}[options%keyvals]
\end{examplelist}
\begin{exerciselist}
\begin{exerciselist}[options%keyvals]
\end{exerciselist}
\begin{lemmalist}
\begin{lemmalist}[options%keyvals]
\end{lemmalist}
\begin{maintheoremlist}
\begin{maintheoremlist}[options%keyvals]
\end{maintheoremlist}
\begin{notationlist}
\begin{notationlist}[options%keyvals]
\end{notationlist}
\begin{propositionlist}
\begin{propositionlist}[options%keyvals]
\end{propositionlist}
\begin{questionlist}
\begin{questionlist}[options%keyvals]
\end{questionlist}
\begin{remarklist}
\begin{remarklist}[options%keyvals]
\end{remarklist}
\begin{theoremlist}
\begin{theoremlist}[options%keyvals]
\end{theoremlist}
\begin{prooflist}
\begin{prooflist}[options%keyvals]
\end{prooflist}

\begin{cptenum}
\begin{cptenum}[options%keyvals]
\end{cptenum}
\begin{cptitem}
\begin{cptitem}[options%keyvals]
\end{cptitem}
\begin{cptdesc}
\begin{cptdesc}[options%keyvals]
\end{cptdesc}

#keyvals:\begin{claimlist}#c,\begin{conjecturelist}#c,\begin{conventionlist}#c,\begin{corollarylist}#c,\begin{definitionlist}#c,\begin{examplelist}#c,\begin{exerciselist}#c,\begin{lemmalist}#c,\begin{maintheoremlist}#c,\begin{notationlist}#c,\begin{propositionlist}#c,\begin{questionlist}#c,\begin{remarklist}#c,\begin{theoremlist}#c,\begin{prooflist}#c,\begin{cptenum}#c,\begin{cptitem}#c,\begin{cptdesc}#c
topsep=##L
partopsep=##L
parsep=##L
itemsep=##L
leftmargin=##L
rightmargin=##L
listparindent=##L
labelwidth=##L
labelsep=##L
itemindent=##L
label=%<commands%>
label*=%<commands%>
ref=%<commands%>
font=%<commands%>
format=%<commands%>
align=#left,right,parleft
labelindent=##L
left=%<labelindent%>
left=%<labelindent%> .. %<leftmargin%>
widest
widest=%<string%>
widest*=%<integer%>
labelsep*=##L
labelindent*=##L
start=%<integer%>
resume
resume=%<series name%>
resume*
resume*=%<series name%>
series=%<series name%>
beginpenalty=%<integer%>
midpenalty=%<integer%>
endpenalty=%<integer%>
before=%<code%>
before*=%<code%>
after=%<code%>
after*=%<code%>
first=%<code%>
first*=%<code%>
style=#standard,unboxed,nextline,sameline,multiline
noitemsep
nosep
wide
wide=%<parindent%>
itemjoin=%<string%>
itemjoin*=%<string%>
afterlabel=%<string%>
mode=#unboxed,boxed
#endkeyvals

\nchairxheader
\nchairxlogo{width}

\chairxfonts{keyvals}

#keyvals:\chairxfonts
algebrafont=%<math font command%>
basisfont=%<math font command%>
categoryfont=%<math font command%>
categorynamefont=%<math font command%>
fieldfont=%<math font command%>
filterfont=%<math font command%>
functorfont=%<math font command%>
groupfont=%<math font command%>
groupoidfont=%<math font command%>
gerstenhaberfont=%<math font command%>
hilbertfont=%<math font command%>
liealgfont=%<math font command%>
modulefont=%<math font command%>
prehilbfont=%<math font command%>
operatorfont=%<math font command%>
ringfont=%<math font command%>
scriptfont=%<math font command%>
sheaffont=%<math font command%>
spacefont=%<math font command%>
topologyfont=%<math font command%>
#endkeyvals

\vast#m
\Vast#m
\vastl#m
\vastm#m
\vastr#m
\Vastl#m
\Vastm#m
\Vastr#m

\decorate{%<symbol%>}{%<^sup1_sub1^sup2_sub2...%>}#m
\decorate[%<pre-indices%>]{%<symbol%>}{%<^sup1_sub1^sup2_sub2...%>}#m
\deco{ul}{ll}{arg}{ur}{lr}#m
\deco[size-cmd]{ul}{ll}{arg}{ur}{lr}#m
\script{text%plain}#m
\I#m
\E#m
\D#m
\cc{arg}#m
\sign#m
\RE#m
\IM#m
\Unit#m
\const#m
\canonical#m
\pt#m

\at{arg}#m
\at[size-cmd]{arg}#m

\Map#m
\Bij#m
\argument#m
\domain#m
\range#m
\id#m
\pr#m
\inv#m
\ev#m
\image#m
\graph#m
\coimage#m
\coker#m
\operator#m

\later#m
\earlier#m

\bigplus#m
\bigtimes#m
\biprod#m

\smiley#m
\frownie#m
\heart#m

\field{letter}#m
\ring{letter}#m
\group{letter}#m
\algebra{letter}#m
\module{letter}#m
\liealg{letter}#m
\MC
\gerstenhaber{letter}#m

\Pol#m
\lmult#m
\rmult#m
\Lmult#m
\Rmult#m
\Center#m
\ad#m
\Ad#m
\Conj#m
\acts#m
\racts#m
\Char#m
\modulo#m
\Clifford#m
\cClifford#m
\Der#m
\Der*#m
\InnDer#m
\InnDer*#m
\OutDer#m
\OutDer*#m
\InnAut#m
\InnAut*#m
\OutAut#m
\OutAut*#m
\formal{arg}#m
\laurent{arg}#m
\sweedler{arg}#m

\algebras#m
\algebras*#m
\Algebras#m
\Algebras*#m
\reps#m
\reps*#m
\Reps#m
\Reps*#m
\PoissonAlg#m
\PoissonAlg*#m
\modules#m
\modules*#m
\Leftmodules#m
\Rightmodules#m
\Modules#m
\Modules#m
\LeftModules#m
\RightModules#m
\Bimodules#m
\Bimodules*#m
\Rings#m
\Groups#m
\Ab#m
\Lattices#m
\Sets#m
\Vect#m
\LieAlgs#m
\Posets#m
\Directed#m
\GSets#m
\GSets[group]#m
\Groupoids#m

\vol#m
\complete{arg}#m
\Ball#m
\abs{arg}#m
\abs[size-cmd]{arg}#m
\abs*{arg}#m
\norm{arg}#m
\norm[size-cmd]{arg}#m
\norm*{arg}#m
\supnorm{arg}#m
\supnorm[size-cmd]{arg}#m
\supnorm*{arg}#m
\expands#m
\expands[scale]#m

\std#m
\Weyl#m
\Op#m
\Opstd#m
\OpWeyl#m

\spacename{arg}#m
\Bounded#m
\Continuous#m
\Contbound#m
\Fun#m
\Fun[sup]#m
\Cinfty#m
\Comega#m
\Holomorphic#m
\AntiHolomorphic#m
\Schwartz#m
\Riemann#m

\singsupp#m
\seminorm{arg}#m
\ord#m
\conv#m
\extreme#m

\hilbert{arg}#m
\prehilb{arg}#m
\Adjointable#m
\Adjointable[sub]#m
\Finite#m
\Finite[sub]#m
\Compact#m
\Compact[sub]#m
\opdomain#m
\spec#m
\closure{arg}#m
\res#m
\Res#m
\specrad#m
\slim#m
\wlim#m

\bra{arg}#m
\bra[size-cmd]{arg}#m
\bra*{arg}#m
\ket{arg}#m
\ket[size-cmd]{arg}#m
\ket*{arg}#m
\braket{arg1}{arg2}#m
\braket[size-cmd]{arg1}{arg2}#m
\ketbra{arg1}{arg2}#m
\ketbra[size-cmd]{arg1}{arg2}#m

\Spec#m
\Rad#m
\ind#m

\Measurable#m
\Meas#m
\BoundMeas#m
\Lp#m
\Lp[sup]#m
\Lone#m
\Ltwo#m
\Linfty#m
\Intp#m
\Intp[sup]#m
\Intone#m
\Inttwo#m
\Intinfty#m
\essrange#m
\esssup#m
\esssupnorm{arg}#m
\esssupnorm[size-cmd]{arg}#m
\esssupnorm*{arg}#m
\ac#m
\sing#m

\indlim#m
\projlim#m

\category{arg}#m
\categoryname{arg}#m
\functor{arg}#m
\groupoid{arg}#m
\source#m
\target#m
\unit#m
\opp#m
\asso#m
\Hom#m
\End#m
\Aut#m
\Aut*#m
\Iso#m
\Iso*#m
\Obj#m
\Morph#m

\colim#m

\Lie#m
\Schouten{arg}#m
\Schouten[size-cmd]{arg}#m
\Schouten*{arg}#m
\Forms#m
\ZdR#m
\BdR#m
\HdR#m
\Diffeo#m
\Diffop#m
\loc#m
\germ#m
\prol#m
\NRbracket{arg}#m
\NRbracket[size-cmd]{arg}#m
\NRbracket*{arg}#m
\FNbracket{arg}#m
\FNbracket[size-cmd]{arg}#m
\FNbracket*{arg}#m
\Manifolds#m

\lefttriv#m
\righttriv#m
\Gau#m
\Conn#m
\ratio#m
\Parallel#m
\CE#m
\HCE#m
\fund#m
\Universal#m
\BCH#m
\LieGroups#m
\Principal#m
\GPrincipal#m
\Fiber#m
\FFiber#m
\FFiber[fiber]#m
\Pin#m
\Spin#m

\nablaLC#m
\Laplace#m
\dAlembert#m
\feynman{arg}#m
\Dirac#m
\rotation#m
\curl#m
\divergence#m
\gradient#m
\Tor#m
\Ric#m
\scal#m
\Riem#m
\Hessian#m
\hodge#m

\Nijenhuis#m
\del#m
\delbar#m
\FS#m

\Lift#m
\ver#m
\hor#m
\Ver#m
\Hor#m
\Sec#m
\Sec[sup]#m
\Secinfty#m
\HolSec#m
\SymD#m
\Densities#m
\Densities[sup]#m
\MeasurableSections#m
\IntpSections#m
\IntpSections[sup]#m
\IntegrableSections#m
\Translation#m
\frames{arg}#m
\Frames#m
\FDiff#m

\Sympl#m
\Jacobiator#m
\Jacobiator[sub]#m
\red#m
\Hess#m
\KKS#m
\Courant{arg}#m
\Courant[size-cmd]{arg}#m
\Courant*{arg}#m
\Dorfman{arg}#m
\Dorfman[size-cmd]{arg}#m
\Dorfman*{arg}#m
\Dir#m
\Forward#m
\Backward#m
\Tangent#m
\MWreduction#m
\Mon#m
\Hol#m

\tr#m
\rank#m
\codim#m
\diag#m
\Trans#m
\Mat#m
\SymMat#m
\ann#m
\Span#m
\Span[sub]#m
\basis{arg}#m

\tensor#m
\tensor[sub]#m
\Tensor#m
\Anti#m
\Sym#m
\Symmetrizer#m
\AntiSymmetrizer#m
\ins#m
\jns#m
\insa#m
\inss#m
\degs#m
\dega#m

\SP{arg}#m
\SP[size-cmd]{arg}#m
\SP*{arg}#m
\littlepara#m
\IP{ul}{ll}{arg}{ur}{lr}#m
\IP[size-cmd]{ul}{ll}{arg}{ur}{lr}#m

\EX#m
\Var#m
\Cov#m
\Cor#m

\cl#m
\scl#m
\interior#m
\boundary#m
\supp#m
\dist#m
\topology{letter}#m
\filter{letter}#m
\sheaf{letter}#m
\Sections#m
\HOM#m
\etale{arg}#m
\etale[size-cmd]{arg}#m
\etale*{arg}#m
\topological#m
\Topological#m
\Sheaves#m
\PreSheaves#m
\Etale#m

\claimautorefname#*
\conjectureautorefname#*
\conventionautorefname#*
\corollaryautorefname#*
\definitionautorefname#*
\exampleautorefname#*
\exerciseautorefname#*
\lemmaautorefname#*
\maintheoremautorefname#*
\notationautorefname#*
\propositionautorefname#*
\questionautorefname#*
\remarkautorefname#*
\thmautorefname#*

\originalleft#S
\originalright#S
\originaltensor#S

# from thmmarks option of ntheorem
\theoremsymbol{symbol}
\theendNonectr#S
\thecurrNonectr#S
\ifsetendmark#S
\setendmarktrue#S
\setendmarkfalse#S