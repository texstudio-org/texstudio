# xsim package
# Matthew Bertucci 2/14/2022 for v0.21

#include:l3keys2e
#include:xsimverb
#include:array
#include:booktabs
#include:translations

#keyvals:\usepackage/xsim#c
verbose
final
clear-aux
no-files
use-files
use-aux
blank
#endkeyvals

\xsimsetup{options%keyvals}

#keyvals:\xsimsetup#c
path=%<file path%>
file-extension=%<extension%>
split-aux-lists=%<string%>
goal-print={%<code%>}
tags={%<tag1,tag2,...%>}
topics={%<topic1,topic2,...%>}
tags/ignore-untagged#true,false
topics/ignore-untagged#true,false
tags/use-unmatched#true,false
topics/use-untagged#true,false
exercise/print#true,false
exercise/use#true,false
exercise/collect#true,false
exercise/within=%<counter%>
exercise/the-counter={%<code%>}
exercise/template=%<template%>
solution/template=%<template%>
exercise/name=%<name%>
solution/name=%<name%>
exercise/heading=%<heading command%>
solution/heading=%<heading command%>
exercise/pre-hook={%<code%>}
exercise/begin-hook={%<code%>}
exercise/end-hook={%<code%>}
exercise/post-hook={%<code%>}
solution/print#true,false
solution/pre-hook={%<code%>}
solution/begin-hook={%<code%>}
solution/end-hook={%<code%>}
solution/post-hook={%<code%>}
collection/%<name%>/match-all#true,false
collection/%<name%>/match-any#true,false
collect#true,false
print-collection/headings#true,false
print-collection/headings-template=%<template%>
print-collection/print=#exercises,solutions,both
random/sort#true,false
random/collection=%<collection%>
random/exclude={%<list of ids%>}
random/print=#exercises,solutions,both
print-solutions/headings#true,false
print-solutions/headings-template=%<template%>
print-solutions/section=#true,false,%<integer%>
print-solutions/chapter=#true,false,%<integer%>
print-solutions/collection=#false,%<collection%>
grading-table/template=%<template%>
grading-table/type=%<type%>
load-style={%<list of styles%>}
blank/blank-style={%<code%>}
blank/filled-style={%<code%>}
blank/style={%<code%>}
blank/scale=%<factor%>
blank/width=##L
blank/linespread=%<factor%>
blank/line-increment=##L
blank/line-minimum-length=##L
blank/fill#true,false
%xsimexertag
#endkeyvals

\begin{exercise}
\begin{exercise}[properties%keyvals]
\end{exercise}

#keyvals:\begin{exercise}#c
ID=%<text%>
counter-value=%<integer%>
subtitle=%<text%>
points=%<number%>
bonus-points=%<number%>
print#true,false
print!#true,false
use#true,false
use!#true,false
used#true,false
solution#true,false
tags={%<tag1,tag2,...%>}
topics={%<topic1,topic2,...%>}
page=%<text%>
page-value=%<integer%>
section=%<text%>
section-value=%<integer%>
chapter=%<text%>
chapter-value=%<integer%>
sectioning={%<section numbers%>}
exercise-body={%<code%>}
solution-body={%<code%>}
%xsimexerprop
%xsimexertag
#endkeyvals

\begin{solution}
\begin{solution}[options%keyvals]
\end{solution}

#keyvals:\begin{solution}#c
template=%<template%>
name=%<name%>
heading=%<heading command%>
print#true,false
pre-hook={%<code%>}
begin-hook={%<code%>}
end-hook={%<code%>}
post-hook={%<code%>}
#endkeyvals

\DeclareExerciseType{type}{parameters%keyvals}#N
\numberofexercises#*

#keyvals:\DeclareExerciseType#c
exercise-env=%<envname%>
solution-env=%<envname%>
exercise-name=%<name%>
exercises-name=%<name%>
solution-name=%<name%>
solutions-name=%<name%>
exercise-template=%<template%>
solution-template=%<template%>
counter=%<counter%>
within=%<counter%>
the-counter=%<code%>
solution-counter=%<counter%>
number=%<integer%>
exercise-heading=%<heading command%>
solution-heading=%<heading command%>
%xsimexerparam
#endkeyvals

\DeclareExerciseParameter{parameter%specialDef}#s#%xsimexerparam
\DeclareExerciseParameter*{parameter%specialDef}#s#%xsimexerparam
\SetExerciseParameter{type}{parameter}{value}
\SetExerciseParameters{type}{parameters}

\DeclareExerciseProperty{property%specialDef}#s#%xsimexerprop
\DeclareExerciseProperty*{property%specialDef}#s#%xsimexerprop
\DeclareExerciseProperty!{property%specialDef}#s#%xsimexerprop
\DeclareExerciseProperty-{property%specialDef}#s#%xsimexerprop
\DeclareExercisePropertyAlias{property1%specialDef}{property2}#s#%xsimexerprop

