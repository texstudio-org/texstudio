#cwl for newclude package, v.2
\include*[prehook]{file}[posthook]#i
\IncludeSurround#*
\DefaultIncludeSurround#*
\include[prehook]{file}[posthook]#i
\AtBeginInclude{tokens}#*
\AtEndInclude{tokens}#*
\includeonly{file}
\includeall
\includeenv[prehook]{file}{envname}{instance}[posthook]#*i
\includeenv*[prehook]{file}{envname}{instance}[posthook]#*i
\includedoc[prehook]{file}[posthook]#*i
\includedoc*[prehook]{file}[posthook]#*i
\IfAllowed {part}{true}{false}#*
\IncludeName#*
\ParentName#*
\DeclareFormattingPackage{packagename}#*
\ifSkipPreamble#*
\SkipPreambletrue#*
\SkipPreamblefalse#*
\Disable{tokens}#*
\DisableAll#*
#I did my best, eboebo.
