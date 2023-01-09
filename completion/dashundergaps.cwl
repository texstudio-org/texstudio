# dashundergaps package
# Matthew Bertucci 9/11/2021 for v2.0h

#include:l3keys2e
#include:ulem
#include:underscore

\gap{text}
\gap[style%keyvals]{text}
\gap*{text}
\gap*[style%keyvals]{text}

#keyvals:\gap,\gap*
u
d
w
b
-
.
#endkeyvals

\TeacherModeOn#*
\TeacherModeOff#*

\dashundergapssetup{options%keyvals}

#keyvals:\dashundergapssetup
teacher-mode#true,false
gap-mode#true,false
teachermode#true,false
gap-format=#underline,double-underline,dash,dot,wave,blank
gap-format-adjust#true,false
teacher-gap-format=#underline,double-underline,dash,dot,wave,blank
gap-font=
dash
dot
gap-numbers#true,false
gap-number-format=
numbers#true,false
display-total-gaps#true,false
displaynbgaps#true,false
gap-widen#true,false
gap-extend-minimum=##L
gap-extend-percent=
widen#true,false
#endkeyvals

\thegapnumber#*
\thetotalgapnumber#*

\dashundergapsdate#S
\dashundergapsversion#S
