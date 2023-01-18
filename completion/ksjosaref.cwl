# ksjosaref package
# ponte-vecchio 2023-01-17 for v0.3

#keyvals:\usepackage/ksjosaref#c
refcmd
#endkeyvals
\josaref[%<type%>][%<delim%>]{%<ref%>%keyvals}#r

#ifOption:refcmd
\ref[%<type%>][%<delim%>]{%<ref%>%keyvals}#r
\pageref{%<ref%>%keyvals}#r
\eqref{%<ref%>%keyvals}#r
\josarefcmds#d
\nojosarefcmds#d
#endif

#keyvals:\josaref#
paren
bracket
left=#[, (, \{, <
right=#], ), \}, >
#endkeyvals
