# pseudo package
# Matthew Bertucci 2023/01/30 for v1.2.2

#include:expl3
#include:xparse
#include:pgfkeys
#include:array
#include:xcolor
#include:colortbl
#include:l3keys2e
#include:aliascnt
#include:etoolbox
#include:tcolorboxlibraryhooks

\pseudoset{options%keyvals}
\pseudodefinestyle{name%specialDef}{options%keyvals}#s#%pseudostyle

\begin{pseudo}
\begin{pseudo}[options%keyvals]
\begin{pseudo}[options%keyvals][line options]
\end{pseudo}
\begin{pseudo*}
\begin{pseudo*}[options%keyvals]
\begin{pseudo*}[options%keyvals][line options]
\end{pseudo*}

#keyvals:\pseudoset#c,\begin{pseudo}#c,\begin{pseudo*}#c,\pseudodefinestyle#c
begin-tabular=%<commands%>
bol=%<commands%>
bol-append=%<commands%>
bol-prepend=%<commands%>
cnfont=%<command%>
compact#true,false
ct-left=%<text%>
ct-right=%<text%>
ctfont=%<command%>
dim
dim-color=#%color
end-tabular=%<command%>
eol=%<commands%>
eol-append=%<commands%>
eol-prepend=%<commands%>
eqs-pad=##L
eqs-scale=%<number%>
eqs-sep=##L
extra-space=##L
fnfont=%<command%>
font=%<command%>
hd-preamble=%<columns%>
hd-space=##L
hl
hl-color=#%color
hl-warn#true,false
hpad=##L
hsep=##L
idfont=%<command%>
indent-length=##L
indent-level=%<integer%>
indent-mark=%<mark%>
indent-mark-color=#%color
indent-mark-shift=##L
indent-mark-width=##L
indent-text=%<text%>
init=%<commands%>
init-append=%<commands%>
init-prepend=%<commands%>
kw
kwfont=%<command%>
label=%<commands%>
label-align=%<column%>
left-margin=##L
line-height=%<factor%>
partopsep=##L
pause
pos=#t,b
preamble=%<columns%>
prefix=%<commands%>
prevdepth=##L
prfont=%<command%>
ref=%<commands%>
setup=%<commands%>
setup-append=%<commands%>
setup-prepend=%<commands%>
st-left=%<text%>
st-right=%<text%>
starred
start=%<number%>
stfont=%<command%>
topsep=##L
%<key%><%<overlay specification%>>=%<value%>
%pseudostyle
#endkeyvals

\cn{name}
\cnfont#*
\ct{name}
\ctfont#*
\fn{name}
\fn{name}(arguments%formula)
\fnfont#*
\hd{name}(arguments%formula)
\id{name}
\idfont#*
\kw{name}
\kwfont#*
\pr{name}
\pr{name}(arguments%formula)
\prfont#*
\pseudocn{name}#*
\pseudoct{name}#*
\pseudofn{name}#*
\pseudofn{name}(arguments%formula)#*
\pseudohd{name}(arguments%formula)#*
\pseudoid{name}#*
\pseudokw{name}#*
\pseudopr{name}#*
\pseudopr{name}(arguments%formula)#*
\pseudost{string}#*
\st{string}
\stfont#*
\tn{text}

\DeclarePseudoComment{cmd}{comment}#d
\DeclarePseudoConstant{cmd}{constant}#d
\DeclarePseudoFunction{cmd}{function}#d
\DeclarePseudoIdentifier{cmd}{identifier}#d
\DeclarePseudoKeyword{cmd}{keyword}#d
\DeclarePseudoNormal{cmd}{text}#d
\DeclarePseudoProcedure{cmd}{procedure}#d
\DeclarePseudoString{cmd}{string}#d

\RestorePseudoBackslash
\RestorePseudoEq

\rng#m
\dts#m
\eqs#m

\nf#*
\pseudobol#*
\pseudodimcolor#*
\pseudoeol#*
\pseudofont#*
\pseudohdpreamble#*
\pseudohl#*
\pseudohlcolor#*
\pseudohpad#*
\pseudoindent#*
\pseudoindentlength#*
\pseudolabel#*
\pseudolabelalign#*
\pseudopos#*
\pseudopreamble#*
\pseudoprefix#*
\pseudosavelabel#*
\pseudosetup#*
\thepseudoenv#*
\thepseudoline#*

#keyvals:\tcbset,\begin{tcolorbox},\tcbsetforeverylayer,\tcbox,\newtcolorbox,\renewtcolorbox,\newtcbox,\renewtcbox,\tcolorboxenvironment,\tcbsubtitle,\tcbsidebyside,\tcbsubskin,\tcbincludegraphics,\tcbincludepdf,\begin{tcbraster},\begin{tcbitemize},\tcbitem,\begin{tcboxedraster},\begin{tcboxeditemize},\begin{tcblisting},\tcbinputlisting,\newtcblisting,\renewtcblisting,\newtcbinputlisting,\renewtcbinputlisting,\newtcbtheorem,\renewtcbtheorem,\tcboxmath,\tcbhighmath,\usetcboxarray,\consumetcboxarray,\posterbox,\begin{posterboxenv},\tcboxfit,\newtcboxfit,\renewtcboxfit,\DeclareTColorBox,\NewTColorBox,\RenewTColorBox,\ProvideTColorBox,\DeclareTotalTColorBox,\NewTotalTColorBox,\RenewTotalTColorBox,\ProvideTotalTColorBox,\DeclareTCBox,\NewTCBox,\RenewTCBox,\ProvideTCBox,\DeclareTotalTCBox,\NewTotalTCBox,\RenewTotalTCBox,\ProvideTotalTCBox,\DeclareTCBListing,\NewTCBListing,\RenewTCBListing,\ProvideTCBListing,\DeclareTCBInputListing,\NewTCBInputListing,\RenewTCBInputListing,\ProvideTCBInputListing,\DeclareTCBoxFit,\NewTCBoxFit,\RenewTCBoxFit,\ProvideTCBoxFit,\DeclareTotalTCBoxFit,\NewTotalTCBoxFit,\RenewTotalTCBoxFit,\ProvideTotalTCBoxFit,\tcboxverb,\begin{docCommand},\begin{docCommand*},\begin{docCommands},\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\begin{docKey},\begin{docKey*},\begin{docKeys},\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations},\docValue,\docValue*,\docAuxCommand,\docAuxCommand*,\docAuxEnvironment,\docAuxEnvironment*,\docAuxKey,\docAuxKey*,\docCounter,\docCounter*,\docLength,\docLength*,\docColor,\docColor*,\begin{dispExample*},\begin{dispListing*},\tcbdocmarginnote
pseudo/boxed
pseudo/booktabs
pseudo/boxruled
pseudo/filled
pseudo/init=%<commands%>
pseudo/ruled
pseudo/tworuled
#endkeyvals

\pseudodate#S
\pseudoversion#S

# defined by package if booktabs not loaded
\aboverulesep#*
\belowrulesep#*
\heavyrulewidth#*
\lightrulewidth#*

# deprecated
\pseudoeq#S
\pseudoslash#S
