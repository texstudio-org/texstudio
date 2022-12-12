# patchplots pgfplotslibrary
# 2022/12/12 for v1.18.1

#keyvals:\begin{axis}#c,\begin{loglogaxis}#c,\begin{semilogxaxis}#c,\begin{semilogyaxis}#c,\addplot#c,\addplot3#c,\addplot+#c,\pgfplotsset#c,\begin{groupplot}#c,\nextgroupplot#c,\begin{smithchart}#c,\begin{polaraxis}#c,\begin{ternaryaxis}#c
patch type=#default,rectaingle,triangle,line,quadratic spline,cubic spline,bezier spline,bilinear,triangle quadr,biquadratic,bicubic,polygon,coons,tensor bezier
vertex count=%<integer%>
patch refines=%<level%>
patch to triangles#true,false
#endkeyvals

# not documented
\pgfplotspathcubicfrominterpolation{arg1}{arg2}{arg3}{arg4}#S
\Pcur#S
\Pstart#S
\Pnextseq#S
\Pstartidx#S