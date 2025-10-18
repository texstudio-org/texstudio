# glossaries-extra-stylemods package
# Matthew Bertucci 2025/10/17 for v1.8

#keyvals:\usepackage/glossaries-extra-stylemods#c
all
inline
list
tree
mcols
long
longragged
longbooktabs
super
superragged
bookindex
longextra
topic
table
#endkeyvals

#ifOption:all
#include:glossary-inline
#include:glossary-list
#include:glossary-tree
#include:glossary-mcols
#include:glossary-long
#include:glossary-longragged
#include:glossary-longbooktabs
#include:glossary-super
#include:glossary-superragged
#include:glossary-bookindex
#include:glossary-longextra
#include:glossary-topic
#include:glossary-table
#endif
#ifOption:inline
#include:glossary-inline
#endif
#ifOption:list
#include:glossary-list
#endif
#ifOption:tree
#include:glossary-tree
#endif
#ifOption:mcols
#include:glossary-mcols
#endif
#ifOption:long
#include:glossary-long
#endif
#ifOption:longragged
#include:glossary-longragged
#endif
#ifOption:longbooktabs
#include:glossary-longbooktabs
#endif
#ifOption:super
#include:glossary-super
#endif
#ifOption:superragged
#include:glossary-superragged
#endif
#ifOption:bookindex
#include:glossary-bookindex
#endif
#ifOption:longextra
#include:glossary-longextra
#endif
#ifOption:topic
#include:glossary-topic
#endif
#ifOption:table
#include:glossary-table
#endif

\glsxtrprelocation#*
\glslistprelocation#*
\glslistchildprelocation#*
\glslistdesc{gls-label}#*
\glslistitem{gls-label}#*
\glsaltlistitem{gls-label}#*
\glslistgroupheaderitem{group-label}{header code}#*
\glslistgroupafterheader#*
\glslistchildpostlocation#*
\glslistgroupskip#*
\glstreedefaultnamefmt{text}#*
\glstreegroupskip#*
\glstreegroupheaderskip#*
\glstreePreHeader{gls-label}{title%text}#*
\glsalttreepredesc#*
\glsalttreechildpredesc#*
\glstreeprelocation#*
\glstreechildprelocation#*
\glstreenonamedesc{gls-label}#*
\glstreenonamesymbol{gls-label}#*
\glstreenonamechilddesc{gls-label}#*
\glstreedesc{gls-label}#*
\glstreesymbol{gls-label}#*
\glstreechilddesc{gls-label}#*
\glstreenonameDescLoc{gls-label}{location}#*
\glstreenonameChildDescLoc{gls-label}{location}#*
\glstreechildsymbol{gls-label}#*
\glstreeDescLoc{gls-label}{location}#*
\glstreeChildDescLoc{gls-label}{location}#*
\glstreeNoDescSymbolPreLocation#*
\glstreesubgroupitem{prev-group-level}{level}{parent-label}{group-label}{group-title}#*
\gglssetwidest{name}#*
\gglssetwidest[level]{name}#*
\eglssetwidest{name}#*
\eglssetwidest[level]{name}#*
\xglssetwidest{name}#*
\xglssetwidest[level]{name}#*
\glsupdatewidest{name}#*
\glsupdatewidest[level]{name}#*
\gglsupdatewidest{name}#*
\gglsupdatewidest[level]{name}#*
\eglsupdatewidest{name}#*
\eglsupdatewidest[level]{name}#*
\xglsupdatewidest{name}#*
\xglsupdatewidest[level]{name}#*
\glsgetwidestname#*
\glsgetwidestsubname{level}#*
\glsFindWidestTopLevelName#*
\glsFindWidestTopLevelName[glossary list]#*
\glsFindWidestUsedTopLevelName#*
\glsFindWidestUsedTopLevelName[glossary list]#*
\glsFindWidestUsedAnyName#*
\glsFindWidestUsedAnyName[glossary list]#*
\glsFindWidestAnyName#*
\glsFindWidestAnyName[glossary list]#*
\glsFindWidestUsedLevelTwo#*
\glsFindWidestUsedLevelTwo[glossary list]#*
\glsFindWidestLevelTwo#*
\glsFindWidestLevelTwo[glossary list]#*
\glsFindWidestUsedAnyNameSymbol{register%cmd}#*d
\glsFindWidestUsedAnyNameSymbol[glossary list]{register%cmd}#*d
\glsFindWidestAnyNameSymbol{register%cmd}#*d
\glsFindWidestAnyNameSymbol[glossary list]{register%cmd}#*d
\glsFindWidestUsedAnyNameSymbolLocation{sym register%cmd}{loc register}#*d
\glsFindWidestUsedAnyNameSymbolLocation[glossary list]{sym register%cmd}{loc register}#*d
\glsFindWidestAnyNameSymbolLocation{sym register%cmd}{loc register}#*d
\glsFindWidestAnyNameSymbolLocation[glossary list]{sym register%cmd}{loc register}#*d
\glsFindWidestUsedAnyNameLocation{register%cmd}#*d
\glsFindWidestUsedAnyNameLocation[glossary list]{register%cmd}#*d
\glsFindWidestAnyNameLocation{register%cmd}#*d
\glsFindWidestAnyNameLocation[glossary list]{register%cmd}#*d
\glsxtralttreeSymbolDescLocation{gls-label}{number list}#*
\glsxtralttreeSubSymbolDescLocation{gls-label}{number list}#*
\glsxtralttreeInit#*
\glsxtrAltTreeIndent#*
\glsxtrAltTreePar#*
\glsxtrAltTreeSetHangIndent#*
\glsxtrAltTreeSetSubHangIndent#*
\glsxtrComputeTreeIndent{gls-label}#*
\glsxtrComputeTreeSubIndent{level}{gls-label}{register%cmd}#*d
\glsxtrtreechildpredesc#*
\glsxtrtreepredesc#*
\glsxtrtreetopindent#*
\glsindexingsetting{prev-group-level}{level}{parent-label}{group-label}{group-title}#*

# not documented
\glsalttreesubgroupheader{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
