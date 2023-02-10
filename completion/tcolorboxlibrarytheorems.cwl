# theorems tcolorboxlibrary
# 2023/02/10 for v6.0.0

#include:amsmath

\NewTcbTheorem{envname}{display name}{options%keyvals}{prefix}#N
\NewTcbTheorem[init options]{envname}{display name}{options%keyvals}{prefix}#N
\newtcbtheorem{envname}{display name}{options%keyvals}{prefix}#N
\newtcbtheorem[init options]{envname}{display name}{options%keyvals}{prefix}#N
\RenewTcbTheorem{envname}{display name}{options%keyvals}{prefix}
\RenewTcbTheorem[init options]{envname}{display name}{options%keyvals}{prefix}
\renewtcbtheorem{envname}{display name}{options%keyvals}{prefix}
\renewtcbtheorem[init options]{envname}{display name}{options%keyvals}{prefix}
\ProvideTcbTheorem{envname}{display name}{options%keyvals}{prefix}#N
\ProvideTcbTheorem[init options]{envname}{display name}{options%keyvals}{prefix}#N
\DeclareTcbTheorem{envname}{display name}{options%keyvals}{prefix}#N
\DeclareTcbTheorem[init options]{envname}{display name}{options%keyvals}{prefix}#N
\tcboxmath{mathematical box content%formula}
\tcboxmath[options%keyvals]{mathematical box content%formula}
\tcbhighmath{mathematical box content%formula}
\tcbhighmath[options%keyvals]{mathematical box content%formula}

#keyvals:\tcbset,\begin{tcolorbox},\tcbsetforeverylayer,\tcbox,\newtcolorbox,\renewtcolorbox,\newtcbox,\renewtcbox,\tcolorboxenvironment,\tcbsubtitle,\tcbsidebyside,\tcbsubskin,\tcbincludegraphics,\tcbincludepdf,\begin{tcbraster},\begin{tcbitemize},\tcbitem,\begin{tcboxedraster},\begin{tcboxeditemize},\begin{tcblisting},\tcbinputlisting,\newtcblisting,\renewtcblisting,\newtcbinputlisting,\renewtcbinputlisting,\NewTcbTheorem,\newtcbtheorem,\RenewTcbTheorem,\renewtcbtheorem,\ProvideTcbTheorem,\DeclareTcbTheorem,\tcboxmath,\tcbhighmath,\usetcboxarray,\consumetcboxarray,\posterbox,\begin{posterboxenv},\tcboxfit,\newtcboxfit,\renewtcboxfit,\DeclareTColorBox,\NewTColorBox,\RenewTColorBox,\ProvideTColorBox,\DeclareTotalTColorBox,\NewTotalTColorBox,\RenewTotalTColorBox,\ProvideTotalTColorBox,\DeclareTCBox,\NewTCBox,\RenewTCBox,\ProvideTCBox,\DeclareTotalTCBox,\NewTotalTCBox,\RenewTotalTCBox,\ProvideTotalTCBox,\DeclareTCBListing,\NewTCBListing,\RenewTCBListing,\ProvideTCBListing,\DeclareTCBInputListing,\NewTCBInputListing,\RenewTCBInputListing,\ProvideTCBInputListing,\DeclareTCBoxFit,\NewTCBoxFit,\RenewTCBoxFit,\ProvideTCBoxFit,\DeclareTotalTCBoxFit,\NewTotalTCBoxFit,\RenewTotalTCBoxFit,\ProvideTotalTCBoxFit,\tcboxverb,\begin{docCommand},\begin{docCommand*},\begin{docCommands},\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\begin{docKey},\begin{docKey*},\begin{docKeys},\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations},\docValue,\docValue*,\docAuxCommand,\docAuxCommand*,\docAuxEnvironment,\docAuxEnvironment*,\docAuxKey,\docAuxKey*,\docCounter,\docCounter*,\docLength,\docLength*,\docColor,\docColor*,\begin{dispExample*},\begin{dispListing*},\tcbdocmarginnote
separator sign=%<sign%>
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color
description color=#%color
description font
description font=%<text%>
description formatter
description formatter=%<macro%>
terminator sign=%<sign%>
terminator sign colon
terminator sign dash
terminator sign none
label separator=%<separator%>
theorem full label supplement={%<style%>}
theorem label supplement={%<style%>}
theorem hanging indent=##L
theorem name and number
theorem number and name
theorem name
theorem number
theorem={%<display name%>}{%<counter%>}{%<title%>}{%<marker%>}
highlight math style={%<options%>}
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
#endkeyvals
