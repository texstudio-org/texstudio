# tocdata package
# Matthew Bertucci 11/22/2021 for v2.04

#include:etoolbox
#include:xpatch

\tocdataformat{text}#*
\tocdata{list extension}{text}

\partauthor{title}{first}{last}#L0
\partauthor[list entry]{title}{first}{last}#L0
\partauthor[list entry]{title}[prefix]{first}{last}[suffix]#L0
\chapterauthor{title}{first}{last}#L1
\chapterauthor[list entry]{title}{first}{last}#L1
\chapterauthor[list entry]{title}[prefix]{first}{last}[suffix]#L1
\sectionauthor{title}{first}{last}#L2
\sectionauthor[list entry]{title}{first}{last}#L2
\sectionauthor[list entry]{title}[prefix]{first}{last}[suffix]#L2
\subsectionauthor{title}{first}{last}#L3
\subsectionauthor[list entry]{title}{first}{last}#L3
\subsectionauthor[list entry]{title}[prefix]{first}{last}[suffix]#L3

\captionartist{title%text}{first}{last}
\captionartist[list entry]{title%text}{first}{last}
\captionartist[list entry]{title%text}[prefix]{first}{last}[suffix]
\captionauthor{title%text}{first}{last}
\captionauthor[list entry]{title%text}{first}{last}
\captionauthor[list entry]{title%text}[prefix]{first}{last}[suffix]
\captionartist*{title%text}{first}{last}#*
\captionartist*[list entry]{title%text}{first}{last}#*
\captionartist*[list entry]{title%text}[prefix]{first}{last}[suffix]#*
\captionauthor*{title%text}{first}{last}#*
\captionauthor*[list entry]{title%text}{first}{last}#*
\captionauthor*[list entry]{title%text}[prefix]{first}{last}[suffix]#*

\tocdatapartprint{prefix}{first}{last}{suffix}#*
\tocdatachapterprint{prefix}{first}{last}{suffix}#*
\tocdatasectionprint{prefix}{first}{last}{suffix}#*
\tocdatasubsectionprint{prefix}{first}{last}{suffix}#*
\tocdataartistprint{prefix}{first}{last}{suffix}#*
\tocdataartisttextprint{text}#*
\tocdataauthorprint{prefix}{first}{last}{suffix}#*
\tocdataauthortextprint{text}#*

\tdartistjustify#*
\tdartistcenter#*
\tdartistleft#*
\tdartistright#*
\tdartisttextjustify#*
\tdartisttextcenter#*
\tdartisttextleft#*
\tdartisttextright#*
\tdauthorjustify#*
\tdauthorcenter#*
\tdauthorleft#*
\tdauthorright#*
\tdauthortextjustify#*
\tdauthortextcenter#*
\tdauthortextleft#*
\tdauthortextright#*

\settocdata{text}#*
\TDoptionalnameprint{name}#*
\TDartistauthorprint{author}{prefix}{first}{last}{suffix}#*
\TDartistauthortextprint{author}{text}#*	

# deprecated
\tocdatafont#S