# amsbkrev class
# Matthew Bertucci 2022/08/19 for v2.37

#include:class-amsart

# options passed to amsart class
#keyvals:\documentclass/amsbkrev#c
10pt
11pt
12pt
8pt
9pt
a4paper
centertags
draft
e-only
final
fleqn
landscape
leqno
letterpaper
noamsfonts
nomath
notitlepage
onecolumn
oneside
portrait
reqno
tbtags
titlepage
twocolumn
twoside
#endkeyvals

\begin{bookinfo}
\end{bookinfo}
\begin{review}
\end{review}
\begin{revinfo}
\end{revinfo}

\reviewer{name}
\publisher{name}
\publaddr{address%text}
\yr{year}
\pages{pages}
\binding{hardcover|softcover}
\price{price}
\isbn{ISBN}
\revtransl{review translator}
\msc{msc}#*
\editor{name}
\bktransl{book translator}
\bkcontrib{name}
\bkcontrib[prefix text%text]{name}
\edition{edition}
\series{series}
\serieseditor{name}
\volume{volume}
\journal{journal}
\cmheight{number}#*
\note{text}
\lang{language}

# not documented
\altpages{pages}#*
\brtitle#*
\cpubl#S
\ctitle#S
\ednote{text}#*
\loosen#*
\num{arg}#*
\originfo{arg1}{arg2}{arg3}{arg4}#S
\Review#*
\reviewersep#*
\Reviews#*
\reviewsep#*
\subtitle{text}#*
\theauthor#*
\thebookinfo#*
\therevcount#*
\tocauthors#*
\tocbkcontribs#*