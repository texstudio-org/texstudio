# phfqit package
# Matthew Bertucci 10/6/2021 for v2.0

#include:calc
#include:etoolbox
#include:dsfont
#include:mathrsfs
#include:mathtools
#include:kvoptions

\Hs#m
\Ident#m
\IdentProc{arg}#m
\IdentProc[sub]{arg}#m
\IdentProc[sub from][sub to]{arg}#m
\ee^{arg}#m
\tr#m
\supp#m
\rank#m
\linspan#m
\spec#m
\diag#m
\poly#m
\bit{0 or 1}
\bitstring{string}
\gate{arg}
\AND
\XOR
\CNOT
\NOT
\NOOP
\uu(arg)#m
\UU(arg)#m
\su(arg)#m
\SU(arg)#m
\so(arg)#m
\SO(arg)#m
\SN(arg)#m
\ket{arg}#m
\ket[size cmd]{arg}#m
\ket*{arg}#m
\bra{arg}#m
\bra[size cmd]{arg}#m
\bra*{arg}#m
\braket{arg1}{arg2}#m
\braket[size cmd]{arg1}{arg2}#m
\braket*{arg1}{arg2}#m
\ketbra{arg1}{arg2}#m
\ketbra[size cmd]{arg1}{arg2}#m
\ketbra*{arg1}{arg2}#m
\proj{arg}#m
\proj[size cmd]{arg}#m
\proj*{arg}#m
\matrixel{arg1}{arg2}{arg3}#m
\matrixel[size cmd]{arg1}{arg2}{arg3}#m
\matrixel*{arg1}{arg2}{arg3}#m
\dmatrixel{arg1}{arg2}#m
\dmatrixel[size cmd]{arg1}{arg2}#m
\dmatrixel*{arg1}{arg2}#m
\innerprod{arg1}{arg2}#m
\innerprod[size cmd]{arg1}{arg2}#m
\innerprod*{arg1}{arg2}#m
\abs{arg}#m
\abs[size cmd]{arg}#m
\abs*{arg}#m
\avg{arg}#m
\avg[size cmd]{arg}#m
\avg*{arg}#m
\norm{arg}#m
\norm[size cmd]{arg}#m
\norm*{arg}#m
\intervalc{arg1}{arg2}#m
\intervalc[size cmd]{arg1}{arg2}#m
\intervalc*{arg1}{arg2}#m
\intervalo{arg1}{arg2}#m
\intervalo[size cmd]{arg1}{arg2}#m
\intervalo*{arg1}{arg2}#m
\intervalco{arg1}{arg2}#m
\intervalco[size cmd]{arg1}{arg2}#m
\intervalco*{arg1}{arg2}#m
\intervaloc{arg1}{arg2}#m
\intervaloc[size cmd]{arg1}{arg2}#m
\intervaloc*{arg1}{arg2}#m
\Hmin{target sys}#m
\Hmin[state]{target sys}#m
\Hmin{target sys}[cond sys]#m
\Hmin[state][epsilon]{target sys}[cond sys]#*m
\HH{target sys}#m
\HH[state]{target sys}#m
\HH{target sys}[cond sys]#m
\HH[state][epsilon]{target sys}[cond sys]#*m
\Hzero{target sys}#m
\Hzero[state]{target sys}#m
\Hzero{target sys}[cond sys]#m
\Hzero[state][epsilon]{target sys}[cond sys]#*m
\Hmaxf{target sys}#m
\Hmaxf[state]{target sys}#m
\Hmaxf{target sys}[cond sys]#m
\Hmaxf[state][epsilon]{target sys}[cond sys]#*m
\HSym#*m
\Hbase{Hsym}{subscript}[state][epsilon]{target sys}[cond sys]#*m
\Hfn(arg)#m
\Hfunc(arg)#*m
\Hfnbase{Hsym}{sub}{sup}(arg)#*m
\DD{state}{relative-to state}#m
\DD_{sub}^{sup}{state}{relative-to state}#m
\Dmax{state}{relative-to state}#m
\Dmax[epsilon]{state}{relative-to state}#m
\Dminz{state}{relative-to state}#m
\Dminz[epsilon]{state}{relative-to state}#m
\Dminf{state}{relative-to state}#m
\Dminf[epsilon]{state}{relative-to state}#m
\Dr{state}{relative-to state}#m
\Dr[epsilon]{state}{relative-to state}#m
\Dminz{state}{relative-to state}#m
\Dminz[epsilon]{state}{relative-to state}#m
\Dsym#*m
\Dbase{Dsym}_{sub}^{sup}{state}{relative-to state}#*m
\DCohx{rho}{X}{X'}{GammaX}{GammaX'}#m
\DCohx[epsilon]{rho}{X}{X'}{GammaX}{GammaX'}#m
\emptysystem#m
\DCohxRefSystemName#*
\DCSym#*m
\DCoh{rho}{R}{X'}{GammaR}{GammaX'}#m
\DCoh[epsilon]{rho}{R}{X'}{GammaR}{GammaX'}#m
\DCohbase{Dsym}[epsilon]{rho}{R}{X'}{GammaR}{GammaX'}#*m
\qitobjAddArg#*
\qitobjAddArgx#*
\qitobjParseDone#*
\qitobjDone#*
\DefineQitObject{name}{parse cmd}{render cmd}#*
\DefineTunedQitObject{name}{parse cmd}{render cmd}{first arg}{custom defs}#*
\phfqitParen#*
\phfqitSquareBrackets#*
\phfqitCurlyBrackets#*