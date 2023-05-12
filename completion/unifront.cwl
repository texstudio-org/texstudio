# unifront package
# Matthew Bertucci 2023/05/08 for v1.0

#include:xcolor
#include:calc

#keyvals:\usepackage/unifront#c
red
blue
yellow
help
#endkeyvals

\currentchapter{%<name1%>}%<{name2}{name3}...%>
\currentsections{%<name1%>}%<{name2}{name3}...%>
\currentsubsections{%<name1%>}%<{name2}{name3}...%>
\newtitle{%<text%>%text}{%<number of chapters%>}{%<\currentchapter{name1}{name2}...%>}
\newchapter{%<title%>%title}{%<number of sections%>}{%<\currentsections{name1}{name2}...%>}#L1
\newsection{%<title%>%title}{%<number of subsections%>}{%<\currentsubsections{name1}{name2}...%>}#L2
\newsubsection{title}#L3