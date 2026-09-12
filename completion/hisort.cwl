# hisort package
# Matthew Bertucci 2026/09/10 for v1.1.0

#include:etoolbox
#include:histrings

\AddToList{list}{arg}#*
\CompReversefalse#S
\CompReversetrue#S
\ifCompReverse#*
\ListElementsMustBeUnique{list}#*
\ListInclusionMacro{list}#*
\NoSort{arg1}{arg2}#*
\ReverseSort{test}{arg1}{arg2}#*
\ShowList{list}#*
\SortAlpha{arg1}{arg2}#*
\SortEasyAlpha{arg1}{arg2}#*
\SortLen{arg1}{arg2}#*
\SortNum{arg1}{arg2}#*
\StripForAlpha{arg1}{arg2}#*

# not documented
\IfEmptyList{arg}#S
\IfKnownList{arg}#S
\IfListContains{arg1}{arg2}#S
\NewSortedList{arg1}{arg2}#S