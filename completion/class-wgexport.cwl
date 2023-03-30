# wgexport class
# Matthew Bertucci 2023/03/30 for v0.5

#include:class-standalone
#include:wargame

#keyvals:\documentclass/wgexport#c
noterrainpic
terrainpic
# options passed to standalone class
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

\begin{imagelist}
\begin{imagelist}[jobname]
\end{imagelist}
\info{image-name}{category}{subcategory}
\info*{image-name}{category}{subcategory}
\chitimages{counter}
\chitimages[faction]{counter}
\doublechitimages{counter}
\doublechitimages[faction]{counter}
\begin{boardimage}{image-name}{subcategory}
\begin{boardimage}[classification]{image-name}{subcategory}
\end{boardimage}

\dice{name}{name}{list}
\dice[tikz-options]{name}{name}{list}
\dice[tikz-options][node-options]{name}{name}{list}

\battlemarkers{arg}#S
\battlemarkers[opt]{arg}#S
\oddsmarkers{arg}#S
\oddsmarkers[opt]{arg}#S
\resultmarkers{arg}#S
\resultmarkers[opt]{arg}#S
\commonicons{arg1}{arg2}#S

## from standalone options
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
