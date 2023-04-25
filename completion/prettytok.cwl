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
\prettyW %<⟨tokens⟩%> \prettystop
\prettyshowN %<⟨token⟩%>
\prettyshowC{csname}
\prettyeN{token list}
\prettyeW %<⟨tokens⟩%> \prettystop
\prettystop#S
