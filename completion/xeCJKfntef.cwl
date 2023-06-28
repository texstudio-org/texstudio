# xeCJKfntef package
# Darcy Hu <hot123tea123@gmail.com> 2016
#modified zepinglee 30 Jan 2021
# updated 02 May 2022 for v3.8.8

#include:xeCJK
#include:ulem

# passes options to ulem
#keyvals:\usepackage/xeCJKfntef#c
normalem
ULforem
normalbf
UWforbf
#endkeyvals

\CJKunderline{contents}
\CJKunderline*{contents}
\CJKunderline-{contents}
\CJKunderline[options%keyvals]{contents}
\CJKunderline*[options%keyvals]{contents}
\CJKunderline-[options%keyvals]{contents}

#keyvals:\CJKunderline,\CJKunderline*,\CJKunderline-
skip#true,false
hidden#true,false
subtract#true,false
thickness=##L
depth=##L
sep=##L
format=%<format commands%>
textformat=%<format commands%>
#endkeyvals

\CJKunderdblline{contents}
\CJKunderdblline*{contents}
\CJKunderdblline-{contents}
\CJKunderdblline[options%keyvals]{contents}
\CJKunderdblline*[options%keyvals]{contents}
\CJKunderdblline-[options%keyvals]{contents}

#keyvals:\CJKunderdblline,\CJKunderdblline*,\CJKunderdblline-
skip#true,false
hidden#true,false
subtract#true,false
thickness=##L
depth=##L
sep=##L
format=%<format commands%>
textformat=%<format commands%>
gap=##L
#endkeyvals

\CJKunderwave{contents}
\CJKunderwave*{contents}
\CJKunderwave-{contents}
\CJKunderwave[options%keyvals]{contents}
\CJKunderwave*[options%keyvals]{contents}
\CJKunderwave-[options%keyvals]{contents}

#keyvals:\CJKunderwave,\CJKunderwave*,\CJKunderwave-
skip#true,false
hidden#true,false
subtract#true,false
symbol=%<symbol%>
depth=##L
sep=##L
format=%<format commands%>
textformat=%<format commands%>
#endkeyvals

\CJKsout{contents}
\CJKsout*{contents}
\CJKsout-{contents}
\CJKsout[options%keyvals]{contents}
\CJKsout*[options%keyvals]{contents}
\CJKsout-[options%keyvals]{contents}

#keyvals:\CJKsout,\CJKsout*,\CJKsout-
skip#true,false
hidden#true,false
subtract#true,false
thickness=##L
height=##L
format=%<format commands%>
textformat=%<format commands%>
#endkeyvals

\CJKxout{contents}
\CJKxout*{contents}
\CJKxout-{contents}
\CJKxout[options%keyvals]{contents}
\CJKxout*[options%keyvals]{contents}
\CJKxout-[options%keyvals]{contents}

#keyvals:\CJKxout,\CJKxout*,\CJKxout-
skip#true,false
hidden#true,false
subtract#true,false
format=%<format commands%>
textformat=%<format commands%>
#endkeyvals

\CJKunderdot{contents}
\CJKunderdot[options%keyvals]{contents}

#keyvals:\CJKunderdot
symbol=%<symbol%>
depth=##L
sep=##L
format=%<format commands%>
textformat=%<format commands%>
boxdepth=##L
#endkeyvals

#keyvals:\xeCJKsetup
underline={%<options%>}
underline/skip#true,false
underline/hidden#true,false
underline/subtract#true,false
underline/thickness=##L
underline/depth=##L
underline/sep=##L
underline/format=%<format commands%>
underline/textformat=%<format commands%>
underdblline={%<options%>}
underdblline/skip#true,false
underdblline/hidden#true,false
underdblline/subtract#true,false
underdblline/thickness=##L
underdblline/depth=##L
underdblline/sep=##L
underdblline/format=%<format commands%>
underdblline/textformat=%<format commands%>
underdblline/gap=##L
underwave={%<options%>}
underwave/skip#true,false
underwave/hidden#true,false
underwave/subtract#true,false
underwave/symbol=%<symbol%>
underwave/depth=##L
underwave/sep=##L
underwave/format=%<format commands%>
underwave/textformat=%<format commands%>
sout={%<options%>}
sout/skip#true,false
sout/hidden#true,false
sout/subtract#true,false
sout/thickness=##L
sout/height=##L
sout/format=%<format commands%>
sout/textformat=%<format commands%>
xout={%<options%>}
xout/skip#true,false
xout/hidden#true,false
xout/subtract#true,false
xout/format=%<format commands%>
xout/textformat=%<format commands%>
underdot={%<options%>}
underdot/symbol=%<symbol%>
underdot/depth=##L
underdot/sep=##L
underdot/format=%<format commands%>
underdot/textformat=%<format commands%>
underdot/boxdepth=##L
symbol/sep=##L
symbol/boxdepth=##L
symbol/textformat=%<format commands%>
ulem={%<options%>}
ulem/skip#true,false
ulem/hidden#true,false
ulem/subtract#true,false
ulem/sep=##L
ulem/boxdepth=##L
ulem/textformat=%<format commands%>
#endkeyvals

\CJKunderanyline{depth%l}{underlined contents}{text}
\CJKunderanyline*{depth%l}{underlined contents}{text}
\CJKunderanyline-{depth%l}{underlined contents}{text}
\CJKunderanyline[options%keyvals]{depth%l}{underlined contents}{text}
\CJKunderanyline*[options%keyvals]{depth%l}{underlined contents}{text}
\CJKunderanyline-[options%keyvals]{depth%l}{underlined contents}{text}

#keyvals:\CJKunderanyline,\CJKunderanyline*,\CJKunderanyline-
textformat=%<format commands%>
skip#true,false
hidden#true,false
subtract#true,false
sep=##L
boxdepth=##L
#endkeyvals

\CJKunderanysymbol{depth%l}{symbol}{contents}
\CJKunderanysymbol[options%keyvals]{depth%l}{symbol}{contents}

#keyvals:\CJKunderanysymbol
textformat=%<format commands%>
sep=##L
boxdepth=##L
#endkeyvals

\xeCJKfntefon
\xeCJKfntefon*
\xeCJKfntefon-
\xeCJKfntefon[options%keyvals]
\xeCJKfntefon*[options%keyvals]
\xeCJKfntefon-[options%keyvals]

#keyvals:\xeCJKfntefon,\xeCJKfntefon*,\xeCJKfntefon-
textformat=%<format commands%>
skip#true,false
hidden#true,false
subtract#true,false
#endkeyvals

\begin{CJKfilltwosides}{width%l}
\begin{CJKfilltwosides}[position]{width%l}
\end{CJKfilltwosides}
\begin{CJKfilltwosides*}{width%l}
\begin{CJKfilltwosides*}[position]{width%l}
\end{CJKfilltwosides*}
