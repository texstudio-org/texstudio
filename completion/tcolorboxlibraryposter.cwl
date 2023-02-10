# poster tcolorboxlibrary
# 2023/02/10 for v6.0.0

#include:tcolorboxlibrarybreakable
#include:tcolorboxlibrarymagazine
#include:tcolorboxlibraryskins
#include:tcolorboxlibraryfitting

\begin{tcbposter}
\begin{tcbposter}[options%keyvals]
\end{tcbposter}
\tcbposterwidth#L
\tcbposterheight#L
\tcbpostercolspacing#L
\tcbposterrowspacing#L
\tcbpostercolumns
\tcbposterrows
\tcbpostercolwidth#L
\tcbposterrowheight#L
\tcbposterset{options%keyvals}
\posterbox{placement}{box content%text}
\posterbox[options%keyvals]{placement}{box content%text}
\begin{posterboxenv}{placement}
\begin{posterboxenv}[options%keyvals]{placement}
\end{posterboxenv}

#keyvals:\begin{tcbposter},\tcbposterset
poster={%<poster options%>}
coverage={%<options%>}
no coverage
boxes={%<options%>}
fontsize=##L
#endkeyvals

#keyvals:\tcbset,\posterbox,\begin{posterboxenv}
posterset/poster={%<poster options%>}
posterset/coverage={%<options%>}
posterset/no coverage
posterset/boxes={%<options%>}
posterset/fontsize=##L
poster/columns=%<number%>
poster/rows=%<number%>
poster/colspacing=##L
poster/rowspacing=##L
poster/showframe#true,false
poster/width=##L
poster/height=##L
poster/prefix=%<name%>
posterloc/name=%<name%>
posterloc/column=%<number%>
posterloc/column*=%<number%>
posterloc/span=%<number%>
posterloc/row=%<number%>
posterloc/rowspan=%<number%>
posterloc/fixed height
posterloc/below=%<name%>
posterloc/above=%<name%>
posterloc/at=%<name%>
posterloc/between=%<name1%> and %<name2%>
posterloc/sequence=%<sequence%>
posterloc/xshift=##L
posterloc/yshift=##L
#endkeyvals

#keyvals:\tcbset,\begin{tcolorbox},\tcbsetforeverylayer,\tcbox,\newtcolorbox,\renewtcolorbox,\newtcbox,\renewtcbox,\tcolorboxenvironment,\tcbsubtitle,\tcbsidebyside,\tcbsubskin,\tcbincludegraphics,\tcbincludepdf,\begin{tcbraster},\begin{tcbitemize},\tcbitem,\begin{tcboxedraster},\begin{tcboxeditemize},\begin{tcblisting},\tcbinputlisting,\newtcblisting,\renewtcblisting,\newtcbinputlisting,\renewtcbinputlisting,\NewTcbTheorem,\newtcbtheorem,\RenewTcbTheorem,\renewtcbtheorem,\ProvideTcbTheorem,\DeclareTcbTheorem,\tcboxmath,\tcbhighmath,\usetcboxarray,\consumetcboxarray,\posterbox,\begin{posterboxenv},\tcboxfit,\newtcboxfit,\renewtcboxfit,\DeclareTColorBox,\NewTColorBox,\RenewTColorBox,\ProvideTColorBox,\DeclareTotalTColorBox,\NewTotalTColorBox,\RenewTotalTColorBox,\ProvideTotalTColorBox,\DeclareTCBox,\NewTCBox,\RenewTCBox,\ProvideTCBox,\DeclareTotalTCBox,\NewTotalTCBox,\RenewTotalTCBox,\ProvideTotalTCBox,\DeclareTCBListing,\NewTCBListing,\RenewTCBListing,\ProvideTCBListing,\DeclareTCBInputListing,\NewTCBInputListing,\RenewTCBInputListing,\ProvideTCBInputListing,\DeclareTCBoxFit,\NewTCBoxFit,\RenewTCBoxFit,\ProvideTCBoxFit,\DeclareTotalTCBoxFit,\NewTotalTCBoxFit,\RenewTotalTCBoxFit,\ProvideTotalTCBoxFit,\tcboxverb,\begin{docCommand},\begin{docCommand*},\begin{docCommands},\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\begin{docKey},\begin{docKey*},\begin{docKeys},\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations},\docValue,\docValue*,\docAuxCommand,\docAuxCommand*,\docAuxEnvironment,\docAuxEnvironment*,\docAuxKey,\docAuxKey*,\docCounter,\docCounter*,\docLength,\docLength*,\docColor,\docColor*,\begin{dispExample*},\begin{dispListing*},\tcbdocmarginnote
placeholder
#endkeyvals
