# fmtcount package
# Matthew Bertucci 10/23/2021 for v3.07

#include:ifthen
#include:xkeyval
#include:etoolbox
#include:fcprefix
#include:amsgen

#keyvals:\usepackage/fmtcount#c
raise
level
#endkeyvals

\ordinal{counter}
\ordinal{counter}[gender]
\FCordinal{counter}#*
\FCordinal{counter}[gender]#*

\fmtord{text}

\ordinalnum{number}
\ordinalnum{number}[gender]
\numberstring{counter}
\numberstring{counter}[gender]
\Numberstring{counter}
\Numberstring{counter}[gender]
\NUMBERstring{counter}
\NUMBERstring{counter}[gender]
\numberstringnum{number}
\numberstringnum{number}[gender]
\Numberstringnum{number}
\Numberstringnum{number}[gender]
\NUMBERstringnum{number}
\NUMBERstringnum{number}[gender]
\ordinalstring{counter}
\ordinalstring{counter}[gender]
\Ordinalstring{counter}
\Ordinalstring{counter}[gender]
\ORDINALstring{counter}
\ORDINALstring{counter}[gender]
\ordinalstringnum{number}
\ordinalstringnum{number}[gender]
\Ordinalstringnum{number}
\Ordinalstringnum{number}[gender]
\ORDINALstringnum{number}
\ORDINALstringnum{number}[gender]

\FMCuse{label}

\storeordinal{label}{counter}
\storeordinal{label}{counter}[gender]
\storeordinalstring{label}{counter}
\storeordinalstring{label}{counter}[gender]
\storeOrdinalstring{label}{counter}
\storeOrdinalstring{label}{counter}[gender]
\storeORDINALstring{label}{counter}
\storeORDINALstring{label}{counter}[gender]
\storenumberstring{label}{counter}
\storenumberstring{label}{counter}[gender]
\storeNumberstring{label}{counter}
\storeNumberstring{label}{counter}[gender]
\storeNUMBERstring{label}{counter}
\storeNUMBERstring{label}{counter}[gender]
\storeordinalnum{label}{number}
\storeordinalnum{label}{number}[gender]
\storeordinalstringnum{label}{number}
\storeordinalstringnum{label}{number}[gender]
\storeOrdinalstringnum{label}{number}
\storeOrdinalstringnum{label}{number}[gender]
\storeORDINALstringnum{label}{number}
\storeORDINALstringnum{label}{number}[gender]
\storenumberstring{label}{number}
\storenumberstringnum{label}{number}[gender]
\storeNumberstringnum{label}{number}
\storeNumberstringnum{label}{number}[gender]
\storeNUMBERstringnum{label}{number}
\storeNUMBERstringnum{label}{number}[gender]

\binary{counter}
\padzeroes
\padzeroes[number]
\binarynum{number}
\octal{counter}
\octalnum{number}
\hexadecimal{counter}
\HEXADecimal{counter}
\hexadecimalnum{number}
\HEXADecimalnum{number}
\decimal{counter}
\decimalnum{number}
\aaalph{counter}
\AAAlph{counter}
\aaalphnum{number}
\AAAlphnum{number}
\abalph{counter}
\ABAlph{counter}
\abalphnum{number}
\ABAlphnum{number}

\fmtcountsetoptions{options%keyvals}

#keyvals:\fmtcountsetoptions#c
fmtord=#level,raise
english={%<options%>}
UKenglish={%<options%>}
brazilian={%<options%>}
british={%<options%>}
USenglish={%<options%>}
american={%<options%>}
spanish={%<options%>}
portuges={%<options%>}
portuguese={%<options%>}
french={%<options%>}
frenchb={%<options%>}
francais={%<options%>}
german={%<options%>}
germanb={%<options%>}
ngerman={%<options%>}
ngermanb={%<options%>}
italian={%<options%>}
abbr#true,false
#endkeyvals

\FCloadlang{language%keyvals}

#keyvals:\FCloadlang#c,\usepackage/fmtcount#c
english
UKenglish
brazilian
british
USenglish
american
spanish
portuges
portuguese
french
frenchb
francais
german
germanb
ngerman
ngermanb
italian
#endkeyvals

\latinnumeralstring{counter}
\latinnumeralstring{counter}[prefix options]
\latinnumeralstringnum{number}
\latinnumeralstringnum{number}[prefix options]

\ProvidesFCLanguage{language}#*
