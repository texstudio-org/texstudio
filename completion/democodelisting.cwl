# democodelisting package
# Matthew Bertucci 2022/09/05 for v1.0beta

#include:listings
#include:scontents

\begin{stcode}
\begin{stcode}[options%keyvals]
\end{stcode}

#keyvals:\begin{stcode}
st=%<st-name%>
store-env=%<st-name%>
print-env#true,false
write-env=%<file.ext%>
write-out=%<file.ext%>
overwrite#true,false
force-eol#true,false
#endkeyvals

\DisplayCode{st-name}
\DisplayCode[options%keyvals]{st-name}

\DemoCode{st-name}
\DemoCode[options%keyvals]{st-name}
\DemoCode{st-name}[length]#*
\DemoCode[options%keyvals]{st-name}[length]#*

\TabbedDemoCode{st-name}
\TabbedDemoCode[options%keyvals]{st-name}
\TabbedDemoCode{st-name}[length]#*
\TabbedDemoCode[options%keyvals]{st-name}[length]#*

\setdclisting{options%keyvals}

#keyvals:\DisplayCode,\DemoCode,\TabbedDemoCode,\setdclisting
settexcs={%<list of csnames%>}
texcs={%<list of csnames%>}
texcsstyle=%<font commands%>
settexcs2={%<list of csnames%>}
texcs2={%<list of csnames%>}
texcs2style=%<font commands%>
settexcs3={%<list of csnames%>}
texcs3={%<list of csnames%>}
texcs3style=%<font commands%>
setkeywd={%<list of csnames%>}
keywd={%<list of keywords%>}
keywdstyle=%<font commands%>
setkeywd2={%<list of keywords%>}
keywd2={%<list of keywords%>}
keywd2style=%<font commands%>
setkeywd3={%<list of keywords%>}
keywd3={%<list of keywords%>}
keywd3style=%<font commands%>
setemph={%<identifier list%>}
emph={%<identifier list%>}
emphstyle=%<font commands%>
setemph2={%<identifier list%>}
emph2={%<identifier list%>}
emph2style=%<font commands%>
setemph3={%<identifier list%>}
emph3={%<identifier list%>}
emph3style=%<font commands%>
stringstyle=%<font commands%>
commentstyle=%<font commands%>
bckgndcolor=#%color
rulecolor=#%color
numbers=#none,left
numberstyle=%<font commands%>
codeprefix=%<prefix%>
resultprefix=%<prefix%>
#endkeyvals

# not documented
\setdcpar{options}#*
\begin{verbsc}{options}#*V
\end{verbsc}#*
\DisplayCodeB{st-name}#*
\DisplayCodeB[options]{st-name}#*
\DemoCodeB{st-name}#*
\DemoCodeB[options]{st-name}#*
\TabbedDemoCodeB{st-name}#*
\TabbedDemoCodeB[options]{st-name}#*