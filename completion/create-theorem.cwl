# create-theorem package
# Matthew Bertucci 3/7/2022 for release 2022-03-03

#include:l3keys2e
#include:aliascnt
#include:crefthe

#keyvals:\usepackage/create-theorem#c
name as context
name as is
name in link
no preset names
#endkeyvals

\NameTheorem{envname}{keyvals}

#keyvals:\NameTheorem
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
#endkeyvals

\CreateTheorem{envname}{keyvals}#N

#keyvals:\CreateTheorem
name={%<\NameTheorem keyvals%>}
name style=
style=%<theorem style%>
parent counter=%<counter%>
shared counter=%<counter%>
numberless
create starred version
copy existed=%<envname%>
#endkeyvals

\SetTheorem{envname}{keyvals}

#keyvals:\SetTheorem
name style=
parent counter=%<counter%>
shared counter=%<counter%>
#endkeyvals

\CreateTheoremAddLanguage{language}#*