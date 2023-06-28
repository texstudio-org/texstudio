# dmlb package
# Matthew Bertucci 2022/07/24 for v2018-07-22

#include:etoolbox
#include:microtype
#include:xstring
#include:longtable
#include:array
#include:multicol
#include:multirow
#include:rotating
#include:caption
#include:fancyhdr
#include:xcolor
# loads table option of xcolor
#include:bookmark
#include:babel
# loads english option of babel
#include:ellipsis
# loads xspace option of ellipsis
#include:pgf
#include:pgfplots
#include:pgfplotstable
#include:pgfplotslibrarydateplot

#keyvals:\usepackage/dmlb#c
graph
#endkeyvals

#ifOption:graph
#include:pgfcalendar
#include:tikzlibrarycalendar
#include:tikzlibraryexternal
#endif

evenRowColor#B
oddRowColor#B
evenRowTextColor#B
oddRowTextColor#B
tableColor#B
headerColor#B
curveColor#B

\row
\dmlbsetdate{YYYY}{MM}{DD}
\dmlbsetdate{YYYY}{MM}{DD}[rel path]
\QQQ{time}{blood glucose}{insulin}{carbohydrates}{protein}{fat}{remarks%text}
\QQQ[date]{time}{blood glucose}{insulin}{carbohydrates}{protein}{fat}{remarks%text}

\autoFileInput{rel path}#*
\calcmaxrows#*
\changestrut#*
\Day#*
\fixme#S
\Month#*
\rowstyle{style commands}#*
\sYear#S
\TwoDigits{num}#*
\writeperiods#*
\Year#*

# from table option of xcolor
#include:colortbl

# from english option of babel
\captionsenglish#*
\dateenglish#*
\extrasenglish#*
\noextrasenglish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*

# from xspace option of ellipsis
#include:xspace
