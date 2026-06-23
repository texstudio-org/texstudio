# hexdumptikz package
# Matthew Bertucci 2026/06/23 for v1.0.1

#include:tikz
#include:tikzlibrarychains

\begin{hexdumptikz}{file}
\begin{hexdumptikz}[options%keyvals]{file}
\end{hexdumptikz}

\hexdumptikzAddrToCol{address}
\hexdumptikzAddrToNodename{address}
\hexdumptikzAddrToRow{address}
\hexdumptikzLabelBytes[options%keyvals]{start-addr}{end-addr}
\hexdumptikzLabelBytesFallback[options%keyvals]{start-addr}{end-addr}
\hexdumptikzLabelBytesFallback{start-addr}{end-addr}
\hexdumptikzLabelBytes{start-addr}{end-addr}
\hexdumptikzPrint[options%keyvals]{selector}
\hexdumptikzPrint{selector}

# not documented
\hexdumptikzIterDump#S
\hexdumptikzMatchRow{arg1}{arg2}{arg3}#S
\hexdumptikzMatchStyle{arg1}{arg2}{arg3}#S
\hexdumptikzParseDump#S
\hexdumptikzParserDbg{arg}#S
\hexdumptikzParseRow{arg}#S
\hexdumptikzReset#S