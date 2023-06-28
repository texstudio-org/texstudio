# tucv package
# Matthew Bertucci 4/25/2022 for v1.0

#include:array
#include:color
#include:calc
#include:fancyhdr

#keyvals:\usepackage/tucv#c
pagesetup
#endkeyvals

\resbib{title%text}{information%text}
\resconference[description%text]{conference name}{role%text}
\resconference{conference name}{role%text}
\resdegree[description%text]{degree%text}
\resdegree{degree%text}
\resdesc{item%text}{description%text}
\resemployer[description%text]{name}
\resemployer{name}
\resentry[indent]{left text%text}{right text%text}
\resentry{left text%text}{right text%text}
\resentrysinglecol[indent]{text}
\resentrysinglecol{text}
\resheading{heading%text}
\resjob[description%text]{job name%text}{start}{end}
\resjob{job name%text}{start}{end}
\resschool{school name}{location}
\ressubconference[description%text]{name}
\ressubconference{name}
\ressubentry{left text%text}{right text%text}
\ressubentrysinglecol{text}

tucvheading#B