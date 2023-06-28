# For derivative v1.1 (2021/06/03) by Simon Jensen.
# URL: https://ctan.org/pkg/derivative?lang=en
# Created by Brian Schubert (2021/08/03).
# updated 2022/07/11 for v1.2

#include:l3keys2e

#keyvals:\usepackage/derivative#c
italic#true,false
upright#true,false
#endkeyvals

## Derivatives and Other Derivatives (section 1)
\pdv[keyvals]{function}/{variables}_{pt1}^{pt2}#*m 
\pdv[keyvals]{function}{variables}_{pt1}^{pt2}#m
\pdv[keyvals]{function}/{variables}#m
\pdv[keyvals]{function}{variables}#m
\pdv{function}/{variables}_{pt1}^{pt2}#*m 
\pdv{function}{variables}_{pt1}^{pt2}#m
\pdv{function}/{variables}#m
\pdv{function}{variables}#m
\pdv*[keyvals]{function}/{variables}_{pt1}^{pt2}#*m 
\pdv*[keyvals]{function}{variables}_{pt1}^{pt2}#m
\pdv*[keyvals]{function}/{variables}#m
\pdv*[keyvals]{function}{variables}#m
\pdv*{function}/{variables}_{pt1}^{pt2}#*m 
\pdv*{function}{variables}_{pt1}^{pt2}#m
\pdv*{function}/{variables}#m
\pdv*{function}{variables}#m
\odv[keyvals]{function}/{variables}_{pt1}^{pt2}#*m 
\odv[keyvals]{function}{variables}_{pt1}^{pt2}#m
\odv[keyvals]{function}/{variables}#m
\odv[keyvals]{function}{variables}#m
\odv{function}/{variables}_{pt1}^{pt2}#*m 
\odv{function}{variables}_{pt1}^{pt2}#m
\odv{function}/{variables}#m
\odv{function}{variables}#m
\odv*[keyvals]{function}/{variables}_{pt1}^{pt2}#*m 
\odv*[keyvals]{function}{variables}_{pt1}^{pt2}#m
\odv*[keyvals]{function}/{variables}#m
\odv*[keyvals]{function}{variables}#m
\odv*{function}/{variables}_{pt1}^{pt2}#*m 
\odv*{function}{variables}_{pt1}^{pt2}#m
\odv*{function}/{variables}#m
\odv*{function}{variables}#m
\mdv[keyvals]{function}/{variables}_{pt1}^{pt2}#*m 
\mdv[keyvals]{function}{variables}_{pt1}^{pt2}#m
\mdv[keyvals]{function}/{variables}#m
\mdv[keyvals]{function}{variables}#m
\mdv{function}/{variables}_{pt1}^{pt2}#*m 
\mdv{function}{variables}_{pt1}^{pt2}#m
\mdv{function}/{variables}#m
\mdv{function}{variables}#m
\mdv*[keyvals]{function}/{variables}_{pt1}^{pt2}#*m 
\mdv*[keyvals]{function}{variables}_{pt1}^{pt2}#m
\mdv*[keyvals]{function}/{variables}#m
\mdv*[keyvals]{function}{variables}#m
\mdv*{function}/{variables}_{pt1}^{pt2}#*m 
\mdv*{function}{variables}_{pt1}^{pt2}#m
\mdv*{function}/{variables}#m
\mdv*{function}{variables}#m
\fdv[keyvals]{function}/{variables}_{pt1}^{pt2}#*m 
\fdv[keyvals]{function}{variables}_{pt1}^{pt2}#m
\fdv[keyvals]{function}/{variables}#m
\fdv[keyvals]{function}{variables}#m
\fdv{function}/{variables}_{pt1}^{pt2}#*m 
\fdv{function}{variables}_{pt1}^{pt2}#m
\fdv{function}/{variables}#m
\fdv{function}{variables}#m
\fdv*[keyvals]{function}/{variables}_{pt1}^{pt2}#*m 
\fdv*[keyvals]{function}{variables}_{pt1}^{pt2}#m
\fdv*[keyvals]{function}/{variables}#m
\fdv*[keyvals]{function}{variables}#m
\fdv*{function}/{variables}_{pt1}^{pt2}#*m 
\fdv*{function}{variables}_{pt1}^{pt2}#m
\fdv*{function}/{variables}#m
\fdv*{function}{variables}#m
\adv[keyvals]{function}/{variables}_{pt1}^{pt2}#*m 
\adv[keyvals]{function}{variables}_{pt1}^{pt2}#m
\adv[keyvals]{function}/{variables}#m
\adv[keyvals]{function}{variables}#m
\adv{function}/{variables}_{pt1}^{pt2}#*m 
\adv{function}{variables}_{pt1}^{pt2}#m
\adv{function}/{variables}#m
\adv{function}{variables}#m
\adv*[keyvals]{function}/{variables}_{pt1}^{pt2}#*m 
\adv*[keyvals]{function}{variables}_{pt1}^{pt2}#m
\adv*[keyvals]{function}/{variables}#m
\adv*[keyvals]{function}{variables}#m
\adv*{function}/{variables}_{pt1}^{pt2}#*m 
\adv*{function}{variables}_{pt1}^{pt2}#m
\adv*{function}/{variables}#m
\adv*{function}{variables}#m
\jdv[keyvals]{function}/{variables}_{pt1}^{pt2}#*m 
\jdv[keyvals]{function}{variables}_{pt1}^{pt2}#m
\jdv[keyvals]{function}/{variables}#m
\jdv[keyvals]{function}{variables}#m
\jdv{function}/{variables}_{pt1}^{pt2}#*m 
\jdv{function}{variables}_{pt1}^{pt2}#m
\jdv{function}/{variables}#m
\jdv{function}{variables}#m
\jdv*[keyvals]{function}/{variables}_{pt1}^{pt2}#*m 
\jdv*[keyvals]{function}{variables}_{pt1}^{pt2}#m
\jdv*[keyvals]{function}/{variables}#m
\jdv*[keyvals]{function}{variables}#m
\jdv*{function}/{variables}_{pt1}^{pt2}#*m 
\jdv*{function}{variables}_{pt1}^{pt2}#m
\jdv*{function}/{variables}#m
\jdv*{function}{variables}#m

