# dccpaper-base package
# Matthew Bertucci 3/25/2022 for v2.3

#include:babel
# loads british option of babel
#include:etoolbox
#include:xpatch
#include:iftex
#include:fontenc
# loads T1 option of fontenc
#include:baskervillef
#include:newtxmath
#include:GoSans
#include:graphicx
#include:xcolor
#include:calc
#include:ifpdf
#include:atbegshi
#include:titlesec
#include:array
#include:booktabs
#include:caption
#include:footmisc
#include:hyperref
#include:hyperxmp

\accepted{date}
\affil{name}
\Affilfont#*
\affilsep#*
\afterabstract#*
\authblksep#*
\Authfont#*
\AuthorBlock#*
\BBA#*
\begin{widequote}#*
\conference{name of conference}
\correspondence{%<name,postal address,%> Email: \email{%<email address%>}}
\doi{DOI}
\email{email address%URL}#U
\end{widequote}#*
\fixspaces#*
\FixTextHeight#*
\flushleftright#*
\HeadTitle#*
\issue{number}
\MainAuthor#*
\nofixspaces#*
\NormalFoot#*
\NormalHead#*
\oldBBA#S
\OrigLineBreak#*
\OtherMainAuthors#*
\ProperTitle#*
\RaggedParindent#*
\raggedyright#*
\raggedyright[length]#*
\received{date}
\revised{date}
\submitted{date}
\subno{number}
\theauthors#*
\theauthorsinblock#*
\theblock#*
\thecorrespondence#*
\thedoi#*
\theissue#*
\thelastpage#*
\thesectionpars#*
\thesubno#*
\thevolume#*
\title[name%text]{full version%text}
\title{full version%text}
\TitleFoot#*
\TitleHead#*
\Version#S
\volume{number}

struct#B
links#B

# from british option of babel
\captionsbritish#*
\datebritish#*
\extrasbritish#*
\noextrasbritish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*

# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n