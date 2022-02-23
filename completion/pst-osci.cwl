# pst-osci package
# Matthew Bertucci 2/22/2022 for v1.01

#include:pstricks
#include:pst-plot
#include:multido
#include:pst-xkey

\Oscillo
\Oscillo[options%keyvals]

#keyvals:\Oscillo#c
period1=%<number%>
period2=%<number%>
periodmodulation1=%<number%>
freqmod1=%<number%>
periodmodulation2=%<number%>
freqmod2=%<number%>
amplitude1=%<number%>
amplitude2=%<number%>
CC1=%<number%>
CC2=%<number%>
timediv=%<number%>
phase1=%<number%>
phase2=%<number%>
sensivity1=%<number%>
sensivity2=%<number%>
damping1=%<number%>
damping2=%<number%>
Fourier=%<number%>
offset1=%<number%>
offset2=%<number%>
offset3=%<number%>
plotstyle1=%<style%>
plotstyle2=%<style%>
plotstyle3=%<style%>
plotstyle4=%<style%>
operation=#add,sub,mul
Wave1=#\TriangleA,\RectangleA,\RDogToothA,\LDogToothA,\SinusA
Wave2=#\TriangleB,\RectangleB,\RDogToothB,\LDogToothB,\SinusB
Lissajous#true,false
AllColor#true,false
combine#true,false
plotpoints=%<number%>
#endkeyvals

\TriangleA
\TriangleB
\RectangleA
\RectangleB
\RDogToothA
\RDogToothB
\LDogToothA
\LDogToothB
\SinusA
\SinusB

Beige#B
LightGray#B
VeryLightGray#B
PaleOrange#B
LightBlue#B
ACredA#B
ACgreenA#B
ACmagentaA#B
ACred#B
ACgreen#B
ACmagenta#B

\ssf#S
\PSTOscilloLoaded#S