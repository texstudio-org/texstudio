# units pgfplotslibrary
# 2022/12/11 for v1.18.1

#keyvals:\begin{axis}#c,\begin{loglogaxis}#c,\begin{semilogxaxis}#c,\begin{semilogyaxis}#c,\addplot#c,\addplot3#c,\addplot+#c,\pgfplotsset#c,\begin{groupplot}#c,\nextgroupplot#c,\begin{smithchart}#c,\begin{polaraxis}#c,\begin{ternaryaxis}#c
use units#true,false
x unit=%<unit%>
y unit=%<unit%>
z unit=%<unit%>
x unit prefix=%<prefix%>
y unit prefix=%<prefix%>
z unit prefix=%<prefix%>
unit marking pre=%<pre%>
unit marking post=%<post%>
unit markings=#parenthesis,square brackets,slash space
unit code/.code 2 args={%<code%>}
x SI prefix=#yocto,zepto,atto,femto,pico,nano,micro,milli,centi,deci,deca,hecto,kilo,mega,giga,tera,peta,exa,zetta,yotta
y SI prefix=#yocto,zepto,atto,femto,pico,nano,micro,milli,centi,deci,deca,hecto,kilo,mega,giga,tera,peta,exa,zetta,yotta
z SI prefix=#yocto,zepto,atto,femto,pico,nano,micro,milli,centi,deci,deca,hecto,kilo,mega,giga,tera,peta,exa,zetta,yotta
change x base#true,false
change y base#true,false
change z base#true,false
axis base prefix={axis %<axis%> base %<base%> prefix %<prefix%>}
#endkeyvals