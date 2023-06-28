# conditext package
# Matthew Bertucci 2022/07/21 for v1.5

#include:simplekv
#include:xifthen

#keyvals:\usepackage/conditext#c
defaultdisplayall
#endkeyvals

\begin{conditext}{propriété de condition}
\begin{conditext}[domaine de condition]{propriété de condition}
\begin{conditext}{propriété de condition}*
\begin{conditext}[domaine de condition]{propriété de condition}*
\end{conditext}

\setcondispace{propriété de condition}
\setcondispace[domaine de condition]{propriété de condition}
\setcondispace*{propriété de condition}
\setcondispace*[domaine de condition]{propriété de condition}
\newcondifield{nouveau domaine de condition}
\newcondifield*{nouveau domaine de condition}
\newcondiprop{domaine de condition}{nouvelle propriété de condition}
\setimplicitcondifield{domaine de condition}
\miniconditext{%<forme-substituable%>}
\miniconditext{%<forme-substituable1%>}[%<forme-substituable2%>]%<...[forme-substituable9]%>
\setminicondiprop{i-ix}{propriété de condition redéfinie}
\setminicondipropi{propriété de condition redéfinie}
\setminicondipropii{propriété de condition redéfinie}
\setminicondipropiii{propriété de condition redéfinie}
\setminicondipropiv{propriété de condition redéfinie}
\setminicondipropv{propriété de condition redéfinie}
\setminicondipropvi{propriété de condition redéfinie}
\setminicondipropvii{propriété de condition redéfinie}
\setminicondipropviii{propriété de condition redéfinie}
\setminicondipropix{propriété de condition redéfinie}
\resettingminicondiprops
\setminicondispace{propriété de condition}

# not documented
\errorifcfalreadycreated{arg1}{arg2}#S
\errorifcfempty{arg1}#S
\errorifcfnoncreated{arg1}{arg2}#S
\errorifcpalreadycreated{arg1}{arg2}#S
\errorifcpempty{arg1}#S
\errorifcpnoncreated{arg1}{arg2}#S
\errorifcpnonok{arg1}{arg2}#S
\errorifcsalreadydefined{arg1}{arg2}{arg3}#S
\errorifmncpalreadyredefined{arg1}{arg2}#S
\errorifmncpempty{arg1}#S
\errorifmncpnone{arg1}{arg2}#S
\errorifmncpnonok{arg1}#S
\errorifmncpnoresetting{arg1}#S
\errorifmncsalreadydefined{arg1}{arg2}#S
\errorifmncsempty{arg1}#S
\errtxtifcfalreadycreated#S
\errtxtifcfempty#S
\errtxtifcfnoncreated#S
\errtxtifcpalreadycreated#S
\errtxtifcpempty#S
\errtxtifcpnoncreated#S
\errtxtifcpnonok#S
\errtxtifcsalreadydefined#S
\errtxtifmncpalreadyredefined#S
\errtxtifmncpempty#S
\errtxtifmncpnone#S
\errtxtifmncpnonok#S
\errtxtifmncpnoresetting#S
\errtxtifmncsalreadydefined#S
\errtxtifmncsempty#S
\hlptxtifcfalreadycreated#S
\hlptxtifcfempty#S
\hlptxtifcfnoncreated#S
\hlptxtifcpalreadycreated#S
\hlptxtifcpempty#S
\hlptxtifcpnoncreated#S
\hlptxtifcpnonok#S
\hlptxtifcsalreadydefined#S
\hlptxtifmncpalreadyredefined#S
\hlptxtifmncpempty#S
\hlptxtifmncpnone#S
\hlptxtifmncpnonok#S
\hlptxtifmncpnoresetting#S
\hlptxtifmncsalreadydefined#S
\hlptxtifmncsempty#S
\icf#S
\ifcfalreadycreatedthenelse{arg1}{arg2}{arg3}#S
\ifcfemptythenelse{arg1}{arg2}{arg3}#S
\ifcfokthenelse{arg1}{arg2}{arg3}#S
\ifcpalreadycreatedthenelse{arg1}{arg2}{arg3}{arg4}#S
\ifcpemptythenelse{arg1}{arg2}{arg3}#S
\ifcpokthenelse{arg1}{arg2}{arg3}{arg4}#S
\ifcsalreadydefinedthenelse{arg1}{arg2}{arg3}{arg4}#S
\ifmatchingcsthenelse{arg1}{arg2}{arg3}{arg4}#S
\ifmatchingmncsthenelse{arg1}{arg2}{arg3}#S
\ifmncpalreadyredefinedthenelse{arg1}{arg2}{arg3}{arg4}#S
\ifmncpemptythenelse{arg1}{arg2}{arg3}#S
\ifmncpnonethenelse{arg1}{arg2}{arg3}#S
\ifmncpnoresettingthenelse{arg1}{arg2}#S
\ifmncpokthenelse{arg1}{arg2}{arg3}#S
\ifmncsalreadydefinedthenelse{arg1}{arg2}{arg3}#S
\ifmncsemptythenelse{arg1}{arg2}{arg3}#S
\minidisplayiii{arg1}{arg2}#S
\minidisplayii{arg1}{arg2}#S
\minidisplayiv{arg1}{arg2}#S
\minidisplayix{arg1}{arg2}#S
\minidisplayi{arg1}{arg2}#S
\minidisplayviii{arg1}{arg2}#S
\minidisplayvii{arg1}{arg2}#S
\minidisplayvi{arg1}{arg2}#S
\minidisplayv{arg1}{arg2}#S
\minidisplay{arg1}{arg2}{arg3}#S
\textdisplay{arg1}{arg2}{arg3}#S