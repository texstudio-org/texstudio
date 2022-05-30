# backref package
# Matthew Bertucci 11/5/2021 for v1.41

#include:kvoptions
#include:kvsetkeys
#include:ltxcmds
#include:rerunfilecheck

\backrefsetup{options%keyvals}

#keyvals:\backrefsetup#c,\usepackage/backref#c
ref
pageref
hyperref
hyperpageref
english
german
french
spanish
brazil
verbose
enable
disable
#endkeyvals

\ifbackrefparscan#*
\backrefparscanfalse
\backrefparscantrue
\backrefprint

\backcite{label}{{page num}{current label}{current anchor}}

\backref{backref list}#*
\backrefalt{num w/o dupes}{backref list w/o dupes}{num w/ dupes}{backref list w/ dupes}#*
\backrefpagesname#*
\backrefsectionsname#*
\backrefsep#*
\backreftwosep#*
\backreflastsep#*
\backrefentrycount{backref entry}{citation count}#*
\backrefenglish#*
\backrefgerman#*
\backreffrench#*
\backrefspanish#*
\backrefbrazil#*
\backrefafrikaans#*
