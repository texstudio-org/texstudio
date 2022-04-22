# frontespizio package
# Matthew Bertucci 4/21/2022 for v1.4a

#include:afterpage
#include:graphicx
#include:atbegshi
#include:environ
#include:ifpdf
#include:ifxetex

#keyvals:\usepackage/frontespizio#c
write
nowrite
standard
suftesi
signatures
noadvisor
swapnames
normal
sans
norules
nouppercase
noinputenc
onlyinclude
driver=%<driver%>
#endkeyvals

#ifOption:onlyinclude
\includefront{imagefile}#g
\includefront[numero]{imagefile}#g
#endif

\begin{frontespizio}
\end{frontespizio}
\Universita{nome breve}
\Istituzione{nome completo}
\Logo{imagefile}#g
\Logo[dimen%l]{imagefile}#g
\Filigrana{imagefile}#g
\Filigrana[parametri%keyvals]{imagefile}#g
#keyvals:\Filigrana
height=##L
before=%<numero%>
after=%<numero%>
#endkeyvals
\Facolta{nome breve}
\Dipartimento{nome breve}
\Divisione{nome completo}
\Interfacolta{nomi completi}
\Corso{nome}
\Corso[tipo]{nome}
\Scuola{nome completo}
\Titoletto{tipo}
\Titolo{titolo}
\Sottotitolo{sottotitolo}
\Candidato{nome}
\Candidato[matricola]{nome}
\Relatore{nome}
\Correlatore{nome}
\Annoaccademico{anno}
\Piede{testo}
\NCandidato{nome}
\NCandidati{nome}
\NRelatore{singolare}{plurale}
\NCorrelatore{singolare}{plurale}
\Punteggiatura{carattere}
\Preambolo{comandi}
\begin{Preambolo*}
\end{Preambolo*}
\Rientro{dimen%l}
\Margini{dimen1%l}{dimen2%l}{dimen3%l}{dimen4%l}

\frontinstitutionfont#*
\frontdivisionfont#*
\frontpretitlefont#*
\fronttitlefont#*
\frontsubtitlefont#*
\frontfixednamesfont#*
\frontnamesfont#*
\frontsmallfont#*
\frontfootfont#*
\fronttitlecolor#*
\fontoptionnormal#*
\fontoptionsans#*
\frontadjustforsignatures#*
\frontcandidatesep#*
\frontlogosep#*
\frontrelcorrelsep#*
\preparefrontpage#*
\preparefrontpagestandard#*
\preparefrontpagesuftesi#*

# deprecated
\IlCandidato{nome}#S
\IlCandidato[matricola]{nome}#S
\Package{comandi}#S
\MoreMargin{dimen%l}#S
\Margins{dimen1%l}{dimen2%l}{dimen3%l}{dimen4%l}#S