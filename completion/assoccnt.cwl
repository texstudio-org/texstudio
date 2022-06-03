# assoccnt package
# Matthew Bertucci 2022/05/31 for v0.8

#include:xcolor
#include:etoolbox
#include:xkeyval
#include:xstring

#keyvals:\usepackage/assoccnt#c
globalsuspend#true,false
#endkeyvals

\setcounter{counter}{value}
\setcounter[options%keyvals]{counter}{value}
#keyvals:\setcounter
AssociatedToo#true,false
AssociatedCounters={%<list of counters%>}
#endkeyvals

\DeclareAssociatedCounters{driver counter}{associated counters list}
\AddAssociatedCounters{driver counter}{associated counters list}
\RemoveAssociatedCounter{driver counter}{associated counter}
\RemoveAssociatedCounters{driver counter}{associated counters list}
\ClearAssociatedCounters{driver counter}
\AddDriverCounter{driver counter name}
\ClearDriverCounter
\IsAssociatedToCounter{driver counter}{associated counter}{true}{false}
\GetDriverCounter{counter}
\IsAssociatedCounter{counter}{true}{false}
\IsDriverCounter{driver counter}{true}{false}
\IsSuspendedCounter{counter}{true}{false}
\AssociatedDriverCounterInfo{counter}
\LastAddedToCounter
\LastSteppedCounter
\LastRefSteppedCounter
\LastSetCounter

\PrettyPrintCounterName{counter}
\PrettyPrintCounterName[options%keyvals]{counter}
#keyvals:\PrettyPrintCounterName
countertype=#general,driver,associated
#endkeyvals

\GeneralCounterInfoColor
\DriverCounterInfoColor
\AssociatedCounterInfoColor
\SuspendCounters{counters list}
\ResumeSuspendedCounters

# not documented
\AssociationStatistics#*
\ClearAssociatedCountersList{associated counters list}#*
\ClearDriverCountersList#*
\IsInResetList{arg1}{arg2}{true}{false}#*
\assoccntpackageversion#S