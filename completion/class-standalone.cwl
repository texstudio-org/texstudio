# standalone class
# Matthew Bertucci 3/26/2022 for v1.3a

#include:ifluatex
#include:ifpdf
#include:ifxetex
#include:shellesc
#include:xkeyval

#keyvals:\documentclass/standalone,\standaloneconfig
beamer#true,false
border=##L
border={%<<l/r> <t/b>%>}
border={%<<l> <b> <r> <t>%>}
class=%<class name%>
convert#true,false
convert={%<conversion options%>}
crop#true,false
float#true,false
float#true,false
gif#true,false
gif={%<conversion options%>}
ignoreempty#true,false
ignorerest#true,false
jpg#true,false
jpg={%<conversion options%>}
margin=##L
math#true,false
multi#true,false
multi={%<envname1,envname2,...%>}
multido#true,false
png#true,false
png={%<conversion options%>}
preview#true,false
pstricks#true,false
tikz#true,false
varwidth#true,false
varwidth=##L
#endkeyvals

#keyvals:\documentclass/standalone
10pt
11pt
12pt
#endkeyvals

#ifOption:beamer
#include:class-beamer
\begin{standaloneframe}
\begin{standaloneframe}<overlay spec>
\begin{standaloneframe}<overlay spec>[<default overlay spec>]
\begin{standaloneframe}<overlay spec>[<default overlay spec>][options]
\begin{standaloneframe}<overlay spec>[<default overlay spec>][options]{title}
\begin{standaloneframe}<overlay spec>[<default overlay spec>][options]{title}{subtitle%text}
\begin{standaloneframe}[<default overlay spec>]
\begin{standaloneframe}[<default overlay spec>][options]
\begin{standaloneframe}[<default overlay spec>][options]{title}
\begin{standaloneframe}[<default overlay spec>][options]{title}{subtitle%text}
\begin{standaloneframe}[options]
\begin{standaloneframe}[options]{title}
\begin{standaloneframe}[options]{title}{subtitle%text}
\begin{standaloneframe}{title}
\end{standaloneframe}
#endif
#ifOption:beamer=true
#include:class-beamer
\begin{standaloneframe}
\begin{standaloneframe}<overlay spec>
\begin{standaloneframe}<overlay spec>[<default overlay spec>]
\begin{standaloneframe}<overlay spec>[<default overlay spec>][options]
\begin{standaloneframe}<overlay spec>[<default overlay spec>][options]{title}
\begin{standaloneframe}<overlay spec>[<default overlay spec>][options]{title}{subtitle%text}
\begin{standaloneframe}[<default overlay spec>]
\begin{standaloneframe}[<default overlay spec>][options]
\begin{standaloneframe}[<default overlay spec>][options]{title}
\begin{standaloneframe}[<default overlay spec>][options]{title}{subtitle%text}
\begin{standaloneframe}[options]
\begin{standaloneframe}[options]{title}
\begin{standaloneframe}[options]{title}{subtitle%text}
\begin{standaloneframe}{title}
\end{standaloneframe}
#endif

#ifOption:math
\multimathsep#*
\begin{multimath}#\math
\end{multimath}
\multidisplaymathsep#*
\begin{multidisplaymath}#\math
\end{multidisplaymath}
#endif
#ifOption:math=true
\multimathsep#*
\begin{multimath}#\math
\end{multimath}
\multidisplaymathsep#*
\begin{multidisplaymath}#\math
\end{multidisplaymath}
#endif

#ifOption:multido
#include:multido
#endif
#ifOption:multido=true
#include:multido
#endif

#ifOption:preview
#include:preview
#endif
#ifOption:preview=true
#include:preview
#endif

#ifOption:pstricks
#include:pstricks
#endif
#ifOption:pstricks=true
#include:pstricks
#endif

#ifOption:tikz
#include:tikz
#endif
#ifOption:tikz=true
#include:tikz
#endif

#ifOption:varwidth
#include:varwidth
#endif
#ifOption:varwidth=true
#include:varwidth
#endif

\standaloneconfig{options%keyvals}
\standaloneenv{envname1,envname2,...}

\standaloneignore#*
\begin{standalone}#*
\end{standalone}#*
\thesapage#*
\ifstandalone#*
\standalonetrue#*
\standalonefalse#*
\ifstandalonebeamer#*
\standalonebeamertrue#*
\standalonebeamerfalse#*
\IfStandalone{code for standalone}{code for main document}#*
\onlyifstandalone{code}#*
