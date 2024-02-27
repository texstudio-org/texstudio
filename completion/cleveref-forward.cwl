# cleveref-forward package
# Matthew Bertucci 2024/02/25 for v2024/02/24

#include:cleveref
#include:iflang
#include:regexpatch

#keyvals:\usepackage/cleveref-forward#c
default=#used on,used by,used by and on
crefthe#true,false
#endkeyvals

#ifOption:crefthe
#include:crefthe
#endif
#ifOption:crefthe=true
#include:crefthe
#endif

\cref[option%keyvals]{labellist}#r
\cref*[option%keyvals]{labellist}#r
\Cref[option%keyvals]{labellist}#r
\Cref*[option%keyvals]{labellist}#r
\labelcref[option%keyvals]{labellist}#r

#keyvals:\cref#c,\cref*#c,\Cref#c,\Cref*#c,\labelcref#c
used on
used by
used by and on
no use
#endkeyvals

\SetUsedOnMessageText{text}
\SetUsedByMessageText{text}
\SetUsedByAndOnMessageText{text}
\SetForwardReferenceStyle{code}
\SetForwardReferenceStyleInsideMath{code}
\SetForwardReferenceStyleOutsideMath{code}
\SetForwardReferenceRefForm{code}
\SetForwardReferencePagerefForm{code}
\restorelabel{label}#r

# not documented
\UsedOnMessageText{arg}#S
\UsedByMessageText{arg}#S
\UsedByAndOnMessageText{arg1}{arg2}#S
\UsedOnMessageContent{arg}#S
\UsedByMessageContent{arg}#S
\UsedByAndOnMessageContent{arg1}{arg2}#S
\SetUsedOnMessageContent{arg}#S
\SetUsedByMessageContent{arg}#S
\SetUsedByAndOnMessageContent{arg}#S
\UsedOnMessage{arg}#S
\UsedByMessage{arg}#S
\UsedByAndOnMessage{arg1}{arg2}#S
\UsedOnMessageMath{arg}#S
\UsedByMessageMath{arg}#S
\UsedByAndOnMessageMath{arg1}{arg2}#S
\UsedOnMessageInsideMath{arg}#S
\UsedByMessageInsideMath{arg}#S
\UsedByAndOnMessageInsideMath{arg1}{arg2}#S
\UsedOnMessageOutsideMath{arg}#S
\UsedByMessageOutsideMath{arg}#S
\UsedByAndOnMessageOutsideMath{arg1}{arg2}#S
\SetUsedOnMessageStyle{arg}#S
\SetUsedByMessageStyle{arg}#S
\SetUsedByAndOnMessageStyle{arg}#S
\SetUsedOnMessageStyleInsideMath{arg}#S
\SetUsedByMessageStyleInsideMath{arg}#S
\SetUsedByAndOnMessageStyleInsideMath{arg}#S
\SetUsedOnMessageStyleOutsideMath{arg}#S
\SetUsedByMessageStyleOutsideMath{arg}#S
\SetUsedByAndOnMessageStyleOutsideMath{arg}#S