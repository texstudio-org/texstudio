# zref-check package
# Matthew Bertucci 12/9/2021 for v0.2.2

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
msglevel=#warn,info,none,infoifdraft,warniffinal
onpage=#labelseq,msg,labelseqifdraft,msgiffinal
closerange=%<integer%>
labelcmd=%<csname%>
#endkeyvals
