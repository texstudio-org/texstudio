# robust-externalize package
# Matthew Bertucci 2023/09/06 for v1.0

#include:pgfkeys
#include:pgffor
#include:graphicx
#include:verbatim
#include:xsimverb

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
\begin{tikzpictureC}[options][preset style]
\end{tikzpictureC}

\addBeforePlaceholder*{placeholder%definition}{content}
\addBeforePlaceholder{placeholder%definition}{content}
\addToPlaceholder*{placeholder%definition}{content}
\addToPlaceholder{placeholder%definition}{content}
\boxRobExt#*
\cacheMe[preset style]{content%definition}
\cacheMe{content%definition}
\copyPlaceholder{new placeholder%definition}{old placeholder%definition}
\evalPlaceholder{name placeholder%definition}
\evalPlaceholderInplace{name placeholder%definition}
\evalPlaceholderNoReplacement{name placeholder%definition}
\getPlaceholder[new placeholder%definition]{name placeholder%definition}
\getPlaceholder{name placeholder%definition}
\getPlaceholderInResult[new placeholder%definition]{name placeholder%definition}
\getPlaceholderInResult{name placeholder%definition}
\getPlaceholderNoReplacement{name placeholder%definition}
\placeholderFromContent{name placeholder%definition}{content placeholder%text}
\placeholderFromFileContent{name placeholder%definition}{file}
\placeholderPathFromContent{name placeholder%definition}[suffix]{content%text}
\placeholderPathFromContent{name placeholder%definition}{content%text}
\placeholderPathFromFilename{name placeholder%definition}{file}
\printAllPlaceholders
\printAllPlaceholdersExceptDefaults
\printAllPlaceholdersExceptDefaults*
\printPlaceholder*{name placeholder%definition}
\printPlaceholder{name placeholder%definition}
\printPlaceholderNoReplacement*{name placeholder%definition}
\printPlaceholderNoReplacement{name placeholder%definition}
\robExtAddCachePath{path%file}#*
\robExtAddCachePathAndName{path%file}#*
\robExtConfigure{preset style}
\robExtDepth#*
\robExtDisableTikzpictureOverwrite#*
\robExtExternalizeAllTikzpictures
\robExtHeight#*
\robExtPathToInput#*
\robExtPrefixFilename#*
\robExtResult#*
\robExtWidth#*
\setPlaceholder{name placeholder%definition}{content placeholder%text}
\setPlaceholderRec{name placeholder%definition}{content placeholder%text}
\writeRobExt#*

# not documented
\begin{RobExtCacheMe}{arg}#S
\begin{RobExtCacheMeCode}{arg}#S
\begin{RobExtCacheMeNoContent}#S
\begin{RobExtPlaceholderFromCode}{arg}#S
\begin{RobExtPlaceholderPathFromCode}[opt]{arg}#S
\begin{RobExtPlaceholderPathFromCode}{arg}#S
\end{RobExtCacheMe}#S
\end{RobExtCacheMeCode}#S
\end{RobExtCacheMeNoContent}#S
\end{RobExtPlaceholderFromCode}#S
\end{RobExtPlaceholderPathFromCode}#S
\robExtAddArgumentToCompilationCommand{arg}#S
\robExtAddBeforePlaceholder*{arg1}{arg2}#S
\robExtAddBeforePlaceholder{arg1}{arg2}#S
\robExtAddDependency{arg}#S
\robExtAddPlaceholderToList{arg}#S
\robExtAddPrefixName{arg}#S
\robExtAddToPlaceholder*{arg1}{arg2}#S
\robExtAddToPlaceholder{arg1}{arg2}#S
\robExtCacheMe[opt]{arg}#S
\robExtCacheMe{arg}#S
\robExtCheckIfPrefixFolderExists#S
\robExtCompileFile{arg}#S
\robExtCopyPlaceholder{arg1}{arg2}#S
\robExtDebugDependency#S
\robExtEvalPlaceholder{arg}#S
\robExtEvalPlaceholderInplace{arg}#S
\robExtEvalPlaceholderNoReplacement{arg}#S
\robExtEvaluateCompileAndInclude#S
\robExtGetPlaceholder[opt]{arg}#S
\robExtGetPlaceholder{arg}#S
\robExtGetPlaceholderInResult[opt]{arg}#S
\robExtGetPlaceholderInResult{arg}#S
\robExtGetPlaceholderNoReplacement{arg}#S
\robExtGetPrefixPath#S
\robExtIncludeFile{arg}#S
\robExtIncludeGraphicsArgs#S
\robExtKeepaftergroup{arg}#S
\robExtPlaceholderFromContent{arg1}{arg2}#S
\robExtPlaceholderFromFileContent{arg1}{arg2}#S
\robExtPlaceholderPathFromContent{arg1}[opt]{arg2}#S
\robExtPlaceholderPathFromContent{arg1}{arg2}#S
\robExtPlaceholderPathFromFilename{arg1}{arg2}#S
\robExtPrintAllPlaceholders#S
\robExtPrintAllPlaceholdersExceptDefaults#S
\robExtPrintAllPlaceholdersExceptDefaults*#S
\robExtPrintPlaceholder*{arg}#S
\robExtPrintPlaceholder{arg}#S
\robExtPrintPlaceholderNoReplacement*{arg}#S
\robExtPrintPlaceholderNoReplacement{arg}#S
\robExtRemovePlaceholder{arg}#S
\robExtResetDependencies{arg}#S
\robExtSetCompilationCommand{arg}#S
\robExtSetPlaceholder{arg1}{arg2}#S
\robExtSetPlaceholderRec{arg1}{arg2}#S
\robExtShowPlaceholder*{arg}#S
\robExtShowPlaceholder{arg}#S
\robExtShowPlaceholders#S
\robExtShowPlaceholders*#S
\robExtShowPlaceholdersContents#S
\robExtShowPlaceholdersContents*#S
\robExtWriteFile{arg}#S