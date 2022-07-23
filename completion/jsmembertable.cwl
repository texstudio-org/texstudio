# jsmembertable package
# Matthew Bertucci 2022/07/21 for v1.12

#include:ifthen
#include:calc
#include:array
#include:longtable
#include:hhline
#include:xkeyval
#include:datatool

#keyvals:\usepackage/jsmembertable#c
datafile=%<.csv file%>
datakeys={%<key1,key2,...%>}
#endkeyvals

\makemembertable{number of blank rows}
\makeprestable{number of blank rows}
\makeprestable[number of sessions]{number of blank rows}
\makeprestable*{number of blank rows}
\makeprestable*[number of sessions]{number of blank rows}

\jsmnameheader#*
\jsmidheader#*
\jsemailheader#*
\jsmsession#*
\jsmsessionheader#*
\jssigheader#*

# not documented
\themembers#S
\themember#S
\thetabrow#S
\thesession#S
\thesnum#S
\iffixedseshead#S
\fixedsesheadtrue#S
\fixedsesheadfalse#S
\sescolhead#S
\getmembernr#S
\addtabtoks{arg}#S
\resettabtoks#S
\printtabtoks#S
\sescolwidth#S
\sescolwidthtwo#S
\inittemplates#S
\bodyrowone#S
\bodyrowtwo#S
\visumcell#S
\headerpone#S
\headerptwo#S
\ltstartone#S
\ltstarttwo#S
\filedate#S
\fileversion#S
\filename#S