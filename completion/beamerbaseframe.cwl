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
\begin{frame}<overlay specification>[<default overlay specification>][options%keyvals]
\begin{frame}<overlay specification>[<default overlay specification>][options%keyvals]{title}
\begin{frame}<overlay specification>[<default overlay specification>][options%keyvals]{title}{subtitle}
\begin{frame}[<default overlay specification>]
\begin{frame}[<default overlay specification>][options%keyvals]
\begin{frame}[<default overlay specification>][options%keyvals]{title}
\begin{frame}[<default overlay specification>][options%keyvals]{title}{subtitle}
\begin{frame}[options%keyvals]
\begin{frame}[options%keyvals]{title}
\begin{frame}[options%keyvals]{title}{subtitle}
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
\againframe<overlay specification>[options%keyvals]{name}
\againframe[options%keyvals]{name}
\againframe[<default overlay specification>][options%keyvals]{name}
\againframe<overlay specification>[<default overlay specification>][options%keyvals]{name}

#keyvals:\begin{frame},\againframe
allowdisplaybreaks
allowdisplaybreaks=#0,1,2,3,4
allowframebreaks
allowframebreaks=%<fraction%>
b
c
t
s
noframenumbering
fragile
fragile=singleslide
environment=%<envname%>
label=##l
plain
shrink
shrink=%<min shrink percent%>
squeeze
#endkeyvals
