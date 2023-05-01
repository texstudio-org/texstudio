# pgf-spectra package
# Matthew Bertucci 2023/04/26 for v3.0.0

#include:tikz

#keyvals:\usepackage/pgf-spectra#c
LSE
NIST
#endkeyvals

pgfspectraIRcolor#B
pgfspectraUVcolor#B
visible#B
visible5#B
visible10#B
visible15#B
visible20#B
visible25#B
visible30#B
visible35#B
visible40#B
visible45#B
visible50#B
visible55#B
visible60#B
visible65#B
visible70#B
visible75#B
visible80#B
visible85#B
visible90#B
visible95#B
visible100#B

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
axis label#true,false
axis label text={%<text%>}
axis label position=#left,center,right
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

\pgfspectrashade(start,end){name}
\pgfspectrashade[h|v](start,end){name}

\usepgfspectralibrary{libraries%keyvals}

#keyvals:\usepgfspectralibrary#c
data
pgfplots
tempercolor
rainbow
#endkeyvals

### < Libraries > ###
# currently no good way to detect libraries loaded via \usepgfspectralibrary so all commands listed here

## data library ##
\pgfspectradata{options%keyvals}
\pgfspectradata[name]{options%keyvals}

#keyvals:\pgfspectradata
# shared with \pgfspectra
element=%<symbol(s)%>
charge=%<<integer> or all%>
Imin=%<factor%>
redshift=%<value%>
begin=%<wavelength%>
end=%<wavelength%>
relative intensity#true,false
# unique to \pgfspectradata
precision=%<integer%>
unit=#nm,micron,A
#endkeyvals

\pgfspectratable
\pgfspectratable{dataset names}
\pgfspectratable[options%keyvals]
\pgfspectratable[options%keyvals]{dataset names}

#keyvals:\pgfspectratable
title={%<text%>}
back color=#%color
data back color=#%color
text color=#%color
width=##L
elements column width=##L
#endkeyvals

\pgfspectrawrite
\pgfspectrawrite{dataset names}
\pgfspectrawrite[filename]
\pgfspectrawrite[filename]{dataset names}

## pgfplots library ##
\pgfspectraplotmap{name}
\pgfspectraplotmap[l|h]{name}

\pgfspectraplotshade{name}
\pgfspectraplotshade[options%keyvals]{name}

#keyvals:\pgfspectraplotshade
shade begin=%<value%>
shade end=%<value%>
shade opacity=%<factor%>
shade opacity color=#%color
logarithmic#true,false
#endkeyvals

## tempercolor library ##
\tempercolor{Kelvin}

## rainbow library ##
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

# not documented
\wldez#S
\wlquatromil#S
