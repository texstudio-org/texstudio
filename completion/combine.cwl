# combine class
# Matthew Bertucci 11/3/2021 for v0.7a

#include:keyval

#ifOption:memoir
#include:class-memoir
#endif

#ifOption:book
#include:class-book
#endif

#ifOption:letter
#include:class-letter
#endif

\begin{papers}
\begin{papers}[text/code]
\end{papers}

\import{file}#i

\maintitlefont#*
\postmaintitle#*
\mainauthorfont#*
\postmainauthor#*
\maindatefont#*
\postmaindate#*
\importtitlefont#*
\postimporttitle#*
\importauthorfont#*
\postimportauthor#*
\importdatefont#*
\postimportdate#*

\bodytitle{long title}
\bodytitle[short title]{long title}
\bodytitlemark{text}#*
\coltoctitle{title%text}
\coltoctitle{author}
\published{long%text}
\published[short]{long%text}

\pubfont#*
\toctitleindent#*
\tocauthorindent#*
\tocpubindent#*
\toctocindent#*
\toctitlefont#*
\tocauthorfont#*
\tocpubfont#*
\begin{tocindent}#*
\end{tocindent}#*

\erasetitling

\provideenvironment{envname}{begdef}{enddef}#*N
\providelength{newlength%cmd}#*d
\providecounter{counter name}#*
\zeroextracounters#*
\appendiargdef{macro}{stuff}#*
\emptyAtBeginDocument#*
\thecolpage#*
\setuppapers#*
\takedownpapers#*