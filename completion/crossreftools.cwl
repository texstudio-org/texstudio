# crossreftools package
# Matthew Bertucci 1/8/2021 for v1.0

#keyvals:\usepackage/crossreftools#c
draft
final
cleverefcompat
#endkeyvals

\crtrefundefinedtext{text%plain}
\crtcrefundefinedcountervalue{integer}

\crtextractref{property%keyvals}{label}#r

#keyvals:\crtextractref
reference
page
anchor
name
unused
#endkeyvals

\crtcrefpage{label}#r
\crtrefnumber{label}#r
\crtrefname{label}#r
\crtrefanchor{label}#r
\crtrefunused{label}#r
\crtrefcounter{label}#r

\crtextractcref{property%keyvals}{label}#r

#keyvals:\crtextractcref
counter
number
result
reference
page
#endkeyvals

\crtcrefcounter{label}#r
\crtcrefnumber{label}#r
\crtcrefcountervalue{label}#r
\crtcrefresult{label}#r
\crtcrefreference{label}#r

\crtcrefname{counter}
\crtCrefname{counter}
\crtcrefpluralname{counter}
\crtCrefpluralname{counter}

\crtcrefnamebylabel{label}#r
\crtCrefnamebylabel{label}#r
\crtcref{label}#r
\crtCref{label}#r

\crthyperlink{anchor}{link text}
\crthypercref{label}#r
\crthyperCref{label}#r

\crtlnameref{label}#r
\crtlnameref*{label}#r
\crtunameref{label}#r
\crtunameref*{label}#r

\crtnameref{label}#r
\crtnameref*{label}#r

\crtprovidecurrentlabel{label content}
\crtprovidecurrentlabelname{nameref label content}
\crtprovidecurrentlabelinfo{label content}{nameref label content}
\crtcrossreflabel{label content}
\crtcrossreflabel[nameref label content]{label content}
\crtcrossreflabel[nameref label content]{label content}[label]#l
\crtcrossreflabel*{label content}
\crtcrossreflabel*[nameref label content]{label content}
\crtcrossreflabel*[nameref label content]{label content}[label]#l

\crtifdefinedlabel{label}{true}{false}
\crtifundefinedlabel{label}{true}{false}
\crtcrefifdefinedlabel{label}{true}{false}
\crtcrefifundefinedlabel{label}{true}{false}

\crtlistoflabels
\crtlistoflabels*
\crtlistoflabelsfileextension{extension}
\listoflabelsname
\crtlistoflabelsstructurelevel{counter}

\crtprelabelhook{code}
\crtpostlabelhook{code}

# not documented
\crossreftoolspackageversion#S
\crtaddlabeltotoc{label}#*
\crtrefpage{label}#*r
\listoflabelstructurelevel#*
\ifcrtfinal#*
\crtfinaltrue#*
\crtfinalfalse#*
\ifcleverefcompatmode#*
\cleverefcompatmodetrue#*
\cleverefcompatmodefalse#*