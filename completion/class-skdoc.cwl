# skdoc class
# Matthew Bertucci 2/19/2022 for v1.5d

#include:class-scrartcl
#include:etoolbox
#include:xstring
#include:atbegshi
#include:kvoptions
#include:pdftexcmds
#include:everyhook
#include:verbatim
#include:needspace
#include:marginnote
#include:calc
#include:hyperref
#include:multicol
#include:hologo
#include:glossaries
#include:ydoc-code
#include:ydoc-desc
#include:scrlayer-scrpage
#include:babel
#include:csquotes
#include:caption
#include:PTSerif
#include:sourcecodepro
#include:opensans
#include:microtype
#include:minted

#keyvals:\documentclass/skdoc#c
load=%<package%>
highlight#true,false
babel=%<babel options%>
#endkeyvals

\package{package}
\package[options%keyvals]{package}

#keyvals:\package
ctan=%<identifier%>
vcs=%<URL%>
#endkeyvals

\version{version}
\ctan{identifier}
\repository{URL}#U
\email{email%URL}#U

\theversion
\thepackage
\thepkg

\PrintLPPL
\Notice{notice%text}
\Warning{warning%text}
\LongWarning{warning%text}

\cs*{csname}
\env*{envname}
\pkg*{package}
\opt*{option}
\bib{BibTeX entry type}
\bib*{BibTeX entry type}
\thm{theme}
\thm*{theme}
\file*{file}

\begin{example}
\end{example}

\Option{option}
\Options{option1,option2,...}
\WithValues{value1,value2,...}
\AndDefault{default value}
\BibEntry{entry}
\WithFields{mandatory fields}
\WithFields[optional fields]{mandatory fields}
\Theme{theme}
\DescribeFile{file}

\begin{macro*}{macro}
\end{macro*}
\begin{environment*}{envname}
\end{environment*}
\begin{option}{option}
\end{option}
\begin{option*}{option}
\end{option*}
\begin{bibentry}{entry}
\end{bibentry}
\begin{bibentry*}{entry}
\end{bibentry*}
\begin{theme}{theme}
\end{theme}
\begin{theme*}{theme}
\end{theme*}

\DeclareFile{file}
\DeclareFile[options%keyvals]{file}

#keyvals:\DeclareFile
key=%<key%>
preamble=%<preamble%>
#endkeyvals

\PreambleTo{token}{file}
\SelfPreambleTo{token}

\begin{MacroCode}
\end{MacroCode}

\Implementation
\Finale
\OnlyDescription
\changes{version}{description}
\PrintChanges
\PrintIndex

# not documented
\LPPL#S
\LPPLdocfile{arg}#S
\LPPLfile{arg}#S
\LPPLicense#S
\LPPLparagraph#S
\LPPLparagraph{arg}#S
\LPPLsection#S
\LPPLsection{arg}#S
\LPPLsubsection#S
\LPPLsubsection{arg}#S
\LPPLsubsubsection#S
\LPPLsubsubsection{arg}#S
\PY#S
\PYZam#S
\PYZat#S
\PYZbs#S
\PYZca#S
\PYZcb#S
\PYZdl#S
\PYZdq#S
\PYZgt#S
\PYZhy#S
\PYZlb#S
\PYZlt#S
\PYZob#S
\PYZpc#S
\PYZrb#S
\PYZsh#S
\PYZsq#S
\PYZti#S
\PYZus#S
\begin{enum}#S
\end{enum}#S
\descframe{arg}#S
\endDescribeEnv#S
\endLPPLicense#S
\generalname#S
\hyperul{arg}#S
\name#S
\oldmakeatletter#S
\skdocpdfsettings#S

# from british option of babel
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