# enverb package
# Matthew Bertucci 2024/08/29 for v1.0

#include:expkv-def

\enverb{keyvals}
\enverb{keyvals}[keyvals%plain]
\enverb*{keyvals}
\enverbBody
\enverbExecute
\enverbListing{env}{args}
\enverbsetup{keyvals}

#keyvals:\enverb,\enverb*,\enverbsetup
ignore=%<integer%>
auto-ignore#true,false
more-ignore=%<integer%>
bol=%<tokens%>
bol+=%<tokens%>
+bol=%<tokens%>
eol=%<tokens%>
eol+=%<tokens%>
+eol=%<tokens%>
key-handler=%<code%>
key-set=%<set%>
oarg-not-enverb#true,false
#endkeyvals