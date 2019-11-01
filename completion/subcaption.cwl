# subcaption package
# Axel Sommerfeldt 04/16/2013
# muzimuzhi/1 Sep 2019, subcaption v1.2
# muzimuzhi/1 Nov 2019, subcaption v1.3
# URL: https://ctan.org/pkg/subcaption

#include:caption

\subcaptionbox[list entry]{heading}[width][inner pos]{contents}
\subcaptionbox&]*[list entry]{heading}[width][inner pos]{contents}

\begin{subfigure}[position][height][inner pos]{width}
\begin{subfigure}[position][height]{width}
\begin{subfigure}[position]{width}
\begin{subfigure}{width}
\begin{subtable}[position][height][inner pos]{width}
\begin{subtable}[position][height]{width}
\begin{subtable}[position]{width}
\begin{subtable}{width}
\end{subfigure}
\end{subtable}

\subcaption{heading}
\subcaption[list entry]{heading}
\subcaption*{heading}
\subcaption*[list entry]{heading}
\DeclareCaptionSubType[numbering scheme]{type}
\DeclareCaptionSubType*[numbering scheme]{type}

\subref{key}#r
\subref*{key}#r
\thesubfigure
\thesubtable

\phantomsubcaption

\subfloat[list entry][sub-caption]{body}
\subfloat[sub-caption]{body}
\subfloat{body}
