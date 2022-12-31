# switching-architectures tikzlibrary
# 2022/12/08 for v0.7a

#include:tikzlibrarybackgrounds
#include:tikzlibrarycalc
#include:tikzlibrarypositioning
#include:tikzlibrarydecorations.pathreplacing

#keyvals:\node#c
clos snb
clos rear
benes
benes complete
banyan omega
banyan flip
clos snb example
clos rear example
clos example with labels
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\node#c
N=%<num input ports%>
M=%<num output ports%>
r1=%<num modules%>
r3=%<num modules%>
P=%<num ports%>
module size=##L
module ysep=%<number%>
module xsep=%<number%>
module label opacity=%<factor%>
pin length factor=%<factor%>
module font=%<font commands%>
connections disabled#true,false
N label=%<text%>
r1 label=%<text%>
m1 label=%<text%>
r2 label=%<text%>
M label=%<text%>
r3 label=%<text%>
m3 label=%<text%>
set math mode labels#true,false
#endkeyvals

\pgfmathomegarotation{degrees}{bits}{macro}#S
\rone#S
\ronelabel#S
\monelabel#S
\rtwolabel#S
\M#S
\Mlabel#S
\rthree#S
\rthreelabel#S
\mthreelabel#S
\P#S
\modulesize#S
\moduleysep#S
\modulexsep#S
\modulefont#S
\modulelabelopacity#S
\pinlength#S
\ifconnectiondisabled#S
\connectiondisabledtrue#S
\connectiondisabledfalse#S