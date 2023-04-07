# scikgtex package
# Matthew Bertucci 2023/04/04 for v2.2.0

#include:luatex
#include:suffix

#keyvals:\usepackage/scikgtex#c
compatibility
#endkeyvals

\researchproblem{problem%text}
\researchproblem[number]{problem%text}
\researchproblem*{problem%text}
\researchproblem*[number]{problem%text}
\objective{objective%text}
\objective[number]{objective%text}
\objective*{objective%text}
\objective*[number]{objective%text}
\method{method%text}
\method[number]{method%text}
\method*{method%text}
\method*[number]{method%text}
\result{result%text}
\result[number]{result%text}
\result*{result%text}
\result*[number]{result%text}
\conclusion{conclusion%text}
\conclusion[number]{conclusion%text}
\conclusion*{conclusion%text}
\conclusion*[number]{conclusion%text}

\metatitle{title%text}
\metatitle*{title%text}
\metaauthor{name}
\metaauthor*{name}
\researchfield{field%text}
\researchfield*{field%text}

\contribution{property}{value}
\contribution[number]{property}{value}
\contribution*{property}{value}
\contribution*[number]{property}{value}

\uri{URI%URL}{label%text}#U

\addmetaproperty{name}
\addmetaproperty[model]{name}

# not documented
\hyperrefloaded#S
\useignorespacesandallpars#S
\ignorespacesandallpars#S
\newpropertycommand{name}#*
\newpropertycommand[model]{name}#*
