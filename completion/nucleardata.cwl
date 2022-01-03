# nucleardata package
# Matthew Bertucci 12/30/2021 for v1.1

#include:pythontex
#include:siunitx

\nucsymbol{name}
\nucname{name}
\nucName{name}
\nucz{name}

\nuchalflife{name}{mass number}
\nuchalflife[unit%keyvals]{name}{mass number}
\nuchalfvalue{name}{mass number}
\nuchalfvalue[unit%keyvals]{name}{mass number}
\nuchalfunit{name}{mass number}
\nuchalfunit[unit%keyvals]{name}{mass number}

#keyvals:\nuchalflife,\nuchalfvalue,\nuchalfunit
ev
mev
kev
as
fs
ps
ns
us
ms
s
m
min
h
hr
d
day
y
yr
My
Gy
#endkeyvals

\nucspin{name}{mass number}

\nucamassu{name}{mass number}
\nucamassu[rnd]{name}{mass number}
\nucamassmev{name}{mass number}
\nucamassmev[rnd]{name}{mass number}
\nucamasskev{name}{mass number}
\nucamasskev[rnd]{name}{mass number}
\nuclearmassu{name}{mass number}
\nuclearmassu[rnd]{name}{mass number}
\nuclearmassmev{name}{mass number}
\nuclearmassmev[rnd]{name}{mass number}
\nuclearmasskev{name}{mass number}
\nuclearmasskev[rnd]{name}{mass number}
\nucexcess{name}{mass number}
\nucexcess[rnd]{name}{mass number}
\nucbea{name}{mass number}
\nucbea[rnd]{name}{mass number}

\nucisotopes{name}

\nucQalpha{name}{mass number}
\nucQalpha[rnd]{name}{mass number}
\nucQbeta{name}{mass number}
\nucQbeta[rnd]{name}{mass number}
\nucQposi{name}{mass number}
\nucQposi[rnd]{name}{mass number}
\nucQec{name}{mass number}
\nucQec[rnd]{name}{mass number}

\nucisalpha{name}{mass number}
\nucisbeta{name}{mass number}
\nucisposi{name}{mass number}
\nucisec{name}{mass number}

\nucreactionqu{%<name1%>}{%<massnumber1%>}%<{name2}{massnumber2}...%>
\nucreactionqu[%<rnd%>]{%<name1%>}{%<massnumber1%>}%<{name2}{massnumber2}...%>
\nucreactionqmev{%<name1%>}{%<massnumber1%>}%<{name2}{massnumber2}...%>
\nucreactionqmev[%<rnd%>]{%<name1%>}{%<massnumber1%>}%<{name2}{massnumber2}...%>
\nucreactionqkev{%<name1%>}{%<massnumber1%>}%<{name2}{massnumber2}...%>
\nucreactionqkev[%<rnd%>]{%<name1%>}{%<massnumber1%>}%<{name2}{massnumber2}...%>

\nucAran{name}

\nucrandom{list size}
\nucrandom[0 or 1]{list size}