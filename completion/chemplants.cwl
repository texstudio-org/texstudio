# chemplants package
# Matthew Bertucci 2/16/2022 for v0.9.9

#include:ifthen
#include:tikz
#include:tikzlibrarydecorations.markings
#include:tikzlibraryhobby
#include:tikzlibrarybending

\measure{(x1,y1)}{(x2,y2)}{label}
\measure[anchor spec]{(x1,y1)}{(x2,y2)}{label}
\setchpblockfontsize{fontsize%l}
\setchpblockscale{factor}
\setchpblockthickness{thickness%l}
\setchphiddencomponentstyle{line pattern}
\setchphiddenstreamstyle{line pattern}
\setchpinstrumentfontsize{fontsize%l}
\setchpinstrumentscale{factor}
\setchpinstrumentthickness{thickness%l}
\setchpmainstreamthickness{thickness%l}
\setchpmeasurecolor{color}
\setchpmeasurefontsize{fontsize%l}
\setchpmeasurethickness{thickness%l}
\setchpmeasuretip{line tip}
\setchpsecondarystreamthickness{thickness%l}
\setchpsignalthickness{thickness%l}
\setchpstreamtip{arrow tip}
\setchpunitscale{factor}
\setchpunitthickness{thickness%l}
\setchputilitystreamthickness{thickness%l}

\chpdate#S
\chpversion#S

#keyvals:\draw#c
main stream
secondary stream
utility stream
hidden stream
signal
short signal
#endkeyvals

#keyvals:\pic#c
hidden component
#endkeyvals
