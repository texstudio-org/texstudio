# beilstein class
# Matthew Bertucci 4/8/2022 for v2.1

#include:xkeyval
#include:ifthen
#include:babel
# loads american option of babel
#include:inputenc
#include:fontenc
# loads T1 option of fontenc
#include:textcomp
#include:tgheros
#include:amsmath
#include:amssymb
#include:newtxtext
#include:newtxtt
#include:newtxmath
#include:geometry
#include:setspace
#include:ragged2e
#include:lineno
#include:multicol
#include:float
#include:flafter
#include:graphicx
#include:array
#include:tabularx
#include:longtable
#include:etoolbox
#include:cleveref
#include:natbib
#include:url

#keyvals:\documentclass/beilstein#c
manuscript=#bookreport,commentary,fullresearchpaper,letter,review,suppinfo
american
british
latin1
utf8
applemac
sectionnumbering#true,false
fnpara#true,false
#endkeyvals

#ifOption:british
\captionsbritish#*
\datebritish#*
\extrasbritish#*
\noextrasbritish#*
#endif

\title[si title%text]{text}
\sititle{si title%text}
\author[affil number]{name}
\author[affil number][email%URL]{name}#U
\author*{name}{email%URL}#U
\author*[affil number]{name}{email%URL}#U
\affiliation{address}
\keywords{keyword1;keyword2;...}
\begin{acknowledgements}
\end{acknowledgements}
\begin{funding}
\end{funding}
\begin{suppinfo}
\end{suppinfo}
\sifile{file}{format}{short desc%text}
\sifile[long desc%text]{file}{format}{short desc%text}
\begin{scheme}
\end{scheme}
\sglcolfigure{imagefile}#g
\sglcolscheme{imagefile}#g
\begin{sglcoltabular}{cols}#\tabular
\end{sglcoltabular}
\begin{sglcoltabularx}{cols}#\tabular
\end{sglcoltabularx}
\dblcolfigure{imagefile}#g
\dblcolscheme{imagefile}#g
\begin{dblcoltabular}{cols}#\tabular
\end{dblcoltabular}
\begin{dblcoltabularx}{cols}#\tabular
\end{dblcoltabularx}
\fnpara
\fnnormal
\chem{formula}
\unit{unit%formula}
\CN{text}
\IUPAC{chemical compound}
\|

# not documented
\BreakHyph#*
\DoIUPAC{arg}#*
\FloatBarrier#*
\MultiBreak#*
\Prep#*
\Updelta#*m
\Upgamma#*m
\Uplambda#*m
\Upomega#*m
\Upphi#*m
\Uppi#*m
\Uppsi#*m
\Upsigma#*m
\Uptheta#*m
\Upupsilon#*m
\Upxi#*m
\affiliations#*
\allowhyphens#*
\angstrom#*
\authors#*
\authorsep#*
\background#*
\begin{widetext}#*
\end{widetext}#*
\beilstein#*
\celsius#*
\conclusion#*
\degree#*
\emails#*
\emailsep#*
\errorfootnote{arg1}{arg2}#*
\firstoptarg#*
\floatcites#*
\fudgefactor#*
\longtablefootnote#*
\makefootnoteparagraph#*
\makehboxofhboxes#*
\mpmakefootnoteparagraph#*
\mynobreakdash#*
\oneORnone#*
\patchAmsMathEnvironmentForLineno{arg1}#*
\patchAmsMathEnvironmentForOnecolumn{arg1}#*
\patchBothAmsMathEnvironmentsForLineno{arg1}#*
\patchBothAmsMathEnvironmentsForOnecolumn{arg1}#*
\percent#*
\permil#*
\removehboxes#*
\results#*
\setdisplaywidth#*
\testbx#*
\testfnpara#*
\themyfootnote#*
\thesuppinfo#*

# from american option of babel
\captionsamerican#*
\dateamerican#*
\extrasamerican#*
\noextrasamerican#*
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
