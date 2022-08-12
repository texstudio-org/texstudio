# create-theorem package
# Matthew Bertucci 2022/08/09 for release 2022/08/08

#include:crefthe
#include:amsfonts

#keyvals:\usepackage/create-theorem#c
name as context
name as is
name in link
no preset names
#endkeyvals

\NameTheorem{envname}{keyvals}

#keyvals:\NameTheorem#c
heading=%<string%>
heading={%<lang1=string1,lang2=string2,...%>}
heading style=%<font commands%>
crefname={%<singular name%>}{%<plural name%>}
crefname={%<lang1={name1}{pluralname1},...%>}
crefname style=%<font commands%>
Crefname={%<singular name%>}{%<plural name%>}
Crefname={%<lang1={name1}{pluralname1},...%>}
Crefname style=%<font commands%>
numbering style=%<font commands%>
use name={%<envname1;envname2;...%>}
#endkeyvals

\CreateTheorem{envname}{keyvals}#N

#keyvals:\CreateTheorem#c
name={%<\NameTheorem keyvals%>}
use name={%<envname1;envname2;...%>}
style=%<theorem style%>
qed=%<symbol%>
parent counter=%<counter%>
shared counter=%<counter%>
numberless
create starred version
copy existed=%<envname%>
#endkeyvals

\SetTheorem{envname}{keyvals}

#keyvals:\SetTheorem#c
name={%<\NameTheorem keyvals%>}
qed=%<symbol%>
parent counter=%<counter%>
shared counter=%<counter%>
#endkeyvals

\SetTheoremBinding{envname}{envname to bind with}

\NameTheorems{language}{keyvals}

#keyvals:\NameTheorems#c
heading={%<envname%>=%<string%>}
crefname={%<envname%>={%<singular%>}{%<plural%>}}
Crefname={%<envname%>={%<singular%>}{%<plural%>}}
#endkeyvals

\CreateTheoremAddLanguage{language}#*
