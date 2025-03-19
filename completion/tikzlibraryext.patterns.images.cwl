# ext.patterns.images tikzlibrary
# 2025/03/19 for v0.6

\tikzextsetupimageaspattern{name}{imagefile}#g
\tikzextsetupimageaspattern[options%keyvals]{name}{imagefile}#g

#keyvals:\pgfsetupimageaspattern
height=##L
width=##L
page=%<page number%>
interpolate#true,false
mask=%<mask name%>
#endkeyvals

#keyvals:\node#c
ext/image as pattern={%<options%>}
#endkeyvals

# from tikzext-util.tex
\tikzextversion#S
\tikzextversionnumber#S
\tikzextset{options%keyvals}
\pgfextset{options%keyvals}
