# nicefilelist package
# Matthew Bertucci 2022/12/10 for v0.8a

#include:monofill
#include:myfilist

#keyvals:\usepackage/nicefilelist#c
r
wrap
#endkeyvals

#ifOption:wrap
#include:hardwrap
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