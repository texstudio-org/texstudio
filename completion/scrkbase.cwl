# scrkbase package
# Matthew Bertucci 11/19/2021 for v3.34

#include:scrbase

\KOMAProcessOptions#*
\KOMAExecuteOptions{option list}#*

\KOMAoptions{option list%keyvals}
\KOMAoption{option}{value list}

\KOMAoptionsOf{file with ext}#*
\KOMAoptionsOf[prefix]{file with ext}#*
\KOMAoptionOf{file with ext}{option}#*
\KOMAoptionsOf[prefix]{file with ext}{option}#*
\AfterKOMAoptions#*

\IfExistskomafont{element}{then code}{else code}#*
\IfIsAliaskomafont{element}{then code}{else code}#*
\setkomafont{element%keyvals}{commands}
\addtokomafont{element%keyvals}{commands}
\usekomafont{element%keyvals}
\usesizeofkomafont{element%keyvals}#*
\usefamilyofkomafont{element%keyvals}#*
\useseriesofkomafont{element%keyvals}#*
\useshapeofkomafont{element%keyvals}#*
\useencodingofkomafont{element%keyvals}#*
\usefontofkomafont{element%keyvals}#*
\addtokomafontrelaxlist{macro}#*
\addtokomafontgobblelist{macro}#*
\addtokomafontonearglist{macro}#*
\newkomafont{element}{default}#*
\newkomafont[warning]{element}{default}#*
\aliaskomafont{alias}{element}#*
