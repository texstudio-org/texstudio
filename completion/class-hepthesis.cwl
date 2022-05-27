# hepthesis class
# Matthew Bertucci 2022/05/26 for v1.5.1

#include:class-scrbook
#include:fontenc
# loads T1 option of fontenc
#include:etoolbox
#include:microtype
#include:changepage
#include:varwidth
#include:amsmath
#include:booktabs
#include:setspace
#include:fancyhdr
#include:tocbibind
#include:comment
#include:rotating
#include:caption
#include:afterpage
#include:csquotes

#keyvals:\documentclass/hepthesis#c
oneside
twoside
sftitles
rmtitles
bind
nobind
bindnopdf
noams
alphafoot
draft
hidefront
hideback
hidefrontback
hyper
hyperpdf
booktabs
nobooktabs
index
titling
hep
a4paper
a4narrow
a5paper
b5paper
letterpaper
legalpaper
executivepaper
10pt
11pt
12pt
hepfd
heplayout
hephyper
hepfloat
hepall
#endkeyvals

#ifOption:a4paper
a4wide
#endif

#ifOption:index
#include:makeidx
#endif

#ifOption:titling
#include:titling
#endif

#ifOption:hep
#include:hep
#endif
#ifOption:hepfd
#include:hep
#endif
#ifOption:heplayout
#include:hep
#endif
#ifOption:hephyper
#include:hep
#endif
#ifOption:hepfloat
#include:hep
#endif
#ifOption:hepall
#include:hep
#endif

#ifOption:draft
#include:lineno
#include:draftcopy
#endif

#ifOption:hyper
#include:hyperref
# loads hyperref with colorlinks=true option
#include:color
#endif
#ifOption:hyperpdf
#include:hyperref
# loads hyperref with colorlinks=true option
#include:color
#endif

\setspacing{choice%keyvals}
\setfrontmatterspacing{choice%keyvals}
\setmainmatterspacing{choice%keyvals}
\setappendixspacing{choice%keyvals}
\setbackmatterspacing{choice%keyvals}

#keyvals:\setspacing,\setfrontmatterspacing,\setmainmatterspacing,\setappendixspacing,\setbackmatterspacing
single
onehalf
double
#endkeyvals

\setextramargins{length}
\setfrontmatterextramargins{length}
\setmainmatterextramargins{length}
\setappendixextramargins{length}
\setbackmatterextramargins{length}
\setabstractextramargins{length}
\setdeclarationextramargins{length}
\setacknowledgementsextramargins{length}
\setprefaceextramargins{length}

\thetitle
\theauthor

\begin{frontmatter}
\end{frontmatter}
\begin{mainmatter}
\end{mainmatter}
\begin{appendices}
\end{appendices}
\begin{backmatter}
\end{backmatter}

\titlepage{title%text}
\titlepage[elaboration%text]{title%text}

\begin{declaration}
\end{declaration}
\begin{acknowledgements}
\end{acknowledgements}
\begin{preface}
\end{preface}

\dedication{text}
\frontquote{quote%text}{who}
\frontquote[language]{quote%text}{who}
\chapterquote{quote%text}{who}
\chapterquote[language]{quote%text}{who}
\pagequote{quote%text}{who}
\pagequote[language]{quote%text}{who}

\begin{colophon}
\end{colophon}

\verysubsection{title}

\smallfigwidth#*
\mediumfigwidth#*
\largefigwidth#*
\hugefigwidth#*

\Chapter
\Section
\Appendix
\Figure
\Table
\Equation
\Reference
\Page

\ChapterRef{label}#r
\SectionRef{label}#r
\AppendixRef{label}#r
\FigureRef{label}#r
\TableRef{label}#r
\EquationRef{label}#r
\ReferenceRef{label}#r
\PageRef{label}#r

# not documented
\begin{chapterintro}#S
\end{chapterintro}#S
\bigfigwidth#S
\filedate#S
\fileversion#S
\frontmattertitleskip#S
\italic#S
\littlefigwidth#S
\sans#S
\sansit#S
\thearg#S
\theiterlist#S

# deprecated
\definethesis{arg1}{arg2}#S