# person package
# Matthew Bertucci 10/31/2021 for v2.32

#include:ifthen
#include:datatool

\newperson{full name}{familiar name}{gender}
\newperson[label]{full name}{familiar name}{gender}
\malelabels#*
\femalelabels#*
\addmalelabel{identifier}
\addfemalelabel{identifier}
\thepeople
\removeperson
\removeperson[label]
\removeallpeople
\removepeople{list}
\personfullname
\personfullname[label]
\personname
\personname[label]
\personpronoun
\personpronoun[label]
\personobjpronoun
\personobjpronoun[label]
\personpossadj
\personpossadj[label]
\personposspronoun
\personposspronoun[label]
\personchild
\personchild[label]
\personparent
\personparent[label]
\personsibling
\personsibling[label]
\Personpronoun
\Personpronoun[label]
\Personobjpronoun
\Personobjpronoun[label]
\Personpossadj
\Personpossadj[label]
\Personposspronoun
\Personposspronoun[label]
\Personchild
\Personchild[label]
\Personparent
\Personparent[label]
\Personsibling
\Personsibling[label]
\peoplefullname
\peoplename
\peoplepronoun
\Peoplepronoun
\peopleobjpronoun
\Peopleobjpronoun
\peoplepossadj
\Peoplepossadj
\peopleposspronoun
\Peopleposspronoun
\peoplechild
\Peoplechild
\peopleparent
\Peopleparent
\peoplesibling
\Peoplesibling

\ifpersonexists{label}{true case}{false case}#*
\ifmale{label}{true case}{false case}#*
\iffemale{label}{true case}{false case}#*
\ifallmale{true case}{false case}#*
\ifallmale[label list]{true case}{false case}#*
\ifallfemale{true case}{false case}#*
\ifallfemale[label list]{true case}{false case}#*
\ifmalelabel{identifier}{true case}{false case}#*
\iffemalelabel{identifier}{true case}{false case}#*
\foreachperson(name cmd,full name cmd,gender cmd,label cmd)\do{body}#*
\foreachperson(name cmd,full name cmd,gender cmd,label cmd)\in{list}\do{body}#*
\do#S
\in#S
\malename#*
\femalename#*
\getpersongender{cmd}{label}#*d
\getpersonname{cmd}{label}#*d
\getpersonfullname{cmd}{label}#*d