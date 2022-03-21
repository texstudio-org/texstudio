# achemso package (distinct from achemso class; see class-achemso.cwl)
# Matthew Bertucci 3/19/2022 for v3.13c

#include:xkeyval
#include:natbib
#include:mciteplus
#include:natmove

#keyvals:\usepackage/achemso#c
abbreviations#true,false
articletitle#true,false
biblabel=#plain,brackets,period,fullstop
biochem#true,false
biochemistry#true,false
chaptertitle#true,false
doi#true,false
email#true,false
etalmode=#firstonly,truncate
hyperref#true,false
journal=#aaembp,aaemcq,aamick,aanmf6,aapmcd,aastgj,abmcb8,abseba,acbcct,accacs,achre4,acncdm,acsccc,acscii,acsodf,aeacb3,aeacc4,aeecco,aelccp,aesccq,aewcaa,afsthl,aidcbc,amacgu,amachv,amclct,amlccd,amlcef,amrcda,anaccx,ancac3,ancham,aoiab5,apcach,apchd5,appccd,asbcd6,ascecg,ascefj,bcches,bichaw,bomaf6,cgdefu,chreay,cmatex,crtoec,enfuem,esthag,estlcu,iecred,inoraj,jaaucr,jacsat,jafcau,jceaax,jceda8,jcisd8,jctcce,jmcmar,jnprdf,joceah,jpcafh,jpcbfk,jpccck,jpclcd,jprobs,langd5,mamobx,mpohbp,nalefd,oprdfk,orgnd7,orlef7
keywords#true,false
layout=#traditional,twocolumn
manuscript=#article,note,communication,review,letter,perspective
maxauthors=%<number%>
super#true,false
usetitle#true,false
#endkeyvals

#ifOption:journal=orlef7
#include:xcolor
orglett#B
#endif

\latin{text}
\bibnote{text}
\bibnotemark#*
\bibnotetext{text}

# not in main documentation
\printbibnotes#*
\thebibnote#*