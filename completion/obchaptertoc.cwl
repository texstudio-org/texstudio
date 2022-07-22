# obchaptertoc package
# Matthew Bertucci 2022/07/21 for v2.0

#include:l3keys2e
#include:etoolbox

#keyvals:\usepackage/obchaptertoc#c
level=%<section level%>
#endkeyvals

\chaptertoc
\ifChapterTOCafterskip#*
\ChapterTOCafterskiptrue
\ChapterTOCafterskipfalse
\chaptertocmaxlevel{section level}
\ChapterTOCFormat{commands}
\chaptertocfont#*
\chaptertocsecfont#*
\TOCFormatsameas{section-level1}{section-level2}{properties}

\thetocmarker#*
\normalchangetocdepth#*
\afterchaptertocskip#*
\theobchaptocmaxdepth#*