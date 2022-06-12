# metre package
# Matthew Bertucci 2022/06/08 for v1.0

#include:relsize

#keyvals:\usepackage/metre#c,\MetraStyle,\ms
st
en
En
#endkeyvals

\metra{metrical-symbols}
\metra[setup]{metrical-symbols}
\r
\r[factor]
\R
\R[factor]
\t
\t[factor]
\T
\T[factor]
\s
\v
\k
\K
\q
\Q
\d
\S{chars}
\S[factor]{chars}
\n{above}{symbol}
\ni{below}{symbol}
\N{above}{symbol}{below}
\numeri{chars}
\m
\b
\a
\ma
\bba
\bm
\mb
\bbmb
\bbm
\bbmx
\bb
\bbb
\mbb
\mbbx
\pm
\ppm
\pppm
\vppm
\vpppm
\tsmb
\tsbm
\tsmm
\ps
\oo
\C
\Ppp
\Pp
\Pxp
\Pppp
\Ppppp
\Cc
\Ccc
\c
\cc
\ccc
\ppp
\pp
\pxp
\pppp
\ppppp
\p
\x
\M
\gM
\B
\gB
\Bm
\gBm
\Mb
\gMb
\Mbb
\gMbb
\mBb
\gmBb
\mbB
\gmbB
\BBm
\gBBm
\Bbm
\gBbm
\bBm
\gbBm
\BB
\gBB
\Bb
\gBb
\bB
\gbB

\MetraStyle{style name%keyvals}
\InterSigna{factor}
\InterPedes{factor}
\SubSigna{factor}
\Intervallum{factor}
\Magnitudo{integer}
\ms{style name%keyvals}#*
\is{factor}#*
\ip{factor}#*
\ss{factor}#*
\i{factor}#*
\m{integer}#*
\en#*
\En#*
\st#*

\begin{metrica}
\begin{metrica}[n|N]
\end{metrica}
\begin{metrike}
\begin{metrike}[n|N]
\end{metrike}

\Elevatio{factor}
\Translatio{factor}
\e{factor}#*
\t{factor}#*
\MetrikeFont{commands}

\sigla{abbrv-specs}
\sigla[n|N]{abbrv-specs}
\charcolon
\charslash
\FaciesSiglorum{font commands}

\angus
\Angus
\angud
\Angud
\quadras
\Quadras
\quadrad
\Quadrad
\alas
\Alas
\alad
\Alad
\semi[
\semi]
\crux
\Crux

\anaclasis
\anaclasis[factor]
\Anaclasis
\Anaclasis[factor]
\antisigma
\antisigma[factor]
\Antisigma
\Antisigma[factor]
\asteriscus
\asteriscus[factor]
\asteriskos#S
\Asteriscus
\Asteriscus[factor]
\Asteriskos#S
\catalexis
\catalexis[factor]
\Catalexis
\Catalexis[factor]
\diple
\diple[factor]
\diple*
\diple*[factor]
\Diple
\Diple[factor]
\Diple*
\Diple*[factor]
\antidiple
\antidiple[factor]
\antidiple*
\antidiple*[factor]
\Antidiple
\Antidiple[factor]
\Antidiple*
\Antidiple*[factor]
\obelus
\obelus[factor]
\obelus*
\obelus*[factor]
\obelos#S
\Obelus
\Obelus[factor]
\Obelus*
\Obelus*[factor]
\Obelos#S
\respondens
\respondens[factor]
\Respondens
\Respondens[factor]
\terminus
\terminus[factor]
\terminus*
\terminus*[factor]
\Terminus
\Terminus[factor]
\Terminus*
\Terminus*[factor]

\margini{text}
\margini*{text}

\macron %<⟨letter⟩%>
\macron[%<factor%>] %<⟨letter⟩%>
\breve %<⟨letter⟩%>
\breve[%<factor%>] %<⟨letter⟩%>
\Breve#S
\acutus %<⟨letter⟩%>
\acutus[%<factor%>] %<⟨letter⟩%>
\gravis %<⟨letter⟩%>
\gravis[%<factor%>] %<⟨letter⟩%>
\circumflexus %<⟨letter⟩%>
\circumflexus[%<factor%>] %<⟨letter⟩%>
\diaeresis %<⟨letter⟩%>
\diaeresis[%<factor%>] %<⟨letter⟩%>
\cons %<⟨letter⟩%>
\dubia %<⟨letter⟩%>
\dubia* %<⟨letter⟩%>
\dubiae %<⟨letter⟩%>
\dubiae* %<⟨letter⟩%>
\erasa
\positio
\pos#S
\Positio
\Pos#S
\punctum
\punctum[repetitions]
\Punctum
\Punctum[repetitions]

\tie{chars}
\tie[factor]{chars}
\tie*{chars}
\tie*[factor]{chars}
\itie{chars}
\itie[factor]{chars}
\itie*{chars}
\itie*[factor]{chars}

\linea
\bifida
\Bifida
\lunata
\Lunata
\lineabifida#S
\Lineabifida#S
\linealunata#S
\Linealunata#S
\geminata
\antelineam{text%plain}
\postlineam{text%plain}
\coronis
\imago{symbol}
\imago[factor]{symbol}
\imago*{symbol}
\imago*[factor]{symbol}
\novalinea{cmd}{indent%l}{length}{factor}#d
\novageminata{cmd}{indent%l}{length}{factor}#d

\lineola{length}
\lineola[factor]{length}
\Lineola{text%plain}
\Lineola[factor]{text%plain}
\structa{text%plain}{above}

\D#*
\+#*
\metrike#*