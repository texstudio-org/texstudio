# newverbs package
# Matthew Bertucci 10/5/2021 for v1.6

#include:shortvrb

\newverbcommand{cmd}{code before}{code after}#d
\newverbcommand{cmd}[verbcmd]{code before}{code after}#d
\renewverbcommand{cmd}{code before}{code after}
\renewverbcommand{cmd}[verbcmd]{code before}{code after}
\provideverbcommand{cmd}{code before}{code after}#d
\provideverbcommand{cmd}[verbcmd]{code before}{code after}#d

\qverb|%<verb text%>|
\qverb{verbatimSymbol}#S
\qverbbeginquote#*
\qverbendquote#*
\fverb|%<verb text%>|
\fverb{verbatimSymbol}#S

\MakeSpecialShortVerb{%<verb cmd%>}{\%<character%>}
\MakeSpecialShortVerb*{%<verb cmd%>}{\%<character%>}

\collectverb{%<code%>}{%<verb text%>}#*
\collectverb{%<code%>}{verbatimSymbol}#S
\collectverb*{%<code%>}{%<verb text%>}#*
\collectverb*{%<code%>}{verbatimSymbol}#S
\Collectverb{%<code%>}{%<verb text%>}#*
\Collectverb{%<code%>}{verbatimSymbol}#S
\Collectverb*{%<code%>}{%<verb text%>}#*
\Collectverb*{%<code%>}{verbatimSymbol}#S
\collectverbenv{code}#*
\collectverbenv*{code}#*
\Collectverbenv{code}#*
\Collectverbenv*{code}#*

\newverbsfont#*
\verbdef{cmd}{verb text}#d
\verbdef{cmd}{verbatimSymbol}#S
\verbdef*{cmd}{verb text}#d
\verbdef*{cmd}{verbatimSymbol}#S
\Verbdef{cmd}{verb text}#*d
\Verbdef{cmd}{verbatimSymbol}#S
\Verbdef*{cmd}{verb text}#*d
\Verbdef*{cmd}{verbatimSymbol}#S