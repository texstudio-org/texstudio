# yaletter class
# Matthew Bertucci 4/27/2022 for v1.1

#include:xkeyval
#include:geometry
#include:fancyhdr
#include:textpos

\yadate{date}
\yahdateskip#*
\yadatestyle#*
\yainsideaddr{address%text}
\yahinsideaddrskip#*
\yainsideaddrstyle#*
\yasalutation{text}
\yahsalutationskip#*
\yasalutationstyle#*
\yafarewell{text}
\yahfarewellskip#*
\yafarewellstyle#*
\yasignature{signature}
\yahsignatureskip#*
\yasignaturestyle#*
\yaenclosure
\yahenclosureskip#*
\yaenclosurestyle#*

\yaoptions{options%keyvals}

#keyvals:\yaoptions
pageheight=##L
pagewidth=##L
lftmarg=##L
rgtmarg=##L
topmarg=##L
botmarg=##L
footskip=##L
headsep=##L
headheight=##L
headwidth=##L
headrulewidth=##L
footrulewidth=##L
predate=##L
postdate=##L
datehskip=##L
preinsideaddr=##L
postinsideaddr=##L
insideaddrhskip=##L
presalutation=##L
postsalutation=##L
saluword=%<word%>
salupunct=%<punctuation%>
saluskip=##L
prefarewell=##L
postfarewell=##L
farewellskip=##L
farewellword=%<word%>
farewellpunct=%<punctuation%>
presignature=##L
postsignature=##L
signatureskip=##L
signatureword=%<word%>
preenclosure=##L
postenclosure=##L
enclosureskip=##L
enclosureword=%<word%>
parskip=##L
parindent=##L
datafile=%<file%>
#endkeyvals

\defineletterhead{name%specialDef}{code%text}#s#%yaletterhead
\yauseletterhead{name%keyvals}
#keyvals:\yauseletterhead#c
%yaletterhead
#endkeyvals

\yaletterblock
\yalettermodblock
\yaletternormal
\yaparskip#*
\yaparindent#*

\yawriter
\yasetwriter{name}
\yawriterstyle#*
\yasetaddressee{name}
\yaaddresseestyle#*
\yaaddressee
\yathedate
\yalastpage

\defineaddress{name%specialDef}{short name%text}{code%text}#s#%yaaddress
\yatoaddress{name%keyvals}
\yareturnaddress{name%keyvals}
\yafromaddress{name%keyvals}
\yaaddress{name%keyvals}
#keyvals:\yatoaddress#c,\yareturnaddress#c,\yafromaddress#c,\yaaddress#c
%yaaddress
#endkeyvals

\yaenvelope{width}{height}
\yaenvunit{unit}
\yaenvrethskip#*
\yaenvretvskip#*
\yaenvtohskip#*
\yaenvtovskip#*
\yaenvtoaddr#*
\yaenvretaddr#*
\yabusiness
\yananoxenvelope
\yadlenvelope
\yacvienvelope
\yacvicvenvelope
\yacvenvelope
\yacivenvelope
\yaciiienvelope
\yanaaiienvelope
\yanaavienvelope
\yanaaviienvelope
\yanaaviiienvelope
\yanaaixenvelope
\yanaaxenvelope
\yananovienvelope
\yananoviienvelope
\yananoixenvelope
\yananoxienvelope
\yananoxiienvelope
\yananoxivenvelope

\yalabelsheet{pagewidth}{pageheight}{labelwidth}{labelheight}{hsep}{vsep}{num across}{num down}
\yalableftmarg#*
\yalabrightmarg#*
\yalabtopmarg#*
\yalabbotmarg#*
\yalabeltext#*
\yaplacelabel{text}{num across}{num down}
\yalabelmarg#*
\yashowboxeson
\yashowboxesoff
\yaavery{number}

\nloop{arg}#*
\yalastpagestyle#*