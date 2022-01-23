# forarray package
# Matthew Bertucci 1/22/2022 for v1.01

\ForEach{separator}{function}{list}#*
\thislevelitem#*
\thislevelcount#*
\ForEachX{separator}{function}{list token}#*
\ForEachSublevel{separator}{function}#*
\ForEachD{%<separator%>}{%<function%>} %<<list> <separator>%> \endforeach#*
\endforeach#S
\ExitForEach#*
\ForArray{sep list}{sublevel tok}{func list sep}{func list}{array}#*
\ForArray{sep list}[marker list]{sublevel tok}{func list sep}{func list}{array}#*
\thislevelmarker#*
\thislevelnr#*
\ExitForEachLevels{start level}{num of levels}#*
\DefineArrayVar{name}{varnamesep}{varlistsep}{varlist}{varcontentlistsep}{varcontent}#*
\DefineArrayVars{varlistsep}{arraydefsep}{arraynamesep}{contentsep}{varnamesep}{varlist}{contentlist}#*
\DefineArrayDefault{arraylistsep}{varnamesep}{indexvar}{defaultvar}{arraylist}#*
\DefineArrayVarTo{varlistsep}{varnamesep}{array name}{content}{varlist}#*
\CommandForEach{varlist sep}{command}{var list}#*
\FunctionForEach{varlist sep}{command}{var list}#*