# footmisc package
# Matthew Bertucci 2/12/2022 for v6.0b

#keyvals:\usepackage/footmisc#c
perpage
para
side
ragged
symbol
symbol*
abovefloats
belowfloats
bottom
bottomfloats
marginal
flushmargin
hang
norule
splitrule
stable
multiple
#endkeyvals

\DefineFNsymbols{set name%specialDef}[style]{symbol list}#s#%fnsymbolset
\DefineFNsymbols*{set name%specialDef}[style]{symbol list}#s#%fnsymbolset
\setfnsymbol{set name%keyvals}
#keyvals:\setfnsymbol#c
bringhurst
chicago
wiley
%fnsymbolset
#endkeyvals
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

\footnotemargin#*
\hangfootparskip#*
\hangfootparindent#*

#ifOption:splitrule
\mpfootnoterule
\pagefootnoterule
\splitfootnoterule
#endif

#ifOption:multiple
\multiplefootnotemarker#*
\multfootsep#*
#endif