\DeclareExerciseGoal{goal%specialDef}#s#%xsimexerprop
\TotalExerciseTypeGoal{type}{goal}{singular}{plural}
\TotalExerciseTypeGoals{type}{list of goals}{singular}{plural}
\TotalExerciseGoal{goal}{singular}{plural}
\TotalExerciseGoals{list of goals}{singular}{plural}
\AddtoExerciseTypeGoal{type}{goal}{value}
\AddtoExerciseTypeGoalPrint{type}{goal}{value}{singular}{plural}
\AddtoExerciseGoal{goal}{value}
\AddtoExerciseGoalPrint{goal}{value}{singular}{plural}
\ExerciseGoalValuePrint{value}{singular}{plural}
\printgoal{value}
\printpoints{type}
\printtotalpoints
\addpoints{value}
\addpoints*{value}
\points{value}
\printbonus{type}
\printtotalbonus
\addbonus{value}
\addbonus*{value}

\DeclareExerciseTagging{tag%specialDef}#s#%xsimexertag
\ProvideExerciseTagging{tag%specialDef}#s#%xsimexertag

\printexercise{type}{list of ids}
\xprintexercise{type}{list of ids}

\DeclareExerciseCollection{name}
\DeclareExerciseCollection[tag values]{name}
\activatecollection{collection name}
\deactivatecollection{collection name}
\collectexercises{collection name}
\collectexercisesstop{collection name}

\printcollection{collection name}
\printcollection[options%keyvals]{collection name}

#keyvals:\printcollection#c
headings#true,false
headings-template=%<template%>
print=#exercises,solutions,both
#endkeyvals

\printrandomexercises{number}
\printrandomexercises[options%keyvals]{number}

#keyvals:\printrandomexercises#c
sort#true,false
collection=%<collection%>
exclude={%<list of ids%>}
print=#exercises,solutions,both
#endkeyvals

\printsolutionstype{type}
\printsolutionstype[options%keyvals]{type}
\printsolutionstype*{type}
\printsolutionstype*[options%keyvals]{type}
\printsolutions
\printsolutions[options%keyvals]
\printsolutions*
\printsolutions*[options%keyvals]
\printallsolutions
\printallsolutions[options%keyvals]
\printallsolutions*
\printallsolutions*[options%keyvals]
\printsolution{type}{id}
\printsolution[options%keyvals]{type}{id}
\xprintsolution{type}{id}

#keyvals:\printsolutionstype#c,\printsolutionstype*#c,\printsolutions#c,\printsolutions*#c,\printallsolutions#c,\printallsolutions*#c,\printsolution#c
headings#true,false
headings-template=%<template%>
section=#true,false,%<integer%>
chapter=#true,false,%<integer%>
collection=#false,%<collection%>
%xsimexertag
#endkeyvals

\gradingtable
\gradingtable[options%keyvals]

#keyvals:\gradingtable#c
template=%<template%>
type=%<type%>
#endkeyvals

\IfExerciseGoalTF{goal}{relation and value}{true}{false}
\IfExerciseGoalT{goal}{relation and value}{true}
\IfExerciseGoalF{goal}{relation and value}{false}
\IfExerciseGoalSingularTF{goal}{true}{false}
\IfExerciseGoalSingularT{goal}{true}
\IfExerciseGoalSingularF{goal}{false}
\IfExerciseTypeGoalsSumTF{type}{list of goals}{relation and value}{true}{false}
\IfExerciseTypeGoalsSumT{type}{list of goals}{relation and value}{true}
\IfExerciseTypeGoalsSumF{type}{list of goals}{relation and value}{false}
\IfExerciseGoalsSumTF{type}{list of goals}{relation and value}{true}{false}
\IfExerciseGoalsSumT{type}{list of goals}{relation and value}{true}
\IfExerciseGoalsSumF{type}{list of goals}{relation and value}{false}
\TotalExerciseTypeGoal{goal}{type}{singular}{plural}
\TotalExerciseGoal{goal}{singular}{plural}

\IfExercisePropertyExistTF{property}{true}{false}
\IfExercisePropertyExistT{property}{true}
\IfExercisePropertyExistF{property}{false}
\IfExercisePropertySetTF{property}{true}{false}
\IfExercisePropertySetT{property}{true}
\IfExercisePropertySetF{property}{false}
\GetExerciseProperty{property}
\GetExercisePropertyTF{property}{true}{false}
\GetExercisePropertyT{property}{true}
\GetExercisePropertyF{property}{false}
\GetExerciseBody{exercise|solution}
\GetExerciseIdForProperty{property}{value}
\GetExerciseTypeForProperty{property}{value}
\SetExerciseProperty{property}{value}
\SetExpandedExerciseProperty{property}{value}
\ExerciseSetProperty{type}{id}{property}{value}
\ExerciseSetExpandedProperty{type}{id}{property}{value}
\IfExerciseBooleanPropertyTF{property}{true}{false}
\IfExerciseBooleanPropertyT{property}{true}
\IfExerciseBooleanPropertyF{property}{false}
\GetExerciseAliasProperty{property}
\SaveExerciseProperty{property}{macro%cmd}#d
\GlobalSaveExerciseProperty{property}{macro%cmd}#d
\ExercisePropertyIfSetTF{type}{id}{property}{true}{false}
\ExercisePropertyIfSetT{type}{id}{property}{true}
\ExercisePropertyIfSetF{type}{id}{property}{false}
\ExercisePropertyGet{type}{id}{property}
\ExercisePropertyGetAlias{type}{id}{property}
\ExercisePropertySave{type}{id}{property}{macro%cmd}#d
\ExercisePropertyGlobalSave{type}{id}{property}{macro%cmd}#d

