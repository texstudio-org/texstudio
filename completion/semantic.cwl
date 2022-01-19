# semantic package
# Matthew Bertucci 1/18/2022 for v2.0ε

#keyvals:\usepackage/semantic#c
ligature
inference
tdiagram
reserved
shorthand
#endkeyvals

\mathlig{characters}{ligature commands%formula}
\mathligson
\mathligsoff
\mathligprotect{macro%cmd}

\inference{line1 \\ ... \\ lineN%formula}{conclusion%formula}
\inference[name]{line1 \\ ... \\ lineN%formula}{conclusion%formula}
\inference*{line1 \\ ... \\ lineN%formula}{conclusion%formula}
\inference*[name]{line1 \\ ... \\ lineN%formula}{conclusion%formula}

\setpremisesend{length}
\setpremisesspace{length}
\setnamespace{length}

\predicate{formula}#*
\predicatebegin#*
\predicateend#*

\compiler{%<source%>,%<machine%>,%<target%>}
\interpreter{%<source%>,%<language%>}
\program{%<program%>,%<language%>}
\machine{%<machine%>}

\reservestyle{macro%cmd}{formatting%definition}#d
\reservestyle[spacing cmd]{macro%cmd}{formatting%definition}#d
\<#S

\comp{command%plain}{environment%formula}
\eval{command%plain}{environment%formula}

\evalsymbol
\evalsymbol[superscript%formula]
\compsymbol
\compsymbol[superscript%formula]

\exe{program}{data%formula}
\exe{program}[machine%formula]{data%formula}

\TestForConflict{command list}#*
\semanticDate#S
\semanticVersion#S