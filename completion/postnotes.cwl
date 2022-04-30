# postnotes package
# Matthew Bertucci 2022/04/29 for v0.1.2

\postnote{text}
\postnote[options%keyvals]{text}

#keyvals:\postnote
mark=%<mark%>
sortnum=%<number%>
nomark
label=##l
zlabel=##l
#endkeyvals

\postnotesection{text}
\postnotesection[options%keyvals]{text}
\postnotesectionx{text}
\postnotesectionx[options%keyvals]{text}

#keyvals:\postnotesection,\postnotesectionx
name=%<name%>
#endkeyvals

\printpostnotes
\postnoteref{label}#r
\postnoteref*{label}#r
\postnotezref{label}#*r
\postnotezref*{label}#*r
\postnotesetup{options%keyvals}

#keyvals:\postnotesetup
heading={%<text%>}
format={%<font commands%>}
listenv=%<envname%>
makemark={%<code%>}
maketextmark={%<code%>}
pretextmark={%<code%>}
posttextmark={%<code%>}
postprintnote={%<code%>}
style=#endnotes,pagenote
hyperref=#auto,true,false
backlink#true,false
sort#true,false
#endkeyvals

\pnhdchapfirst#*
\pnhdchaplast#*
\pnhdnamefirst#*
\pnhdnamefirst#*
\pnhdnamelast#*
\pnhdnamelast#*
\pnhdnotes#*
\pnhdpagefirst#*
\pnhdpagelast#*
\pnhdsectfirst#*
\pnhdsectlast#*
\pnhdtopage#*
\pnhdtopages#*
\pnheaderdefault#*
\pnheading#*
\pnthechapter#*
\pnthechapternextnote#*
\pnthepage#*
\pnthesection#*
\pnthesectionnextnote#*
\pntitle#*
\thepostnote#*
\thepostnotesection#*
\thepostnotetext#*
