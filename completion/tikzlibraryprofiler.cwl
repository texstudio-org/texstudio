# profiler tikzlibrary
# 2022/12/05

# only documented cmds listed here; all others in pgfcore.cwl
\pgfprofilenew{name}
\pgfprofilenewforcommand{macro}{args}
\pgfprofilenewforcommand[profiler entry name]{macro}{args}
\pgfprofilecs#*
\pgfprofilenewforcommandpattern{macro}{arg pattern}{invocation pattern}
\pgfprofilenewforcommandpattern[profiler entry name]{macro}{arg pattern}{invocation pattern}
\pgfprofileshowinvocationsfor{profiler entry name}
\pgfprofileshowinvocationsexpandedfor{profiler entry name}
\pgfprofilenewforenvironment{envname}
\pgfprofilenewforenvironment[profiler entry name]{envname}
\pgfprofileenv#*
\pgfprofilestart{profiler entry name}
\pgfprofileend{profiler entry name}
\pgfprofilepostprocess
\pgfprofilesetrel{profiler entry name}
\pgfprofileifisrunning{profiler entry name}{true code}{false code}