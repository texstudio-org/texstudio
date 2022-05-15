# phonenumbers package
# Matthew Bertucci 2022/05/15 for v2.4

#include:l3keys2e
#include:ltxcmds

\phonenumber{number}
\phonenumber{number}[extension]
\phonenumber[options%keyvals]{number}
\phonenumber[options%keyvals]{number}[extension]
\setphonenumbers{options%keyvals}

\AreaCodesGeographic
\AreaCodesGeographic[options%keyvals]
\AreaCodesNonGeographic
\AreaCodesNonGeographic[options%keyvals]
\CountryCodes

#keyvals:\usepackage/phonenumbers#c,\phonenumber,\setphonenumbers,\AreaCodesGeographic,\AreaCodesNonGeographic
country=#AT,DE,FR,UK,US
link=#on,off
foreign=#international,american,european,off
foreign-area-code-sep=#space,brackets
home-country=#AT,DE,FR,UK,US,none
home-area-code=%<area code%>
group-min=#3,4,5,6,7
area-code-sep=#slash,brackets,space,hyphen
area-code=#number,place,place-and-number
trunk-prefix=#on,off
#endkeyvals
