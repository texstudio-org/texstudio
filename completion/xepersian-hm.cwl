# xepersian-hm package
# Matthew Bertucci 2022/05/07 for v1.1a

#include:l3keys2e
#include:graphicx
#include:zref-savepos
#include:xcolor
#include:xepersian

#keyvals:\usepackage/xepersian-hm#c
Kashida=#glyph,leaders+glyph,leaders+hrule,Off,On
linebreakpenalty=%<integer%>
ligatures=#aalt,ccmp,dlig,fina,init,locl,medi,rlig,default
color=#%color
kashidastretch=#kayhan,khorramshahr,kayhannavaar,kayhanpook,kayhansayeh,khoramshahr,khorramshahr,niloofar,paatch,riyaz,roya,shafigh,shafighKurd,shafighUzbek,shiraz,sols,tabriz,titr,titre,traffic,vahid,vosta,yaghut,yagut,yas,yekan,yermook,zar,ziba,default,noskip
#endkeyvals

\KashidaOff
\KashidaOn
\KashidaHMFixOff#*
\KashidaHMFixOn#*
\discouragebadlinebreaks{text}
\discouragebadlinebreaks[linebreakpenalty]{text}
\discouragebadlinebreaks[linebreakpenalty][kashidastretch]{text}
\XePersianHM#*