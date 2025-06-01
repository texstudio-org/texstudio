# codelisting package
# Matthew Bertucci 2025/05/31 for v1.9

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
\tscode{st-name}[index]
\tscode[code-keys%keyvals]{st-name}
\tscode[code-keys%keyvals]{st-name}[index]
\tscode*{st-name}
\tscode*{st-name}[index]
\tscode*[code-keys%keyvals]{st-name}
\tscode*[code-keys%keyvals]{st-name}[index]
\tsdemo{st-name}
\tsdemo{st-name}[index]
\tsdemo[code-keys%keyvals]{st-name}
\tsdemo[code-keys%keyvals]{st-name}[index]
\tsdemo*{st-name}
\tsdemo*{st-name}[index]
\tsdemo*[code-keys%keyvals]{st-name}
\tsdemo*[code-keys%keyvals]{st-name}[index]
\tsresult{st-name}
\tsresult{st-name}[index]
\tsresult[code-keys%keyvals]{st-name}
\tsresult[code-keys%keyvals]{st-name}[index]
\tsresult*{st-name}
\tsresult*{st-name}[index]
\tsresult*[code-keys%keyvals]{st-name}
\tsresult*[code-keys%keyvals]{st-name}[index]
\tsmergedcode{st-name-index list}
\tsmergedcode[code-keys%keyvals]{st-name-index list}
\tsmergedcode*{st-name-index list}
\tsmergedcode*[code-keys%keyvals]{st-name-index list}
\tsexec{st-name}
\tsexec{st-name}[index]

\setcodekeys{code-keys%keyvals}
\setnewcodekey{new-key}{code-keys%keyvals}#s#%codelistingkey

#keyvals:\tscode,\tscode*,\tsdemo,\tsdemo*,\tsresult,\tsresult*,\tsmergedcode,\tsmergedcode*,\setcodekeys,\setnewcodekey
settexcs={%<csname1,csname2,...%>}
settexcs2={%<csname1,csname2,...%>}
settexcs3={%<csname1,csname2,...%>}
settexcs4={%<csname1,csname2,...%>}
texcs={%<csname1,csname2,...%>}
texcs2={%<csname1,csname2,...%>}
texcs3={%<csname1,csname2,...%>}
texcs4={%<csname1,csname2,...%>}
texcsstyle=%<font commands%>
texcs2style=%<font commands%>
texcs3style=%<font commands%>
texcs4style=%<font commands%>
setkeywd={%<keyword1,keyword2,...%>}
setkeywd2={%<keyword1,keyword2,...%>}
setkeywd3={%<keyword1,keyword2,...%>}
setkeywd4={%<keyword1,keyword2,...%>}
keywd={%<keyword1,keyword2,...%>}
keywd2={%<keyword1,keyword2,...%>}
keywd3={%<keyword1,keyword2,...%>}
keywd4={%<keyword1,keyword2,...%>}
keywdstyle=%<font commands%>
keywd2style=%<font commands%>
keywd3style=%<font commands%>
keywd4style=%<font commands%>
setemph={%<keyword1,keyword2,...%>}
setemph2={%<keyword1,keyword2,...%>}
setemph3={%<keyword1,keyword2,...%>}
setemph4={%<keyword1,keyword2,...%>}
emph={%<keyword1,keyword2,...%>}
emph2={%<keyword1,keyword2,...%>}
emph3={%<keyword1,keyword2,...%>}
emph4={%<keyword1,keyword2,...%>}
emphstyle=%<font commands%>
emph2style=%<font commands%>
emph3style=%<font commands%>
emph4style=%<font commands%>
letter=
other=
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
basicstyle=%<font commands%>
%codelistingkey
#endkeyvals

# not documented
\PkgDescription{arg}#S
\PkgInfo{arg1}{arg2}#S
