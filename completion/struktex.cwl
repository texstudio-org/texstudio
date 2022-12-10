# struktex package
# Matthew Bertucci 2022/12/08 for v2.3c-0-g7d3fc5b

#include:ifthen
#include:struktxf
#include:struktxp
#include:pict2e

#keyvals:\usepackage/struktex#c
english
german
ngerman
curves
emlines
pict2e
verification
nofiller
draft
final
debug
outer
#endkeyvals

#ifOption:curves
#include:curves
#endif

#ifOption:emlines
#include:emlines2
#endif

#ifOption:verification
\assert{assertion%text}
\assert[height]{assertion%text}
#endif

\StrukTeX

\begin{struktogramm}(width,height)#\pictureHighlight
\begin{struktogramm}(width,height)[title%text]
\end{struktogramm}

\sProofOn
\sProofOff
\PositionNSS{position}
\assign{content%text}
\assign[height]{content%text}

\begin{declaration}
\begin{declaration}[title%text]
\end{declaration}

\declarationtitle
\description{variable name}{description%text}
\descriptionindent
\descriptionwidth
\descriptionsep

\sub{text}
\sub[height]{text}
\return{text}
\return[height]{text}

\while{text}
\while[width]{text}
\whileend
\until{text}
\until[width]{text}
\untilend
\forallin{text}
\forallin[width]{text}
\forallinend
\forever
\forever[width]
\foreverend
\exit{text}
\exit[height]{text}

\ifthenelse{left angle}{right angle}{condition%text}{left text%text}{right text%text}
\ifthenelse[height]{left angle}{right angle}{condition%text}{left text%text}{right text%text}
\change
\ifend

\case{angle}{num cases}{condition%text}{case1 text%text}
\case[height]{angle}{num cases}{condition%text}{case1 text%text}
\switch{case-n text%text}
\switch[position]{case-n text%text}
\caseend

\inparallel{num tasks}{task1 description%text}
\inparallel[height]{num tasks}{task1 description%text}
\task{task-n description%text}
\task[position]{task-n description%text}
\inparallelend

\begin{centernss}
\end{centernss}

\CenterNssFile{file}#i
\centernssfile{file}#*i

# not documented
\dimtomm{arg}#S
\getnum[arg]#S
\getoption[arg]#S

# deprecated
\openstrukt{width}{height}#S
\closestrukt#S
\dfr#S
\dfrend#S