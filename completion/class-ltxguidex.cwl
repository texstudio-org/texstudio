# ltxguidex class
# Matthew Bertucci 11/16/2021 for v0.2.0

#include:class-ltxguide
#include:hyperref
#include:xkeyval
#include:xcolor
#include:framed
#include:showexpl
#include:enumitem

\pipe
\bs
\meta{arg}
\ctanlogo
\command{csname}
\cs{csname}#*

\begin{desc}
\end{desc}

\email{address}#U
\https{URL}#U
\http{URL}#U
\ctan{package}#U

\package{package}
\ltxclass{class}
\option{option}
\filename{file}
\extension{file extension}

\begin{latexcode}#V
\end{latexcode}

\New{text}

\begin{warning}
\end{warning}
\begin{note}
\end{note}
\begin{example}
\end{example}
\begin{bug}
\end{bug}

\newnotice{envname}{text}

\begin{packages}
\end{packages}
\begin{classes}
\end{classes}
\begin{options}
\end{options}

\begin{advise}
\end{advise}
\begin{faq}
\end{faq}
\Q
\A
\advisespace

\alternative{csv list}

\begin{keys}
\end{keys}
\key{key name}[key value]
\key{key name}[key value][default value]
\key[options%keyvals]{key name}[key value]
\key[options%keyvals]{key name}[key value][default value]
\bool

#keyvals:\key
default=%<default value%>
note=%<note%>
v=
#endkeyvals

\noticestyle#*
\newdescriptionenvironment{envname}{label cmd}#*N
\labeladvise#*
\advisestyle#*
\docstrip#*
\Th{text}#*
\Th[cols]{text}#*