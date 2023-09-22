# robust-externalize package
# Matthew Bertucci 2023/09/22 for v2.0

#include:pgfkeys
#include:pgffor
#include:graphicx
#include:verbatim
#include:xsimverb
#include:etoolbox

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
\copyGroupPlaceholders{name group}{name group to copy}
\copyPlaceholder{new placeholder%definition}{old placeholder%definition}
\evalPlaceholder{name placeholder%definition}
\evalPlaceholderInplace{name placeholder%definition}
\evalPlaceholderNoReplacement{name placeholder%definition}
\firstPlaceholdersInCompilationCommand{list of placeholders%definition}
\firstPlaceholdersInTemplate{list of placeholders%definition}
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
\removeImportedPlaceholder{name placeholder%definition}
\removePlaceholder{placeholder%definition}
\removePlaceholderFromGroup{name group}{list of placeholders%definition}
\removePlaceholdersFromGroup{name group}{list of placeholders%definition}
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
\robExtImportAllPlaceholders#S
\robExtImportPlaceholder#S
\robExtImportPlaceholderFirst{arg}#S
\robExtImportPlaceholdersFromGroup{arg}#S
\robExtIncludeFile{arg}#S
\robExtIncludeGraphicsArgs#S
\robExtKeepaftergroup{arg}#S
\robExtKeepPlaceholderAfterGroup{arg}#S
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
\robExtSaveDependencies{arg}#S
\robExtSetBackCompilationCommandAndTemplate#S
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
\robExtWriteFile{arg}#S
\setPlaceholderFirst{arg1}{arg2}#S
\setPlaceholderFromStringExpanded{arg1}{arg2}#S
\showAllRegisteredGroupsAndPlaceholders#S
