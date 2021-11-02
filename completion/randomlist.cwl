# randomlist package
# Matthew Bertucci 10/29/2021 for v1.3

#include:xkeyval

\NewList{list}
\ShowList{list}

\ShiftList{list}{start}{number}

\InsertFirstItem{list}{content}
\InsertLastItem{list}{content}
\InsertItem{list}{index}{content}
\InsertRandomItem{list}{content}
\InsertList{receive list}{index}{insert list}

\ExtractFirstItem{list}{macro}
\ExtractLastItem{list}{macro}
\ExtractItem{list}{index}{macro}
\ExtractRandomItem{list}{macro}
\ExtractList{main list}{start index}{end index}{receive list}

\SetFirstItem{list}{content}
\SetLastItem{list}{content}
\SetItem{list}{index}{content}
\SetRandomItem{list}{content}
\SetList{list}{list of contents}
\ClearList{list}
\CopyList{list1}{list2}

\GetFirstItem{list}{macro}
\GetLastItem{list}{macro}
\GetItem{list}{index}{macro}
\GetRandomItem{list}{macro}
\GetList{read list}{start index}{end index}{written list}

\ForEachFirstItem{list}{macro}{code}
\ForEachLastItem{list}{macro}{code}
\ForEachRandomItem{list}{macro}{code}

\ReadFieldItem{record}{rank}{macro}
\ReadFileList{list}{file}
\ReadFileList[separator]{list}{file}

\RLuniformdeviate{number}{macro}
\RLsetrandomseed{value}

\CountList{list}{macro}

\RandomItemizeList{%<item1%>}{%<item2%>}%<{item3}...%>
\RandomEnumerateList{%<item1%>}{%<item2%>}%<{item3}...%>

\RandomListLoaded#S
\RLAtCatcode#S
\RLfor#S