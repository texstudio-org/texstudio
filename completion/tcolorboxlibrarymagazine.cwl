# magazine tcolorboxlibrary
# 2023/02/10 for v6.0.0

#include:tcolorboxlibrarybreakable

\newboxarray{name}
\boxarrayreset
\boxarrayreset[name]
\boxarrayclear
\boxarrayclear[name]
\begin{boxarraystore}{name}
\end{boxarraystore}
\boxarraygetsize{macro%cmd}#d
\boxarraygetsize[name]{macro%cmd}#d
\useboxarray{index}
\useboxarray[name]{index}
\usetcboxarray{index}{options%keyvals}
\usetcboxarray[name]{index}{options%keyvals}
\consumeboxarray{index}
\consumeboxarray[name]{index}
\consumetcboxarray{index}{options%keyvals}
\consumetcboxarray[name]{index}{options%keyvals}
\boxarraygetbox{macro%cmd}{index}#d
\boxarraygetbox[name]{macro%cmd}{index}#d
\ifboxarrayempty{index}{true}{false}
\ifboxarrayempty[name]{index}{true}{false}
\boxarraygetwidth{macro%cmd}{index}#d
\boxarraygetwidth[name]{macro%cmd}{index}#d
\boxarraygetheight{macro%cmd}{index}#d
\boxarraygetheight[name]{macro%cmd}{index}#d
\boxarraygetdepth{macro%cmd}{index}#d
\boxarraygetdepth[name]{macro%cmd}{index}#d
\boxarraygettotalheight{macro%cmd}{index}#d
\boxarraygettotalheight[name]{macro%cmd}{index}#d

#keyvals:\tcbset,\begin{tcolorbox},\tcbsetforeverylayer,\tcbox,\newtcolorbox,\renewtcolorbox,\newtcbox,\renewtcbox,\tcolorboxenvironment,\tcbsubtitle,\tcbsidebyside,\tcbsubskin,\tcbincludegraphics,\tcbincludepdf,\begin{tcbraster},\begin{tcbitemize},\tcbitem,\begin{tcboxedraster},\begin{tcboxeditemize},\begin{tcblisting},\tcbinputlisting,\newtcblisting,\renewtcblisting,\newtcbinputlisting,\renewtcbinputlisting,\NewTcbTheorem,\newtcbtheorem,\RenewTcbTheorem,\renewtcbtheorem,\ProvideTcbTheorem,\DeclareTcbTheorem,\tcboxmath,\tcbhighmath,\usetcboxarray,\consumetcboxarray,\posterbox,\begin{posterboxenv},\tcboxfit,\newtcboxfit,\renewtcboxfit,\DeclareTColorBox,\NewTColorBox,\RenewTColorBox,\ProvideTColorBox,\DeclareTotalTColorBox,\NewTotalTColorBox,\RenewTotalTColorBox,\ProvideTotalTColorBox,\DeclareTCBox,\NewTCBox,\RenewTCBox,\ProvideTCBox,\DeclareTotalTCBox,\NewTotalTCBox,\RenewTotalTCBox,\ProvideTotalTCBox,\DeclareTCBListing,\NewTCBListing,\RenewTCBListing,\ProvideTCBListing,\DeclareTCBInputListing,\NewTCBInputListing,\RenewTCBInputListing,\ProvideTCBInputListing,\DeclareTCBoxFit,\NewTCBoxFit,\RenewTCBoxFit,\ProvideTCBoxFit,\DeclareTotalTCBoxFit,\NewTotalTCBoxFit,\RenewTotalTCBoxFit,\ProvideTotalTCBoxFit,\tcboxverb,\begin{docCommand},\begin{docCommand*},\begin{docCommands},\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\begin{docKey},\begin{docKey*},\begin{docKeys},\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations},\docValue,\docValue*,\docAuxCommand,\docAuxCommand*,\docAuxEnvironment,\docAuxEnvironment*,\docAuxKey,\docAuxKey*,\docCounter,\docCounter*,\docLength,\docLength*,\docColor,\docColor*,\begin{dispExample*},\begin{dispListing*},\tcbdocmarginnote
reset box array
reset box array=%<name%>
store to box array
store to box array=%<name%>
reset and store to box array
reset and store to box array=%<name%>
do not store to box array
#endkeyvals
