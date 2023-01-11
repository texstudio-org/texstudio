# nccsect package
# Matthew Bertucci 2/3/2022 for v1.6

#include:afterpackage

\startpart{level}{title}#L0
\startpart{level}[short title]{title}#L0
\startpart{level}*{title}#L0

\startchapter{level}{title}#L1
\startchapter{level}[short title]{title}#L1
\startchapter{level}*{title}#L1

\startsection{level}{title}#L2
\startsection{level}[short title]{title}#L2
\startsection{level}*{title}#L2

\startsubsection{level}{title}#L3
\startsubsection{level}[short title]{title}#L3
\startsubsection{level}*{title}#L3

\startsubsubsection{level}{title}#L4
\startsubsubsection{level}[short title]{title}#L4
\startsubsubsection{level}*{title}#L4

\startparagraph{level}{title}#L5
\startparagraph{level}[short title]{title}#L5
\startparagraph{level}*{title}#L5

\startsubparagraph{level}{title}#L6
\startsubparagraph{level}[short title]{title}#L6
\startsubparagraph{level}*{title}#L6

\sectionstyle{style%keyvals}
\sectionstyle[type]{style%keyvals}

#keyvals:\sectionstyle#c
hangindent
hangindent*
parindent
parindent*
hangparindent
hangparindent*
center
centerlast
%sectionstyle
#endkeyvals

\sectiontagsuffix{suffix}
\sectiontagsuffix[type]{suffix}
\indentaftersection
\noindentaftersection
\aftersectionvspace{space%l}
\adjustsectionmargins{left skip%l}{right skip%l}

\norunninghead
\runninghead{running title%text}
\noheadingtag
\headingtag{tag}
\headingtag*{tag}
\skipwritingtoaux

\caption*{text}

\captionstyle{style%keyvals}
\captionstyle[type]{style%keyvals}

#keyvals:\captionstyle#c
default
para
left
center
right
centerlast
#endkeyvals

\captiontagstyle{style%keyvals}
\captiontagstyle[type]{style%keyvals}

#keyvals:\captiontagstyle#c
para
left
center
right
#endkeyvals

\captiontagsuffix{suffix}
\captiontagsuffix[type]{suffix}
\captionwidth{width}
\captionwidth[type]{width}

\SetTOCStyle{declarations}
\ChapterPrefixStyle{appearance list}

\newplainsectionstyle{name%specialDef}{indent}{left skip%l}{right skip%l}#s#%sectionstyle
\newplainsectionstyle{name%specialDef}{indent}[pos]{left skip%l}{right skip%l}#s#%sectionstyle
\newhangsectionstyle{name%specialDef}{min tag width%l}{left skip%l}{right skip%l}#s#%sectionstyle
\newhangsectionstyle{name%specialDef}{min tag width%l}[pos]{left skip%l}{right skip%l}#s#%sectionstyle

\DeclareSection{level}{type}{prefix}{beforeskip%l}{afterskip%l}{style}
\DeclareSection{level}{type}[indent%l]{prefix}{beforeskip%l}{afterskip%l}{style}
\DeclareSection*{level}{type}{prefix}{beforeskip%l}{afterskip%l}{style}
\bff

\SectionTagSuffix{suffix}
\RunningSectionSuffix{suffix}
\norunningsuffix
\CaptionTagSuffix{suffix}

\DeclareTOCEntry{level}{action}{prefix}{prototype}{style}
\DeclareTOCEntry{level}{action}{prefix}{prototype}{style}[next]
\applystyle{text style}{number style}

\NumberlineSuffix{calc suffix}{actual suffix}
\PnumPrototype{prototype}
\TOCMarginDrift{increment%l}

\runinsectionskip

\RegisterFloatType{float type}

\beforechapter{code}
\epigraph{text}{author}
\epigraph[width]{text}{author}
\epigraphparameters{style}{width}{height}{author style}{after code}
\epigraphwidth

\StartFromTextArea
\StartFromHeaderArea

\DeclarePart{before}{after}{prefix}{style}
\DeclareTOCPart{action}{prefix}{prototype}{style}
\DeclareTOCPart{action}[afterskip%l]{prefix}{prototype}{style}

\partmark{text}#*