# luaxml package
# Matthew Bertucci 2024/11/17 for v0.2b

#include:luacode

#keyvals:\usepackage/luaxml#c
default
#endkeyvals

\LXMLRule{%<CSS selector%>}|%<transformation rule%>|
\LXMLRule[%<options%>]{%<CSS selector%>}|%<transformation rule%>|
\LXMLRule[options%keyvals]{CSS selector}{verbatimSymbol}#S

#keyvals:\LXMLRule#c
verbatim
transformer=%<transformer%>
#endkeyvals

\LXMLSnippet{XML code}
\LXMLSnippet[transformer]{XML code}
\LXMLSnippet*{HTML code}
\LXMLSnippet*[transformer]{HTML code}
\LXMLInputFile{XML file%file}
\LXMLInputFile[transformer]{XML file%file}
\LXMLInputFile*{HTML file%file}
\LXMLInputFile*[transformer]{HTML file%file}
\begin{LXMLCode}{transformer}
\end{LXMLCode}
\begin{LXMLCode*}{transformer}
\end{LXMLCode*}

# not documented
\LXMLUseTransformer{arg}#S
\LXMLDeclareTransformer{arg}#S
\LXMLLoadDefaults#S
