# bubblesort package
# Matthew Bertucci 11/13/2021 for v1.1

#include:etoolbox

\bubblesort{list}{macro%cmd}#d
\bubblesort[comparator cmd]{list}{macro%cmd}#d

\doublebubblesort{list1}{macro1%cmd}{list2}{macro2%cmd}#d
\doublebubblesort[comparator cmd]{list1}{macro1%cmd}{list2}{macro2%cmd}#d

\bubblesortflag
\realSort{arg1}{arg2}
\alphSort{arg1}{arg2}
\ta#S
\tb#S
\leftappendItem{%<arg1%>}\to{%<arg2%>}#S
\to#S