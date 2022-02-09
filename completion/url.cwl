# tbraun 5.01.2007; updated by Matthew Bertucci 9/27/2021 for v3.4
# ctan url package

#keyvals:\usepackage/url#c
obeyspaces
hyphens
spaces
lowtilde
allowmove
#endkeyvals

\url{URL}#U
\path{URL}#U
\urldef{cmd}#*d
\DeclareUrlCommand{cmd}{definition}#*d
\urlstyle{style%keyvals}#*
#keyvals:\urlstyle#c
tt
rm
sf
same
#endkeyvals
\UrlBreaks#*
\UrlBigBreaks#*
\UrlNoBreaks#*
\UrlOrds#*
\UrlSpecials#*
\UrlTildeSpecial#*
\UrlFont#*
\UrlLeft#*
\UrlRight#*
\Urlmuskip#*
\UrlBreakPenalty#*
\UrlBigBreakPenalty#*