## Differentials and Other Differentials (section 2)
\odif[keyvals]{variables}#m
\odif{variables}#m
\odif*[keyvals]{variables}#m
\odif*{variables}#m
\pdif[keyvals]{variables}#m
\pdif{variables}#m
\pdif*[keyvals]{variables}#m
\pdif*{variables}#m
\mdif[keyvals]{variables}#m
\mdif{variables}#m
\mdif*[keyvals]{variables}#m
\mdif*{variables}#m
\fdif[keyvals]{variables}#m
\fdif{variables}#m
\fdif*[keyvals]{variables}#m
\fdif*{variables}#m
\adif[keyvals]{variables}#m
\adif{variables}#m
\adif*[keyvals]{variables}#m
\adif*{variables}#m

## Options (section 3)
\derivset{derivative%cmd}
\derivset{derivative%cmd}[options%keyvals]

## Derivative options (section 3.3)
### Derivative Style (style-)
#keyvals:\derivset,\NewDerivative,\RenewDerivative,\ProvideDerivative,\DeclareDerivative,\pdv,\pdv*,\odv,\odv*,\mdv,\mdv*,\fdv,\fdv*,\adv,\adv*,\jdv,\jdv*
style-inf=%<infinitesimal%>
style-frac=%<frac macro%>
style-frac-/=%<slashfrac macro%>
style-var=#single,multiple

### Derivative Scaling (scale-)
scale-eval=#auto,none,big,Big,bigg,Bigg
scale-eval-/=#auto,none,big,Big,bigg,Bigg
scale-fun=#auto,none,big,Big,bigg,Bigg
scale-var=#auto,none,big,Big,bigg,Bigg
scale-frac=#auto,none,big,Big,bigg,Bigg
scale-frac-/=#auto,none,big,Big,bigg,Bigg

### Derivative Delimiters (delim-)
delims-eval={%<left delim%>}{%<right delim%>}
delims-eval-/={%<left delim%>}{%<right delim%>}
delims-fun={%<left delim%>}{%<right delim%>}
delims-var={%<left delim%>}{%<right delim%>}
delims-frac={%<left delim%>}{%<right delim%>}
delims-frac-/={%<left delim%>}{%<right delim%>}

