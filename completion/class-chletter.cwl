# chletter class
# Matthew Bertucci 2023/03/14 for v2.0

#keyvals:\documentclass/chletter#c
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
leqno
fleqn
onecolumn
twocolumn
leftwin
leftsig
foldmark
footfill
#endkeyvals

\titlehead#L
\titletopheight#L
\titlemidheight#L
\titlebotheight#L
\titlemargin#L
\titlewidth#L
\addressmargin#L
\addresswidth#L

\begin{letter}{address}
\begin{letter}[i|n]{address}
\end{letter}

\toname#*
\toaddress#*
\makelabels
\stopbreaks
\startbreaks
\theletter#*
\name{name}
\address{address}
\location{location}
\telephone{number}
\return{address}
\signature{signature}
\fromname#*
\fromaddress#*
\fromlocation#*
\telephonenum#*
\returnaddress#*
\fromsig#*
\object{text}
\opening{text}
\closing{text}
\salutation#*
\valediction#*
\ps{header%text}{text}
\encl{text}
\cc{names}
\enclname#*
\ccname#*

# not in main documentation
\closingmatter#*
\foldmark#*
\footfill#*
\headtoname#*
\indentedwidth#*
\longindentation#*
\pagename#*
\splitfield{arg1}{arg2}#S
\startlabels#*
\titlebotmatter#*
\titlemidmatter#*
\titletopmatter#*