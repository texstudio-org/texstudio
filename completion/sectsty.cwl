# sectsty package
# Matthew Bertucci 1/4/2022 for v2.0.2

#keyvals:\usepackage/sectsty#c
garrulous
chatty
taciturn
yorkshire
#endkeyvals

\allsectionsfont{commands}
\partfont{commands}
\chapterfont{commands}
\sectionfont{commands}
\subsectionfont{commands}
\subsubsectionfont{commands}
\paragraphfont{commands}
\subparagraphfont{commands}
\minisecfont{commands}
\partnumberfont{commands}
\parttitlefont{commands}
\chapternumberfont{commands}
\chaptertitlefont{commands}

\nohang
\ulemheading{ulem command}
\sectionrule{raise top%l}{top rule%l}{raise bottom%l}{bottom rule%l}

\SSifnumberpart{true}{false}#*
\SSiftitlepart{true}{false}#*
\SSsectlevel#*
\chapterformat#*
\ifcentering{true}{false}#*
\ifraggedleft{true}{false}#*