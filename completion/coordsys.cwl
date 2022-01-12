#coordsys.cwl
#for coordsys package
#neeraavi 26 Mar 2007

#keyvals:\usepackage/coordsys#c
centred
outside
inside
#endkeyvals

\numbline{from}{to}
\numbline[spacing]{from}{to}
\numbline*{from}{to}
\numbline*[spacing]{from}{to}

\vnumbline{from}{to}
\vnumbline[spacing]{from}{to}
\vnumbline*{from}{to}
\vnumbline*[spacing]{from}{to}

\coordsys(lower-left)(upper-right)
\coordsys[h-spacing](lower-left)(upper-right)#*
\coordsys[h-spacing][v-spacing](lower-left)(upper-right)
\coordsys*(lower-left)(upper-right)
\coordsys*[h-spacing](lower-left)(upper-right)#*
\coordsys*[h-spacing][v-spacing](lower-left)(upper-right)

\fcoordsys(lower-left)(upper-right)
\fcoordsys[h-spacing](lower-left)(upper-right)#*
\fcoordsys[h-spacing][v-spacing](lower-left)(upper-right)
\fcoordsys*(lower-left)(upper-right)
\fcoordsys*[h-spacing](lower-left)(upper-right)#*
\fcoordsys*[h-spacing][v-spacing](lower-left)(upper-right)

\bcoordsys(lower-left)(upper-right)
\bcoordsys[h-spacing](lower-left)(upper-right)#*
\bcoordsys[h-spacing][v-spacing](lower-left)(upper-right)
\bcoordsys*(lower-left)(upper-right)
\bcoordsys*[h-spacing](lower-left)(upper-right)#*
\bcoordsys*[h-spacing][v-spacing](lower-left)(upper-right)

\window(lower-left)(upper-right)
\window[h-spacing](lower-left)(upper-right)#*
\window[h-spacing][v-spacing](lower-left)(upper-right)
\window*(lower-left)(upper-right)
\window*[h-spacing](lower-left)(upper-right)#*
\window*[h-spacing][v-spacing](lower-left)(upper-right)

\coordgrid(lower-left)(upper-right)
\coordgrid[h-spacing](lower-left)(upper-right)#*
\coordgrid[h-spacing][v-spacing](lower-left)(upper-right)
\coordgrid*(lower-left)(upper-right)
\coordgrid*[h-spacing](lower-left)(upper-right)#*
\coordgrid*[h-spacing][v-spacing](lower-left)(upper-right)

\gridstyle{thin-declaration}{thick-declaration}

\sethlabel{label}
\sethlabel[alignment]{label}
\setvlabel{label}
\setvlabel[alignment]{label}

\hthickratio
\vthickratio

\rescaleby{num}{den}{cmd}
\rescaleby[symb]{num}{den}{cmd}

\tickstyle{thin-declaration}{thick-declaration}
\ticklength
