# turkce-sayi package
# Matthew Bertucci 2026/06/13 for v1.0

#include:iftex
#include:luatexbase
#include:refcount

#keyvals:\usepackage/turkce-sayi#c
debug
#endkeyvals

\trkappend{integer}{suffix}
\trkbibappend{integer}{suffix}
\trkbibref{bibid}{suffix}#C
\trkmanual{display}{literal-suffix}
\trkpageref{label}{suffix}#r
\trkref{label}{suffix}#r
\trkremoveoverride{integer}{algo-output}
\trksetoverride{integer}{algo-output}{replacement}
\trksuffix{integer}{suffix}