# jsonresume package
# Matthew Bertucci 2026/01/22 for v1.0.0

#include:ifluatex
#include:hyperref
#include:enumitem

#keyvals:\usepackage/jsonresume#c
strict
#endkeyvals

\resumefromfile{file}
\resumefromurl{URL}#U
\resumevalidate
\resumevalidationsummary
\resumewarningcount
\jrget{path}
\jrgetraw{path}#*
\jrifexists{path}{true code}{false code}#*
\jrsectionheader{text}#*
\jrentryheader{arg1}{arg2}{arg3}{arg4}#*
\resumebasics
\resumework
\resumework[title%text]
\resumeeducation
\resumeeducation[title%text]
\resumeskills
\resumeskills[title%text]
\resumevolunteer
\resumevolunteer[title%text]
\resumeawards
\resumeawards[title%text]
\resumecertificates
\resumecertificates[title%text]
\resumepublications
\resumepublications[title%text]
\resumelanguages
\resumelanguages[title%text]
\resumeinterests
\resumeinterests[title%text]
\resumereferences
\resumereferences[title%text]
\resumeprojects
\resumeprojects[title%text]
\renderresumecore
\renderresume