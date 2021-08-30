# phonenumbers package
# Matthew Bertucci 8/29/2021 for v2.3

#include:l3keys2e
#include:ltxcmds

\phonenumber{number}
\phonenumber[options%keyvals]{number}[extension]
\setphonenumbers{options%keyvals}

#keyvals:\phonenumber,\setphonenumbers
country=#AT,DE,FR,UK,US
link=#on,off
foreign=#international,american,european,off
foreign-area-code-sep=#space,brackets
home-country=#AT,DE,FR,UK,US,none
home-area-code=
area-code-sep=#slash,brackets,space,hyphen
area-code=#number,place,place-and-number
trunk-prefix=#on,off
#endkeyvals

\AreaCodesGeographic[options]#*
\AreaCodesNonGeographic[options]#*
\CountryCodes#*