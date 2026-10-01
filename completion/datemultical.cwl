# datemultical package
# Matthew Bertucci 2026/09/17 for v0.1.0

#include:iftex

#keyvals:\usepackage/datemultical#c
native
persian
#endkeyvals

\dmc[calendar]{name}{style}
\dmcformat[calendar]{name}{pattern}
\dmcformat{name}{pattern}
\dmcget[calendar]{name}{year}
\dmcget{name}{year}
\dmcnew[calendar]{name}{keyvals}
\dmcnew{name}{keyvals}
\dmcset[calendar]{name}{year}{month}{day}
\dmcset{name}{year}{month}{day}
\dmcstyle[calendar]{style}{pattern}
\dmcstyle{style}{pattern}
\dmc{name}{style}
\FaMiladi{integer}
\Ghamari{integer}
\Miladi{integer}
\Persianweekday{integer}
\Shamsi{integer}
\ShortGhamari{integer}
\ShortMiladi{integer}
\ShortShamsi{integer}

# not documented
\dmcdate{arg1}{arg2}#S
\dmcday{arg1}{arg2}#S
\dmcjdn{arg1}{arg2}{arg3}{arg4}#S
\dmcLuaStoreDynamic{arg1}{arg2}{arg3}{arg4}#S
\dmcLuaStoreJDN{arg1}{arg2}#S
\dmcLuaStoreRD{arg1}{arg2}#S
\dmcLuaStoreWeekday{arg1}{arg2}#S
\dmcLuaStore{arg1}{arg2}{arg3}{arg4}{arg5}#S
\dmcmonth{arg1}{arg2}#S
\dmcyear{arg1}{arg2}#S