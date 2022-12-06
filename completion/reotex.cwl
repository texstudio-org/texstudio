# reotex package
# Matthew Bertucci 4/14/2022 for v1.1

#include:ifthen
#include:tikz
#include:verbatim
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibrarydecorations.shapes
#include:tikzlibrarycalc

\sync{start}{target}{labels}
\sync*{start}{target}{labels}
\lossysync{start}{target}{labels}
\lossysync*{start}{target}{labels}
\syncdrain{start}{target}{labels}
\syncdrain*{start}{target}{labels}
\syncspout{start}{target}{labels}
\syncspout*{start}{target}{labels}
\filter{start}{target}{labels}
\filter*{start}{target}{labels}
\fifoe{start}{target}{labels}
\fifoe*{start}{target}{labels}
\fifof{start}{target}{labels}
\fifof*{start}{target}{labels}
\asyncdrain{start}{target}{labels}
\asyncdrain*{start}{target}{labels}
\asyncspout{start}{target}{labels}
\asyncspout*{start}{target}{labels}
\fifon{start}{target}{labels}
\fifon*{start}{target}{labels}
\shiftfifon{start}{target}{labels}
\shiftfifon*{start}{target}{labels}
\lossyfifon{start}{target}{labels}
\lossyfifon*{start}{target}{labels}
\timer{start}{target}{labels}
\timer*{start}{target}{labels}
\ordered{start}{target}{labels}
\ordered*{start}{target}{labels}
\orderedn{start}{target}{labels}
\orderedn*{start}{target}{labels}
\bag{start}{target}{labels}
\bag*{start}{target}{labels}
\bagn{start}{target}{labels}
\bagn*{start}{target}{labels}
\set{start}{target}{labels}
\set*{start}{target}{labels}
\setn{start}{target}{labels}
\setn*{start}{target}{labels}
\delayset{start}{target}{labels}
\delayset*{start}{target}{labels}
\delaysetn{start}{target}{labels}
\delaysetn*{start}{target}{labels}
\keyedset{start}{target}{labels}
\keyedset*{start}{target}{labels}
\keyedsetn{start}{target}{labels}
\keyedsetn*{start}{target}{labels}

\ionode{reference}{point}{labels}
\mixednode{reference}{point}{labels}
\xrouter{reference}{point}{labels}

\Lchannel{channel name}{start}{target}{length}{orientation}{polarization}{labels}
\Lchannel[dashed]{%<channel name%>}{%<start%>}{%<target%>}{%<length%>}{%<orientation%>}{%<polarization%>}{%<labels%>}
\Lchannel*{channel name}{start}{target}{length}{orientation}{polarization}{labels}
\Lchannel*[dashed]{%<channel name%>}{%<start%>}{%<target%>}{%<length%>}{%<orientation%>}{%<polarization%>}{%<labels%>}
\Uchannel{channel name}{start}{target}{length}{orientation}{polarization}{labels}
\Uchannel[dashed]{%<channel name%>}{%<start%>}{%<target%>}{%<length%>}{%<orientation%>}{%<polarization%>}{%<labels%>}
\Uchannel*{channel name}{start}{target}{length}{orientation}{polarization}{labels}
\Uchannel*[dashed]{%<channel name%>}{%<start%>}{%<target%>}{%<length%>}{%<orientation%>}{%<polarization%>}{%<labels%>}

# not documented
\component{corner1}{corner2}{labels}#*
\reader{reference}{point}{labels}#*
\writer{reference}{point}{labels}#*
