# prettytok package
# Matthew Bertucci 2023/04/18 for v0.2.0

#include:precattl

#keyvals:\usepackage/prettytok#c
mode=#term-8bit,term-shell,html
html-file-name=%<file name%>
html-refresh-strategy=%<value 0-4%>
html-refresh-duration=%<milliseconds%>
term-prefix=%<string%>
term-prefix-more=%<string%>
term-wrap-limit=%<number%>
term-shell-decode-cmd=%<command%>
term-shell-decode-cmd-print
#endkeyvals

\prettyN{token list}
\prettyX{token list}
\prettyO{token list}
\prettyV{token list}
\prettyW %<⟨token list⟩%> \prettystop
\prettyshowN %<⟨token⟩%>
\prettyshowC{csname}
\prettyeN{token list}
\prettyeW %<⟨token list⟩%> \prettystop
\prettystop#S

# expl3 interface
\pretty:n {%<⟨token list⟩%>}#/%expl3
\pretty:x {%<⟨token list⟩%>}#/%expl3
\pretty:o {%<⟨token list⟩%>}#/%expl3
\pretty:V %<⟨tl var⟩%>#/%expl3
\pretty:w %<⟨token list⟩%> \prettystop#/%expl3
\prettyshow:N %<⟨token⟩%>#/%expl3
\prettyshow:c {%<⟨token name⟩%>}#/%expl3
\pretty:N %<⟨token⟩%>#/%expl3
\pretty:c {%<⟨token name⟩%>}#/%expl3
\pretty:nn {%<⟨token list⟩%>} {%<⟨token list⟩%>}#/%expl3
\pretty:nnn {%<⟨token list⟩%>} {%<⟨token list⟩%>} {%<⟨token list⟩%>}#/%expl3
\prettye:n {%<⟨token list⟩%>}#/%expl3
\prettye:w %<⟨token list⟩%> \prettystop#/%expl3
\prettye:nn {%<⟨token list⟩%>} {%<⟨token list⟩%>}#/%expl3
\prettye:nnn {%<⟨token list⟩%>} {%<⟨token list⟩%>} {%<⟨token list⟩%>}#/%expl3
\prettye:nw {%<⟨callback⟩%>} %<⟨token list⟩%> \prettystop#/%expl3
\prettye:nnw {%<⟨callback⟩%>} {%<⟨token list⟩%>} %<⟨token list⟩%> \prettystop#/%expl3
\prettye:nnnw {%<⟨callback⟩%>} {%<⟨token list⟩%>} {%<⟨token list⟩%>} %<⟨token list⟩%> \prettystop#/%expl3
