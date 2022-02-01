# beamerbaseframe package
# Matthew Bertucci 1/30/2022 for v3.65

\framelatex{contents%text}#*
\refcounter{counter}#*
\thesubsectionslide#*
\insertframetitle#*
\insertframesubtitle#*

\resetcounteronoverlays{counter}
\resetcountonoverlays{count register}

\begin{frame}
\begin{frame}<overlay specification>
\begin{frame}<overlay specification>[<default overlay specification>]
\begin{frame}<overlay specification>[<default overlay specification>][options]
\begin{frame}<overlay specification>[<default overlay specification>][options]{title}
\begin{frame}<overlay specification>[<default overlay specification>][options]{title}{subtitle}
\begin{frame}[<default overlay specification>]
\begin{frame}[<default overlay specification>][options]
\begin{frame}[<default overlay specification>][options]{title}
\begin{frame}[<default overlay specification>][options]{title}{subtitle}
\begin{frame}[options]
\begin{frame}[options]{title}
\begin{frame}[options]{title}{subtitle}
\begin{frame}{title}
\end{frame}

\endframe#S
\framewidth#*
\beamerclosesubstitutedenvironement{envname}#*

\includeonlyframes{frame label list}

\theframenumber#*
\insertframenumber#*
\insertslidenumber#*
\insertoverlaynumber#*

\pagebreak<overlay specifications>
\nopagebreak<overlay specifications>
\framebreak
\noframebreak

\againframe{name}
\againframe<overlay specification>{name}
\againframe<overlay specification>[options]{name}
\againframe[options]{name}
\againframe[<default overlay specification>][options]{name}
\againframe<overlay specification>[<default overlay specification>][options]{name}