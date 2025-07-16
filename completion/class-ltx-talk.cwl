# ltx-talk class
# Matthew Bertucci 2025/07/13 for v0.1.0

#include:pdfmanagement
#include:relsize
#include:geometry
#include:unicode-math
#include:hyperref
#include:xcolor
#include:graphicx

#keyvals:\documentclass/ltx-talk#c
aspect-ratio=%<width:height%>
frame-title-arg
mode=#handout,projector
#endkeyvals

#ifOption:frame-title-arg
\begin{frame}{title%text}
\begin{frame}[options%keyvals]{title%text}
\begin{frame}<overlay spec>{title%text}
\begin{frame}<overlay spec>[options%keyvals]{title%text}
\begin{frame*}{title%text}
\begin{frame*}[options%keyvals]{title%text}
\begin{frame*}<overlay spec>{title%text}
\begin{frame*}<overlay spec>[options%keyvals]{title%text}
#endif

\begin{actionenv}
\begin{actionenv}<action spec>
\end{actionenv}
\begin{alertenv}
\begin{alertenv}<overlay spec>
\end{alertenv}
\begin{columns}
\begin{columns}<overlay spec>
\begin{columns}<overlay spec>[options%keyvals]
\begin{columns}[options%keyvals]
\end{columns}
\begin{column}<overlay spec>[placement%keyvals]{width}
\begin{column}<overlay spec>{width}
\begin{column}[placement%keyvals]{width}
\begin{column}{width}
\end{column}
\begin{description}[<%<default overlay spec%>>]
\begin{description}[options%keyvals]
\begin{enumerate}[<%<default overlay spec%>>]
\begin{enumerate}[options%keyvals]
\begin{frame*}
\begin{frame*}<overlay spec>
\begin{frame*}<overlay spec>[options%keyvals]
\begin{frame*}[options%keyvals]
\end{frame*}
\begin{frame}
\begin{frame}<overlay spec>
\begin{frame}<overlay spec>[options%keyvals]
\begin{frame}[options%keyvals]
\end{frame}
\begin{invisibleenv}
\begin{invisibleenv}<overlay spec>
\end{invisibleenv}
\begin{itemize}[<%<default overlay spec%>>]
\begin{itemize}[options%keyvals]
\begin{onlyenv}
\begin{onlyenv}<overlay spec>
\end{onlyenv}
\begin{overlayarea}{width}{height}
\end{overlayarea}
\begin{overprint}
\begin{overprint}[width]
\end{overprint}
\begin{uncoverenv}
\begin{uncoverenv}<overlay spec>
\end{uncoverenv}
\begin{visibleenv}
\begin{visibleenv}<overlay spec>
\end{visibleenv}

\action<action spec>{text}
\action{text}
\alert<overlay spec>{text}
\alert{text}
\alt<overlay spec>{default text%text}{alternative text%text}
\alt{default text%text}{alternative text%text}
\color<overlay spec>[model]{color}
\color<overlay spec>{color}
\emph<overlay spec>{text}
\framesubtitle<overlay spec>[options%keyvals]{text}#*
\framesubtitle<overlay spec>{text}
\framesubtitle[options%keyvals]{text}#*
\framesubtitle{text}
\frametitle<overlay spec>[options%keyvals]{text}#*
\frametitle<overlay spec>{text}
\frametitle[options%keyvals]{text}#*
\frametitle{text}
\includegraphics<overlay spec>[options%keyvals]{imagefile}#g
\includegraphics<overlay spec>{imagefile}#g
\invisible<overlay spec>{text}
\invisible{text}
\item<action spec>
\item<action spec>[label%text]
\mathcolor<overlay spec>[model]{color}{math}
\mathcolor<overlay spec>{color}{math}
\only<overlay spec>{text}
\only{text}
\onslide
\onslide<overlay spec>
\pause
\pause[overlay spec]
\temporal<overlay spec>{before slide text%text}{default text%text}{after slide text%text}
\temporal{before slide text%text}{default text%text}{after slide text%text}
\textbf<overlay spec>{text}
\textcolor<overlay spec>[model]{color}{text}
\textcolor<overlay spec>{color}{text}
\textit<overlay spec>{text}
\textmd<overlay spec>{text}
\textnormal<overlay spec>{text}
\textrm<overlay spec>{text}
\textsc<overlay spec>{text}
\textsf<overlay spec>{text}
\textsl<overlay spec>{text}
\texttt<overlay spec>{text}
\textup<overlay spec>{text}
\uncover<overlay spec>{text}
\uncover{text}
\visible<overlay spec>{text}
\visible{text}

#keyvals:\begin{columns}
vertical-alignment=#bottom,center,top
width=##L
#endkeyvals

#keyvals:\begin{column}
b
c
t
vertical-alignment=#bottom,center,top
#endkeyvals

#keyvals:\begin{frame},\begin{frame*}
tag-slides=%<spec%>
vertical-alignment=#bottom,center,stretch,top
#endkeyvals

# not documented
\begin{block}{title%text}
\begin{block}<action spec>{title%text}
\end{block}
\DeclareColor{name%specialDef}[model]{color-spec}#s#%color
\DeclareColor{name%specialDef}{color}#s#%color
\insertsection#*
\insertsubsection#*
\insertsubsubsection#*
\institute[options%keyvals]{institute%text}
\institute{institute%text}
\label<overlay spec>{label}#l
\maketitle[options%keyvals]
\mode<mode spec>{text}
\mode{text}
\subtitle[options%keyvals]{text}
\subtitle{text}
\thepauses#*
\theslide#*

alert#B
example#B
structure#B

\stdcolor#S
\stdincludegraphics#S
\stditem#S
\stdmathcolor#S
\stdnewtheorem#S
\stdtextcolor#S