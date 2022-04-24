# zref-check package
# Matthew Bertucci 4/24/2022 for v0.3.0

#include:zref-user
#include:zref-abspage
#include:ifdraft
#include:zref-hyperref

\zcheck{labellist}{text}#r
\zcheck[checks%keyvals]{labellist}{text}#r

#keyvals:\zcheck
thispage
prevpage
nextpage
otherpage
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

#keyvals:\zrefchecksetup
hyperref=#auto,true,false
msglevel=#warn,info,none,infoifdraft,warniffinal
onpage=#labelseq,msg,labelseqifdraft,msgiffinal
closerange=%<integer%>
#endkeyvals
