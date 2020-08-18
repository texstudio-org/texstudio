# thmtools package
# muzimuzhi, 8 Aug 2020 for thmtools v0.72

\declaretheoremstyle{style name}
\declaretheoremstyle[options%keyvals]{style name}
\declaretheorem{envname}#N
\declaretheorem[options%keyvals]{envname}#N
\declaretheorem[options]{envname}[options%keyvals]#N
\declaretheorem{envname}[options%keyvals]#N
\listoftheorems
\listoftheorems[options%keyvals]
\listtheoremname
\begin{restatable}[thm title]{envname}{cmd name}
\begin{restatable}{envname}{cmd name}
\end{restatable}

#keyvals:\declaretheoremstyle
spaceabove=##L
spacebelow=##L
headfont
notefont
bodyfont
headpunct
notebraces=%<two chars%>
postheadspace=##L
headformat=%<code%>
headindent=##L
qed
#endkeyvals

#keyvals:\declaretheoremstyle,\declaretheorem
parent=%<counter%>
numberwithin=%<counter%>
within=%<counter%>
slibling=%<counter%>
numberlike=%<counter%>
sharenumber=%<counter%>
title
name
heading
numbered=#yes,no,unique
style
preheadhook
postheadhook
prefoothook
postfoothook
refname
Refname
shaded
thmbox=#L,M,S
mdframed={%<options%>}
#endkeyvals

#keyvals:\listoftheorems
title
ignore
ignoreall
show
showall
onlynamed
swapnumber
numwidth=##L
#endkeyvals
