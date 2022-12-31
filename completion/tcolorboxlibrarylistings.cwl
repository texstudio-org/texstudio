# listings tcolorboxlibrary
# 2022/12/12 for v5.1.1

#include:listings
# loads processing and listingscore tcolorbox libraries

#keyvals:\tcbset,\begin{tcblisting},\tcbinputlisting,\newtcblisting,\renewtcblisting,\newtcbinputlisting,\renewtcbinputlisting,\DeclareTCBListing,\NewTCBListing,\RenewTCBListing,\ProvideTCBListing,\DeclareTCBInputListing,\NewTCBInputListing,\RenewTCBInputListing,\ProvideTCBInputListing
listing options={%<listings options%>}
no listing options
listing style=%<style%>
listing inputencoding=%<encoding%>
listing remove caption#true,false
every listing line=%<text%>
every listing line*=%<text%>
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
\newtcblisting[init options]{envname}[args][default]{options%keyvals}#N
\renewtcblisting{envname}{options%keyvals}#N
\renewtcblisting[init options]{envname}[args][default]{options%keyvals}#N
\DeclareTCBListing{envname}{xargs}{options%keyvals}#N
\DeclareTCBListing[init options]{envname}{xargs}{options%keyvals}#*N
\NewTCBListing{envname}{xargs}{options%keyvals}#N
\NewTCBListing[init options]{envname}{xargs}{options%keyvals}#*N
\RenewTCBListing{envname}{xargs}{options%keyvals}#N
\RenewTCBListing[init options]{envname}{xargs}{options%keyvals}#*N
\ProvideTCBListing{envname}{xargs}{options%keyvals}#N
\ProvideTCBListing[init options]{envname}{xargs}{options%keyvals}#*N
\newtcbinputlisting{cmd}{options%keyvals}#d
\newtcbinputlisting[init options]{cmd}[args][default]{options%keyvals}#d
\renewtcbinputlisting{cmd}{options%keyvals}#d
\renewtcbinputlisting[init options]{cmd}[args][default]{options%keyvals}#d
\DeclareTCBInputListing{cmd}{xargs}{options%keyvals}#d
\DeclareTCBInputListing[init options]{cmd}{xargs}{options%keyvals}#*d
\NewTCBInputListing{cmd}{xargs}{options%keyvals}#d
\NewTCBInputListing[init options]{cmd}{xargs}{options%keyvals}#*d
\RenewTCBInputListing{cmd}{xargs}{options%keyvals}#d
\RenewTCBInputListing[init options]{cmd}{xargs}{options%keyvals}#*d
\ProvideTCBInputListing{cmd}{xargs}{options%keyvals}#d
\ProvideTCBInputListing[init options]{cmd}{xargs}{options%keyvals}#*d
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
run xelatex=%<arguments%>
run xelatex
run lualatex=%<arguments%>
run lualatex
run makeindex=%<arguments%>
run makeindex
run bibtex=%<arguments%>
run bibtex
run biber=%<arguments%>
run biber
run arara=%<arguments%>
run arara
run latex=%<arguments%>
run latex
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
#include:pdftexcmds
#include:shellesc
\tcbprocmdfivesum#S
\tcbiffileprocess{condition}{source}{md5-file}{target}{true}{false}#*