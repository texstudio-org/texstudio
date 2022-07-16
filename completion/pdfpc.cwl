# pdfpc package
# Matthew Bertucci 2022/07/15 for v0.7.0

#include:kvoptions
#include:xstring
#include:iftex
#include:hyperxmp

\pdfpcsetup{options%keyvals}

#keyvals:\pdfpcsetup,\usepackage/pdfpc#c
duration=
starttime=
endtime=
enduserslide=
lastminutes=
hidenotes#true,false
overridenote#true,false
notesposition=#right,left,top,bottom,none
disablemarkdown#true,false
defaulttransition=
#endkeyvals

\pdfpcnote{text}
