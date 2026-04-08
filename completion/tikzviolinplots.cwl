# tikzviolinplots package
# Matthew Bertucci 2026/04/06 for v0.11.0

#include:pgfplots
#include:pgfplotstable
#include:pgfkeys

\violinplotsset{pgfplots options}
\violinplotsset[package-specific options%keyvals]{pgfplots options}
\violinsetoptions{pgfplots options}#*
\violinsetoptions[package-specific options%keyvals]{pgfplots options}#*

#keyvals:\violinplotsset,\violinsetoptions
scaled
data points
averages
no mirror
reverse axis
#endkeyvals

# mark no-option version with #* since probably never wanted
\addviolinplot{filename%file}#*
\addviolinplot[options%keyvals]{filename%file}
\violinplot{filename%file}#*
\violinplot[options%keyvals]{filename%file}#*

\violinplotwholefile{filename%file}#*
\violinplotwholefile[options%keyvals]{filename%file}

#keyvals:\addviolinplot,\violinplot,\violinplotwholefile
col sep=#space,tab,comma,colon,semicolon,braces,ampersand
index=%<column name%>
frequencies=%<column name%>
kernel=#gaussian,logistic,parabolic,uniform,triangular
bandwidth=%<number%>
samples=%<integer%>
relative position=%<integer%>
color=#%color
fill opacity=%<factor%>
label={%<text%>}
data label style={%<style keys%>}
invert#true,false
average mark=%<mark%>
dataset mark=%<mark%>
average size=##L
dataset size=##L
average color=#%color
dataset color=#%color
average opacity=%<factor%>
dataset opacity=%<factor%>
average fill=#%color
dataset fill=#%color
average fill opacity=%<factor%>
dataset fill opacity=%<factor%>
dataset jitter=%<factor%>
#endkeyvals

# keys only for \violinplotwholefile
#keyvals:\violinplotwholefile
primary color=#%color
secondary color=#%color
indexes={%<index1,index2,...%>}
spacing=%<number%>
labels={%<label1,label2,...%>}
#endkeyvals
