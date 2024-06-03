# l3sys-query package
# Matthew Bertucci 2024/06/02 for v1.0a

\QueryWorkingDirectory{result cmd%cmd}#d
\QueryFiles{spec}{function}
\QueryFiles[options%keyvals]{spec}{function}
\QueryFilesTF{spec}{function}{pre code}{empty list code}
\QueryFilesTF[options%keyvals]{spec}{function}{pre code}{empty list code}

#keyvals:\QueryFiles,\QueryFilesTF
recursive
ignore-case
reverse
pattern
sort=#date,name
type=#d,f
exclude=%<Lua pattern%>
#endkeyvals