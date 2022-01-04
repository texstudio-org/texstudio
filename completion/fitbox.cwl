# fitbox package
# Matthew Bertucci 1/3/2022 for v1.02

#include:xkeyval

\fitbox{content%text}
\fitbox[options%keyvals]{content%text}
\fitbox*{content%text}
\fitbox*[options%keyvals]{content%text}

\fitboxset{options%keyvals}

\fitboxnatwidth#L
\fitboxnatheight#L

\SetFitboxLayout{rows}{columns}
\SetFitboxLayout[options%keyvals]{rows}{columns}

#keyvals:\fitbox,\fitbox*,\fitboxset,\SetFitboxLayout
maxheight=##L
maxwidth=##L
minheight=##L
minwidth=##L
belowboxspace=##L
maxenlargepage=##L
colsep=##L
colsepexpr=%<space macro%>
maincapheight=##L
maincaplines=%<integer%>
subcapheight=##L
subcaplines=%<integer%>
#endkeyvals