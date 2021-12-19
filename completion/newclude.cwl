#cwl for newclude package, v.2

#include:moredefs
#include:afterpage

#keyvals:\usepackage/newclude#c
simple
tag
allocate
#endkeyvals

\include[prehook]{file}#i
\include[prehook]{file}[posthook]#i
\include*[prehook]{file}#i
\include*[prehook]{file}[posthook]#i
\AtBeginInclude{tokens}#*
\AtEndInclude{tokens}#*
\IncludeSurround#*
\DefaultIncludeSurround#*
\includeall
\IncludeEnv{file}{envname}{instance}#*i
\IncludeEnv[prehook]{file}{envname}{instance}#*i
\IncludeEnv[prehook]{file}{envname}{instance}[posthook]#*i
\IncludeEnv*{file}{envname}{instance}#*i
\IncludeEnv*[prehook]{file}{envname}{instance}#*i
\IncludeEnv*[prehook]{file}{envname}{instance}[posthook]#*i
\includedoc[prehook]{file}#i
\includedoc[prehook]{file}[posthook]#i
\includedoc*[prehook]{file}#i
\includedoc*[prehook]{file}[posthook]#i
\includedocskip[prehook]{file}[posthook]#*i
\includedocskip*[prehook]{file}[posthook]#*i
\IfAllowed{part name}{true}{false}#*
\IncludeName#*
\ParentName#*
\DeclareFormattingPackage{package name}#*
\ifSkipPreamble#*
\SkipPreambletrue#*
\SkipPreamblefalse#*
\Disable{tokens}#*
\DisableAll#*

#ifOption:allocate
\NextAux#*
\DynamicAux#*
\StaticAux{number of streams}#*
\InitWheel{cmd}#*d
\DefWheel{cmd}{spokes}#*d
\Roll{wheel}#*
\Top{wheel}#*
\AddSpokes{wheel}{spokes}#*
\IfTop{wheel}{spoke}{true}{false}#*
#endif
