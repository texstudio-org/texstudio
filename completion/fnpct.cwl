# fnpct package
# Matthew Bertucci 10/18/2021 for v1.0

#include:l3keys2e
#include:translations

\footnote*[number]{text}
\footnote*{text}
\footnotemark*#*
\footnotemark*[number]#*

\setfnpct{options%keyvals}

#keyvals:\setfnpct
dont-mess-around#true,false
reverse#true,false
ranges#true,false
add-trailing-token={%<token%>{%<name%>}}
add-trailing-token={[%<before%>]%<token%>[%<after%>]{%<name%>}}
activate-trailing-tokens={%<tokenlist%>}
deactivate-trailing-tokens={%<tokenlist%>}
before-footnote-space=##L
before-dot-space=##L
before-comma-space=##L
before-punct-space=##L
after-dot-space=##L
after-comma-space=##L
after-punct-space=##L
mult-fn-delim={%<code%>}
separation-symbol=%<symbol%>
range-symbol=%<symbol%>
print-separation={%<code%>}
print-range={%<code%>}
keep-ranges#true,false
#endkeyvals

\multfootsep#*
\multfootrange#*

#ifOption:multiple
\multfootnote{fn1;fn2;...}
\multfootnote*{fn1;fn2;...}
#endif

\AdaptNote{cmd}{args}{code}#*
\AdaptNote{cmd}{args}[counter]{code}#*
\AdaptNoteName{csname}{args}{code}#*
\AdaptNoteName{csname}{args}[counter]{code}#*
\MultVariant{cmd}#*
\MultVariantName{csname}#*
\AddPunctuation[%<before%>]%<token%>[%<after%>]{%<name%>}#*