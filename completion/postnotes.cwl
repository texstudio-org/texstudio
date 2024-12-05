# postnotes package
# Matthew Bertucci 2024/12/05 for v0.5.1

#keyvals:\usepackage/postnotes#c
deprecatedheadervars#true,false
#endkeyvals

#ifOption:deprecatedheadervars
\pnhdchapfirst#*
\pnhdchaplast#*
\pnhdnamefirst#*
\pnhdnamelast#*
\pnhdpagefirst#*
\pnhdpagelast#*
\pnhdsectfirst#*
\pnhdsectlast#*
#endif
#ifOption:deprecatedheadervars=true
\pnhdchapfirst#*
\pnhdchaplast#*
\pnhdnamefirst#*
\pnhdnamelast#*
\pnhdpagefirst#*
\pnhdpagelast#*
\pnhdsectfirst#*
\pnhdsectlast#*
#endif

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
