# minted tcolorboxlibrary
# 2025/05/20 for v6.5.0

#include:minted
# loads processing and listingscore tcolorbox libraries

#keyvals:\tcbset,\begin{tcblisting},\tcbinputlisting,\newtcblisting,\renewtcblisting,\newtcbinputlisting,\renewtcbinputlisting,\DeclareTCBListing,\NewTCBListing,\RenewTCBListing,\ProvideTCBListing,\DeclareTCBInputListing,\NewTCBInputListing,\RenewTCBInputListing,\ProvideTCBInputListing
minted language=%<programming lang%>
minted options={%<minted options%>}
default minted options={%<minted options%>}
minted style=%<style%>
#endkeyvals

# from listingscore tcolorbox library
\begin{tcblisting}{options%keyvals}#V
\end{tcblisting}
\begin{tcboutputlisting}#V
\end{tcboutputlisting}
\tcbinputlisting{options%keyvals}
\tcbuselistingtext
\tcbuselistinglisting
\tcbusetemplisting
\newtcblisting{envname}{options%keyvals}#N
\newtcblisting{envname}[args]{options%keyvals}#N
\newtcblisting{envname}[args][default]{options%keyvals}#N
\newtcblisting[init options%keyvals]{envname}{options%keyvals}#N
\newtcblisting[init options%keyvals]{envname}[args]{options%keyvals}#*N
\newtcblisting[init options%keyvals]{envname}[args][default]{options%keyvals}#*N
\renewtcblisting{envname}{options%keyvals}
\renewtcblisting{envname}[args]{options%keyvals}
\renewtcblisting{envname}[args][default]{options%keyvals}
\renewtcblisting[init options%keyvals]{envname}{options%keyvals}
\renewtcblisting[init options%keyvals]{envname}[args]{options%keyvals}#*
\renewtcblisting[init options%keyvals]{envname}[args][default]{options%keyvals}#*
\DeclareTCBListing{envname}{xargs}{options%keyvals}#N
\DeclareTCBListing[init options%keyvals]{envname}{xargs}{options%keyvals}#N
\NewTCBListing{envname}{xargs}{options%keyvals}#N
\NewTCBListing[init options%keyvals]{envname}{xargs}{options%keyvals}#N
\RenewTCBListing{envname}{xargs}{options%keyvals}
\RenewTCBListing[init options%keyvals]{envname}{xargs}{options%keyvals}
\ProvideTCBListing{envname}{xargs}{options%keyvals}#N
\ProvideTCBListing[init options%keyvals]{envname}{xargs}{options%keyvals}#N
\newtcbinputlisting{cmd}{options%keyvals}#d
\newtcbinputlisting{cmd}[args]{options%keyvals}#d
\newtcbinputlisting{cmd}[args][default]{options%keyvals}#d
\newtcbinputlisting[init options%keyvals]{cmd}{options%keyvals}#d
\newtcbinputlisting[init options%keyvals]{cmd}[args]{options%keyvals}#*d
\newtcbinputlisting[init options%keyvals]{cmd}[args][default]{options%keyvals}#*d
\renewtcbinputlisting{cmd}{options%keyvals}
\renewtcbinputlisting{cmd}[args]{options%keyvals}
\renewtcbinputlisting{cmd}[args][default]{options%keyvals}
\renewtcbinputlisting[init options%keyvals]{cmd}{options%keyvals}
\renewtcbinputlisting[init options%keyvals]{cmd}[args]{options%keyvals}#*
\renewtcbinputlisting[init options%keyvals]{cmd}[args][default]{options%keyvals}#*
\DeclareTCBInputListing{cmd}{xargs}{options%keyvals}#d
\DeclareTCBInputListing[init options%keyvals]{cmd}{xargs}{options%keyvals}#d
\NewTCBInputListing{cmd}{xargs}{options%keyvals}#d
\NewTCBInputListing[init options%keyvals]{cmd}{xargs}{options%keyvals}#d
\RenewTCBInputListing{cmd}{xargs}{options%keyvals}
\RenewTCBInputListing[init options%keyvals]{cmd}{xargs}{options%keyvals}
\ProvideTCBInputListing{cmd}{xargs}{options%keyvals}#d
\ProvideTCBInputListing[init options%keyvals]{cmd}{xargs}{options%keyvals}#d
\thetcblisting#*

#keyvals:\tcbset,\begin{tcblisting},\tcbinputlisting,\newtcblisting,\renewtcblisting,\newtcbinputlisting,\renewtcbinputlisting,\DeclareTCBListing,\NewTCBListing,\RenewTCBListing,\ProvideTCBListing,\DeclareTCBInputListing,\NewTCBInputListing,\RenewTCBInputListing,\ProvideTCBInputListing
listing engine=#listings,minted
listing file=%<file name%>
listing and text
text and listing
listing only
text only
comment=%<text%>
comment only
image comment={%<graphics options%>}{%<file%>}
tcbimage comment=%<file name%>
pdf comment
pdf comment=%<file name%>
pdf extension=%<extension%>
comment style={%<options%>}
listing and comment
comment and listing
listing side text
text side listing
listing outside text
text outside listing
listing side comment
comment side listing
listing outside comment
comment outside listing
listing above text
listing above* text
text above listing
text above* listing
listing above comment
listing above* comment
comment above listing
comment above* listing
no process
process code={%<code%>}
run system command=%<system command%>
compilable listing
run pdflatex=%<arguments%>
run pdflatex
run pdflatex-dev=%<arguments%>
run pdflatex-dev
run xelatex=%<arguments%>
run xelatex
run xelatex-dev=%<arguments%>
run xelatex-dev
run lualatex=%<arguments%>
run lualatex
run lualatex-dev=%<arguments%>
run lualatex-dev
run makeindex=%<arguments%>
run makeindex
run bibtex=%<arguments%>
run bibtex
run biber=%<arguments%>
run biber
run arara=%<arguments%>
run arara
run latexmk=%<arguments%>
run latexmk
run latex=%<arguments%>
run latex
run latex-dev=%<arguments%>
run latex-dev
run dvips=%<arguments%>
run dvips
run ps2pdf=%<arguments%>
run ps2pdf
freeze file=%<file%>
freeze none
freeze extension=%<text%>
freeze pdf
freeze png
freeze jpg
#endkeyvals

# from processing tcolorbox library
\tcbiffileprocess{condition}{source}{md5-file}{target}{true}{false}#*
