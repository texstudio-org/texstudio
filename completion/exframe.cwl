# exframe package
# Matthew Bertucci 1/12/2021 for v3.4

#include:color
#include:verbatim
#include:xkeyval

#ifOption:metastr
#include:metastr
#endif
#ifOption:metastr=true
#include:metastr
#endif

#keyvals:\usepackage/exframe#c
extdata#true,false
extstyle#true,false
metastr#true,false
problemenv=%<name%>
subproblemenv=%<name%>
solutionenv=%<name%>
sheetenv=%<name%>
problemcounter=%<name%>
subproblemcounter=%<name%>
solutioncounter=%<name%>
sheetcounter=%<name%>
#endkeyvals

\exercisesetup{options%keyvals}

#keyvals:\usepackage/exframe#c,\exercisesetup
solutions#true,false
pdfdata=#auto,manual,sheet,off
lineno#true,false
twoside#true,false
solutionhref#true,false
warntext#true,false
autolabelsheet#true,false
autolabelproblem#true,false
solutionbuf#true,false
problembuf#true,false
emptytestchar=%<char%>
#endkeyvals

\begin{problem}
\begin{problem}[options%keyvals]
\end{problem}

#keyvals:\begin{problem},\setproblemdata
title={%<text%>}
rawtitle={%<text%>}
%userproblemdatakey
#endkeyvals

#keyvals:\getproblemdata
title
rawtitle
%userproblemdatakey
#endkeyvals

\begin{subproblem}
\begin{subproblem}[options%keyvals]
\end{subproblem}

\begin{solution}
\begin{solution}[options%keyvals]
\end{solution}

#keyvals:\begin{problem},\begin{subproblem},\begin{solution}
author={%<text%>}
editor={%<text%>}
source={%<text%>}
difficulty={%<text%>}
keyword={%<text%>}
comment={%<text%>}
optional={%<text%>}
%userprobleminfokey
#endkeyvals

#keyvals:\showprobleminfo
author#true,false
editor#true,false
source#true,false
difficulty#true,false
keyword#true,false
comment#true,false
optional#true,false
%userprobleminfokey
#endkeyvals

#ifOption:extdata
#keyvals:\begin{problem},\begin{subproblem},\begin{solution}
review={%<text%>}
recycle={%<text%>}
timesolve={%<text%>}
timepresent={%<text%>}
#endkeyvals
#keyvals:\showprobleminfo
review#true,false
recycle#true,false
timesolve#true,false
timepresent#true,false
#endkeyvals
#endif
#ifOption:extdata=true
#keyvals:\begin{problem},\begin{subproblem},\begin{solution}
review={%<text%>}
recycle={%<text%>}
timesolve={%<text%>}
timepresent={%<text%>}
#endkeyvals
#keyvals:\showprobleminfo
review#true,false
recycle#true,false
timesolve#true,false
timepresent#true,false
#endkeyvals
#endif

\begin{sheet}
\begin{sheet}[options%keyvals]
\end{sheet}

#keyvals:\begin{sheet},\setsheetdata
due={%<text%>}
handout={%<text%>}
title={%<text%>}
rawtitle={%<text%>}
author={%<text%>}
editor={%<text%>}
editdate={%<text%>}
%usersheetdatakey
points=%<points%>
#endkeyvals

#keyvals:\getsheetdata
due
handout
title
rawtitle
author
editor
editdate
%usersheetdatakey
points
#endkeyvals

\ifsolutions
\begin{onlysolutions}
\end{onlysolutions}
\insertsolutions
\writesolutions
\writesolutions[file]
\readsolutions#i
\readsolutions[file]#i
\insertproblems
\writeproblems
\writeproblems[file]
\readproblems#i
\readproblems[file]#i

\exercisedata{keyvals}

#keyvals:\exercisedata
author={%<text%>}
title={%<text%>}
date={%<text%>}
subject={%<text%>}
keyword={%<text%>}
course={%<text%>}
institution={%<text%>}
instructor={%<text%>}
period={%<text%>}
material={%<text%>}
%userdatakey
#endkeyvals

\defexercisedata{key%specialDef}#s#%userdatakey
\getexercisedata{key%keyvals}

#keyvals:\getexercisedata
author
title
date
subject
keyword
course
institution
instructor
period
material
%userdatakey
#endkeyvals

\exercisedataempty{key%plain}{empty code}{filled code}

\defsheetdata{key%specialDef}#s#%usersheetdatakey
\setsheetdata{keyvals}
\getsheetdata{key%keyvals}
\sheetdataempty{key%plain}{empty code}{filled code}

\defproblemdata{key%specialDef}#s#%userproblemdatakey
\setproblemdata{keyvals}
\getproblemdata{key%keyvals}
\problemdataempty{key%plain}{empty code}{filled code}

\writeexercisedata

\showprobleminfo{keys%keyvals}
\defprobleminfo{key%specialDef}{code}#s#%userprobleminfokey

\addprobleminfo{info}
\addprobleminfo*{info}

#keyvals:\begin{problem},\begin{subproblem}
points=%<points%>
#endkeyvals

#keyvals:\begin{sheet},\begin{problem},\begin{subproblem}
label=##l
tag=%<tag%>
#endkeyvals

\showpoints
\getsheetpoints{tag}
\getproblempoints{tag}
\getsubproblempoints{tag}
\getsolutionpoints{tag}
\extractpoints
\extractpoints*
\switchpoints{reg}{bonus}{both}{none}{val}
\awardpoints{points}
\awardpoints[details]{points}
\awardpoints*{points}
\awardpoints*[details]{points}

