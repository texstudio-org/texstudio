# pst-func package
# Matthew Bertucci 2023/04/14 for v1.02

#include:pstricks
#include:pst-plot
#include:pst-math
#include:pst-tools
#include:pstricks-add
#include:pst-xkey
#include:iftex
#include:luacode

\ChebyshevT
\ChebyshevU
\psPolynomial{x0}{x1}
\psPolynomial[options%keyvals]{x start}{x end}
\psBernstein(i,n)
\psBernstein(t0,t1)(i,n)
\psBernstein[options%keyvals](i,n)
\psBernstein[options%keyvals](t0,t1)(i,n)
\psLaguerre(x0,x1)
\psLaguerre[options%keyvals](x0,x1)
\psLegendre(x0,x1)
\psLegendre[options%keyvals](x0,x1)
\psZero(x0,x1){function%definition}{node name}
\psZero(x0,x1){functionA%definition}[functionB%definition]{node name}
\psZero[options%keyvals](x0,x1){function%definition}{node name}
\psZero[options%keyvals](x0,x1){functionA%definition}[functionB%definition]{node name}
\psFourier{x0}{x1}
\psFourier[options%keyvals]{x0}{x1}
\psBessel{order}{x0}{x1}
\psBessel[options%keyvals]{order}{x0}{x1}
\psModBessel{x0}{x1}
\psModBessel[options%keyvals]{x0}{x1}
\psSi{x0}{x1}
\psSi[options%keyvals]{x0}{x1}
\pssi{x0}{x1}
\pssi[options%keyvals]{x0}{x1}
\psCi{x0}{x1}
\psCi[options%keyvals]{x0}{x1}
\psci{x0}{x1}
\psci[options%keyvals]{x0}{x1}
\psIntegral{x0}{x1}(a,b){function%definition}
\psIntegral[options%keyvals]{x0}{x1}(a,b){function%definition}
\psCumIntegral{x0}{x1}{function%definition}
\psCumIntegral[options%keyvals]{x0}{x1}{function%definition}
\psConv{x0}{x1}(a,b){function f%definition}{function g%definition}
\psConv[options%keyvals]{x0}{x1}(a,b){function f%definition}{function g%definition}
\psGauss{x0}{x1}
\psGauss[options%keyvals]{x0}{x1}
\psGaussI{x0}{x1}
\psGaussI[options%keyvals]{x0}{x1}
\psBinomial{%<<N> or <m,N> or <m,n,N>%>}{%<probability%>}
\psBinomial[%<options%>]{%<<N> or <m,N> or <m,n,N>%>}{%<probability%>}
\psBinomialC{N}{probability}
\psBinomialC[options%keyvals]{N}{probability}
\psBinomialN{N}{probability}
\psBinomialN[options%keyvals]{N}{probability}
\psBinomialF{%<<N> or <m,N> or <m,n,N>%>}{%<probability%>}
\psBinomialF[%<options%>]{%<<N> or <m,N> or <m,n,N>%>}{%<probability%>}
\psBinomialFS{%<<N> or <m,N> or <m,n,N>%>}{%<probability%>}
\psBinomialFS[%<options%>]{%<<N> or <m,N> or <m,n,N>%>}{%<probability%>}
\psPoisson{%<<N> or <M,N>%>}{%<lambda%>}
\psPoisson[%<options%>]{%<<N> or <M,N>%>}{%<lambda%>}
\psGammaDist{x0}{x1}
\psGammaDist[options%keyvals]{x0}{x1}
\psChiIIDist{x0}{x1}
\psChiIIDist[options%keyvals]{x0}{x1}
\psTDist{x0}{x1}
\psTDist[options%keyvals]{x0}{x1}
\psNonCentralTDist{x0}{x1}
\psNonCentralTDist[options%keyvals]{x0}{x1}
\psFDist{x0}{x1}
\psFDist[options%keyvals]{x0}{x1}
\psNonCentralFDist{x0}{x1}
\psNonCentralFDist[options%keyvals]{x0}{x1}
\psBetaDist{x0}{x1}
\psBetaDist[options%keyvals]{x0}{x1}
\psCauchy{x0}{x1}
\psCauchy[options%keyvals]{x0}{x1}
\psCauchyI{x0}{x1}
\psCauchyI[options%keyvals]{x0}{x1}
\psWeibull{x0}{x1}
\psWeibull[options%keyvals]{x0}{x1}
\psWeibullI{x0}{x1}
\psWeibullI[options%keyvals]{x0}{x1}
\psVasicek{x0}{x1}
\psVasicek[options%keyvals]{x0}{x1}
\psLorenz{y data}
\psLorenz<x data>{y data}
\psLorenz[options%keyvals]{y data}
\psLorenz[options%keyvals]<x data>{y data}
\psLorenz*{y data}
\psLorenz*<x data>{y data}
\psLorenz*[options%keyvals]{y data}
\psLorenz*[options%keyvals]<x data>{y data}
\psLame{r}
\psLame[options%keyvals]{r}
\psThomae(x0,x1){points}
\psThomae[options%keyvals](x0,x1){points}
\psWeierstrass(x0,x1){a}
\psWeierstrass(x0,x1)[a]{b}
\psWeierstrass[options%keyvals](x0,x1){a}
\psWeierstrass[options%keyvals](x0,x1)[a]{b}
\psplotImp(xmin,ymin)(xmax,ymax){function%definition}
\psplotImp(xmin,ymin)(xmax,ymax)[PS code]{function%definition}
\psplotImp[options%keyvals](xmin,ymin)(xmax,ymax){function%definition}
\psplotImp[options%keyvals](xmin,ymin)(xmax,ymax)[PS code]{function%definition}
\psVolume(x0,x1){steps}{function%definition}
\psVolume[options%keyvals](x0,x1){steps}{function%definition}

# not documented
\psGetZeros(x0,x1){function%definition}#*
\psLaguerreC(xmin,xmax)(ymin,ymax)#*
\psLaguerreC[options%keyvals](xmin,xmax)(ymin,ymax)#*
\psLaguerreCC(xmin,xmax)(ymin,ymax)#*
\psLaguerreCC[options%keyvals](xmin,xmax)(ymin,ymax)#*
\psLaguerreCCC(xmin,xmax)(ymin,ymax)#*
\psLaguerreCCC[options%keyvals](xmin,xmax)(ymin,ymax)#*
\psLaguerreCCCC(xmin,xmax)(ymin,ymax)#*
\psLaguerreCCCC[options%keyvals](xmin,xmax)(ymin,ymax)#*
\psContourLaguerre(xmin,xmax)(ymin,ymax)#*
\psContourLaguerre[options%keyvals](xmin,xmax)(ymin,ymax)#*
\cplotstyle#*
\psCplot{x0}{x1}{vars}{function%definition}#*
\PSTfuncLoaded#S
