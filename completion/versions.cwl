# versions package
# Matthew Bertucci 1/12/2021 for v0.55

#keyvals:\usepackage/versions#c
nogroup
tracing
#endkeyvals

\markversion{version%envname}#N
\includeversion{version%envname}#N
\excludeversion{version%envname}#N
\begin{comment}
\end{comment}
\processifversion{version}{code}

#ifOption:nogroup
\includeversionnogroup{version%envname}#N
#endif

\versionmessage{version}{type%keyvals}
#keyvals:\versionmessage#c
excluded
included
included with marks
#endkeyvals

\beginmarkversion#S
\endmarkversion#S