\sheettag
\problemtag
\subproblemtag

\getsheetlist{}
\getproblemlist{tag}
\getproblemlist*
\getsubproblemlist{tag}

\exerciseloop{items}{command}
\exerciseloopstr{items}{string}
\exerciseloopstr[macro%cmd]{items}{string}#d
\exerciseloopret#*
\theexerciseloop#*

\exerciseconfig{key%keyvals}{definition}
\exerciseconfig{key%keyvals}[args]{definition}
\exerciseconfigappend{key%keyvals}{definition}
\exerciseconfigprepend{key%keyvals}{definition}
\getexerciseconfig{key%keyvals}
\getexerciseconfig{key%keyvals}[args]
\exerciseconfigempty{key%plain}{empty code}{filled code}

#keyvals:\exerciseconfig,\exerciseconfigappend,\exerciseconfigprepend,\getexerciseconfig
termsheet
termsheets
termproblem
termproblems
termsolution
termsolutions
termpoint
termpoints
styletext
styletextproblem
styletextsolution
styletitle
styletitleproblem
styletitlesubproblem
styletitlesolution
styletitlesolutionsproblem
styletitlesolutions
styletitleproblems
skipproblemabove
skipproblembelow
skipproblemtitle
skipprobleminfo
skipproblemitem
skipsubproblemabove
skipsubproblembelow
skipsubproblemtitle
skipsubprobleminfo
skipsubproblemitem
skipsolutionabove
skipsolutionbelow
skipsolutiontitle
skipsolutioninfo
skipsolutionitem
skipsolutionitemsub
skipsolutionsabove
skipsolutionsbelow
skipsolutionsproblemabove
skipsolutionsproblemtitle
skipsolutionsproblem
skipsolutionstitle
skipproblemsabove
skipproblemsbelow
skipproblemstitle
insertsheettitle
insertsheetclearpage
insertsheetbefore
insertsheetafter
insertsolutionsbefore
insertsolutionsafter
insertproblemsbefore
insertproblemsafter
insertproblembefore
insertproblemafter
insertproblemsolution
insertprobleminfo
insertproblemselect
insertsubproblembefore
insertsubproblemafter
insertsubprobleminfo
insertsubproblemsolution
insertsolutionbefore
insertsolutionafter
insertsolutioninfo
composeitemsep
composetitlesheet
composemetasheet
composetocsheet
composeitemproblem
composeitemproblemsep
composetitleproblem
composetocproblem
composeitemsubproblem
composeitemsubproblemsep
composetitlesubproblem
composeitemsolution
composeitemsolutionsub
composeitemsolutionsep
composetitlesolutionsingle
composetitlesolutionmulti
composetocsolution
composetitlesolutions
composetitleproblems
composetocsolutions
composetocproblems
composetitlesolutionsproblemsingle
composetitlesolutionsproblemmulti
composeitemsolutionlabel
composepointsnum
composepoints
composepointsstart
composepointsmargin
composepointsbody
composepointssheet
composepointsaward
composepointsawardalt
composepointspair
composepointspairbody
composepointspairstart
composepointspairmargin
composepointspairsheet
composepointspairaward
composepointspairawardalt
composepointspairbodyproblem
composepointspairbodysubproblem
composepointspairbodysolution
composepointspairstartproblem
composepointspairstartsubproblem
composepointspairstartsolution
insertpointsmargin
insertwarnpoints
insertwarnpointsrerun
countersheet
counterproblem
counterproblemmax
countersubproblem
countersubproblemmax
countersheetequation
counterproblemequation
countersolutionequation
tagsheet
tagproblem
tagsubproblem
labelsheet
labelproblem
labelsubproblem
toclevelsheet
toclevelproblem
toclevelproblems
toclevelsolution
toclevelsolutions
extsolutions
extproblems
#endkeyvals

\exerciseifempty{expr}{empty code}{filled code}
\exerciseifnotempty{expr}{filled code}

\exercisestyle{styles%keyvals}

#keyvals:\exercisestyle
solutionbelow=#here,subproblem,subproblem*,problem,problem*,sheet,manual
problempointsat=#start,start*,margin,end,manual
subproblempointsat=#start,start*,margin,end,manual
solutionpointsat=#start,start*,margin,end,manual
problemby=%<counter%>
equationby=%<counter%>
problembysheet
equationbysheet
pagebysheet
sheetequation#true,false
problemequation#true,false
solutionequation#true,false
fracpoints#true,false
twoside#true,false
%userexercisestyle
#endkeyvals

#ifOption:extstyle
#keyvals:\exercisestyle
plainheader
contents
solutionsf
solutiondimproblem
solutionsep
#endkeyvals
#endif
#ifOption:extstyle=true
#keyvals:\exercisestyle
plainheader
contents
solutionsf
solutiondimproblem
solutionsep
#endkeyvals
#endif

\defexercisestyle{style%specialDef}{init}#s#%userexercisestyle
\defexercisestylearg{style%specialDef}{init}#s#%userexercisestyle
\defexercisestylearg[default]{style%specialDef}{init}#s#%userexercisestyle

\begin{printproblem}{keys%plain}#*
\end{printproblem}#*
\begin{printsolution}{keys%plain}#*
\end{printsolution}#*
\closeproblems#*
\closesolutions#*
\exercisecleardoublepage#*
\showfracpoints{arg}#*
\solutionssection{arg}#*
\theHequation#S
\theHpage#S