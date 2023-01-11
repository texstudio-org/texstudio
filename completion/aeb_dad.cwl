# aeb_dad package
# Matthew Bertucci 2022/05/13 for v1.2a

#include:annot_pro
#include:xkeyval
#include:calc
#include:refcount

\initDDGame{title%plain}
\ddDimens{keyvals}
#keyvals:\ddDimens
iconwidth=##L
iconheight=##L
targetwidth=##L
targetheight=##L
#endkeyvals
\ddGameIcon{icon name%specialDef}#s#%ddgameicon
\ddTargetOfIcon{icon name%keyvals}{caption%text}
#keyvals:\ddTargetOfIcon#c
%ddgameicon
#endkeyvals
\ddTargetCaption{text}#*
\ddTargetFmt{format cmds}
\ddReset
\ddReset[title%plain]

\ddRightMsg
\ddWrongMsg
\ddDragOnlyOne
\ddExternalMsg
\ddBadAppMsg

# not documented
\ddBtnAppr#*
\ddGameIconArgs#*
\ddTrueName#*
\theaebdadcnt#*
\thisDDNAME#*
\thisDDName{arg}#*