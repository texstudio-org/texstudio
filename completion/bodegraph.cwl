# bodegraph package
# Matthew Bertucci 12/13/2021 for v1.4

#include:ifsym
#include:ifthen
#include:tikz
#include:tikzlibraryshapes
#include:tikzlibrarybackgrounds
#include:tikzlibrarydecorations.markings

\semilog{min-decades}{max-decades}{y-min}{y-max}
\semilog*{min-decades}{max-decades}{y-min}{y-max}
\semilogNG{decades}{amplitude}
\UnitedB
\UniteDegre
\OrdBode{number}
\Unitx
\Unity

#keyvals:\tikzset#c,\begin{tikzpicture}#c
Bode lines/.style={%<options%>}
asymp lines/.style={%<options%>}
semilog lines/.style={%<options%>}
semilog half lines/.style={%<options%>}
semilog label x/.style={%<options%>}
semilog label y/.style={%<options%>}
Black lines/.style={%<options%>}
Black grid/.style={%<options%>}
Black label points/.style={%<options%>}
Black label axes/.style={%<options%>}
Black abaque mag/.style={%<options%>}
Black abaque phase/.style={%<options%>}
ref points/.style={%<options%>}
Nyquist lines/.style={%<options%>}
Nyquist grid/.style={%<options%>}
Nyquist label axes/.style={%<options%>}
Nyquist label points/.style={%<options%>}
Temp lines/.style={%<options%>}
Temp grid/.style={%<options%>}
Temp label axes/.style={%<options%>}
Temp label points/.style={%<options%>}
#endkeyvals

\BodeGraph{%<domain%>}{%<function%>}
\BodeGraph[%<options%>]{%<domain%>}{%<function%>}
\BodeGraph*{%<domain%>}{%<function%>}{[%<node options%>]%<text%>}
\BodeGraph*[%<options%>]{%<domain%>}{%<function%>}{[%<node options%>]%<text%>}
\BodePoint{list}{function}
\BodePoint[options%keyvals]{list}{function}
\POAmp{K}{tau}
\POAmpAsymp{K}{tau}
\POArg{K}{tau}
\POArgAsymp{K}{tau}
\SOAmp{K}{z}{Wn}
\SOAmpAsymp{K}{z}{Wn}
\SOArg{K}{z}{Wn}
\SOArgAsymp{K}{z}{Wn}
\IntAmp{K}
\IntArg{K}
\KAmp{K}
\KArg{K}#*
\RetAmp{Tr}
\RetArg{Tr}
\POgAmp{K}{a1}{a2}{b1}{b2}
\POgArg{K}{a1}{a2}{b1}{b2}
\POgAmpAsymp{K}{a1}{a2}{b1}{b2}
\POgArgAsymp{K}{a1}{a2}{b1}{b2}
\PIAmp{Kp}{Ti}
\PIArg{Kp}{Ti}
\PIAmpAsymp{Kp}{Ti}
\PIArgAsymp{Kp}{Ti}
\PDAmp{Kp}{Td}
\PDArg{Kp}{Td}
\PDAmpAsymp{Kp}{Td}
\PDArgAsymp{Kp}{Td}
\APAmp{Kp}{T1}{a}
\APArg{Kp}{Ti}{a}
\APAmpAsymp{Kp}{T1}{a}
\APArgAsymp{Kp}{Ti}{a}
\RPAmp{Kp}{T1}{a}
\RPArg{Kp}{Ti}{a}
\RPAmpAsymp{Kp}{T1}{a}
\RPArgAsymp{Kp}{Ti}{a}
\PIDAmp{Kp}{Ti}{Td}
\PIDArg{Kp}{Ti}{Td}
\PIDAmpAsymp{Kp}{Ti}{Td}
\PIDArgAsymp{Kp}{Ti}{Td}

