# abspos package
# Matthew Bertucci 2022/09/24 for v0.1

#include:atbegshi

\absposset{options%keyvals}
\absput{contents%text}
\absput[options%keyvals]{contents%text}
\absputcoffin %<⟨coffin⟩%>
\absputcoffin[%<options%>] %<⟨coffin⟩%>

#keyvals:\absposset#c,\absput#c,\absputcoffin#c
angle=%<degrees%>
h=#l,hc,r
pg=%<page-coffin%>
pg-h=#l,hc,r
pg-v=#t,vc,b,H,T,B
scale=%<factor%>
v=#t,vc,b,H,T,B
width=##L
x=##L
y=##L
#endkeyvals