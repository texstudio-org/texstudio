# sgamevar package
# Matthew Bertucci 4/4/2022 for v2.15

#include:color

\begin{game}{rows}{columns}#\tabular
\begin{game}{rows}{columns}[game label]
\begin{game}{rows}{columns}[row label][column label]
\begin{game}{rows}{columns}[row label][column label][game label]
\end{game}
\begin{game*}{rows}{columns}#\tabular
\begin{game*}{rows}{columns}[game label]
\begin{game*}{rows}{columns}[row label][column label]
\begin{game*}{rows}{columns}[row label][column label][game label]
\end{game*}

\gamestretch
\sgcolsep
\sglabelsep
\ifirpawcgl#*
\irpawcgltrue
\irpawcglfalse
\ifirplwcgl#*
\irplwcgltrue
\irplwcglfalse
\ifgamemath#*
\gamemathtrue
\gamemathfalse
\ifgamevalign#*
\gamevaligntrue
\gamevalignfalse
\ifssual#*
\ssualtrue
\ssualfalse
\sglinecolor
\sgtextcolor

# not documented
\begin{gtabular}{preamble}#S\tabular
\end{gtabular}#S
\begin{gstartabular}#S\tabular
\end{gstartabular}#S
\enoughcols#S
\tempstretch#S