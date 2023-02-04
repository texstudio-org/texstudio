# nameauth package
# Matthew Bertucci 2023/02/04 for v3.7

#include:etoolbox
#include:trimspaces
#include:suffix
#include:xargs

#keyvals:\usepackage/nameauth#c
comma
allcaps
allreversed
allrevcomma
noindex
nopretag
verbose
frontmatter
alwaysformat
formatAKA
smallcaps
italic
boldface
altformat
globaltest
oldAKA
oldreset
oldpass
oldtoks
oldsee
#endkeyvals

\AccentCapThis
\AKA*[forename]{surname}[xref forename]{xref surname}
\AKA*[forename]{surname}[xref forename]{xref surname}[xref alternate]#*
\AKA*[forename]{surname}{xref surname}
\AKA*{surname,affix}{xref surname,affix}
\AKA[forename]{surname}[xref forename]{xref surname}
\AKA[forename]{surname}[xref forename]{xref surname}[xref alternate]#*
\AKA[forename]{surname}{xref surname}
\AKA{surname,affix}{xref surname,affix}
\AKA{surname,affix}{xref surname,affix}
\AllCapsActive
\AllCapsInactive
\AltCaps{arg}
\AltFormatActive
\AltFormatActive*
\AltFormatInactive
\AltOff
\AltOn
\begin{nameauth}#\array
\CapName
\CapThis
\DropAffix
\end{nameauth}
\ExcludeName[forename]{surname}
\ExcludeName[forename]{surname}[alternate]#*
\ExcludeName{surname,affix}
\FName[forename]{surname}
\FName[forename]{surname}[alternate]#*
\FName{surname,affix}
\ForceFN
\ForceName
\ForgetName[forename]{surname}
\ForgetName[forename]{surname}[alternate]#*
\ForgetName{surname,affix}
\ForgetThis
\GlobalNames
\GlobalNameTest
\IfAKA[forename]{surname}[alternate]{yes}{no}#*
\IfAKA[forename]{surname}{yes}{no}
\IfAKA{surname,affix}{yes}{no}
\IfFrontName[forename]{surname}[alternate]{yes}{no}#*
\IfFrontName[forename]{surname}{yes}{no}
\IfFrontName{surname,affix}{yes}{no}
\IfMainName[forename]{surname}[alternate]{yes}{no}#*
\IfMainName[forename]{surname}{yes}{no}
\IfMainName{surname,affix}{yes}{no}
\IncludeName*[forename]{surname}
\IncludeName*[forename]{surname}[alternate]#*
\IncludeName*{surname,affix}
\IncludeName[forename]{surname}
\IncludeName[forename]{surname}[alternate]#*
\IncludeName{surname,affix}
\IndexActive
\IndexActual
\IndexInactive
\IndexName[forename]{surname}
\IndexName[forename]{surname}[alternate]#*
\IndexName{surname,affix}
\IndexProtect
\IndexRef[forename]{surname}[alternate]{ref target}#*
\IndexRef[forename]{surname}{ref target}
\IndexRef{surname,affix}{ref target}
\IndexWarnTerse
\IndexWarnVerbose
\JustIndex
\KeepAffix
\KeepName
\LocalNames
\LocalNameTest
\Name*[forename]{surname}
\Name*[forename]{surname}[alternate]#*
\Name*{surname,affix}
\Name[forename]{surname}
\Name[forename]{surname}[alternate]#*
\Name{surname,affix}
\NameAddInfo[forename]{surname}[alternate]{tag}#*
\NameAddInfo[forename]{surname}{tag}
\NameAddInfo{surname,affix}{tag}
\NameauthIndex
\NameClearInfo[forename]{surname}[alternate]{tag}#*
\NameClearInfo[forename]{surname}{tag}
\NameClearInfo{surname,affix}{tag}
\NameQueryInfo[forename]{surname}[alternate]{tag}#*
\NameQueryInfo[forename]{surname}{tag}
\NameQueryInfo{surname,affix}{tag}
\NamesActive
\NamesInactive
\NoComma
\PName*[forename]{surname}[xref forename]{xref surname}
\PName*[forename]{surname}[xref forename]{xref surname}[xref alternate]#*
\PName*[forename]{surname}{xref surname}
\PName*{surname,affix}{xref surname,affix}
\PName[forename]{surname}[xref forename]{xref surname}
\PName[forename]{surname}[xref forename]{xref surname}[xref alternate]#*
\PName[forename]{surname}{xref surname}
\PretagName[forename]{surname}[alternate]{tag}#*
\PretagName[forename]{surname}{tag}
\PretagName{surname,affix}{tag}
\RevComma
\ReverseActive
\ReverseCommaActive
\ReverseCommaInactive
\ReverseInactive
\RevName
\SeeAlso
\ShowComma
\SkipIndex
\SubvertName[forename]{surname}
\SubvertName[forename]{surname}[alternate]#*
\SubvertName{surname,affix}
\SubvertThis
\TagName[forename]{surname}[alternate]{tag}#*
\TagName[forename]{surname}{tag}
\TagName{surname,affix}{tag}
\textBF{text}
\textIT{text}
\textSC{text}
\textUC{text}
\UntagName[forename]{surname}
\UntagName[forename]{surname}[alternate]#*
\UntagName{surname,affix}

\<#S
\FrontNameHook#*
\FrontNamesFormat#*
\ifNameauthObsolete#*
\ifNameauthWestern#*
\MainNameHook#*
\NameauthFName#*
\NameauthLName#*
\NameauthObsoletefalse#S
\NameauthObsoletetrue#S
\NameauthPattern#*
\NameauthWesternfalse#S
\NameauthWesterntrue#S
\NameauthName#*
\NameParser#*
\NamesFormat#*
\RevSpace#S
\ShowIdxPageref*[forename]{surname}#*
\ShowIdxPageref*[forename]{surname}[alternate]#*
\ShowIdxPageref*{surname,affix}#*
\ShowIdxPageref[forename]{surname}#*
\ShowIdxPageref[forename]{surname}[alternate]#*
\ShowIdxPageref{surname,affix}#*
\ShowNameInfo[forename]{surname}#*
\ShowNameInfo[forename]{surname}[alternate]#*
\ShowNameInfo{surname,affix}#*
\ShowNameState[forename]{surname}#*
\ShowNameState[forename]{surname}[alternate]#*
\ShowNameState{surname,affix}#*
\ShowPattern[forename]{surname}#*
\ShowPattern[forename]{surname}[alternate]#*
\ShowPattern{surname,affix}#*
\Space#S
\SpaceW#S