\BlackGraph{%<domain%>}{%<argument,module%>}
\BlackGraph[%<options%>]{%<domain%>}{%<argument,module%>}
\BlackGraph*{%<domain%>}{%<argument,module%>}{[%<node options%>]%<text%>}
\BlackGraph*[%<options%>]{%<domain%>}{%<argument,module%>}{[%<node options%>]%<text%>}
\BlackPoint{pulse list}{argument,module}
\BlackPoint[options%keyvals]{pulse list}{argument,module}
\BlackPoint*{pulse list}{argument,module}
\BlackPoint*[options%keyvals]{pulse list}{argument,module}
\BlackText{pulse/pos/text}{argument,module}
\BlackText[options%keyvals]{pulse/pos/text}{argument,module}
\BlackText*{pulse/pos/text}{argument,module}
\BlackText*[options%keyvals]{pulse/pos/text}{argument,module}
\BlackGrid
\BlackGrid*
\valgridBx
\valgridBy

\AbaqueBlack
\AbaqueBlack*
\IsoModule
\IsoModule[amplitudes]
\IsoArgument
\IsoArgument[amplitudes]
\StyleIsoM[options]
\StyleIsoA[options]

\NyquistGraph{%<domain%>}{%<module%>}{%<argument%>}
\NyquistGraph[%<options%>]{%<domain%>}{%<module%>}{%<argument%>}
\NyquistGraph*{%<domain%>}{%<module%>}{%<argument%>}{[%<node options%>]%<text%>}
\NyquistGraph*[%<options%>]{%<domain%>}{%<module%>}{%<argument%>}{[%<node options%>]%<text%>}
\NyquistPoint{pulse list}{module}{argument}
\NyquistPoint[options%keyvals]{pulse list}{module}{argument}
\NyquistPoint*{pulse list}{module}{argument}
\NyquistPoint*[options%keyvals]{pulse list}{module}{argument}
\NyquistText{pulse/pos/text}{module}{argument}
\NyquistText[options%keyvals]{pulse/pos/text}{module}{argument}
\NyquistText*{pulse/pos/text}{module}{argument}
\NyquistText*[options%keyvals]{pulse/pos/text}{module}{argument}
\NyquistGrid
\valgridNx
\valgridNy

\RepTemp{%<domain%>}{%<function%>}
\RepTemp[%<options%>]{%<domain%>}{%<function%>}
\RepTemp*{%<domain%>}{%<function%>}{[%<node options%>]%<text%>}
\RepTemp*[%<options%>]{%<domain%>}{%<function%>}{[%<node options%>]%<text%>}
\TempGrid
\TempGrid[options%keyvals]

\AbaqueTRsecond
\AbaqueDepassement

\CorpsPol#*
\LW#*
\POAmpReel{arg1}{arg2}#*
\POAmpng{arg1}{arg2}#*
\POArgReel{arg1}{arg2}#*
\POBlack{arg1}{arg2}#*
\SOAmpReel{arg1}{arg2}{arg3}#*
\SOArgReel{arg1}{arg2}{arg3}#*
\SOBlack{arg1}{arg2}{arg3}#*
\SOncArg{arg1}{arg2}{arg3}{arg4}#*
\UnitS#*
\ValK#*
\ValW#*
\ValZ#*
\Valsuivante#*
\Xmax#*
\puce#*
\theidGnuplo*
\valgridx#*
\valgridy#*
\valmaxBf#*
\valmaxx#*
\valmaxy#*
\valpas#*
\valpi#*

\AbaqueBlackNoStar#S
\AbaqueBlackStar#S
\BlackGraphNoText#S
\BlackGraphText#S
\BlackGridNoStar#S
\BlackGridStar#S
\BlackPointNoPos#S
\BlackPointPos#S
\BlackTextNoPoint#S
\BlackTextPoint#S
\BodeAmp#S
\BodeAmpPointA#S
\BodeArg#S
\BodeGraphNoText#S
\BodeGraphText#S
\NyquistGraphNoText#S
\NyquistGraphText#S
\NyquistGridNoStar#S
\NyquistGridStar#S
\NyquistPointNoPos#S
\NyquistPointPos#S
\NyquistTextNoPoint#S
\NyquistTextPoint#S
\RepTempNoText#S
\RepTempText#S
\TempGridNoStar#S
\TempGridStar#S
\semilogNS#S
\semilogS#S
