# sesstime package
# Matthew Bertucci 1/30/2022 for v1.12

#include:keyval

\timingconfigure{options%keyvals}
\timingconfigure[cond]{options%keyvals}

#keyvals:\usepackage/sesstime#c,\timingconfigure
print#true,false
block#true,false
chapter#true,false
session#true,false
comment#true,false
warning#true,false
width=##L
widthl=##L
widthr=##L
autosession=%<duration%>
depthsec=%<depth%>
depthpar=%<depth%>
flags={%<flag1,flag2,...%>}
#endkeyvals

\timingstart{abstime}
\timingstart[cond%keyvals]{abstime}
\timingstart*{reltime}
\timingstart*[cond%keyvals]{reltime}
\timingsplit{abstime}
\timingsplit[cond%keyvals]{abstime}
\timingsplit*{reltime}
\timingsplit*[cond%keyvals]{reltime}
\timingstop{abstime}
\timingstop[cond%keyvals]{abstime}
\timingstop*{reltime}
\timingstop*[cond%keyvals]{reltime}
\timingnext{abstime}
\timingnext[cond%keyvals]{abstime}
\timingnext*{reltime}
\timingnext*[cond%keyvals]{reltime}

\timinglapse{reltime}
\timinglapse[cond%keyvals]{reltime}
\timinggauge{abstime}
\timinggauge[cond%keyvals]{abstime}

\timingblocktotal
\timingblocktotal[error]
\timingblocktotal*
\timingblocktotal*[error]

\timingchapter
\timingchapter[cond%keyvals]
\timingchapterend
\timingchapterend[cond%keyvals]

\timingchapterlabel{chapterlabel%special}#s#%chapterlabel
\timingchaptertotal{chapterlabel%special}
\timingchapterlabel[error]{chapterlabel%special}
\timingchaptertotal*{chapterlabel%special}
\timingchapterlabel*[error]{chapterlabel%special}
\timingreturn

\timingsession
\timingsession[cond%keyvals]
\timingsessionend
\timingsessionend[cond%keyvals]

\timinglistofsessions

\timingcomment{comment%text}
\timingcomment[cond%keyvals]{comment%text}

\timingif{code}
\timingif[cond%keyvals]{code}

#keyvals:\timingstart,\timingstart*,\timingsplit,\timingsplit*,\timingstop,\timingstop*,\timingnext,\timingnext*,\timinglapse,\timinggauge,\timingchapter,\timingchapterend,\timingsession,\timingsessionend,\timingcomment,\timingif
if=%<flag%>
not=%<flag%>
#endkeyvals

# not documented
\timingprint{arg}#*
\timingprint[opt]{arg}#*
\timingprintblock{arg1}{arg2}{arg3}#*
\timingprintchapter{arg}#*
\timingprintmark{arg}#*
\timingprintremark{arg}#*
\timingprintsession{arg1}{arg2}#*
\timingsessionline{arg1}{arg2}{arg3}{arg4}{arg5}#*
\timingsessiontotal{arg}#*
\timingsessiontotal[opt]{arg}#*