# person package
# Matthew Bertucci 2025/03/06 for v3.0

#include:datatool

#keyvals:\usepackage/person#c
base-only
datatool
shortcuts
# options passed to datatool
delimiter=%<char%>
separator=%<char%>
default-name=%<db name%>
new-value-expand#true,false
new-value-trim#true,false
store-datum#true,false
# options passed to datatool-base
math=#l3fp,lua,fp,pgfmath
lang-warn#true,false
nolocale
locales={%<locales list%>}
lang={%<locales list%>}
verbose#true,false
initial-purify=#early,late
auto-reformat-types={%<list of types%>}
lists={%<keyvals%>}
compare={%<keyvals%>}
numeric={%<keyvals%>}
datetime={%<keyvals%>}
#endkeyvals

#ifOption:math=fp
#include:fp
#endif

#ifOption:math=pgfmath
#include:pgfrcs
#include:pgfkeys
#include:pgfmath
#endif

#ifOption:shortcuts
\they
\They
\them
\Them
\their
\Their
\theirs
\Theirs
\you
\You
\thee
\Thee
\your
\Your
\yours
\Yours
\children
\Children
\parents
\Parents
\siblings
\Siblings
#endif

#keyvals:\DTLsetup
person={%<keyvals%>}
#endkeyvals

\newperson{full name}{name}{gender label}
\newperson[person label]{full name}{name}{gender label}
\newperson*{keyvals}
\newperson*[person label]{keyvals}

#keyvals:\newperson*
fullname=%<full name%>
expand-fullname=%<full name%>
expand-once-fullname=%<full name%>
name=%<name%>
expand-name=%<name%>
expand-once-name=%<name%>
forenames=%<forenames%>
expand-fornames=%<forenames%>
expand-once-fornames=%<forenames%>
surname=%<surname%>
expand-surname=%<surname%>
expand-once-surname=%<surname%>
title=%<title%>
expand-title=%<title%>
expand-once-title=%<title%>
gender=%<gender label%>
#endkeyvals

\PersonTotalCount
\removeperson
\removeperson[person label]
\removepeople{list}
\removeallpeople

\PersonSetMaleLabels{label list}
\PersonSetFemaleLabels{label list}
\PersonSetNonBinaryLabels{label list}
\PersonIfMaleLabel{gender label}{true code}{false code}
\PersonIfFemaleLabel{gender label}{true code}{false code}
\PersonIfNonBinaryLabel{gender label}{true code}{false code}
\PersonMaleCount
\PersonFemaleCount
\PersonNonBinaryCount
\PersonUnknownGenderCount

\personpronoun
\personpronoun[person label]
\Personpronoun
\Personpronoun[person label]
\peoplepronoun
\Peoplepronoun
\personpronounii
\personpronounii[person label]
\Personpronounii
\Personpronounii[person label]
\peoplepronounii
\Peoplepronounii
\personobjpronoun
\personobjpronoun[person label]
\Personobjpronoun
\Personobjpronoun[person label]
\peopleobjpronoun
\Peopleobjpronoun
\personobjpronounii
\personobjpronounii[person label]
\Personobjpronounii
\Personobjpronounii[person label]
\peopleobjpronounii
\Peopleobjpronounii
\personpossadj
\personpossadj[person label]
\Personpossadj
\Personpossadj[person label]
\peoplepossadj
\Peoplepossadj
\personpossadjii
\personpossadjii[person label]
\Personpossadjii
\Personpossadjii[person label]
\peoplepossadjii
\Peoplepossadjii
\personposspronoun
\personposspronoun[person label]
\Personposspronoun
\Personposspronoun[person label]
\peopleposspronoun
\Peopleposspronoun
\personposspronounii
\personposspronounii[person label]
\Personposspronounii
\Personposspronounii[person label]
\peopleposspronounii
\Peopleposspronounii
\personchild
\personchild[person label]
\Personchild
\Personchild[person label]
\peoplechild
\Peoplechild
\personparent
\personparent[person label]
\Personparent
\Personparent[person label]
\peopleparent
\Peopleparent
\personsibling
\personsibling[person label]
\Personsibling
\Personsibling[person label]
\peoplesibling
\Peoplesibling
\personfullname
\personfullname[person label]
\personname
\personname[person label]
\personforenames
\personforenames[person label]
\personsurname
\personsurname[person label]
\persontitlesurname
\persontitlesurname[person label]
\persontitlesurnamesep#*
\persongender{person label}#*
\Persongender{person label}#*
\getpersongender{cmd}{person label}#*d
\getpersonname{cmd}{person label}#*d
\getpersonforenames{cmd}{person label}#*d
\getpersonsurname{cmd}{person label}#*d
\getpersonfullname{cmd}{person label}#*d
\getpersontitle{cmd}{person label}#*d
\twopeoplesep#*
\personlastsep#*
\personsep#*
\peoplefullname
\peoplename
\peopleforenames
\peoplesurname
\peopletitlesurname

\ifpersonexists{person label}{true code}{false code}#*
\PersonIfMale{person label}{true code}{false code}#*
\PersonIfAllMale{true code}{false code}#*
\PersonIfAllMale[person label list]{true code}{false code}#*
\PersonIfFemale{person label}{true code}{false code}#*
\PersonIfAllFemale{true code}{false code}#*
\PersonIfAllFemale[person label list]{true code}{false code}#*
\PersonIfNonBinary{person label}{true code}{false code}#*
\PersonIfAllNonBinary{true code}{false code}#*
\PersonIfAllNonBinary[person label list]{true code}{false code}#*
\PersonIfUnknownGender{person label}{true code}{false code}#*
\PersonIfAllUnknownGender{true code}{false code}#*
\PersonIfAllUnknownGender[person label list]{true code}{false code}#*
\foreachpersonbreak#*
\forallpeople{label cmd}{body}#*
\forallpeople[people label list]{label cmd}{body}#*
\foreachperson(name cmd,full name cmd,gender cmd,label cmd)\do{body}#*
\foreachperson(name cmd,full name cmd,gender cmd,label cmd)\in{list}\do{body}#*
\do#S
\in#S
\PersonSetLocalisation{gender label}{type}{value}#*

# not documented
\thepeople#S