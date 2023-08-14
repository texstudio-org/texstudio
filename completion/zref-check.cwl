# zref-check package
# Matthew Bertucci 2023/08/14 for v0.3.4

#include:zref-user
#include:zref-abspage
#include:ifdraft
#include:zref-hyperref

\zcheck{labellist}{text}#r
\zcheck[checks%keyvals]{labellist}{text}#r

#keyvals:\zcheck
# checks
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
manual
# local-only options
ignore
ok
#endkeyvals

\zctarget{label}{text}#l

\begin{zcregion}{label}#l
\end{zcregion}

\zrefchecksetup{options%keyvals}

# local/global options
#keyvals:\zcheck,\zrefchecksetup,\usepackage/zref-check#c
msglevel=#warn,info,none,infoifdraft,warniffinal
onpage=#labelseq,msg,labelseqifdraft,msgiffinal
#endkeyvals

# global-only options
#keyvals:\zrefchecksetup,\usepackage/zref-check#c
hyperref=#auto,true,false
closerange=%<integer%>
#endkeyvals
