#logsys.cwl
#for logsys package
#neeraavi 26 Mar 2007

#include:coordsys

#keyvals:\usepackage/logsys#c
centred
outside
inside
#endkeyvals

\logline{from}{to}
\logline[spacing]{from}{to}
\logline*{from}{to}
\logline*[spacing]{from}{to}

\vlogline{from}{to}
\vlogline[spacing]{from}{to}
\vlogline*{from}{to}
\vlogline*[spacing]{from}{to}

\logsys(lower-left)(upper-right)
\logsys[h-spacing](lower-left)(upper-right)#*
\logsys[h-spacing][v-spacing](lower-left)(upper-right)
\logsys*(lower-left)(upper-right)
\logsys*[h-spacing](lower-left)(upper-right)#*
\logsys*[h-spacing][v-spacing](lower-left)(upper-right)

\semilogsys(lower-left)(upper-right)
\semilogsys[h-spacing](lower-left)(upper-right)#*
\semilogsys[h-spacing][v-spacing](lower-left)(upper-right)
\semilogsys*(lower-left)(upper-right)
\semilogsys*[h-spacing](lower-left)(upper-right)#*
\semilogsys*[h-spacing][v-spacing](lower-left)(upper-right)

\loglogsys(lower-left)(upper-right)
\loglogsys[h-spacing](lower-left)(upper-right)#*
\loglogsys[h-spacing][v-spacing](lower-left)(upper-right)
\loglogsys*(lower-left)(upper-right)
\loglogsys*[h-spacing](lower-left)(upper-right)#*
\loglogsys*[h-spacing][v-spacing](lower-left)(upper-right)

\loggrid(lower-left)(upper-right)
\loggrid[h-spacing](lower-left)(upper-right)#*
\loggrid[h-spacing][v-spacing](lower-left)(upper-right)
\loggrid*(lower-left)(upper-right)
\loggrid*[h-spacing](lower-left)(upper-right)#*
\loggrid*[h-spacing][v-spacing](lower-left)(upper-right)

\semiloggrid(lower-left)(upper-right)
\semiloggrid[h-spacing](lower-left)(upper-right)#*
\semiloggrid[h-spacing][v-spacing](lower-left)(upper-right)
\semiloggrid*(lower-left)(upper-right)
\semiloggrid*[h-spacing](lower-left)(upper-right)#*
\semiloggrid*[h-spacing][v-spacing](lower-left)(upper-right)

\logloggrid(lower-left)(upper-right)
\logloggrid[h-spacing](lower-left)(upper-right)#*
\logloggrid[h-spacing][v-spacing](lower-left)(upper-right)
\logloggrid*(lower-left)(upper-right)
\logloggrid*[h-spacing](lower-left)(upper-right)#*
\logloggrid*[h-spacing][v-spacing](lower-left)(upper-right)

\interval
\intervalthickness{width}
\intervalthickness[offset%l]{width}
\vinterval
