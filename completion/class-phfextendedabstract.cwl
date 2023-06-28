# phfextendedabstract class
# Matthew Bertucci 2022/05/06 for v1.0

#include:class-revtex4-2
#include:geometry
#include:kvoptions
#include:phfnote
#include:phfthm

# from pkgset=extended option of phfnote
#include:float
#include:verbdef
#include:csquotes
#include:dsfont
#include:bbm
#include:mathtools

#keyvals:\documentclass/phfextendedabstract#c
papertype=%<type%>
ptsize=#10pt,11pt,12pt
sectiondecorations#true,false
paragraphdecorations#true,false
noheadingdecorations
compressverticalspacing=%<factor%>
loadtheorems#true,false
sansstyle#true,false
usehyperref#true,false
pkgset=#none,minimal,rich,extended
#endkeyvals

\section!{title}#L2
\section![short title]{title}#L2
\section<decoration>{title}#L2
\section<decoration>[short title]{title}#L2
\paragraph!{title}#L5
\paragraph![short title]{title}#L5
\paragraph<decoration>{title}#L5
\paragraph<decoration>[short title]{title}#L5

\phfeaSectionDecoration{symbol}
\phfeaParagraphDecoration{symbol}

\phfeaSectionDecorationSymbol#*
\phfeaParagraphDecorationSymbol#*
\phfeaSectionBeforeSkip#*
\phfeaSectionAfterHSkip#*
\phfeaParagraphBeforeSkip#*
\phfeaParagraphAfterHSkip#*
\phfeaSectionStyle#*
\phfeaParagraphStyle#*
\phfeaSectionFormatHeading{text}#*
\phfeaParagraphFormatHeading{text}#*
\phfeaVerticalSpacingCompressionFactor#*
\phfeaDefineTheoremStyle#*
\phfeaDisplayVerticalSpacingFactorWeight#*
\phfeaParskipVerticalSpacingFactorWeight#*

\begin{enumerate*}
\begin{enumerate*}[options%keyvals]
\end{enumerate*}

\phfeaListsVerticalSkip#*
\phfeaListsItemSep#*
\phfeaListsParSep#*
\phfeaHeadingStyle#*
\phfeaTitleStyle#*
