# robust-externalize package
# Matthew Bertucci 2023/11/14 for v2.2

#include:pgfkeys
#include:pgffor
#include:graphicx
#include:verbatim
#include:xsimverb
#include:etoolbox
#include:iftex
#include:xparse
#include:atveryend
#include:etl

\begin{CacheMe}{preset style}
\end{CacheMe}
\begin{CacheMeCode}{preset style}#V
\end{CacheMeCode}
\begin{CacheMeNoContent}
\end{CacheMeNoContent}
\begin{PlaceholderFromCode}{name placeholder}#V
\end{PlaceholderFromCode}
\begin{PlaceholderPathFromCode}{name placeholder}#V
\begin{PlaceholderPathFromCode}[suffix]{name placeholder}#V
\end{PlaceholderPathFromCode}
\begin{SetPlaceholderCode}{name placeholder}#V
\end{SetPlaceholderCode}
\begin{tikzpictureC}#\pictureHighlight
\begin{tikzpictureC}[options]
\begin{tikzpictureC}<preset style>
\begin{tikzpictureC}<preset style>[options]
\end{tikzpictureC}

\addBeforePlaceholder*{placeholder%definition}{content}
\addBeforePlaceholder{placeholder%definition}{content}
\addBeforePlaceholderNoImport*{placeholder%definition}{content}
\addBeforePlaceholderNoImport{placeholder%definition}{content}
\addPlaceholdersToGroup{name group}{placeholders%definition}
\addToPlaceholder*{placeholder%definition}{content}
\addToPlaceholder{placeholder%definition}{content}
\addToPlaceholderNoImport*{placeholder%definition}{content}
\addToPlaceholderNoImport{placeholder%definition}{content}
\appendBeforeGroupPlaceholders{name group}{name group to append}
\appendGroupPlaceholders{name group}{name group to append}
\boxRobExt#*
\cacheEnvironment[delimiters]{envname}{preset options}
\cacheEnvironment{envname}{preset options}
\cacheMe[preset style]{content%definition}
\cacheMe{content%definition}
\cacheTikz
\cacheTikz[preset for TikZ]
\cacheTikz[preset for TikZ][preset for TikZpicture]
\cacheTikz[preset for TikZ][preset for TikZpicture][delimiters]
\clearGroupPlaceholders{name group}
\clearImportedPlaceholders{name placeholder%definition}
\configIfMacroPresent{macro}{options}
\copyGroupPlaceholders{name group}{name group to copy}
\copyPlaceholder{new placeholder%definition}{old placeholder%definition}
\DeclareDocumentCommandAutoForward{cmd}{xargs}[add. style]{def}#d
\DeclareDocumentCommandAutoForward{cmd}{xargs}{def}#d
\DeclareExpandableDocumentCommandAutoForward{cmd}{xargs}[add. style]{def}#d
\DeclareExpandableDocumentCommandAutoForward{cmd}{xargs}{def}#d
\defAutoForward{cmd}[arg spec]{def}#d
\defAutoForward{cmd}[arg spec]{def}[add. style]#d
\defAutoForward{cmd}{def}#d
\defAutoForward{cmd}{def}[add. style]#d
\evalPlaceholder{name placeholder%definition}
\evalPlaceholderInplace{name placeholder%definition}
\evalPlaceholderNoReplacement{name placeholder%definition}
\firstPlaceholdersInCompilationCommand{list of placeholders%definition}
\firstPlaceholdersInTemplate{list of placeholders%definition}
\genericAutoForward{string}{code}
\genericAutoForward{string}[add. style]{code}
\genericAutoForward[preset]{string}{code}
\genericAutoForward[preset]{string}[add. style]{code}
\genericAutoForward*{string}{code}
\genericAutoForward*{string}[add. style]{code}
\genericAutoForward*[preset]{string}{code}
\genericAutoForward*[preset]{string}[add. style]{code}
\genericAutoForwardStringMatch{string}{code}
\genericAutoForwardStringMatch{string}[add. style]{code}
\genericAutoForwardStringMatch[preset]{string}{code}
\genericAutoForwardStringMatch[preset]{string}[add. style]{code}
\genericAutoForwardStringMatch*{string}{code}
\genericAutoForwardStringMatch*{string}[add. style]{code}
\genericAutoForwardStringMatch*[preset]{string}{code}
\genericAutoForwardStringMatch*[preset]{string}[add. style]{code}
\getPlaceholder[new placeholder%definition]{name placeholder%definition}
\getPlaceholder{name placeholder%definition}
\getPlaceholderInResult[new placeholder%definition]{name placeholder%definition}
\getPlaceholderInResult{name placeholder%definition}
\getPlaceholderInResultReplaceFromList*[new placeholder%definition]{name placeholder%definition}{arg}
\getPlaceholderInResultReplaceFromList[new placeholder%definition]{name placeholder%definition}{arg}
\getPlaceholderInResultReplaceFromList{name placeholder%definition}{arg}
\getPlaceholderNoReplacement{name placeholder%definition}
\importAllPlaceholders
\importAllPlaceholders
\importPlaceholder{name placeholder%definition}
\importPlaceholderFirst
\importPlaceholdersFromGroup{name group}
\importPlaceholdersFromGroup{name placeholder%definition}
\newcommandAutoForward{cmd}[args][default]{def}#d
\newcommandAutoForward{cmd}[args][default]{def}[add. style]#d
\newcommandAutoForward{cmd}[args]{def}#d
\newcommandAutoForward{cmd}[args]{def}[add. style]#d
\newcommandAutoForward{cmd}{def}#d
\newcommandAutoForward{cmd}{def}[add. style]#d
\NewDocumentCommandAutoForward{cmd}{xargs}[add. style]{def}#d
\NewDocumentCommandAutoForward{cmd}{xargs}{def}#d
\NewExpandableDocumentCommandAutoForward{cmd}{xargs}[add. style]{def}#d
\NewExpandableDocumentCommandAutoForward{cmd}{xargs}{def}#d
\newGroupPlaceholders{name group}
\onlyPlaceholdersInCompilationCommand{list of placeholders%definition}
\onlyPlaceholdersInTemplate{list of placeholders%definition}
\placeholderDoubleNumberHashesInplace{placeholder%definition}
\placeholderFromContent{name placeholder%definition}{content placeholder%text}
\placeholderFromFileContent{name placeholder%definition}{file}
\placeholderFromString*{latex3 string%definition}
\placeholderFromString{latex3 string%definition}
\placeholderHalveNumberHashesInplace{placeholder%definition}
\placeholderPathFromContent{name placeholder%definition}[suffix]{content%text}
\placeholderPathFromContent{name placeholder%definition}{content%text}
\placeholderPathFromFilename{name placeholder%definition}{file}
\placeholderReplaceInplace{placeholder%definition}{from}{to}
\placeholderReplaceInplaceEval{placeholder%definition}{from}{to}
\printAllPlaceholders
\printAllPlaceholdersExceptDefaults
\printAllPlaceholdersExceptDefaults*
\printAllRegisteredGroups
\printAllRegisteredGroupsAndPlaceholders
\printAllRegisteredGroupsAndPlaceholders*
\printGroupPlaceholders*{name group}
\printGroupPlaceholders{name group}
\printImportedPlaceholders
\printImportedPlaceholdersExceptDefaults
\printPlaceholder*{name placeholder%definition}
\printPlaceholder{name placeholder%definition}
\printPlaceholderNoReplacement*{name placeholder%definition}
\printPlaceholderNoReplacement{name placeholder%definition}
\providecommandAutoForward{cmd}[args][default]{def}#d
\providecommandAutoForward{cmd}[args][default]{def}[add. style]#d
\providecommandAutoForward{cmd}[args]{def}#d
\providecommandAutoForward{cmd}[args]{def}[add. style]#d
\providecommandAutoForward{cmd}{def}#d
\providecommandAutoForward{cmd}{def}[add. style]#d
\ProvideDocumentCommandAutoForward{cmd}{xargs}[add. style]{def}#d
\ProvideDocumentCommandAutoForward{cmd}{xargs}{def}#d
\ProvideExpandableDocumentCommandAutoForward{cmd}{xargs}[add. style]{def}#d
\ProvideExpandableDocumentCommandAutoForward{cmd}{xargs}{def}#d
\removeImportedPlaceholder{name placeholder%definition}
\removePlaceholder{placeholder%definition}
\removePlaceholderFromGroup{name group}{list of placeholders%definition}
\removePlaceholdersFromGroup{name group}{list of placeholders%definition}
\renewcommandAutoForward{cmd}[args][default]{def}
\renewcommandAutoForward{cmd}[args][default]{def}[add. style]
\renewcommandAutoForward{cmd}[args]{def}
\renewcommandAutoForward{cmd}[args]{def}[add. style]
\renewcommandAutoForward{cmd}{def}
\renewcommandAutoForward{cmd}{def}[add. style]
\RenewDocumentCommandAutoForward{cmd}{xargs}[add. style]{def}
\RenewDocumentCommandAutoForward{cmd}{xargs}{def}
\RenewExpandableDocumentCommandAutoForward{cmd}{xargs}[add. style]{def}
\RenewExpandableDocumentCommandAutoForward{cmd}{xargs}{def}
\rescanPlaceholderInVariableNoReplacement{name macro}{name placeholder%definition}
\robExtAddCachePath{path%file}#*
\robExtAddCachePathAndName{path%file}#*
\robExtCacheCommand[delimiters]{csname}[xparse signature]{preset options}
\robExtCacheCommand[delimiters]{csname}{preset options}
\robExtCacheCommand{csname}[xparse signature]{preset options}
\robExtCacheCommand{csname}{preset options}
\robExtConfigure{preset style}
\robExtDepth#*
\robExtDisableTikzpictureOverwrite#*
\robExtExternalizeAllTikzpictures#*
\robExtGetPlaceholderInResultReplaceFromList*{name placeholder%definition}{arg}
\robExtHeight#*
\robExtPathToInput#*
\robExtPrefixFilename#*
\robExtResult#*
\robExtWidth#*
\setPlaceholder{name placeholder%definition}{content placeholder%text}
\setPlaceholderFromString*{latex3 string%definition}
\setPlaceholderFromString{latex3 string%definition}
\setPlaceholderRec{name placeholder%definition}{content placeholder%text}
\setPlaceholderRecReplaceFromList{list of placeholders%definition}{new placeholder%definition}{content}
\writeRobExt#*

