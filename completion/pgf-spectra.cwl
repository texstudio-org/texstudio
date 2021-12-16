# pgf-spectra package
# Matthew Bertucci 12/14/2021 for v2.1.2

#include:tikz

#keyvals:\usepackage/pgf-spectra#c
LSE
NIST
#endkeyvals

wlIRcolor#B
wlUVcolor#B
tempercolor#B

\pgfspectra
\pgfspectra[options%keyvals]

\wlcolor{wavelength}

\pgfspectraStyle[options%keyvals]
\pgfspectraStyleReset

#keyvals:\pgfspectra,\pgfspectraStyle,\pgfspectraplotshade
use visible shading#true,false
width=##L
height=##L
element=%<symbol(s)%>
charge=%<<integer> or all%>
Imin=%<factor%>
relative intensity#true,false
relative intensity threshold=%<factor%>
line intensity=%<number%>
gamma=%<number%>
brightness=%<factor%>
back=#%color
backIRUV=#%color
IRcolor=#%color
UVcolor=#%color
lines={%<wavelengths%>}
line width=##L
begin=%<wavelength%>
end=%<wavelength%>
absorption#true,false
axis#true,false
axis step=%<integer%>
axis ticks=%<integer%>
axis unit=#nm,micron,A
axis unit precision=%<integer%>
axis color=#%color
axis font=%<font commands%>
axis font color=#%color
label#true,false
label position=#north west,north,north east,west,east,south west,south,south east
label font=%<font commands%>
label font color=#%color
label before text=%<text%>
label after text=%<text%>
redshift=%<value%>
show redshift value#true,false
#endkeyvals

\tempercolor{Kelvin}

\pgfspectrashade(start,end){name}
\pgfspectrashade[h or v](start,end){name}

\pgfspectraplotshade{name}
\pgfspectraplotshade[options%keyvals]{name}

#keyvals:\pgfspectraplotshade
shade begin=%<value%>
shade end=%<value%>
shade opacity=%<factor%>
shade opacity color=#%color
logarithmic#true,false
#endkeyvals

\pgfspectraplotmap{name}
\pgfspectraplotmap[l or h]{name}

\pgfspectrarainbow{radius}
\pgfspectrarainbow(options%keyvals){radius}
\pgfspectrarainbow[TikZ options](options%keyvals){radius}

#keyvals:\pgfspectrarainbow
rainbow start=%<fraction%>
rainbow knock out=%<value%>
rainbow fade=%<fading%>
rainbow transparency=%<factor%>
rainbow background=#%color
#endkeyvals

\rO#*
\wldez#*
\wlquatromil#*
\xI#*
\xLI#*
\xscale#*