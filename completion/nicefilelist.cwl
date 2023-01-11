# nicefilelist package
# Matthew Bertucci 2023/01/08 for v0.9a

#include:monofill
#include:myfilist

#keyvals:\usepackage/nicefilelist#c
r
wrap
autolength
#endkeyvals

#ifOption:wrap
#include:hardwrap
#endif

#ifOption:autolength
#include:xstring
#endif

\NFLspaceI
\NFLspaceII
\NFLspaceIII
\NFLnodate
\NFLnoversion
\NFLnotfound
\MaxBaseEmptyList{longest-name}
\MaxBaseEmptyList{longest-name}[read-again-files]
\MaxBaseEmptyList*
\MaxBaseEmptyList*[read-again-files]
\maxBaseEmptyList{longest-name}#S
\maxBaseEmptyList{longest-name}[read-again-files]#S
\ifNFLwrap#S
\NFLwraptrue#S
\NFLwrapfalse#S
\ifNFLautolength#S
\NFLautolengthtrue#S
\NFLautolengthfalse#S
