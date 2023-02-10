# fitting tcolorboxlibrary
# 2023/02/10 for v6.0.0

\tcboxfit{box content%text}
\tcboxfit[options%keyvals]{box content%text}
\newtcboxfit{cmd}{options%keyvals}#d
\newtcboxfit{cmd}[args]{options%keyvals}#d
\newtcboxfit{cmd}[args][default]{options%keyvals}#d
\newtcboxfit[init options]{cmd}{options%keyvals}#d
\newtcboxfit[init options]{cmd}[args]{options%keyvals}#*d
\newtcboxfit[init options]{cmd}[args][default]{options%keyvals}#*d
\renewtcboxfit{cmd}{options%keyvals}
\renewtcboxfit{cmd}[args]{options%keyvals}
\renewtcboxfit{cmd}[args][default]{options%keyvals}
\renewtcboxfit[init options]{cmd}{options%keyvals}
\renewtcboxfit[init options]{cmd}[args]{options%keyvals}#*
\renewtcboxfit[init options]{cmd}[args][default]{options%keyvals}#*
\DeclareTCBoxFit{cmd}{xargs}{options%keyvals}#d
\DeclareTCBoxFit[init options]{cmd}{xargs}{options%keyvals}#d
\NewTCBoxFit{cmd}{xargs}{options%keyvals}#d
\NewTCBoxFit[init options]{cmd}{xargs}{options%keyvals}#d
\RenewTCBoxFit{cmd}{xargs}{options%keyvals}
\RenewTCBoxFit[init options]{cmd}{xargs}{options%keyvals}
\ProvideTCBoxFit{cmd}{xargs}{options%keyvals}#d
\ProvideTCBoxFit[init options]{cmd}{xargs}{options%keyvals}#d
\DeclareTotalTCBoxFit{cmd}{xargs}{options%keyvals}{content%text}#d
\DeclareTotalTCBoxFit[init options]{cmd}{xargs}{options%keyvals}{content%text}#d
\NewTotalTCBoxFit{cmd}{xargs}{options%keyvals}{content%text}#d
\NewTotalTCBoxFit[init options]{cmd}{xargs}{options%keyvals}{content%text}#d
\RenewTotalTCBoxFit{cmd}{xargs}{options%keyvals}{content%text}
\RenewTotalTCBoxFit[init options]{cmd}{xargs}{options%keyvals}{content%text}
\ProvideTotalTCBoxFit{cmd}{xargs}{options%keyvals}{content%text}#d
\ProvideTotalTCBoxFit[init options]{cmd}{xargs}{options%keyvals}{content%text}#d
\tcbfitdim#L
\tcbfontsize{factor}
\tcbfitsteps

#keyvals:\tcbset,\begin{tcolorbox},\tcbsetforeverylayer,\tcbox,\newtcolorbox,\renewtcolorbox,\newtcbox,\renewtcbox,\tcolorboxenvironment,\tcbsubtitle,\tcbsidebyside,\tcbsubskin,\tcbincludegraphics,\tcbincludepdf,\begin{tcbraster},\begin{tcbitemize},\tcbitem,\begin{tcboxedraster},\begin{tcboxeditemize},\begin{tcblisting},\tcbinputlisting,\newtcblisting,\renewtcblisting,\newtcbinputlisting,\renewtcbinputlisting,\NewTcbTheorem,\newtcbtheorem,\RenewTcbTheorem,\renewtcbtheorem,\ProvideTcbTheorem,\DeclareTcbTheorem,\tcboxmath,\tcbhighmath,\usetcboxarray,\consumetcboxarray,\posterbox,\begin{posterboxenv},\tcboxfit,\newtcboxfit,\renewtcboxfit,\DeclareTColorBox,\NewTColorBox,\RenewTColorBox,\ProvideTColorBox,\DeclareTotalTColorBox,\NewTotalTColorBox,\RenewTotalTColorBox,\ProvideTotalTColorBox,\DeclareTCBox,\NewTCBox,\RenewTCBox,\ProvideTCBox,\DeclareTotalTCBox,\NewTotalTCBox,\RenewTotalTCBox,\ProvideTotalTCBox,\DeclareTCBListing,\NewTCBListing,\RenewTCBListing,\ProvideTCBListing,\DeclareTCBInputListing,\NewTCBInputListing,\RenewTCBInputListing,\ProvideTCBInputListing,\DeclareTCBoxFit,\NewTCBoxFit,\RenewTCBoxFit,\ProvideTCBoxFit,\DeclareTotalTCBoxFit,\NewTotalTCBoxFit,\RenewTotalTCBoxFit,\ProvideTotalTCBoxFit,\tcboxverb,\begin{docCommand},\begin{docCommand*},\begin{docCommands},\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\begin{docKey},\begin{docKey*},\begin{docKeys},\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations},\docValue,\docValue*,\docAuxCommand,\docAuxCommand*,\docAuxEnvironment,\docAuxEnvironment*,\docAuxKey,\docAuxKey*,\docCounter,\docCounter*,\docLength,\docLength*,\docColor,\docColor*,\begin{dispExample*},\begin{dispListing*},\tcbdocmarginnote
fit
fit to=%<width%> and %<height%>
fit to height=##L
fit basedim=##L
fit skip=%<factor%>
fit fontsize macros
fit height plus=##L
fit width plus=##L
fit width from=%<min%> to %<max%>
fit height from=%<min%> to %<max%>
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=%<number%>
fit maxfontdiff=##L
fit maxfontdiffgap=##L
fit maxwidthdiff=##L
fit maxwidthdiffgap=##L
fit warning=#off,on,final
#endkeyvals
