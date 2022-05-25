# mwbk class
# Matthew Bertucci 2022/05/23 for v0.75

#keyvals:\documentclass/mwbk#c
a4paper
a5paper
a6paper
b4paper
b5paper
b6paper
letterpaper
legalpaper
executivepaper
landscape
wide
withmarginpar
withoutmarginpar
10pt
10dd
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
openright
openany
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

\SetSectionFormatting{nazwa polecenia}{odstęp przed}{nagłówek}{odstęp p}
\SetSectionFormatting[flagi%keyvals]{nazwa polecenia}{odstęp przed}{nagłówek}{odstęp p}
\DeclareSectioningCommand{nazwa polecenia}{odstęp przed}#*
\DeclareSectioningCommand[flag%keyvals]{nazwa polecenia}{odstęp przed}#*

#keyvals:\SetSectionFormatting,\DeclareSectioningCommand
runin
breakbefore
breakafter
wholewidth
#endkeyvals

\backmatter
\bibname
\captionsettings#*
\centeredlast#*
\chapter*{title}#L1
\chapter[short title]{title}#L1
\chapter{title}#L1
\chaptermark{code}#*
\chaptername
\figuresettings#*
\FormatBlockHeading{dekl}
\FormatChapterHeading{odstęp}{dekl num}{dekl tyt}
\FormatHangHeading{dekl}
\FormatRigidChapterHeading{wys}{odstęp}{dekl num}{dekl tyt}
\FormatRunInHeading{dekl}
\frontmatter
\HeadingNumber
\HeadingNumberedfalse#*
\HeadingNumberedtrue#*
\HeadingRHeadText
\HeadingText
\HeadingTOCText
\ifHeadingNumbered
\mainmatter
\partmark{code}#*
\secondarysize
\sectsettings#*
\SetTOCIndents{{%<code1%>}{%<code2%>}%<...%>}
\tablesettings#*
\thechapter#*
\titlesettings#*