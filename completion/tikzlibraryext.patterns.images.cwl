# ext.patterns.images tikzlibrary
# 2022/12/09 for v0.4.2

\pgfsetupimageaspattern{name}{imagefile}#g
\pgfsetupimageaspattern[options%keyvals]{name}{imagefile}#g

#keyvals:\pgfsetupimageaspattern
height=##L
width=##L
page=%<page number%>
interpolate#true,false
mask=%<mask name%>
#endkeyvals

#keyvals:\node#c
image as pattern={%<options%>}
#endkeyvals