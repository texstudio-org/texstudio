# currency package
# Matthew Bertucci 12/10/2021 for v0.4

#include:siunitx
#include:pgfkeys
#include:etoolbox
#include:textcomp
#include:eurosym

\DefineCurrency{ISO}{maps%keyvals}
\CurrencySetup{maps%keyvals}
\CurrencySetupAppend{maps%keyvals}

#keyvals:\DefineCurrency,\CurrencySetup,\CurrencySetupAppend
name={%<name%>}
plural={%<plural%>}
iso={%<ISO%>}
symbol={%<symbol%>}
pre-between={%<tokens%>}
post-between={%<tokens%>}
before={%<tokens%>}
before+={%<tokens%>}
before<={%<tokens%>}
font={%<tokens%>}
font+={%<tokens%>}
after={%<tokens%>}
after+={%<tokens%>}
after<={%<tokens%>}
prefix={%<tokens%>}
kind=#iso,plural,name,symbol
cents=#true,false,always
pre#true,false
number#true,false
base=%<integer%>
#endkeyvals

\currencyunit

\displayCurrency{ISO}{value}#*
\displayCurrency{ISO}[options]{value}#*
\displayCurrencySymbol{ISO}#*
\displayCurrencySymbol{ISO}[options]#*
\SetPrecision#*
\Unknown#S