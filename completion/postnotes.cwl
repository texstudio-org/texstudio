# postnotes package
# Matthew Bertucci 2022/12/28 for v0.2.0

\postnote{text}
\postnote[options%keyvals]{text}

#keyvals:\postnote
mark=%<number%>
markstr=%<string%>
sortnum=%<number%>
nomark
label=##l
zlabel=##l
#endkeyvals

\postnotesection{text}
\postnotesection[options%keyvals]{text}

#keyvals:\postnotesection,\postnotesectionx
name=%<name%>
exp#true,false
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

# deprecated
\postnotesectionx{text}#S
\postnotesectionx[options]{text}#S