# not documented
\addPlaceholdersToGroupBefore{arg1}{arg2}#S
\autoForwardMacro{arg}#S
\autoForwardMacro{arg}[opt]#S
\begin{RobExtCacheMe}{arg}#S
\begin{RobExtCacheMeCode}{arg}#S
\begin{RobExtCacheMeNoContent}#S
\begin{RobExtPlaceholderFromCode}{arg}#S
\begin{RobExtPlaceholderPathFromCode}[opt]{arg}#S
\begin{RobExtPlaceholderPathFromCode}{arg}#S
\checkIfPlaceholderNameIsLegal{arg}#S
\end{RobExtCacheMe}#S
\end{RobExtCacheMeCode}#S
\end{RobExtCacheMeNoContent}#S
\end{RobExtPlaceholderFromCode}#S
\end{RobExtPlaceholderPathFromCode}#S
\ensureGroupPlaceholdersExists{arg}#S
\evalPlaceholderInplaceFromSinglePlaceholder{arg}#S
\evalPlaceholderReplaceFromList{arg1}{arg2}#S
\evalPlaceholderStartFromList{arg1}{arg2}#S
\keepPlaceholderAfterGroup{arg}#S
\placeholderFromContentFirst{arg1}{arg2}#S
\placeholderFromStringExpanded{arg1}{arg2}#S
\registerGroupPlaceholders{arg}#S
\robExtAddArgumentToCompilationCommand{arg}#S
\robExtAddBeforePlaceholder*{arg1}{arg2}#S
\robExtAddBeforePlaceholder{arg1}{arg2}#S
\robExtAddBeforePlaceholderNoImport*{arg1}{arg2}#S
\robExtAddBeforePlaceholderNoImport{arg1}{arg2}#S
\robExtAddDependency{arg}#S
\robExtAddPlaceholdersToGroup{arg1}{arg2}#S
\robExtAddPlaceholdersToGroupBefore{arg1}{arg2}#S
\robExtAddPlaceholderToList{arg}#S
\robExtAddPlaceholderToListFirst{arg}#S
\robExtAddPrefixName{arg}#S
\robExtAddToCommandResetList{arg}#S
\robExtAddToEnvironmentResetList{arg}#S
\robExtAddToPlaceholder*{arg1}{arg2}#S
\robExtAddToPlaceholder{arg1}{arg2}#S
\robExtAddToPlaceholderNoImport*{arg1}{arg2}#S
\robExtAddToPlaceholderNoImport{arg1}{arg2}#S
\robExtAppendBeforeGroupPlaceholders{arg1}{arg2}#S
\robExtAppendGroupPlaceholders{arg1}{arg2}#S
\robExtArgumentList#S
\robExtAutoForward#S
\robExtAutoForwardMacro{arg}#S
\robExtAutoForwardMacro{arg}[opt]#S
\robExtCacheCommand[opt]{arg1}{arg2}#S
\robExtCacheCommand[opt1]{arg1}[opt2]{arg2}#S
\robExtCacheCommand{arg1}[opt]{arg2}#S
\robExtCacheCommand{arg1}{arg2}#S
\robExtCacheEnvironment[opt]{arg1}{arg2}#S
\robExtCacheEnvironment{arg1}{arg2}#S
\robExtCacheMe[opt]{arg}#S
\robExtCacheMe{arg}#S
\robExtCheckIfPrefixFolderExists#S
\robExtClearGroupPlaceholders{arg}#S
\robExtClearImportedPlaceholders#S
\robExtCompileFile{arg}#S
\robExtConfigIfMacroPresent{macro}{options}#S
\robExtCopyGroupPlaceholders{arg1}{arg2}#S
\robExtCopyPlaceholder*{arg1}{arg2}#S
\robExtCopyPlaceholder{arg1}{arg2}#S
\robExtCurrentCompilationCommand#S
\robExtDebugDependency#S
\robExtDebugMessage{arg}#S
\robExtDebugWarning{arg}#S
\robExtDisableTikzpictureOverwrite#S
\robExtEnsureGroupPlaceholdersExists{arg}#S
\robExtEvalPlaceholder{arg}#S
\robExtEvalPlaceholderInplace{arg}#S
\robExtEvalPlaceholderInplaceFromSinglePlaceholder{arg}#S
\robExtEvalPlaceholderNoReplacement{arg}#S
\robExtEvalPlaceholderReplaceFromList{arg1}{arg2}#S
\robExtEvalPlaceholderStartFromList{arg1}{arg2}#S
\robExtEvaluateCompileAndInclude#S
\robExtFirstPlaceholdersInCompilationCommand{arg}#S
\robExtFirstPlaceholdersInTemplate{arg}#S
\robExtGetCommandDefinition{arg}#S
\robExtGetCommandDefinitionInMacro{arg}#S
\robExtGetNearlyFinalValueTemplateAndCompilationCommand#S
\robExtGetPlaceholder[opt]{arg}#S
\robExtGetPlaceholder{arg}#S
\robExtGetPlaceholderInResult*[opt]{arg}#S
\robExtGetPlaceholderInResult*{arg}#S
\robExtGetPlaceholderInResult[opt]{arg}#S
\robExtGetPlaceholderInResult{arg}#S
\robExtGetPlaceholderInResultFromSinglePlaceholder*[opt]{arg}#S
\robExtGetPlaceholderInResultFromSinglePlaceholder*{arg}#S
\robExtGetPlaceholderInResultFromSinglePlaceholder[opt]{arg}#S
\robExtGetPlaceholderInResultFromSinglePlaceholder{arg}#S
\robExtGetPlaceholderInResultReplaceFromList*{arg1}[opt]{arg2}#S
\robExtGetPlaceholderInResultReplaceFromList*{arg1}{arg2}#S
\robExtGetPlaceholderInResultReplaceFromList{arg1}[opt]{arg2}#S
\robExtGetPlaceholderInResultReplaceFromList{arg1}{arg2}#S
\robExtGetPlaceholderNoReplacement{arg}#S
\robExtGetPrefixPath#S
\RobExtIfFormatAtLeastTF{true}{false}#S
\robExtIfMatchesRegex{arg1}{arg2}#S
\robExtIfMatchesString{arg1}{arg2}#S
\robExtIfWindowsTF{true}{false}#S
\robExtImagePlaceholderIfFallbackMode#S
\robExtImagePlaceholderIfManualMode#S
\robExtImagePlaceholderIfParallelCompilation#S
\robExtImportAllPlaceholders#S
\robExtImportPlaceholder#S
\robExtImportPlaceholderFirst{arg}#S
\robExtImportPlaceholdersFromGroup{arg}#S
\robExtIncludeFile{arg}#S
\robExtIncludeGraphicsArgs#S
\robExtKeepaftergroup{arg}#S
\robExtKeepPlaceholderAfterGroup{arg}#S
\robExtLoadAutoForwardMacroConfig{arg}#S
\robExtLoadSpecialPlaceholders#S
\robExtOnlyPlaceholdersInCompilationCommand{arg}#S
\robExtOnlyPlaceholdersInTemplate{arg}#S
\robExtPlaceholderDoubleNumberHashesInplace{arg}#S
\robExtPlaceholderFromContent{arg1}{arg2}#S
\robExtPlaceholderFromContentFirst*{arg1}{arg2}#S
\robExtPlaceholderFromContentFirst{arg1}{arg2}#S
\robExtPlaceholderFromFileContent*{arg1}{arg2}#S
\robExtPlaceholderFromFileContent{arg1}{arg2}#S
\robExtPlaceholderFromString*{arg1}{arg2}#S
\robExtPlaceholderFromString{arg1}{arg2}#S
\robExtPlaceholderFromStringExpanded*{arg1}{arg2}#S
\robExtPlaceholderFromStringExpanded{arg1}{arg2}#S
\robExtPlaceholderHalveNumberHashesInplace{arg}#S
\robExtPlaceholderPathFromContent*{arg1}[opt]{arg2}#S
\robExtPlaceholderPathFromContent*{arg1}{arg2}#S
\robExtPlaceholderPathFromContent{arg1}[opt]{arg2}#S
\robExtPlaceholderPathFromContent{arg1}{arg2}#S
\robExtPlaceholderPathFromFilename*{arg1}{arg2}#S
\robExtPlaceholderPathFromFilename{arg1}{arg2}#S
\robExtPlaceholderReplaceInplace{arg1}{arg2}{arg3}#S
\robExtPlaceholderReplaceInplaceEval{arg1}{arg2}{arg3}#S
\robExtPrintAllPlaceholders#S
\robExtPrintAllPlaceholdersExceptDefaults#S
\robExtPrintAllPlaceholdersExceptDefaults*#S
\robExtPrintAllRegisteredGroups#S
\robExtPrintAllRegisteredGroups*#S
\robExtPrintAllRegisteredGroupsAndPlaceholders#S
\robExtPrintAllRegisteredGroupsAndPlaceholders*#S
\robExtPrintGroupPlaceholders*{arg}#S
\robExtPrintGroupPlaceholders{arg}#S
\robExtPrintPlaceholder*{arg}#S
\robExtPrintPlaceholder{arg}#S
\robExtPrintPlaceholderNoReplacement*{arg}#S
\robExtPrintPlaceholderNoReplacement{arg}#S
\robExtRegisterGroupPlaceholders{arg}#S
\robExtRemoveImportedPlaceholder{arg}#S
\robExtRemovePlaceholder{arg}#S
\robExtRemovePlaceholdersFromGroup{arg1}{arg2}#S
\robExtRescanHashRobust{arg}#S
\robExtRescanPlaceholderInVariableNoReplacement{arg1}{arg2}#S
\robExtResetDependencies{arg}#S
\robExtRestoreDependencies{arg}#S
\robExtRunCodeToRunForMacroPresent{arg}#S
\robExtSaveDependencies{arg}#S
\robExtSetBackCompilationCommandAndTemplate#S
\robExtSetCodeToRunIfMacroPresent{arg1}{arg2}#S
\robExtSetCommandResetList{arg}#S
\robExtSetCompilationCommand{arg}#S
\robExtSetEnvironmentResetList{arg}#S
\robExtSetPlaceholder{arg1}{arg2}#S
\robExtSetPlaceholderFirst{arg1}{arg2}#S
\robExtSetPlaceholderRec*{arg1}{arg2}#S
\robExtSetPlaceholderRec{arg1}{arg2}#S
\robExtSetPlaceholderRecReplaceFromList*{arg1}{arg2}{arg3}#S
\robExtSetPlaceholderRecReplaceFromList{arg1}{arg2}{arg3}#S
\robExtShowAllRegisteredGroupsAndPlaceholders#S
\robExtShowAllRegisteredGroupsAndPlaceholders*#S
\robExtShowPlaceholder*{arg}#S
\robExtShowPlaceholder{arg}#S
\robExtShowPlaceholders#S
\robExtShowPlaceholders*#S
\robExtShowPlaceholdersContents#S
\robExtShowPlaceholdersContents*#S
\robExtStrSetHashRobust{arg1}{arg2}#S
\robExtUseHookJustBeforeWritingFiles#S
\robExtWriteFile{arg}#S
\setPlaceholderFirst{arg1}{arg2}#S
\setPlaceholderFromStringExpanded{arg1}{arg2}#S
\showAllRegisteredGroupsAndPlaceholders#S
\robExtGenericAutoForward{string}{code}
\robExtGenericAutoForward{string}[add. style]{code}
\robExtGenericAutoForward[preset]{string}{code}
\robExtGenericAutoForward[preset]{string}[add. style]{code}
\robExtGenericAutoForward*{string}{code}
\robExtGenericAutoForward*{string}[add. style]{code}
\robExtGenericAutoForward*[preset]{string}{code}
\robExtGenericAutoForward*[preset]{string}[add. style]{code}
\robExtGenericAutoForwardStringMatch{string}{code}
\robExtGenericAutoForwardStringMatch{string}[add. style]{code}
\robExtGenericAutoForwardStringMatch[preset]{string}{code}
\robExtGenericAutoForwardStringMatch[preset]{string}[add. style]{code}
\robExtGenericAutoForwardStringMatch*{string}{code}
\robExtGenericAutoForwardStringMatch*{string}[add. style]{code}
\robExtGenericAutoForwardStringMatch*[preset]{string}{code}
\robExtGenericAutoForwardStringMatch*[preset]{string}[add. style]{code}
