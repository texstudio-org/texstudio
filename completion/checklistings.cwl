# checklistings package
# Matthew Bertucci 2022/06/14 for v1.0

#include:keyval
#include:kvoptions
#include:fancyvrb
#include:color
#include:listings

\checklistings{options%keyvals}

#keyvals:\usepackage/checklistings#c,\checklistings
withresult#true,false
withoutresult#true,false
showproblems#true,false
hideproblems#true,false
skipone
skiptwo
codestyle={%<fancyvrb options%>}
msgstyle={%<fancyvrb options%>}
errstyle={%<fancyvrb options%>}
codelst={%<listings options%>}
msglst={%<listings options%>}
errlst={%<listings options%>}
emptyoption=%<string%>
subdir=%<directory%>
prefix=%<prefix%>
ext=%<extension%>
prompt=%<prompt%>
compiler=%<path%>
compilerflags=%<flags%>
lastflags=%<flags%>
includecmd=%<command%>
html=%<path%>
#endkeyvals

\begin{chklisting}#V
\begin{chklisting}[options%keyvals]#V
\end{chklisting}

#keyvals:\begin{chklisting}
continue
include=%<label%>
fail
label=%<label%>
skipnone
skipone
skiptwo
hide
withresult
withoutresult
showproblems
hideproblems
#endkeyvals

\chklistingcmd
\chklistingmsg{label}
\chklistingerr{label}

\begin{ChkListingErr}#*V
\end{ChkListingErr}#*
\begin{ChkListingMsg}#*V
\end{ChkListingMsg}#*
\ChkListingErr#*
\chklistingfalse#*
\chklistingfile#*
\ChkListingMsg#*
\chklistingtrue#*
\ifchklisting#*
\setchklistingcmd{command}#*
\thechklisting#*