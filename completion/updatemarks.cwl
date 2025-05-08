# updatemarks package
# Matthew Bertucci 2025/05/08 for v0.4

#include:etoolbox
#include:updatemarks-nums

#keyvals:\usepackage/updatemarks#c
minipage
multicol
tcolorbox
#endkeyvals

\AddToUpdateMarksList{number list}
\SetUpdateMarksList{number list}
\RemoveFromUpdateMarksList{number list}
\AddAllocatedToUpdateMarksList
\ExtractMarks{box number}
\ExtractMarks[number list]{box number}
\ExtractMarks*{text}
\ExtractMarks*[number list]{text}
\ExtractSplitMarks
\ExtractSplitMarks[number list]
\UpdateMarks
\UpdateMarks[number list]
\ExtractMarksTo{box number}{cmd}#d
\ExtractMarksTo[number list]{box number}{cmd}#d
\ExtractMarksTo*{text}{cmd}#d
\ExtractMarksTo*[number list]{text}{cmd}#d

#keyvals:\tcbset,\begin{tcolorbox},\tcbsetforeverylayer,\tcbox,\newtcolorbox,\renewtcolorbox,\newtcbox,\renewtcbox,\tcolorboxenvironment,\tcbsubtitle,\tcbsidebyside,\tcbsubskin,\tcbincludegraphics,\tcbincludepdf,\begin{tcbraster},\begin{tcbitemize},\tcbitem,\begin{tcboxedraster},\begin{tcboxeditemize},\begin{tcblisting},\tcbinputlisting,\newtcblisting,\renewtcblisting,\newtcbinputlisting,\renewtcbinputlisting,\NewTcbTheorem,\newtcbtheorem,\RenewTcbTheorem,\renewtcbtheorem,\ProvideTcbTheorem,\DeclareTcbTheorem,\tcboxmath,\tcbhighmath,\usetcboxarray,\consumetcboxarray,\posterbox,\begin{posterboxenv},\tcboxfit,\newtcboxfit,\renewtcboxfit,\DeclareTColorBox,\NewTColorBox,\RenewTColorBox,\ProvideTColorBox,\DeclareTotalTColorBox,\NewTotalTColorBox,\RenewTotalTColorBox,\ProvideTotalTColorBox,\DeclareTCBox,\NewTCBox,\RenewTCBox,\ProvideTCBox,\DeclareTotalTCBox,\NewTotalTCBox,\RenewTotalTCBox,\ProvideTotalTCBox,\DeclareTCBListing,\NewTCBListing,\RenewTCBListing,\ProvideTCBListing,\DeclareTCBInputListing,\NewTCBInputListing,\RenewTCBInputListing,\ProvideTCBInputListing,\DeclareTCBoxFit,\NewTCBoxFit,\RenewTCBoxFit,\ProvideTCBoxFit,\DeclareTotalTCBoxFit,\NewTotalTCBoxFit,\RenewTotalTCBoxFit,\ProvideTotalTCBoxFit,\tcboxverb,\begin{docCommand},\begin{docCommand*},\begin{docCommands},\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\begin{docKey},\begin{docKey*},\begin{docKeys},\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations},\docValue,\docValue*,\docAuxCommand,\docAuxCommand*,\docAuxEnvironment,\docAuxEnvironment*,\docAuxKey,\docAuxKey*,\docCounter,\docCounter*,\docLength,\docLength*,\docColor,\docColor*,\begin{dispExample*},\begin{dispListing*},\tcbdocmarginnote
updatemarks#true,false
#endkeyvals

\updatemarks_parse_classes:Nn %<⟨seq var⟩%> {%<⟨number list⟩%>}#/%expl3
\updatemarks_extract:nN {%<⟨material⟩%>} %<⟨seq var⟩%>#/%expl3
\updatemarks_extract_split:N %<⟨seq var⟩%>#/%expl3
\updatemarks_extract:nNN {%<⟨material⟩%>} %<⟨seq var⟩ ⟨tl var⟩%>#/%expl3
\updatemarks_extract_act:nNn {%<⟨material⟩%>} %<⟨seq var⟩%> {%<⟨code⟩%>}#/%expl3
\updatemarks_update:N %<⟨seq var⟩%>#/%expl3
\updatemarks_save:Nnn %<⟨seq var⟩%> {%<⟨position⟩%>} {%<⟨value code⟩%>}#/%expl3
\updatemarks_save_e:Nnn %<⟨seq var⟩%> {%<⟨position⟩%>} {%<⟨value code⟩%>}#/%expl3
\updatemarks_alias:Nnn %<⟨seq var⟩%> {%<⟨alias position⟩%>} {%<⟨source position⟩%>}#/%expl3
\updatemarks_remove:Nn %<⟨seq var⟩%> {%<⟨position⟩%>}#/%expl3
\updatemarks_value:nn {%<⟨position⟩%>} {%<⟨mark class⟩%>}#/%expl3
\g_updatemarks_max_int#/%expl3
\g_updatemarks_seq#/%expl3
\g_updatemarks_classes_seq#/%expl3
\l_updatemarks_nonempty_bool#/%expl3
\l_updatemarks_first_tl#/%expl3
\l_updatemarks_last_tl#/%expl3
