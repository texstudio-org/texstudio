# phfnote package
# Matthew Bertucci 2/8/2022 for v4.0

#include:xkeyval
#include:kvoptions
#include:etoolbox
#include:xcolor
#include:geometry
#include:sectsty
#include:amsmath
#include:amsfonts
#include:amssymb
#include:amsthm
#include:setspace
#include:caption
#include:enumitem
# enumitem loaded with shortlabels option
#include:graphicx
#include:fontenc
# fontenc loaded with T1 option
#include:inputenc
#include:iftex
#include:microtype
#include:hyperref

#keyvals:\usepackage/phfnote#c
preset=#sfnote,sfssnote,opensansnote,utopianote,mnmynote,pkgdoc,xpkgdoc,article,reset
title=#default,pretty,pretty2,small,article
notitle
abstract={%<attributes%>}
noabstract
pkgset=#none,minimal,rich,extended
pagegeom=#default,narrow,wide,xwide,bigmargin
nopagegeom
secfmt=={%<attributes%>}
nosecfmt
par=#indent,skip,indentminiskip
nopar
spacingdefs#true,false
nospacingdefs
fontdefs#true,false
nofontdefs
footnotedefs#true,false
nofootnotedefs
hyperrefdefs={%<options%>}
nohyperrefdefs
bibliographydefs#true,false
nobibliographydefs
#endkeyvals

#ifOption:pkgset=extended
#include:float
#include:verbdef
#include:csquotes
#include:dsfont
#include:bbm
#include:mathtools
#endif

#ifOption:preset=opensansnote
#include:opensans
#endif

#ifOption:preset=utopianote
#include:fourier
#endif

#ifOption:preset=mnmynote
#include:MnSymbol
#include:MinionPro
#include:MyriadPro
#endif

#ifOption:preset=xpkgdoc
#include:tcolorbox
#include:verbdef
\PrintChangesAndIndexSpacing
\PrintChangesAndIndex
phfxpkgdocmacronamehyphencolor#B
\ScaleHorizontallyAndHyphenateAnywhere{arg1}{arg2}#*
\PrintMarginLabelContents{arg}
\PrintMarginLabel{arg}
\pkgname{package}
\pkgnamefmt{text}#*
\thephfnotechanged#*
\changed{version}{date}{description%text}
\changed[label name]{version}{date}{description%text}
\changedreftext{label name}#*
\changedtextfmt{version}{date}{description%text}#*
\begin{pkgoptions}
\end{pkgoptions}
\metatruefalsearg
\pkgoptionfmt{text}#*
\pkgoptionfmt[opt]{text}#*
\handleitemindex{arg}#*
\pkgoptname#*
\packageoptionsname#*
\begin{cmdoptions}
\end{cmdoptions}
\cmdoptname#*
\commandoptionsname#*
\setcmdnotpkgoptions#*
\cmdoptionsfbox{text}#*
\pkgoptattrib{arg}
\pkgoptattribnodots{arg}
\pkgoptattribempty
\begin{pkgnote}
\end{pkgnote}
\begin{pkgwarning}
\end{pkgwarning}
\begin{pkgtip}
\end{pkgtip}
\phfqitltxPkgTitle{package}#*
\pkgfmtdate{date}#*
#endif

\notetitlefont{text}#*
\notetitleauthorfont{text}#*
\notetitledatefont{text}#*
\notetitlebelowspace#*
\notetitlebottomspace#*
\notetitletopspace#*
\notetitlehrule#*
\notetitleinnervsep#*
\notetitlewidth#*
\notetitleparskip#*
\notetitlefontparsetup#*
\notetitleaftertitleskip#*
\notetitleauthorfontparsetup#*
\notetitledatefontparsetup#*
\notetitledonextvskip#*
\notetitlemakecontents#*
\notetitlemakecontentstop#*
\notetitlemakecontentsbottom#*
\notetitlebeginrender#*
\notetitleendrender#*
\notetitleusemainbox{text}#*
\ifnotetitleusempfootnotes#*
\notetitleusempfootnotestrue#*
\notetitleusempfootnotesfalse#*
\singlespace#*

\thanks[number]{text}
\thanksmark[number]

#ifOption:title=pretty
\notetitleprettylsiderulewidth#*
\notetitleprettylsidespacewidth#*
\notetitleprettyrsiderulewidth#*
\notetitleprettyrsidespacewidth#*
\notetitleprettytopspace#*
\notetitleprettybottomspace#*
\notetitleprettytophrulewidth#*
\notetitleprettybottomhrulewidth#*
notetitleprettylsiderulecolor#B
notetitleprettyrsiderulecolor#B
notetitleprettytophrulecolor#B
notetitleprettybottomhrulecolor#B
notetitleprettytextcolor#B
notetitleprettybgcolor#B
#endif

#ifOption:title=pretty2
\notetitleprettylsiderulewidth#*
\notetitleprettylsidespacewidth#*
\notetitleprettyrsiderulewidth#*
\notetitleprettyrsidespacewidth#*
\notetitleprettytopspace#*
\notetitleprettybottomspace#*
\notetitleprettytophrulewidth#*
\notetitleprettybottomhrulewidth#*
notetitleprettylsiderulecolor#B
notetitleprettyrsiderulecolor#B
notetitleprettytophrulecolor#B
notetitleprettybottomhrulecolor#B
notetitleprettytextcolor#B
notetitleprettybgcolor#B
#endif

#ifOption:title=small
\notetitlesmallauthordatesep#*
#endif

\noteabstracttextfont#*
\noteabstractnamefont#*
\noteabstracttextwidth#*
\noteabstractafterspacing#*
\noteabstractbeforespacing#*
\begin{noteabstract}#*
\end{noteabstract}#*
\begin{notedefaultabstract}#S
\end{notedefaultabstract}#S

\notesectionallfont#*
\notesectionallfontfamily#*
\notesectionfont#*
\notesubsectionfont#*
\notesubsubsectionfont#*
\noteparagraphfont#*
\notesubparagraphfont#*
\notesectionsetfonts{sec style}{subsec style}{subsubsec style}#*
\noteparagraphsetfonts{para style}{subpara style}#*

docnotelinkcolor#B

\email{email%URL}#U
\phfnoteEmail{email%URL}#*U
\phfnotePdfLinkColor{color}

\eprint{arxiv ID%URL}#*U
\doibase{arg}#*

\notesmaller
\notesmaller[factor]
\notesmallerfrac#*

\inlinetoc

#keyvals:\urlstyle#c
notett
notesf
notesfss
noteitsf
noterm
noteit
notesml
#endkeyvals

\phfnoteHackSectionStarWithTOC#*
\phfnoteHackSectionStarWithTOCInCommand{cmd}#*

\phfnoteSaveDefs{identifier}{list of macro names}#*
\phfnoteRestoreDefs{identifier}#*

\phfverb{text%definition}
\phfverbfmt{text%definition}#*

# from shortlabels option of enumitem
#keyvals:\begin{enumerate}#c,\begin{itemize}#c,\begin{description}#c,\begin{enumerate*}#c,\begin{itemize*}#c,\begin{description*}#c
A
a
I
i
1
#endkeyvals

# from T1 option of fontenc
\DH#n
\NG#n
\dj#n
\ng#n
\k{arg}#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\quotedblbase#n
\quotesinglbase#n
\textquotedbl#n
\DJ#n
\th#n
\TH#n
\dh#n
\Hwithstroke#*n
\hwithstroke#*n
\textogonekcentered{arg}#*n
\guillemetleft#n
\guillemetright#n