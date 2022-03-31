# lni class
# Matthew Bertucci 3/29/2022 for v1.7

#include:iftex
#include:cmap
#include:inputenc
#include:fontenc
# loads T1 option of fontenc
#include:textcomp
#include:babel
# loads english and ngerman options of babel
#include:newtxtext
#include:newtxmath
#include:newtxtt
#include:microtype
#include:ccicons
#include:etoolbox
#include:geometry
#include:csquotes
#include:graphicx
#include:eso-pic
#include:grffile
#include:fancyhdr
#include:listings
#include:caption
#include:verbatim
#include:url
#include:xspace
#include:hyperref
#include:cleveref
#include:hypcap

#keyvals:\documentclass/lni#c
latin1
utf8
ansinew
english
nohyperref
nocleveref
biblatex
crop
oldfonts
norunningheads
# options passed to article class
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

#ifOption:oldfonts
#include:mathptmx
#endif

#ifOption:crop
#include:crop
#endif

#ifOption:biblatex
#include:biblatex
# loads natbib=true option of biblatex
\citet[prenote][postnote]{bibid}#C
\citet[postnote]{bibid}#C
\citet{bibid}#C
\citet*[prenote][postnote]{bibid}#C
\citet*[postnote]{bibid}#C
\citet*{bibid}#C
\citep[prenote][postnote]{bibid}#C
\citep[postnote]{bibid}#C
\citep{bibid}#C
\citep*[prenote][postnote]{bibid}#C
\citep*[postnote]{bibid}#C
\citep*{bibid}#C
\citealt[prenote][postnote]{bibid}#C
\citealt[postnote]{bibid}#C
\citealt{bibid}#C
\citealt*[prenote][postnote]{bibid}#C
\citealt*[postnote]{bibid}#C
\citealt*{bibid}#C
\citealp[prenote][postnote]{bibid}#C
\citealp[postnote]{bibid}#C
\citealp{bibid}#C
\citealp*[prenote][postnote]{bibid}#C
\citealp*[postnote]{bibid}#C
\citealp*{bibid}#C
\citeauthor[prenote][postnote]{bibid}#C
\citeauthor[postnote]{bibid}#C
\citeauthor{bibid}#C
\citeauthor*[prenote][postnote]{bibid}#C
\citeauthor*[postnote]{bibid}#C
\citeauthor*{bibid}#C
\citeyearpar[prenote][postnote]{bibid}#C
\citeyearpar[postnote]{bibid}#C
\citeyearpar{bibid}#C
\Citet[prenote][postnote]{bibid}#C
\Citet[postnote]{bibid}#C
\Citet{bibid}#C
\Citet*[prenote][postnote]{bibid}#C
\Citet*[postnote]{bibid}#C
\Citet*{bibid}#C
\Citep[prenote][postnote]{bibid}#C
\Citep[postnote]{bibid}#C
\Citep{bibid}#C
\Citep*[prenote][postnote]{bibid}#C
\Citep*[postnote]{bibid}#C
\Citep*{bibid}#C
\Citealt[prenote][postnote]{bibid}#C
\Citealt[postnote]{bibid}#C
\Citealt{bibid}#C
\Citealt*[prenote][postnote]{bibid}#C
\Citealt*[postnote]{bibid}#C
\Citealt*{bibid}#C
\Citealp[prenote][postnote]{bibid}#C
\Citealp[postnote]{bibid}#C
\Citealp{bibid}#C
\Citealp*[prenote][postnote]{bibid}#C
\Citealp*[postnote]{bibid}#C
\Citealp*{bibid}#C
\citefullauthor[prenote][postnote]{bibid}#C
\citefullauthor[postnote]{bibid}#C
\citefullauthor{bibid}#C
\Citefullauthor[prenote][postnote]{bibid}#C
\Citefullauthor[postnote]{bibid}#C
\Citefullauthor{bibid}#C
\citetext{text}
\defcitealias{bibid}{alias}
\citetalias{bibid}
\citepalias{bibid}
#endif

\andname#*
\authorrunning{text}
\autofontsfalse#S
\autofontstrue#S
\begin{keywords}
\end{keywords}
\booksubtitle{subtitle%text}
\booktitle[short title%text]{title%text}
\booktitle{title%text}
\BPEL
\BPM
\BPMN
\cf
\cropfalse#S
\croptrue#S
\doihoffset#*
\doivoffset#*
\editor{%<name(s)%>}
\eg
\email{email address%URL}#U
\etal
\fnindent#*
\ie
\ifautofonts#S
\ifcrop#S
\ifkeywords#S
\iflnienglish#S
\ifnofonts#S
\ifnorunningheads#S
\ifoldfonts#S
\ifusebiblatex#S
\ifusecleveref#S
\ifusehyperref#S
\keywordsfalse#S
\keywordstrue#S
\lniabbrv{cmd}{abbrv}#*d
\lnidoi{DOI}
\lnienglishfalse#S
\lnienglishtrue#S
\lniinitialism{cmd}{text%plain}#d
\nofontsfalse#S
\nofontstrue#S
\norunningheadsfalse#S
\norunningheadstrue#S
\oldfontsfalse#S
\oldfontstrue#S
\oldsmall#S
\OMG
\powerset#m
\startpage{number}
\subtitle{text}
\thisbottomragged#*
\title[short title%text]{text}
\UML
\usebiblatexfalse#S
\usebiblatextrue#S
\useclevereffalse#S
\useclevereftrue#S
\usehyperreffalse#S
\usehyperreftrue#S
\yearofpublication{year}

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

# from ngerman option of babel
\captionsngerman#*
\datengerman#*
\extrasngerman#*
\noextrasngerman#*
\dq
\ntosstrue#*
\ntossfalse#*
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
\mdqon#*
\mdqoff#*
#repl:"a ä
#repl:"e ë
#repl:"i ï
#repl:"o ö
#repl:"u ü
#repl:"A Ä
#repl:"E Ë
#repl:"I Ï
#repl:"O Ö
#repl:"U Ü
#repl:"s ß
#repl:"z ß
#repl:"S SS
#repl:"Z SZ
#repl:"|
#repl:"= -
#repl:"~ -
#repl:""
#repl:"/ /
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »

# from english option of babel
\captionsenglish#*
\dateenglish#*
\extrasenglish#*
\noextrasenglish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
