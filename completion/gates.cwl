# gates package
# Matthew Bertucci 11/6/2021 for v0.2

#include:texapi

\gates add %<<gate list>%>%<<l-gate>%>
\gates add %<<gate list>%>[%<<position>%>]%<<l-gate>%>
\gates ajar %<<gate spec>%>%<<l-gate>%>
\gates ajar! %<<gate spec>%>
\gates close %<<gate spec>%>%<<l-gate>%>
\gates close! %<<gate spec>%>
\gates conditional %<<gate spec>%>%<<l-gate>%>%<<conditional>%>
\gates conditional! %<<gate spec>%>%<<conditional>%>
\gates copy %<<gate1>%>%<<gate2>%>
\gates def %<<name>%>{%<<definition>%>}
\gates def %<<name>%>%<<optional conditions>%>{%<<definition>%>}
\gates def %<<name>%>[%<<number of arguments>%>]%<<optional conditions>%>{%<<definition>%>}
\gates edef %<<name>%>{%<<definition>%>}
\gates edef %<<name>%>%<<optional conditions>%>{%<<definition>%>}
\gates edef %<<name>%>[%<<number of arguments>%>]%<<optional conditions>%>{%<<definition>%>}
\gates execute %<<name>%>%<<arguments>%>
\gates family
\gates list %<<name>%>
\gates list %<<name>%>[%<<number of arguments>%>]
\gates list %<<name>%>[%<<number of arguments>%>]%<<optional conditions>%>
\gates list %<<name>%>[%<<number of arguments>%>]%<<optional conditions>%>%<<optional subgates>%>
\gates loop %<<gate spec>%>%<<l-gate>%>%<<conditional>%>
\gates loop! %<<gate spec>%>%<<conditional>%>
\gates loopuntil %<<gate spec>%>%<<l-gate>%>%<<conditional>%>
\gates loopuntil! %<<gate spec>%>%<<conditional>%>
\gates new %<<control sequence>%>%<<family>%>
\gates noloop %<<gate spec>%>%<<l-gate>%>%<<conditional>%>
\gates noloop! %<<gate spec>%>
\gates noloopuntil %<<gate spec>%>%<<l-gate>%>%<<conditional>%>
\gates noloopuntil! %<<gate spec>%>
\gates open %<<gate spec>%>%<<l-gate>%>
\gates open! %<<gate spec>%>
\gates remove %<<gate list>%>%<<l-gate>%>
\gates return %<<arguments>%>
\gates return0
\gates return1
\gates return2
\gates return3
\gates return4
\gates return5
\gates return6
\gates return7
\gates return8
\gates return9
\gates return! %<<arguments>%>
\gates show %<<gate>%>
\gates skip %<<gate spec>%>%<<l-gate>%>
\gates skip! %<<gate spec>%>
\gates status %<<gate>%>%<<l-gate>%>
\gates status! %<<gate>%>
\gates subchar %<<character>%>
\gates subgates %<<l-gate>%>%<<definition>%>
\gates type %<<name>%>
\gates trace %<<number>%>