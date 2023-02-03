# scrkbase package
# Matthew Bertucci 2022/05/18 for v3.36

#include:scrbase
#include:scrlogo

\KOMAProcessOptions#*
\KOMAExecuteOptions{option list}#*

\KOMAoptions{option list%keyvals}
\KOMAoption{option}{value list}

\KOMAoptionsOf{file with ext%file}#*
\KOMAoptionsOf[prefix]{file with ext%file}#*
\KOMAoptionOf{file with ext%file}{option}#*
\KOMAoptionsOf[prefix]{file with ext%file}{option}#*
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
