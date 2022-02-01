# beamerprosper package
# tbraun 11/5/2006
# added commands for beamer emulation package
# Matthew Bertucci updated 2/1/2022 for v3.65

#keyvals:\usepackage/beamerprosper#c
framesassubsections
#endkeyvals

\email{text%plain}
\institution{text}
\Logo{logo text%text}
\Logo(x,y){logo text%text}

\begin{slide}{frame title%text}
\begin{slide}[options%keyvals]{frame title%text}
\end{slide}

#keyvals:\begin{slides},\prosperpart
toc=%<entry%>
trans=#Glitter,R,Replace,Split,Blinds,Box,Wipe,Dissolve
#endkeyvals

#keyvals:\begin{slides},\prosperpart,\PDFtransition
Glitter
R
Replace
Split
Blinds
Box
Wipe
Dissolve
#endkeyvals

\overlays{number}{slide environment%text}
\fromSlide{slide number}{text}
\fromSlide*{slide number}{text}
\onlySlide{slide number}{text}
\onlySlide*{slide number}{text}
\untilSlide{slide number}{text}
\untilSlide*{slide number}{text}
\FromSlide{slide number}
\OnlySlide{slide number}
\UntilSlide{slide number}
\slideCaption{text}
\fontTitle{text}
\fontText{text}
\PDFtransition{prosper transition%keyvals}

\begin{Itemize}\item
\end{Itemize}
\begin{itemstep}\item
\end{itemstep}
\begin{enumstep}\item
\end{enumstep}

\hiddenitem
\prosperpart{text}
\prosperpart[options%keyvals]{text}
\tsection{title}#L2
\tsection*{title}#*L2
\tsectionandpart{title}#L2
\tsectionandpart[options%keyvals]{title}#L2
\tsectionandpart*{title}#*L2
\tsectionandpart*[options%keyvals]{title}#*L2

\dualslide[x][y][z]{options%keyvals}{left column%text}{right column%text}#*
\dualslide[y][z]{options%keyvals}{left column%text}{right column%text}#*
\dualslide[z]{options%keyvals}{left column%text}{right column%text}#*
\dualslide{options%keyvals}{left column%text}{right column%text}

#keyvals:\dualslide
lcolwidth=##L
rcolwidth=##L
#endkeyvals

\PDForPS{PostScript text}{PDF text}
\onlyInPDF{PDF text}
\onlyInPS{PostScript text}

\begin{notes}{title%text}
\end{notes}

# for compatibility only
\myitem#S
\FontTitle#S
\FontText#S
\ColorFoot#S
\DefaultTransition#S
\NoFrenchBabelItemize#S
\TitleSlideNav#S
\NormalSlideNav#S
\HAPsetup#S
\LeftFoot#S
\RightFoot#S
\begin{wideslide}#S
\end{wideslide}#S
