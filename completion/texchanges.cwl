# texchanges package
# Matthew Bertucci 2026/08/23 for v0.3.0

#include:xcolor
#include:ulem
#include:truncate
#include:soul

#keyvals:\usepackage/texchanges#c
review
draft
final
original
mode=#review,final,original
markup=
addedmarkup=
deletedmarkup=
highlightmarkup=
commentmarkup=
authormarkup=
authormarkupposition=
authormarkuptext=
defaultcolor=
compat=#none,changes
commandnameprefix=
xcolor={%<xcolor options%>}
ulem={%<ulem options%>}
todonotes={%<todonotes options%>}
truncate={%<truncate options%>}
#endkeyvals

#ifOption:commentmarkup=todo
#include:todonotes
#endif

#ifOption:compat=changes
\comment[options%keyvals]{text}
\comment{text}
\highlight[options%keyvals]{text}
\highlight{text}
#endif

\add[options%keyvals]{text}
\add{text}
\remove[options%keyvals]{}
\remove{text}
\replace[options%keyvals]{old text%text}{new text%text}
\replace{old text%text}{new text%text}
\txadd[options%keyvals]{text}
\txadd{text}
\txcomment[options%keyvals]{text}
\txcomment{text}
\txdefineauthor[options%keyvals]{name}
\txdefineauthor{name}
\txhighlight[options%keyvals]{text}
\txhighlight{text}
\txlistofchanges
\txlistofchanges[options%keyvals]
\txremove[options%keyvals]{}
\txremove{text}
\txreplace[options%keyvals]{old text%text}{new text%text}
\txreplace{old text%text}{new text%text}

texchangesAdded#B
texchangesRemoved#B
texchangesComment#B
texchangesHighlight#B

# not documented
\texchangesmode#S
\txacceptedname#S
\txaddedname#S
\txauthorname#S
\txcommentedname#S
\txcompactsummaryname#S
\txcompatadded[opt]{arg}#S
\txcompatadded{arg}#S
\txcompatcomment[opt]{arg}#S
\txcompatcomment{arg}#S
\txcompatdeleted[opt]{arg}#S
\txcompatdeleted{arg}#S
\txcompathighlight[opt]{arg}#S
\txcompathighlight{arg}#S
\txcompatreplaced[opt]{arg1}{arg2}#S
\txcompatreplaced{arg1}{arg2}#S
\txhighlightedname#S
\txlistchangesname#S
\txnochangesname#S
\txpendingname#S
\txrejectedname#S
\txremovedname#S
\txreplacedname#S
\txreportline{arg1}{arg2}{arg3}{arg4}{arg5}#S
\txsetaddedmarkup{arg}#S
\txsetanonymousname{arg}#S
\txsetauthormarkupposition{arg}#S
\txsetauthormarkuptext{arg}#S
\txsetauthormarkup{arg}#S
\txsetcommentmarkup{arg}#S
\txsetdeletedmarkup{arg}#S
\txsethighlightmarkup{arg}#S
\txsetlocextension{arg}#S
\txsetsocextension{arg}#S
\txsetsummarytowidth{arg}#S
\txsetsummarywidth{arg}#S
\txsettruncatewidth{arg}#S
\txstatusname#S
\txsummaryentry{arg1}{arg2}#S
\txsummaryname#S