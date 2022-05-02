# listofitems package
# Matthew Bertucci 10/11/2021 for v1.63

\setsepchar{character}
\setsepchar[nested sep char]{character}
\readlist{cmd}{list}#d
\readlist*{cmd}{list}#d
\greadlist{cmd}{list}#d
\greadlist*{cmd}{list}#d
\showitems{list cmd}
\ignoreemptyitems#*
\reademptyitems#*
\foreachitem%<\var%>\in%<\list%>{%<code%>}
\foreachitem{cmd}#Sd
\in#S
\itemtomacro{list cmd}[index]{cmd}#d
\gitemtomacro{list cmd}[index]{cmd}#d
\listlen{list cmd}[index]
\defpair{%<<tok1><tok2>...%>}
\insidepair%<<tok1><tok2>%>{%<expression%>}{%<cmd%>}#d
\loiname#S
\loiver#S
\loidate#S