### Derivative Math Spacing (sep-)
sep-inf-ord=%<<num>, <mspace>, or <delim>%>
sep-inf-fun=%<<num>, <mspace>, or <delim>%>
sep-ord-func=%<<num>, <mspace>, or <delim>%>
sep-frac-fun=%<<num>, <mspace>, or <delim>%>
sep-inf-var=%<<num>, <mspace>, or <delim>%>
sep-var-ord=%<<num>, <mspace>, or <delim>%>
sep-var-inf=%<<num>, <mspace>, or <delim>%>
sep-ord-inf=%<<num>, <mspace>, or <delim>%>
sep-var-var=%<<num>, <mspace>, or <delim>%>
sep-eval-sb=%<<num>, <mspace>, or <delim>%>
sep-eval-sp=%<<num>, <mspace>, or <delim>%>

### Derivative Switches (switch-)
switch-*#true,false
switch-/#true,false
switch-sort#true,false

### Derivative Sort (sort-)
sort-method={%<abs, lexical, number, sign, and/or symbol%>}
sort-numerical=#auto,first,last,symbolic
sort-abs-reverse#true,false
sort-number-reverse#true,false
sort-sign-reverse#true,false
sort-symbol-reverse#true,false
sort-lexical-reverse#true,false

### Derivative Miscellaneous
fun#true,false
frac#true,false
var
var=%<none, all, or {cs-numbers}%>
order={%<cs-orders%>}
ord={%<cs-orders%>}
mixed-order={%<mixed order%>}
mixord={%<mixed order%>}
#endkeyvals

## Differential options (section 3.4)
### Differential Style (style-)
#keyvals:\derivset,\NewDifferential,\RenewDifferential,\ProvideDifferential,\DeclareDifferential,\odif,\odif*,\pdif,\pdif*,\mdif,\mdif*,\fdif,\fdif*,\adif,\adif*
style-inf=%<infinitesimal%>
style-notation=#single,multiple,mixed
style-notation-*=#single,multiple,mixed

### Differential Scaling (scale-)
scale-var=#auto,none,big,Big,bigg,Bigg
scale-var-*=#auto,none,big,Big,bigg,Bigg

### Differential Delimiters (delim-)
delims-var={%<left delim%>}{%<right delim%>}
delims-var-*={%<left delim%>}{%<right delim%>}

### Differential Math Spacing (sep-)
sep-begin=%<<num>, <mspace>, or <delim>%>
sep-inf-ord=%<<num>, <mspace>, or <delim>%>
sep-inf-var=%<<num>, <mspace>, or <delim>%>
sep-ord-var=%<<num>, <mspace>, or <delim>%>
sep-var-inf=%<<num>, <mspace>, or <delim>%>
sep-var-var=%<<num>, <mspace>, or <delim>%>
sep-ord-ord=%<<num>, <mspace>, or <delim>%>
sep-end=%<<num>, <mspace>, or <delim>%>

### Differential Switches (switch-)
switch-*=#true,false

### Differential Miscellaneous
var
var=%<none, all, or {cs-numbers}%>
order={%<cs-orders%>}
ord={%<cs-orders%>}
#endkeyvals

## All derivatives and differentials options (section 3.5)
#keyvals:\derivset
scale-auto=#leftright,mleftright
#endkeyvals

## Defining variants (section 4)
\NewDerivative{cmd}{infinitesimal%formula}[keyvals]#nd
\RenewDerivative{cmd}{infinitesimal%formula}[keyvals]#n
\ProvideDerivative{cmd}{infinitesimal%formula}[keyvals]#nd
\DeclareDerivative{cmd}{infinitesimal%formula}[keyvals]#nd
\NewDifferential{cmd}{infinitesimal%formula}[keyvals]#nd
\RenewDifferential{cmd}{infinitesimal%formula}[keyvals]#n
\ProvideDifferential{cmd}{infinitesimal%formula}[keyvals]#nd
\DeclareDifferential{cmd}{infinitesimal%formula}[keyvals]#nd

# Miscellaneous (section 6)
\slashfrac{numerator}{denominator}#m
\slashfrac[scale%keyvals]{numerator}{denominator}#m
# Note: as of v1.1, ths scale argument is still subject to change. See 7.2(ii).
#keyvals:\slashfrac
auto
none
big
Big
bigg
Bigg
#endkeyvals
