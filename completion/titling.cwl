# titling package
# Matthew Bertucci 11/10/2021 for v2.1d

\pretitle{text}
\pretitle{text}
\posttitle{text}
\preauthor{text}
\postauthor{text}
\predate{text}
\postdate{text}

\droptitle#*
\maketitlehooka#*
\maketitlehookb#*
\maketitlehookc#*
\maketitlehookd#*

\begin{titlingpage}
\end{titlingpage}

\calccentering{length}{margin}

\thetitle
\theauthor
\thedate

\killtitle
\keepthetitle
\emptythanks

\thanksmarkseries{format}#*
\symbolthanksmark#*
\continuousmarks#*
\thanksheadextra{pre%l}{post%l}#*
\thanksfootextra{pre%l}{post%l}#*
\thanksmark{n}#*
\thanksgap#*
\tamark#*
\thanksmarkwidth#*
\thanksmargin#*
\thanksfootmark#*
\thanksfootpre#*
\thanksfootpost#*
\thanksscript{text}#*
\makethanksmarkhook#*
\makethanksmark#*
\thanksrule#*
\usethanksrule#*
\cancelthanksrule#*
\appendiargdef{macro}{code}#*