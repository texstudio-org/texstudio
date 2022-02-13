# businesscard-qrcode class
# Matthew Bertucci 2/12/2022 for v1.2

#include:kvoptions
#include:class-extarticle
#include:marvosym
#include:fontawesome
#include:qrcode
#include:etoolbox
#include:DejaVuSans
#include:fontenc
# loads T1 option of fontenc
#include:wrapfig
#include:geometry
#include:varwidth
#include:calc
#include:crop

#keyvals:\documentclass/businesscard-qrcode#c
paperwidth=##L
paperheight=##L
contentwidth=##L
contentheight=##L
fontsize=##L
padding=##L
cutdist=%<number%>
cutlen=%<number%>
textwidth=%<factor%>
qrwidth=%<factor%>
lang=%<lang prefix%>
address#true,false
noaddress
hint#true,false
nohint
icon#true,false
noicon
rightalign#true,false
leftalign
iconleft#true,false
iconright
fill#true,false
nofill
qrfirst#true,false
textfirst
https#true,false
www
#endkeyvals

\content
\papersize
\padding
\border
\cutlen
\textpercents
\imagepercents
\lang
\protdisplay
\protprefix
\printaddress

\registerData{data type}#*

\type{type}
\givennames{given names}
\familynames{family names}
\honoricprefix{prefix}
\honoricsuffix{suffix}
\additionalnames{names}
\pobox{PO box}
\extaddr{address extension}
\street{street}
\city{city}
\region{region}
\zip{ZIP code}
\country{country}
\phone{phone number}
\email{email%URL}#U
\jabber{jabber address%URL}#U
\matrixorg{matrix address%URL}#U
\cloud{nextcloud ID%URL}#U
\homepage{URL}#U
\wordpress{URL}#U
\drupal{URL}#U
\joomla{URL}#U
\wikipedia{page name%URL}#U
\link{URL}#U
\world{URL}#U
\git{URL}#U
\gitea{URL}#U
\github{account name%URL}#U
\facebook{account name%URL}#U
\twitter{account name%URL}#U
\youtube{account name%URL}#U
\google{account name%URL}#U
\pgpurl{URL}#U
\pgpfingerprint{fingerprint%URL}#U

\enforceright#*
\exec{csname}#*
\insa{csname1}{csname2}#*
\insa[text%plain]{csname1}{csname2}#*
\ifexists{csname}{code}#*
\ifboth{csname1}{csname2}{code}#*
\ifany{csname1}{csname2}{code}#*
\cond{csname}#*
\heightscale#*

\name#*
\vcard#*
\address#*
\inserttext#*
\insertqrcode#*
\insertname#*

\drawcard

\tl#*
\tr#*
\bl#*
\br#*

# from T1 option of fontenc
\DH#n
\NG#n
\dj#n
\ng#n
\k{arg}#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\quotedblbase#n
\quotesinglbase#n
\textquotedbl#n
\DJ#n
\th#n
\TH#n
\dh#n
\Hwithstroke#*n
\hwithstroke#*n
\textogonekcentered{arg}#*n
\guillemetleft#n
\guillemetright#n