\GetExerciseParameter{parameter}
\GetExerciseParameterTF{parameter}{true}{false}
\GetExerciseParameterT{parameter}{true}
\GetExerciseParameterF{parameter}{false}
\GetExerciseName
\GetExerciseHeadingF{false}
\ExerciseParameterGet{type}{parameter}
\IfExerciseParameterSetTF{parameter}{true}{false}
\IfExerciseParameterSetT{parameter}{true}
\IfExerciseParameterSetF{parameter}{false}
\ExerciseParameterIfSetTF{type}{parameter}{true}{false}
\ExerciseParameterIfSetT{type}{parameter}{true}
\ExerciseParameterIfSetF{type}{parameter}{false}

\ForEachExerciseTag{type}{code}
\ListExerciseTags{type}{between}
\UseExerciseTags{type}{between two}{between}{between last two}
\IfExerciseTagSetTF{value}{true}{false}
\IfExerciseTagSetT{value}{true}
\IfExerciseTagSetF{value}{false}
\IfExerciseTopicSetTF{value}{true}{false}
\IfExerciseTopicSetT{value}{true}
\IfExerciseTopicSetF{value}{false}

\UseExerciseTemplate{type}{name}
\ExerciseType
\ExerciseID
\ExerciseText
\ExerciseCollection
\numberofusedexercises
\ExerciseTableType{code}
\IfInsideSolutionTF{true}{false}
\IfInsideSolutionT{true}
\IfInsideSolutionF{false}
\IfSolutionPrintTF{true}{false}
\IfSolutionPrintT{true}
\IfSolutionPrintF{false}
\IfExistSolutionTF{true}{false}
\IfExistSolutionT{true}
\IfExistSolutionF{false}
\ForEachPrintedExerciseByType{code}
\ForEachUsedExerciseByType{code}
\ForEachUsedExerciseByOrder{code}
\ForEachPrintedExerciseByID{code}
\ForEachUsedExerciseByID{code}
\XSIMprint{exercise|solution}{type}{id}
\XSIMxprint{exercise|solution}{type}{id}
\XSIMtranslate{keyword}
\XSIMexpandcode{code}
\XSIMifchapterTF{true}{false}
\XSIMifchapterT{true}
\XSIMifchapterF{false}
\XSIMmixedcase{code}
\XSIMputright%<\macro%>{%<code%>}
\XSIMifeqTF{code1}{code2}{true}{false}
\XSIMifeqT{code1}{code2}{true}
\XSIMifeqF{code1}{code2}{false}
\XSIMifblankTF{code}{true}{false}
\XSIMifblankT{code}{true}
\XSIMifblankF{code}{false}
\XSIMatbegindocument{code}
\XSIMatenddocument{code}

\DeclareExerciseEnvironmentTemplate{name}{begin code}{end code}
\DeclareExerciseHeadingTemplate{name}{code}
\DeclareExerciseTableTemplate{name}{code}

\xsimstyle{style name}
\xsimstyle*{style name}
\loadxsimstyle{list of style names}

\DeclareExerciseTranslation{language}{keyword}{translation}
\DeclareExerciseTranslations{keyword}{translations}
\XSIMtranslate{keyword}
\ForEachExerciseTranslation{code}

\blank{text}
\blank[options%keyvals]{text}
\blank*{text}
\blank*[options%keyvals]{text}

#keyvals:\blank#c,\blank*#c
blank-style={%<code%>}
filled-style={%<code%>}
style={%<code%>}
scale=%<factor%>
width=##L
linespread=%<factor%>
line-increment=##L
line-minimum-length=##L
#endkeyvals

\ExerciseTableCode
\numberofcolumns
\theexercise
\ParameterValue
\PropertyValue

# not documented
\DeclareGradeDistribution{arg}#S
\GetGradeRequirementForGoals{arg1}{arg2}{arg3}{arg4}#S
\GetGradeRequirementForGoal{arg1}{arg2}{arg3}{arg4}#S
\GetGradeRequirement{arg1}{arg2}{arg3}#S
\examspace{arg}#S
\examspace*{arg}#S
\goalsforgrade{arg1}{arg2}#S
\pointsforgrade{arg}#S
\printforexercises*{arg}#S
\printforexercises{arg}#S
\totalgoalforgrade{arg}#S
