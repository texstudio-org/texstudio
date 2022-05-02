# exercisebank package
# Matthew Bertucci 4/13/2022 for v0.3.0

#include:xstring
#include:pgffor
#include:scrextend
#include:comment
#include:calc
#include:pgfpages
#include:geometry
#include:listofitems
#include:trimspaces
#include:needspace

## Environments ##
\DisplaySolutions
\SolutionsOnly
\begin{problem}
\end{problem}
\begin{solution}
\end{solution}
\begin{intro}
\end{intro}

## Making sets ##
\makesetdefaults{}
\spritesets{}
\makeset{name}{file}#i
\makeset[options%keyvals]{name}{file}#i
\phead
\about{text}
\buildall
\sprite
\sprite[number]
\exec{code}
\DeclareExerciseCommand{cmd}{def}#d
\DeclareExerciseCommand{cmd}[args]{def}#d
\exclude{file}{list of numbers}
\select{file}{list of numbers}
\buildset{name}
\buildset[options%keyvals]{name}
\setName
\buildsets{list of names}
\buildsets[options%keyvals]{list of sets}
\buildtags{list of tags}{list of sets}
\buildsprite{list of sets}
\pplabel{label}#l
\ppref{label}#r
\ppgref{label}#r
\pref{label}#r
\pgref{label}#r
\HideTags{list of tags}
\ShowAllTags
\exercisenote{text}

## Configuration and options ##
\ShowNumbers
\ShowTags
\ShowFilenames

\exercisebanksetup{options%keyvals}
#keyvals:\exercisebanksetup
part problems
tighten paragraphs
problem header
problem needs space
no needspace
part problem header
part problem header suffix
solution header
exercise directory
figure root directory
use margins
front page
style margins
show lonely part problems
current points style
disable points
#endkeyvals

## Internationalization ##
\translateExBank{keyvals}
#keyvals:\translateExBank

#endkeyvals

## Problem options: points and tagging ##
\nextproblem{options%keyvals}
#keyvals:\nextproblem#c
head=%<text%>
solution only
points=%<number%>
hide
tag=%<tag%>
tag={%<tag1,tag2,...%>}
#endkeyvals

\totalpoints
\exercisepoints

## Triggers ##
\Trigger%<\macro%>
\PartProblemHeaderSuffix
\PostPPHeader
\BeginPartproblem
\VeryBeginPartproblem
\InputExercise
\BeginProblem
\EndProblem
\BeginBuildset
\EndBuildset

## General reference ##
\ownLineNoSpacesGotIt
\exercisebankversion#*
\exercisebankbuild#*
\At%<\macro%>
\thisfilepath
\exerciseFile

## Counters ##
\theproblemcounter#*
\thepartproblemcounter#*

## Lengths and margins ##
\pMarginBelow#*
\pMarginAbove#*
\pMarginLeft#*
\ppMarginBelow#*
\ppMarginAbove#*
\ppMargin#*
\introOutdent#*

# deprecated
\setExercisesDir{directory}#S

# not documented
\AtNextPar{code}#*
\buildex{file}#*i
\continueLoop#*
\csvlist#*
\csvsets#*
\csvtags#*
\ea#S 
\emptyList#*
\exerciseFileInfo#*
\exfile#*
\figuresPath#*
\fileInputBase#*
\fileInputPath#*
\firstarg#S
\haystack#*
\ifppMode{arg}#*
\ignoreOutlineSpaces#*
\incl{file}#*i
\introarg#*
\ipm{arg}#*
\isFalse#*
\isInList#*
\isppMode{arg1}{arg2}#*
\isTrue#*
\keystring#*
\listarg#*
\marginw#*
\markeverypar#*
\mname#*
\ncArgs#*
\needle#*
\nextprobargs#*
\nextproblems{arg}#*
\nohead#*
\numppex#*
\obeyOutlineSpaces#*
\oldep#S
\orderedselect{arg1}{arg2}#*
\ppList#*
\ppMode#*
\pppref{arg1}#*
\pptag#*
\removebs{arg1}#*
\resetnextproblems#*
\setmacro#*
\showhideproblem{arg}#*
\shownextchar{arg}#*
\skeys#*
\solutionMarginAbove#*
\squeeze#*
\stopfilbreak#*
\strif{arg1}{arg2}#*
\themetacounter#*
\thenumppInFile#*
\theset#*
\thissetid#*
\tmpargs#*
\tpd#S
\whenfalse#*
\whentrue#*