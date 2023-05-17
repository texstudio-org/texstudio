# codelisting package
# Matthew Bertucci 2023/05/12 for v1.0

#include:listings
#include:scontents

\begin{codestore}#V
\begin{codestore}[options%keyvals]#V
\end{codestore}

#keyvals:\begin{codestore}#c
%<st-name%>
st=%<st-name%>
store-at=%<st-name%>
# inherited from scontents
store-env=%<seq name%>
print-env#true,false
write-env=%<file.ext%>
write-out=%<file.ext%>
overwrite#true,false
force-eol#true,false
#endkeyvals

\tscode{st-name}
\tscode[code-keys%keyvals]{st-name}
\tscode*{st-name}
\tscode*[code-keys%keyvals]{st-name}
\tsdemo{st-name}
\tsdemo[code-keys%keyvals]{st-name}
\tsdemo*{st-name}
\tsdemo*[code-keys%keyvals]{st-name}

\setcodekeys{code-keys%keyvals}

#keyvals:\tscode,\tscode*,\tsdemo,\tsdemo*,\setcodekeys
settexcs={%<csname1,csname2,...%>}
settexcs2={%<csname1,csname2,...%>}
settexcs3={%<csname1,csname2,...%>}
texcs={%<csname1,csname2,...%>}
texcs2={%<csname1,csname2,...%>}
texcs3={%<csname1,csname2,...%>}
texcsstyle=%<font commands%>
texcs2style=%<font commands%>
texcs3style=%<font commands%>
setkeywd={%<keyword1,keyword2,...%>}
setkeywd2={%<keyword1,keyword2,...%>}
setkeywd3={%<keyword1,keyword2,...%>}
keywd={%<keyword1,keyword2,...%>}
keywd2={%<keyword1,keyword2,...%>}
keywd3={%<keyword1,keyword2,...%>}
keywdstyle=%<font commands%>
keywd2style=%<font commands%>
keywd3style=%<font commands%>
setemph={%<keyword1,keyword2,...%>}
setemph2={%<keyword1,keyword2,...%>}
setemph3={%<keyword1,keyword2,...%>}
emph={%<keyword1,keyword2,...%>}
emph2={%<keyword1,keyword2,...%>}
emph3={%<keyword1,keyword2,...%>}
emphstyle=%<font commands%>
emph2style=%<font commands%>
emph3style=%<font commands%>
numbers=#none,left
numberstyle=%<font commands%>
stringstyle=%<font commands%>
commentstyle=%<font commands%>
bckgndcolor=%<color commands%>
rulecolor=%<color commands%>
codeprefix=%<text%>
resultprefix=%<text%>
parindent=##L
ruleht=%<number%>
#endkeyvals