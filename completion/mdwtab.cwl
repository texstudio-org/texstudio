# mdwtab package
# Matthew Bertucci 2022/06/08 for v1.9

\tabpause#t
\vline#t
\vline[width]#t
\begin{array}{cols}#\math,array
\begin{array}[pos]{cols}#\math,array
\end{array}
\begin{smarray}{cols}#\math,array
\begin{smarray}[pos]{cols}#\math,array
\end{smarray}
\vgap{length}#t
\vgap[cols]{length}#t
\hlx{colspec}#t
\tabstyle#*
\extrarowheight#*
\tabextrasep#*
\arrayextrasep#*
\smarrayextrasep#*
\smarraycolsep#*
\newcolumntype{name}{definition}
\newcolumntype{name}[args]{definition}
\newcolumntype{name}[args][default]{definition}
\colset{set-name}
\colpush{set-name}
\colpop
\coldef %<⟨col-name⟩%>{%<definition%>}
\coldef[%<set-name%>] %<⟨col-name⟩%>{%<definition%>}#*
\tabcoltype{pre-text}{post-text}
\tabuserpretype{text}
\tabuserposttype{text}
\tabspctype{text}
\tabruletype{text}
\collet %<⟨col-name1⟩%> %<⟨col-name2⟩%>
\collet %<⟨col-name1⟩%> [%<set-name%>]%<⟨col-name2⟩%>
\collet[%<set-name1%>] %<⟨col-name1⟩%> [%<set-name2%>]%<⟨col-name2⟩%>#*
\hlxdef %<⟨name⟩%>{%<definition%>}#*
\ifinrange{number}{range-list}{then}{else}#*
\ranges{macro}{range-list}#*
\showcol{name}#*
\showpream{preamble}#*

\begin{savenotes}
\end{savenotes}
\savenotes#*
\spewnotes#*

\doafter%<⟨token⟩ ⟨group⟩%>#*