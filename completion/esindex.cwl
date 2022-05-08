# esindex package
# Matthew Bertucci 2022/05/05 for v1.7

#keyvals:\usepackage/esindex#c
ignorespaces
replaceindex
nospanish
babel
encap=
level=
actual=
quote=
#endkeyvals

\esindex{entry}
\esindexactual{entry}{text}
\esindexsort{entry}{replacement}
\everyesindex{code}
\ignorewords{word}

\esindexexpandkey#*
\esindexexpandkeys#*
\esindexexpandsubkey#*
\esindexexpandsubsubkey#*
\esindexkey#*
\esindexlanguage#*
\esindexlastchar#*
\esindexreplace{text%plain}{replacement}#*
\esindexreplacesub{text%plain}{replacement}{integer}#*
\esindexreplacesubsub{text%plain}{replacement}{integer1}{integer2}#*
\esindexsubkey#*
\esindexsubsubkey#*