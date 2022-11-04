# achemso class (distinct from achemso package; see achemso.cwl)
# Matthew Bertucci 2022/10/31 for v3.13e

#include:xkeyval
#include:geometry
#include:caption
#include:float
#include:graphicx
#include:setspace
#include:url
#include:natbib
#include:mciteplus
#include:natmove

#keyvals:\documentclass/achemso#c
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

\affiliation{affiliation}
\affiliation[short affiliation]{affiliation}
\alsoaffiliation{affiliation}
\alsoaffiliation[short affiliation]{affiliation}
\altaffiliation{affiliation}
\email{email%URL}#U
\fax{fax number}
\phone{phone number}
\title[short title%text]{text}
\begin{scheme}
\begin{scheme}[placement]
\end{scheme}
\begin{chart}
\begin{chart}[placement]
\end{chart}
\begin{graph}
\begin{graph}[placement]
\end{graph}
\SectionNumbersOff
\SectionNumbersOn
\SectionsOff 
\SectionsOn
\AbstractOff
\AbstractOn
\begin{acknowledgement}
\end{acknowledgement}
\begin{suppinfo}
\end{suppinfo}
\begin{tocentry}
\end{tocentry}
\latin{text}
\bibnote{text}
\bibnotemark#*
\bibnotetext{text}

# not in main documentation
\abbreviations{abbreviations}
\acknowledgementname#*
\acksize#*
\affilfont#*
\affilsize#*
\authorfont#*
\authorsize#*
\capsize#*
\chartname#*
\emailfont#*
\emailsize#*
\graphname#*
\keywords{keywords}#*
\printbibnotes#*
\refsize#*
\schemename#*
\suppinfoname#*
\suppsize#*
\thebibnote#*
\thechart#*
\thegraph#*
\thescheme#*
\titlefont#*
\titlesize#*
\tocentryname#*
\tocsize#*

# deprecated
\plainref{label}#Sr
