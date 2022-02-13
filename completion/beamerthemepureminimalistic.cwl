# pureminimalistic beamertheme
# Matthew Bertucci 2/10/2022 for v2.0.0

#keyvals:\usetheme/pureminimalistic#c
darkmode
showmaxslides
nofooterlogo
nofooter
customfont
noto
#endkeyvals

# from pureminimalistic colortheme
#include:ifthen
\beamertitlecolor#*
\beamertextcolor#*
\beamerbgcolor#*
\beamerfootertextcolor#*

# from pureminimalistic innertheme
\itemsymbol#*
\svitem#*
\begin{vfilleditems}
\begin{vfilleditems}<overlay specification>
\end{vfilleditems}
\olditem#S

# from pureminimalistic outertheme
#include:etoolbox
#include:calc
\headerpath#*
\institutepath#*
\logoheader
\logotitle
\logofooter
\pageword#*
\showpagenum#*
\myleftmargin#*
\myrightmargin#*
\mytextlength#*
\myfooterheight#*
\basicfooter{height}{content%text}#*

# from pureminimalistic fonttheme
#include:silence
#include:fontenc
# fontenc loaded with T1 option
#ifOption:noto
#include:noto
#endif
#include:FiraSans
#include:FiraMono
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