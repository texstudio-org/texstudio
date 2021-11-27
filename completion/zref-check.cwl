# zref-check package
# Matthew Bertucci 11/26/2021 for v0.2.1

#include:zref-user
#include:zref-abspage
#include:ifdraft
#include:l3keys2e
#include:zref-hyperref

\zcheck{labellist}{text}#r
\zcheck[checks%keyvals]{labellist}{text}#r

#keyvals:\zcheck
thispage
prevpage
nextpage
pagegap
facing
above
below
pagesbefore
ppbefore
pagesafter
ppafter
before
after
thischap
prevchap
nextchap
chapsbefore
chapsafter
thissec
prevsec
nextsec
secsbefore
secsafter
close
far
#endkeyvals

\zctarget{label}{text}#l

\begin{zcregion}{label}#l
\end{zcregion}

\zrefchecksetup{options%keyvals}

#keyvals:\zrefchecksetup,\usepackage/zref-check#c
hyperref=#auto,true,false
msglevel=#warn,info,none,obeydraft,obeyfinal
onpage=#labelseq,msg,obeydraft,obeyfinal
closerange=%<integer%>
labelcmd=%<csname%>
#endkeyvals
