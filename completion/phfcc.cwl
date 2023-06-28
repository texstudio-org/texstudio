# phfcc package
# Matthew Bertucci 10/13/2021 for v2.0

#include:xkeyval
#include:kvoptions
#include:etoolbox
#include:xcolor
#include:marginnote

\phfMakeCommentingCommand{cmd name}
\phfMakeCommentingCommand[options%keyvals]{cmd name}

#keyvals:\phfMakeCommentingCommand#c,\phfDefineCommentingStyle#c,\phfSetDefaultCommentingStyle#c
color=#%color
initials={%<initials%>}
formatinitials=%<format cmds%>
formatinitials=#default,margin,box,nobox,hide,footnote
style=#footcomments,rmstrikethrough
font={%<font cmds%>}
spacing=##L
begin=
end=
cfont={%<font cmds%>}
cspacing=##L
cbegin=
cend=
rmfont={%<font cmds%>}
rmspacing=##L
rmbegin=
rmend=
ifont={%<font cmds%>}
ispacing=##L
ibegin=
iend=
#endkeyvals

\phfDisableCommentingCommands

\phfDefineCommentingStyle{style name}{options%keyvals}
\phfSetDefaultCommentingStyle{options%keyvals}

\phfccformatmargininitials{initials}#*
\phfccmargininitialssep#*
\phfccformatboxinitials{initials}#*
\phfCCChangesBy{initials}#*
\phfCommentingDefaultStartCmds#*
\phfCommentingDefaultEndCmds#*
\phfCommentingDefaultFont#*
\phfCommentingDefaultSpacing#*
\phfCommentingDefaultBegin#*
\phfCommentingDefaultEnd#*
\phfCommentingDefaultCFont#*
\phfCommentingDefaultCSpacing#*
\phfCommentingDefaultCBegin#*
\phfCommentingDefaultCEnd#*
\phfCommentingDefaultRmFont#*
\phfCommentingDefaultRmSpacing#*
\phfCommentingDefaultRmBegin#*
\phfCommentingDefaultRmEnd#*
\phfCommentingDefaultIFont#*
\phfCommentingDefaultISpacing#*
\phfCommentingDefaultIBegin#*
\phfCommentingDefaultIEnd#*
\phfccfootcommenttextstyle#*
\newphfccmarginnote#S