# statistics pgfplotslibrary
# 2022/12/12 for v1.18.1

#keyvals:\begin{axis}#c,\begin{loglogaxis}#c,\begin{semilogxaxis}#c,\begin{semilogyaxis}#c,\addplot#c,\addplot3#c,\addplot+#c,\pgfplotsset#c,\begin{groupplot}#c,\nextgroupplot#c
boxplot prepared={%<options%>}
boxplot
boxplot={%<options%>}
hist
hist={%<options%>}
#endkeyvals

\pgfplotsboxplotvalue{options%keyvals}#*
\boxplotvalue{options%keyvals}

#keyvals:\pgfplotsboxplotvalue#c,\boxplotvalue#c
draw position=%<axis unit%>
data=%<expression%>
data value=%<value%>
data filter/.code={%<code%>}
lower whisker=%<value%>
lower quartile=%<value%>
median=%<value%>
upper quartile=%<value%>
upper whisker=%<value%>
average=%<value%>
draw direction=#x,y
variable width#true,false
sample size=%<number%>
variable width expr=%<expression%>
sample size min=%<number%>
sample size max=%<number%>
variable width min target=%<factor%>
box extend=%<factor%>
whisker extend=%<factor%>
draw relative anchor=%<factor%>
estimator=#R1,R2,R3,R4,R5,R6,R7,R8,R9,legacy
whisker range=%<number%>
every boxplot/.style={%<TikZ keys%>}
every whisker/.style={%<TikZ keys%>}
every box/.style={%<TikZ keys%>}
every median/.style={%<TikZ keys%>}
every average/.style={%<TikZ keys%>}
#endkeyvals

\pgfplotsplothandlerboxplot#S
\pgfplotsplothandlerboxplotprepared#S
\pgfplotsboxplotpointabbox{arg1}{arg2}#S
\pgfplotsboxplotpointabwhisker{arg1}{arg2}#S
\pgfplotsboxplotpointab{arg1}{arg2}#S