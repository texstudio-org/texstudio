# templatetools package
# Matthew Bertucci 2023/05/23 for v0.2

#include:array
#include:etoolbox
#include:ifdraft
#include:iftex
#include:ltxcmds
#include:scrlfile

\IfDefined{command}{code-defined}
\IfUndefined{command}{code-undefined}
\IfElseDefined{command}{code-defined}{code-undefined}
\IfElseUndefined{command}{code-undefined}{code-defined}
\IfMultDefined{list of commands%cmd}{code-defined}{code-undefined}

\IfDraft{draft-mode-active code}
\IfNotDraft{draft-mode-disabled code}
\IfNotDraftElse{draft-mode-active code}{draft-mode-disabled code}

\IfPackageLoaded{package}{is-loaded code}
\IfPackageNotLoaded{package}{is-not-loaded code}
\IfPackagesLoaded{list of packages}{all-are-loaded code}
\IfPackagesNotLoaded{list of packages}{none-are-loaded code}
\IfElsePackageLoaded{package}{is-loaded code}{is-not-loaded code}

\ExecuteAfterPackage{package}{code}
\ExecuteBeforePackage{package}{code}

\IfTikzLibraryLoaded{library}{if-loaded code}

\IfColumntypeDefined{column type}{code-defined}{code-undefined}
\IfColumntypesDefined{column type}{code-undefined}{code-defined}

\IfColorDefined{color}{code-defined}{code-undefined}
\IfColorsDefined{color}{code-undefined}{code-defined}

\IfMathVersionDefined{font version}{code-defined}{code-undefined}

\IfGlossariesStyleDefined{style name}{code-defined}

\IfBibEnvironmentDefined{envname}{code-defined}

\SetTemplateDefinition{group}{property}{code}
\UseDefinition{group}{property}

\CheckIfColumntypeDefined{column type}#*
\isColumntypeDefined{column type}#*
