# footmisc package
# Matthew Bertucci 9/5/2021 for v5.5b

\DefineFNsymbols{set name}[style]{symbol list}#*
\DefineFNsymbols*{set name}[style]{symbol list}#*
\setfnsymbol{set name}#*
\mpfootnotemark
\mpfootnotemark[number]
\footref{label}#r
\footnotelayout#*
\footglue#*
\footnotebaselineskip#*
\fudgefactor#*
\makefootnoteparagraph#*
\makehboxofhboxes#*
\removehboxes#*
\footnotehint#*

#ifOption:marginal
\footnotemargin
#endif

#ifOption:hang
\hangfootparskip#*
\hangfootparindent#*
#endif

#ifOption:splitrule
\mpfootnoterule
\pagefootnoterule
\splitfootnoterule
#endif

#ifOption:multiple
\multiplefootnotemarker#*
\multfootsep#*
#endif
