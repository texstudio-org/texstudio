# flashcards class
# Matthew Bertucci 2022/07/21 for v1.0.2

#include:ifthen
#include:geometry

#keyvals:\documentclass/flashcards#c
dvips
grid
frame
fronts
backs
avery5371
avery5388
#endkeyvals

\begin{flashcard}{title}
\begin{flashcard}[heading%text]{title}
\end{flashcard}

\cardfrontstyle{style%keyvals}
\cardfrontstyle[font commands]{style%keyvals}

#keyvals:\cardfrontstyle#c
empty
plain
headings
#endkeyvals

\cardfrontfoot{text}

\cardbackstyle{style%keyvals}
\cardbackstyle[font commands]{style%keyvals}

#keyvals:\cardbackstyle#c
empty
plain
#endkeyvals

\cardfrontheadstyle{style%keyvals}
\cardfrontheadstyle[font commands]{style%keyvals}
\cardfrontfootstyle{style%keyvals}
\cardfrontfootstyle[font commands]{style%keyvals}

#keyvals:\cardfrontheadstyle#c,\cardfrontfootstyle#c
left
center
right
#endkeyvals

\cardheight#L
\cardwidth#L
\topoffset#L
\oddoffset#L
\evenoffset#L
\oddevenshift#L
\cardmargin#L
\cardinnerheight#L
\cardinnerwidth#L

# from avery5388.cfg (or avery5371.cfg)
\cardpapermode#*
\cardpaper#*
\cardrows#*
\cardcolumns#*