# makecmds package
# Matthew Bertucci 12/24/2021 for v1.0a

#keyvals:\usepackage/makecmds#c
warn
#endkeyvals

\makecommand{cmd}[args][default]{def}#d
\makecommand{cmd}[args]{def}#d
\makecommand{cmd}{def}#d
\makecommand*{cmd}[args][default]{def}#d
\makecommand*{cmd}[args]{def}#d
\makecommand*{cmd}{def}#d

\provideenvironment{envname}[args][default]{begdef}{enddef}#N
\provideenvironment{envname}[args]{begdef}{enddef}#N
\provideenvironment{envname}{begdef}{enddef}#N
\provideenvironment*{envname}[args][default]{begdef}{enddef}#N
\provideenvironment*{envname}[args]{begdef}{enddef}#N
\provideenvironment*{envname}{begdef}{enddef}#N

\makeenvironment{envname}[args][default]{begdef}{enddef}#N
\makeenvironment{envname}[args]{begdef}{enddef}#N
\makeenvironment{envname}{begdef}{enddef}#N
\makeenvironment*{envname}[args][default]{begdef}{enddef}#N
\makeenvironment*{envname}[args]{begdef}{enddef}#N
\makeenvironment*{envname}{begdef}{enddef}#N

\providelength{cmd}#d
\makelength{cmd}#d

\providecounter{counter name}
\makecounter{counter name}