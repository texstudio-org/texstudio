# beamerbaseoverlay package
# Matthew Bertucci 1/30/2022 for v3.65

\only<overlay specification>{text}
\only{text}<overlay specification>
\only{text}

\alt<overlay specification>{default text%text}{alternative text%text}
\alt{default text%text}{alternative text%text}<overlay specification>
\alt{default text%text}{alternative text%text}

\begin{altenv}{begin text%text}{end text%text}{alternate begin text%text}{alternate end text%text}
\begin{altenv}<overlay specification>{begin text%text}{end text%text}{alternate begin text%text}{alternate end text%text}
\begin{altenv}{begin text%text}{end text%text}{alternate begin text%text}{alternate end text%text}<overlay specification>
\end{altenv}
\altenv#S
\endaltenv#S

\action<action specification>{text}
\action{text}

\begin{actionenv}
\begin{actionenv}<action specification>
\end{actionenv}
\actionenv#S
\endactionenv#S

\temporal{before slide text%text}{default text%text}{after slide text%text}
\temporal<overlay specification>{before slide text%text}{default text%text}{after slide text%text}

\beameroriginal{command}#*

\newenvironment<>{envname}{begdef}{enddef}#*N
\newenvironment<>{envname}[args]{begdef}{enddef}#*N
\newenvironment<>{envname}[args][default]{begdef}{enddef}#*N
\renewenvironment<>{envname}{begdef}{enddef}#*
\renewenvironment<>{envname}[args]{begdef}{enddef}#*
\renewenvironment<>{envname}[args][default]{begdef}{enddef}#*
\newcommand<>{cmd}[args][default]{def}#*d
\newcommand<>{cmd}[args]{def}#*d
\newcommand<>{cmd}{def}#*d
\renewcommand<>{cmd}[args][default]{def}#*
\renewcommand<>{cmd}[args]{def}#*
\renewcommand<>{cmd}{def}#*

\opaqueness<overlay specification>{percentage of opaqueness}

\setbeamercovered{options%keyvals}

#keyvals:\setbeamercovered
invisible
transparent
transparent=%<opaqueness%>
dynamic
highly dynamic
still covered=%<not yet list%>
again covered=%<once more list%>
#endkeyvals

\pause
\pause[number]

\music#*
\beamerpause#*

\onslide
\onslide<overlay specification>
\onslide<overlay specification>{text}
\onslide+<overlay specification>
\onslide+<overlay specification>{text}
\onslide*<overlay specification>
\onslide*<overlay specification>{text}

\item<alert specification>
\item<alert specification>[item label]
\item[item label]<alert specification>

\beamerdefaultoverlayspecification{default overlay specification}

\uncover{text}
\uncover<overlay specification>{text}
\visible{text}
\visible<overlay specification>{text}
\invisible{text}
\invisible<overlay specification>{text}

\begin{visibleenv}
\begin{visibleenv}<overlay specification>
\end{visibleenv}
\begin{invisibleenv}
\begin{invisibleenv}<overlay specification>
\end{invisibleenv}
\begin{uncoverenv}
\begin{uncoverenv}<overlay specification>
\end{uncoverenv}
\begin{onlyenv}
\begin{onlyenv}<overlay specification>
\end{onlyenv}

\color<overlay specification>{color}
\textbf<overlay specification>{text}
\textit<overlay specification>{text}
\textmd<overlay specification>{text}
\textnormal<overlay specification>{text}
\textrm<overlay specification>{text}
\textsc<overlay specification>{text}
\textsf<overlay specification>{text}
\textsl<overlay specification>{text}
\texttt<overlay specification>{text}
\textup<overlay specification>{text}
\hypertarget<overlay specification>{target name}{anchor text%text}
\hyperlink<overlay specification>{target name}{link text%text}
\emph<overlay specification>{text}

\begin{overlayarea}{area width%l}{area height%l}
\end{overlayarea}
\begin{overprint}
\begin{overprint}[area width%l]
\end{overprint}

\transblindshorizontal[options%keyvals]
\transblindshorizontal<overlay specification>[options%keyvals]
\transblindsvertical[options%keyvals]
\transblindsvertical<overlay specification>[options%keyvals]
\transboxin[options%keyvals]
\transboxin<overlay specification>[options%keyvals]
\transboxout[options%keyvals]
\transboxout<overlay specification>[options%keyvals]
\transcover[options%keyvals]
\transcover<overlay specification>[options%keyvals]
\transdissolve[options%keyvals]
\transdissolve<overlay specification>[options%keyvals]
\transfade[options%keyvals]
\transfade<overlay specification>[options%keyvals]
\transglitter[options%keyvals]
\transglitter<overlay specification>[options%keyvals]
\transpush[options%keyvals]
\transpush<overlay specification>[options%keyvals]
\transreplace[options%keyvals]
\transreplace<overlay specification>[options%keyvals]
\transsplitverticalin[options%keyvals]
\transsplitverticalin<overlay specification>[options%keyvals]
\transsplitverticalout[options%keyvals]
\transsplitverticalout<overlay specification>[options%keyvals]
\transsplithorizontalin[options%keyvals]
\transsplithorizontalin<overlay specification>[options%keyvals]
\transsplithorizontalout[options%keyvals]
\transsplithorizontalout<overlay specification>[options%keyvals]
\transuncover[options%keyvals]
\transuncover<overlay specification>[options%keyvals]
\transwipe[options%keyvals]
\transwipe<overlay specification>[options%keyvals]
\transfly[options%keyvals]
\transfly<overlay specification>[options%keyvals]

#keyvals:\transblindshorizontal,\transblindsvertical,\transboxin,\transboxout,\transcover,\transdissolve,\transfade,\transglitter,\transpush,\transreplace,\transsplitverticalin,\transsplitverticalout,\transsplithorizontalin,\transsplithorizontalout,\transuncover,\transwipe,\transfly
direction=%<degrees%>
duration=%<seconds%>
#endkeyvals

\transduration{number of seconds}
\transduration<overlay specification>{number of seconds}

\animate<overlay specification>
\animatevalue<start slide - end slide>{name}{start value}{end value}

\label<overlay specification>{key%labeldef}
