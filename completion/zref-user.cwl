# zref-user package
# Matthew Bertucci 11/10/2021 for v2.32

#include:zref-base

\zlabel{label}#l

\zkvlabel{keyvals}{label}#l

#keyvals:\zkvlabel
prop=
list=
delprop=
immediate#true,false
values=
#endkeyvals

\zref{label}#r
\zref[propname%keyvals]{label}#r

#keyvals:\zref#c
default
page
#endkeyvals

\zpageref{label}#r
\zrefused{label}#r