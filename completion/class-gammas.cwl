# gammas class
# Matthew Bertucci 4/11/2022 for v1.1

#include:class-scrartcl
#include:inputenc
#include:fontenc
#include:lmodern
#include:fourier
#include:babel
# loads english option of babel
#include:microtype
#include:anyfontsize
#include:amssymb
#include:amsmath
#include:amsthm
#include:mathtools
#include:mathrsfs
#include:subdepth
#include:graphicx
#include:xcolor
#include:tikz
#include:pgfplots
#include:geometry
#include:scrlayer-scrpage
#include:booktabs
#include:enumitem
#include:caption
#include:siunitx
#include:lineno
#include:listings
#include:ifthen
#include:hyperref
#include:cleveref
#include:csquotes
#include:biblatex

#keyvals:\documentclass/gammas#c
usebiber
usebibtex
#endkeyvals

#ifOption:usebibtex
#include:natbib
#endif

\gammtitle{text}
\gammauthora{name}
\gammauthorb{name}
\gammauthorc{name}
\gammauthord{name}
\gammauthore{name}
\gammauthorf{name}
\gammauthoraorcid{ORCID}
\gammauthorborcid{ORCID}
\gammauthorcorcid{ORCID}
\gammauthordorcid{ORCID}
\gammauthoreorcid{ORCID}
\gammauthorforcid{ORCID}
\gammaddressa{address}
\gammaddressb{address}
\gammaddressc{address}
\gammaddressd{address}
\gammaddresse{address}
\gammaddressf{address}
\inst{supscript}
\corauth
\gammauthorhead{text}
\gammcorrespondence{email%URL}#U
\gammsupervisor{name}
\gammbibfilename{bib file}
\begin{gammabstract}
\end{gammabstract}
\begin{gammkeywords}
\end{gammkeywords}
\begin{gammacode}
\end{gammacode}
\begin{gammacknowledgement}
\end{gammacknowledgement}
\gammotherpublication{publication}
\orcid{ORCID}

\gammasHeader#*
\gammbiberopt{true|false}#*
\gammfinalmode{arg}#*
\gammloadoptbiber{true|false}#*
\gammloadoptbibtex{true|false}#*
\gammtwocolumnmode{arg}#*
\makegammhead#*
\patchAmsMathEnvironmentForLineno{envname}#*
\patchBothAmsMathEnvironmentsForLineno{envname}#*
\setbiber{bib file}#*
\setbib{bib file}#*
\GAMMAUTHORA#*
\GAMMAUTHORB#*
\GAMMAUTHORC#*
\GAMMAUTHORD#*
\GAMMAUTHORE#*
\GAMMAUTHORF#*
\GAMMAUTHORAORCID#*
\GAMMAUTHORBORCID#*
\GAMMAUTHORCORCID#*
\GAMMAUTHORDORCID#*
\GAMMAUTHOREORCID#*
\GAMMAUTHORFORCID#*
\GAMMADDRESSA#*
\GAMMADDRESSB#*
\GAMMADDRESSC#*
\GAMMADDRESSD#*
\GAMMADDRESSE#*
\GAMMADDRESSF#*
\GAMMAUTHORHEAD#*
\GAMMCORRESPONDENCE#*
\GAMMSUPERVISOR#*
\GAMMSUPERVISORTEXT#*
\GAMMOTHERPUBLICATION#*
\GAMMBIBFILENAME#*
\GAMMLOADOPTBIBER#*
\GAMMBIBEROPT#*
\GAMMLOADOPTBIBTEX#*
\GAMMFINALMODE#*
\GAMMTWOCOLUMNMODE#*

GAMMgreen#B
lstbackground#B
lstcommand#B

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

# from english option of babel
\captionsenglish#*
\dateenglish#*
\extrasenglish#*
\noextrasenglish#*
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