# minifp package
# Matthew Bertucci 9/30/2021 for v0.96

\MFPloadextra#*
\startMFPprogram
\stopMFPprogram

\MFPadd{num1}{num2}{cmd}#d
\MFPsub{num1}{num2}{cmd}#d
\MFPmul{num1}{num2}{cmd}#d
\MFPmpy{num1}{num2}{cmd}#d
\MFPdiv{num1}{num2}{cmd}#d
\MFPmin{num1}{num2}{cmd}#d
\MFPmax{num1}{num2}{cmd}#d

\MFPchs{num}{cmd}#d
\MFPabs{num}{cmd}#d
\MFPdbl{num}{cmd}#d
\MFPhalve{num}{cmd}#d
\MFPint{num}{cmd}#d
\MFPfrac{num}{cmd}#d
\MFPfloor{num}{cmd}#d
\MFPceil{num}{cmd}#d
\MFPsgn{num}{cmd}#d
\MFPsq{num}{cmd}#d
\MFPinv{num}{cmd}#d
\MFPincr{num}{cmd}#d
\MFPdecr{num}{cmd}#d
\MFPzero{num}{cmd}#d
\MFPstore{num}{cmd}#d

\MFPnoop

\MFPpi
\MFPe
\MFPphi

\MFPchk{num}
\MFPcmp{num1}{num2}
\IFneg{true text}{false text}
\IFzero{true text}{false text}
\IFpos{true text}{false text}
\IFlt{true text}{false text}
\IFeq{true text}{false text}
\IFgt{true text}{false text}

\MFPtruncate{integer}{num}{cmd}#d
\MFPround{integer}{num}{cmd}#d
\MFPstrip{num}{cmd}#d

\Rpush{num}
\Rpop{cmd}#d

\Radd
\Rsub
\Rmul
\Rmpy
\Rdiv
\Rmin
\Rmax
\Rchs
\Rabs
\Rdbl
\Rhalve
\Rint
\Rfrac
\Rfloor
\Rceil
\Rsgn
\Rsq
\Rinv
\Rincr
\Rdecr
\Rzero

\Rnoop

\Rchk
\Rcmp

\Rdup
\Rexch

\Export{macro}
\Global{macro}
\ExportStack
\GlobalStack

\EndofStack#*
\ZeroOverZeroInt#*
\ZeroOverZeroFrac#*
\xOverZeroInt#*
\xOverZeroFrac#*

\MaxRealInt#*
\MaxRealFrac#*

#ifOption:extra
\MFPsin{num}{cmd}#d
\MFPcos{num}{cmd}#d
\MFPangle{x}{y}{cmd}#d
\MFPrad{num}{cmd}#d
\MFPdeg{num}{cmd}#d
\MFPlog{num}{cmd}#d
\MFPln{num}{cmd}#d
\MFPexp{num}{cmd}#d
\MFPsqrt{num}{cmd}#d
\MFPrand{num}{cmd}#d
\MFPpow{num}{integer}{cmd}#d
\MFPsetseed{integer}
\MFPrandgenA
\MFPrandgenB
\MFPrandgenC
\Rsin
\Rcos
\Rangle
\Rrad
\Rdeg
\Rlog
\Rln
\Rexp
\Rsqrt
\Rrand
\Rpow
\LogOfZeroInt#*
\LogOfZeroFrac#*
#endif

\MFPsin{num}{cmd}#Sd
\MFPcos{num}{cmd}#Sd
\MFPangle{x}{y}{cmd}#Sd
\MFPrad{num}{cmd}#Sd
\MFPdeg{num}{cmd}#Sd
\MFPlog{num}{cmd}#Sd
\MFPln{num}{cmd}#Sd
\MFPexp{num}{cmd}#Sd
\MFPsqrt{num}{cmd}#Sd
\MFPrand{num}{cmd}#Sd
\MFPpow{num}{integer}{cmd}#Sd
\MFPsetseed{integer}#S
\MFPrandgenA#S
\MFPrandgenB#S
\MFPrandgenC#S
\Rsin#S
\Rcos#S
\Rangle#S
\Rrad#S
\Rdeg#S
\Rlog#S
\Rln#S
\Rexp#S
\Rsqrt#S
\Rrand#S
\Rpow#S
\LogOfZeroInt#S
\LogOfZeroFrac#S