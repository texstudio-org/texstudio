# postnotes package
# Matthew Bertucci 2024/12/04 for v0.5.0

\postnote{text}
\postnote[options%keyvals]{text}

#keyvals:\postnote
mark=%<number%>
markstr=%<string%>
sortnum=%<number%>
nomark
label=##l
zlabel=##l
maybemulti
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
multiple#true,false
multisep=%<separator%>
pretextmark={%<code%>}
posttextmark={%<code%>}
postprintnote={%<code%>}
style=#endnotes,pagenote
hyperref=#auto,true,false
backlink#true,false
sort#true,false
checkduplicates#true,false
checkfloats#true,false
maybemulti#true,false
counteraux#true,false
#endkeyvals

\pnhdnotes#*
\pnhdtopage#*
\pnhdtopages#*
\pnheaderdefault#*
\pnheading#*
\pnidnextnote#*
\pnthechapter#*
\pnthechapternextnote#*
\pnthepage#*
\pnthesection#*
\pnthesectionnextnote#*
\pntitle#*
\thepostnote#*
\theHpostnote#*
\thepostnotesection#*
\theHpostnotesection#*
\thepostnotetext#*
\theHpostnotetext#*
\pnsetcounteraux{integer}#*
\pnaddtocounteraux{integer}#*

# deprecated
\pnhdchapfirst#S
\pnhdchaplast#S
\pnhdnamefirst#S
\pnhdnamelast#S
\pnhdpagefirst#S
\pnhdpagelast#S
\pnhdsectfirst#S
\pnhdsectlast#S
