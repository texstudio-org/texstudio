# resphilosophica class
# Matthew Bertucci 3/28/2022 for v1.35

#include:xkeyval
#include:class-amsart
#include:microtype
#include:fancyhdr
#include:xcolor
#include:lastpage
#include:collect
#include:footmisc
#include:hyperref
#include:mathdesign
#include:lsabon
#include:natbib

#keyvals:\documentclass/resphilosophica#c
8pt
9pt
10pt
11pt
12pt
manuscript
screen
preprint
forthcoming
bodyfont=#auto,sabon,cm
rpfont=#auto,imprintshadow,cm
natbib#true,false
#endkeyvals

\AddtoEndMatter{bibliography commands}
\articleentry{arg1}{arg2}{arg3}{arg4}#S
\authornote{note%text}
\begin{notes}{title%text}
\copyrightnote{copyright statement%text}
\copyrightyear{year}
\doinumber{DOI}
\ECSelect{level1,level2,...}
\EditorialComment[level]{comments%text}
\EditorialComment{comments%text}
\end{notes}
\endpage{number}
\issuenumber{%<number(s)%>}
\manuscriptid{id}
\onlinedate{date}
\papernumber{number}
\paperUrl{URL}#U
\prevpaper{previous paper%definition}
\publicationmonth[%<abbrev month(s)%>]{%<month(s)%>}
\publicationmonth{%<month(s)%>}
\publicationyear{year}
\rpdefault#*
\startpage{number}
\TC[level]{text}
\TC{text}
\TCSelect[color]{level1,level2,...}
\TCSelect{level1,level2,...}
\titlenote{note%text}
\volumenumber{%<number(s)%>}